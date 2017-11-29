#pragma once
#include <GameObject.h>
#include <SFML\Graphics.hpp>

/** Ball object class used to create a ball object with Box2d physics and to update and handle it. */
class BallObject : public GameObject
{
public:
	BallObject(Game* Game, float PosX, float PosY); ///< Ball object instance, on load create ball with specified game instance in specified position.

	virtual void Update(const float elapsed); ///< Update the ball.
	virtual void Destroy(); ///< Destroy the ball.

	void ApplyForce(float forceAmount); ///< Set the linear velocity of the ball to the specified amount.

	sf::CircleShape m_Shape; ///< A circle shape value.
};