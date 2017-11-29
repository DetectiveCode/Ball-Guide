#pragma once
#include <stack>
#include <SFML/Graphics.hpp>
#include <TextureManager.h>
#include <SoundManager.h>
#include <FontManager.h>
#include <Box2D\Box2D.h>
#include <DebugDraw.h>

/** Nested game state class. */
class GameState;

/** Game class which handles the main game loop and game states. */
class Game
{
public:
	Game(); ///< Game state, on load.
	~Game(); ///< Game state, on destroy.

	void GameLoop(); ///< Game loop function for the main game loop.

	GameState* m_State(); ///< A derefenced variable of game state.
	std::stack<GameState*> m_StateStack; ///< A stack of type dereferenced variable game state.

	void PushState(GameState* state); ///< Push state function, allows to push the specified game state onto the stack.
	void PopState(); ///< Pop state function, removes the top most game state.
	void ChangeState(GameState* state); ///< Change state function, changes the current state to the specified state.
	GameState* PeekState(); ///< Peek state function, returns the top most state.

	sf::RenderWindow m_Window; ///< A render window variable which holds the window.
	sf::Sprite m_Background; ///< A sprite variable which holds the background image.

	b2World World = b2World(b2Vec2(0.f, 9.8f)); ///< A b2World variabl which holds an instance of Box2D b2World, the physics world.
	const float SCALE = 30.f; ///< A constant float variable which holds the meter to pixel scale ration.
	
	bool m_UpdateWorld = false; ///< A boolean which indicates if the physics world should be updated.
	bool m_AudioMute = false; ///< A boolean which indicates if the audio should be muted.
	sf::Music m_bgm; ///< A music variable which holds the background music.

	TextureManager m_TextureManager; ///< A texture manager variable which holds a new instance of texture manager.
	SoundManager m_SoundManager; ///< A sound manager variable which holds a new instance of sound manager.
	FontManager m_FontManager; ///< A font manager varaible which holds a new instance of font manager.

private:
	void LoadTextures(); ///< A load textures function which loads and creates all of the textures.
	void LoadSounds(); ///< A load sound fucntion which loads and creates all of the sounds.
	void LoadFonts(); ///< A load font function which loads all of the sounds.

	DebugDraw debugDraw = DebugDraw(m_Window); ///< A debug draw variable which creates a new instance of debug draw, allowing us to view debug information.
};