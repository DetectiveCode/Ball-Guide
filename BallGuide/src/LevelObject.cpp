#include <LevelObject.h>

LevelObject::LevelObject(Game* Game, float ballX, float ballY, float goalX, float goalY, int maxPlanks, int maxShortPlanks, int maxWindmills)
{
	m_Game = Game;

	m_ballX = ballX;
	m_ballY = ballY;
	m_goalX = goalX;
	m_goalY = goalY;
	m_MaxNormalPlanks = maxPlanks;
	m_MaxShortPlanks = maxShortPlanks;
	m_MaxWindmillPlanks = maxWindmills;
}

void LevelObject::Update(const float elapsed)
{
	if (m_BallObjects.size() != 0)
	{
		for (size_t i = 0; i < m_BallObjects.size(); i++)
		{
			if (m_BallObjects[i].GetBody()->GetLinearVelocity().x <= 0.2 && m_BallObjects[i].GetBody()->GetLinearVelocity().x >= -0.2)
			{
				m_BallObjects[i].GetBody()->SetLinearVelocity(b2Vec2(0, m_BallObjects[i].GetBody()->GetLinearVelocity().y));
			}
			m_BallObjects[i].Update(elapsed);
		}
	}

	if (m_GoalObjects.size() != 0)
	{
		for (size_t i = 0; i < m_GoalObjects.size(); i++)
		{
			m_GoalObjects[i].Update(elapsed);
		}
	}

	if (m_PlankObjects.size() != 0)
	{
		for (size_t i = 0; i < m_PlankObjects.size(); i++)
		{
			m_PlankObjects[i].Update(elapsed);
		}
	}
}

bool LevelObject::CheckLoss()
{
	// false = not lost
	// true = has lost

	for (size_t i = 0; i < m_BallObjects.size(); i++)
	{
		if (m_BallObjects[i].m_Shape.getPosition().x > m_Game->m_Window.getSize().x + m_BallObjects[i].m_Shape.getRadius())
		{
			return true;
			break;
		}

		if (m_BallObjects[i].m_Shape.getPosition().x < -m_BallObjects[i].m_Shape.getRadius())
		{
			return true;
			break;
		}

		if (m_BallObjects[i].m_Shape.getPosition().y > m_Game->m_Window.getSize().y + m_BallObjects[i].m_Shape.getRadius())
		{
			return true;
			break;
		}

		if (m_BallObjects[i].m_Shape.getPosition().y < -m_BallObjects[i].m_Shape.getRadius())
		{
			return true;
			break;
		}

		if (m_BallObjects[i].GetBody()->GetLinearVelocity().x == 0.f && m_BallObjects[i].GetBody()->GetLinearVelocity().y == 0.f)
		{
			if (!CheckWin())
			{
				return true;
			}
		}
	}

	return false;
}

bool LevelObject::CheckWin()
{
	// false = not won
	// true = has won

	for (size_t i = 0; i < m_BallObjects.size(); i++)
	{
		if (m_BallObjects[i].GetBody()->GetLinearVelocity().x == 0.f && m_BallObjects[i].GetBody()->GetLinearVelocity().y == 0.f)
		{
			for (size_t x = 0; x < m_GoalObjects.size(); x++)
			{
				float ballY = m_BallObjects[i].m_Shape.getPosition().y + (m_BallObjects[i].m_Shape.getRadius() + m_GoalObjects[x].m_PlankObjects[2].m_Shape.getSize().y / 2);
				float plankY = m_GoalObjects[x].m_PlankObjects[2].m_Shape.getPosition().y;

				if ((plankY + 5 > ballY) && (plankY - 5 < ballY))
				{
					float ballX = m_BallObjects[i].m_Shape.getPosition().x - m_BallObjects[i].m_Shape.getRadius();
					float plankX = m_GoalObjects[x].m_PlankObjects[2].m_Shape.getPosition().x;

					if ((ballX > plankX - m_GoalObjects[x].m_PlankObjects[2].m_Shape.getSize().x / 2) && (ballX < plankX + m_GoalObjects[x].m_PlankObjects[2].m_Shape.getSize().x / 2))
					{
						return true;
						break;
					}
				}
			}
		}
	}

	return false;
}

void LevelObject::Draw()
{
	for (size_t i = 0; i < m_BallObjects.size(); i++)
	{
		m_Game->m_Window.draw(m_BallObjects[i].m_Shape);
	}

	for (size_t i = 0; i < m_GoalObjects.size(); i++)
	{
		m_GoalObjects[i].Draw();
	}

	for (size_t i = 0; i < m_PlankObjects.size(); i++)
	{
		m_Game->m_Window.draw(m_PlankObjects[i].m_Shape);
		m_Game->m_Window.draw(m_PlankObjects[i].m_CircleShape);
	}
}

void LevelObject::Start()
{
	m_BallObjects[0].ApplyForce(2.25f);
}

void LevelObject::Destroy()
{
	m_Init = false;

	if (!m_Game->World.IsLocked())
	{
		for (size_t i = 0; i < m_BallObjects.size(); i++)
		{
			m_BallObjects[i].Destroy();
		}
		m_BallObjects.clear();

		for (size_t i = 0; i < m_GoalObjects.size(); i++)
		{
			m_GoalObjects[i].Destroy();
		}
		m_GoalObjects.clear();

		for (size_t i = 0; i < m_PlankObjects.size(); i++)
		{
			m_PlankObjects[i].Destroy();
		}
		m_PlankObjects.clear();
	}
}

void LevelObject::Init()
{
	if (!m_Init)
	{
		m_GoalObjects.push_back(GoalObject(m_Game, m_goalX, m_goalY));
		m_BallObjects.push_back(BallObject(m_Game, m_ballX, m_ballY));

		m_PlankObjects.push_back(PlankObject(m_Game, 1));
		m_PlankObjects[0].m_Shape.setPosition(sf::Vector2f(m_ballX, m_ballY + 15.f));
		m_PlankObjects[0].Update(0);
	}

	m_Init = true;
}
