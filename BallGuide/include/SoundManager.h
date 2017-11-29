#pragma once
#include <SFML/Audio.hpp>
#include <map>

/** Sound type class, used to define new type which includes sound buffer and volume. */
class SoundType
{
public:
	sf::SoundBuffer buffer; ///< A sound buffer.
	float volume; ///< A float value for volume.
};

/** Sound manager class, allows you to load sounds, play sounds and get references to managed sounds. */
class SoundManager
{
public:
	void LoadSounds(const std::string & name, const std::string & filename, const float & volume = 100); ///< Load sound with specified name, filename and volume.
	void PlaySound(const std::string & name); ///< Play specified sound.
	sf::SoundBuffer& getRef(const std::string & sound); ///< Get reference to specified sound.

private:
	std::map<std::string, SoundType> m_Sounds; ///< A private array of map, with string as key and sound type as type.
	std::vector<sf::Sound> m_PlayingSounds; ///< A private array of vector, containing sound.
	std::string m_AssetPath = ".\\assets\\audio\\"; ///< A string with the location of the audio resource folder.
};