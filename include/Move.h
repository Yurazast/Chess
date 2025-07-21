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

	explicit Move(Position src, Position dest, Move::Type type, std::shared_ptr<Piece> piece_moved, std::shared_ptr<Piece> piece_defeated, bool is_first_move);

	Position get_src_position() const;
	Position get_dest_position() const;
	Move::Type get_type() const;
	std::shared_ptr<Piece> get_piece_moved() const;
	std::shared_ptr<Piece> get_piece_defeated() const;
	std::shared_ptr<Piece> get_piece_promoted() const;
	void set_piece_promoted(std::shared_ptr<Piece> piece_promoted);
	bool is_first_move() const;
	Position get_en_passant_position() const;
	void set_en_passant_position(Position en_passant_position);
	uint8_t get_halfmove_clock() const;
	void set_halfmove_clock(uint8_t halfmove_clock);
	uint8_t get_fullmove_counter() const;
	void set_fullmove_counter(uint8_t fullmove_counter);

private:
	Position m_src_position;
	Position m_dest_position;
	Move::Type m_type;
	std::shared_ptr<Piece> m_piece_moved;
	std::shared_ptr<Piece> m_piece_defeated;
	std::shared_ptr<Piece> m_piece_promoted;
	bool m_first_move;
	Position m_en_passant_position;
	uint8_t m_halfmove_clock;
	uint8_t m_fullmove_counter;
};

#endif //MOVE_H_
