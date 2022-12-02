#include "Vector3f.h"
#include <cmath>

Vector3f::Vector3f() :pos{ 0,0,0 } {}
Vector3f::Vector3f(float x, float y, float z) : pos{ x,y,z } {}
void Vector3f::setPos(float x, float y, float z) {
	pos[0] = x; pos[1] = y; pos[2] = z;
}
float Vector3f::size() const {
	return sqrt(pos[0] * pos[0] + pos[1] * pos[1] + pos[2] * pos[2]);
}

float& Vector3f::operator[](const int i) {
	return pos[i];
}
float Vector3f::operator[](const int i) const {
	return pos[i];
}

Vector3f Vector3f::operator+(const Vector3f& v) {
	return Vector3f(pos[0] + v.pos[0], pos[1] + v.pos[1], pos[2] + v.pos[2]);
}
Vector3f Vector3f::operator-(const Vector3f& v) {
	return Vector3f(pos[0] - v.pos[0], pos[1] - v.pos[1], pos[2] - v.pos[2]);
}
Vector3f Vector3f::operator*(const float s) {
	return Vector3f(s * pos[0], s * pos[1], s * pos[2]);
}
Vector3f Vector3f::operator/(const float s) {
	return Vector3f(pos[0] / s, pos[1] / s, pos[2] / s);
}
float Vector3f::dotProduct(const Vector3f& v1, const Vector3f& v2){
	return (v1.pos[0] * v2.pos[0] + v1.pos[1] * v2.pos[1] + v1.pos[2] * v2.pos[2]);
}