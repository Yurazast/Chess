#ifndef QUEEN_H_
#define QUEEN_H_

#include "Piece.h"

class Queen final : public Piece
{
public:
	explicit Queen(ISXChess::Team team);

	std::list<Move> GeneratePossibleMoves(const ISXChess::ChessBoard& chess_board, Position position) const override;
	bool IsMoveValid(Position src, Position dest, const ISXChess::ChessBoard& chess_board) const override;
};

#endif //QUEEN_H_
