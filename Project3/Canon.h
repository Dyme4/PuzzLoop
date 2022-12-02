#pragma once
#define LAUNCH 0
#define AWAIT 1
#define NEXT 2

#include <vector>
using namespace std;

#include "Sphere.h"
#include "Constants.h"
#include<cstdlib>
#include<ctime>
#include <cmath>

class Canon
{
public:
	Canon();

	void createCanon();
	void adjustAngle(int angle);
	void setCanonLoadCenter();

	void setCanonFired(bool Fired);
	bool isCanonFired();

	float getVelX(int theta) const;
	float getVelY(int theta) const;

	void updateRecoil();
	float getRecoil() const;

	void fire();
	void ReadyToFire();
	void moveLaunchSphere();
	void draw() const;
	bool boundaryDetection();

	Sphere& getSphere();

	void setColorIndexVec(const vector<int>& v);

private:
	int recoilVal = 0;
	vector<Sphere> sphereOnCanon;
	bool canonFired = false;
	int directionAngle = 0;
	vector<Material> mats;
	vector<int> colorIndexVec;

	//상수
	const int recoil_size = 8;
	const float recoil[8] = { 0,-35.f,-50.f,-75.f,-60.f,-45.f, -30.f, -15.f };
	const double PI = 3.1415926;
	const float radius = 25.f;
	const float shotVel = 7;
	const float windowRadius = sqrt(pow(boundaryX, 2) + pow(boundaryY, 2));

};

//발사중 - L A N fired == 1
//경계면 - L삭제 fired == 0
//장전중 - A N(발사가능) fired == 0
//발사시 - A N->L A N fired == 1

