#include "Board.h"

Board::Board()
	: m_chess_board{}
{}

Board::~Board()
{
	Clear();
}

void Board::Init()
{
	ISXUtility::InitSquares(m_chess_board);
	InitPieces(ISXChess::Team::WHITE);
	InitPieces(ISXChess::Team::BLACK);
}

void Board::Reset()
{
	Clear();
	Init();
}

void Board::Clear()
{
	for (std::array<BoardSquare, BOARD_WIDTH>& row : m_chess_board)
	{
		for (BoardSquare& board_square : row)
		{
			board_square = {};
		}
	}
	m_chess_board.at(0).at(0).en_passant_position = INVALID_POSITION;
}

void Board::ClearHighlightedSquares()
{
	for (std::array<BoardSquare, BOARD_WIDTH>& row : m_chess_board)
	{
		for (BoardSquare& board_square : row)
		{
			board_square.is_highlighted = false;
		}
	}
}

void Board::ClearDangerSquares()
{
	for (std::array<BoardSquare, BOARD_WIDTH>& row : m_chess_board)
	{
		for (BoardSquare& board_square : row)
		{
			board_square.is_danger = false;
		}
	}
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (uint8_t y = 0; y < BOARD_HEIGHT; ++y)
	{
		for (uint8_t x = 0; x < BOARD_WIDTH; ++x)
		{
			sf::RectangleShape square = m_chess_board.at(y).at(x).square;
			sf::RectangleShape highlight_square = m_chess_board.at(y).at(x).highlight_square;
			sf::RectangleShape danger_square = m_chess_board.at(y).at(x).danger_square;
			std::shared_ptr<Piece> piece = m_chess_board.at(y).at(x).piece;

			target.draw(square);

			if (m_chess_board.at(y).at(x).is_highlighted)
			{
				target.draw(highlight_square);
			}

			if (m_chess_board.at(y).at(x).is_danger)
			{
				target.draw(danger_square);
			}

			if (piece != nullptr)
			{
				target.draw(*piece);
			}
		}
	}
}

std::shared_ptr<Piece> Board::GetPiece(Position position) const
{
	return m_chess_board.at(position.y).at(position.x).piece;
}

std::shared_ptr<King> Board::GetKing(ISXChess::Team team) const
{
	const Position king_position = FindKingPosition(team);

	if (king_position.IsInvalid())
	{
		return nullptr;
	}

	return std::static_pointer_cast<King>(GetPiece(king_position));
}

Position Board::FindKingPosition(ISXChess::Team team) const
{
	for (int8_t y = 0; y < BOARD_HEIGHT; ++y)
	{
		for (int8_t x = 0; x < BOARD_WIDTH; ++x)
		{
			const std::shared_ptr<Piece> piece = GetPiece({ x, y });
			if (piece != nullptr && piece->get_team() == team && piece->get_type() == Piece::Type::KING)
			{
				return { x, y };
			}
		}
	}

	return INVALID_POSITION;
}

std::list<std::pair<std::shared_ptr<Piece>, Position>> Board::GetPiecesPositions(ISXChess::Team team) const
{
	std::list<std::pair<std::shared_ptr<Piece>, Position>> pieces{};

	for (int8_t y = 0; y < BOARD_HEIGHT; ++y)
	{
		for (int8_t x = 0; x < BOARD_WIDTH; ++x)
		{
			std::shared_ptr<Piece> piece = GetPiece({ x, y });
			if (piece != nullptr && piece->get_team() == team)
			{
				pieces.push_back({ piece, { x, y }});
			}
		}
	}

	return pieces;
}

const ISXChess::ChessBoard& Board::get_chess_board() const
{
	return this->m_chess_board;
}

ISXChess::ChessBoard& Board::get_chess_board()
{
	return this->m_chess_board;
}

void Board::set_chess_board(const ISXChess::ChessBoard& chess_board)
{
	this->m_chess_board = chess_board;
}

void Board::InitPieces(ISXChess::Team team)
{
	bool is_team_white = ISXUtility::IsWhiteSide(team);
	int start_y = !is_team_white ? WHITE_TEAM_START_Y : BLACK_TEAM_START_Y;
	int shift = !is_team_white ? 1 : -1; // shift for pawn pieces depending on the team

	m_chess_board.at(start_y).at(0).piece = PieceFactory::Create(Piece::Type::ROOK, team);
	m_chess_board.at(start_y).at(1).piece = PieceFactory::Create(Piece::Type::KNIGHT, team);
	m_chess_board.at(start_y).at(2).piece = PieceFactory::Create(Piece::Type::BISHOP, team);
	m_chess_board.at(start_y).at(3).piece = PieceFactory::Create(Piece::Type::QUEEN, team);
	m_chess_board.at(start_y).at(4).piece = PieceFactory::Create(Piece::Type::KING, team);
	m_chess_board.at(start_y).at(5).piece = PieceFactory::Create(Piece::Type::BISHOP, team);
	m_chess_board.at(start_y).at(6).piece = PieceFactory::Create(Piece::Type::KNIGHT, team);
	m_chess_board.at(start_y).at(7).piece = PieceFactory::Create(Piece::Type::ROOK, team);

	for (uint8_t x = 0; x < BOARD_WIDTH; ++x)
	{
		sf::RectangleShape& square = m_chess_board.at(start_y).at(x).square;
		std::shared_ptr<Piece> piece = m_chess_board.at(start_y).at(x).piece;

		piece->get_sprite().setPosition(square.getPosition());
		piece->get_sprite().setScale(sf::Vector2f(BOARD_SQUARE_INIT_SIZE / 128, BOARD_SQUARE_INIT_SIZE / 128));
	}

	for (uint8_t x = 0; x < BOARD_WIDTH; ++x)
	{
		m_chess_board.at(start_y + shift).at(x).piece = PieceFactory::Create(Piece::Type::PAWN, team);

		sf::RectangleShape& square = m_chess_board.at(start_y + shift).at(x).square;
		std::shared_ptr<Piece> piece = m_chess_board.at(start_y + shift).at(x).piece;

		piece->get_sprite().setPosition(square.getPosition());
		piece->get_sprite().setScale(sf::Vector2f(BOARD_SQUARE_INIT_SIZE / 128, BOARD_SQUARE_INIT_SIZE / 128));
	}
}
