#ifndef ARGSUTILITY_H_
#define ARGSUTILITY_H_

#include <iostream>
#include <sstream>

constexpr auto CHESS_VERSION = "1.0.0";

namespace ISXUtility
{

void PrintHelp(const std::string& program_name);
void PrintVersion();

}

#endif //ARGSUTILITY_H_
