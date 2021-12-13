#pragma once
#include "pch.h"

struct UserDataBase {
	string Username;
	bool fail;
	int assistance,
		score;
	vector<char> remainingLetters, failedLetters;
	vector<int> assistedScores, nonAssistedScores;

	UserDataBase() {
		string Username = "";
		assistance = score = 0;
		fail = false;
	}
};

struct ScoreStruct {

	string username;
	int score;

	ScoreStruct() : username(""), score(0) {};
	ScoreStruct(string _username, int _score) : username(_username), score(_score) {};
};

class UserData {

public:
	UserData();
	~UserData();

	bool login(string _username),
		saveScore(),
		* getFailed();
	string scoresToString();
	int* getAssistance(),
		* getScore();

	vector<char> *getRemainingLetters(),
		* getFailedLetters();
	void genRemainingLetters(bool test),
		genFailLetters();

private:
	UserDataBase* UDB = NULL;
	unordered_map<string, UserDataBase> database;
	vector<ScoreStruct> assistedScores, nonAssistedScores;
	vector<string> keys;
	string currentUser;
};