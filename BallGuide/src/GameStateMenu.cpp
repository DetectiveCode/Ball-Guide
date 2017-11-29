#include <GameStateMenu.h>
#include <GameStatePlaying.h>
#include <GameStateCredits.h>
#include <SFML\Graphics.hpp>

GameStateMenu::GameStateMenu(Game* Game)
{
	m_Game = Game;
	sf::Vector2f pos = sf::Vector2f(m_Game->m_Window.getSize());
	m_View.setSize(pos);
	pos *= 0.5f;
	m_View.setCenter(pos);

	m_ButtonManager = ButtonManager(Game);
	LoadButtons();

	m_Title.setTexture(m_Game->m_TextureManager.GetRef("title"));
	m_Title.setPosition(sf::Vector2f(GetCenterTextureX("title"), 50));
}

void GameStateMenu::Draw(const float elapsed)
{
	m_Game->m_Window.setView(m_View);

	m_Game->m_Window.clear(sf::Color::Black);
	m_Game->m_Window.draw(m_Game->m_Background);
	m_Game->m_Window.draw(m_Title);
	m_ButtonManager.Draw();
}

void GameStateMenu::Update(const float elapsed)
{
	m_ButtonManager.Update();
}

void GameStateMenu::HandleInput()
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
					m_Game->m_Window.close();
				}

				if (event.key.code == sf::Keyboard::Space)
				{
					m_Game->PushState(new GameStatePlaying(m_Game));
				}

				if (event.key.code == sf::Keyboard::M)
				{
					m_Game->m_AudioMute = !m_Game->m_AudioMute;
				}
				break;
			}

			case sf::Event::MouseButtonPressed:
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (m_ButtonManager.ButtonEvent("play"))
					{
						m_Game->m_SoundManager.PlaySound("click");
						m_Game->PushState(new GameStatePlaying(m_Game));
					}

					if (m_ButtonManager.ButtonEvent("credits"))
					{
						m_Game->m_SoundManager.PlaySound("click");
						m_Game->PushState(new GameStateCredits(m_Game));
					}

					if (m_ButtonManager.ButtonEvent("exit"))
					{
						m_Game->m_SoundManager.PlaySound("click");
						m_Game->m_Window.close();
					}
				}
				break;
			}

			default: break;
		}
	}
}

void GameStateMenu::LoadButtons()
{
	m_ButtonManager.LoadButton("play", "play0", "play1", "rollover", GetCenterTextureX("play0"), GetCenterTextureY("play0"));
	m_ButtonManager.LoadButton("credits", "credits0", "credits1", "rollover", GetCenterTextureX("credits0"), GetCenterTextureY("credits0") + GetTextureY("credits0"));
	m_ButtonManager.LoadButton("exit", "exit0", "exit1", "rollover", GetCenterTextureX("exit0"), GetCenterTextureY("exit0") + GetTextureY("exit0") * 2);
}