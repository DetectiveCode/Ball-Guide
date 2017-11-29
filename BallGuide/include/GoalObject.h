#pragma once
#include <GameObject.h>
#include <PlankObject.h>

/** Goal object class, to create a goal object, update and handle it. */
class GoalObject : public GameObject
{
public:
	GoalObject(Game* Game, float PosX, float PosY); ///< Goal object instance, on load create ball with specified game instance in specified position.

	virtual void Update(const float elapsed); ///< Update the goal object.
	virtual void Destroy(); ///< Destroy the goal object.
	void Draw(); ///< Draw the goal object.

	std::vector<PlankObject> m_PlankObjects; ///< An array of vector, containing plank objects.
};