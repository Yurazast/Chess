#include "pieces/King.h"
#include "Board.h"
#include "Move.h"

King::King(ISXChess::Team team)
	: Piece(team, Piece::Type::KING, 100)
	, m_king_side_castling(true)
	, m_queen_side_castling(true)
{
	LoadImageFromFile(ISXUtility::IsWhiteSide(team) ? WHITE_KING_IMAGE_FILEPATH : BLACK_KING_IMAGE_FILEPATH);
}

std::list<Move> King::GeneratePossibleMoves(const ISXChess::ChessBoard& chess_board, Position position) const
{
	std::list<Move> moves{};

	std::list<Position> shifts{{ -1, 0 }, { 0, -1 }, { 1, 0 }, { 0, 1 }, { -1, -1 }, { 1, 1 }, { -1, 1 }, { 1, -1 }};
	std::list<Position> castling_shifts{{ -1, 1 }, { 1, -1 }};

	for (Position shift : shifts)
	{
		Position dest = position + shift;

		if (IsMoveValid(position, dest, chess_board))
		{
			moves.push_back(Move{ position, dest, Move::Type::REGULAR, ISXUtility::GetPiece(chess_board, position), ISXUtility::GetPiece(chess_board, dest) });
		}
	}

	if (this->m_king_side_castling)
	{
		Position dest = position + Position{ 2, 0 };

		if (IsMoveValid(position, dest, chess_board))
		{
			moves.push_back(Move{ position, dest, Move::Type::KING_SIDE_CASTLING, ISXUtility::GetPiece(chess_board, position), std::weak_ptr<Piece>() });
		}
	}
	if (this->m_queen_side_castling)
	{
		Position dest = position + Position{ -2, 0 };

		if (IsMoveValid(position, dest, chess_board))
		{
			moves.push_back(Move{ position, dest, Move::Type::QUEEN_SIDE_CASTLING, ISXUtility::GetPiece(chess_board, position), std::weak_ptr<Piece>() });
		}
	}

	return moves;
}

bool King::IsMoveValid(Position src, Position dest, const ISXChess::ChessBoard& chess_board) const
{
	if (!ISXUtility::IsValidBorders(src) || !ISXUtility::IsValidBorders(dest))
	{
		return false;
	}

	bool is_position_available = ISXUtility::IsPositionAvailable(chess_board, dest);
	bool has_enemy_piece = ISXUtility::HasEnemyPiece(chess_board, dest, ISXUtility::EnemyTeam(this->m_team));
	int dx = abs(dest.x - src.x), dy = abs(dest.y - src.y);

	if (((is_position_available || has_enemy_piece) && (dx <= 1 && dy <= 1)) 	// regular move
	 || (is_position_available && IsCastling(src, dest, chess_board)))			// castling move
	{
		return true;
	}

	return false;
}

bool King::can_do_king_side_castling() const
{
	return this->m_king_side_castling;
}

void King::set_king_side_castling(bool king_side_castling)
{
	this->m_king_side_castling = king_side_castling;
}

bool King::can_do_queen_side_castling() const
{
	return this->m_queen_side_castling;
}

void King::set_queen_side_castling(bool queen_side_castling)
{
	this->m_queen_side_castling = queen_side_castling;
}

bool King::IsCastling(Position src, Position dest, const ISXChess::ChessBoard& chess_board) const
{
	bool is_king_side_castling = (dest.x - src.x) == 2 && src.y == dest.y;
	bool is_queen_side_castling = (dest.x - src.x) == -2 && src.y == dest.y;

	if (is_king_side_castling)
	{
		Position king_side_rook_position = ISXUtility::IsWhiteSide(this->m_team) ? Position{ 7, 7 } : Position{ 7, 0 };
		std::shared_ptr<Piece> king_side_rook = chess_board.at(king_side_rook_position.y).at(king_side_rook_position.x).piece;

		return !ISXUtility::IsObstacleBetween(chess_board, src, { static_cast<int8_t>(dest.x + 1), dest.y })
			&& king_side_rook && king_side_rook->get_type() == Piece::Type::ROOK && king_side_rook->get_team() == this->m_team
			&& this->is_first_move() && king_side_rook->is_first_move();
	}
	else if (is_queen_side_castling)
	{
		Position queen_side_rook_position = ISXUtility::IsWhiteSide(this->m_team) ? Position{ 0, 7 } : Position{ 0, 0 };
		std::shared_ptr<Piece> queen_side_rook = chess_board.at(queen_side_rook_position.y).at(queen_side_rook_position.x).piece;

		return !ISXUtility::IsObstacleBetween(chess_board, src, { static_cast<int8_t>(dest.x - 2), dest.y })
			&& queen_side_rook && queen_side_rook->get_type() == Piece::Type::ROOK && queen_side_rook->get_team() == this->m_team
			&& this->is_first_move() && queen_side_rook->is_first_move();
	}

	return false;
}
