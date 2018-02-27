#ifndef SOUND_H_
#define SOUND_H_
#include"game.h"
#include<dsound.h>

//ライブラリリンク
#pragma comment(lib,"dsound.lib")
#pragma comment(lib,"winmm.lib")

namespace SoundNS
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

class Sound
{
private:
	const char* file;
	LPDIRECTSOUND8 lpDS = NULL;
	LPDIRECTSOUNDBUFFER lpPrimary = NULL;//プライマリサウンドバッファ
	LPDIRECTSOUNDBUFFER lpSecondary = NULL;//セカンダリサウンドバッファ
public:
	Sound();
	Sound(const char *file);
	void Play();
	void Stop();
	void Init(Game *main);
	bool CreatePrimaryBuffer(void);
	bool CreateSoundBuffer(LPDIRECTSOUNDBUFFER *dsb, const char *file);
	bool Exit(void);
};




#endif