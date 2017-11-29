#pragma once
#include <Game.h>
#include <Box2D\Box2D.h>

/** A game object class, the base class for game objects, with virtual updates and destroys as well as Box2d body creation. */
class GameObject
{
public:
	GameObject(); ///< Game object instane, on load.
	
	virtual void Update(const float elapsed) = 0; ///< A pure virtual update function.
	virtual void Destroy() = 0; ///< A pure virtual destroy function.

	b2Body* GetBody(); ///< Function to get retrieve m_Body variable.
	
	bool m_MoveShape = false; ///< A boolean value indicating if the shape is currently able to be moved.

protected:
	Game* m_Game; ///< A dereferened pointer value of game.
	b2Body* m_Body; ///< A derefenced pointer value of b2Body.
	b2Body* m_Body2; ///< A derefenced pointer value of b2Body.

	sf::Vector2f m_Position; ///< A float vector, which holds the game object posiiton.
	sf::Vector2f m_Size; ///< A float vector, which holds the game object size.

	void CreateBody(b2PolygonShape & Shape); ///< A function to create a body, with the address of the specified polygon shape.
	void CreateBody(b2CircleShape & Shape); ///< A function to create a body, with the address of the specified circle shape.
	void CreateBody(b2PolygonShape & polyShape, b2CircleShape & circleShape); ///< A function to create a body, with the address of the specified polygon shape and circle shape.
};