#include <Game.h>
#include <GameState.h>
#include <SFML\System.hpp>

Game::Game()
{
	LoadTextures();
	LoadSounds();
	LoadFonts();

	unsigned int windowWidth = 961;
	unsigned int windowHeight = 640;

	m_Window.create(sf::VideoMode(windowWidth, windowHeight), "Ball Guide", sf::Style::Titlebar | sf::Style::Close, sf::ContextSettings(24, 8, 16));
	m_Window.setFramerateLimit(60);

	int centerPosX = sf::VideoMode().getDesktopMode().width / 2 - windowWidth / 2;
	int centerPosY = sf::VideoMode().getDesktopMode().height / 2 - windowHeight / 2 - 25;

	m_Window.setPosition(sf::Vector2i(centerPosX, centerPosY));

	m_Background.setTexture(m_TextureManager.GetRef("bg"));

	m_bgm.openFromFile(".\\assets\\audio\\jazzcomedy.ogg");
	m_bgm.setLoop(true);
	m_bgm.setVolume(15);
	m_bgm.play();

	/* Initialize SFML Debug Draw */
#if _DEBUG
	World.SetDebugDraw(&debugDraw);
	debugDraw.SetFlags(b2Draw::e_shapeBit); //Only draw shapes
	debugDraw.AppendFlags(b2Draw::e_aabbBit);
	debugDraw.AppendFlags(b2Draw::e_centerOfMassBit);
	debugDraw.AppendFlags(b2Draw::e_jointBit);
	debugDraw.AppendFlags(b2Draw::e_pairBit);
#endif
}

Game::~Game()
{
	while (!m_StateStack.empty())
	{
		m_StateStack.pop();
	}
}

void Game::GameLoop()
{
	sf::Clock clock;

	while (m_Window.isOpen())
	{
		if (m_UpdateWorld)
		{
			World.Step(1 / 60.f, 8, 3);
		}

		if (m_AudioMute || !m_Window.hasFocus())
		{
			m_bgm.pause();
		}
		else
		{
			if (m_bgm.getStatus() == m_bgm.Paused)
			{
				m_bgm.play();
			}
		}

		float elapsedTime = clock.restart().asSeconds();

		if (m_Background.getPosition().x <= -m_Background.getGlobalBounds().width / 2 + 10)
		{
			m_Background.setPosition(sf::Vector2f(0, m_Background.getPosition().y));
		}

		m_Background.setPosition(sf::Vector2f(m_Background.getPosition().x - 0.4f , m_Background.getPosition().y));

		if (PeekState() == nullptr) continue;

		PeekState()->HandleInput();
		PeekState()->Update(elapsedTime);
		m_Window.clear(sf::Color::Black);
		PeekState()->Draw(elapsedTime);

#if _DEBUG
		World.DrawDebugData();
#endif
		m_Window.display();
	}
}

GameState* Game::m_State()
{
	if (m_StateStack.empty())
	{
		return nullptr;
	}
	else
	{
		m_StateStack.top();
	}
}

void Game::PushState(GameState* state)
{
	m_StateStack.push(state);
	return;
}

void Game::PopState()
{
	m_StateStack.pop();
	return;
}

void Game::ChangeState(GameState* state)
{
	if (!m_StateStack.empty())
	{
		PopState();
	}

	PushState(state);
}

GameState* Game::PeekState()
{
	if (m_StateStack.empty())
	{
		return nullptr;
	}

	return m_StateStack.top();
}

void Game::LoadTextures()
{
	m_TextureManager.LoadTexture("bg", "bg.png");
	m_TextureManager.LoadTexture("title", "title.png");

	m_TextureManager.LoadTexture("play0", "play0.png");
	m_TextureManager.LoadTexture("play1", "play1.png");

	m_TextureManager.LoadTexture("credits0", "credits0.png");
	m_TextureManager.LoadTexture("credits1", "credits1.png");

	m_TextureManager.LoadTexture("exit0", "exit0.png");
	m_TextureManager.LoadTexture("exit1", "exit1.png");

	m_TextureManager.LoadTexture("back0", "back0.png");
	m_TextureManager.LoadTexture("back1", "back1.png");

	m_TextureManager.LoadTexture("resume0", "resume0.png");
	m_TextureManager.LoadTexture("resume1", "resume1.png");

	m_TextureManager.LoadTexture("menu0", "menu0.png");
	m_TextureManager.LoadTexture("menu1", "menu1.png");

	m_TextureManager.LoadTexture("continue0", "continue0.png");
	m_TextureManager.LoadTexture("continue1", "continue1.png");

	m_TextureManager.LoadTexture("restart0", "restart0.png");
	m_TextureManager.LoadTexture("restart1", "restart1.png");

	m_TextureManager.LoadTexture("start0", "start0.png");
	m_TextureManager.LoadTexture("start1", "start1.png");

	m_TextureManager.LoadTexture("giveup0", "giveup0.png");
	m_TextureManager.LoadTexture("giveup1", "giveup1.png");

	m_TextureManager.LoadTexture("credits", "credits.png");
	m_TextureManager.LoadTexture("panel", "panel.png");
	m_TextureManager.LoadTexture("pausepanel", "pausepanel.png");
}

void Game::LoadSounds()
{
	m_SoundManager.LoadSounds("rollover", "rollover.ogg", 5);
	m_SoundManager.LoadSounds("click", "click.ogg", 20);
}

void Game::LoadFonts()
{
	m_FontManager.LoadFont("franks", "franks.ttf");
}