#include "Texture.h"



Texture::Texture()
{
}


Texture::~Texture()
{
}

bool Texture::loadTexture(char* name)
{
	char* texFile = name;
	
	auto format = FreeImage_GetFileType(texFile, 0);
	FIBITMAP* image = FreeImage_Load(format, texFile);

	if (image == nullptr) //load fail
	{
		cout << "Texture load fail" << endl;
		return false;
	}

	FIBITMAP* image32bit = FreeImage_ConvertTo32Bits(image);
	FreeImage_Unload(image);

	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, FreeImage_GetWidth(image32bit), FreeImage_GetHeight(image32bit), 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(image32bit));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//textures.push_back(texID);
	//texIndex = textures.size();

	FreeImage_Unload(image32bit);
	glBindTexture(GL_TEXTURE_2D, 0);
	return true;
}