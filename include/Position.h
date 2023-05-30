#ifndef POSITION_H_
#define POSITION_H_

#include <cstdint>

struct Position
{
	int8_t x;
	int8_t y;

	Position() = default;
	constexpr Position(int8_t x, int8_t y) : x(x), y(y) {}

	bool IsInvalid() const;

	Position& operator+=(const Position& pos);
	Position& operator-=(const Position& pos);
	Position operator+(const Position& pos) const;
	Position operator-(const Position& pos) const;
	bool operator<(const Position& pos) const;
	bool operator>(const Position& pos) const;
	bool operator==(const Position& pos) const;
	bool operator!=(const Position& pos) const;
};

constexpr Position INVALID_POSITION = { -1, -1 };

#endif //POSITION_H_
