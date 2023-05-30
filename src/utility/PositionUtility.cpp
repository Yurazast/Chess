#include "utility/PositionUtility.h"

namespace ISXUtility
{

bool IsValidPosition(const std::string& position)
{
    return position.size() == 2	&& position[0] >= 'a' && position[0] <= 'h' && position[1] >= '1' && position[1] <= '8';
}

Position Convert(const std::string& position)
{
    if (IsValidPosition(position))
    {
        return { static_cast<int8_t>(position[0] - 'a'), static_cast<int8_t>(position[1] - '1') };
    }
    else
    {
        return INVALID_POSITION;
    }
}

}
