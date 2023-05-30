#ifndef KNIGHT_H_
#define KNIGHT_H_

#include "Piece.h"

class Knight final : public Piece
{
public:
	explicit Knight(ISXChess::Team team);

	std::list<Move> GeneratePossibleMoves(const ISXChess::ChessBoard& chess_board, Position position) const override;
	bool IsMoveValid(Position src, Position dest, const ISXChess::ChessBoard& chess_board) const override;
};

#endif //KNIGHT_H_
