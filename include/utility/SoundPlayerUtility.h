#ifndef SOUNDPLAYERUTILITY_H_
#define SOUNDPLAYERUTILITY_H_

#include <string>

#include "audio/SoundType.h"
#include "utility/ResourcesFilepath.h"

namespace ISXUtility
{

std::string GetSoundFilepathByType(ISXChess::SoundType sound_type);

}

#endif //SOUNDPLAYERUTILITY_H_
