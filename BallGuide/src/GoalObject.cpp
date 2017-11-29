#include <GoalObject.h>

GoalObject::GoalObject(Game * Game, float PosX, float PosY)
{
	m_Game = Game;

	m_PlankObjects.push_back(PlankObject(m_Game, 1));
	m_PlankObjects.push_back(PlankObject(m_Game, 1));
	m_PlankObjects.push_back(PlankObject(m_Game, 1));

	m_PlankObjects[0].m_Shape.setPosition(sf::Vector2f(0.f + PosX, 0.f + PosY));
	m_PlankObjects[1].m_Shape.setPosition(sf::Vector2f(90.f + PosX, 0.f + PosY));
	m_PlankObjects[2].m_Shape.setPosition(sf::Vector2f(45.f + PosX, 45.f + PosY));

	m_PlankObjects[0].m_Shape.setRotation(90.f);
	m_PlankObjects[1].m_Shape.setRotation(90.f);

	for (size_t i = 0; i < m_PlankObjects.size(); i++)
	{
		m_PlankObjects[i].Update(0);
	}
}

void GoalObject::Update(const float elapsed)
{
}

void GoalObject::Destroy()
{
	for (size_t i = 0; i < m_PlankObjects.size(); i++)
	{
		m_PlankObjects[i].Destroy();
	}

	m_PlankObjects.clear();
}

void GoalObject::Draw()
{
	for (size_t i = 0; i < m_PlankObjects.size(); i++)
	{
		m_Game->m_Window.draw(m_PlankObjects[i].m_Shape);
	}
}
