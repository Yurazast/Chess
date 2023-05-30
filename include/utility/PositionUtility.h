#ifndef POSITIONUTILITY_H_
#define POSITIONUTILITY_H_

#include <string>

#include "Position.h"

namespace ISXUtility
{

bool IsValidPosition(const std::string& position);
Position Convert(const std::string& position);

}

#endif //POSITIONUTILITY_H_
