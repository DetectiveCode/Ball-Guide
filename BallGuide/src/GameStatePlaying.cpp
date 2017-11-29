#include <GameStatePlaying.h>

GameStatePlaying::GameStatePlaying(Game * Game)
{
	m_Game = Game;
	sf::Vector2f pos = sf::Vector2f(m_Game->m_Window.getSize());
	m_GameView.setSize(pos);
	pos *= 0.5f;
	m_GameView.setCenter(pos);
	
	LoadPlaceHolders();
	LoadLevels();
	LoadButtons();
}

void GameStatePlaying::Draw(const float elapsed)
{
	m_Game->m_Window.clear(sf::Color::White);
	m_Game->m_Window.draw(m_Game->m_Background);

	for (size_t i = 0; i < m_PlankObjects.size(); i++)
	{
		m_Game->m_Window.draw(m_PlankObjects[i].m_Shape);
		m_Game->m_Window.draw(m_PlankObjects[i].m_CircleShape);
	}

	if (m_LoadedLevels.size() != 0)
	{
		m_LoadedLevels[m_Level].Draw();
	}

	m_Game->m_Window.draw(m_ShapePanel);
	m_Game->m_Window.draw(m_NormalPlank);
	m_Game->m_Window.draw(m_ShortPlank);
	m_Game->m_Window.draw(m_WindmillPlank);
	m_Game->m_Window.draw(m_WindmillJoint);

	DrawText();
	m_GameButtons.Draw();

	if (m_Pause)
	{
		m_Game->m_Window.draw(m_PausePanel);
		m_PauseButtons.Draw();
		m_InterfaceText.setCharacterSize(36);
		m_InterfaceText.setString("PAUSE");
		m_InterfaceText.setPosition((float)m_Game->m_Window.getSize().x / 2 - 60, (float)m_Game->m_Window.getSize().y / 2 - 80);
		m_Game->m_Window.draw(m_InterfaceText);
	}
	else if (m_Victory)
	{
		m_Game->m_Window.draw(m_PausePanel);
		m_VictoryButtons.Draw();
		m_InterfaceText.setCharacterSize(36);
		m_InterfaceText.setString("VICTORY");
		m_InterfaceText.setPosition((float)m_Game->m_Window.getSize().x / 2 - 80, (float)m_Game->m_Window.getSize().y / 2 - 80);
		m_Game->m_Window.draw(m_InterfaceText);
	}
	else if (m_Defeat)
	{
		m_Game->m_Window.draw(m_PausePanel);
		m_DefeatButtons.Draw();
		m_InterfaceText.setCharacterSize(36);

		if (m_Fini)
		{
			m_InterfaceText.setString("FINI");
			m_InterfaceText.setPosition((float)m_Game->m_Window.getSize().x / 2 - 40, (float)m_Game->m_Window.getSize().y / 2 - 80);
		}
		else
		{
			m_InterfaceText.setString("DEFEAT");
			m_InterfaceText.setPosition((float)m_Game->m_Window.getSize().x / 2 - 70, (float)m_Game->m_Window.getSize().y / 2 - 80);
		}
		
		m_Game->m_Window.draw(m_InterfaceText);
	}
}

void GameStatePlaying::Update(const float elapsed)
{
	if (m_Pause)
	{
		m_Game->m_UpdateWorld = false;
		m_PauseButtons.Update();
	}
	else if (m_Victory)
	{
		m_Game->m_UpdateWorld = false;
		m_VictoryButtons.Update();
	}
	else if (m_Defeat)
	{
		m_Game->m_UpdateWorld = false;
		m_DefeatButtons.Update();
	}
	else if (!m_Started)
	{
		m_Game->m_UpdateWorld = false;
		m_GameButtons.Update();
	}
	else
	{
		m_Game->m_UpdateWorld = true;
		m_GameButtons.Update();
	}

	for (size_t i = 0; i < m_PlankObjects.size(); i++)
	{
		m_PlankObjects[i].Update(elapsed);
	}

	if (m_LoadedLevels.size() != 0)
	{
		m_LoadedLevels[m_Level].Update(elapsed);

		if (m_Started && (!m_Defeat && !m_Victory))
		{
			if (m_LoadedLevels[m_Level].CheckLoss())
			{
				m_Defeat = true;
			}
			else if (m_LoadedLevels[m_Level].CheckWin())
			{
				if (m_Level == m_LoadedLevels.size()-1)
				{
					m_Fini = true;
					m_Defeat = true;
				}
				else
				{
					m_Victory = true;
				}
			}
		}
	}
}

void GameStatePlaying::HandleInput()
{
	sf::Event event;

	while (m_Game->m_Window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
		{
			m_Game->m_Window.close();
			break;
		}

		case sf::Event::Resized:
		{
			m_GameView.setSize(float(event.size.width), float(event.size.height));
			m_Game->m_Background.setPosition(m_Game->m_Window.mapPixelToCoords(sf::Vector2i(0, 0), m_GameView));
			m_Game->m_Background.setScale(
				float(event.size.width) / float(m_Game->m_Background.getTexture()->getSize().x),
				float(event.size.height) / float(m_Game->m_Background.getTexture()->getSize().y));
			break;
		}

		case sf::Event::KeyPressed:
		{
			if (event.key.code == sf::Keyboard::M)
			{
				m_Game->m_AudioMute = !m_Game->m_AudioMute;
				break;
			}

			if (event.key.code == sf::Keyboard::P || event.key.code == sf::Keyboard::Escape)
			{
				m_Pause = !m_Pause;
				break;
			}
			
			if (m_PlankObjects.size() != 0)
			{
				if (event.key.code == sf::Keyboard::Right && !m_Started)
				{
					m_PlankObjects[selectedObject].m_Shape.setRotation(m_PlankObjects[selectedObject].m_Shape.getRotation() + 1.f);
					break;
				}

				if (event.key.code == sf::Keyboard::Left && !m_Started)
				{
					m_PlankObjects[selectedObject].m_Shape.setRotation(m_PlankObjects[selectedObject].m_Shape.getRotation() - 1.f);
					break;
				}
			}
			break;
		}

		case sf::Event::MouseButtonPressed:
		{
			if (event.mouseButton.button == sf::Mouse::Button::Left)
			{
				if (m_Pause)
				{
					if (m_PauseButtons.ButtonEvent("menu"))
					{
						m_Game->m_SoundManager.PlaySound("click");
						DestroyPlanks();
						m_LoadedLevels[m_Level].Destroy();
						m_Game->PopState();
						break;
					}

					if (m_PauseButtons.ButtonEvent("resume"))
					{
						m_Game->m_SoundManager.PlaySound("click");
						m_Pause = false;
						break;
					}
				}
				else
				{
					if (m_Victory)
					{
						if (m_VictoryButtons.ButtonEvent("menu"))
						{
							m_Game->m_SoundManager.PlaySound("click");
							DestroyPlanks();
							m_LoadedLevels[m_Level].Destroy();
							m_Game->PopState();
							break;
						}

						if (m_VictoryButtons.ButtonEvent("continue"))
						{
							m_Started = false;
							m_LoadedLevels[m_Level].Destroy();
							DestroyPlanks();
							m_Level++;

							if (m_Level < (int)m_LoadedLevels.size())
							{
								m_LoadedLevels[m_Level].Init();
								m_Victory = false;
							}
							break;
						}
					}
					else if (m_Defeat)
					{
						if (m_DefeatButtons.ButtonEvent("menu"))
						{
							m_Game->m_SoundManager.PlaySound("click");

							DestroyPlanks();
							m_LoadedLevels[m_Level].Destroy();
							m_Game->PopState();
							break;
						}

						if (m_DefeatButtons.ButtonEvent("restart"))
						{
							m_Game->m_SoundManager.PlaySound("click");
							m_LoadedLevels[m_Level].Destroy();

							if (!m_Fini)
							{
								m_Lives--;
							}

							if (m_Lives == 0)
							{
								m_Level = 0;
								m_Lives = 3;
								DestroyPlanks();
							}
							
							m_LoadedLevels[m_Level].Init();

							m_Defeat = false;
							m_Started = false;
							break;
						}
					}
					else if (!m_Started && m_LoadedLevels.size() != 0)
					{
						if (m_GameButtons.ButtonEvent("start"))
						{
							m_Game->m_SoundManager.PlaySound("click");
							m_LoadedLevels[m_Level].Start();
							m_Game->m_UpdateWorld = true;
							m_Started = true;
							break;
						}
					}
					else if (m_Started && m_LoadedLevels.size() != 0)
					{
						if (m_GameButtons.ButtonEvent("giveup"))
						{
							m_Game->m_SoundManager.PlaySound("click");
							m_Defeat = true;
							break;
						}
					}
				}

				if (m_PlankObjects.size() != 0 && !m_Started)
				{
					for (size_t i = m_PlankObjects.size(); i-- > 0;)
					{
						if (m_PlankObjects[i].m_Shape.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(m_Game->m_Window))))
						{
							selectedObject = i;
							break;
						}
					}

					if (m_PlankObjects[selectedObject].m_Shape.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(m_Game->m_Window))))
					{
						m_PlankObjects[selectedObject].m_MoveShape = true;
						break;
					}
				}

				if (m_LoadedLevels.size() != 0 && !m_Started)
				{
					if (m_NormalPlank.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(m_Game->m_Window))))
					{
						if (totalNormalPlanks < m_LoadedLevels[m_Level].m_MaxNormalPlanks)
						{
							m_PlankObjects.push_back(PlankObject(m_Game, 0));
							totalNormalPlanks++;
						}
						break;
					}

					if (m_ShortPlank.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(m_Game->m_Window))))
					{
						if (totalShortPlanks < m_LoadedLevels[m_Level].m_MaxShortPlanks)
						{
							m_PlankObjects.push_back(PlankObject(m_Game, 1));
							totalShortPlanks++;
						}
						break;
					}

					if (m_WindmillPlank.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(m_Game->m_Window))))
					{
						if (totalWindmills < m_LoadedLevels[m_Level].m_MaxWindmillPlanks)
						{
							m_PlankObjects.push_back(PlankObject(m_Game, 2));
							totalWindmills++;
						}
						break;
					}
				}
				break;
			}
		}

		case sf::Event::MouseButtonReleased:
		{
			if (m_PlankObjects.size() != 0 && selectedObject < (int)m_PlankObjects.size())
			{
				m_PlankObjects[selectedObject].m_MoveShape = false;
			}
			break;
		}

		case sf::Event::MouseMoved:
		{
			if (m_PlankObjects.size() == 0) break;
			if (selectedObject >= (int)m_PlankObjects.size()) break;

			if (m_PlankObjects[selectedObject].m_MoveShape)
			{				
				float mouseX = (float)sf::Mouse::getPosition(m_Game->m_Window).x;
				float mouseY = (float)sf::Mouse::getPosition(m_Game->m_Window).y;

				float windowH = (float)m_Game->m_Window.getSize().y;
				float windowW = (float)m_Game->m_Window.getSize().x;

				float shapeX = m_PlankObjects[selectedObject].m_Shape.getPosition().x;
				float shapeY = m_PlankObjects[selectedObject].m_Shape.getPosition().y;

				if (mouseX < 0 + m_PlankObjects[selectedObject].m_Shape.getOrigin().y)
				{
					m_PlankObjects[selectedObject].m_Shape.setPosition(sf::Vector2f(shapeX, mouseY));
				}
				else if (mouseX > windowW - m_PlankObjects[selectedObject].m_Shape.getOrigin().y)
				{
					m_PlankObjects[selectedObject].m_Shape.setPosition(sf::Vector2f(shapeX, mouseY));
				}
				else if (mouseY < 0 + m_PlankObjects[selectedObject].m_Shape.getOrigin().y)
				{
					m_PlankObjects[selectedObject].m_Shape.setPosition(sf::Vector2f(mouseX, shapeY));
				}
				else if (mouseY > windowH - m_PlankObjects[selectedObject].m_Shape.getOrigin().y)
				{
					m_PlankObjects[selectedObject].m_Shape.setPosition(sf::Vector2f(mouseX, shapeY));
				}
				else
				{
					m_PlankObjects[selectedObject].m_Shape.setPosition(sf::Vector2f(mouseX, mouseY));
				}
			}

			break;
		}

		default: break;
		}
	}
}

void GameStatePlaying::LoadPlaceHolders()
{
	m_ShapePanel.setTexture(m_Game->m_TextureManager.GetRef("panel"));
	m_ShapePanel.setPosition(sf::Vector2f(GetCenterTextureX("panel"), 0));

	m_PausePanel.setTexture(m_Game->m_TextureManager.GetRef("pausepanel"));
	m_PausePanel.setPosition(sf::Vector2f(GetCenterTextureX("pausepanel"), GetCenterTextureY("pausepanel")));

	m_NormalPlank.setSize(sf::Vector2f(200.f, 10.f));
	m_NormalPlank.setPosition(180.5f, 30.f);
	m_NormalPlank.setOrigin(sf::Vector2f(0.f, 0.f));
	m_NormalPlank.setFillColor(sf::Color::Green);

	m_ShortPlank.setSize(sf::Vector2f(100.f, 10.f));
	m_ShortPlank.setPosition(455.5f, 30.f);
	m_ShortPlank.setOrigin(sf::Vector2f(0.f, 0.f));
	m_ShortPlank.setFillColor(sf::Color::Green);

	m_WindmillPlank.setSize(sf::Vector2f(150.f, 10.f));
	m_WindmillPlank.setPosition(630.5f, 30.f);
	m_WindmillPlank.setOrigin(sf::Vector2f(0.f, 0.f));
	m_WindmillPlank.setFillColor(sf::Color::Green);

	m_WindmillJoint.setRadius(4.f);
	m_WindmillJoint.setPosition(705.f, 33.f);
	m_WindmillJoint.setOrigin(sf::Vector2f(2.f, 2.f));
	m_WindmillJoint.setFillColor(sf::Color(0, 220, 0, 255));
}

void GameStatePlaying::LoadLevels()
{
	m_LoadedLevels.push_back(LevelObject(m_Game, 20, 100, 150, 280, 0, 1, 0)); //Level 1
	m_LoadedLevels.push_back(LevelObject(m_Game, 20, 100, 850, 580, 2, 3, 0)); //Level 2
	m_LoadedLevels.push_back(LevelObject(m_Game, 20, 100, 020, 500, 0, 0, 1)); //Level 3
	m_LoadedLevels.push_back(LevelObject(m_Game, 20, 300, 850, 380, 3, 1, 1)); //Level 4
	m_LoadedLevels.push_back(LevelObject(m_Game, 20, 300, 450, 330, 2, 2, 1)); //Level 5

	m_LoadedLevels[0].Init();
}

void GameStatePlaying::DrawText()
{
	m_InterfaceText.setFont(m_Game->m_FontManager.GetRef("franks"));
	m_InterfaceText.setCharacterSize(14);
	m_InterfaceText.setFillColor(sf::Color(48, 114, 140, 255));

	m_InterfaceText.setPosition(280.5f, 10.f);
	m_InterfaceText.setString(std::to_string(m_LoadedLevels.size() != 0 ? m_LoadedLevels[m_Level].m_MaxNormalPlanks - totalNormalPlanks : 0));
	m_Game->m_Window.draw(m_InterfaceText);

	m_InterfaceText.setPosition(223.f, 45.f);
	m_InterfaceText.setString("normal planks");
	m_Game->m_Window.draw(m_InterfaceText);

	m_InterfaceText.setPosition(502.f, 10.f);
	m_InterfaceText.setString(std::to_string(m_LoadedLevels.size() != 0 ? m_LoadedLevels[m_Level].m_MaxShortPlanks - totalShortPlanks : 0));
	m_Game->m_Window.draw(m_InterfaceText);

	m_InterfaceText.setPosition(453.f, 45.f);
	m_InterfaceText.setString("short planks");
	m_Game->m_Window.draw(m_InterfaceText);

	m_InterfaceText.setPosition(702.f, 10.f);
	m_InterfaceText.setString(std::to_string(m_LoadedLevels.size() != 0 ? m_LoadedLevels[m_Level].m_MaxWindmillPlanks - totalWindmills : 0));
	m_Game->m_Window.draw(m_InterfaceText);

	m_InterfaceText.setPosition(643.f, 45.f);
	m_InterfaceText.setString("windmill planks");
	m_Game->m_Window.draw(m_InterfaceText);

	m_InterfaceText.setPosition(30.f, 15.f);
	m_InterfaceText.setString("lives: " + std::to_string(m_Lives));
	m_Game->m_Window.draw(m_InterfaceText);

	m_InterfaceText.setPosition(30.f, 40.f);
	m_InterfaceText.setString("level: " + std::to_string(m_Level + 1));
	m_Game->m_Window.draw(m_InterfaceText);
}

void GameStatePlaying::LoadButtons()
{
	m_PauseButtons = ButtonManager(m_Game);
	m_VictoryButtons = ButtonManager(m_Game);
	m_DefeatButtons = ButtonManager(m_Game);
	m_GameButtons = ButtonManager(m_Game);

	m_GameButtons.LoadButton("start", "start0", "start1", "rollover", m_Game->m_Window.getSize().x - GetTextureX("start0") - 17, 10);
	m_GameButtons.LoadButton("giveup", "giveup0", "giveup1", "rollover", m_Game->m_Window.getSize().x - GetTextureX("giveup0") - 17, 35);

	m_PauseButtons.LoadButton("menu", "menu0", "menu1", "rollover", GetCenterTextureX("menu0"), GetCenterTextureY("menu0"));
	m_PauseButtons.LoadButton("resume", "resume0", "resume1", "rollover", GetCenterTextureX("resume0"), GetCenterTextureY("resume0") + GetTextureY("resume0"));

	m_VictoryButtons.LoadButton("menu", "menu0", "menu1", "rollover", GetCenterTextureX("menu0"), GetCenterTextureY("menu0"));
	m_VictoryButtons.LoadButton("continue", "continue0", "continue1", "rollover", GetCenterTextureX("continue0"), GetCenterTextureY("continue0") + GetTextureY("continue0"));

	m_DefeatButtons.LoadButton("menu", "menu0", "menu1", "rollover", GetCenterTextureX("menu0"), GetCenterTextureY("menu0"));
	m_DefeatButtons.LoadButton("restart", "restart0", "restart1", "rollover", GetCenterTextureX("restart0"), GetCenterTextureY("restart0") + GetTextureY("restart0"));
}

void GameStatePlaying::DestroyPlanks()
{
	for (size_t i = 0; i < m_PlankObjects.size(); i++)
	{
		m_PlankObjects[i].Destroy();
	}
	m_PlankObjects.clear();

	totalNormalPlanks = 0;
	totalShortPlanks = 0;
	totalWindmills = 0;
}