#include "WorkWithAudio.h"
#include <iostream>

namespace WorkWithAudio
{
    Audio::Audio()
    {
        Audio::filePaths = {
            "Music/Мячик-отбит.wav",
            "Music/Мячик-не-отбит.wav"
        };

        Audio::soundObject = { 0 };
    }

    Audio::~Audio()
    {
        if (Audio::soundObject.frameCount > 0)
        {
            UnloadSound(Audio::soundObject);
        }

        CloseAudioDevice();
    }

    void Audio::LoadFileToBuffer(MusicModes musicMode)
    {
        std::string temp = "";

        switch (musicMode)
        {
        case WorkWithAudio::MusicModes::TheBallBounced:
            temp = Audio::filePaths.at(0);
            break;

        case WorkWithAudio::MusicModes::TheBallBouncedOff:
            temp = Audio::filePaths.at(1);
            break;

        default:
            std::cout << "Неизвестный режим музыки!" << std::endl;
            return;
        }

        std::string fullPath = Audio::GetDirectory() + "\\" + temp;

        if (Audio::soundObject.frameCount > 0)
        {
            UnloadSound(Audio::soundObject);
        }

        Audio::soundObject = LoadSound(fullPath.c_str());

        if (Audio::soundObject.frameCount == 0)
        {
            std::cout << "Ошибка загрузки аудиофайла: " << fullPath << std::endl;
            std::cout << "Убедитесь, что файл существует и имеет поддерживаемый формат (.wav, .ogg, .mp3)" << std::endl;
        }
        else
            std::cout << "Аудиофайл загружен: " << fullPath << std::endl;
    }

    void Audio::PlayMusic()
    {
        if (Audio::soundObject.frameCount == 0)
        {
            std::cout << "Ошибка: звук не загружен!" << std::endl;
            return;
        }

        PlaySound(Audio::soundObject);
    }

    void Audio::StopMusic()
    {
        StopSound(Audio::soundObject);
    }

    void Audio::PauseMusic()
    {
        PauseSound(Audio::soundObject);
    }

    void Audio::ResumeMusic()
    {
        ResumeSound(Audio::soundObject);
    }

    void Audio::SetVolume(float volume)
    {
        if ((volume >= 0) && (volume <= 100))
        {
            float raylibVolume = volume / 100.0f;
            SetSoundVolume(Audio::soundObject, raylibVolume);
        }
        else
        {
            std::cout << "Громкость должна быть в диапазоне 0-100!" << std::endl;
        }
    }

    bool Audio::IsPlaying() const
    {
        return IsSoundPlaying(Audio::soundObject);
    }

    Sound Audio::GetSound() const
    {
        return Audio::soundObject;
    }

    std::string Audio::GetDirectory()
    {
        std::filesystem::path currentPath = std::filesystem::current_path();
        return currentPath.string();
    }
}