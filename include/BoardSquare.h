#ifndef BOARDSQUARE_H_
#define BOARDSQUARE_H_

#include <memory>

#include <SFML/Graphics/RectangleShape.hpp>

#include "Position.h"

class Piece;

constexpr auto BOARD_SQUARE_INIT_SIZE = 80.f;
const sf::Color BOARD_SQUARE_WHITE_COLOR = {240, 225, 195};
const sf::Color BOARD_SQUARE_BLACK_COLOR = {115, 150, 85};
const sf::Color BOARD_SQUARE_DANGER_COLOR = {150, 0, 0};
const sf::Color BOARD_SQUARE_MOVE_COLOR = {200, 255, 5, 100};
const sf::Color BOARD_SQUARE_HIGHLIGHTED_COLOR = {95, 95, 195, 125};
const sf::Color BOARD_SQUARE_SELECTED_COLOR = {60, 205, 70};

struct BoardSquare
{
    sf::Color init_color;
    sf::RectangleShape square{};

    std::shared_ptr<Piece> piece;
    static Position en_passant_position;

    enum State : uint8_t {
        NONE = 0x0,
        DANGER = 0x1,
        MOVE = 0x2,
        HIGHLIGHTED = 0x4,
        SELECTED = 0x8,
    };
    uint8_t state;
};

#endif //BOARDSQUARE_H_
