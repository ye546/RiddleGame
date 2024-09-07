#pragma once
#include "GameLoopManager.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <limits>

GameLoopManager::GameLoopManager() 
{
	//Start();
}

GameLoopManager::~GameLoopManager() 
{
	std::cin.get(); // To wait for user input before exiting
	// Destructor implementation
}

void GameLoopManager::Start() 
{
	// Game loop condition
	std::string ReturnString;
	std::string UserInput;
	char GC = 0;

	std::vector<std::string> GameCommands
	{
		"1. Spela", 
		"2. Logga in",
		"3. Skapa ny användare",
		"4. Spela som gäst",
		"5. Visa toppoäng",
		"6. Visa spelregler",
		"7. Visa användarinformation",
		"8. Avsluta spelet" 
	};

	// Game loop
	do 
	{
		for (auto& cli : GameCommands)
			std::cout << cli << "\n";

		//Get user input to load func.
		std::cin >> GC;

		switch (GC)
		{
		case '1':
			Play();
			break;
		case '2':
			Login();
			break;
		case '3':
			RegisterNewUser();
			break;
		case '4':
			PlayAsGuest();
			break;
		case '5':
			DisplayHighscore();
			break;
		case '6':
			DisplayGameRules();
			break;
		case '7':
			GetUserAccountInfo();
			break;
		case '8':
			GameLoopManager::~GameLoopManager();
			break;
		default:
			
			std::cout << "Faulty command, retry...\n";
			break;
		}

	} while (ReturnString != QUIT);  // Check for both "quit" and "finish"
}

void GameLoopManager::Play()
{
	ClearScreen();
}

void GameLoopManager::Login()
{
	ClearScreen();
}

void GameLoopManager::PlayAsGuest()
{
	ClearScreen();
}

void GameLoopManager::RegisterNewUser() //TODO fix this fucking function..
{
	//CLS & buffer
	
	//	TODO
	//	1. Fix reading current users so no duplicates can be made - DONE
	//	2. Fix pin requirment check - it's fucked - DONE
	//	3. Improve case sensitivity and perhaps introduce an ID-system to allow users with the same names...
	

	//Create the new user object
	struct UserAccountData NewUser;
	int CheckSum = 0;

	Print("Set a username: "); std::getline(std::cin, NewUser.name);
	if (CheckSum = CheckIfUsernameIsTaken(NewUser) == 1)
	{
		Print("Username is already taken, try again(press any key to continue)...");

		ClearCinBuffer();
		RegisterNewUser();
		return;
	}

	Print("Set a pincode (requirment: >=4 and <=12: "); std::getline(std::cin, NewUser.pincode);
	if (CheckSum = CheckPinRequirments(NewUser) == 1)
	{
		Print("Pincode has too few characters, try again(press any key to continue)...");
		ClearCinBuffer();
		RegisterNewUser();
		return;
	}
	else if (CheckSum = CheckPinRequirments(NewUser) == 2)
	{
		Print("Pincode has too many characters, try again(press any key to continue)...");
		ClearCinBuffer();
		RegisterNewUser();
		return;
	}

	Print("Useraccount created.\n");


	//set default points to 0

	//Save the new user to UserAccounts.csv
	std::fstream NewUserAccount("UserAccounts.csv", std::fstream::app);
	std::string temp = NewUser.name + ";" + NewUser.pincode + ";" + "0" + "\n";
	if (NewUserAccount.is_open())
	{
		NewUserAccount << temp;

	}
	//Close the file:
	NewUserAccount.close();
}

//prints \n
void GameLoopManager::PrintNL(int count)
{
	for (int i = 0; i < count; i++)
		std::cout << "\n";
}

//Never prints \n at end of message
void GameLoopManager::Print(std::string message)
{
	std::cout << message;
}

std::string GameLoopManager::GetUserInput()
{
	std::string input;
	std::getline(std::cin, input);
	std::cin.ignore();
	return input;
}

void GameLoopManager::DisplayHighscore()
{
	ClearScreen();
}

void GameLoopManager::DisplayGameRules()
{
	ClearScreen();
	std::cout <<
		"---- Game rules ----\n\n"
		<< "Lorem ipsum....." <<

		std::endl;
}

void GameLoopManager::GetUserAccountInfo()
{
	ClearScreen();
}

void GameLoopManager::ClearScreen()
{
	std::cout << "\033[2J\033[1;1H"; // ANSI escape code to clear screen;
	//std::cin.clear(); //clear buffer
// Limit the use of std::numeric_limits to the local scope
//using std::numeric_limits; // Import numeric_limits into local scope
	//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int GameLoopManager::CountLinesInCSV(const std::string filename) 
{
	std::ifstream file(filename);
	int lineCount = 0;

	if (!file.is_open()) {
		//std::cout << "Error opening file: " << filename << std::endl;
		return -1;
	}
	else
	{
		//std::cout << "opening file: " << filename << std::endl;
		std::string line;
		while (std::getline(file, line)) {
			++lineCount;
		}
		//std::cout << "closing file: " << filename << std::endl;
		//std::cout << "file line counter: " << lineCount << std::endl;
		file.close();
	}

	return lineCount;
}

//Load riddles
std::vector<GameLoopManager::RiddleData> GameLoopManager::GetAllRiddles()
{
	std::string filename = RIDDLE_FILE;
	int lineCount = CountLinesInCSV(filename);
	//variables
	std::fstream RiddleFile(filename, std::fstream::in); // I/O to open the CSV-file with all the riddles.
	std::vector<GameLoopManager::RiddleData> RiddleVector;

	if (lineCount != -1 && RiddleFile.is_open())
	{
		for (int i = 0; i < lineCount; i++)
		{
			GameLoopManager:RiddleData riddle;
			std::getline(RiddleFile, riddle.RiddleName, ';');
			std::getline(RiddleFile, riddle.RiddleQuestion, ';');
			std::getline(RiddleFile, riddle.RiddleAnswer, ';');
			std::getline(RiddleFile, riddle.Category, ';');
			std::getline(RiddleFile, riddle.Difficulty, ';');
			std::getline(RiddleFile, riddle.PointsGiven, '\n');

			if (RiddleFile.eof() || RiddleFile.fail()) 
			{
				break; // Exit the loop if we reach the end of the file or encounter an error
			}

			RiddleVector.push_back(riddle);
		}
	}

	return RiddleVector;
}

std::vector<GameLoopManager::UserAccountData> GameLoopManager::GetAllRegisteredUsers()
{
	std::string filename = USER_FILE;
	//Read all accounts from master file
	std::fstream UserAccountData(filename, std::fstream::in); // I/O to open the CSV-file with all the riddles.
	
	//Create a vector of UserAccountData to read all accounts
	std::vector<GameLoopManager::UserAccountData> Users;

	int lineCount = CountLinesInCSV(filename);

	if (lineCount != -1 && UserAccountData.is_open())
	{
		for (int i = 0; i < lineCount; i++)
		{
			GameLoopManager::UserAccountData account_data;
			std::getline(UserAccountData, account_data.name, ';');
			std::getline(UserAccountData, account_data.pincode, ';');
			std::getline(UserAccountData, account_data.points, '\n');

			if (UserAccountData.eof() || UserAccountData.fail())
			{
				break; // Exit the loop if we reach the end of the file or encounter an error
			}

			Users.push_back(account_data);
		}
	}

	return Users;
}

void GameLoopManager::DisplayUsersNeatly()
{
	std::vector<GameLoopManager::UserAccountData> vec = GetAllRegisteredUsers();
	
	//always remove first input
	if (!vec.empty())
		vec.front() = std::move(vec.back()); vec.pop_back();
	
	Print("--- All registered users ---");
	PrintNL(1);

	for (auto& t : vec)
	{
		Print("Username: ");
		Print(t.name);
		PrintNL(1);
		Print("Pincode: ");
		Print(t.pincode);
		PrintNL(1);
		Print("Points: ");
		Print(t.points);
		PrintNL(1);
		Print("------------");
		PrintNL(1);
	}
}

//TODO: Fix this function, it displays last riddle as first, think the "remove first input" is fucked?
void GameLoopManager::DisplayRiddlesNeatly()
{
	std::vector<GameLoopManager::RiddleData> vec = GetAllRiddles();
	
	//always remove first input
	if (!vec.empty())
		vec.front() = std::move(vec.back()); vec.pop_back();

	Print("--- All riddles ---");
	PrintNL(1);

	for (auto& t : vec)
	{
		Print("Riddle name: ");
		Print(t.RiddleName);
		PrintNL(1);
		Print("Riddle question: ");
		Print(t.RiddleQuestion);
		PrintNL(1);
		Print("Riddle answer: ");
		Print(t.RiddleAnswer);
		PrintNL(1);
		Print("Category: ");
		Print(t.Category);
		PrintNL(1);
		Print("Difficulty: ");
		Print(t.Difficulty);
		PrintNL(1);
		Print("pointsGiven: ");
		Print(t.PointsGiven);
		PrintNL(1);

		Print("------------");
		PrintNL(1);
	}
}

int GameLoopManager::CheckIfUsernameIsTaken(struct GameLoopManager::UserAccountData User)
{
	std::vector<GameLoopManager::UserAccountData> CurrentUsers = GetAllRegisteredUsers();

	for (auto& t : CurrentUsers)
	{
		if (t.name == User.name)
		{
			return 1;
		}
	}

	return 0;
}

int GameLoopManager::CheckPinRequirments(struct GameLoopManager::UserAccountData User)
{
	/*std::string* buf[sizeof(std::string) / sizeof(User.pincode)];

	for (auto& c : buf)
	{
		if(c)
	}
	*/

	if (User.pincode.length() < 4)
	{
		return 1;
	}
	else if (User.pincode.length() > 12)
	{
		return 2;
	}

	return 0;
}

void GameLoopManager::ClearCinBuffer()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int GameLoopManager::UpdateUser(struct GameLoopManager::UserAccountData User)
{
	//TODO: find the users line-pos in the csv-file and replace with updated data.
	
	
	//Look for the user in the database
	std::vector<GameLoopManager::UserAccountData> AllUsers = GetAllRegisteredUsers();
	
	for (auto& u : AllUsers)
	{
		if (u.name == User.name)
		{
			u.points = User.points;
		}
	}

	//Update the position in the csv-file
	std::ifstream file(USER_FILE);
	int lineCount = 0;

	if (!file.is_open()) {
		//std::cout << "Error opening file: " << filename << std::endl;
		return -1;
	}
	else
	{
		//std::cout << "opening file: " << filename << std::endl;
		//std::string line;
		//while (std::getline(file, line)) {
		//	if(line.)
		//	++lineCount;
		//}
		//std::cout << "closing file: " << filename << std::endl;
		//std::cout << "file line counter: " << lineCount << std::endl;
		file.close();
	}

	return lineCount;

	std::fstream();
}