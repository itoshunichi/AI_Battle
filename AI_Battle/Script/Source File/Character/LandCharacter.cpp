#include"../../Header File/Character/landCharacter.h"

LandCharacter::LandCharacter()
{
	//陸上タイプ
	type = Type::LAND;
}

LandCharacter::~LandCharacter()
{

}

//位置の設定
void LandCharacter::setPosition(float pointPositionX, int pointRow)
{
	if (pointRow == 1)
	{
		position = vector2(pointPositionX, firstColumnMaxY);
	}
	else if (pointRow == 2)
	{
		position = vector2(pointPositionX, secondColumnMaxY);
	}

	else if (pointRow == 3)
	{
		position = vector2(pointPositionX, thirdColumnMaxY);
	}
	position.y -= currentImage.getHeight();
}
