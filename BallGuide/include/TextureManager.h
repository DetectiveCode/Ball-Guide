#pragma once
#include <SFML/Graphics.hpp>
#include <map>

/** Texture manager class, allows you to load in texture and get references to managed textures. */
class TextureManager
{
public:
	void LoadTexture(const std::string& name, const std::string& filename); ///< Load the texture with the specified name and location.
	sf::Texture& GetRef(const std::string& texture); ///< Get reference to specified texture.

private:
	std::map<std::string, sf::Texture> m_Textures; ///< An array of map, with string as key and texture as type.
	std::string m_AssetPath = ".\\assets\\textures\\"; ///< A string with the location of the texture resource folder.
};