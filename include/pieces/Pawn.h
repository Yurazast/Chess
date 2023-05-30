#ifndef PAWN_H_
#define PAWN_H_

#include "Piece.h"

class Pawn final : public Piece
{
public:
	explicit Pawn(ISXChess::Team team);

	std::list<Move> GeneratePossibleMoves(const ISXChess::ChessBoard& chess_board, Position position) const override;
	bool IsMoveValid(Position src, Position dest, const ISXChess::ChessBoard& chess_board) const override;
};

#endif //PAWN_H_
