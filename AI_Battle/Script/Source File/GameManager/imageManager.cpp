#include"../../Header File/GameManager/imageManager.h"

ImageManager::ImageManager()
{
	facility_TextureManager = new TextureManager(TextureName::FACILIITY_TEXTURE);
	fade = new TextureManager(TextureName::FADE_TEXTURE);
	aitemIcon_TextureManager = new TextureManager(TextureName::AITEMICON_TEXTURE);
	testCharacter_TextureManager = new TextureManager(TextureName::TESTPLAYER_TEXTURE);
	formCharacterPoint_TextureManager = new TextureManager(TextureName::FORMCHARACTERPOINT_TEXTURE);
	backGround_TextureManager = new TextureManager(TextureName::BACKGROUND_TEXTURE);
	textures = {facility_TextureManager,fade,aitemIcon_TextureManager,testCharacter_TextureManager,formCharacterPoint_TextureManager,backGround_TextureManager};
}

void ImageManager::initialize(Graphics *g)
{
	for (int i = 0; i < textures.size(); i++)
	{
		textures[i]->initialize(g);
	}

	facility_image.initialize(g, 0, 0, 0, facility_TextureManager);
	fadeImage.initialize(g, 0, 0, 0, fade);
	aitemIcon_image.initialize(g, 0, 0, 0, aitemIcon_TextureManager);
	testCharacter_image.initialize(g, 0, 0, 0, testCharacter_TextureManager);
	formCharacterPoint_image.initialize(g, 0, 0, 0, formCharacterPoint_TextureManager);
	backGround_Imgae.initialize(g, 0, 0, 0, backGround_TextureManager);
	/*player_wait_image.initialize(g, 128, 128, 4, player_wait);
	hp_Image.initialize(g, 0, 0, 0, hp);
	wall_Image.initialize(g, 0, 0, 0, wall);
	testPoint_Image.initialize(g, 0, 0, 0, testPoint);
	WT_Enemey_wait_Image.initialize(g, 128, 128, 4, WT_Enemey_wait);*/

}

void ImageManager::onLostDevice()
{
	std::for_each(textures.begin(), textures.end(), [](TextureManager* textureManager){textureManager->onLostDevice(); });
}

void ImageManager::onReserDevice()
{
	std::for_each(textures.begin(), textures.end(), [](TextureManager* textureManager){textureManager->onResetDevice(); });
}




