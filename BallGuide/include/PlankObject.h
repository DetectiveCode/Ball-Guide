#pragma once
#include <SFML\Graphics.hpp>
#include <GameObject.h>

/** Plank object class, allows you to create a new plank object and easily managed and update it. */
class PlankObject : public GameObject
{
public:
	PlankObject(Game* Game, int plankType = 0); ///< Plank object instanc, on load create plank object with specified game instance and plank type.

	virtual void Update(const float elapsed); ///< Update the plank object.
	virtual void Destroy(); ///< Destroy the plank object.
	
	sf::RectangleShape m_Shape; ///< A rectangle shape variable holding the shape information.
	sf::CircleShape m_CircleShape; ///< A circle shape variable holding the shape information.
	int m_PlankType; ///< An integer variable holding the plank type.
};