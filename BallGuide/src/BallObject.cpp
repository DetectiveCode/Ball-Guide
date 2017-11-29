#include <BallObject.h>

BallObject::BallObject(Game* Game, float PosX, float PosY)
{
	m_Game = Game;
	m_Position = sf::Vector2f(PosX, PosY);
	m_Size = sf::Vector2f(10, 10);

	m_Shape.setRadius(m_Size.x);
	m_Shape.setPosition(m_Position);
	m_Shape.setOrigin(sf::Vector2f(m_Shape.getRadius(), m_Shape.getRadius()));
	m_Shape.setFillColor(sf::Color::Green);
	//m_Shape.setOutlineColor(sf::Color::Black);
	//m_Shape.setOutlineThickness(1.f);
	m_Shape.setRotation(0.f);

	b2CircleShape bodyShape;
	CreateBody(bodyShape);
}

void BallObject::Update(const float elapsed)
{
	m_Shape.setPosition(m_Game->SCALE * m_Body->GetPosition().x, m_Game->SCALE * m_Body->GetPosition().y);
	m_Shape.setRotation(m_Body->GetAngle() * 180 / b2_pi);
}

void BallObject::Destroy()
{
	m_Game->World.DestroyBody(m_Body);
}

void BallObject::ApplyForce(float forceAmount)
{
	m_Body->SetLinearVelocity(b2Vec2(forceAmount, 0.f));
}
