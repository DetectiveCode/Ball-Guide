#include <GameStateCredits.h>
#include <GameStatePlaying.h>
#include <SFML\Graphics.hpp>

GameStateCredits::GameStateCredits(Game* Game)
{
	m_Game = Game;
	sf::Vector2f pos = sf::Vector2f(m_Game->m_Window.getSize());
	m_View.setSize(pos);
	pos *= 0.5f;
	m_View.setCenter(pos);

	m_ButtonManager = ButtonManager(Game);

	m_Title.setTexture(m_Game->m_TextureManager.GetRef("title"));
	m_Title.setPosition(sf::Vector2f(GetCenterTextureX("title"), 50.f));

	m_ButtonManager.LoadButton("back", "back0", "back1", "rollover", 10.f, m_Game->m_Window.getSize().y - 57.f);

	m_Credits.setTexture(m_Game->m_TextureManager.GetRef("credits"));
	m_Credits.setPosition(sf::Vector2f(GetCenterTextureX("credits"), GetCenterTextureY("credits") + 75.f));
}

void GameStateCredits::Draw(const float elapsed)
{
	m_Game->m_Window.setView(m_View);

	m_Game->m_Window.clear(sf::Color::Black);
	m_Game->m_Window.draw(m_Game->m_Background);
	m_Game->m_Window.draw(m_Title);
	m_Game->m_Window.draw(m_Credits);
	m_ButtonManager.Draw();
}

void GameStateCredits::Update(const float elapsed)
{
	m_ButtonManager.Update();
}

void GameStateCredits::HandleInput()
{
	sf::Event event;

	while (m_Game->m_Window.pollEvent(event))
	{
		switch (event.type)
		{
			/*Close the Window*/
		case sf::Event::Closed:
		{
			m_Game->m_Window.close();
			break;
		}

		/*Resize the Window*/
		case sf::Event::Resized:
		{
			m_View.setSize(float(event.size.width), float(event.size.height));
			m_Game->m_Background.setPosition(m_Game->m_Window.mapPixelToCoords(sf::Vector2i(0, 0), m_View));
			m_Game->m_Background.setScale(
				float(event.size.width) / float(m_Game->m_Background.getTexture()->getSize().x),
				float(event.size.height) / float(m_Game->m_Background.getTexture()->getSize().y));
			break;
		}

		/*Key Press*/
		case sf::Event::KeyPressed:
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				m_Game->PopState();
			}
			break;
		}

		case sf::Event::MouseButtonPressed:
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (m_ButtonManager.ButtonEvent("back"))
				{
					m_Game->m_SoundManager.PlaySound("click");
					m_Game->PopState();
				}
			}
			break;
		}

		default: break;
		}
	}
}