#include "Loop.h"
#include<cstdlib>
#include<ctime>

using namespace std;


Loop::Loop() : gameOver(false), moveVertical(0.f),pullHandling(false),pullNum(0),fadeout(1.0f),deleteSphereNum(0),frontIdx(0), numOfSphere(0), score(0), difficulty(1.f) {
	loopPoints.clear();
}
void Loop::setGameOver(bool b) { gameOver = b; }
bool Loop::getGameOver() const { return gameOver; }

int Loop::getScore() const { return score; }
void Loop::addScore(int s) { score += s; }

vector<int> Loop::getColorIndexes() const {
	vector<int> colorIndexes;
	for (int i = 1; i < sphereOnLoop.size() - 1 && sphereOnLoop.size() > 2; ++i) {
		colorIndexes.push_back(sphereOnLoop[i].getColorIdx());
	}
	sort(colorIndexes.begin(), colorIndexes.end());
	colorIndexes.erase(unique(colorIndexes.begin(), colorIndexes.end()), colorIndexes.end());
	return colorIndexes;
}

bool Loop::getPullHandling() const { return pullHandling; }
void Loop::setDifficulty(float f) { difficulty = f; }

void Loop::createLoop(int stage) {
	const float radius = 25.0f;
	
	if (stage == 0) { //���� �ʱ�ȭ
		loopPoints.clear();
		sphereOnLoop.clear();
		score = 0;
		pullHandling = false;
		return;
	}

	else if (stage == 1) {
		loopPoints.clear();
		sphereOnLoop.clear();
		pullHandling = false;

		numOfSphere = 13 * difficulty; //����� ����, ���� 13

		loopPoints.reserve(3097);
		for (int i = -boundaryX - 2 * numOfSphere * radius - radius; i < boundaryX - 200; i++)
			loopPoints.push_back(Vector3f(i, 250.0f, 0.0f));

		for (int i = 250; i >= -250; i--)
			loopPoints.push_back(Vector3f(boundaryX - 200, i, 0.0f));

		for (int i = boundaryX - 200; i > -boundaryX - 20; i--)
			loopPoints.push_back(Vector3f(i, -250.0f, 0.0f));

		

	}
	else if (stage == 2) {
		loopPoints.clear();
		sphereOnLoop.clear();
		pullHandling = false;

		numOfSphere = 20 * difficulty; //����� ����, ���� 20

		loopPoints.reserve(4518);
		for (int i = -boundaryY - 2 * numOfSphere * radius - radius; i < 0; i++)
			loopPoints.push_back(Vector3f(-380, i, 0.0f));


		float r = 380.0f;
		const float PI = 3.1415926;

		for (float theta = PI; theta >= -3 * PI; theta -= 1 / r) {
			loopPoints.push_back(Vector3f(r * cos(theta), r * sin(theta), 0));
			r -= 0.075f;
		}

	}
	else if (stage == 3) {
		loopPoints.clear();
		sphereOnLoop.clear();
		pullHandling = false;

		numOfSphere = 11 * difficulty; //���� 11

		loopPoints.reserve(2210);		
		float r = 350.0f;
		const float PI = 3.1415926;
		for (int i = +boundaryX + numOfSphere * radius *2; i > 0; i--)
			loopPoints.push_back(Vector3f(i, -r, 0.0f));
		for (float theta = 1.5*PI; theta >= -PI; theta -= 1 / r) {
			loopPoints.push_back(Vector3f(r * cos(theta), r * sin(theta), 0));
			r -= 0.11f;
		}
	}
	else if (stage == 4) { //3������������ 3,4 ��� ����
		loopPoints.clear();
		sphereOnLoop.clear();
		pullHandling = false;

		numOfSphere = 11 * difficulty; //���� 11

		loopPoints.reserve(2210);
		float r = 350.0f;
		const float PI = 3.1415926;

		for (int i = -boundaryX - numOfSphere * radius * 2; i < 0; i++)
			loopPoints.push_back(Vector3f(i, r, 0.0f));
		for (float theta = 0.5*PI; theta >= -2 * PI; theta -= 1 / r) {
			loopPoints.push_back(Vector3f(r * cos(theta), r * sin(theta), 0));
			r -= 0.11f;
		}
	}

	vector<Material> mats;

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

	Material voidMat; //voidMat�� ���� �׸��� ����.
	
	srand(clock());
	for (int i = 0; i < numOfSphere; ++i) {
		Sphere s;
		s.setRadius(radius);
		s.setSlice(30);
		s.setStack(30);
		s.setLoopPointIdx(2 * radius * (numOfSphere - i));
		s.setCenter(loopPoints[s.getLoopPointIdx()]);

		if (i == 0 || i == numOfSphere - 1) { //�� �յ� ���� �� ����
			s.setColorIdx(999);
			s.setMTL(voidMat);
		}
		else {
			int randomColor = (rand() % 4);
			if (i >= 2 && sphereOnLoop[i - 2].getColorIdx() == randomColor && sphereOnLoop[i - 1].getColorIdx() == randomColor) {
				if (randomColor == 3) randomColor = 0;
				else randomColor++;
			}
			s.setColorIdx(randomColor);
			s.setMTL(mats[randomColor]);
		}

		sphereOnLoop.push_back(s);
	}
}


void Loop::moveSphere() {	
	if(pullHandling==false) {
		for (int idx = 0; idx < sphereOnLoop.size(); ++idx) {

			if (sphereOnLoop[idx].getCollisionHandling() == true) { //�浹
				sphereOnLoop[idx].setCenter(getVerticalBetween(sphereOnLoop[idx - 1], sphereOnLoop[idx + 1], -25.f));//�浹 ��ġ�� �̵�
				searchRep(idx, deleteSphereNum, frontIdx);//idx�� ������ �� ���� ���� ������ ���� ������ ù ���� �ε����� ���� ������ �ִ´�.
				if (deleteSphereNum >= 3) {//3���̻� �ߺ�
					fadeout -= 0.1f; // ���̵�ƿ� �ִϸ��̼� ���� 1.0f ~ 0���� 10������
					for (int i = 0; i < deleteSphereNum; i++) {
						sphereOnLoop[frontIdx + i].getMTL() *= fadeout; //�����ڷ� �ҷ��ͼ� ���͸��� ��Ӱ� ����
					}

					if (fadeout <= 0) {
						PlaySound(TEXT("source/sound/fadeout.wav"), NULL, SND_FILENAME | SND_ASYNC);
						//sound.playingFadeoutSfx();
						fadeout = 1.0f;
						for (int i = 0; i < deleteSphereNum; i++) {//�� ����
							deleteSphere(frontIdx);
						}
						cout << "deleted : " << deleteSphereNum << endl;
						addScore(deleteSphereNum * 10);
						pullHandling = true;//pull ����
					}
				}
				
				else {//3�� �̸� �ߺ�(�и��� ���ϸ��̼�)
					sphereOnLoop[idx].setCenter(getVerticalBetween(sphereOnLoop[idx - 1], sphereOnLoop[idx + 1], moveVertical - 25.f));
					moveVertical += 5.f;

					for (int i = 0; i < idx; ++i) {
						sphereOnLoop[i].setLoopPointIdx(sphereOnLoop[i].getLoopPointIdx() + 10.f); //�տ� ������ 10�� 5�� �з���
						sphereOnLoop[i].setCenter(loopPoints[sphereOnLoop[i].getLoopPointIdx()]);
					}

					if (moveVertical >= 25.f) { //������ �������� LoopPointIdx�� ����
						moveVertical = 0.f;
						sphereOnLoop[idx].setLoopPointIdx(sphereOnLoop[idx - 1].getLoopPointIdx() - 50.f);
						sphereOnLoop[idx].setCollisionHandling(false);
					}
				}
			}
			else if (sphereOnLoop[idx].getChainHandling() == true) { //���� ȿ��
				searchRep(idx, deleteSphereNum, frontIdx);//idx�� ������ �� ���� ���� ������ ���� ������ ù ���� �ε����� ���� ������ �ִ´�.
				if (deleteSphereNum >= 3) {//3���̻� �ߺ�
					fadeout -= 0.1f; // ���̵�ƿ� �ִϸ��̼� ���� 1.0f ~ 0���� 10������

					for (int i = 0; i < deleteSphereNum; i++) {
						sphereOnLoop[frontIdx + i].getMTL() *= fadeout; //�����ڷ� �ҷ��ͼ� �ٷ� ����
					}

					if (fadeout <= 0) {
						PlaySound(TEXT("source/sound/fadeout.wav"), NULL, SND_FILENAME | SND_ASYNC);
						//sound.playingFadeoutSfx();
						sphereOnLoop[idx].setChainHandling(false);
						fadeout = 1.0f;
						for (int i = 0; i < deleteSphereNum; i++) //�� ����
							deleteSphere(frontIdx);
						cout << "deleted : " << deleteSphereNum << endl;
						addScore(deleteSphereNum * 10);
						pullHandling = true;//pull ����
						pullNum = -5;//�� �ϳ� �� ��ܾ���
					}
				}
				else
					sphereOnLoop[idx].setChainHandling(false);
				
			}
			else if (sphereOnLoop.size() > 2) {
				int currLoopPtIdx = sphereOnLoop[idx].getLoopPointIdx();
				int newLoopPtIdx = currLoopPtIdx + 1;
				sphereOnLoop[idx].setLoopPointIdx(newLoopPtIdx);
				sphereOnLoop[idx].setCenter(loopPoints[newLoopPtIdx]);
				if (newLoopPtIdx >= loopPoints.size() - 25 && sphereOnLoop.size() > 2) {
					setGameOver(true);
				}
			}
		}
	}
	else { //pull
		pullNum++;
		
		for (int i = 0; i < frontIdx; ++i) {
			sphereOnLoop[i].setLoopPointIdx(sphereOnLoop[i].getLoopPointIdx() - 10.f); //�տ� ������ 10�� �����
			sphereOnLoop[i].setCenter(loopPoints[sphereOnLoop[i].getLoopPointIdx()]);
		}
		if (pullNum>=(deleteSphereNum-1)*5) { //FMBM�� BMFM�浹, �浹�� ���� ��� pullNum =0, ����ȿ���� ��� ��ĭ �� ���־��ؼ� pullNum = -5
			pullNum = 0;

			sphereOnLoop[frontIdx].setChainHandling(true);//����ȿ�� �۵�
			pullHandling = false;
		}
	}
}

void Loop::handleCollision(Sphere& cannonSph, int idx) {
	addSphere(idx, cannonSph);//������ ���� idx ��° ���Ϳ� �߰�, ���� LoopPtIdx�� �������� ����!!

	sphereOnLoop[idx].setCollisionHandling(true);

}

void Loop::addSphere(int idx, const Sphere& s) {
	sphereOnLoop.insert(sphereOnLoop.begin() + idx, s);
}
void Loop::deleteSphere(int idx) {
	sphereOnLoop.erase(sphereOnLoop.begin() + idx);
}



Sphere Loop::getSphere(int idx) const {
	return sphereOnLoop[idx];
}

vector<Sphere>& Loop::getSphereVector() {
	return sphereOnLoop;
}


void Loop::searchRep(int idx, int& deleteSphereNum, int& frontIdx) {
	int color_Idx, frontIndex;	
	int repBack= 0,repFront=0;
	int check_Idx = sphereOnLoop[idx].getColorIdx();

	//�޺κ� �ߺ���
	for (int i = idx+1; i < sphereOnLoop.size(); ++i) {
		color_Idx = sphereOnLoop[i].getColorIdx();
		if (check_Idx == color_Idx) {
			repBack++;
		}
		else {
			break;
		}
	}

	//�պκ� �ߺ���
	frontIndex = idx;
	for (int i = idx-1; i >=0; --i) {
		color_Idx = sphereOnLoop[i].getColorIdx();
		if (check_Idx == color_Idx) {
			repFront++;
		}
		else {
			break;
		}
		frontIndex = i;
	}
	int total = repBack + repFront + 1;
	
	deleteSphereNum = total;
	frontIdx = frontIndex;
}

Vector3f Loop::getVerticalBetween(const Sphere& s1, const Sphere& s2, float move) const {
	Vector3f center = (s1.getCenter() + s2.getCenter())/2;
	Vector3f parallel = s1.getCenter() - s2.getCenter();
	Vector3f vertical;
	vertical.setPos(-parallel[1], parallel[0], 0.f);
	vertical = vertical / vertical.size();
	return center + vertical * move;
}

void Loop::draw() const {
	// draw sphere
	glEnable(GL_LIGHTING);
	for (int i = 1; i < sphereOnLoop.size()-1  && !sphereOnLoop.empty(); ++i) { //�� �� �ڴ� �׸��� ����
		sphereOnLoop[i].draw();
	}
		

	// draw loop
	glDisable(GL_LIGHTING);
	glLineWidth(12.5f);
	
	glBegin(GL_LINE_STRIP);
	glColor3f(0.5f, 0.5f, 0.5f);
	for (int i = 0; i < loopPoints.size() - 100 && !loopPoints.empty(); i++)
		glVertex3f(loopPoints[i][0], loopPoints[i][1], loopPoints[i][2]);

	glColor3f(0.9f, 0.1f, 0.1f);
	for (int i = loopPoints.size() - 100; i < loopPoints.size() - 50 && !loopPoints.empty(); i++) //�� �տ� ������ ���� �ֱ� ������ �������� �ȱ׸� -50����
		glVertex3f(loopPoints[i][0], loopPoints[i][1], loopPoints[i][2]);

	glEnd();
}