#pragma once
#include <GameState.h>
#include <LevelObject.h>
#include <ButtonManager.h>

/** Game state playing class, which defines the playing state. */
class GameStatePlaying : public GameState
{
public:
	GameStatePlaying(Game* Game); ///< Game state playing, on load.

	virtual void Draw(const float elapsed); ///< Virtual draw function.
	virtual void Update(const float elapsed); ///< Virtual update function.
	virtual void HandleInput(); ///< Virtual handle input function.

private:
	void LoadPlaceHolders(); ///< A function to load interface place holders.
	void LoadLevels(); ///< A function to create all of the levels.
	void DrawText(); ///< A function to draw the interface text.
	void LoadButtons(); ///< A function to create all of the buttons.
	void DestroyPlanks(); ///< A function to destroy all of the planks.

	sf::View m_GameView; ///< A view variable which hold the state view.

	std::vector<PlankObject> m_PlankObjects; ///< A vector array which holds plank objects.
	std::vector<LevelObject> m_LoadedLevels; ///< A vector array which holds level objects.
	
	sf::Sprite m_ShapePanel; ///< A sprite variable which holds the main interface GUI panel.
	sf::Sprite m_PausePanel; ///< A sprite variable which holds the different game condition interface GUI panel.

	sf::RectangleShape m_NormalPlank; ///< A rectangle shape variable which holds the normal plank shape.
	sf::RectangleShape m_ShortPlank; ///< A rectangle shape variable which holds the short plank shape.
	sf::RectangleShape m_WindmillPlank; ///< A rectangle shape variable which holds the windmill plank shape.
	sf::CircleShape m_WindmillJoint; ///< A circle shape which holds the windmill plank joint.
	sf::Text m_InterfaceText; ///< A text variable which is used to draw the GUI text to the screen.

	int m_Level = 0; ///< An integer variable which holds the current game level.
	int m_Lives = 3; ///< An integer variable which holds the player lives.
	int selectedObject = 0; ///< An integer variable which holds the currently selected game object.
	int totalNormalPlanks = 0; ///< An integer variable which holds the total amount of used normal planks.
	int totalShortPlanks = 0; ///< An integer variable which holds the total amount of used short planks.
	int totalWindmills = 0; ///< An integer variable which holds the total amount of used windmill planks.
	
	bool m_Pause = false; ///< A boolean variable which indicates if the game has been paused.
	bool m_Started = false; ///< A boolean variable which indicates if the game has been started.
	bool m_Victory = false; ///< A boolean variable which indicates if the level has been completed.
	bool m_Defeat = false; ///< A boolean varialbe which indicates if the player has failed to complete the level.
	bool m_Fini = false; ///< A boolean variable which indicates if the player has finished the game.

	ButtonManager m_GameButtons = ButtonManager(m_Game); ///< A button manager variable used to create a new instance of game buttons
	ButtonManager m_PauseButtons = ButtonManager(m_Game); ///< A button manager variable used to create a new instance of pause buttons
	ButtonManager m_VictoryButtons = ButtonManager(m_Game); ///< A button manager variable used to create a new instance of victory buttons
	ButtonManager m_DefeatButtons = ButtonManager(m_Game); ///< A button manager variable used to create a new instance of defeat buttons
};