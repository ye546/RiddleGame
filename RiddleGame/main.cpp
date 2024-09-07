#include "SFML/Graphics.hpp"
#include "GameLoopManager.h"
#include <iostream>
#include <string>

int main()
{
	GameLoopManager Handle;
	
    int counter = Handle.CountRiddlesInCSV("UserAccounts.csv");
    std::vector<GameLoopManager::UserAccountData> test = Handle.AppendUserAccountsToVector("UserAccounts.csv", counter);

    Handle.DisplayUsersNeatly(test);


    //Handle.Start();


}

/*not in use atm */

/*
    const std::string filename = "C:\Riddles.csv";

    const int counter = Handler.CountRiddlesInCSV(filename);

    std::vector<GameLoopManager::RiddleData> vector = Handler.AppendRiddlesToVector(filename, counter);

    if (vector.empty())
        std::cout << "The RiddleVector is empty, something wrong?\n";
    else
    {
        for (auto& riddle : vector) {
            std::cout << "Riddle Name: " << riddle.RiddleName << "\n";
            std::cout << "Riddle Question: " << riddle.RiddleQuestion << "\n";
            std::cout << "Riddle Answer: " << riddle.RiddleAnswer << "\n";
            std::cout << "---------------------------\n";
        }
    }

std::string Game()
{
    std::string Answer = "";
    char Retry = '\0';

    // Print the welcome text and the riddle
    std::cout << "Solve the riddle to access the secret sauce!\n\n"
        << "The riddle is as follows... \n\n-- What has hands and a face but can't hold anything or smile? --\n\n"
        << "You may give a free answer or a singular word - give it your best! :)\n\n"
        << "Answer: ";

    // Get the user input
    std::getline(std::cin, Answer);

    // Validate the user input
    if ((Answer.find("clock") != Answer.npos) || (Answer.find("Clock") != Answer.npos))
    {
        std::cout << "Your answer contains the word 'Clock'... you are correct!\n\n"
            << "Now, as promised, here is the secret sauce...\n\n"
            << "Go outside and get a life you cave-dwelling person! :)\n\n"
            << "Jk love ya kiss :*";

        return "finish";
    }
    else
    {
        std::cout << "Your answer does not seem to be correct... want to give it another go? :)\n(Y = yes, N = no) Y/N: ";
        std::cin >> Retry;
        std::cin.ignore();

        // Restart logic
        switch (Retry)
        {
        case 'Y':
        case 'y':
            return "retry";
        default:
            std::cout << "\n\nThanks for playing - better luck next time!\n\n";
            return "quit";
        }
    }

    return "finish"; // Unreachable but kept for completeness
}

*/
