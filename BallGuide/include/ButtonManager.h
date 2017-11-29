#pragma once
#include <Game.h>
#include <ButtonObject.h>

/** Class to manage buttons, allows you to add, draw and update buttons easily. */
class ButtonManager
{
public:
	ButtonManager(Game* Game); ///< Button manager instance, on load.

	void LoadButton(const std::string & buttonId, const std::string & normalTexture, const std::string & hoverTexture, const std::string & rollSound, float positionX, float positionY); ///< Load button and start handling it.
	void Update(); ///< Update the button.
	void Draw(); ///< Draw the button.

	bool ButtonEvent(const std::string & buttonId); ///< Check if a button with the specified Id was pressed.
	Game* m_Game; ///< Dereferenced pointer value of Game.

private:
	std::vector<ButtonObject> m_LoadedButtons; ///< An array of vector containing button objects.
};