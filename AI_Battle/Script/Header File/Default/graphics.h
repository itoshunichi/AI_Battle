#ifndef _GRAPHICS_H //���̃t�@�C���������̉ӏ��ŃC���N���[�h�����ꍇ
#define _GRAPHICS_H //���d�ɒ�`����邱�Ƃ�h���܂�
#define _WIN32_LEAN_AND_MEAN
#ifdef _DEBUG
#define D3D_DEBUG_INFO
#endif
#include<d3d9.h>
#include<d3dx9.h>
#include "constants.h"
#include"gameError.h"
#include<list>
//DirectX�|�C���^�^
#define LP_TEXTURE  LPDIRECT3DTEXTURE9
#define LP_3DDEVICE LPDIRECT3DDEVICE9
#define LP_3D LPDIRECT3D9
#define LP_SPRITE LPD3DXSPRITE
#define LP_VERTEXBUFFER LPDIRECT3DVERTEXBUFFER9
#define LP_DXFONT   LPD3DXFONT
//�F�̒�`
#define COLOR_ARGB DWORD
#define SETCOLOR_ARGB(a,r,g,b) \
	((COLOR_ARGB)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))

//#define VECTOR2 D3DXVECTOR2

namespace graphicsNS
{
	// ���ʂŎg�p����F
	// ARGB�̐��l�͈̔͂�0����255�܂�
	// A = �A���t�@�`�����l��(�����x�A255�͕s����)
	// R = ��, G = ��, B = ��
	const COLOR_ARGB ORANGE = D3DCOLOR_ARGB(255, 255, 165, 0);
	const COLOR_ARGB BROWN = D3DCOLOR_ARGB(255, 139, 69, 19);
	const COLOR_ARGB LTGRAY = D3DCOLOR_ARGB(255, 192, 192, 192);
	const COLOR_ARGB GRAY = D3DCOLOR_ARGB(255, 128, 128, 128);
	const COLOR_ARGB OLIVE = D3DCOLOR_ARGB(255, 128, 128, 0);
	const COLOR_ARGB PURPLE = D3DCOLOR_ARGB(255, 128, 0, 128);
	const COLOR_ARGB MAROON = D3DCOLOR_ARGB(255, 128, 0, 0);
	const COLOR_ARGB TEAL = D3DCOLOR_ARGB(255, 0, 128, 128);
	const COLOR_ARGB GREEN = D3DCOLOR_ARGB(255, 0, 128, 0);
	const COLOR_ARGB NAVY = D3DCOLOR_ARGB(255, 0, 0, 128);
	const COLOR_ARGB WHITE = D3DCOLOR_ARGB(255, 255, 255, 255);
	const COLOR_ARGB YELLOW = D3DCOLOR_ARGB(255, 255, 255, 0);
	const COLOR_ARGB MAGENTA = D3DCOLOR_ARGB(255, 255, 0, 255);
	const COLOR_ARGB RED = D3DCOLOR_ARGB(255, 255, 0, 0);
	const COLOR_ARGB CYAN = D3DCOLOR_ARGB(255, 0, 255, 255);
	const COLOR_ARGB LIME = D3DCOLOR_ARGB(255, 0, 255, 0);
	const COLOR_ARGB BLUE = D3DCOLOR_ARGB(255, 0, 0, 255);
	const COLOR_ARGB BLACK = D3DCOLOR_ARGB(255, 0, 0, 0);
	const COLOR_ARGB FILTER = D3DCOLOR_ARGB(0, 0, 0, 0);  // colorFilter�ŕ`�悷�邱�Ƃ��w�肷�邽�߂Ɏg�p
	const COLOR_ARGB ALPHA25 = D3DCOLOR_ARGB(64, 255, 255, 255);  // �F��AND�����s����25%�A���t�@���擾
	const COLOR_ARGB ALPHA50 = D3DCOLOR_ARGB(128, 255, 255, 255);  // �F��AND�����s����50%�A���t�@���擾
	const COLOR_ARGB BACK_COLOR = NAVY; 


	enum DISPLAY_MODE{ TOGGLE, FULLSCREEN, WINDOW };
}

struct VertexC
{
	float x, y, z;
	float rhw;
	unsigned long color;
};

#define D3DFVF_VERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

//�X�v���C�g��`�悷��Graphics::drawSprite���K�v�Ƃ���v���p�e�B
struct SpriteData
{
	int width;//�X�v���C�g�̕�
	int height;//�X�v���C�g�̍���
	float x; //��ʈʒu
	float y; //��ʈʒu
	float scale;//<1�͏k��,>1�͊g��
	float angle;//��]�p�x
	RECT rect;  //�傫�ȃe�N�X�`�������̉摜��I������Ƃ��Ɏg�p
	LP_TEXTURE texture;//�e�N�X�`���ւ̃|�C���^
	bool flipHorizontal;//�X�v���C�g�𐅕������ɔ��]����ꍇ
	                    //(���̂悤�Ȕ���̏ꍇ)true
	bool flipVertical;  //�X�v���C�g�𐂒������ɔ��]����ꍇ
};

class Graphics
{
private:
	//DirectX�|�C���^�Ȃ�
	LP_3D direct3d;
	LP_3DDEVICE device3d;
	LP_SPRITE sprite;
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE pMode;
	//���̑��̕ϐ�
	HRESULT result; //�W����Window���^�[���R�[�h
	HWND hwnd;
	bool fullscreen;
	int width;
	int height;
	//(�G���W���̎g�p���ɓ����I�ɂ̂ݎg�p���܂�)
	//�����ɂ̓��[�U�[���g�p������̂͂���܂���
	//D3D�v���[���e�[�V�����p�����[�^��������
	void initD3Dpp();
	COLOR_ARGB  backColor;

public:
	//�R���X�g���N�^
	Graphics();
	//�f�X�g���N�^
	virtual ~Graphics();
	//direct3d��device3d�����
	void releaseAll();
	//DirectX�O���t�B�b�N�X��������
	//hw = �E�B���h�E�ւ̃n���h��
	//width = ��
	//height = ����
	//fullscreen == �S��ʕ\���̏ꍇ��true,�E�B���h�E�̏ꍇ��false
	//�G���[����GameError���X���[
	void initialize(HWND hw, int width, int heigth, bool fullscreen);
	//�I�t�X�N���[���o�b�N�o�b�t�@����ʂɕ\��
	HRESULT showBackbuffer();

	//�A�_�v�^�[���`�F�b�N���āAd3dpp�Ŏw�肳�ꂽBackBuffer�̍����A��
	//���t���b�V�����[�g�ɑΉ����Ă��邩�ǂ������m�F���܂��B
	//�Ή�������̂����������ꍇ�́ApMode�\���̂ɁA
	//�Ή����Ă��郂�[�h�̃t�H�[�}�b�g��ݒ肵�܂��B
	//���s�O�Fd3dpp������������Ă���
	//���s��F�Ή����Ă��郂�[�h��������ApMode�\���̂Ƀf�[�^��
	//�ݒ肳�ꂽ�ꍇtrue��߂��܂��B
	//�Ή����Ă��郂�[�h��������Ȃ������ꍇ�Afalse��߂��܂�
	bool isAdapterCompatible();

	

	//�O���t�B�b�N�X�f�o�C�X�����Z�b�g
	HRESULT reset();

	void changeDisplayMode(graphicsNS::DISPLAY_MODE mode = graphicsNS::TOGGLE);

	LP_3D get3D(){ return direct3d; }
	LP_3DDEVICE get3Ddevice(){ return device3d; }
	LP_SPRITE getSprite(){ return sprite; }
	HRESULT getDeviceState();
	bool getFullscreen(){ return fullscreen; }
	void setBackColor(COLOR_ARGB c){ backColor = c; }

	//�o�b�N�o�b�t�@���N���A���āADirectX��BeginScene()���Ăяo��
	//�o�b�N�o�b�t�@���N���A���āADirectX��BeginScene()���Ăяo��
	HRESULT beginScene()
	{
		result = E_FAIL;
		if (device3d == NULL)
			return result;
		//�o�b�N�o�b�t�@��backColor�ŃN���A����
		device3d->Clear(0, NULL, D3DCLEAR_TARGET, backColor, 1.0F, 0);
		result = device3d->BeginScene(); //�`��̂��߂̃V�[�����J�n����
		return result;
	}

	//DirectX��EndScene���Ăяo��
	HRESULT endScene()
	{
		result = E_FAIL;
		if (device3d)
			result = device3d->EndScene();
		return result;
	}

	void spriteBegin()
	{
		sprite->Begin(D3DXSPRITE_ALPHABLEND);
	}

	void spriteEnd()
	{
		sprite->End();
	}
	
	HRESULT loadTexture(const char *filename, COLOR_ARGB transcolor,
		UINT &width, UINT &height, LP_TEXTURE &texture);

	void drawSprite(const SpriteData &spriteDate, COLOR_ARGB color = graphicsNS::WHITE);

	//�x�N�g���̒�����float�Ƃ��Ė߂�
	//static float Vector2Length(const VECTOR2 *v){ return D3DXVec2Length(v); }

	//�x�N�g��V1��V2�̃h�b�g�ς�float�Ƃ��Ė߂��B�����V1���P�ʃx�N�g���ł���ꍇ�AV2��V1�����̒���
	//static float Vector2Dot(const VECTOR2 *v1, const VECTOR2 *v2){ return D3DXVec2Dot(v1, v2); }

	//�x�N�g��V��P�ʃx�N�g���ɕϊ����܂��B
	//static void Vector2Normalize(VECTOR2 *v){ D3DXVec2Normalize(v, v); }

	//�O�p�`�t�@�����g���āA�A���t�@���ߐ������l�p�`��\��
	bool drawQuad(LP_VERTEXBUFFER vertexBuffer);

	//���_�o�b�t�@���쐬
	HRESULT createVertexBuffer(VertexC verts[], UINT size, LP_VERTEXBUFFER &vertexBuffer);

};
#endif

