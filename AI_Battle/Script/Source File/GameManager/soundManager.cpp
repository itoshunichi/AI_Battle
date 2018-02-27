#include"../../Header File/GameManager/soundManager.h"

SoundManager::SoundManager()
{
	titleBGM = Sound(SoundName::TITLE_MUSIC);
	mainBGM = Sound(SoundName::MAIN_MUSIC);
	gameOverBGM = Sound(SoundName::GAMEOVER_MUSIC);
	gameClearBGM = Sound(SoundName::GAMECLEAR_MUSIC);
	moveSE = Sound(SoundName::MOVE_SE);
	selectSE = Sound(SoundName::SELECT_SE);
	deadSE = Sound(SoundName::DEAD_SE);
	clearSE = Sound(SoundName::CLEAR_SE);}

void SoundManager::Init(Game *game)
{
	titleBGM.Init(game);
	mainBGM.Init(game);
	gameOverBGM.Init(game);
	gameClearBGM.Init(game);
	moveSE.Init(game);
	selectSE.Init(game);
	deadSE.Init(game);
	clearSE.Init(game);
}