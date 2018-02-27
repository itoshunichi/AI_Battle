#include"../../Header File/GameManager/gameManager.h"

GameManager::GameManager()
{

}

void GameManager::initialize(Game *game, HWND hwnd)
{
	input = game->getInput();
	input->initialize(hwnd, false);
	imageManager = new ImageManager();
	imageManager->initialize(game->getGraphics());
	soundManager = new SoundManager();
	soundManager->Init(game);
	text = new TextDX();
	text->initialize(game->getGraphics(), 14, false, false, "Courier New");
	text->setFontColor(gameNS::FONT_COLOR);
	graphics = game->getGraphics();
}