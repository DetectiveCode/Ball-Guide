#pragma once
#include <Game.h>

/** Game state class, used to create a new game state. */
class GameState
{
public:
	Game* m_Game; ///< A dereferenced pointer of value game.
	
	virtual void Draw(const float elapsed) = 0; ///< Pure virtual function draw.
	virtual void Update(const float elapsed) = 0; ///< Pure virtual function update.
	virtual void HandleInput() = 0; ///< Pure virtual funcion handle input.

protected:
	float GetCenterTextureX(const std::string & texture); ///< Float function which returns the center X of the specified texture name in float.
	float GetCenterTextureY(const std::string & texture); ///< Float function which returns the center Y of the specified texture name in float.

	float GetTextureX(const std::string & texture); ///< Float function which returns the width (in float) of specified texture.
	float GetTextureY(const std::string & texture); ///< Float function which returns the height (in float) of specified texture.
};

