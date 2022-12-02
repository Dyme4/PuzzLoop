#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class player {
public:
	player() {};
	player(string n, int s) : name(n), score(s) {};
	string getName() const {
		return name;
	}
	int getScore() const {
		return score;
	}
private:
	string name;
	int score;
};


class scoreboard
{
public:
	void write(string name,int score);
	void load();
	void clearBoard();
	player operator[](const int i);
private:
	vector<player> players;
};

