#include "Position.h"

bool Position::IsInvalid() const
{
    return this->operator==(INVALID_POSITION); // equals to (-1, -1)
}

Position& Position::operator+=(const Position& pos)
{
    *this = *this + pos;
    return *this;
}

Position& Position::operator-=(const Position& pos)
{
    *this = *this - pos;
    return *this;
}

Position Position::operator+(const Position& pos) const
{
    return Position{ static_cast<int8_t>(this->x + pos.x), static_cast<int8_t>(this->y + pos.y) };
}

Position Position::operator-(const Position& pos) const
{
    return Position{ static_cast<int8_t>(this->x - pos.x), static_cast<int8_t>(this->y - pos.y) };
}

bool Position::operator<(const Position& pos) const
{
    return (this->y < pos.y) || ((this->y == pos.y) && (this->x < pos.x)); // check by Y first, then by X
}

bool Position::operator>(const Position& pos) const
{
    return (this->y > pos.y) || ((this->y == pos.y) && (this->x > pos.x));
}

bool Position::operator==(const Position& pos) const
{
    return this->x == pos.x && this->y == pos.y;
}

bool Position::operator!=(const Position& pos) const
{
    return !(*this == pos);
}
