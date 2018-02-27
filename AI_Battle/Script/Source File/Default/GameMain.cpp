#include "../../Header File/Default/gamemain.h"

//�R���X�g���N�^
GameMain::GameMain()
{
	
	
}

//�f�X�g���N�^
GameMain::~GameMain()
{
	releaseAll();//���ׂẴO���t�B�b�N�X�A�C�e���ɂ���onLostDevice()��ǂݏo��
}

//�Q�[����������
//�G���[����GameError���X���[
void GameMain::initialize(HWND hwnd)
{
	Game::initialize(hwnd);//GameError���X���[
	text.initialize(getGraphics(), 14, false, false, "Courier New");
	text.setFontColor(gameNS::FONT_COLOR);

	gameManager.initialize(this, hwnd);

    sceneManager = SceneManager(&gameManager);
	sceneManager.addScene();
	sceneManager.change(SceneMode::GAMEPLAY);
}

//���ׂẴQ�[���A�C�e�����X�V
void GameMain::update()
{
	sceneManager.update(frameTime);

}

//�l�H�m�\
void GameMain::ai()
{
}

//�Փ˂�����
void GameMain::collisions()
{
	sceneManager.collision();
}

//�Q�[���A�C�e���������_�[
void GameMain::render()
{
	
	graphics->spriteBegin();   //�X�v���C�g�̕`����J�n

	//title.draw();
	sceneManager.draw();

	graphics->spriteEnd();
}

//�O���t�B�b�N�X�f�o�C�X�����������ꍇ
//�O���t�B�b�N�X�f�o�C�X�����Z�b�g�\�ɂ��邽��
//�\�񂳂�Ă����r�f�I�����������ׂĉ��
void GameMain::releaseAll()
{
	gameManager.getImageManager()->onLostDevice();
	Game::releseAll();
	return;
}

//�O���t�B�b�N�X�����Z�b�g���ꂽ�ꍇ
//���ׂẴT�[�t�F�C�X���č쐬
void GameMain::resetAll()
{
	gameManager.getImageManager()->onReserDevice();
	Game::resetAll();
	return;
}