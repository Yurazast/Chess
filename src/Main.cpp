#include "Game.h"

int main()
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(static_cast<unsigned int>(BOARD_SQUARE_INIT_SIZE * BOARD_WIDTH), static_cast<unsigned int>(BOARD_SQUARE_INIT_SIZE * BOARD_HEIGHT)), "Chess", sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);

    window.setPosition(sf::Vector2i((desktop.width - window.getSize().x) / 2, (desktop.height - window.getSize().y) / 2));
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    Game game(window);
    game.Run();

    return EXIT_SUCCESS;
}
