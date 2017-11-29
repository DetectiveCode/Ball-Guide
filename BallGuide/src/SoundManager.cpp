#include <SoundManager.h>

void SoundManager::LoadSounds(const std::string & name, const std::string & filename, const float & volume)
{
	SoundType type;
	
	sf::SoundBuffer soundBuffer;
	soundBuffer.loadFromFile(m_AssetPath + filename);

	type.buffer = soundBuffer;
	type.volume = volume;

	m_Sounds[name] = type;
}

sf::SoundBuffer& SoundManager::getRef(const std::string & sound)
{
	return m_Sounds.at(sound).buffer;
}

void SoundManager::PlaySound(const std::string & name)
{
	if (m_PlayingSounds.size() == 0)
	{	
		m_PlayingSounds.push_back(sf::Sound());
		m_PlayingSounds.at(0).setBuffer(m_Sounds.at(name).buffer);
		m_PlayingSounds.at(0).setVolume(m_Sounds.at(name).volume);
		m_PlayingSounds.at(0).play();
	}
	else
	{
		bool foundSlot = false;

		for (size_t i = 0; i < m_PlayingSounds.size(); i++)
		{
			if (m_PlayingSounds.at(i).getStatus() != 2)
			{
				m_PlayingSounds.at(i).setBuffer(m_Sounds.at(name).buffer);
				m_PlayingSounds.at(i).setVolume(m_Sounds.at(name).volume);
				m_PlayingSounds.at(i).play();
				foundSlot = true;
				break;
			}
		}

		if (!foundSlot)
		{
			size_t lastElement = m_PlayingSounds.size() - 1;

			m_PlayingSounds.push_back(sf::Sound());
			m_PlayingSounds.at(lastElement).setBuffer(m_Sounds.at(name).buffer);
			m_PlayingSounds.at(lastElement).setVolume(m_Sounds.at(name).volume);
			m_PlayingSounds.at(lastElement).play();
		}
	}
}