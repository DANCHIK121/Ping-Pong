#pragma once

// Standart libraries
#include <string>
#include <vector>

// Project libraries
#include <SFML/Audio.hpp>

namespace WorkWithAudio
{
	enum MusicModes
	{
		TheBallBounced,
		TheBallBouncedOff,
	};

	class Audio
	{
	public:
		Audio();

		sf::Sound LoadBufferToSound();
		
		void PlayMusic(sf::Sound& sound);
		void StopMusic(sf::Sound& sound);
		void LoadFileToBuffer(MusicModes musicMode);
		void SetVolume(sf::Sound& sound, float volume);

	private:
		std::vector<std::string> filePaths;

		sf::SoundBuffer soundBuffer;

		std::string GetDirectory();

		void PauseMusic(sf::Sound& sound);
		void MultiThreadsPlayMusic(sf::Sound& sound);
	};
}