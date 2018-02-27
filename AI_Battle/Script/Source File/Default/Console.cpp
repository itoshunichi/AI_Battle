#include"../../Header File/Default/console.h"

//�R���X�g���N�^
Console::Console()
{
	initialized = false; //����ɏ��������ꂽ�ꍇ�Atrue��ݒ�
	graphics = NULL;
	visible = false; //��\���ɂ���
	fontColor = consoleNS::FONT_COLOR;
	backColor = consoleNS::BACK_COLOR;
	x = consoleNS::X;//�ŏ��̃R���\�[���ʒu
	y = consoleNS::Y;
	textRect.bottom = consoleNS::Y + consoleNS::HEIGHT - consoleNS::MARGIN;
	textRect.left = consoleNS::X + consoleNS::MARGIN;
	textRect.right = consoleNS::X + consoleNS::WIDTH - consoleNS::MARGIN;
	textRect.top = consoleNS::Y + consoleNS::MARGIN;
	vertexBuffer = NULL;
	rows = 0;
	scrollAmount = 0;
}

//�f�X�g���N�^
Console::~Console()
{
	onLostDevice();
}

//�R���\�[����������
bool Console::initialize(Graphics *g, Input *in)
{
	try
	{
		graphics = g;//�O���t�B�b�N�V�X�e��
		input = in;
		//����
		vtx[0].x = x;
		vtx[0].y = y;
		vtx[0].z = 0.0f;
		vtx[0].rhw = 1.0f;
		vtx[0].color = backColor;
		//�E��
		vtx[1].x = x + consoleNS::WIDTH;
		vtx[1].y = y;
		vtx[1].z = 0.0f;
		vtx[1].rhw = 1.0f;
		vtx[1].color = backColor;
		//�E��
		vtx[2].x = x + consoleNS::WIDTH;
		vtx[2].y = y + consoleNS::HEIGHT;
		vtx[2].z = 0.0f;
		vtx[2].rhw = 1.0f;
		vtx[2].color = backColor;
		//����
		vtx[3].x = x;
		vtx[3].y = y + consoleNS::HEIGHT;
		vtx[3].z = 0.0f;
		vtx[3].rhw = 1.0f;
		vtx[3].color = backColor;
		graphics->createVertexBuffer(vtx, sizeof vtx, vertexBuffer);
		//DirectX�t�H���g��������
		if (dxFont.initialize(graphics, consoleNS::FONT_HEIGHT, false,
			false, consoleNS::FONT) == false)
			return false; //���s�̏ꍇ
		dxFont.setFontColor(fontColor);
	}
	catch (...)
	{
		return false;
	}
	initialized = true;
	return true;
}

//�R���\�[����`��
//���s�O:BeginScene��EndScene�̓����ɂ���
const void Console::draw()
{
	if (!visible || graphics == NULL || !initialized)
		return;
	graphics->drawQuad(vertexBuffer);//�w�i��`��
	if (text.size() == 0)
		return;
	graphics->spriteBegin();//�X�v���C�g�̕`����J�n
	//�R���\�[���Ƀe�L�X�g��\��
	textRect.left = 0;
	textRect.top = 0;
	//textRect�̉��[���P�s�̍����ɐݒ�
	dxFont.print("|", textRect, DT_CALCRECT);//�u|�v���A�S�����g�������Ƃ��Ďg�p
	int rowHeight = textRect.bottom + 2;//1�s�̍���(+2�͍s�ԃX�y�[�X)
	if (rowHeight <= 0)//�����true�ɂ͂Ȃ�Ȃ��Ƒz�肳���
		rowHeight = 20; //�@�\����l�������I�ɐݒ�

	//�R���\�[����ɕ\���\�ȍs��
	rows = (consoleNS::HEIGHT - 2 * consoleNS::MARGIN) / rowHeight;
	rows -= 2; //�����ɓ��̓v�����g�p�̃X�y�[�X���󂯂�
	if (rows <= 0) //�����true�ɂ͂Ȃ�Ȃ��Ƒz�肳���
		rows = 5;//�@�\����l�������I�ɐݒ�

	//1�s�̃e�L�X�g�\��rect��ݒ�
	textRect.left = (long)(x + consoleNS::MARGIN);
	textRect.right = (long)(textRect.right + consoleNS::WIDTH -
		consoleNS::MARGIN);
	//-2*rowHeight�́A���̓v�����g�p�̃X�y�[�X
	textRect.bottom = (long)(y + consoleNS::HEIGHT -
		2 * consoleNS::MARGIN - 2 * rowHeight);
	//���ׂĂ̍s(�ő��text.size())���������֏���
	for (int r = scrollAmount; r < rows + scrollAmount && r < (int)(text.size()); r++)
	{
		//���̍s�̃e�L�X�g�\��rect�̏�[��ݒ�
		textRect.top = textRect.bottom - rowHeight;
		//�e�L�X�g�̂P�s��\��
		dxFont.print(text[r], textRect, DT_LEFT);
		//�e�L�X�g�\��rect�̉��[�����̍s�p�ɒ���
		textRect.bottom -= rowHeight;
	}

	//�R�}���h�p�v�����g�ƁA���݂̃R�}���h�������\��
	//�v�����g�p�̃e�L�X�g�\��rect��ݒ�
	textRect.bottom = (long)(y + consoleNS::HEIGHT - consoleNS::MARGIN);
	textRect.top = textRect.bottom - rowHeight;
	std::string prompt = ">";  //�v�����g��������쐬
	prompt += input->getTextIn();
	dxFont.print(prompt, textRect, DT_LEFT); //�v�����g�ƃR�}���h��\��
	graphics->spriteEnd();
}

//�R���\�[���̕\���Ɣ�\��
void Console::shoeHide()
{
	if (!initialized)
		return;
	visible = !visible;
	input->clear(inputNS::KEYS_PRESSED | inputNS::TEXT_IN);//�Â����͂�����
}

//�R���\�[���Ƀe�L�X�g��ǉ�
//str�̐擪�s�̃e�L�X�g�̂ݕ\�������
void Console::print(const std::string &str) //�R���\�[���Ƀe�L�X�g��ǉ�
{
	if (!initialized)
		return;
	text.push_front(str); //str���f�b�Ntext�ɒǉ�
	if (text.size() > consoleNS::MAX_LINES)
		text.pop_back(); //�ł��Â��s���폜
}

//�R���\�[���R�}���h��߂�
//�V���O���L�[�̃R���\�[���R�}���h����������
//���̑��̃R�}���h�͂��ׂăQ�[���ɖ߂�
std::string Console::getCommand()
{
	//�R���\�[��������������Ă��Ȃ��ꍇ�A�܂��͕\������Ă��Ȃ��ꍇ
	if (!initialized || !visible)
		return "";
	//�R���\�[���L�[���`�F�b�N
	if (input->wasKeyPressed(CONSOLE_KEY))
		hide();//�R���\�[�����\��
	//Esc�L�[���`�F�b�N
	if (input->wasKeyPressed(ESC_KEY))
		return"";
	//�X�N���[�����`�F�b�N
	if (input->wasKeyPressed(VK_UP))//������L�[
		scrollAmount++;
	else if (input->wasKeyPressed(VK_DOWN))//�������L�[
		scrollAmount--;
	else if (input->wasKeyPressed(VK_PRIOR))//Page Up�L�[
		scrollAmount += rows;
	else if (input->wasKeyPressed(VK_NEXT))//Page Down�L�[
		scrollAmount -= rows;
	if (scrollAmount < 0)
		scrollAmount = 0;
	if (scrollAmount > consoleNS::MAX_LINES - 1)
		scrollAmount = consoleNS::MAX_LINES - 1;
	if (scrollAmount > (int)(text.size()) - 1)
		scrollAmount = (int)(text.size() - 1);
	commantStr = input->getTextIn(); //���[�U�[�����͂����e�L�X�g���擾
	//�L�[���Q�[���ɓn���Ȃ�
	input->clear(inputNS::KEYS_DOWN | inputNS::KEYS_PRESSED | inputNS::MOUSE);
	if (commantStr.length() == 0) //�R�}���h�����͂���Ă��Ȃ��ꍇ
		return"";
	//Enter�L�[��������Ă��Ȃ��ꍇ
	if (commantStr.at(commantStr.length() - 1) != '\r')
		return""; //�߂�
	//�R�}���h�̖�������u\r�v������
	commantStr.erase(commantStr.length() - 1);
	input->clearTextIn(); //���͍s���N���A
	return commantStr; //�R�}���h��߂�

}
void Console::onLostDevice()
{
	if (!initialized)
		return;
	dxFont.onLostDevice();
	SAFE_RELEASE(vertexBuffer);
}

void Console::onResetDevice()
{
	if (!initialized)
		return;
	graphics->createVertexBuffer(vtx, sizeof vtx, vertexBuffer);
	dxFont.onResetDevice();
}