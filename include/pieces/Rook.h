#ifndef ROOK_H_
#define ROOK_H_

#include "Piece.h"

class Rook final : public Piece
{
public:
	explicit Rook(ISXChess::Team team);

	std::list<Move> GeneratePossibleMoves(const ISXChess::ChessBoard& chess_board, Position position) const override;
	bool IsMoveValid(Position src, Position dest, const ISXChess::ChessBoard& chess_board) const override;
};

#endif //ROOK_H_
