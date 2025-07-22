#include "utility/ArgsUtility.h"

namespace ISXUtility
{

void PrintHelp(const std::string& program_name)
{
	std::ostringstream os;

	os << "Usage: " << program_name << " [options]\n"
	   << "\nOptions:\n"
	   << "    -h, --help                  show this help message and exit\n"
	   << "    -v, --version               show version information and exit\n"
	   << "    -f, --fen FEN               load chess position from the FEN string\n"
	   << "    -W, --width WIDTH           set the window width\n"
	   << "    -H, --height HEIGHT         set the window height\n"
	   << "    -S, --size WIDTHxHEIGHT     set the window size\n"
	   << "    -F, --fullscreen            launch in fullscreen mode";

	std::cout << os.str() << std::endl;
	exit(EXIT_SUCCESS);
}

void PrintVersion()
{
	std::cout << "Chess v" << CHESS_VERSION << std::endl;
	exit(EXIT_SUCCESS);
}

}
