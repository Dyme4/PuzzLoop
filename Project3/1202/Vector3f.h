#pragma once
class Vector3f
{
public:
	Vector3f();
	Vector3f(float x, float y, float z);
	void setPos(float x, float y, float z);
	float size() const;

	float& operator[](const int i);
	float operator[](const int i) const;

	Vector3f operator+(const Vector3f& v);
	Vector3f operator-(const Vector3f& v);
	Vector3f operator*(const float s);
	Vector3f operator/(const float s);
	float dotProduct(const Vector3f& v1, const Vector3f& v2);

private:
	float pos[3];

};

