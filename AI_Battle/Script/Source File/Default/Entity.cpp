#include"../../Header File/Default/entity.h"


Entity::Entity()
{
	radius = 1.0;
	edge.left = -1;
	edge.top = -1;
	edge.right = 1;
	edge.bottom = 1;
	mass = 1.0f;
	velocity.x = 0.0;
	velocity.y = 0.0;
	deltaV.x = 0.0;
	deltaV.y = 0.0;
	active = true; //�G���e�B�e�B�̓A�N�e�B�u
	rotatedBoxReady = false;
	collisionType = entityNS::CIRCLE;
	health = 100;
	gravity = entityNS::GRAVITY;
	center = vector2(0, 0);
}

////Entity��������
////���s�O:*gamePtr = Game�I�u�W�F�N�g�ւ̃|�C���^
////width = Image�̕�(�s�N�Z���P��)(0 = �e�N�X�`���S�̂̕����g�p)
////heigth = Image�̍���(�s�N�Z���P��)(0 = �e�N�X�`���S�̂̍������g�p)
////ncols = �e�N�X�`�����̗�(1����n�܂�)(0��1�Ɠ���)
////*textureM = TextureManager�I�u�W�F�N�g�ւ̃|�C���^
////���s��:���������ꍇ��true,���s�����ꍇ��false��߂�
//bool Entity::initialize(Game *gamePtr, int width, int height, int ncols,
//	TextureManager *textureM)
//{
//	//input = gamePtr->getInput(); //���̓V�X�e��
//	//audio = gamePtr->getAudio();
//	//return(Image::initialize(gamePtr->getGraphics(), width, height, ncols, textureM));
//}

//�G���e�B�e�B���A�N�e�B�u��
void Entity::activate()
{
	active = true;
}

//Update
//�ʏ�A�t���[�����ƂɂP��Ăяo��
//frameTime�́A�ړ��ƃA�j���[�V�����̑����𐧌䂷�邽�߂Ɏg�p
void Entity::update(float frameTime)
{
	currentImage.setX(position.x);
	currentImage.setY(position.y);
	currentImage.update(frameTime);
	velocity += deltaV;
	deltaV.x = 0;
	deltaV.y = 0;
	//Image::update(frameTime);
	rotatedBoxReady = false; //rotateBox�̏Փ˔���̂���
}

//AI(�l�H�m�\)
//�ʏ�A�t���[�����ƂɂP��Ăяo��
//�l�H�m�\�v�Z�����s,ent�͑��ݍ�p�̂��߂ɓn�����
void Entity::ai(float frameTime, Entity &ent)
{}

//���̃G���e�B�e�B�Ƃ�������̃G���e�B�e�B�̏Փ˂𔻒�
//�e�G���e�B�e�B�͕K��1��ނ̏Փ˂��g�p���܂�
//�Փ˂̎�ނ𕡐��K�v�Ƃ��镡�G�͐}�`�́A
//�e������ʌ̃G���e�B�e�B�Ƃ��Ĉ������Ƃɂ�菈���ł��܂�
//�ʏ�A�t���[�����ƂɂP��Ăяo��
//�Փ˂̎��:CIRCLE,BOX,�܂���ROTATED_BOX
//���s��F�Փ˂��Ă���ꍇ��true,���Ă��Ȃ��ꍇ��false��߂�
//        �Փ˂��Ă���ꍇ��,collisionVector��ݒ�
bool Entity::collideWith(Entity &ent)
{
	//if (otherTag != ""&&ent.getTag() != otherTag)return false;

	//�ǂ��炩�̃G���e�B�e�B���A�N�e�B�u�łȂ��ꍇ�A�Փ˂͋N����Ȃ�
	if (!active || !ent.getActive())
		return false;
	//�����̃G���e�B�e�B��CIRCLR�Փ˂ł���ꍇ
	if (collisionType == entityNS::CIRCLE&&
		ent.getCollisionType() == entityNS::CIRCLE)
		return collideCircle(ent);

	//�����̃G���e�B�e�B��BOX�Փ˂ł���ꍇ
	if (collisionType == entityNS::BOX&&
		ent.getCollisionType() == entityNS::BOX)
		return collideBox(ent);
	//���̂��ׂĂ̑g�ݍ��킹���g�p���镪�����e�X�g
	//�ǂ���̃G���e�B�e�B��CIRCLE�Փ˔�����g�p���Ȃ��ꍇ
	if (collisionType != entityNS::CIRCLE&&
		ent.getCollisionType() != entityNS::CIRCLE)
		return collideRotatedBox(ent);
	else//�ǂ��炩��̃G���e�B�e�B�͉~�̏ꍇ
		//���̃G���e�B�e�B��CIRCLE�Փ˂��g�p����ꍇ
		if (collisionType == entityNS::CIRCLE)
			return ent.collideRotatedBoxCircle(*this);
		else//��������̃G���e�B�e�B��CIRCLE�Փ˂��g�p����ꍇ
			return collideRotatedBoxCircle(ent);


}

//���̃G���e�B�e�B���w�肳�ꂽ�Z�`�̊O���ɂ��邩
//���s��F�Z�`�̊O���ɂ���ꍇ��true,����ȊO�̏ꍇ��false��߂�
bool Entity::outsideRect(RECT rect)
{
	if (position.x + currentImage.getWidth()*currentImage.getScale()<rect.left ||
		position.x>rect.right ||
		position.y + currentImage.getHeight()*currentImage.getScale()<rect.top ||
		position.y>rect.bottom)
		return true;
	return false;
}

//Damage
//���̃G���e�B�e�B���A����ɂ���ă_���[�W���󂯂�
//�p�����鑤�̃N���X�ł̂��̊֐����I�[�o�[���C�h
void Entity::damage(int weapon)
{

}

//�~�̏Փ˔��胁�\�b�h
//collision()�ɂ���ČĂяo�����A�f�t�H���g�̏Փ˔��胁�\�b�h
//���s��F�Փ˂��Ă���ꍇ��true,���Ă��Ȃ��ꍇ��false��߂�
//�Փ˂��Ă���ꍇ�́AcollisionVector��ݒ�
bool Entity::collideCircle(Entity &ent)
{
	//���S�ƒ��S�̊Ԃ̍�
	distSqured = getCenter() - ent.getCenter();
	distSqured.x = distSqured.x * distSqured.x;//�����Q��
	distSqured.y = distSqured.y  * distSqured.y;
	//���a�̍��v���v�Z(�g��k���̔{���𒲐�)
	sumRadiiSquared = (radius*currentImage.getScale()) + (ent.radius*ent.getCurrentImage().getScale());
	sumRadiiSquared *= sumRadiiSquared;//2��
	//�G���e�B�e�B���Փ˂��Ă���ꍇ
	if (distSqured.x + distSqured.y <= sumRadiiSquared)
	{
		//�Փ˃x�N�g����ݒ�
		collisionVelocity = ent.getCenter() - getCenter();
		return true;
	}
	return false;
}

//�����s���E�{�b�N�X�̏Փ˔��胁�\�b�h
//collision()�ɂ���ČĂяo�����
//���s��:�Փ˂��Ă���ꍇ��true,���Ă��Ȃ��ꍇ��false��߂�
//�Փ˂��Ă���ꍇ�́AcollisionVector��ݒ�
bool Entity::collideBox(Entity &ent)
{
	//�ǂ��炩�̃G���e�B�e�B���A�N�e�B�u�łȂ��ꍇ�A�Փ˂͋N����Ȃ�
	if (!active || !ent.getActive())
		return false;
	
	////�����s���E�{�b�N�X���g���ďՓ˂��`�F�b�N
	//if ((currentImage.getCenterX() + edge.right*currentImage.getScale() >=
	//	ent.getCurrentImage().getCenterX() + ent.getEdge().left*ent.getCurrentImage().getScale()) &&
	//	(currentImage.getCenterX() + edge.left*currentImage.getScale() <=
	//	ent.getCurrentImage().getCenterX() + ent.getEdge().right*ent.getCurrentImage().getScale()) &&
	//	(currentImage.getCenterY() + edge.bottom*currentImage.getScale() >=
	//	ent.getCurrentImage().getCenterY() + ent.getEdge().top*ent.getCurrentImage().getScale()) &&
	//	(currentImage.getCenterY() + edge.top*getCurrentImage().getScale() <=
	//	ent.getCurrentImage().getCenterY() + ent.getEdge().bottom*ent.getCurrentImage().getScale()))
	if (Math::abs(position.x - ent.getPosition().x)<(currentImage.getWidth()*currentImage.getScale()) / 2 + (ent.getCurrentImage().getWidth()*ent.getCurrentImage().getScale())/2&&
		Math::abs(position.y - ent.getPosition().y)<(currentImage.getHeight()*currentImage.getScale()) / 2 + (ent.getCurrentImage().getHeight()*ent.getCurrentImage().getScale())/2)
	{
		//�Փ˃x�N�g����ݒ�
		collisionVelocity = ent.getCenter() - getCenter();
		//Vector2 test =ent.getCenter();
		return true;

	}

	return false;
}

//��]����{�b�N�X�̏Փ˔��胁�\�b�h
//collision()�ɂ���ČĂяo�����
//���s��:�Փ˂��Ă���ꍇ��true,���Ă��Ȃ��ꍇ��false��߂�
//       �Փ˂��Ă���ꍇ�́AcollisionVector��ݒ�
//�������e�X�g���g�p���ďՓ˂𔻒�
//�������e�X�g�F
//2�̃{�b�N�X�́A����̒����ւ̓��e���d�Ȃ��Ă��Ȃ���ΏՓ˂��Ȃ�
bool  Entity::collideRotatedBox(Entity &ent)
{
	computeRotatedBox(); //��]����{�b�N�X������
	ent.computeRotatedBox();//��]����{�b�N�X������
	if (projectionsOverlap(ent) && ent.projectionsOverlap(*this))
	{
		//�Փ˃x�N�g����ݒ�
		collisionVelocity = ent.getCenter() - getCenter();
		return true;
	}

	return false;
}

//��]����{�b�N�X�̒��_�A���e���A���e�̍ŏ��l�ƍő�l���v�Z
//0---1���_�̔ԍ�
//|   |
//3---2
void Entity::computeRotatedBox()
{
	if (rotatedBoxReady)
		return;
	float projection;

	//x��y�̃x�N�g�������݂̃G���e�B�e�B�̊p�x����쐬����
	Vector2 rotatedX = vector2(cos(getCurrentImage().getRadians()), sin(getCurrentImage().getRadians()));
	Vector2 rotatedY = vector2(-sin(getCurrentImage().getRadians()), cos(getCurrentImage().getRadians()));

	//��]����{�b�N�X�̒��_���v�Z����
	const Vector2 center = getCenter();
	corners[0] = center + rotatedX*((float)edge.left*getCurrentImage().getScale()) +
		rotatedY*((float)edge.top*getCurrentImage().getScale());

	corners[1] = center + rotatedX*((float)edge.right * getCurrentImage().getScale()) +
		rotatedY *((float)edge.top*getCurrentImage().getScale());

	corners[2] = center + rotatedX*((float)edge.right * getCurrentImage().getScale()) +
		rotatedY *((float)edge.bottom * getCurrentImage().getScale());

	corners[3] = center + rotatedX*((float)edge.left*getCurrentImage().getScale()) +
		rotatedY*((float)edge.top *getCurrentImage().getScale());

	//2�̓��e�����쐬
	//corners[0]����_�Ƃ��Ďg�p
	//corners[0]�ɐڂ����ӂ𓊉e���Ƃ��Ďg�p
	edge01 = vector2(corners[1].x - corners[0].x,
		corners[1].y - corners[0].y);
	normalize(edge01);
	//graphics->Vector2Normalize(&edge01);

	edge03 = vector2(corners[3].x - corners[0].x,
		corners[3].y - corners[0].y);
	normalize(edge03);

	//���̃G���e�B�e�B�𓊉e����ɓ��e�����Ƃ��̍ŏ��l�ƍő�l
	projection = dot(edge01, corners[0]);
	edge01Min = projection;
	edge01Max = projection;
	//edge01�ւ̓��e
	projection = dot(edge01, corners[1]);
	if (projection < edge01Min)
		edge01Max = projection;
	//edge03�ւ̓��e
	projection = dot(edge03, corners[0]);
	edge03Min = projection;
	edge03Max = projection;
	projection = dot(edge03, corners[3]);
	if (projection < edge03Min)
		edge03Min = projection;
	else if (projection > edge03Max)
		edge03Max = projection;
	rotatedBoxReady = true;
}

//����̃{�b�N�X���A���̃G���e�B�e�B��edge01�����edge03�ɓ��e
//collideRotatedBox()�ɂ���ČĂяo�����
//���s��F���e���d�Ȃ��Ă���ꍇ��true�A����ȊO�̏ꍇ��false��߂�
bool Entity::projectionsOverlap(Entity &ent)
{
	float projection, min01, max01, min03, max03;
	//����̃{�b�N�X��edge01�ɓ��e
	projection = dot(edge01, *ent.getCorner(0));//
	//���_�O�𓊉e
	min01 = projection;
	max01 = projection;
	//�c��̒��_���ꂼ�������
	for (int c = 1; c < 4; c++)
	{
		//���_��edge01�ɓ��e
		projection = dot(edge01, *ent.getCorner(c));
		if (projection < min01)
			min01 = projection;
		else if (projection>max01)
			max01 = projection;
	}
	//���e���d�Ȃ�Ȃ��ꍇ
	if (min01 > edge01Max || max01 < edge01Min)
		return false;//�Փ˂̉\������
	//����̃{�b�N�X��edge03�ɓ��e
	projection = dot(edge03, *ent.getCorner(0));
	//���_0�𓊉e
	min03 = projection;
	max03 = projection;
	//�c��̒��_���ꂼ�������
	for (int c = 1; c < 4; c++)
	{
		//���_��edge03�ɓ��e
		projection = dot(edge03, *ent.getCorner(c));
		if (projection < min03)
			min03 = projection;
		else if (projection > max03)
			max03 = projection;
	}
	//���e���d�Ȃ�Ȃ��ꍇ
	if (min03>edge03Max || max03 < edge03Min)
		return false;//�Փ˂̉\������
	return true;     //���e���d�Ȃ��Ă���ꍇ
}

//��]����{�b�N�X�Ɖ~�̏Փ˔��胁�\�b�h
//collision()�ɂ���ČĂяo�����
//�{�b�N�X�̕ӂƉ~�̔��a�ŕ������e�X�g���g�p
//�~�̒��S���Փ˃{�b�N�X�̊e�ӂ�L�΂��������̊O��
//(�{���C�m�̈�ƌĂ΂��)�ɂ���ꍇ�A�{�b�N�X�̍ł��߂����_��
//�Փ˂��Ȃ����������̃`�F�b�N�Ŕ��肵�܂�
//�ł��߂����_�́A�d�Ȃ�̃e�X�g���画�f�ł��܂��B
//
//Voronoi0 |   | Voronoi1
//      ---0---1---
//         |   |
//      ---3---2---
//Voronoi3 |   | Voronoi2
//
//���s�O�F���̃G���e�B�e�B�͕K���{�b�N�X�A����̃G���e�B�e�B(ent)�͕K���~
//���s��F�Փ˂��Ă���ꍇ��true�A���Ă��Ȃ��ꍇ��false��߂�
//�Փ˂��Ă���ꍇ��,collisionVector��ݒ�
bool Entity::collideRotatedBoxCircle(Entity &ent)
{
	float min01, min03, max01, max03, center01, center03;

	computeRotatedBox(); //��]����{�b�N�X������

	//�~�̒��S��edge01�ɓ��e
	center01 = dot(edge01, ent.getCenter());
	//�ŏ��l�ƍő�l�͒��S����̔��a
	min01 = center01 - ent.getCurrentImage().getRadians()*ent.getCurrentImage().getScale();
	max01 = center01 + ent.getCurrentImage().getRadians()*ent.getCurrentImage().getScale();
	if (min01 > edge01Max || max01 < edge01Min)//���e���d�Ȃ�Ȃ��ꍇ
		return false;     //�Փ˂̉\���Ȃ�

	//�~�̒��S��edge03�ɓ��e
	center03 = dot(edge03, ent.getCenter());
	//�ŏ��l�ƍő�l�͒��S����̔��a
	min03 = center03 - ent.getCurrentImage().getRadians()*ent.getCurrentImage().getScale();
	max03 = center03 + ent.getCurrentImage().getRadians()*ent.getCurrentImage().getScale();
	if (min03 > edge03Max || max03 < edge03Min)//���e���d�Ȃ�Ȃ��ꍇ
		return false; //�Փ˂̉\���Ȃ�

	//�~�̓��e���{�b�N�X�̓��e�ɏd�Ȃ�ꍇ
	//�~���Փ˃{�b�N�X�̃{���C�m�̈�ɂ��邩�ǂ����`�F�b�N

	//���S��Vornoi0�ɂ���ꍇ
	if (center01 < edge01Min&&center03 < edge03Min)
		return collideCornerCircle(corners[0], ent);

	//���S��Voronoi1�ɂ���ꍇ
	if (center01>edge01Max&&center03 < edge03Min)
		return collideCornerCircle(corners[1], ent);

	//���S��Voronoi2�ɂ���ꍇ
	if (center01>edge01Max&&center03>edge03Max)
		return collideCornerCircle(corners[2], ent);

	//���S��Voronoi3�ɂ���ꍇ
	if (center01 > edge01Min&&center03 > edge03Max)
		return collideCornerCircle(corners[3], ent);

	//�~���{���m�C�̈�ɂȂ��ꍇ�A�~�̓{�b�N�X�̕ӂƏՓ˂��Ă���
	//�Փ˃x�N�g����ݒ�A�P���ɁA�~�̒��S����{�b�N�X�̒��S�܂ł��g�p
	collisionVelocity = ent.getCenter() - getCenter();

	return true;


}

//�{�b�N�X�̒��_���~�ƏՓ˂��Ă��Ȃ������A�����̃`�F�b�N���g�p���Ĕ���
//collideRotatedBoxCircle()�ɂ���ČĂяo�����
//���s��F�Փ˂��Ă���ꍇ��true�A���Ă��Ȃ��ꍇ��false��߂�
//�Փ˂��Ă���ꍇ��,collisionVector��ݒ�
bool Entity::collideCornerCircle(Vector2 corner, Entity &ent)
{
	distSqured = corner -ent.getCenter(); //���_-�~
	distSqured.x = distSqured.x * distSqured.x;//�����Q��
	distSqured.y = distSqured.y*distSqured.y;
	//���a�̍��v���v�Z���Ă���A������Q��
	sumRadiiSquared = ent.getRadius()*ent.getCurrentImage().getScale(); //(0+�~�̔��a)
	sumRadiiSquared *= sumRadiiSquared;//�Q�悷��
	//���_�Ɖ~���Փ˂��Ă���ꍇ
	if (distSqured.x + distSqured.y <= sumRadiiSquared)
	{
		//�Փ˃x�N�g����ݒ�
		collisionVelocity = ent.getCenter() - corner;
		return true;
	}
	return false;
}

//���̃G���e�B�e�B�Ƃ̏Փˌ�̒��˕Ԃ�
void Entity::bounce(Vector2 &collisionVector, Entity &ent)
{
	Vector2 Vdiff = ent.getVelocity() - velocity;
	Vector2 cUV = collisionVector; //�Փ˒P�ʃx�N�g��
	normalize(cUV);
	float cUVdotVdiff = dot(cUV, Vdiff);
	float massRatio = 2.0f;
	if (getMass() != 0)
		massRatio *= (ent.getMass() / (getMass() + ent.getMass()));
	//�G���e�B�e�B�����ɗ��������ɓ����Ă���ꍇ�́Abouce��
	//�O�ɂ��Ăяo���ꂽ���̂́A�Փ˂��܂������Ă����Ԃł��B
	//�G���e�B�e�B���AcollisionVector�ɉ����ė��������Ɉړ�
	if (cUVdotVdiff > 0)
	{
		position.x = (position.x - cUV.x*massRatio);
		position.y = (position.y - cUV.y*massRatio);
	}
	else
		deltaV += ((massRatio * cUVdotVdiff)*cUV);
}

//����̃G���e�B�e�B����̂��̃G���e�B�e�B�ւ̏d��
//�d�͂����̃G���e�B�e�B�̑��x�x�N�g���ɉ��Z
//Force = GRAVITY * m1 * m2 /r*r
//                2          2
//r*r = (Ax - Bx) + (Ay - By)
void Entity::gravityForce(Entity *ent, float frameTime)
{
	//�ǂ��炩�̃G���e�B�e�B���A�N�e�B�u�łȂ��ꍇ�A�d�͂̉e���͂Ȃ�
	if (!active || !ent->getActive())
		return;
	rr = pow((ent->getCurrentImage().getCenterX() - getCurrentImage().getCenterX()), 2) +
		pow((ent->getCurrentImage().getCenterY() - getCurrentImage().getCenterY()), 2);
	force = gravity * ent->getMass() * mass / rr;

	//---�x�N�g���v�Z���g���ďd�̓x�N�g�����쐬---
	//�G���e�B�e�B�Ԃ̃x�N�g�����쐬
	Vector2 gravityV = vector2(ent->getCurrentImage().getCenterX() - getCurrentImage().getCenterX(),
		ent->getCurrentImage().getCenterY() - getCurrentImage().getCenterY());

	//�x�N�g���𐳋K��
	normalize(gravityV);
	//�d�͂ŏ�Z���āA�d�̓x�N�g�����쐬
	gravityV *= force * frameTime;

	//�d�̓x�N�g�����A�ړ����̑��x�x�N�g���ɉ��Z���āA������ς���
	velocity += gravityV;
}