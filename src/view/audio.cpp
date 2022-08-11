#include "audio.hpp"
#include "../../lib/bass24-linux/bass.h"
#include <chrono>
#include <thread>

void play_audio(const char *filename)
{
    if (!BASS_Init(-1, 44100, 0, 0, 0)) // Initializes BASS Library. Needed only once.
        return;
    HSTREAM AudioChannel = BASS_StreamCreateFile(false, filename, 0, 0, 0);
    // Create a Audio Stream from a File.
    BASS_ChannelPlay(AudioChannel, true);
    // Plays the Stream.
    while (BASS_ChannelIsActive(AudioChannel))
    {
        // Waits until song/audio file ends.
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    BASS_ChannelPlay(AudioChannel, true);
    // Plays the Stream.
    while (BASS_ChannelIsActive(AudioChannel))
    {
        // Waits until song/audio file ends.
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    BASS_ChannelPlay(AudioChannel, true);
    // Plays the Stream.
    while (BASS_ChannelIsActive(AudioChannel))
    {
        // Waits until song/audio file ends.
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    BASS_Free();
}