#ifndef GAMETEXTURE_H
#define GAMETEXTURE_H
#define WIN32_LEAN_AND_MEAN

#include"imageManager.h"
#include"../Default/image.h"
#include<vector>
#include"../Default/game.h"

using namespace std;

namespace TextureName
{
	const char FACILIITY_TEXTURE[] = "pictures\\siro.png";
	const char FADE_TEXTURE[] = "pictures\\fade.png";
	const char AITEMICON_TEXTURE[] = "pictures\\aitemIcon.png";
	const char TESTPLAYER_TEXTURE[] = "pictures\\character.png";
	const char FORMCHARACTERPOINT_TEXTURE[] = "pictures\\point.png";
	const char BACKGROUND_TEXTURE[] = "pictures\\backGround.png";
	const char LONGATTACKTESTCHARACTER_TEXTURE[] = "pictures\\character2.png";
	const char TESTWEAPON_TEXTURE[] = "pictures\\TestWeapon.png";
	const char COST_TEXTURE[] = "pictures\\life.png";
}

class ImageManager
{
private:
	TextureManager* facility_TextureManager;
	TextureManager* aitemIcon_TextureManager;
	TextureManager* testCharacter_TextureManager;
	TextureManager* formCharacterPoint_TextureManager;
	TextureManager* backGround_TextureManager;
	TextureManager* longAttackTestCharacter_TextureManager;
	TextureManager* testWeapon_TextureManager;
	//TextureManager
	TextureManager* player_wait;
	TextureManager* fade;
	TextureManager* hp;
	TextureManager* wall;
	TextureManager* testPoint;
	TextureManager* WT_Enemey_wait;

	//Image
	Image facility_image;
	Image aitemIcon_image;
	Image testCharacter_image;
	Image player_wait_image;
	Image formCharacterPoint_image;
	Image backGround_Imgae;
	Image longAttackTestCharacter_Image;
	Image testWeapon_Image;

	Image hp_Image;
	Image wall_Image;
	Image testPoint_Image;
	Image WT_Enemey_wait_Image;

	//TextDX text;


	vector<TextureManager*> textures;
	vector<Image>images;

public:
	ImageManager();
	void initialize(Graphics *g);
	void onLostDevice();
	void onReserDevice();

	//Image�擾
	Image getFacility_Image(){ return facility_image; }
	Image getAitemIcon_Image(){ return aitemIcon_image; }
	Image getTestCharacter_Image(){ return testCharacter_image; }
	Image GetPlayer_Wait_Image(){ return player_wait_image; }
	Image fadeImage;
	Image getFadeImage(){ return fadeImage; }
	Image getHpImage(){ return hp_Image; }
	Image getWallImage(){ return wall_Image; }
	Image getTestPointImage(){ return testPoint_Image; }
	Image getWT_Enemy_Wait_Image(){ return WT_Enemey_wait_Image; }
	Image getFormCharacterPoint_Image(){ return formCharacterPoint_image; }
	Image getBackGround_Image(){ return backGround_Imgae; }
	Image getLongAttackTestCharacter_Image(){ return longAttackTestCharacter_Image; }
	Image getTestWeapon_Image(){ return testWeapon_Image; }
};

#endif