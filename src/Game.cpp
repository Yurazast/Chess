#include "Game.h"

Game::Game(sf::RenderWindow& window, PlayerArray players)
	: m_board{}
	, m_window{ window }
	, m_players{ players }
	, m_played_moves{}
	, m_status{ Game::Status::ACTIVE }
	, m_selected_piece_position{ INVALID_POSITION }
	, m_pawn_promotion_pieces{}
	, m_halfmove_clock(0)
	, m_fullmove_counter(1)
{
	if (players[0] == nullptr || players[1] == nullptr)
	{
		throw std::runtime_error("The players are not assigned");
	}

	if (players[0]->get_team() == players[1]->get_team())
	{
		throw std::runtime_error("The players are in same team");
	}
}

void Game::Init(const std::string& fen)
{
	if (fen.empty())
	{
		m_board.Init();
		m_current_turn = ISXChess::Team::WHITE;
	}
	else
	{
		FENParser fen_parser(fen);
		FENInfo fen_info = fen_parser.Parse();

		m_board.set_chess_board(fen_info.chess_board);
		m_current_turn = fen_info.current_turn;

		std::shared_ptr<King> white_king = m_board.GetKing(ISXChess::Team::WHITE);
		std::shared_ptr<King> black_king = m_board.GetKing(ISXChess::Team::BLACK);

		if (white_king == nullptr || black_king == nullptr)
		{
			throw std::runtime_error("No king(s) on the board");
		}

		white_king->set_king_side_castling(fen_info.castling_rights.white_king_side);
		white_king->set_queen_side_castling(fen_info.castling_rights.white_queen_side);
		black_king->set_king_side_castling(fen_info.castling_rights.black_king_side);
		black_king->set_queen_side_castling(fen_info.castling_rights.black_queen_side);

		if (!fen_info.en_passant_square.IsInvalid())
		{
			m_board.get_chess_board()[0][0].en_passant_position = fen_info.en_passant_square;
		}

		this->m_halfmove_clock = fen_info.halfmove_clock;
		this->m_fullmove_counter = fen_info.fullmove_counter;

		if (IsInCheck())
		{
			const Position king_position = m_board.FindKingPosition(fen_info.current_turn);
			m_board.get_chess_board().at(king_position.y).at(king_position.x).is_danger = true;
		}
	}
}

void Game::Run()
{
	Init("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

	sf::Text text;
	sf::Font font;

	font.loadFromFile(AMETHYSTA_REGULAR_FONT_FILEPATH);
	text.setFont(font);
	text.setFillColor(sf::Color::Blue);
	text.setPosition(BOARD_SQUARE_INIT_SIZE * 1.43f, BOARD_SQUARE_INIT_SIZE * 3.5f);

	while (m_window.isOpen())
	{
		sf::Event event;

		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_window.close();
			}

			if (event.type == sf::Event::Resized)
			{
				m_board_square_size_x = m_window.getSize().x / BOARD_WIDTH;
				m_board_square_size_y = m_window.getSize().y / BOARD_HEIGHT;
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
			{
				Reset();
			}

			if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sf::Vector2i mouse_position = sf::Mouse::getPosition(m_window);

				if (!IsGameOver())
				{
					if (m_pawn_promotion_pieces.front() != nullptr)
					{
						OnPawnPromotion(mouse_position);
					}
					else
					{
						OnMouseClick(mouse_position);
					}
				}
			}
		}

		m_window.clear(sf::Color::White);
		m_window.draw(m_board);

		if (m_pawn_promotion_pieces.front() != nullptr)
		{
			for (const std::shared_ptr<Piece> piece : m_pawn_promotion_pieces)
			{
				m_window.draw(*piece);
			}
		}

		if (IsGameOver())
		{
			text.setString(GetGameResults());
			m_window.draw(text);
		}

		m_window.display();
	}
}

void Game::Reset(const PlayerArray* const players)
{
	m_board.Clear();
	m_played_moves.clear();
	m_pawn_promotion_pieces.fill(nullptr);

	if (players)
	{
		m_players = *players;
	}

	m_status = Game::Status::ACTIVE;
	m_selected_piece_position = INVALID_POSITION;
	m_halfmove_clock = 0;
	m_fullmove_counter = 1;

	Init();
}

void Game::SwitchTurn()
{
	this->m_current_turn = ISXUtility::IsWhiteSide(this->m_current_turn) ? ISXChess::Team::BLACK : ISXChess::Team::WHITE;
}

bool Game::IsGameOver()
{
	if (m_status != Game::Status::ACTIVE)
	{
		return true;
	}

	if (m_halfmove_clock == 100)
	{
		m_status = Game::Status::DRAW;
		return true;
	}

	if (!CanMove())
	{
		if (IsInCheck())
		{
			m_status = ISXUtility::IsWhiteSide(m_current_turn) ? Game::Status::BLACK_WIN : Game::Status::WHITE_WIN;
		}
		else
		{
			m_status = Game::Status::STALEMATE;
		}

		return true;
	}

	return false;
}

bool Game::MakeMove(Position src, Position dest)
{
	std::shared_ptr<Piece> src_piece = m_board.get_chess_board()[src.y][src.x].piece;
	std::shared_ptr<Piece> dest_piece = m_board.get_chess_board()[dest.y][dest.x].piece;

	if (m_possible_moves.empty())
	{
		return false;
	}

	std::list<Move>::iterator moves_iterator = std::find_if(m_possible_moves.begin(), m_possible_moves.end(),
															[dest](const Move &move){ return move.get_dest_position() == dest; });

	if (!src_piece || src_piece->get_team() != m_current_turn || moves_iterator == m_possible_moves.end())
	{
		return false;
	}

	if (dest_piece != nullptr || src_piece->get_type() == Piece::Type::PAWN)
	{
		m_halfmove_clock = 0;
	}
	else
	{
		++m_halfmove_clock;
	}

	if (m_current_turn == ISXChess::Team::BLACK)
	{
		++m_fullmove_counter;
	}

	if (src_piece->get_type() == Piece::Type::PAWN && src_piece->is_first_move() && abs(dest.y - src.y) == 2)
	{
		Position en_passant_square = { dest.x, (src.y + dest.y) / 2 };
		m_board.get_chess_board()[en_passant_square.y][en_passant_square.x].en_passant_position = en_passant_square;
	}
	else
	{
		m_board.get_chess_board()[dest.y][dest.x].en_passant_position = INVALID_POSITION;
	}

	src_piece->set_first_move(false);
	src_piece->get_sprite().setPosition(m_board.get_chess_board()[dest.y][dest.x].square.getPosition());
	m_board.get_chess_board()[dest.y][dest.x].piece = std::move(src_piece);
	m_board.get_chess_board()[src.y][src.x].piece = nullptr;

	Move move = *moves_iterator;

	CheckSpecialMoves(move);
	m_played_moves.push_back(move);

	SoundPlayer::Play(ISXChess::SoundType::MOVE_PIECE);
	return true;
}

void Game::OnMouseClick(const sf::Vector2i& mouse_position)
{
	int8_t board_square_x = (mouse_position.x - (m_window.getSize().x - m_board_square_size_x * BOARD_HEIGHT) / 2) / m_board_square_size_x;
	int8_t board_square_y = (mouse_position.y - (m_window.getSize().y - m_board_square_size_y * BOARD_WIDTH) / 2) / m_board_square_size_y;
	Position board_square_position{ board_square_x, board_square_y };

	if (!ISXUtility::IsValidBorders(board_square_position))
	{
		return;
	}

	std::shared_ptr<Piece> piece = ISXUtility::GetPiece(m_board.get_chess_board(), board_square_position);

	if (piece != nullptr && piece->get_team() == m_current_turn)
	{
		m_selected_piece_position = board_square_position;
		m_board.ClearHighlightedSquares();

		m_possible_moves.clear();
		m_possible_moves = piece->GeneratePossibleMoves(m_board.get_chess_board(), m_selected_piece_position);

		RemoveMovesLeadingToCheck(m_possible_moves);

		for (const Move& move : m_possible_moves)
		{
			Position position = move.get_dest_position();
			m_board.get_chess_board().at(position.y).at(position.x).is_highlighted = true;
		}
	}
	else if (!m_selected_piece_position.IsInvalid())
	{
		if (MakeMove(m_selected_piece_position, board_square_position))
		{
			SwitchTurn();
			m_board.ClearDangerSquares();

			if (IsInCheck())
			{
				const Position king_position = m_board.FindKingPosition(m_current_turn);
				m_board.get_chess_board().at(king_position.y).at(king_position.x).is_danger = true;

				SoundPlayer::Play(ISXChess::SoundType::NOTIFICATION);
			}
		}

		m_selected_piece_position = INVALID_POSITION;
		m_board.ClearHighlightedSquares();
	}
}

void Game::OnPawnPromotion(const sf::Vector2i& mouse_position)
{
	float board_square_x = (mouse_position.x - (m_window.getSize().x - m_board_square_size_x * BOARD_HEIGHT) / 2) / m_board_square_size_x;
	float board_square_y = (mouse_position.y - (m_window.getSize().y - m_board_square_size_y * BOARD_WIDTH) / 2) / m_board_square_size_y;
	Position board_square_position{ board_square_x, board_square_y };

	sf::Vector2f pieces_pos = m_pawn_promotion_pieces.front()->get_sprite().getPosition();
	Position pieces_position = { pieces_pos.x / BOARD_SQUARE_INIT_SIZE, pieces_pos.y / BOARD_SQUARE_INIT_SIZE };

	if (board_square_position != pieces_position)
	{
		return;
	}

	int8_t figure_x = (board_square_x - static_cast<int>(board_square_x)) > 0.5;
	int8_t figure_y = (board_square_y - static_cast<int>(board_square_y)) > 0.5;

	if (figure_x < 0 || figure_x > 1 || figure_y < 0 || figure_y > 1)
	{
		return;
	}

	std::shared_ptr<Piece> piece = m_pawn_promotion_pieces.at(figure_x + figure_y * PAWN_PROMOTION_PIECES_COUNT / 2);

	piece->get_sprite().setPosition(pieces_pos);
	piece->get_sprite().setScale(sf::Vector2f(BOARD_SQUARE_INIT_SIZE / 128, BOARD_SQUARE_INIT_SIZE / 128));

	m_board.get_chess_board()[pieces_position.y][pieces_position.x].piece = piece;
	m_pawn_promotion_pieces.fill(nullptr);

	SoundPlayer::Play(ISXChess::SoundType::MOVE_PIECE);

	if (IsInCheck())
	{
		const Position king_position = m_board.FindKingPosition(m_current_turn);
		m_board.get_chess_board().at(king_position.y).at(king_position.x).is_danger = true;

		SoundPlayer::Play(ISXChess::SoundType::NOTIFICATION);
	}
}

sf::String Game::GetGameResults() const
{
	sf::String status_string;

	if (m_status == Game::Status::BLACK_WIN)
	{
		status_string = "\t\t\tBlack wins!\n";
	}
	else if (m_status == Game::Status::WHITE_WIN)
	{
		status_string = "\t\t\tWhite wins!\n";
	}
	else if (m_status == Game::Status::STALEMATE)
	{
		status_string = "\t\t\t Stalemate!\n";
	}
	else if (m_status == Game::Status::DRAW)
	{
		status_string = "\t\t\t\tDraw!\n";
	}

	status_string += "Press R to restart the game";
	return status_string;
}

void Game::CheckSpecialMoves(const Move& move)
{
	Position src = move.get_src_position(), dest = move.get_dest_position();
	Move::Type move_type = move.get_type();

	if (move_type == Move::Type::EN_PASSANT)
	{
		Position enemy_piece_position = { dest.x, src.y };
		m_board.get_chess_board()[enemy_piece_position.y][enemy_piece_position.x].piece = nullptr;
	}

	if (move_type == Move::Type::KING_SIDE_CASTLING)
	{
		Position king_side_rook_position = ISXUtility::IsWhiteSide(m_current_turn) ? Position{ 7, 7 } : Position{ 7, 0 };
		std::shared_ptr<Rook> king_side_rook = std::static_pointer_cast<Rook>(m_board.get_chess_board()[king_side_rook_position.y][king_side_rook_position.x].piece);

		if (king_side_rook == nullptr)
		{
			throw std::runtime_error("King side rook cannot be null during castling");
		}

		king_side_rook->set_first_move(false);
		king_side_rook->get_sprite().setPosition(m_board.get_chess_board()[dest.y][(src.x + dest.x) / 2].square.getPosition());
		m_board.get_chess_board()[dest.y][(src.x + dest.x) / 2].piece = std::move(king_side_rook);
		m_board.get_chess_board()[king_side_rook_position.y][king_side_rook_position.x].piece = nullptr;

		SoundPlayer::Play(ISXChess::SoundType::MOVE_PIECE);
		std::this_thread::sleep_for(std::chrono::milliseconds(70));
	}
	else if (move_type == Move::Type::QUEEN_SIDE_CASTLING)
	{
		Position queen_side_rook_position = ISXUtility::IsWhiteSide(m_current_turn) ? Position{ 0, 7 } : Position{ 0, 0 };
		std::shared_ptr<Rook> queen_side_rook = std::static_pointer_cast<Rook>(m_board.get_chess_board()[queen_side_rook_position.y][queen_side_rook_position.x].piece);

		if (queen_side_rook == nullptr)
		{
			throw std::runtime_error("Queen side rook cannot be null during castling");
		}

		queen_side_rook->set_first_move(false);
		queen_side_rook->get_sprite().setPosition(m_board.get_chess_board()[dest.y][(src.x + dest.x) / 2].square.getPosition());
		m_board.get_chess_board()[dest.y][(src.x + dest.x) / 2].piece = std::move(queen_side_rook);
		m_board.get_chess_board()[queen_side_rook_position.y][queen_side_rook_position.x].piece = nullptr;

		SoundPlayer::Play(ISXChess::SoundType::MOVE_PIECE);
		std::this_thread::sleep_for(std::chrono::milliseconds(70));
	}

	if (move_type == Move::Type::PAWN_PROMOTION)
	{
		m_board.get_chess_board()[dest.y][dest.x].piece = nullptr;

		m_pawn_promotion_pieces = {
			PieceFactory::Create(Piece::Type::ROOK, m_current_turn),
			PieceFactory::Create(Piece::Type::QUEEN, m_current_turn),
			PieceFactory::Create(Piece::Type::BISHOP, m_current_turn),
			PieceFactory::Create(Piece::Type::KNIGHT, m_current_turn)
		};

		sf::Vector2f square_pos = m_board.get_chess_board()[dest.y][dest.x].square.getPosition();
		int i = 0;

		for (std::shared_ptr<Piece> piece : m_pawn_promotion_pieces)
		{
			piece->get_sprite().setPosition(square_pos.x + (i & 1) * BOARD_SQUARE_INIT_SIZE / 2, square_pos.y + (i & 2) * BOARD_SQUARE_INIT_SIZE / 4);
			piece->get_sprite().setScale(sf::Vector2f(BOARD_SQUARE_INIT_SIZE / 2 / 128, BOARD_SQUARE_INIT_SIZE / 2 / 128));
			++i;
		}
	}
}

std::list<Move> Game::GeneratePossibleMoves()
{
	const std::list<std::pair<std::shared_ptr<Piece>, Position>> pieces_positions = m_board.GetPiecesPositions(m_current_turn);
	std::list<Move> moves{};

	for (const auto& [piece, piece_position] : pieces_positions)
	{
		moves.splice(moves.end(), piece->GeneratePossibleMoves(m_board.get_chess_board(), piece_position));
	}

	RemoveMovesLeadingToCheck(moves);
	return moves;
}

void Game::RemoveMovesLeadingToCheck(std::list<Move>& moves)
{
	std::list<Move>::iterator it = moves.begin();

	while (it != moves.end())
	{
		Position src = it->get_src_position(), dest = it->get_dest_position();
		std::shared_ptr<Piece> save_dest_piece = ISXUtility::GetPiece(m_board.get_chess_board(), dest);

		// make pseudo-legal move
		m_board.get_chess_board()[dest.y][dest.x].piece = std::move(m_board.get_chess_board()[src.y][src.x].piece);
		m_board.get_chess_board()[src.y][src.x].piece = nullptr;

		// if king becomes in check after move, then remove move from list
		if (IsInCheck())
		{
			it = moves.erase(it);
		}
		else
		{
			++it;
		}

		// undo pseudo-legal move
		m_board.get_chess_board()[src.y][src.x].piece = std::move(m_board.get_chess_board()[dest.y][dest.x].piece);
		m_board.get_chess_board()[dest.y][dest.x].piece = save_dest_piece;
	}
}

bool Game::CanMove()
{
	return !GeneratePossibleMoves().empty();
}

bool Game::IsInCheck() const
{
	const Position king_position = m_board.FindKingPosition(m_current_turn);
	const std::list<std::pair<std::shared_ptr<Piece>, Position>> pieces_positions = m_board.GetPiecesPositions(ISXUtility::EnemyTeam(m_current_turn));

	for (const auto& [piece, piece_position] : pieces_positions)
	{
		if (piece != nullptr && piece->IsMoveValid(piece_position, king_position, m_board.get_chess_board()))
		{
			return true;
		}
	}

	return false;
}
