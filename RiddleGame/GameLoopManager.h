#pragma once
#include "SFML/Graphics.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

#define QUIT "quit"
#define USER_FILE "UserAccounts.csv"
#define RIDDLE_FILE "Riddles.csv"

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
		std::string Category;
		std::string Difficulty;
		std::string PointsGiven;
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
	void DisplayUsersNeatly();
	void DisplayRiddlesNeatly();
	void ClearCinBuffer();
	std::string GetUserInput();


	int CheckIfUsernameIsTaken(struct GameLoopManager::UserAccountData User);
	int CheckPinRequirments(struct GameLoopManager::UserAccountData User);
	int CountLinesInCSV(const std::string filename);
	int SaveUser(struct GameLoopManager::UserAccountData User);
	int UpdateUser(struct GameLoopManager::UserAccountData User);

	/*Vector(s)*/
	//std::vector<GameLoopManager::RiddleData> RiddleVector;
	std::vector<GameLoopManager::RiddleData> GetAllRiddles();
	std::vector<GameLoopManager::UserAccountData> GetAllRegisteredUsers();

	
	std::vector<GameLoopManager::RiddleData> RiddleVector;

	//Typedefs


	//typedef std::vector<GameLoopManager::UserAccountData> userVec;
	//typedef std::vector<GameLoopManager::RiddleData> ridVec;
};

