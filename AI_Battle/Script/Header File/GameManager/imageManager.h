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
	const char FACILIITY_TEXTURE[] = "pictures\\siro.png"
}

class ImageManager
{
private:
	TextureManager* facility_TextureManager;
	//TextureManager
	TextureManager* player_wait;
	TextureManager* fade;
	TextureManager* hp;
	TextureManager* wall;
	TextureManager* testPoint;
	TextureManager* WT_Enemey_wait;

	//Image
	Image facility_image;
	Image player_wait_image;
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

	//ImageŽæ“¾
	Image GetPlayer_Wait_Image(){ return player_wait_image; }
	Image fadeImage;
	Image getFadeImage(){ return fadeImage; }
	Image getHpImage(){ return hp_Image; }
	Image getWallImage(){ return wall_Image; }
	Image getTestPointImage(){ return testPoint_Image; }
	Image getWT_Enemy_Wait_Image(){ return WT_Enemey_wait_Image; }
};

#endif