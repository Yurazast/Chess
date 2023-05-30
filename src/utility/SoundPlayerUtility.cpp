#include "utility/SoundPlayerUtility.h"

namespace ISXUtility
{

std::string GetSoundFilepathByType(ISXChess::SoundType sound_type)
{
    if (sound_type == ISXChess::SoundType::MOVE_PIECE)
    {
        return MOVE_PIECE_SOUND_FILEPATH;
    }
    else if (sound_type == ISXChess::SoundType::NOTIFICATION)
    {
        return NOTIFICATION_SOUND_FILEPATH;
    }

    return "";
}

}
