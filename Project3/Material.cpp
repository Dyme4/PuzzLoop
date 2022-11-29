#include "Material.h"

Material::Material() : emission(0,0,0,0), ambient(0,0,0,0), diffuse(0,0,0,0), specular(0,0,0,0), shininess(0) {

}
void Material::setEmission(float r, float g, float b, float a) {
	emission[0] = r; emission[1] = g; emission[2] = b; emission[3] = a;
}
void Material::setAmbient(float r, float g, float b, float a) {
	ambient[0] = r; ambient[1] = g; ambient[2] = b; ambient[3] = a;
}
void Material::setDiffuse(float r, float g, float b, float a) {
	diffuse[0] = r; diffuse[1] = g; diffuse[2] = b; diffuse[3] = a;
}
void Material::setSpecular(float r, float g, float b, float a) {
	specular[0] = r; specular[1] = g; specular[2] = b; specular[3] = a;
}
void Material::setShininess(float sh) {
	shininess = sh;
}

Material& Material::operator*= (const float s) {
	emission[0] *= s; emission[1] *= s; emission[2] *= s; emission[3] *= s;
	ambient[0] *= s; ambient[1] *= s; ambient[2] *= s; ambient[3] *= s;
	diffuse[0] *= s; diffuse[1] *= s; diffuse[2] *= s; diffuse[3] *= s;
	specular[0] *= s; specular[1] *= s; specular[2] *= s; specular[3] *= s;

	return (*this);
}

Vector4f Material::getEmission() const {
	return emission;
}
Vector4f Material::getAmbient() const {
	return ambient;
}
Vector4f Material::getDiffuse() const {
	return diffuse;
}
Vector4f Material::getSpecular() const {
	return specular;
}
float Material::getShininess() const {
	return shininess;
}