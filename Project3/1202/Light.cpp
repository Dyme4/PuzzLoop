#include "Light.h"
#include "Constants.h"


Light::Light(int x, int y, int z, int LID) : bLightOn(true), lightID(LID), pos(x,y,z){}
void Light::setLightID(int LID) {
	lightID = LID;
}
void Light::setPosition(float x, float y, float z) {
	pos[0] = x; pos[1] = y; pos[2] = z; 
}
void Light::setAmbient(float r, float g, float b, float a) {
	ambient[0] = r; ambient[1] = g; ambient[2] = b; ambient[3] = a;
}
void Light::setDiffuse(float r, float g, float b, float a) {
	diffuse[0] = r; diffuse[1] = g; diffuse[2] = b; diffuse[3] = a;
}
void Light::setSpecular(float r, float g, float b, float a) {
	specular[0] = r; specular[1] = g; specular[2] = b; specular[3] = a;
}
void Light::enableLight(bool bOn) {
	bLightOn = bOn;
}
bool Light::isLightOn() const {
	return bLightOn;
}
void Light::draw() const {
	if (bLightOn) {
		float ambientArr[] = { ambient[0], ambient[1], ambient[2], ambient[3] };
		float diffuseArr[] = { diffuse[0], diffuse[1], diffuse[2], diffuse[3] };
		float specularArr[] = { specular[0], specular[1], specular[2], specular[3] };
		float positionArr[] = { pos[0], pos[1], pos[2], 1.0f }; //1.0f mean point light
		
		glEnable(lightID);
		glLightfv(lightID, GL_AMBIENT, ambientArr);
		glLightfv(lightID, GL_DIFFUSE, diffuseArr);
		glLightfv(lightID, GL_SPECULAR, specularArr);
		glLightfv(lightID, GL_POSITION, positionArr);
	}
	else
		glDisable(lightID);


}
