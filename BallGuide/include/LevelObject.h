#pragma once
#include <GoalObject.h>
#include <BallObject.h>
#include <PlankObject.h>

/** Level  object class, allows you to create a new level and easily update and check level information */
class LevelObject
{
public:
	LevelObject(Game* Game, float ballX, float ballY, float goalX, float goalY, int maxPlanks = 0, int maxShortPlanks = 0, int maxWindmills = 0); ///< Level object instance, on load create level with speicfied game instance and settings.

	void Update(const float elapsed); ///< Update the level object.
	bool CheckLoss(); ///< Check level winning condition.
	bool CheckWin(); ///< Check level losing condition.
	void Draw(); ///< Draw level.
	void Start(); ///< Start level.
	void Destroy(); ///< Destroy level.
	void Init(); ///< Initialize level.

	int m_MaxNormalPlanks = 0; ///< An integer variable holding the max number of normal planks.
	int m_MaxShortPlanks = 0; ///< An integer variable holding the max number of short planks.
	int m_MaxWindmillPlanks = 0; ///< An integer variable holding the max number of wind mill planks.

	float m_ballX; ///< A float variable holding the X position of the ball.
	float m_ballY; ///< A float variable holding the Y position of the ball.
	float m_goalX; ///< A float variable holding the X position of the goal.
	float m_goalY; ///< A float variable holding the Y position of the goal.

	Game* m_Game; ///< A derefenced pointer value of game.

	bool m_Init = false; ///< A bool indicating if the level has been initialized.

private:
	std::vector<PlankObject> m_PlankObjects; ///< An array of vector containing plank objects.
	std::vector<BallObject> m_BallObjects; ///< An array of vector containing ball objects.
	std::vector<GoalObject> m_GoalObjects; ///< An array of vector containing goal objects.
};