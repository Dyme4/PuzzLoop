#pragma once
#include "Constants.h"
#include "Vector3f.h"
#include "Material.h"
#include "GL/glut.h"



class Sphere
{
public:
	Sphere();
	Sphere(float r, int sl, int st);

	void setRadius(float r);
	float getRadius() const;
	void setSlice(int sl);
	void setStack(int st);

	void setCenter(float x, float y, float z);
	void setCenter(const Vector3f& cen);
	Vector3f getCenter() const;

	void setVelocity(float x, float y, float z);
	void setVelocity(const Vector3f& vel);
	Vector3f getVelocity() const;

	void setColorIdx(int i);
	int getColorIdx() const;

	void setMTL(const Material& m);
	Material& getMTL() ;

	void setLoopPointIdx(int idx);
	int getLoopPointIdx() const;
	void setCanonLoadIdx(int idx);
	int getCanonLoadIdx() const;

	void setCollisionHandling(bool b);
	bool getCollisionHandling() const;
	void setChainHandling(bool b);
	bool getChainHandling() const;



	void draw() const;

	bool boundaryDetection();
private:
	float radius;
	int slice;
	int stack;

	bool collisionHandling;
	bool chainHandling;

	int colorIdx; //0:RED, 1:GREEN, 2:BLUE, 3:YELLOW , 999:void

	Material mtl;


	Vector3f center;
	Vector3f velocity;

	int loopPointIndex;
	int canonLoadIndex;//AWAIT:0 NEXT:1 LAUNCH:2
};

