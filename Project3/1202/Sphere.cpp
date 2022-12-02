#include "Sphere.h"

Sphere::Sphere(float r, int sl, int st) : radius(r), slice(sl), stack(st), collisionHandling(false), chainHandling(false), colorIdx(999) {}
Sphere::Sphere() : collisionHandling(false), chainHandling(false), colorIdx(999) { }

void Sphere::setRadius(float r) {
	radius = r;
}
float Sphere::getRadius() const {
	return radius;
}
void Sphere::setSlice(int sl) {
	slice = sl;
}
void Sphere::setStack(int st) {
	stack = st;
}
void Sphere::setCenter(float x, float y, float z) {
	center[0] = x; center[1] = y; center[2] = z;
}
void Sphere::setCenter(const Vector3f& cen) {
	center = cen;
}

Vector3f Sphere::getCenter() const {
	return center;
}

void Sphere::setVelocity(float x, float y, float z) {
	velocity[0] = x; velocity[1] = y; velocity[2] = z;
}
void Sphere::setVelocity(const Vector3f& vel) {
	velocity = vel;
}
Vector3f Sphere::getVelocity() const {
	return velocity;
}

void Sphere::setColorIdx(int i) {
	colorIdx = i;
}
int Sphere::getColorIdx() const {
	return colorIdx;
}


void Sphere::setMTL(const Material& m) {
	mtl = m;
}
Material& Sphere::getMTL(){
	return mtl;
}

void Sphere::setLoopPointIdx(int idx) {
	loopPointIndex = idx;
}
int Sphere::getLoopPointIdx() const { return loopPointIndex; }
void Sphere::setCanonLoadIdx(int idx) {
	canonLoadIndex = idx;
}
int Sphere::getCanonLoadIdx() const { return canonLoadIndex; }

void Sphere::setCollisionHandling(bool b) { collisionHandling = b; }
bool Sphere::getCollisionHandling() const { return collisionHandling; }
void Sphere::setChainHandling(bool b) { chainHandling = b; }
bool Sphere::getChainHandling() const { return chainHandling; }

bool Sphere::boundaryDetection() {
	int radius = 25.f;
	if (center[0] >= boundaryX + radius || center[0] <= -boundaryX - radius || center[1] >= boundaryY + radius || center[1] <= -boundaryY - radius) {
		return true;
	}
	else return false;
}
void Sphere::draw() const {
	glPushMatrix();
	glTranslatef(center[0], center[1], center[2]);
	glShadeModel(GL_SMOOTH);
	float emissionArr[] = { mtl.getEmission()[0],mtl.getEmission()[1],mtl.getEmission()[2],mtl.getEmission()[3] };
	float ambientArr[] = { mtl.getAmbient()[0], mtl.getAmbient()[1], mtl.getAmbient()[2], mtl.getAmbient()[3] };
	float diffuseArr[] = { mtl.getDiffuse()[0], mtl.getDiffuse()[1], mtl.getDiffuse()[2], mtl.getDiffuse()[3] };
	float specularArr[] = { mtl.getSpecular()[0], mtl.getSpecular()[1], mtl.getSpecular()[2], mtl.getSpecular()[3] };
	float shininessArr[] = { mtl.getShininess() };

	glMaterialfv(GL_FRONT, GL_EMISSION, emissionArr);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientArr);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseArr);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularArr);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininessArr);

	glutSolidSphere(radius, slice, stack);
	glPopMatrix();
}