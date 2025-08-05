#include <string>
#include <locale>
#include <vector>
#include <thread>
#include <codecvt>
#include <iostream>
#include <windows.h>
#include <SFML/Audio.hpp>

#include "WorkWithAudio.h"

namespace WorkWithAudio
{
	Audio::Audio()
	{
		Audio::filePaths = { "\\Music\\ћ€чик-отбит.wav", "\\Music\\ћ€чик-не-отбит.wav" };
	}

	void Audio::LoadFileToBuffer(MusicModes musicMode)
	{
		// Variables
		std::string temp = "";

		// Select path
		switch (musicMode)
		{
		case WorkWithAudio::MusicModes::TheBallBounced:
			temp = Audio::filePaths.at(0);
			break;

		case WorkWithAudio::MusicModes::TheBallBouncedOff:
			temp = Audio::filePaths.at(1);
			break;

		default:
			break;
		}

		// Load file to buffer
		if (!Audio::soundBuffer.loadFromFile(Audio::GetDirectory() + temp))
		{
			std::cout << "Ќе удалось загрузить аудиофайл!" << std::endl;
		}
	}

	sf::Sound Audio::LoadBufferToSound()
	{
		// Load buffer
		sf::Sound sound = sf::Sound(Audio::soundBuffer);
		return sound;
	}

	void Audio::PlayMusic(sf::Sound& sound)
	{
		if (sound.getStatus() == sf::Music::Status::Stopped)
		{
			// Play music
			sound.play();
		}
	}

	void Audio::StopMusic(sf::Sound& sound)
	{
		// Stop music
		sound.stop();
	}

	void Audio::MultiThreadsPlayMusic(sf::Sound& sound)
	{
		while (TRUE)
		{
			// Play music
			sound.play();
			std::this_thread::sleep_for(std::chrono::seconds(105));
		}
	}

	void Audio::PauseMusic(sf::Sound& sound)
	{
		// Pause music
		sound.pause();
	}

	void Audio::SetVolume(sf::Sound& sound, float volume)
	{
		if ((volume >= 0) && (volume <= 100))
			sound.setVolume(volume);
	}

	std::string Audio::GetDirectory()
	{
		std::string str;

		// Deprecated
		/*TCHAR buffer[MAX_PATH] = { 0 };
		GetModuleFileName(NULL, buffer, MAX_PATH);
		std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		str = converter.to_bytes(std::wstring(buffer).substr(0, pos));*/

		// Actual
		std::filesystem::path currentPath = std::filesystem::current_path();
		str = currentPath.string();

		return str;
	}
}
