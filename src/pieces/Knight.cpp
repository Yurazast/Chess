#include "pieces/Knight.h"
#include "Move.h"

Knight::Knight(ISXChess::Team team)
	: Piece(team, Piece::Type::KNIGHT, 3)
{
	LoadImageFromFile(ISXUtility::IsWhiteSide(team) ? WHITE_KNIGHT_IMAGE_FILEPATH : BLACK_KNIGHT_IMAGE_FILEPATH);
}

std::list<Move> Knight::GeneratePossibleMoves(const ISXChess::ChessBoard& chess_board, Position position) const
{
	std::list<Move> moves{};

	std::list<Position> shifts{{ -2, -1 }, { -1, -2 }, { -2, 1 }, { 1, -2 }, { -1, 2 }, { 2, -1 }, { 1, 2 }, { 2, 1 }};

	for (Position shift : shifts)
	{
		Position dest = position + shift;

		if (IsMoveValid(position, dest, chess_board))
		{
			moves.push_back(Move{ position, dest, Move::Type::REGULAR, ISXUtility::GetPiece(chess_board, position), ISXUtility::GetPiece(chess_board, dest), m_first_move });
		}
	}

	return moves;
}

bool Knight::IsMoveValid(Position src, Position dest, const ISXChess::ChessBoard& chess_board) const
{
	if (!ISXUtility::IsValidBorders(src) || !ISXUtility::IsValidBorders(dest))
	{
		return false;
	}

	bool is_position_available = ISXUtility::IsPositionAvailable(chess_board, dest);
	bool has_enemy_piece = ISXUtility::HasEnemyPiece(chess_board, dest, ISXUtility::EnemyTeam(this->m_team));
	int dx = abs(dest.x - src.x), dy = abs(dest.y - src.y);

	if ((is_position_available || has_enemy_piece) && ((dx == 2 && dy == 1) || (dx == 1 && dy == 2)))	// L-shape move
	{
		return true;
	}

	return false;
}
