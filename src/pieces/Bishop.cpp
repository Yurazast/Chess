#include "pieces/Bishop.h"
#include "Board.h"
#include "Move.h"

Bishop::Bishop(ISXChess::Team team)
	: Piece('B', team, Piece::Type::BISHOP, 3)
{
	LoadImageFromFile(ISXUtility::IsWhiteSide(team) ? WHITE_BISHOP_IMAGE_FILEPATH : BLACK_BISHOP_IMAGE_FILEPATH);
}

std::list<Move> Bishop::GeneratePossibleMoves(const ISXChess::ChessBoard& chess_board, Position position) const
{
	std::list<Move> moves{};

	std::list<Position> shifts{{ -1, -1 }, { 1, 1 }, { -1, 1 }, { 1, -1 }};

	for (Position shift : shifts)
	{
		Position dest = position + shift;

		while (IsMoveValid(position, dest, chess_board))
		{
			moves.push_back(Move{ position, dest, Move::Type::REGULAR, ISXUtility::GetPiece(chess_board, position), ISXUtility::GetPiece(chess_board, dest) });
			dest += shift;
		}
	}

	return moves;
}

bool Bishop::IsMoveValid(Position src, Position dest, const ISXChess::ChessBoard& chess_board) const
{
	if (!ISXUtility::IsValidBorders(src) || !ISXUtility::IsValidBorders(dest))
	{
		return false;
	}

	bool is_position_available = ISXUtility::IsPositionAvailable(chess_board, dest);
	bool has_enemy_piece = ISXUtility::HasEnemyPiece(chess_board, dest, ISXUtility::EnemyTeam(this->m_team));
	bool is_obstacle = ISXUtility::IsObstacleBetween(chess_board, src, dest);
	int dx = abs(dest.x - src.x), dy = abs(dest.y - src.y);

	if ((is_position_available || has_enemy_piece) && !is_obstacle && dx == dy)		// diagonal move
	{
		return true;
	}

	return false;
}
