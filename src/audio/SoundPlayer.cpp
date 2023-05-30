#include "audio/SoundPlayer.h"

std::map<ISXChess::SoundType, sf::SoundBuffer> SoundPlayer::s_sound_buffers;
sf::Sound SoundPlayer::s_sound;

sf::SoundBuffer SoundPlayer::LoadFromFile(const std::string& filepath)
{
    sf::SoundBuffer sound_buffer;
    sound_buffer.loadFromFile(filepath);
    return sound_buffer;
}

void SoundPlayer::Play(ISXChess::SoundType sound_type)
{
    if (s_sound_buffers.find(sound_type) == s_sound_buffers.end())
    {
        s_sound_buffers[sound_type] = LoadFromFile(ISXUtility::GetSoundFilepathByType(sound_type));
    }

    s_sound.setBuffer(s_sound_buffers[sound_type]);
    s_sound.play();
}

void SoundPlayer::Pause()
{
    s_sound.pause();
}

void SoundPlayer::Stop()
{
    s_sound.stop();
}
