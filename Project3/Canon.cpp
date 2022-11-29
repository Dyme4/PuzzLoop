#include "Canon.h"
Canon::Canon() {}

void Canon::createCanon() {

	Material redMat;
	redMat.setEmission(0.5f, 0.1f, 0.1f, 1.0f);
	redMat.setAmbient(0.3f, 0.1f, 0.1f, 1.0f);
	redMat.setDiffuse(0.5f, 0.5f, 0.5f, 1.0f);
	redMat.setSpecular(1.0f, 0.8f, 0.8f, 1.0f);
	redMat.setShininess(50.0f);
	mats.push_back(redMat);

	Material greenMat;
	greenMat.setEmission(0.1f, 0.5f, 0.1f, 1.0f);
	greenMat.setAmbient(0.0f, 0.3f, 0.1f, 1.0f);
	greenMat.setDiffuse(0.5f, 0.5f, 0.5f, 1.0f);
	greenMat.setSpecular(0.8f, 1.0f, 0.8f, 1.0f);
	greenMat.setShininess(50.0f);
	mats.push_back(greenMat);

	Material blueMat;
	blueMat.setEmission(0.1f, 0.1f, 0.5f, 1.0f);
	blueMat.setAmbient(0.1f, 0.1f, 0.3f, 1.0f);
	blueMat.setDiffuse(0.5f, 0.5f, 0.5f, 1.0f);
	blueMat.setSpecular(0.8f, 0.8f, 1.0f, 1.0f);
	blueMat.setShininess(50.0f);
	mats.push_back(blueMat);

	Material yellowMat;
	yellowMat.setEmission(0.5f, 0.5f, 0.1f, 1.0f);
	yellowMat.setAmbient(0.3f, 0.3f, 0.1f, 1.0f);
	yellowMat.setDiffuse(0.5f, 0.5f, 0.5f, 1.0f);
	yellowMat.setSpecular(1.0f, 1.0f, 0.8f, 1.0f);
	yellowMat.setShininess(50.0f);
	mats.push_back(yellowMat);

	srand(time(NULL));
	for (int index : { AWAIT, NEXT}) {
		Sphere s;
		s.setRadius(radius);
		s.setSlice(30);
		s.setStack(30);
		s.setCanonLoadIdx(index);
		if (index == NEXT) {
			s.setCenter(0, 0, 0);
		}
		else if (index == AWAIT) {
			s.setVelocity(Vector3f(1, 0, 0) * shotVel);
			double posX = cos(directionAngle * PI / 180) * 2 * radius;
			double posY = sin(directionAngle * PI / 180) * 2 * radius;
			s.setCenter(posX, posY, 0);
		}
		
		int randomColor = (rand() % 4);
		s.setColorIdx(randomColor);
		s.setMTL(mats[randomColor]);
		sphereOnCanon.push_back(s);

		colorIndexVec = { 0,1,2,3 };
	}
}

void Canon::adjustAngle(int angle) {
	directionAngle += angle;
}

void Canon::setCanonLoadCenter() {
	double velX = cos(directionAngle * PI / 180);
	double velY = sin(directionAngle * PI / 180);
	for (Sphere& ball : sphereOnCanon) {
		if (ball.getCanonLoadIdx() == AWAIT) {
			ball.setVelocity(Vector3f(velX, velY, 0)*shotVel);
			ball.setCenter(velX * 2 * radius, velY * 2 * radius, 0);
		}
	}
}

void Canon::moveLaunchSphere() {
	Sphere& LaunchBall = sphereOnCanon[0];
	LaunchBall.setCenter(LaunchBall.getCenter()+LaunchBall.getVelocity());
}
void Canon::setCanonFired(bool Fired) {
	canonFired = Fired;
}

bool Canon::isCanonFired() {
	return canonFired;
}
bool Canon::boundaryDetection() {
	return sphereOnCanon[0].boundaryDetection();
}
void Canon::fire() {
	setCanonFired(true);
	double velX = cos(directionAngle * PI / 180);
	double velY = sin(directionAngle * PI / 180);
	for (Sphere& ball : sphereOnCanon) {
		switch (ball.getCanonLoadIdx()) {
		case AWAIT:
			ball.setCanonLoadIdx(LAUNCH);
			break;
		case NEXT:
			ball.setCanonLoadIdx(AWAIT);
			ball.setVelocity(Vector3f(velX, velY, 0) * shotVel);
			ball.setCenter(velX * 2 * radius, velY * 2 * radius, 0);
			break;

		}
	}
		srand(time(NULL));
		Sphere s;
		s.setRadius(radius);
		s.setSlice(30);
		s.setStack(30);	
		s.setCanonLoadIdx(NEXT);
		s.setCenter(0, 0, 0);
		int randomColor;

		if (colorIndexVec.size() == 0) //0으로 나누기 예외
			randomColor = 0;
		else
			randomColor = colorIndexVec[rand() % colorIndexVec.size()];

		//int randomColor = rand() % 4;
		s.setColorIdx(randomColor);
		s.setMTL(mats[randomColor]);
		sphereOnCanon.push_back(s);
	
}

float Canon::getVelX(int theta) const {
	float velX = cos((directionAngle + theta) * PI / 180);
	return velX;
}
float Canon::getVelY(int theta) const {
	float velY = sin((directionAngle + theta) * PI / 180);
	return velY;
}

void Canon::setColorIndexVec(const vector<int>& v) { colorIndexVec = v; }


void Canon::ReadyToFire() {
	sphereOnCanon.erase(sphereOnCanon.begin());
	setCanonFired(false);
}

Sphere &Canon::getSphere() {
	return sphereOnCanon[0];
}

void Canon::draw() const {
	for (const Sphere& ball : sphereOnCanon) {
		ball.draw();
	}	
	
	glDisable(GL_LIGHTING);
	
	glEnable(GL_LINE_STIPPLE);
	glColor3f(0.7, 0.7, 0.7);
	glLineStipple(5, 0xAAAA);
	glLineWidth(2);

	glBegin(GL_LINES);
	
	glVertex3f(0,0,0);
	double velX = cos(directionAngle * PI / 180);
	double velY = sin(directionAngle * PI / 180);
	glVertex3f(velX * windowRadius, velY*windowRadius, 0);
	glEnd();
	glDisable(GL_LINE_STIPPLE);

	glEnable(GL_LIGHTING);
}