#include <TextureManager.h>

void TextureManager::LoadTexture(const std::string& name, const std::string& filename)
{
	sf::Texture newTexture;
	newTexture.loadFromFile(m_AssetPath + filename);

	m_Textures[name] = newTexture;
}

sf::Texture& TextureManager::GetRef(const std::string& texture)
{
	return m_Textures.at(texture);
}