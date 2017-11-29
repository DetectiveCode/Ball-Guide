#pragma once
#include <SFML/Graphics.hpp>
#include <GameState.h>
#include <ButtonManager.h>

/** Game state credit class, which defines the credit screen state. */
class GameStateCredits : public GameState
{
public:
	GameStateCredits(Game* Game); ///< Game state credit instance, on load.

	virtual void Draw(const float elapsed); ///< Virtual draw function..
	virtual void Update(const float elapsed); ///< Virtual update function.
	virtual void HandleInput(); ///< Virtual handle input function.

private:
	sf::View m_View; ///< A view variable containing the state view.
	sf::Vector2f m_MousePos; ///< A float vector variable containing the mouse position.
	sf::Sprite m_Title; ///< A sprite variable containing the logo sprite.
	sf::Sprite m_Credits; ///< A sprite variable containing the credit sprite.

	ButtonManager m_ButtonManager = ButtonManager(m_Game); ///< Button manager variable which holds the button manager instance for this state.
};