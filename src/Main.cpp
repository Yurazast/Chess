#include "Game.h"
#include "parsers/ArgsParser.h"

int32_t main(const int32_t argc, const char* const argv[])
{
    try {
        ArgsParser args_parser({ argv, argv + argc });
        ArgsInfo args_info = args_parser.Parse();

        sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

        unsigned int window_width = args_info.fullscreen ? desktop.width
                                  : args_info.window_width ? args_info.window_width
                                  : static_cast<unsigned int>(BOARD_SQUARE_INIT_SIZE * BOARD_WIDTH);
        unsigned int window_height = args_info.fullscreen ? desktop.height
                                   : args_info.window_height ? args_info.window_height
                                   : static_cast<unsigned int>(BOARD_SQUARE_INIT_SIZE * BOARD_HEIGHT);

        sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Chess",
            args_info.fullscreen ? sf::Style::Fullscreen : sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);

        window.setPosition(sf::Vector2i((desktop.width - window.getSize().x) / 2, (desktop.height - window.getSize().y) / 2));
        window.setVerticalSyncEnabled(true);
        window.setFramerateLimit(60);

        Game game(window, args_info.fen);
        game.Run();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
