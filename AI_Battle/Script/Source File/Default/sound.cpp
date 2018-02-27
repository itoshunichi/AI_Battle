#include"../../Header File/Default/sound.h"

Sound::Sound()
{
	
}

Sound::Sound(const char *file)
{
	this->file = file;
}
//再生
void Sound::Play()
{
	if (!CreatePrimaryBuffer())Exit();
	if (!CreateSoundBuffer(&lpSecondary, file))Exit();
	lpSecondary->Play(0, 0, 0);
}

//終了
void Sound::Stop()
{
	lpSecondary->Stop();
	Exit();
}

//初期化
void Sound::Init(Game *main)
{
	HRESULT ret;

	//COMの初期化
	CoInitialize(NULL);

	//DirectSound8を作成
	ret = DirectSoundCreate8(NULL, &lpDS, NULL);
	if (FAILED(ret))
	{
		Exit();//終了
		//return false;
	}

	//協調モード
	ret = lpDS->SetCooperativeLevel(main->Hwnd(), DSSCL_EXCLUSIVE | DSSCL_PRIORITY);
	if (FAILED(ret))
	{
		Exit();//終了
		//return false;
	}

	//return true;
};

//プライマリサウンドバッファの作成
bool Sound::CreatePrimaryBuffer(void)
{
	HRESULT ret;
	WAVEFORMATEX wf;

	//プライマリサウンドバッファの作成
	DSBUFFERDESC dsdesc;
	ZeroMemory(&dsdesc, sizeof(DSBUFFERDESC));
	dsdesc.dwSize = sizeof(DSBUFFERDESC);
	dsdesc.dwFlags = DSBCAPS_PRIMARYBUFFER;
	dsdesc.dwBufferBytes = 0;
	dsdesc.lpwfxFormat = NULL;
	ret = lpDS->CreateSoundBuffer(&dsdesc, &lpPrimary, NULL);
	if (FAILED(ret))
	{
		return false;
	}

	//プライマリバッファのステータスを決定
	wf.cbSize = sizeof(WAVEFORMATEX);
	wf.wFormatTag = WAVE_FORMAT_PCM;
	wf.nChannels = 2;
	wf.nSamplesPerSec = 44100;
	wf.wBitsPerSample = 16;
	wf.nBlockAlign = wf.nChannels * wf.wBitsPerSample / 8;
	wf.nAvgBytesPerSec = wf.nSamplesPerSec * wf.nBlockAlign;
	ret = lpPrimary->SetFormat(&wf);
	if (FAILED(ret))
	{
		return false;
	}

	return true;
}

//サウンドバッファの作成
bool Sound::CreateSoundBuffer(LPDIRECTSOUNDBUFFER *dsb, const char *file)
{
	HRESULT ret;
	MMCKINFO mSrcWaveFile;
	MMCKINFO mSrcWaveFmt;
	MMCKINFO mSrcWaveDate;
	LPWAVEFORMATEX wf;

	//WAVファイルをロード
	HMMIO hSrc;
	hSrc = mmioOpenA((LPSTR)file, NULL, MMIO_ALLOCBUF | MMIO_READ | MMIO_COMPAT);
	if (!hSrc){ return false; }

	//WAVEチャンクチェック
	ZeroMemory(&mSrcWaveFile, sizeof(mSrcWaveFile));
	ret = mmioDescend(hSrc, &mSrcWaveFile, NULL, MMIO_FINDRIFF);
	if (mSrcWaveFile.fccType != mmioFOURCC('W', 'A', 'V', 'E'))
	{
		mmioClose(hSrc, 0);
		return false;
	}

	//'fmt'チャンクチェック
	ZeroMemory(&mSrcWaveFmt, sizeof(mSrcWaveFmt));
	ret = mmioDescend(hSrc, &mSrcWaveFmt, &mSrcWaveFile, MMIO_FINDCHUNK);
	if (mSrcWaveFmt.ckid != mmioFOURCC('f', 'm', 't', ' '))
	{
		mmioClose(hSrc, 0);
		return false;
	}

	//ヘッダサイズの計算
	int iSrcHeaderSize = mSrcWaveFmt.cksize;
	if (iSrcHeaderSize < sizeof(WAVEFORMATEX))
		iSrcHeaderSize = sizeof(WAVEFORMATEX);

	//ヘッダメモリ確保
	wf = (LPWAVEFORMATEX)malloc(iSrcHeaderSize);
	if (!wf){
		mmioClose(hSrc, 0);
		return false;
	}
	ZeroMemory(wf, iSrcHeaderSize);

	//WAVEフォーマットのロード
	ret = mmioRead(hSrc, (char*)wf, mSrcWaveFmt.cksize);
	if (FAILED(ret))
	{
		free(wf);
		mmioClose(hSrc, 0);
		return false;
	}

	//fmtチャンクに戻る
	mmioAscend(hSrc, &mSrcWaveFmt, 0);

	//dataチャンクを探す
	while (1)
	{
		//検索
		ret = mmioDescend(hSrc, &mSrcWaveDate, &mSrcWaveFile, 0);
		if (FAILED(ret))
		{
			free(wf);
			mmioClose(hSrc, 0);
			return false;
		}
		if (mSrcWaveDate.ckid == mmioStringToFOURCCA("data", 0))
			break;
		//次のチャンクへ
		ret = mmioAscend(hSrc, &mSrcWaveDate, 0);
	}

	//サウンドバッファの作成
	DSBUFFERDESC dsdesc;
	ZeroMemory(&dsdesc, sizeof(DSBUFFERDESC));
	dsdesc.dwSize = sizeof(DSBUFFERDESC);
	dsdesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_STATIC | DSBCAPS_LOCDEFER;
	dsdesc.dwBufferBytes = mSrcWaveDate.cksize;
	dsdesc.lpwfxFormat = wf;
	dsdesc.guid3DAlgorithm = DS3DALG_DEFAULT;
	ret = lpDS->CreateSoundBuffer(&dsdesc, dsb, NULL);
	if (FAILED(ret))
	{
		free(wf);
		mmioClose(hSrc, 0);
		return false;
	}

	//ロック開始
	LPVOID pMem1, pMem2;
	DWORD dwSize1, dwSize2;
	ret = (*dsb)->Lock(0, mSrcWaveDate.cksize, &pMem1, &dwSize1, &pMem2, &dwSize2, 0);
	if (FAILED(ret))
	{
		free(wf);
		mmioClose(hSrc, 0);
		return false;
	}

	//データ書き込み
	mmioRead(hSrc, (char*)pMem1, dwSize1);
	mmioRead(hSrc, (char*)pMem2, dwSize2);

	//ロック解除
	(*dsb)->Unlock(pMem1, dwSize1, pMem2, dwSize2);

	//ヘッダ用メモリを開放
	free(wf);

	//WAVを閉じる
	mmioClose(hSrc, 0);

	return true;
}

//終了
bool Sound::Exit(void)
{
	if (lpSecondary)
	{
		lpSecondary->Release();
		lpSecondary = NULL;
	}

	if (lpPrimary)
	{
		lpPrimary->Release();
		lpPrimary = NULL;
	}

	if (lpDS)
	{
		lpDS->Release();
		lpDS = NULL;
	}

	//COMの終了
	CoUninitialize();

	return true;
}

