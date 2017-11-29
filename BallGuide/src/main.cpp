#include <Game.h>
#include <GameStateMenu.h>

void main()
{
	Game game;

	game.PushState(new GameStateMenu(&game));
	game.GameLoop();
}