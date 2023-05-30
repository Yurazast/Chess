#include "Move.h"

Move::Move(Position src, Position dest, Move::Type type, std::weak_ptr<Piece> piece_moved, std::weak_ptr<Piece> piece_defeated)
    : m_src_position(src)
    , m_dest_position(dest)
    , m_type(type)
    , m_piece_moved(piece_moved)
    , m_piece_defeated(piece_defeated)
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
    if (this->m_piece_moved.expired())
    {
        return nullptr;
    }

    return this->m_piece_moved.lock();
}

std::shared_ptr<Piece> Move::get_piece_defeated() const
{
    if (this->m_piece_defeated.expired())
    {
        return nullptr;
    }

    return this->m_piece_defeated.lock();
}
