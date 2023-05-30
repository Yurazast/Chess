#ifndef MOVE_H_
#define MOVE_H_

#include "ChessBoard.h"
#include "pieces/Piece.h"

class Move
{
public:
	enum class Type
	{
		REGULAR,
		KING_SIDE_CASTLING,
		QUEEN_SIDE_CASTLING,
		PAWN_PROMOTION,
		EN_PASSANT
	};

	explicit Move(Position src, Position dest, Move::Type type, std::weak_ptr<Piece> piece_moved, std::weak_ptr<Piece> piece_defeated);

	Position get_src_position() const;
	Position get_dest_position() const;
	Move::Type get_type() const;
	std::shared_ptr<Piece> get_piece_moved() const;
	std::shared_ptr<Piece> get_piece_defeated() const;

private:
	Position m_src_position;
	Position m_dest_position;
	Move::Type m_type;
	std::weak_ptr<Piece> m_piece_moved;
	std::weak_ptr<Piece> m_piece_defeated;
};

#endif //MOVE_H_
