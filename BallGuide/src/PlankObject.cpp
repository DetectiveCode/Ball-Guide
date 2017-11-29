#include <PlankObject.h>

PlankObject::PlankObject(Game* Game, int plankType)
{
	m_Game = Game;
	m_PlankType = plankType;

	if (plankType == 0) //normal plank
	{
		m_Position = sf::Vector2f(280.5f, 100.f);
		m_Size = sf::Vector2f(200.f, 10.f);
	}
	else if (plankType == 1) //short plank
	{
		m_Position = sf::Vector2f(505.5f, 100.f);
		m_Size = sf::Vector2f(100.f, 10.f);
	}
	else if (plankType == 2) //windmill plank
	{
		m_Position = sf::Vector2f(705.f, 100.f);
		m_Size = sf::Vector2f(150.f, 10.f);
	}
	else //undefined plank
	{
		m_Position = sf::Vector2f(280.5f, 100.f);
		m_Size = sf::Vector2f(200.f, 10.f);
	}

	m_Shape.setSize(m_Size);
	m_Shape.setPosition(m_Position);
	m_Shape.setOrigin(sf::Vector2f(m_Shape.getSize().x / 2, m_Shape.getSize().y / 2));
	m_Shape.setFillColor(sf::Color::Green);
	//m_Shape.setOutlineColor(sf::Color::Black);
	//m_Shape.setOutlineThickness(1.f);
	m_Shape.setRotation(0.f);

	if (plankType == 2)
	{
		m_CircleShape.setRadius(m_Size.y * 0.4f);
		m_CircleShape.setPosition(m_Position);
		m_CircleShape.setOrigin(sf::Vector2f(m_CircleShape.getRadius(), m_CircleShape.getRadius()));
		m_CircleShape.setFillColor(sf::Color(0, 220, 0, 255));
		//m_CircleShape.setOutlineColor(sf::Color::Black);
		//m_CircleShape.setOutlineThickness(1.f);
		m_CircleShape.setRotation(0.f);

		b2PolygonShape bodyShape1;
		b2CircleShape bodyShape2;
		CreateBody(bodyShape1, bodyShape2);
	}
	else
	{
		b2PolygonShape bodyShape;
		CreateBody(bodyShape);
	}
}

void PlankObject::Update(const float elapsed)
{
	if (m_PlankType == 2)
	{
		if (!m_Game->m_UpdateWorld)
		{
			m_Body->SetTransform(b2Vec2(m_Shape.getPosition().x / m_Game->SCALE, m_Shape.getPosition().y / m_Game->SCALE), m_Shape.getRotation() * b2_pi / 180);
			m_Body2->SetTransform(b2Vec2(m_Shape.getPosition().x / m_Game->SCALE, m_Shape.getPosition().y / m_Game->SCALE), m_Body2->GetAngle());
		}
		else
		{
			m_Body->SetTransform(b2Vec2(m_Shape.getPosition().x / m_Game->SCALE, m_Shape.getPosition().y / m_Game->SCALE), m_Body->GetAngle());
			m_Body2->SetTransform(b2Vec2(m_Shape.getPosition().x / m_Game->SCALE, m_Shape.getPosition().y / m_Game->SCALE), m_Body2->GetAngle());
		}

		m_Shape.setPosition(m_Game->SCALE * m_Body->GetPosition().x, m_Game->SCALE * m_Body->GetPosition().y);
		m_Shape.setRotation(m_Body->GetAngle() * 180 / b2_pi);

		m_CircleShape.setPosition(m_Game->SCALE * m_Body2->GetPosition().x, m_Game->SCALE * m_Body2->GetPosition().y);
		m_CircleShape.setRotation(m_Body2->GetAngle() * 180 / b2_pi);
	}
	else
	{
		m_Body->SetTransform(b2Vec2(m_Shape.getPosition().x / m_Game->SCALE, m_Shape.getPosition().y / m_Game->SCALE), m_Shape.getRotation() * b2_pi / 180);
	}
}

void PlankObject::Destroy()
{
	m_Game->World.DestroyBody(m_Body);

	if (m_PlankType == 2)
	{
		m_Game->World.DestroyBody(m_Body2);
	}
}
