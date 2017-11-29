#pragma once
#include <SFML/Graphics.hpp>
#include <map>

/** Class to manage fonts, it allows you to load in fonts and get references to managed fonts. */
class FontManager
{
public:
	void LoadFont(const std::string& name, const std::string& filename); ///< Load the font with the specified name and file location.
	sf::Font& GetRef(const std::string& font); ///< Get reference to specified font.

private:
	std::map<std::string, sf::Font> m_Fonts; ///< An array of map, with string as key and font as type.
	std::string m_AssetPath = ".\\assets\\fonts\\"; ///< A string with the location of the font resource folder.
};