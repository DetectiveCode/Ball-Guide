#include <FontManager.h>

void FontManager::LoadFont(const std::string& name, const std::string& filename)
{
	sf::Font newFont;
	newFont.loadFromFile(m_AssetPath + filename);

	m_Fonts[name] = newFont;
}

sf::Font& FontManager::GetRef(const std::string& font)
{
	return m_Fonts.at(font);
}