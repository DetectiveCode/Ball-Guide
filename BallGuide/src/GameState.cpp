#include <GameState.h>

float GameState::GetCenterTextureX(const std::string & texture)
{
	return (float)((m_Game->m_Window.getSize().x / 2) - (m_Game->m_TextureManager.GetRef(texture).getSize().x / 2));
}

float GameState::GetCenterTextureY(const std::string & texture)
{
	return (float)((m_Game->m_Window.getSize().y / 2) - (m_Game->m_TextureManager.GetRef(texture).getSize().y / 2));
}

float GameState::GetTextureX(const std::string & texture)
{
	return (float)m_Game->m_TextureManager.GetRef(texture).getSize().x;
}

float GameState::GetTextureY(const std::string & texture)
{
	return (float)m_Game->m_TextureManager.GetRef(texture).getSize().y;
}
