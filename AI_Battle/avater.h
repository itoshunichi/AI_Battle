#ifndef AVATER_H_
#define AVATER_H_

#include"gameManager.h"
#include"vector2.h"
#include"lerpMove.h"
#include"entity.h"


class Avater:public Entity
{
	//�ϐ�
private:
	//�Q�[���}�l�[�W���[
	//GameManager *gameManager;
	//ImageManager *imageManager;
	//�ړ����x
	float speed;
	//���݂̉摜
	//Image currentImage;
	//�e�摜
	Image wait_Image;
	//�ړ����̖ڕW�ʒu
	Vector2 move_TargetPosition;
	LerpMove lerpMove;
	bool isAttack = false;


public:
	Avater();
	Avater(GameManager *gameManager);
	~Avater();
	//������
	void initialize();
	//�X�V
	void update(float frameTime);
	//�`��
	void draw();
	//�v���C���[�̕�������
	void setAngle_ToPlayer(Vector2 playerPos);
	//�U���J�n
	void startAttack(Vector2 endPos);
	//�U������
	void attack();

	void setAngle(float angle){ currentImage.setDegress(angle); }
	

private:
	//Image�̐ݒ�
	void setImage();
	//�A�j���[�V�����̐ݒ�
	void setAnimation();
	//�A�j���[�V�����̍X�V
	void animationUpdate(float frameTime);
};

#endif