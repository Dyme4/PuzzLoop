#include "Vector4f.h"

Vector4f::Vector4f() :pos{ 0,0,0,0} {}
Vector4f::Vector4f(float x, float y, float z, float w) : pos{ x,y,z,w } {}
void Vector4f::setPos(float x, float y, float z, float w) {
	pos[0] = x; pos[1] = y; pos[2] = z; pos[3] = w;
}
float& Vector4f::operator[](const int i) {
	return pos[i];
}
float Vector4f::operator[](const int i) const {
	return pos[i];
}

Vector4f Vector4f::operator+(const Vector4f& v) {
	return Vector4f(pos[0] + v.pos[0], pos[1] + v.pos[1], pos[2] + v.pos[2], pos[3] + v.pos[3]);
}
Vector4f Vector4f::operator-(const Vector4f& v) {
	return Vector4f(pos[0] - v.pos[0], pos[1] - v.pos[1], pos[2] - v.pos[2], pos[3] - v.pos[3]);
}
Vector4f Vector4f::operator*(const float s) {
	return Vector4f(s * pos[0], s * pos[1], s * pos[2], s*pos[3]);
}
Vector4f Vector4f::operator/(const float s) {
	return Vector4f(pos[0] / s, pos[1] / s, pos[2] / s, pos[3] / s);
}
