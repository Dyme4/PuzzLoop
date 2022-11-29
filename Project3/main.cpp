#include <iostream>
#include <string>
#include <cmath>
#include "Sound.h"
#include "Loop.h"
#include "Light.h"
#include "Canon.h"
#include "Texture.h"


Loop loop, loop2;
Light light(boundaryX, boundaryY, boundaryX / 2, GL_LIGHT0);
Canon canon;
Texture canonTexture;
vector<Texture> menuTexture;
Texture optionTexture, pauseTexture, pause_keyTexture, scoreboardTexture;
int menuIdx=0;
Sound sound;

clock_t playing_start_t = clock(); //게임 시작한 시점
clock_t start_t = clock(); //1/60초마다 end_t로 초기화
clock_t end_t; //idle 내에서 계속 바뀜

int gameSpeed = 10;
bool keyboardPause=true;
bool gameStarted = false;
bool optionBool = false; //false면 메인메뉴, true면 옵션메뉴
bool scoreboardBool = false; //true면 스코어보드
bool gamePaused = false;//true면 pause창이 켜진 상태

int stage = 1;//기본 1

float rotateTetrahedron = 0;

enum MENU { PLAY, OPTION, SCOREBOARD, EXIT } menu;
enum OptionMENU { EASY, NORMAL, HARD, ON, OFF, BACK} optionmenu;
enum PauseMENU { CONTINUE, MAINMENU } pausemenu;
float optionDifficultyPos[2] = {-197.5, -72};
float optionMusicPos[2] = { 342.5f, -30.f };

void displayCharacters(void* font, string str, float x, float y) {
	glDisable(GL_LIGHTING);
	glRasterPos2f(x, y);
	for (int i = 0; i < str.size(); i++)
		glutBitmapCharacter(font, str[i]);
}

float distance(const Sphere& sph1, const Sphere& sph2) {
	return sqrt(pow(sph1.getCenter()[0] - sph2.getCenter()[0], 2) +
		pow(sph1.getCenter()[1] - sph2.getCenter()[1], 2) +
		pow(sph1.getCenter()[2] - sph2.getCenter()[2], 2));
}

float distance(const Vector3f& v1, const Vector3f& v2) {
	return sqrt(pow(v1[0] - v2[0], 2) +
		pow(v1[1] - v2[1], 2) +
		pow(v1[2] - v2[2], 2));
}

bool isCollisionDetected(const Sphere& sph1, const Sphere& sph2) {
	return distance(sph1, sph2) < (sph1.getRadius() + sph2.getRadius());
}

void handleCollision(Sphere& cannonSph, vector<Sphere>& loopSph) {
	try {
		for (int i=1; i < loopSph.size()-1; ++i) { //맨 앞 뒤는 충돌 무시, 1~size()-2까지만
			if (isCollisionDetected(cannonSph, loopSph[i])) {
				
				if (distance(cannonSph.getCenter(),loop.getVerticalBetween(loopSph[i+1], loopSph[i], 25.f)) > 
					distance(cannonSph.getCenter(),loop.getVerticalBetween(loopSph[i], loopSph[i-1], 25.f))) {//앞의 공에 더 가까울때
					throw i;
				}
				else { //뒤의 공에 더 가까울때
					
					throw i + 1;
				}
			}
		}
	}
	catch (int idx) {
		loop.handleCollision(cannonSph, idx);
		sound.playingHitSfx();
		canon.ReadyToFire();
	}
}

void handleCollision2(Sphere& cannonSph, vector<Sphere>& loopSph) {
	try {
		for (int i = 1; (i < loopSph.size() - 1) && !loopSph.empty(); ++i) { //맨 앞 뒤는 충돌 무시, 1~size()-2까지만, loop2가 비어있지 않을때
			if (isCollisionDetected(cannonSph, loopSph[i])) {

				if (distance(cannonSph.getCenter(), loop2.getVerticalBetween(loopSph[i + 1], loopSph[i], 25.f)) >
					distance(cannonSph.getCenter(), loop2.getVerticalBetween(loopSph[i], loopSph[i - 1], 25.f))) {//앞의 공에 더 가까울때
					throw i;
				}
				else { //뒤의 공에 더 가까울때

					throw i + 1;
				}
			}
		}
	}
	catch (int idx) {
		loop2.handleCollision(cannonSph, idx);
		sound.playingHitSfx();
		canon.ReadyToFire();
	}
}

void drawCanonWithTexture() {
	int imageWidth = 100;
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, canonTexture.getTextureID() );
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(imageWidth * canon.getVelX(45), imageWidth * canon.getVelY(45));
	glTexCoord2f(0.0f, 1.0f); glVertex2f(imageWidth * canon.getVelX(135), imageWidth * canon.getVelY(135));
	glTexCoord2f(1.0f, 1.0f); glVertex2f(imageWidth * canon.getVelX(225), imageWidth * canon.getVelY(225));
	glTexCoord2f(1.0f, 0.0f); glVertex2f(imageWidth * canon.getVelX(315), imageWidth * canon.getVelY(315));
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void drawMenuTexture(int idx) {
	int imageWidth = 1200; int imageHeight = 800;
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, menuTexture[idx].getTextureID());
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(-imageWidth/2 , -imageHeight/2 );
	glTexCoord2f(0.0f, 1.0f); glVertex2f(-imageWidth/2 , imageHeight/2);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(imageWidth/2, imageHeight / 2);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(imageWidth/2, -imageHeight / 2);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void drawPauseKeyTexture() {
	int imageWidth = 220; int imageHeight = 70;
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, pause_keyTexture.getTextureID());
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(-imageWidth+570, -imageHeight+380);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(-imageWidth+570, 380);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(570, 380);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(570, -imageHeight+380);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}


	
void specialKeyboardDown(int key, int x, int y) {
	if (gameStarted == false && optionBool == false){ //메인메뉴
		switch (key) {
		case GLUT_KEY_UP:
			if (menu == PLAY)
				menu = EXIT;
			else
				menu = static_cast<MENU>(menu - 1);
			break;

		case GLUT_KEY_DOWN:
			if (menu == EXIT)
				menu = PLAY;
			else
				menu = static_cast<MENU>(menu + 1);
			break;
		default:
			break;
		}
	}
	else if (gameStarted == false && optionBool == true) { //옵션
		switch (key) {
		case GLUT_KEY_UP:
			if (optionmenu == EASY)
				optionmenu = BACK;
			else
				optionmenu = static_cast<OptionMENU>(optionmenu - 1);
			break;

		case GLUT_KEY_DOWN:
			if (optionmenu == BACK)
				optionmenu = EASY;
			else
				optionmenu = static_cast<OptionMENU>(optionmenu + 1);
			break;
		default:
			break;
		}
	}
	else if (gameStarted == true && gamePaused == true) { //퍼즈
		switch (key) {
		case GLUT_KEY_UP:
		case GLUT_KEY_DOWN:
			if (pausemenu == CONTINUE)
				pausemenu = MAINMENU;
			else
				pausemenu = CONTINUE;
			break;
		default:
			break;
		}
	}
	glutPostRedisplay();
}

void keyboardDown(unsigned char key, int x, int y) {
	if (gameStarted == false && optionBool == false && scoreboardBool == false) { //메인메뉴
		switch (key) {
		case ' ':
			switch (menu) {
			case PLAY:
				loop.createLoop(1); //1스테이지 생성
				stage = 1;
				playing_start_t = clock();
				loop.setGameOver(false); loop2.setGameOver(false);
				gameStarted = true;
				PlaySound(TEXT("source/sound/collision.wav"), NULL, SND_FILENAME | SND_ASYNC);//SND_ASYNC: 재생하는동안 프로그렘 실행, SND_SYNC :재생하는 동안 프로그렘 정지
				break;

			case OPTION:
				optionBool = true;
				break;

			case SCOREBOARD:
				scoreboardBool = true;
				break;

			case EXIT:
				exit(0);
				break;
			}
		}
	}
	else if (gameStarted == false && optionBool == true) { //옵션
		switch (key) {
		case ' ':
			switch (optionmenu) {
			case EASY: 
				optionDifficultyPos[0] = -197.5f; optionDifficultyPos[1] = -12.f;
				loop.setDifficulty(0.75f); loop2.setDifficulty(0.75f); //공 개수 0.75배
				break;

			case NORMAL:
				optionDifficultyPos[0] = -197.5f; optionDifficultyPos[1] = -72.f;
				loop.setDifficulty(1.f); loop2.setDifficulty(1.f); //공 개수 1배
				break;

			case HARD:
				optionDifficultyPos[0] = -197.5f; optionDifficultyPos[1] = -132.f;
				loop.setDifficulty(1.5f); loop2.setDifficulty(1.5f); //공 개수 1.5배
				break;

			case ON:
				optionMusicPos[0] = 342.5f; optionMusicPos[1] = -30.f;
				sound.playingBgm(true);
				break;
			case OFF:
				optionMusicPos[0] = 342.5f; optionMusicPos[1] = -90.f;
				sound.playingBgm(false);
				break;
			case BACK:
				optionBool = false;
				break;
			default:
				break;
			}
		}
	}
	else if (gameStarted == false && scoreboardBool == true) { //스코어보드
		switch (key) {
		case ' ':
			scoreboardBool = false; //스코어보드 나가기
			break;
		default:
			break;
		}
	}
	else if (gameStarted == true && gamePaused == true) { //퍼즈
		switch (key) {
		case ' ':
			switch (pausemenu)	
			{
			case CONTINUE:
				gamePaused = false;
				break;
			case MAINMENU:
				gameStarted = false;
				gamePaused = false;
				loop.createLoop(0);
				loop2.createLoop(0);
				break;
			}

		case 'p':
			gamePaused = false;
			break;

		default: 
			break;
		}
		glutPostRedisplay();
	}
	
	//rotating Canon (q=CCW, w=CW)
	else if (gameStarted == true && keyboardPause == false  && gamePaused == false) { //게임 중
		int	add = 3;
		switch (key) {
		case 'q':
			cout << "CCW" << endl;
			canon.adjustAngle(add);
			canon.setCanonLoadCenter();
			break;
		case 'w':
			cout << "CW" << endl;
			canon.adjustAngle(-add);
			canon.setCanonLoadCenter();
			break;
		case ' ':
			cout << "spacebar" << endl;
			if (!canon.isCanonFired()) {
				sound.playingFireSfx();
				cout << "Fired" << endl;
				vector<int> colors1 = loop.getColorIndexes();
				vector<int> colors2 = loop2.getColorIndexes();
				colors1.insert(colors1.end(), colors2.begin(), colors2.end());
				sort(colors1.begin(), colors1.end());
				colors1.erase(unique(colors1.begin(), colors1.end()), colors1.end());
				
				canon.setColorIndexVec(colors1);
				canon.fire();
			}
			break;
		case 'p':
			gamePaused = true;
			pausemenu = CONTINUE;
			break;
		}
	}
	glutPostRedisplay();
}

void initialize() {
	cout << "Loading..." << endl;
	light.setAmbient(0.5f, 0.5f, 0.5f, 1.0f);
	light.setDiffuse(0.7f, 0.7f, 0.7f, 1.0f);
	light.setSpecular(1.0f, 1.0f, 1.0f, 1.0f);

	loop.createLoop(0);
	loop2.createLoop(0);//void loop
	canon.createCanon();
	canonTexture.initializeTexture("source/snu.png");
	optionTexture.initializeTexture("source/option.png");
	pauseTexture.initializeTexture("source/pause.png");
	pause_keyTexture.initializeTexture("source/pause_key.png");
	scoreboardTexture.initializeTexture("source/scoreboard.png");

	menuTexture.reserve(299);
	for (int i = 0; i < 299; ++i) {
		Texture t;
		t.initializeTexture("source/mainmenu/" + to_string(i) + ".png");
		menuTexture.push_back(t);
	}

	sound.playingBgm(true);
	cout << "Done!" << endl;
}

void drawPause() {
	int imageWidth = 500; int imageHeight = 600;
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, pauseTexture.getTextureID());
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-imageWidth / 2, -imageHeight / 2, 30);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-imageWidth / 2, imageHeight / 2, 30);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(imageWidth / 2, imageHeight / 2, 30);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(imageWidth / 2, -imageHeight / 2, 30);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPushMatrix();
	glTranslatef(-140, -132 - 65 * pausemenu, 30);
	glRotatef(45, 0, 1, 0);
	glRotatef(-45, 0, 0, 1);
	glRotatef(rotateTetrahedron, 1, 1, 1);
	glScalef(25, 25, 25);
	glLineWidth(1.f);
	glColor3f(1, 1, 1);
	glutWireTetrahedron();
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(-140, -132 - 65 * pausemenu, 30);
	glRotatef(45, 0, 1, 0);
	glRotatef(-45, 0, 0, 1);
	glRotatef(rotateTetrahedron, 1, 1, 1);
	glScalef(25, 25, 25);
	glLineWidth(1.f);
	glColor3f(1, 1, 1);
	glutWireTetrahedron();
	glPopMatrix();

}

void drawMenu() {
	drawMenuTexture(menuIdx);

	glPushMatrix();
	glTranslatef(-260, -70-80*menu, 0);
	glRotatef(45, 0, 1, 0);
	glRotatef(-45, 0, 0, 1);
	glRotatef(rotateTetrahedron, 1,1,1);
	glScalef(40, 40, 40);
	glLineWidth(1.5f);
	glColor3f(1, 1, 1);
	glutWireTetrahedron();
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(-260, -70 - 80 * menu, 0);
	glRotatef(45, 0, 1, 0);
	glRotatef(-45, 0, 0, 1);
	glRotatef(rotateTetrahedron, 1, 1, 1);
	glScalef(40, 40, 40);
	glLineWidth(1.5f);
	glColor3f(1, 1, 1);
	glutWireTetrahedron();
	glPopMatrix();
}

void drawScoreboard() {
	int imageWidth = 1200; int imageHeight = 800;
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, scoreboardTexture.getTextureID());
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(-imageWidth / 2, -imageHeight / 2);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(-imageWidth / 2, imageHeight / 2);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(imageWidth / 2, imageHeight / 2);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(imageWidth / 2, -imageHeight / 2);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//커서
	glPushMatrix();
	glTranslatef(320, -287, 0);
	glRotatef(180, 0, 1, 0);
	glRotatef(45, 0, 1, 0);
	glRotatef(-45, 0, 0, 1);
	glRotatef(rotateTetrahedron, 1, 1, 1);
	glScalef(30, 30, 30);
	glColor3f(1, 1, 1);
	glLineWidth(1.2f);
	glutWireTetrahedron();
	glPopMatrix();

	//점수표시~
}

void drawOption() {
	int imageWidth = 1200; int imageHeight = 800;
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, optionTexture.getTextureID());
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(-imageWidth / 2, -imageHeight / 2);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(-imageWidth / 2, imageHeight / 2);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(imageWidth / 2, imageHeight / 2);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(imageWidth / 2, -imageHeight / 2);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	int x = -150, y = 126;
	switch (optionmenu)
	{
	case EASY: x = -130, y = -5;
		break;
	case NORMAL: x = -130, y = -65;
		break;
	case HARD: x = -130, y = -125;
		break;
	case ON: x = 410, y = -23;
		break;
	case OFF: x = 410, y = -83;
		break;
	case BACK: x = 320, y = -287;
		break;
	default:
		break;
	}
	//커서
	glPushMatrix();
	glTranslatef(x, y, 0);
	glRotatef(180, 0, 1, 0);
	glRotatef(45, 0, 1, 0);
	glRotatef(-45, 0, 0, 1);
	glRotatef(rotateTetrahedron, 1, 1, 1);
	glScalef(30, 30, 30);
	glColor3f(1, 1, 1);
	glLineWidth(1.2f);
	glutWireTetrahedron();
	glPopMatrix();

	//체크무늬
	glPushMatrix();
	glTranslatef(optionDifficultyPos[0], optionDifficultyPos[1], 0);
	glLineWidth(6.f);
	glBegin(GL_LINE_STRIP);
	glColor3f(1, 0.3, 0.15);
	glVertex3f(-8, 17, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(15.5, 35, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(optionMusicPos[0], optionMusicPos[1], 0);
	glLineWidth(6.f);
	glBegin(GL_LINE_STRIP);
	glColor3f(0.1, 0.3, 1);
	glVertex3f(-8, 17, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(15.5, 35, 0);
	glEnd();
	glPopMatrix();

}

void menuIdleFunc() {
	if (end_t - start_t > 1000 / 30) {

		rotateTetrahedron += 5;
		menuIdx++;
		if (menuIdx == 299)
			menuIdx = 0;


		start_t = end_t;
	}
}

void inGameIdleFunc() {
	if (end_t - playing_start_t < 1000) {
		gameSpeed = 10;
		keyboardPause = true;
	}
	else {
		gameSpeed = 1;
		keyboardPause = false;
	}

	if (end_t - start_t > 1000 / gameSpeed / 60) {
		if (canon.isCanonFired()) {
			canon.moveLaunchSphere();
			handleCollision(canon.getSphere(), loop.getSphereVector());
			handleCollision2(canon.getSphere(), loop2.getSphereVector());

			if (canon.boundaryDetection()) { canon.ReadyToFire(); }
		}
		if (loop.getGameOver() != true && loop2.getGameOver() != true && stage != 4) {
			loop2.moveSphere();
			loop.moveSphere();
		}


		if (loop.getSphereVector().size() == 2 && stage == 1) {
			stage = 2;
			Sleep(300);
			loop.createLoop(2);
			playing_start_t = clock();
			PlaySound(TEXT("source/sound/stageAdvance.wav"), NULL, SND_FILENAME | SND_ASYNC);//SND_ASYNC: 재생하는동안 프로그렘 실행, SND_SYNC :재생하는 동안 프로그렘 정지
		}
		else if (loop.getSphereVector().size() == 2 && stage == 2) {
			stage = 3;
			loop.createLoop(3);
			Sleep(300);
			loop2.createLoop(4);
			playing_start_t = clock();
			PlaySound(TEXT("source/sound/stageAdvance.wav"), NULL, SND_FILENAME | SND_ASYNC);//SND_ASYNC: 재생하는동안 프로그렘 실행, SND_SYNC :재생하는 동안 프로그렘 정지
		}
		else if (stage == 3 && loop.getSphereVector().size() == 2 && loop2.getSphereVector().size() == 2) {
			stage = 4; //All-clear
			Sleep(250);
			PlaySound(TEXT("source/sound/clear.wav"), NULL, SND_FILENAME | SND_ASYNC);//SND_ASYNC: 재생하는동안 프로그렘 실행, SND_SYNC :재생하는 동안 프로그렘 정지
		}

		start_t = end_t;
	}
}


void idle() {
	end_t = clock();

	if (gameStarted == false || gamePaused == true)
		menuIdleFunc();
	else if(gameStarted == true && gamePaused == false)
		inGameIdleFunc();


	glutPostRedisplay();
}

void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-boundaryX, boundaryX, -boundaryY, boundaryY, -100.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	light.draw();

	if (gameStarted == false && optionBool == false && scoreboardBool == false) {
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);
		drawMenu();
	}
	else if (gameStarted == false && optionBool == true) {
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);
		drawOption();
	}
	else if (gameStarted == false && scoreboardBool == true) {
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);
		drawScoreboard();
	}

	else if (gameStarted == true) {
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		canon.draw();
		drawCanonWithTexture();
		drawPauseKeyTexture();
		switch (stage)
		{
		case 1:
			loop.draw();
			break;
		case 2:
			loop.draw();
			break;
		case 3:
			loop.draw();
			loop2.draw();
			break;
		case 4:
			glColor3f(1, 1, 1);
			displayCharacters(GLUT_BITMAP_TIMES_ROMAN_24, "ALL CLEAR!" , -55.f,150);
			break;
		default:
			break;
		}

		glColor3f(1, 1, 1);
		displayCharacters(GLUT_BITMAP_TIMES_ROMAN_24, "Score : " + std::to_string(loop.getScore() + loop2.getScore()), -20.f, -300.f);
	}

	if (gamePaused == true) {
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);
		drawPause();
	}


	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	

	glutSwapBuffers();
}

int main(int argc, char** argv) {
	// init GLUT and create Window
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(200, 20);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Puzz Loop!");
	initialize();

	// register callbacks
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboardDown);
	glutSpecialFunc(specialKeyboardDown);
	glutIdleFunc(idle);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}
