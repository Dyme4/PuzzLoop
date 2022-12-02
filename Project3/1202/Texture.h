#pragma once

#include <iostream>
#include <GL/glut.h>

#include <string>
#include "Constants.h"
#include <FreeImage.h>

using namespace std;

class Texture
{
public:
	Texture();

	FIBITMAP* createBitMap(string filename);
	void initializeTexture(string filename);

	GLuint getTextureID() const;

private:
	GLuint textureID;
	GLubyte* textureData;
	int imageWidth, imageHeight;
};

