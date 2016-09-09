#include "TextureComposer.hpp"
#include "Constants.hpp"

USING_NS_CC;
Texture2D * TextureComposer::composeGreyoutTexture(std::string filename)
{
	Image * image = new Image();
	image->initWithImageFile(filename);
	int width = image->getWidth();
	int height = image->getHeight();
	
	if (width <= 0 || height <= 0)
	{
		return nullptr;
	}
	
	FDBYTE* data = image->getData();
	FDBYTE* updateddata = new unsigned char[width * height * 4];
	
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			int index = (j * width + i ) * 4;

			int white = (data[index] + data[index + 1] + data[index + 2]) / 3;
			white = MIN(white, 255);
			updateddata[index] = white;
			updateddata[index + 1] = white;
			updateddata[index + 2] = white;
			updateddata[index + 3] = data[index + 3];
		}
	}
	
	image->release();
	
	Texture2D * texture = new Texture2D();
	texture->initWithData(updateddata, sizeof(Color4B) * width * height, kCCTexture2DPixelFormat_RGBA8888, width, height, CCSize(width, height));

	delete[] updateddata;
	texture->autorelease();
	return texture;
}