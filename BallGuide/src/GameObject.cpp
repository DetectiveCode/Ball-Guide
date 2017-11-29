#include <GameObject.h>

GameObject::GameObject()
{
}

void GameObject::CreateBody(b2PolygonShape & Shape)
{
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(m_Position.x / m_Game->SCALE, m_Position.y / m_Game->SCALE);
	BodyDef.type = b2_staticBody;

	m_Body = m_Game->World.CreateBody(&BodyDef);

	Shape.SetAsBox((m_Size.x / 2) / m_Game->SCALE, (m_Size.y / 2) / m_Game->SCALE); //Half Extents of the Shape

	b2FixtureDef FixtureDef;
	FixtureDef.density = 0.f;
	FixtureDef.friction = 1.0f;
	FixtureDef.filter.categoryBits = 0x0002; //i am
	FixtureDef.filter.maskBits = 0x0004; //i collide with
	FixtureDef.shape = &Shape;

	m_Body->CreateFixture(&FixtureDef);
}

void GameObject::CreateBody(b2CircleShape & Shape)
{
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(m_Position.x / m_Game->SCALE, m_Position.y / m_Game->SCALE);
	BodyDef.type = b2_dynamicBody;

	m_Body = m_Game->World.CreateBody(&BodyDef);

	Shape.m_p.Set(0, 0); //Position relative to the body position
	Shape.m_radius = (m_Size.x) / m_Game->SCALE;

	b2FixtureDef FixtureDef;
	FixtureDef.density = 1.f;
	FixtureDef.friction = 0.7f;
	FixtureDef.restitution = 0.6f;
	FixtureDef.filter.categoryBits = 0x0004; //i am
	FixtureDef.filter.maskBits = 0x0002; //i collide with
	FixtureDef.shape = &Shape;

	m_Body->CreateFixture(&FixtureDef);
	//m_Body->ApplyForce(b2Vec2(3 * m_Game->SCALE, 0), m_Body->GetWorldCenter(), true);
}

void GameObject::CreateBody(b2PolygonShape & polyShape, b2CircleShape & circleShape)
{
	b2BodyDef BodyDef;
	
	b2FixtureDef FixtureDef;
	FixtureDef.density = 0.f;
	FixtureDef.friction = 1.0f;
	FixtureDef.filter.categoryBits = 0x0002; //i am
	FixtureDef.filter.maskBits = 0x0004; //i collide with

	BodyDef.type = b2_dynamicBody;
	//BodyDef.angularVelocity = 1.f;
	polyShape.SetAsBox((m_Size.x / 2) / m_Game->SCALE, (m_Size.y / 2) / m_Game->SCALE);
	BodyDef.position = b2Vec2(m_Position.x / m_Game->SCALE, m_Position.y / m_Game->SCALE);
	FixtureDef.shape = &polyShape;
	m_Body = m_Game->World.CreateBody(&BodyDef);
	m_Body->CreateFixture(&FixtureDef);
	m_Body->SetAngularVelocity(0.5f);
	

	BodyDef.type = b2_staticBody;
	BodyDef.angularVelocity = 0.f;
	circleShape.m_p.Set(0, 0);
	circleShape.m_radius = (m_Size.y * 0.4f) / m_Game->SCALE;
	BodyDef.position = b2Vec2(m_Position.x / m_Game->SCALE, m_Position.y / m_Game->SCALE);
	FixtureDef.shape = &circleShape;
	m_Body2 = m_Game->World.CreateBody(&BodyDef);
	m_Body2->CreateFixture(&FixtureDef);

	b2Joint* m_Joint;
	b2RevoluteJointDef revoluteJointDef;

	revoluteJointDef.Initialize(m_Body, m_Body2, m_Body2->GetWorldCenter());

	//revoluteJointDef.bodyA = m_Body;
	//revoluteJointDef.bodyB = m_Body2;
	//revoluteJointDef.collideConnected = false;
	//revoluteJointDef.localAnchorA.Set(0, 0);//the top right corner of the box
	//revoluteJointDef.localAnchorB.Set(0, 0);//center of the circle

	//revoluteJointDef.enableLimit = true;
	//revoluteJointDef.lowerAngle = -45 * 180 / b2_pi;
	//revoluteJointDef.upperAngle = 45 * 180 / b2_pi;

	//revoluteJointDef.enableMotor = true;
	//revoluteJointDef.maxMotorTorque = 5;
	//revoluteJointDef.motorSpeed = 90 * 180 / b2_pi;

	m_Joint = (b2RevoluteJoint*)m_Game->World.CreateJoint(&revoluteJointDef);
}

b2Body * GameObject::GetBody()
{
	return m_Body;
}
