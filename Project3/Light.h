#pragma once
#include "Vector3f.h"
#include "Vector4f.h"
#include "GL/glut.h"


class Light
{
public:
	//Light light(boundaryX, boundaryY, boundaryX / 2, GL_LIGHT0);

	Light(int x, int y, int z, int LID);
	void setLightID(int LID);
	void setPosition(float x, float y, float z);
	void setAmbient(float r, float g, float b, float a);
	void setDiffuse(float r, float g, float b, float a);
	void setSpecular(float r, float g, float b, float a);
	void enableLight(bool bOn);


	bool isLightOn() const;

	void draw() const;

private:
	int lightID;
	Vector3f pos;
	Vector4f ambient;
	Vector4f diffuse;
	Vector4f specular;

	bool bLightOn;

};

