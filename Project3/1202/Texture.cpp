#include "Texture.h"

Texture::Texture() {
	textureID = -1;
	textureData = nullptr;
	imageWidth = imageHeight = 0;
}

FIBITMAP* Texture::createBitMap(string filename) {
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename.c_str(), 0);
	if (format == -1) {
		cout << "Could not find image: " << filename << " - Aborting." << endl;
		exit(-1);
	}
	else if (format == FIF_UNKNOWN) {
		cout << "Couldn't determine file format - attempting to get from file extension..." << endl;
		format = FreeImage_GetFIFFromFilename(filename.c_str());

		if (!FreeImage_FIFSupportsReading(format)) {
			cout << "Detected image format cannot be read!" << endl;
			exit(-1);
		}
	}

	FIBITMAP* bitmap = FreeImage_Load(format, filename.c_str());
	int bitsPerPixel = FreeImage_GetBPP(bitmap);
	FIBITMAP* bitmap24;
	if (bitsPerPixel == 24) {
		//cout << "Source image has " << bitsPerPixel << " bits per pixel. Skipping conversion." << endl;
		bitmap24 = bitmap;
	}
	else {
		//cout << "Source image has " << bitsPerPixel << " bits per pixel. Converting to 24-bit colour." << endl;
		bitmap24 = FreeImage_ConvertTo24Bits(bitmap);
	}

	return bitmap24;
}

void Texture::initializeTexture(string filename) {
	FIBITMAP* bitmap24 = createBitMap(filename);
	imageWidth = FreeImage_GetWidth(bitmap24);
	imageHeight = FreeImage_GetHeight(bitmap24);
	textureData = FreeImage_GetBits(bitmap24);
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, textureData);
}

GLuint Texture::getTextureID() const {
	return textureID;
}


