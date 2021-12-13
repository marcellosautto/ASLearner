#include "pch.h"
#include "UserData.h"

static bool sortScore(const ScoreStruct& a, const ScoreStruct& b)
{
	return a.score > b.score;
}

UserData::UserData()
{
	string input = currentUser = "";
	int inputI = 0;

	ifstream inFile("Assets/userdata.txt");
	if (inFile.fail())
		errorMessageExit("Failed To Open userdata.text");

	while (inFile >> input && input != ";") {
		inFile >> inputI;
		assistedScores.emplace_back(input, inputI);
	}

	while (inFile >> input && input != ";") {
		inFile >> inputI;
		nonAssistedScores.emplace_back(input, inputI);
	}
	inFile.ignore(1, '\n');

	while (!inFile.eof()) {
		string userName;
		getline(inFile, userName);
		keys.emplace_back(userName);
		database.emplace(userName, UserDataBase());
		database.at(userName).Username = userName;
		inFile >> input;
		database.at(userName).assistance = stoi(input);
		while (inFile >> input && input != ";")
			database.at(userName).remainingLetters.emplace_back(input.at(0));
		while (inFile >> input && input != ";")
			database.at(userName).failedLetters.emplace_back(input.at(0));
		while (inFile >> input && input != ";")
			database.at(userName).assistedScores.emplace_back(stoi(input));
		while (inFile >> input && input != ";")
			database.at(userName).nonAssistedScores.emplace_back(stoi(input));
		if (!inFile.eof())
			getline(inFile, userName);
	}
	login("");
}

UserData::~UserData()
{
	ofstream outFile("Assets/userdata.txt");
	if (outFile.fail())
		errorMessageExit("Failed To Open userdata.text");

	for (int i = 0; i < assistedScores.size(); i++)
		outFile << assistedScores.at(i).username << " " << assistedScores.at(i).score << " ";
	outFile << " ;\n";
	for (int i = 0; i < nonAssistedScores.size(); i++)
		outFile << nonAssistedScores.at(i).username << " " << nonAssistedScores.at(i).score << " ";
	outFile << " ;";
	for (int i = 0; i < keys.size(); i++) {
		string userName = keys.at(i);
		outFile << "\n" << userName << "\n";
		outFile << database.at(userName).assistance << "\n";
		for (int j = 0; j < database.at(userName).remainingLetters.size(); j++)
			outFile << database.at(userName).remainingLetters.at(j) << " ";
		outFile << ";\n";
		for (int j = 0; j < database.at(userName).failedLetters.size(); j++)
			outFile << database.at(userName).failedLetters.at(j) << " ";
		outFile << ";\n";
		for (int j = 0; j < database.at(userName).assistedScores.size(); j++)
			outFile << database.at(userName).assistedScores.at(j) << " ";
		outFile << ";\n";
		for (int j = 0; j < database.at(userName).nonAssistedScores.size(); j++)
			outFile << database.at(userName).nonAssistedScores.at(j) << " ";
		outFile << ";";
	}
}

bool UserData::login(string _username)
{
	currentUser = _username;
	if (database.find(_username) == database.end()) {
		database.emplace(_username, UserDataBase());
		if (_username != "")
			keys.emplace_back(_username);
		UDB = &database.at(currentUser);
		return true;
	}
	UDB = &database.at(currentUser);
	if (UDB->remainingLetters.size() > 0 || UDB->failedLetters.size() > 0)
		UDB->fail = true;
	return false;
}

bool UserData::saveScore() {

	vector<ScoreStruct>* allScores = NULL;
	vector<int>* userScores = NULL;

	int assistance = UDB->assistance,
		score = UDB->score;

	if (assistance == 2) {
		userScores = &UDB->assistedScores;
		allScores = &assistedScores;
	}
	else if (assistance == 3) {
		userScores = &UDB->nonAssistedScores;
		allScores = &nonAssistedScores;
	}

	userScores->push_back(score);
	if (currentUser != "")
		allScores->push_back({ currentUser, score });
	sort(userScores->begin(), userScores->end(), greater<int>());
	sort(allScores->begin(), allScores->end(), sortScore);
	int uSize = userScores->size(), aSize = allScores->size();
	if (uSize > 3 && userScores->at(uSize - 1) == score) {
		userScores->pop_back();
		return false;
	}
	else if (uSize > 3)
		userScores->pop_back();
	if (aSize > 3 && allScores->at(aSize - 1).score == score) {
		allScores->pop_back();
		return false;
	}
	else if (aSize > 3)
		allScores->pop_back();

	return true;
}

string UserData::scoresToString()
{
	string scores;
	vector<int> scoresTemp;
	vector<ScoreStruct> scoreStructTemp;

	int assistance = UDB->assistance;

	if (assistance < 2)
		assistance = 2;

	if (assistance == 2) {
		scores += "With Assistance\n";
		scoresTemp = UDB->assistedScores;
	}
	else if (assistance == 3) {
		scores += "Without Assistance\n";
		scoresTemp = UDB->nonAssistedScores;
	}

	if (scoresTemp.size() != 0) {
		scores += "Your Scores\n";
		for (int i = 0; i < scoresTemp.size(); i++)
			scores += to_string(scoresTemp.at(i)) + "\n";
	}

	scores += "All Scores\n";

	if (assistance == 2)
		scoreStructTemp = assistedScores;
	else if (assistance == 3)
		scoreStructTemp = nonAssistedScores;

	if (scoreStructTemp.size() != 0)
		for (int i = 0; i < scoreStructTemp.size(); i++)
			scores += to_string(scoreStructTemp.at(i).score) + ": " + scoreStructTemp.at(i).username + "\n";
	else
		scores += "\nNo High Scores!";


	return scores;
}

int* UserData::getAssistance()
{
	return &UDB->assistance;
}

int* UserData::getScore()
{
	return &UDB->score;
}

vector<char>* UserData::getRemainingLetters()
{
	return &UDB->remainingLetters;
}

vector<char>* UserData::getFailedLetters()
{
	return &UDB->failedLetters;
}

bool* UserData::getFailed()
{
	return &UDB->fail;
}

void UserData::genRemainingLetters(bool test)
{
	UDB->remainingLetters.clear();
	UDB->failedLetters.clear();
	for (int i = 122; i > 96; i--)
		UDB->remainingLetters.push_back(char(i));

	random_device rd;
	mt19937 g(rd());

	if (test)
		shuffle(UDB->remainingLetters.begin(), UDB->remainingLetters.end(), g);
}

void UserData::genFailLetters()
{
	if (UDB->remainingLetters.size() == 0 && UDB->failedLetters.size() != 0)
		while (UDB->failedLetters.size() != 0) {
			UDB->remainingLetters.push_back(UDB->failedLetters.at(UDB->failedLetters.size() - 1));
			UDB->failedLetters.pop_back();
		}
}

//display username with high scores//
//new buttons//
// //login in as guest//
// //login screen move //
//Highscore screen when assistance <2//
//Highscore switch assistance//
//Letter Shuffle//
// Failed redo///
//Save prog//
//Pretty GUI//
//display username in menus
//High score assistance swtich//
//random test//
//lib cleanup//
