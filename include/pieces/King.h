#ifndef KING_H_
#define KING_H_

#include "Piece.h"

class King final : public Piece
{
public:
	explicit King(ISXChess::Team team);

	std::list<Move> GeneratePossibleMoves(const ISXChess::ChessBoard& chess_board, Position position) const override;
	bool IsMoveValid(Position src, Position dest, const ISXChess::ChessBoard& chess_board) const override;

	bool can_do_king_side_castling() const;
	void set_king_side_castling(bool king_side_castling);
	bool can_do_queen_side_castling() const;
	void set_queen_side_castling(bool queen_side_castling);

private:
	bool IsCastling(Position src, Position dest, const ISXChess::ChessBoard& chess_board) const;

	bool m_king_side_castling;
	bool m_queen_side_castling;
};

#endif //KING_H_
