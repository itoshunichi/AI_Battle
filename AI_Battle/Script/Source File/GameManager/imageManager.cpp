#include"../../Header File/GameManager/imageManager.h"

ImageManager::ImageManager()
{
	facility_TextureManager = new TextureManager(TextureName::FACILIITY_TEXTURE);
	
	textures = {facility_TextureManager};
}

void ImageManager::initialize(Graphics *g)
{
	for (int i = 0; i < textures.size(); i++)
	{
		textures[i]->initialize(g);
	}

	facility_image.initialize(g, 0, 0, 0, facility_TextureManager);
	/*fadeImage.initialize(g, 0, 0, 0, fade);
	player_wait_image.initialize(g, 128, 128, 4, player_wait);
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




