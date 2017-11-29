#pragma once
#include <SFML/Graphics.hpp>
#include <Game.h>

/** A button object class, allows you to set button information, update and draw button. */
class ButtonObject
{
public:
	ButtonObject(Game* Game); ///< Button object instance, on load.

	void Update(); ///< Update button object.
	void Draw(); ///< Draw button object.

	sf::Sprite m_ButtonSprite; ///< A sprite variable. containing button sprite.
	std::string m_ButtonId; ///< A string variable, containing button Id.
	std::string m_NormalTexture; ///< A string variable, containing the name of the normal button texture.
	std::string m_HoverTexture; ///< A string variable, containing the name of the hovered button texture.
	std::string m_RollSound; ///< A string variable, containing the name of the button roll sound.

	Game* m_Game; ///< Dereferenced pointer value of game.

	bool m_Hovered; ///< A boolean value indicating if the button has been hovered.
};