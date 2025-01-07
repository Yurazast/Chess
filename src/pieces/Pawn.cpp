#include "pieces/Pawn.h"
#include "Board.h"
#include "Move.h"

Position BoardSquare::en_passant_position = INVALID_POSITION;

Pawn::Pawn(ISXChess::Team team)
	: Piece(team, Piece::Type::PAWN, 1)
{
	LoadImageFromFile(ISXUtility::IsWhiteSide(team) ? WHITE_PAWN_IMAGE_FILEPATH : BLACK_PAWN_IMAGE_FILEPATH);
}

std::list<Move> Pawn::GeneratePossibleMoves(const ISXChess::ChessBoard& chess_board, Position position) const
{
	std::list<Move> moves{};

	int8_t step_forward = ISXUtility::IsWhiteSide(this->m_team) ? -1 : 1;

	std::list<Position> forward_shifts{{ 0, step_forward }, { 0, static_cast<int8_t>(2*step_forward) }};
	std::list<Position> attack_shifts{{ -1, step_forward }, { 1, step_forward }};

	for (Position shift : forward_shifts)
	{
		Position dest = position + shift;
		Move::Type move_type = Move::Type::REGULAR;

		if (IsMoveValid(position, dest, chess_board))
		{
			if ((this->m_team == ISXChess::Team::WHITE && dest.y == WHITE_TEAM_START_Y) || (this->m_team == ISXChess::Team::BLACK && dest.y == BLACK_TEAM_START_Y))
			{
				move_type = Move::Type::PAWN_PROMOTION;
			}

			moves.push_back(Move{ position, dest, move_type, ISXUtility::GetPiece(chess_board, position), ISXUtility::GetPiece(chess_board, dest) });
		}
	}

	for (Position shift : attack_shifts)
	{
		Position dest = position + shift;
		Move::Type move_type = Move::Type::REGULAR;

		if (IsMoveValid(position, dest, chess_board))
		{
			if ((this->m_team == ISXChess::Team::WHITE && dest.y == WHITE_TEAM_START_Y) || (this->m_team == ISXChess::Team::BLACK && dest.y == BLACK_TEAM_START_Y))
			{
				move_type = Move::Type::PAWN_PROMOTION;
			}
			else if (chess_board.at(dest.y).at(dest.x).en_passant_position == dest)
			{
				move_type = Move::Type::EN_PASSANT;
			}

			moves.push_back(Move{ position, dest, move_type, ISXUtility::GetPiece(chess_board, position), ISXUtility::GetPiece(chess_board, dest) });
		}
	}

	return moves;
}

bool Pawn::IsMoveValid(Position src, Position dest, const ISXChess::ChessBoard& chess_board) const
{
	if (!ISXUtility::IsValidBorders(src) || !ISXUtility::IsValidBorders(dest))
	{
		return false;
	}

	bool is_forward = ISXUtility::IsWhiteSide(this->m_team) ? (dest.y < src.y) : (dest.y > src.y);
	bool is_position_available = ISXUtility::IsPositionAvailable(chess_board, dest);
	bool has_enemy_piece = ISXUtility::HasEnemyPiece(chess_board, dest, ISXUtility::EnemyTeam(this->m_team));
	Position en_passant_position = chess_board.at(dest.y).at(dest.x).en_passant_position;
	int dx = abs(dest.x - src.x), dy = abs(dest.y - src.y);

	if (is_forward
	 &&	((is_position_available && (dx == 0 && dy == 1)) 																				// one step forward move
	 ||  (is_position_available && (dx == 0 && dy == 2) && m_first_move && !ISXUtility::IsObstacleBetween(chess_board, src, dest))		// two step forward move
	 ||  (has_enemy_piece && (dx == 1 && dy == 1)) 																						// attack move
	 ||  (!en_passant_position.IsInvalid() && en_passant_position == dest && (dx == 1 && dy == 1)))) 									// en passant move
	{
		return true;
	}

	return false;
}
