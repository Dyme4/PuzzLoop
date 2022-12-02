#pragma once
#include <windows.h>
#include <vector>
#include<algorithm>
#include<string>
using namespace std;
#include <iostream>
#include "Sphere.h"
#include "Constants.h"
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include "Sound.h"

class Loop
{
public:
	Loop();

	void createLoop(int stage);
	void moveSphere();
	void handleCollision(Sphere& cannonSph, int idx);

	void setGameOver(bool b);
	bool getGameOver() const;

	int getScore() const;
	void addScore(int s);

	bool getPullHandling() const;

	void draw() const;

	void addSphere(int idx, const Sphere& s);
	void deleteSphere(int idx);

	void setDifficulty(float f);


	void searchRep(int idx, int& deletedSphereNum, int& frontIdx);

	Sphere getSphere(int idx) const;
	vector<Sphere>& getSphereVector();
	vector<int> getColorIndexes() const;

	Vector3f getVerticalBetween(const Sphere& s1, const Sphere& s2, float move) const;

private:
	vector<Vector3f> loopPoints;

	vector<Sphere> sphereOnLoop;



	int numOfSphere;
	int pullNum;
	bool gameOver;
	bool pullHandling;
	float moveVertical;

	int deleteSphereNum, frontIdx; //Pull¿ë º¯¼ö
	float fadeout;
	int score;

	Sound sound;

	float difficulty;
};

