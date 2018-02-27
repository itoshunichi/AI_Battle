#include"../../Header File/Default/sound.h"

Sound::Sound()
{
	
}

Sound::Sound(const char *file)
{
	this->file = file;
}
//�Đ�
void Sound::Play()
{
	if (!CreatePrimaryBuffer())Exit();
	if (!CreateSoundBuffer(&lpSecondary, file))Exit();
	lpSecondary->Play(0, 0, 0);
}

//�I��
void Sound::Stop()
{
	lpSecondary->Stop();
	Exit();
}

//������
void Sound::Init(Game *main)
{
	HRESULT ret;

	//COM�̏�����
	CoInitialize(NULL);

	//DirectSound8���쐬
	ret = DirectSoundCreate8(NULL, &lpDS, NULL);
	if (FAILED(ret))
	{
		Exit();//�I��
		//return false;
	}

	//�������[�h
	ret = lpDS->SetCooperativeLevel(main->Hwnd(), DSSCL_EXCLUSIVE | DSSCL_PRIORITY);
	if (FAILED(ret))
	{
		Exit();//�I��
		//return false;
	}

	//return true;
};

//�v���C�}���T�E���h�o�b�t�@�̍쐬
bool Sound::CreatePrimaryBuffer(void)
{
	HRESULT ret;
	WAVEFORMATEX wf;

	//�v���C�}���T�E���h�o�b�t�@�̍쐬
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

	//�v���C�}���o�b�t�@�̃X�e�[�^�X������
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

//�T�E���h�o�b�t�@�̍쐬
bool Sound::CreateSoundBuffer(LPDIRECTSOUNDBUFFER *dsb, const char *file)
{
	HRESULT ret;
	MMCKINFO mSrcWaveFile;
	MMCKINFO mSrcWaveFmt;
	MMCKINFO mSrcWaveDate;
	LPWAVEFORMATEX wf;

	//WAV�t�@�C�������[�h
	HMMIO hSrc;
	hSrc = mmioOpenA((LPSTR)file, NULL, MMIO_ALLOCBUF | MMIO_READ | MMIO_COMPAT);
	if (!hSrc){ return false; }

	//WAVE�`�����N�`�F�b�N
	ZeroMemory(&mSrcWaveFile, sizeof(mSrcWaveFile));
	ret = mmioDescend(hSrc, &mSrcWaveFile, NULL, MMIO_FINDRIFF);
	if (mSrcWaveFile.fccType != mmioFOURCC('W', 'A', 'V', 'E'))
	{
		mmioClose(hSrc, 0);
		return false;
	}

	//'fmt'�`�����N�`�F�b�N
	ZeroMemory(&mSrcWaveFmt, sizeof(mSrcWaveFmt));
	ret = mmioDescend(hSrc, &mSrcWaveFmt, &mSrcWaveFile, MMIO_FINDCHUNK);
	if (mSrcWaveFmt.ckid != mmioFOURCC('f', 'm', 't', ' '))
	{
		mmioClose(hSrc, 0);
		return false;
	}

	//�w�b�_�T�C�Y�̌v�Z
	int iSrcHeaderSize = mSrcWaveFmt.cksize;
	if (iSrcHeaderSize < sizeof(WAVEFORMATEX))
		iSrcHeaderSize = sizeof(WAVEFORMATEX);

	//�w�b�_�������m��
	wf = (LPWAVEFORMATEX)malloc(iSrcHeaderSize);
	if (!wf){
		mmioClose(hSrc, 0);
		return false;
	}
	ZeroMemory(wf, iSrcHeaderSize);

	//WAVE�t�H�[�}�b�g�̃��[�h
	ret = mmioRead(hSrc, (char*)wf, mSrcWaveFmt.cksize);
	if (FAILED(ret))
	{
		free(wf);
		mmioClose(hSrc, 0);
		return false;
	}

	//fmt�`�����N�ɖ߂�
	mmioAscend(hSrc, &mSrcWaveFmt, 0);

	//data�`�����N��T��
	while (1)
	{
		//����
		ret = mmioDescend(hSrc, &mSrcWaveDate, &mSrcWaveFile, 0);
		if (FAILED(ret))
		{
			free(wf);
			mmioClose(hSrc, 0);
			return false;
		}
		if (mSrcWaveDate.ckid == mmioStringToFOURCCA("data", 0))
			break;
		//���̃`�����N��
		ret = mmioAscend(hSrc, &mSrcWaveDate, 0);
	}

	//�T�E���h�o�b�t�@�̍쐬
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

	//���b�N�J�n
	LPVOID pMem1, pMem2;
	DWORD dwSize1, dwSize2;
	ret = (*dsb)->Lock(0, mSrcWaveDate.cksize, &pMem1, &dwSize1, &pMem2, &dwSize2, 0);
	if (FAILED(ret))
	{
		free(wf);
		mmioClose(hSrc, 0);
		return false;
	}

	//�f�[�^��������
	mmioRead(hSrc, (char*)pMem1, dwSize1);
	mmioRead(hSrc, (char*)pMem2, dwSize2);

	//���b�N����
	(*dsb)->Unlock(pMem1, dwSize1, pMem2, dwSize2);

	//�w�b�_�p���������J��
	free(wf);

	//WAV�����
	mmioClose(hSrc, 0);

	return true;
}

//�I��
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

	//COM�̏I��
	CoUninitialize();

	return true;
}

