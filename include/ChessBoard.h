#ifndef CHESSBOARD_H_
#define CHESSBOARD_H_

#include <array>

#include "BoardSquare.h"

constexpr auto BOARD_HEIGHT = 8;
constexpr auto BOARD_WIDTH = 8;
constexpr auto WHITE_TEAM_START_Y = 0;
constexpr auto BLACK_TEAM_START_Y = BOARD_HEIGHT - 1;

namespace ISXChess
{

using ChessBoard = std::array<std::array<BoardSquare, BOARD_WIDTH>, BOARD_HEIGHT>;

}

#endif //CHESSBOARD_H_
