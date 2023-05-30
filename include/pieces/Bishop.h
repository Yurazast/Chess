#ifndef BISHOP_H_
#define BISHOP_H_

#include "Piece.h"

class Bishop final : public Piece
{
public:
	explicit Bishop(ISXChess::Team team);

	std::list<Move> GeneratePossibleMoves(const ISXChess::ChessBoard& chess_board, Position position) const override;
	bool IsMoveValid(Position src, Position dest, const ISXChess::ChessBoard& chess_board) const override;
};

#endif //BISHOP_H_
