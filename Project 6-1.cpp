//Brian Bredahl
//November 3, 2019
//Project 6
//Programming Challenges 24 - page 379

/*
Chapter6
Programming Challenges
24. Rock, Paper, Scissors Game

Write a program that lets the user play the game of Rock, Paper, Scissors against the
computer. The program should work as follows:

	1. When the program begins, a random number in the range of 1 through 3 is
	   generated. If the number is 1, then the computer has chosen rock, If the number
	   is 2, then the computer has chosen paper. If the number is 3, then the computer
	   has chosen scissors. {Don't display the computer's choice yet.}
	
	2. The user enters his or her choice of "rock", "paper", or "scissors" at the
	   keyboard. (You can use a menu if you prefer.)

	3. The computer's choice is displayed.

	4. A winner is selected according to the following rules:

		-If one player chooses rock and the other player chooses scissors, then rock
		 wins. (The rock smashes the scissors.)

		-If one player chooses scissors and the other player chooses paper, then
		 scissors wins. (Scissors cuts paper.)

		-If one player chooses paper and the other player chooses rock, then paper
		 wins. (Paper wraps rock.)

		-If both players make the same choice, the game must be played again to
		 determine the winner.

	Be sure to divide the program into functions the perform each major task.

Make sure to have one function displaying the menu (scissors, paper, or rock), reading the choice, 
validating it and rereading if needed, and then returning the valid choice as a number 1-3.

Make sure to have another function to which you send what the user selected and what computer 
generated, and the function will declare the winner printing the result.

Make sure to use srand()--------
*/

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <array>
#include <stdlib.h>
#include <ctime>

using std::cout;
using std::left;
using std::cin;
using std::setw;
using std::fixed;
using std::setprecision;
using std::string;
using std::vector;
using std::array;
using std::srand;
using std::rand;
using std::time;
using std::endl;


// used to associate strings Rock, Paper, and Scissors with a number so that they can be easily called upon
const int RPS_SIZE = 3;
const string RPS[RPS_SIZE] = { "ROCK", "PAPER", "SCISSORS" };

struct GameData {
	string UserChoice;
	string ComputerChoice;
	int gamecount;
	int wins;
	int losses;
	int ties;
}PlayGame;

// used for the computers selction of rock paper or scissors based on a random number seeded by time
int ComputerSelection() {
	unsigned seed = time(0);					// used to seed the srand( for random numbers)
	srand(seed);								// used to seed rand
	int computer = (rand() % 3);				// assigns a random number between 0 and 2 to computer
	PlayGame.ComputerChoice = RPS[computer];	// the string ComputerChoice apart of the global data structure PlayGame is assigned the string Rock, Paper, or Scissors 
	return computer;							// the number computer is returned to the main function
}

// used for the user input --> user enters a number between 1 and 3 --> input is checked --> strings are sent to the stuct playgame
int UserSelection() {
	int user, invalidCount = 5;													// user is for user input -- invalidCount is for the number of times the user input is invalid
	bool error;																	// used in the error catching step of this function
	string error_catcher;														// used in the error cathcing step of this function
	cout << "\n     Please Select Rock, Paper, or Scissors" << endl << endl;	// output to user
	for (int i = 0; i < 3; i++) {												//used to output all the options (ROCK, PAPER, & SCISSORS) to user
		cout << "\tPress\t" << i + 1 << "\tfor\t" << RPS[i] << endl;			// output to user
	}
	do {																		// will loop if the user input is invalid
		error = false;															// sets or resets error to false
		cout << "\n\tPlease make you selection now: ";							//output to user
		cin >> user;															//accepts input from user and assigns it to the variable user
		if (user < 1 || user > 3) {												// if the user input is outside the accepted range -- error catching --
			cin.clear();														// since the user input is out of range the input buffer is cleared
			getline(cin, error_catcher);										// if a string or character is entered it is removed from the buffer
			cout << endl << endl <<"\t    ERROR: Invalid Input" << endl << endl;//outputs error to the user
			error = true;														// sets error to true so that the user can enter a valid input
			cout << "   You have " << invalidCount-- << " more attempts to enter a vaild number" << endl << endl; // indicates how many more attempts the user has to enter valid input before the program exits
		}
		if (invalidCount < 0) {													// if the number of invalid inputs is less than zero then the program will exit
			exit(0);
		}
	} while (error == true);
	int stringset = user -1;													// sets the variable stringset to the users input - 1
	PlayGame.UserChoice = RPS[stringset];										// assigns the string UserChoice inside of the global data structure PlayGame to the string ROCK, PAPER, & SCISSORS
	return stringset;															// returns stringset to the main function
}

//outputs the outcome of the game to the user --> will cause main function to loop in a tie exists
bool Outcome(int UserInput, int ComputerInput) {
	PlayGame.gamecount += 1;				// increments the game count by one for game based stats at end of game
	cout << "\tYour Choice:\t  The Computer's Choice:" << endl		// displays your choice and the computers choice on screen
		<< "\t  " << setw(10) << left <<PlayGame.UserChoice << "\t\t" <<setw(10) << left << PlayGame.ComputerChoice << endl << endl;
	
	if (UserInput == 0 && ComputerInput == 2 || UserInput == 1 && ComputerInput == 0 || UserInput == 2 && ComputerInput == 1 ) { // will display if the user has won
		cout << "\t    Congratulations! You've Won!" << endl << endl;
		PlayGame.wins += 1; // increments the games won by user by 1
	}
	else if (UserInput == 0 && ComputerInput == 1 || UserInput == 1 && ComputerInput == 2 || UserInput == 2 && ComputerInput == 0) { // Will display if the user loses
		cout << "\t\t    You've Lost" << endl << endl;
		PlayGame.losses += 1; // increments the games lost by user by 1
	}
	else { // if the user ties the computer
		cout << "\tYou and the Computer have tied" << endl << endl;
		cout << "\tPlay again to determine the winner" << endl << endl;
		PlayGame.ComputerChoice.clear(); // clears the string in the data structure associated with the user's choice 
		PlayGame.UserChoice.clear(); // clears the string in the data structure associated with the computers choice
		PlayGame.ties += 1; // increments the game data for games tied by 1
		return true; // returns true to the main function so that the game can be played again so a winner can be decided
	}
	return false; // returns false so that the main function do not loop back so the game will be played again

}

//asks user if they want to play again
// basically the user inputs a character
//  if the input is invalid the user will be looped back to the beginning of the program so that they can enter a valid input
//   if the user fails to enter a valid input the program will exit
bool PlayAgain() {
	char input; 
	bool error;
	int invalidCount = 5;
	string error_catcher;
	cout << "\tWould You Like to Play the Game again?" << endl << endl;
	cout << "    Press [ Y ] to play again\tPress [ N ] to exit" << endl << endl;

	do {
		error = false;
		cout << "\t  Please make your selection now: ";
		cin >> input;
		getline(cin, error_catcher);
		if (error_catcher.empty() == true) {
			switch (input) {
			case 'y':
			case 'Y':
				
				return true;
				break;
			case 'n':
			case 'N':
				return false;
				break;
			default:
				cout << endl << "\t   Invalid input, Please try again\n" << endl;
				cout << "   You have " << invalidCount-- << " more attempts to enter a vaild number" << endl << endl;
				if (invalidCount < 0) {
					return false;
				}
				error = true;
			}
		}
		else {
			cout << endl << "\t   Invalid input, Please try again\n" << endl;
			error = true;
			cout << "   You have " << invalidCount-- << " more attempts to enter a vaild number" << endl << endl;
			if (invalidCount < 0) {
				return false;
			}
		}
	} while (error == true);
}

// formated out put of the game stats for games played
void GameStats() {
	cout << "\t\t\tGame Stats:\n";
	cout << "\n\tNumber of Games Played: \t" << PlayGame.gamecount << endl;
	cout << "\tNumber of Wins: \t\t" << PlayGame.wins << endl;
	cout << "\tNumber of Losses: \t\t" << PlayGame.losses << endl;
	cout << "\tNumber of Ties: \t\t" << PlayGame.ties << endl;
	double chancesOfWinning = (static_cast<double>(PlayGame.wins) / static_cast<double>(PlayGame.gamecount)) * 100;
	cout << "\tYour likelihood of Winning: \t" << fixed << setprecision(2) << chancesOfWinning << "%" << endl;
}

int main() {
	PlayGame.gamecount = 0;
	PlayGame.losses = 0;
	PlayGame.ties = 0;
	PlayGame.wins = 0;
	bool go_on = true;
	bool tie;
	int computer, user;
	cout << "\n     This is a game of Rock, Paper, Scissors" << endl;
	do {
		do {
			computer = ComputerSelection();
			user = UserSelection();
			system("CLS");
			tie = Outcome(user, computer);
		} while (tie == true);
		go_on = PlayAgain();
		system("CLS");
	} while (go_on == true);
	GameStats();
	return 0;
}
