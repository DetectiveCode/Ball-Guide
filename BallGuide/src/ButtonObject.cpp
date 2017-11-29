#include <ButtonObject.h>

ButtonObject::ButtonObject(Game* Game)
{
	m_Game = Game;
}

void ButtonObject::Update()
{
	sf::Vector2f m_MousePos = sf::Vector2f(sf::Mouse::getPosition(m_Game->m_Window));

	if (m_ButtonSprite.getGlobalBounds().contains(m_MousePos))
	{
		if (!m_Hovered && m_Game->m_Window.hasFocus())
		{
			m_ButtonSprite.setTexture(m_Game->m_TextureManager.GetRef(m_HoverTexture));
			m_Game->m_SoundManager.PlaySound(m_RollSound);
			m_Hovered = true;
		}
	}
	else
	{
		if (m_Hovered)
		{
			m_ButtonSprite.setTexture(m_Game->m_TextureManager.GetRef(m_NormalTexture));
			m_Hovered = false;
		}
	}
}

void ButtonObject::Draw()
{
	m_Game->m_Window.draw(m_ButtonSprite);
}
