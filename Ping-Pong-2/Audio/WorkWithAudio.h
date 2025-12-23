#ifndef WORK_WITH_AUDIO_H
#define WORK_WITH_AUDIO_H

#include <string>
#include <vector>
#include <filesystem>
#include "raylib.h"

namespace WorkWithAudio
{
    enum class MusicModes
    {
        TheBallBounced,
        TheBallBouncedOff
    };

    class Audio
    {
    private:
        std::vector<std::string> filePaths;
        Sound soundObject;                 

        std::string GetDirectory();        

    public:
        Audio();

        ~Audio();

        void LoadFileToBuffer(MusicModes musicMode);

        void PlayMusic();

        void StopMusic();

        void PauseMusic();

        void ResumeMusic();

        void SetVolume(float volume);

        bool IsPlaying() const;

        Sound GetSound() const;
    };
}

#endif 