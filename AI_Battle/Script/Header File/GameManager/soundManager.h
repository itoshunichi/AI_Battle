#ifndef SOUNDMANAGER_H_
#define SOUNDMANAGER_H_

#include"../Default/sound.h"
#include"../Default/game.h"
#include<vector>

/*ƒtƒ@ƒCƒ‹–¼*/
namespace SoundName
{
	const char TITLE_MUSIC[] = "Title.wav";
	const char MAIN_MUSIC[] = "gameMain.wav";
	const char GAMEOVER_MUSIC[] = "gameOver.wav";
	const char GAMECLEAR_MUSIC[] = "gameClear.wav";
	const char MOVE_SE[] = "move.wav";
	const char SELECT_SE[] = "select.wav";
	const char DEAD_SE[] = "dead.wav";
	const char CLEAR_SE[] = "clear.wav";
}

class SoundManager
{
private:
	//vector<Sound>*soundns;
	//BGM
	Sound titleBGM;
	Sound mainBGM;
	Sound gameOverBGM;
	Sound gameClearBGM;
	//SE
	Sound moveSE;
	Sound selectSE;
	Sound deadSE;
	Sound clearSE;

public:
	SoundManager();
	void Init(Game *game);
	Sound getTitleBGM(){ return titleBGM; }
	Sound getMainBGM(){ return mainBGM; }
	Sound getGameClearBGM(){ return gameClearBGM; }
	Sound getGameOverBGM(){ return gameOverBGM; }
	Sound getMoveSE(){ return moveSE; }
	Sound getSelectSE(){ return selectSE; }
	Sound getDeadSE(){ return deadSE; }
	Sound getClearSE(){ return clearSE; }
};

#endif