#include "FENParser.h"

FENParser::FENParser(const std::string& fen)
	: m_fen(fen)
	, m_fen_info{}
{}

FENInfo FENParser::Parse()
{
	std::istringstream fen_stream{ m_fen };
	std::string fen_position, fen_current_turn, fen_castling_rights, fen_en_passant, fen_halfmove, fen_fullmove;

	std::getline(fen_stream, fen_position, FEN_DELIMITER);
	std::getline(fen_stream, fen_current_turn, FEN_DELIMITER);
	std::getline(fen_stream, fen_castling_rights, FEN_DELIMITER);
	std::getline(fen_stream, fen_en_passant, FEN_DELIMITER);
	std::getline(fen_stream, fen_halfmove, FEN_DELIMITER);
	std::getline(fen_stream, fen_fullmove, FEN_DELIMITER);

	if (fen_stream.fail())
	{
		throw std::runtime_error("Bad FEN syntax");
	}

	m_fen_info = {};

	ParseChessBoard(fen_position);
	ParseCurrentTurn(fen_current_turn);
	ParseCastlingRights(fen_castling_rights);
	ParseEnPassant(fen_en_passant);
	ParseCounters(fen_halfmove, fen_fullmove);

	return m_fen_info;
}

const std::string& FENParser::get_fen() const
{
	return this->m_fen;
}

void FENParser::set_fen(const std::string& fen)
{
	this->m_fen = fen;
}

bool FENParser::IsFENValid(const std::string& fen)
{
	try
	{
		FENParser(fen).Parse();
	}
	catch (...)
	{
		return false;
	}

	return true;
}

void FENParser::ParseChessBoard(const std::string& fen_position)
{
	if ((std::count(fen_position.begin(), fen_position.end(), 'k') != 1) ||
		(std::count(fen_position.begin(), fen_position.end(), 'K') != 1))
	{
		throw std::runtime_error("Invalid number of kings");
	}

	if (std::count(fen_position.begin(), fen_position.end(), '/') != 7)
	{
		throw std::runtime_error("Invalid number of rows");
	}

	ISXUtility::InitSquares(m_fen_info.chess_board);

	int x = 0, y = 0;
	for (char c : fen_position)
	{
		if (c == '/')
		{
			++y;
			x = 0;
		}
		else if (std::isdigit(c))
		{
			unsigned int count = c - '0';
			while (count--)
			{
				m_fen_info.chess_board.at(y).at(x++).piece = nullptr;
			}
		}
		else if (std::islower(c))
		{
			m_fen_info.chess_board.at(y).at(x).piece = PieceFactory::Create(c, ISXChess::Team::BLACK);

			sf::RectangleShape& square = m_fen_info.chess_board.at(y).at(x).square;
			std::shared_ptr<Piece> piece = m_fen_info.chess_board.at(y).at(x).piece;

			piece->get_sprite().setPosition(square.getPosition());
			piece->get_sprite().setScale(sf::Vector2f(BOARD_SQUARE_INIT_SIZE / 128, BOARD_SQUARE_INIT_SIZE / 128));
			++x;
		}
		else if (std::isupper(c))
		{
			m_fen_info.chess_board.at(y).at(x).piece = PieceFactory::Create(std::tolower(c), ISXChess::Team::WHITE);

			sf::RectangleShape& square = m_fen_info.chess_board.at(y).at(x).square;
			std::shared_ptr<Piece> piece = m_fen_info.chess_board.at(y).at(x).piece;

			piece->get_sprite().setPosition(square.getPosition());
			piece->get_sprite().setScale(sf::Vector2f(BOARD_SQUARE_INIT_SIZE / 128, BOARD_SQUARE_INIT_SIZE / 128));
			++x;
		}
		else
		{
			m_fen_info.chess_board.at(y).at(x++).piece = nullptr;
		}
	}
}

void FENParser::ParseCurrentTurn(const std::string& fen_current_turn)
{
	if (fen_current_turn == "w")
	{
		m_fen_info.current_turn = ISXChess::Team::WHITE;
	}
	else if (fen_current_turn == "b")
	{
		m_fen_info.current_turn = ISXChess::Team::BLACK;
	}
	else
	{
		throw std::runtime_error("Invalid side to move: " + fen_current_turn);
	}
}

void FENParser::ParseCastlingRights(const std::string& fen_castling_rights)
{
	if (fen_castling_rights == "-")
	{
		m_fen_info.castling_rights = {};
		return;
	}

	if (fen_castling_rights.find('K') != std::string::npos)
	{
		m_fen_info.castling_rights.white_king_side = true;
	}
	if (fen_castling_rights.find('Q') != std::string::npos)
	{
		m_fen_info.castling_rights.white_queen_side = true;
	}
	if (fen_castling_rights.find('k') != std::string::npos)
	{
		m_fen_info.castling_rights.black_king_side = true;
	}
	if (fen_castling_rights.find('q') != std::string::npos)
	{
		m_fen_info.castling_rights.black_queen_side = true;
	}
}

void FENParser::ParseEnPassant(const std::string& fen_en_passant)
{
	if (fen_en_passant.empty() || fen_en_passant == "-")
	{
		m_fen_info.en_passant_square = INVALID_POSITION;
	}
	else
	{
		if (!ISXUtility::IsValidPosition(fen_en_passant))
		{
			throw std::runtime_error("En passant square is not valid");
		}

		m_fen_info.en_passant_square = ISXUtility::Convert(fen_en_passant);
	}
}

void FENParser::ParseCounters(const std::string& fen_halfmove, const std::string& fen_fullmove)
{
	char* halfmove_ptr, *fullmove_ptr;
	m_fen_info.halfmove_clock = std::strtol(fen_halfmove.c_str(), &halfmove_ptr, 10);
	m_fen_info.fullmove_counter = std::strtol(fen_fullmove.c_str(), &fullmove_ptr, 10);

	if (*halfmove_ptr || *fullmove_ptr)
	{
		throw std::runtime_error("Halfmove Clock or Fullmove Counter is not a number");
	}
}
