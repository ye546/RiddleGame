#pragma once
#include "GameLoopManager.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

GameLoopManager::GameLoopManager() 
{
	
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

void GameLoopManager::RegisterNewUser()
{
	ClearScreen();

	//get all users
	struct UserAccountData new_user;
	int AmountOfUsers = 0; //user counter
	std::vector<GameLoopManager::UserAccountData> CurrentUsers = AppendUserAccountsToVector("UserAccounts.csv", AmountOfUsers);

	Print("--- Create a new user ---");
	PrintNL(1);
	Print("Give a username: ");
	new_user.name = GetUserInput();
	PrintNL(1);
	Print("Set a security pin for your user account.\n");
	Print("Security pin requirments are:\n");
	Print("1. Can be anything\n");
	Print("2. Must be 8 chars long\n");
	Print("Enter pin: "); 
	retry_pin:
	new_user.pincode = GetUserInput();
	
	//Check if useraccount already is taken
	if (!(CurrentUsers.empty()))
	{
		bool taken = 0;
		
		for (auto& users : CurrentUsers)
		{
			if (users.name == new_user.name)
			{
				Print("The given username is already taken, please try again.");
				taken = 1;
				break;
			}
			else
				break;
		}

		//Restart the account registration
		if(taken)
			RegisterNewUser();
	}

	//Check if pin meets requirments
	if (!(new_user.pincode.length() < 8 || new_user.pincode.length() > 8))
	{
		Print("The pincode does not match the requirments, try again:");
		new_user.pincode = "";
		goto retry_pin;
	}

	//verify
	/*Print("You are about to create a new account:");
	Print("Name: "); Print(new_user.name);
	Print("Pincode: "); Print(new_user.pincode);
	PrintNL(2);
	Print("confirm? (yes/no) Y/N");
	std::string confirm = GetUserInput();

	if()*/

	Print("Useraccount created.\n");
	Print(new_user.name);
	Print(new_user.pincode);

	//set default points to 0
	new_user.points = "0";

	//Save the new user to UserAccounts.csv
	std::fstream NewUserAccount("UserAccounts.csv", std::fstream::app);

	NewUserAccount << new_user.name << ";" << new_user.pincode << ";" << new_user.points << "\n";
	
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
	std::cin.ignore(); //clear buffer
}

int GameLoopManager::CountRiddlesInCSV(const std::string filename) 
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
std::vector<GameLoopManager::RiddleData> GameLoopManager::AppendRiddlesToVector(std::string filename, const int lineCount) 
{
	
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
			std::getline(RiddleFile, riddle.RiddleAnswer, '\n');

			if (RiddleFile.eof() || RiddleFile.fail()) 
			{
				break; // Exit the loop if we reach the end of the file or encounter an error
			}

			RiddleVector.push_back(riddle);
		}
	}

	return RiddleVector;
}

std::vector<GameLoopManager::UserAccountData> GameLoopManager::AppendUserAccountsToVector(std::string filename, const int lineCount)
{

	//variables
	std::fstream UserAccountData(filename, std::fstream::in); // I/O to open the CSV-file with all the riddles.
	std::vector<GameLoopManager::UserAccountData> UserAccountVector;

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

			UserAccountVector.push_back(account_data);
		}
	}

	return UserAccountVector;
}

void GameLoopManager::DisplayUsersNeatly(std::vector<GameLoopManager::UserAccountData> vec)
{
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