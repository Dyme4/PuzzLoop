#include "scoreboard.h"

void scoreboard::write(string name, int score) {
	ofstream fout("source/scoreboard.txt", std::ios_base::app);
	fout << name << " " << score<<"\n";
	fout.close();
}

bool compare(player a, player b) {
	return a.getScore() > b.getScore();
}

void scoreboard::load() {
	players.clear();
	ifstream fin("source/scoreboard.txt");
	string name;
	int score;
	string someVar;

	while (fin >> name) {
		fin >> score; 
		players.push_back(player(name, score));
	}
	fin.close();
	sort(players.begin(), players.end(), compare);

	if (players.size() < 3) {
		for (int i = 0; i < (3 - players.size()); i++) {
			players.push_back(player("---", 0));
		}
	}
}

void scoreboard::clearBoard() {
	ofstream fout("source/scoreboard.txt");
	fout.close();
}
player scoreboard::operator[](const int i) {
	return players[i];
}
