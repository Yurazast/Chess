#ifndef SOUNDPLAYER_H_
#define SOUNDPLAYER_H_

#include <string>
#include <map>

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include "audio/SoundType.h"
#include "utility/SoundPlayerUtility.h"

class SoundPlayer
{
public:
    static sf::SoundBuffer LoadFromFile(const std::string& filepath);
	static void Play(ISXChess::SoundType sound_type);
	static void Pause();
	static void Stop();

private:
    static sf::Sound s_sound;
    static std::map<ISXChess::SoundType, sf::SoundBuffer> s_sound_buffers;
};

#endif //SOUNDPLAYER_H_
