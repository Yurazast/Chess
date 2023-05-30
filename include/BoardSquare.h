#ifndef BOARDSQUARE_H_
#define BOARDSQUARE_H_

#include <memory>

#include <SFML/Graphics/RectangleShape.hpp>

#include "Position.h"

class Piece;

constexpr auto BOARD_SQUARE_INIT_SIZE = 80.f;
const sf::Color BOARD_SQUARE_WHITE_COLOR = {240, 225, 195};
const sf::Color BOARD_SQUARE_BLACK_COLOR = {115, 150, 85};
const sf::Color BOARD_SQUARE_HIGHLIGHT_COLOR = {95, 95, 195, 75};
const sf::Color BOARD_SQUARE_DANGER_COLOR = {150, 0, 0};

struct BoardSquare
{
    sf::RectangleShape square{};
    sf::RectangleShape highlight_square{};
    sf::RectangleShape danger_square{};

    std::shared_ptr<Piece> piece;
    static Position en_passant_position;

    bool is_highlighted;
    bool is_danger;
};

#endif //BOARDSQUARE_H_
