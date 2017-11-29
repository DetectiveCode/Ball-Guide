#include <ButtonManager.h>

ButtonManager::ButtonManager(Game * Game)
{
	m_Game = Game;
}

void ButtonManager::LoadButton(const std::string & buttonId, const std::string & normalTexture, const std::string & hoverTexture, const std::string & rollSound, float positionX, float positionY)
{
	ButtonObject newButton(m_Game);

	newButton.m_ButtonId = buttonId;
	newButton.m_NormalTexture = normalTexture;
	newButton.m_HoverTexture = hoverTexture;
	newButton.m_RollSound = rollSound;

	newButton.m_ButtonSprite.setTexture(m_Game->m_TextureManager.GetRef(normalTexture));
	newButton.m_ButtonSprite.setPosition(sf::Vector2f(positionX, positionY));

	m_LoadedButtons.push_back(newButton);
}

void ButtonManager::Update()
{
	for (size_t i = 0; i < m_LoadedButtons.size(); i++)
	{
		m_LoadedButtons[i].Update();
	}
}

void ButtonManager::Draw()
{
	for (size_t i = 0; i < m_LoadedButtons.size(); i++)
	{
		m_LoadedButtons[i].Draw();
	}
}

bool ButtonManager::ButtonEvent(const std::string & buttonId)
{
	sf::Vector2f m_MousePos = sf::Vector2f(sf::Mouse::getPosition(m_Game->m_Window));

	for (size_t i = 0; i < m_LoadedButtons.size(); i++)
	{
		if (m_LoadedButtons[i].m_ButtonId == buttonId)
		{
			if (m_LoadedButtons[i].m_ButtonSprite.getGlobalBounds().contains(m_MousePos))
			{
				return true;
				break;
			}
			else
			{
				return false;
				break;
			}
		}
	}

	return false;
}
