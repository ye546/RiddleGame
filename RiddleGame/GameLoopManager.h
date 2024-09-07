#pragma once
#include "SFML/Graphics.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

#define QUIT "quit"

class GameLoopManager
{
private:


public:
	GameLoopManager();
	~GameLoopManager();
	
	/*Struct(s)*/
	struct RiddleData
	{
		std::string RiddleName;
		std::string RiddleQuestion;
		std::string RiddleAnswer;
		//int complexity 1, 2, 3;
	};

	struct UserAccountData
	{
		std::string name;
		std::string pincode;
		std::string points;
	};


	/*Funtion(s)*/
	void Play();
	void Print(std::string message);
	void PrintNL(int count);
	void Login();
	void Start();
	void QuitGame();
	void PlayAsGuest();
	void ClearScreen();
	void RegisterNewUser();
	void DisplayHighscore();
	void DisplayGameRules();
	void GetUserAccountInfo();
	void DisplayUsersNeatly(std::vector<GameLoopManager::UserAccountData> vec);
	std::string GetUserInput();


	/*Vector(s)*/
	//std::vector<GameLoopManager::RiddleData> RiddleVector;
	std::vector<GameLoopManager::RiddleData> AppendRiddlesToVector(std::string filename, const int lineCount);
	std::vector<GameLoopManager::UserAccountData> AppendUserAccountsToVector(std::string filename, const int lineCount);

	int CountRiddlesInCSV(const std::string filename);
	std::vector<GameLoopManager::RiddleData> RiddleVector;
};

