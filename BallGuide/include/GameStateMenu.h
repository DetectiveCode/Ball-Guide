#pragma once
#include <SFML/Graphics.hpp>
#include <GameState.h>
#include <ButtonManager.h>

/** Game state menu class, which defines the main menu state. */
class GameStateMenu : public GameState
{
public:
	GameStateMenu(Game* Game); ///< Game state menu instance, on load.

	virtual void Draw(const float elapsed); ///< Virtual draw function.
	virtual void Update(const float elapsed); ///< Virtual update function.
	virtual void HandleInput(); ///< Virtual handle input function.

private:
	void LoadButtons(); ///< Load button function, used to create and load buttons into button manager container.

	sf::View m_View; ///< A view variable containing the state view.
	sf::Sprite m_Title; ///< a sprite variable containing the game logo.

	ButtonManager m_ButtonManager = ButtonManager(m_Game); ///< Button manager variable which holds the button manager instance for this state.
};