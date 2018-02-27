#include"../../Header File/Default/graphics.h"

//�R���X�g���N�^
Graphics::Graphics()
{
	direct3d = NULL;
	device3d = NULL;
	sprite = NULL;
	fullscreen = false;
	width = GAME_WIDTH;
	height = GAME_HEIGHT;
	backColor = graphicsNS::BACK_COLOR;
}

//�f�X�g���N�^
Graphics::~Graphics()
{
	releaseAll();
}

//���ׂĂ����
void Graphics::releaseAll()
{
	SAFE_RELEASE(sprite)
	SAFE_RELEASE(device3d);
	SAFE_RELEASE(direct3d);
}

//DirectX�O���t�B�b�N�X��������
//�G���[����GameErro���X���[
void Graphics::initialize(HWND hw, int w, int h, bool full)
{
	hwnd = hw;
	width = w;
	height = h;
	fullscreen = full;
	//Direct3D��������
	direct3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (direct3d == NULL)
		throw(GameError(gameErrorNS::FATAL_ERROR,
		"Error initializing Direct3D"));

	initD3Dpp(); //D3D�v���[���e�[�V�����p�����[�^��������

	if (fullscreen)   //�S��ʕ\�����[�h�̑Ή�
	{
		if (isAdapterCompatible())//�A�_�v�^�[���Ή����Ă��邩�ǂ���
		{
			//�Ή����Ă��郊�t���b�V�����[�g��ݒ�
			d3dpp.FullScreen_RefreshRateInHz = pMode.RefreshRate;
		}
		else
		{
			throw(GameError(gameErrorNS::FATAL_ERROR,
				"The graphics device does not support the"\
				"specifiled resolution and/or fomat."));
		}
		
	}

	//�O���t�B�b�N�X�J�[�h���n�[�h�E�F�A�e�N�X�`�������O�ƃ��C�e�B���O�A
	//���_�V�F�[�_�[���T�|�[�g���Ă��邩�ǂ����𔻒�
	D3DCAPS9 caps;
	DWORD behavior;
	result = direct3d->GetDeviceCaps(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL, &caps);
	//�f�o�C�X��HW�e�N�X�`�������O�ƃ��C�e�B���O���T�|�[�g���Ă��Ȃ��ꍇ
	//�܂���1.1���_�V�F�[�_���n�[�h�E�F�A�ŃT�|�[�g���Ă��Ȃ��ꍇ
	//�\�t�g�E�F�A���_�����ɐ؂�ւ��܂�
	if ((caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) == 0 ||
		caps.VertexShaderVersion < D3DVS_VERSION(1, 1))
		//�\�t�g�E�F�A�݂̂̏������g�p
		behavior = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	else
		//�n�[�h�E�F�A�݂̂̏������g�p
		behavior = D3DCREATE_HARDWARE_VERTEXPROCESSING;

	//Direct3D�f�o�C�X���쐬
	result = direct3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hwnd,
		//�ꕔ�̃V�X�e���ł�Direct3D9(ERROR)ASSERTION FAILED!)
		//���񍐂���܂���,���ۂɂ̓G���[�ł͂���܂���
		behavior,
		//�O���t�B�b�N�X�J�[�h���n�[�h�E�F�A���_�������T�|�[�g���Ȃ��ꍇ�͋@�\���Ȃ�
		//D3DCREATE_HARDWRE_VERTEXPROCESSING
		&d3dpp,
		&device3d);

	if (FAILED(result))
		throw(GameError(gameErrorNS::FATAL_ERROR,
		"Error creating Direct3D device"));

	result = D3DXCreateSprite(device3d, &sprite);
	if (FAILED(result))
		throw(GameError(gameErrorNS::FATAL_ERROR,
		"Error creating Direct3D sprite"));
}

//D3D�v���[���e�[�V�����p�����[�^��������
void Graphics::initD3Dpp()
{
	try
	{
		ZeroMemory(&d3dpp, sizeof(d3dpp)); //�\���̂�0��ݒ�
		//�K�v�ȃp�����[�^��ݒ�
		d3dpp.BackBufferWidth = width;
		d3dpp.BackBufferHeight = height;

		if (fullscreen)//�S��ʕ\���̏ꍇ
			d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;//24�r�b�g�J���[
		else
			d3dpp.BackBufferFormat = D3DFMT_UNKNOWN; //�f�X�N�g�b�v�ݒ���g�p

		d3dpp.BackBufferCount = 1;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.hDeviceWindow = hwnd;
		d3dpp.Windowed = (!fullscreen);
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;


	}
	catch (...)
	{
		throw(GameError(gameErrorNS::FATAL_ERROR,
			"Erro initializing D3D presentation parameters"));
	}
}

//�o�b�N�o�b�t�@��\��
HRESULT Graphics::showBackbuffer()
{
	result = E_FAIL; //���s���f�t�H���g�Ƃ��A�������ɒu������
	//�i���̊֐��́A��̃o�[�W�����ł͈ړ����܂��j
	//�o�b�N�o�b�t�@�����C���O���[���ɃN���A
	result = device3d->Present(NULL, NULL, NULL, NULL);
	return result;
}

//�A�_�v�^�[���`�F�b�N���āAd3dpp�Ŏw�肳�ꂽBackBuffer�̍����A��
//���t���b�V�����[�g�ɑΉ����Ă��邩�ǂ������m�F���܂��B
//�Ή�������̂����������ꍇ�́ApMode�\���̂ɁA
//�Ή����Ă��郂�[�h�̃t�H�[�}�b�g��ݒ肵�܂��B
//���s�O�Fd3dpp������������Ă���
//���s��F�Ή����Ă��郂�[�h��������ApMode�\���̂Ƀf�[�^��
//�ݒ肳�ꂽ�ꍇtrue��߂��܂��B
//�Ή����Ă��郂�[�h��������Ȃ������ꍇ�Afalse��߂��܂�
bool Graphics::isAdapterCompatible()
{
	UINT modes = direct3d->GetAdapterModeCount(
		D3DADAPTER_DEFAULT, d3dpp.BackBufferFormat);
	for (UINT i = 0; i < modes; i++)
	{
		result = direct3d->EnumAdapterModes(
			D3DADAPTER_DEFAULT, d3dpp.BackBufferFormat, i, &pMode);
		if (pMode.Height == d3dpp.BackBufferHeight&&
			pMode.Width == d3dpp.BackBufferWidth&&
			pMode.RefreshRate >= d3dpp.FullScreen_RefreshRateInHz)
			return true;
	}
	
	return false;
}

//�f�o�C�X���������Ă��Ȃ������`�F�b�N
HRESULT Graphics::getDeviceState()
{
	result = E_FAIL; //���s���f�t�H���g�Ƃ��A�������ɒu������
	if (device3d == NULL)return result;

		result = device3d->TestCooperativeLevel();
		return result;
	
}

//�O���t�B�b�N�X�f�o�C�X�����Z�b�g
HRESULT Graphics::reset()
{
	result = E_FAIL; //���s���f�t�H���g�Ƃ��A�������ɒu������
	initD3Dpp();       //D3D�v���[���e�[�V�����p�����[�^��������
	sprite->OnLostDevice();
	//�O���t�B�b�N�X�f�o�C�X�̃��Z�b�g�����݂�
	result = device3d->Reset(&d3dpp);
	//�v���~�e�B�u�̃A���t�@�u�����h�p�̍\�z
	device3d->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	device3d->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device3d->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	sprite->OnResetDevice();
	return result;
}

//�e�N�X�`�����f�t�H���g��D3D�������ɓǂݍ���
//�G���W���̎g�p���ɓ����I�ɂ̂ݎg�p���܂��B
//�Q�[���e�N�X�`���̓ǂݍ��݂ɂ�,TetxureManager�N���X���g�p���܂�
//�Q�[���e�N�X�`���̓ǂ݂��݂ɂ�TextureManager�N���X���g�p���܂�
//���s�O:filename�̓e�N�X�`���t�@�C���̖��O
//       transcolor�́A�����Ƃ��Ĉ����F
//���s��:width��heigh = �e�N�X�`���̐��@
//      texture�̓e�N�X�`�����w��
//HRESULT��߂�
HRESULT Graphics::loadTexture(const char *filename, COLOR_ARGB transcolor,
	UINT &width, UINT &height, LP_TEXTURE &texture)
{
	//�t�@�C������ǂݎ�邽�߂̍\����
	D3DXIMAGE_INFO info;
	result = E_FAIL;
	try
	{
		if (filename == NULL)
		{
			texture = NULL;
			return D3DERR_INVALIDCALL;
		}

		//���ƍ������t�@�C������擾
		result = D3DXGetImageInfoFromFile(filename, &info);
		if (result != D3D_OK)
			return result;
		width = info.Width;
		height = info.Height;

		//�t�@�C����ǂݍ���ŁA�V�����e�N�X�`�����쐬
		result = D3DXCreateTextureFromFileEx(
			device3d, //3D�f�o�C�X
			filename, //�摜�t�@�C���̖��O
			info.Width,//�e�N�X�`���̕�
			info.Height, //�e�N�X�`���̍���
			1,         //�~�j�}�b�v�̃��x��(�`�F�[�������̏ꍇ�͂P)
			0,         //�g�p���@(Usage)
			D3DFMT_UNKNOWN,//�T�[�t�F�C�X�t�H�[�}�b�g(�f�t�H���g)
			D3DPOOL_DEFAULT,//�e�N�X�`���p�̃������̎��
			D3DX_DEFAULT,//�摜�t�B���^
			D3DX_DEFAULT,//�~�b�v�t�B���^
			transcolor, //�����p�̐Fj�L�[
			&info,      //�r�b�g�}�b�v�t�@�C�����(�ǂݍ��񂾃t�@�C������)
			NULL,      //�J���[�p���b�g
			&texture   //�ړI�̃e�N�X�`��
			);

	}
	catch (...)
	{
		throw(GameError(gameErrorNS::FATAL_ERROR,
			"Erro in Graphics::loadTexture"));
	}
	return result;
}

//SpriteDate�\���̂ɋL�q���ꂽ�X�v���C�g��`��
//color(�I�v�V����)�́A�t�B���^�̂悤�ɓK�p�����
//�f�t�H���g�͔�(�ω��Ȃ�)
//���s�O:sprite->Begin()���Ăяo��
//���s��:sprite->End()���Ăяo��
//       sproteDate.rect�́A�`�悷��spriteDate.texture�񂐕������`
//       spriteDate.rect.right�́A�E�[+1�ɂ���K�v������
//       spriteDate.rect.bottom�́A���[+1�ɂ���K�v������
void Graphics::drawSprite(const SpriteData &spriteDate, COLOR_ARGB color)
{
	if (spriteDate.texture == NULL)//�e�N�X�`���������ꍇ
		return;
	

	//�X�v���C�g�̒��S�����
	D3DXVECTOR2 spriteCeneter = D3DXVECTOR2(
		(float)(spriteDate.width / 2 * spriteDate.scale),
		(float)(spriteDate.height / 2 * spriteDate.scale));

	//�X�v���C�g�̉�ʈʒu
	D3DXVECTOR2 translate =
		D3DXVECTOR2((float)spriteDate.x, (float)spriteDate.y);

	//X������Y�����̊g��k��
	D3DXVECTOR2 scaling(spriteDate.scale, spriteDate.scale);

	if (spriteDate.flipHorizontal)//���������ɔ��]����ꍇ
	{
		scaling.x *= -1;   //X�X�P�[���𕉂ɂ��Ĕ��]
		//���]���ꂽ�摜�̒��S���擾
		spriteCeneter.x -= (float)(spriteDate.width * spriteDate.scale);
		//���[�𒆐S�ɔ��]���N����̂�,���]���ꂽ�摜��
		//���Ɠ����ʒu�ɔz�u���邽�߂ɁA�E�ֈړ����܂��B
		translate.x += (float)(spriteDate.width * spriteDate.scale);
	}

	if (spriteDate.flipVertical)//���������ɔ��]����ꍇ
	{
		scaling.y *= -1;   //Y�X�P�[���𕉂ɂ��Ĕ��]
		//���]���ꂽ�摜�̒��S���擾
		spriteCeneter.y -= (float)(spriteDate.height * spriteDate.scale);
		//���[�𒆐S�ɔ��]���N����̂�,���]���ꂽ�摜��
		//���Ɠ����ʒu�ɔz�u���邽�߂ɁA�E�ֈړ����܂��B
		translate.y += (float)(spriteDate.height * spriteDate.scale);
	}

	//�X�v���C�g�̉�]�A�g��k���A�z�u���s�����߂̍s����쐬
	D3DXMATRIX matrix;
	D3DXMatrixTransformation2D(
		&matrix,    //�s��
		NULL,       //�g��k�����s���Ƃ��A���_�͍���̂܂�)
		0.0f,       //�g��k�����̉�]�Ȃ�
		&scaling,   //�g��k���̔{��
		&spriteCeneter,//��]�̒��S
		(float)(spriteDate.angle),//��]�̊p�x
		&translate  //X,Y�ʒu
		);

	//�s����X�v���C�g�ɓK�p
	sprite->SetTransform(&matrix);

	//�X�v���C�g��`��
	sprite->Draw(spriteDate.texture, &spriteDate.rect, NULL, NULL, color);
}

//=============================================================================
// Toggle window or fullscreen mode
// Pre: All user created D3DPOOL_DEFAULT surfaces are freed.
// Post: All user surfaces are recreated.
//=============================================================================
void Graphics::changeDisplayMode(graphicsNS::DISPLAY_MODE mode)
{
	try{
		switch (mode)
		{
		case graphicsNS::FULLSCREEN:
			if (fullscreen)      // if already in fullscreen mode
				return;
			fullscreen = true; break;
		case graphicsNS::WINDOW:
			if (fullscreen == false) // if already in window mode
				return;
			fullscreen = false; break;
		default:        // default to toggle window/fullscreen
			fullscreen = !fullscreen;
		}
		reset();
		if (fullscreen)  // fullscreen
		{
			SetWindowLong(hwnd, GWL_STYLE, WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP);
		}
		else            // windowed
		{
			SetWindowLong(hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
			SetWindowPos(hwnd, HWND_TOP, 0, 0, GAME_WIDTH, GAME_HEIGHT,
				SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

			// Adjust window size so client area is GAME_WIDTH x GAME_HEIGHT
			RECT clientRect;
			GetClientRect(hwnd, &clientRect);   // get size of client area of window
			MoveWindow(hwnd,
				0,                                           // Left
				0,                                           // Top
				GAME_WIDTH + (GAME_WIDTH - clientRect.right),    // Right
				GAME_HEIGHT + (GAME_HEIGHT - clientRect.bottom), // Bottom
				TRUE);                                       // Repaint the window
		}

	}
	catch (...)
	{
		// An error occured, try windowed mode 
		SetWindowLong(hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
		SetWindowPos(hwnd, HWND_TOP, 0, 0, GAME_WIDTH, GAME_HEIGHT,
			SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

		// Adjust window size so client area is GAME_WIDTH x GAME_HEIGHT
		RECT clientRect;
		GetClientRect(hwnd, &clientRect);   // get size of client area of window
		MoveWindow(hwnd,
			0,                                           // Left
			0,                                           // Top
			GAME_WIDTH + (GAME_WIDTH - clientRect.right),    // Right
			GAME_HEIGHT + (GAME_HEIGHT - clientRect.bottom), // Bottom
			TRUE);                                       // Repaint the window
	}
}

//�O�p�`�t�@�����g���āA�A���t�@���ߐ������l�p�`��\��
//���s�O�FcreateVertexBuffer���g����vertexBuffer���쐬���A
//       �l�p�`�����v���̏����Œ�`����S�̒��_���i�[���Ă���
//       g3ddec->BeginScene���Ăяo��
//���s��F�l�p�`���`�悳���
bool Graphics::drawQuad(LP_VERTEXBUFFER vertexBuffer)
{
	HRESULT result = E_FAIL; //�W����Window�߂�l
	if (vertexBuffer == NULL)
		return false;
	//�A���t�@�u�����h��L����
	device3d->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	device3d->SetStreamSource(0, vertexBuffer, 0, sizeof(VertexC));
	device3d->SetFVF(D3DFVF_VERTEX);
	result = device3d->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, 2);
	//�A���t�@�u�����h�𖳌���
	device3d->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	if (FAILED(result))
		return false;
	return true;
}

//���_�o�b�t�@���쐬
//���s�O�Fverts[]�ɒ��_�f�[�^���i�[����Ă���
//        size = verts[]�̃T�C�Y
//���s��F���������ꍇ�A&vertexBuffer���o�b�t�@���w��
HRESULT Graphics::createVertexBuffer(
	VertexC verts[], UINT size, LP_VERTEXBUFFER &vertexBuffer)
{
	//�W����Windows�߂�l
	HRESULT result = E_FAIL;
	//���_�o�b�t�@���쐬
	result = device3d->CreateVertexBuffer(size, D3DUSAGE_WRITEONLY,
		D3DFVF_VERTEX, D3DPOOL_DEFAULT, &vertexBuffer, NULL);
	if (FAILED(result))
		return result;
	void *ptr;
	//�f�[�^���]������Ă���O�ɁA�o�b�t�@�����b�N����K�v������
	result = vertexBuffer->Lock(0, size, (void**)&ptr, 0);
	if (FAILED(result))
		return result;
	memcpy(ptr, verts, size);//���_�f�[�^���o�b�t�@�ɃR�s�[
	vertexBuffer->Unlock();//�o�b�t�@�̃��b�N������
	return result;
}
