#include "Move.h"

Move::Move(Position src, Position dest, Move::Type type, std::shared_ptr<Piece> piece_moved, std::shared_ptr<Piece> piece_defeated, bool is_first_move)
    : m_src_position(src)
    , m_dest_position(dest)
    , m_type(type)
    , m_piece_moved(piece_moved)
    , m_piece_defeated(piece_defeated)
    , m_piece_promoted(nullptr)
    , m_first_move(is_first_move)
    , m_en_passant_position(INVALID_POSITION)
    , m_halfmove_clock(0)
    , m_fullmove_counter(0)
{}

Position Move::get_src_position() const
{
    return this->m_src_position;
}

Position Move::get_dest_position() const
{
    return this->m_dest_position;
}

Move::Type Move::get_type() const
{
    return this->m_type;
}

std::shared_ptr<Piece> Move::get_piece_moved() const
{
    return this->m_piece_moved;
}

std::shared_ptr<Piece> Move::get_piece_defeated() const
{
    return this->m_piece_defeated;
}

std::shared_ptr<Piece> Move::get_piece_promoted() const
{
    return this->m_piece_promoted;
}

void Move::set_piece_promoted(std::shared_ptr<Piece> piece_promoted)
{
	this->m_piece_promoted = piece_promoted;
}

bool Move::is_first_move() const
{
	return this->m_first_move;
}

Position Move::get_en_passant_position() const
{
	return this->m_en_passant_position;
}

void Move::set_en_passant_position(Position en_passant_position)
{
	this->m_en_passant_position = en_passant_position;
}

uint8_t Move::get_halfmove_clock() const
{
	return this->m_halfmove_clock;
}

void Move::set_halfmove_clock(uint8_t halfmove_clock)
{
	this->m_halfmove_clock = halfmove_clock;
}

uint8_t Move::get_fullmove_counter() const
{
	return this->m_fullmove_counter;
}

void Move::set_fullmove_counter(uint8_t fullmove_counter)
{
    this->m_fullmove_counter = fullmove_counter;
}
