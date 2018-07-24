#include <cstring>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <array>
#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include "LinkedList.h"

using namespace std;

void print(char*);
void addScore(int&, int);
void question(int, int, char *);
void undo(int*, int, int*, int&, char*, int&, int&);
void storeandAdd();
void Reset();

bool isGameOver = false;
bool isAdded = false;
int InputCount = 0; // count player time of input.
char Num[30]; //For store all Question Number.
int mark[99]; // store the score record for undo.
int comboRecord[99]; //store the combo record for undo.
int afterComboStepRecord[99]; //store the combostep record for undo.
int recording[99]; //store the record for user inputed for undo.
int score = 0; //store the total score.
int userInput; //store userinput for the position.
int Comboc = 1; // store the combo value.
int aftercombostep = 2;// If COMBO is successful, it is used to detect whether the next step can also be Combo.
bool isPlay = true;// check player is / not playeing in game, when game over, player can select again or quit.
char response; // the response for play again option.
int repeatTime = 0; // store the question repeat time.

LinkedList <char> TL; //Position - TopLeft 
LinkedList <char> TM; //Position - TopMiddle
LinkedList <char> TR; //Position - TopRight
LinkedList <char> ML; //Position - MiddleLeft 
LinkedList <char> MM; //Position - MiddleMiddle
LinkedList <char> MR; //Position - MiddleRight
LinkedList <char> BL; //Position - BottomLeft
LinkedList <char> BM; //Position - BottomMiddle
LinkedList <char> BR; //Position - BottomRight

int main() {
	//initialize the game, and the method for calling the whole game.
	Reset();
	cout << "Please input the question file: ";
	char* filename = new char[255];
	std::stringstream file;
	char buffer[60];
	int NumCount = 0;
	char position[10];
	for (int i = 0; i <= 8; i++) {
		position[i] = '-';
	}
	{  //initialize all postion.
		TL.push_back('-');
		TM.push_back('-');
		TR.push_back('-');

		ML.push_back('-');
		MM.push_back('-');
		MR.push_back('-');

		BL.push_back('-');
		BM.push_back('-');
		BR.push_back('-');
	}
	cin >> filename;
	file << filename << ".txt";
	ifstream infile(file.str());
	cout << "loading\" " << file.str() << "\"..." << endl;
	if (!infile) {
		cout << "Fail to load the question file.";
		system("pause");
		exit(EXIT_FAILURE);
		return false;		// fail to load
	}
	while (isGameOver == false) {
		while (infile) {
			//Read vaild file and get the question number.
			infile.getline(buffer, 60);
			repeatTime++;
			//char bufferWithoutWS[30];
			//int sizecount = 0;
			for (int i = 0; i < sizeof(buffer); i++) {
				if (!isspace(buffer[i])) {
					if (buffer[i] != '-') {
						//cout << buffer[i];
						if (NumCount < 30) {
							Num[NumCount] = buffer[i];
							NumCount++;
						}
						//bufferWithoutWS[sizecount] = buffer[i];
						//sizecount++;
					}
				}
			}
			//cout << bufferWithoutWS << endl;
		}
		for (int i = 1 + 30 * (repeatTime - 1); i <= (NumCount * repeatTime); i++) {
			question(i, score, Num);
			print(position);
			cout << "Please enter the position (-1 to quit, -2 to undo):";
			while (!(cin >> userInput)) {
				// if Player not input a number in userInput, then show the wrong message and ask player to input again.
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << endl << "Invalid input" << endl;
				question(i, score, Num);
				print(position);
				cout << "Please enter the position (-1 to quit, -2 to undo):";
				//cout << i << " / " << InputCount << endl;					
			}

			if (InputCount == 0) {
				score = 0;
			}
			switch (userInput)
				// Handle all user input and do push and check.
			{
			case -1:
				//quit game
				cout << "You Quit the game." << endl;
				system("pause");
				exit(EXIT_FAILURE);
				break;
			case -2:
				// Undo

				if (InputCount != 0 && InputCount != 30 * repeatTime) {
					undo(recording, InputCount, mark, score, Num, Comboc, aftercombostep);
					InputCount = InputCount - 1;
					i = i - 2;
				}
				else if (InputCount == 30 * repeatTime)
				{
					cout << "You Can't undo when the question is repeat recently." << endl;
					i = i - 1;
				}

				else {
					cout << "Invalid input" << endl;
					i = i - 1;
				}
				break;
			case 1: if (TL.size() < 9) {
				//store Number to TopLeft Position.
				TL.push_front(Num[i - 1]);
				storeandAdd();// call method to do store and addscore.
			}
					else {
						cout << "Invalid input:stacks is full" << endl;
						InputCount = InputCount - 1;
						i = i - 1;
					}
					break;
			case 2:
				if (TM.size() < 9) {
					//store Number to TopMiddle Position.
					TM.push_front(Num[i - 1]);
					storeandAdd();// call method to do store and addscore.
				}
				else {
					cout << "Invalid input:stacks is full" << endl;
					InputCount = InputCount - 1;
					i = i - 1;
				}
				break;
			case 3: if (TR.size() < 9) {
				//store Number to TopRight Position.
				TR.push_front(Num[i - 1]);
				storeandAdd();// call method to do store and addscore.
			}
					else {
						cout << "Invalid input:stacks is full" << endl;
						InputCount = InputCount - 1;
						i = i - 1;
					}
					break;
			case 4: if (ML.size() < 9) {
				//store Number to MiddleLeft Position.
				ML.push_front(Num[i - 1]);
				storeandAdd();// call method to do store and addscore.
			}
					else {
						cout << "Invalid input:stacks is full" << endl;
						InputCount = InputCount - 1;
						i = i - 1;
					}
					break;
			case 5: if (MM.size() < 9) {
				//store Number to MiddleMiddle Position.
				MM.push_front(Num[i - 1]);
				storeandAdd();// call method to do store and addscore.
			}
					else {
						cout << "Invalid input:stacks is full" << endl;
						InputCount = InputCount - 1;
						i = i - 1;
					}
					break;
			case 6: if (MR.size() < 9) {
				//store Number to MiddleRight Position.
				MR.push_front(Num[i - 1]);
				storeandAdd();// call method to do store and addscore.
			}
					else {
						cout << "Invalid input:stacks is full" << endl;
						InputCount = InputCount - 1;
						i = i - 1;
					}
					break;
			case 7: if (BL.size() < 9) {
				//store Number to BottomLeft Position.
				BL.push_front(Num[i - 1]);
				storeandAdd();// call method to do store and addscore.
			}
					else {
						cout << "Invalid input:stacks is full" << endl;
						InputCount = InputCount - 1;
						i = i - 1;
					}
					break;
			case 8: if (BM.size() < 9) {
				//store Number to BottomMiddle Position.
				BM.push_front(Num[i - 1]);
				storeandAdd();// call method to do store and addscore.
			}
					else {
						cout << "Invalid input:stacks is full" << endl;
						InputCount = InputCount - 1;
						i = i - 1;
					}
					break;
			case 9: if (BR.size() < 9) {
				//store Number to BottomRight Position.
				BR.push_front(Num[i - 1]);
				storeandAdd();// call method to do store and addscore.
			}
					else {
						cout << "Invalid input:stacks is full" << endl;
						InputCount = InputCount - 1;
						i = i - 1;
					}
					break;
			default:
				cin.clear();
				cout << "Invalid input" << endl;
				InputCount = InputCount - 1;
				i = i - 1;
				break;
			}


			if (TL.size() >= 9 && TM.size() >= 9 && TR.size() >= 9 && ML.size() >= 9 && MM.size() >= 9 && MR.size() >= 9 &&
				BL.size() >= 9 && BM.size() >= 9 && BR.size() >= 9) {
				// Check if all Position size >= 9, that will gameover.
				cout << "Game Over" << endl;
				cout << "All stacks are full." << endl;
				cout << "Do you want to Play Again? (Y/N)" << endl;
				cin >> response;
				while (response != 'Y' || response != 'y' || response != 'N' || response != 'n')
				{
					if (response == 'Y' || response == 'y') {
						isGameOver = false;
						main();
					}
					else if (response == 'N' || response == 'n') {
						isGameOver = true;
						isPlay = false;
						cout << "Your Score: " << score << endl;
						cout << "Thanks for playing!" << endl;
						system("pause");
						exit(EXIT_FAILURE);
					}
					else {
						cout << "Please Enter Vaild Response!" << endl;
						cout << "Do you want to Play Again? (Y/N)";
						cin >> response;
					}
				}
			}
		}
	}
	return 0;
}

void Reset() {
	//initialize all data for replay or first start.
	InputCount = 0;
	for (int i = 0; i < (sizeof(mark) / sizeof(mark[0])); i++) {
		mark[i] = 0;
	}
	for (int i = 0; i < (sizeof(comboRecord) / sizeof(comboRecord[0])); i++) {
		comboRecord[i] = 0;
	}
	for (int i = 0; i < (sizeof(afterComboStepRecord) / sizeof(afterComboStepRecord[0])); i++) {
		afterComboStepRecord[i] = 0;
	}
	for (int i = 0; i < (sizeof(recording) / sizeof(recording[0])); i++) {
		recording[i] = 0;
	}
	score = 0;
	userInput = NULL;
	Comboc = 1;
	aftercombostep = 2;
}

//Show and reload the question in top of screen.
void question(int q, int Score, char *num) {
	cout << "---------------------------------------" << endl;
	cout << "QUESTION: [" << num[q - 1] << " " << num[q] << " "
		<< num[q + 1] << "]\tSCORE: " << Score << endl;
	cout << "---------------------------------------" << endl;
}

//Show and reload the Postion and the size of postion in middle of screen.
void print(char* left) {
	cout << "Game         Size" << endl;
	cout << "----         ----" << endl;
	cout << TL.front() << " " << TM.front() << " " << TR.front();
	cout << "    |  " << TL.size() << " " << TM.size() << " " << TR.size() << "\n";
	cout << ML.front() << " " << MM.front() << " " << MR.front();
	cout << "    |  " << ML.size() << " " << MM.size() << " " << MR.size() << "\n";
	cout << BL.front() << " " << BM.front() << " " << BR.front();
	cout << "    |  " << BL.size() << " " << BM.size() << " " << BR.size() << "\n";
}

// undo: restore the question list, score and game board state in last action.
void undo(int* Record, int Time, int* Mark, int& Score, char* num, int& Combo, int& afterComboStepa) {
	TL.destroyList();
	TM.destroyList();
	TR.destroyList();
	ML.destroyList();
	MM.destroyList();
	MR.destroyList();
	BL.destroyList();
	BM.destroyList();
	BR.destroyList();

	TL.push_front('-');
	TM.push_front('-');
	TR.push_front('-');
	ML.push_front('-');
	MM.push_front('-');
	MR.push_front('-');
	BL.push_front('-');
	BM.push_front('-');
	BR.push_front('-');


	for (int i = 0; i < (Time - 1); i++) {
		switch (Record[i])
		{
		case 1: TL.push_front(num[i]);
			break;
		case 2: TM.push_front(num[i]);
			break;
		case 3: TR.push_front(num[i]);
			break;
		case 4: ML.push_front(num[i]);
			break;
		case 5: MM.push_front(num[i]);
			break;
		case 6: MR.push_front(num[i]);
			break;
		case 7: BL.push_front(num[i]);
			break;
		case 8: BM.push_front(num[i]);
			break;
		case 9: BR.push_front(num[i]);
			break;
		}
	}
	if (isAdded == true) {
		addScore(Score, Comboc);
	}
	isAdded = false;
	Score = Mark[Time - 1];
	Combo = comboRecord[Time - 1];
	afterComboStepa = afterComboStepRecord[Time - 1];
}

void addScore(int& Score, int combo) {
	if (TL.front() == TM.front() && TM.front() == TR.front() && TR.front() != '-') {
		//Add Score when TopLeft, TopMiddle and TopRight Number are same.
		Score = Score + 10 * combo;
		Comboc++;
		aftercombostep = 2;
		TL.pop_front();
		TM.pop_front();
		TR.pop_front();
		isAdded = true;
		addScore(Score, Comboc);
	}
	else if ((TM.front() == (TL.front() + 1) && TR.front() == (TM.front() + 1)) || (TM.front() == (TL.front() - 1) && TR.front() == (TM.front() - 1))) {
		//Add Score when TopLeft, TopMiddle and TopRight are sort ascending /descending .
		Score = Score + 30 * combo;
		Comboc++;
		aftercombostep = 2;
		TL.pop_front();
		TM.pop_front();
		TR.pop_front();
		isAdded = true;
		addScore(Score, Comboc);
	}
	if (ML.front() == MM.front() && MM.front() == MR.front() && MR.front() != '-') {
		//Add Score when MiddleLeft, MiddleMiddle and MiddleRight Number are same.
		Score = Score + 10 * combo;
		Comboc++;
		aftercombostep = 2;
		ML.pop_front();
		MM.pop_front();
		MR.pop_front();
		isAdded = true;
		addScore(Score, Comboc);
	}
	else if ((MM.front() == (ML.front() + 1) && MR.front() == (MM.front() + 1)) || (MM.front() == (ML.front() - 1) && MR.front() == (MM.front() - 1))) {
		//Add Score when MiddleLeft, MiddleMiddle and MiddleRight are sort ascending /descending.
		Score = Score + 30 * combo;
		Comboc++;
		aftercombostep = 2;
		ML.pop_front();
		MM.pop_front();
		MR.pop_front();
		isAdded = true;
		addScore(Score, Comboc);
	}
	if (BL.front() == BM.front() && BM.front() == BR.front() && BR.front() != '-') {
		//Add Score when BottomLeft, BottomMiddle and BottomRight Number are same.
		Score = Score + 10 * combo;
		Comboc++;
		aftercombostep = 2;
		BL.pop_front();
		BM.pop_front();
		BR.pop_front();
		isAdded = true;
		addScore(Score, Comboc);
	}
	else if ((BM.front() == (BL.front() + 1) && BR.front() == (BM.front() + 1)) || (BM.front() == (BL.front() - 1) && BR.front() == (BM.front() - 1))) {
		//Add Score when BottomLeft, BottomMiddle and BottomRight Number are sort ascending /descending.
		Score = Score + 30 * combo;
		Comboc++;
		aftercombostep = 2;
		BL.pop_front();
		BM.pop_front();
		BR.pop_front();
		isAdded = true;
		addScore(Score, Comboc);
	}

	if (TL.front() == ML.front() && ML.front() == BL.front() && BL.front() != '-') {
		//Add Score when TopLeft, MiddleLeft and BottomLeft Number are same.
		Score = Score + 10 * combo;
		Comboc++;
		aftercombostep = 2;
		BL.pop_front();
		TL.pop_front();
		ML.pop_front();
		isAdded = true;
		addScore(Score, Comboc);
	}
	else if ((ML.front() == (TL.front() + 1) && BL.front() == (ML.front() + 1)) || (ML.front() == (TL.front() - 1) && BL.front() == (ML.front() - 1))) {
		//Add Score when TopLeft, MiddleLeft and BottomLeft Number are sort ascending /descending.
		Score = Score + 30 * combo;
		Comboc++;
		aftercombostep = 2;
		TL.pop_front();
		ML.pop_front();
		BL.pop_front();
		isAdded = true;
		addScore(Score, Comboc);
	}

	if (TM.front() == MM.front() && MM.front() == BM.front() && BM.front() != '-') {
		//Add Score when TopMiddle, MiddleMiddle and BottomMiddle Number are same.
		Score = Score + 10 * combo;
		Comboc++;
		aftercombostep = 2;
		BM.pop_front();
		TM.pop_front();
		MM.pop_front();
		isAdded = true;
		addScore(Score, Comboc);
	}
	else if ((MM.front() == (TM.front() + 1) && BM.front() == (MM.front() + 1)) || (MM.front() == (TM.front() - 1) && BM.front() == (MM.front() - 1))) {
		//Add Score when TopMiddle, MiddleMiddle and BottomMiddle Number are sort ascending /descending.
		Score = Score + 30 * combo;
		Comboc++;
		aftercombostep = 2;
		TM.pop_front();
		MM.pop_front();
		BM.pop_front();
		isAdded = true;
		addScore(Score, Comboc);
	}

	if (TR.front() == MR.front() && MR.front() == BR.front() && BR.front() != '-') {
		//Add Score when TopRight, MiddleRight and BottomRight Number are same.
		Score = Score + 10 * combo;
		Comboc++;
		aftercombostep = 2;
		BR.pop_front();
		TR.pop_front();
		MR.pop_front();
		isAdded = true;
		addScore(Score, Comboc);
	}
	else if ((MR.front() == (TR.front() + 1) && BR.front() == (MR.front() + 1)) || (MR.front() == (TR.front() - 1) && BR.front() == (MR.front() - 1))) {
		//Add Score when TopRight, MiddleRight and BottomRight Number are sort ascending /descending.
		Score = Score + 30 * combo;
		Comboc++;
		aftercombostep = 2;
		TR.pop_front();
		MR.pop_front();
		BR.pop_front();
		isAdded = true;
		addScore(Score, Comboc);
	}

	if (TR.front() == MM.front() && MM.front() == BL.front() && BL.front() != '-') {
		//Add Score when TopRight, MiddleMiddle and BottomLeft Number are same.
		Score = Score + 10 * combo;
		Comboc++;
		aftercombostep = 2;
		TR.pop_front();
		MM.pop_front();
		BL.pop_front();
		isAdded = true;
		addScore(Score, Comboc);
	}
	else if ((MM.front() == (TR.front() + 1) && BL.front() == (MM.front() + 1)) || (MM.front() == (TR.front() - 1) && BL.front() == (MM.front() - 1))) {
		//Add Score when TopRight, MiddleMiddle and BottomLeft Number are sort ascending /descending.
		Score = Score + 30 * combo;
		Comboc++;
		aftercombostep = 2;
		TR.pop_front();
		MM.pop_front();
		BL.pop_front();
		isAdded = true;
		addScore(Score, Comboc);
	}

	if (TL.front() == MM.front() && MM.front() == BR.front() && BR.front() != '-') {
		//Add Score when TopLeft, MiddleMiddle and BottomRight Number are same.
		Score = Score + 10 * combo;
		Comboc++;
		aftercombostep = 2;
		TL.pop_front();
		MM.pop_front();
		BR.pop_front();
		isAdded = true;
		addScore(Score, Comboc);
	}
	else if ((MM.front() == (TL.front() + 1) && BR.front() == (MM.front() + 1)) || (MM.front() == (TL.front() - 1) && BR.front() == (MM.front() - 1))) {
		//Add Score when TopLeft, MiddleMiddle and BottomRight Number are sort ascending /descending.
		Score = Score + 30 * combo;
		Comboc++;
		aftercombostep = 2;
		TL.pop_front();
		MM.pop_front();
		BR.pop_front();
		isAdded = true;
		addScore(Score, Comboc);
	}
	comboRecord[InputCount] = Comboc;
	afterComboStepRecord[InputCount] = aftercombostep;
}

void storeandAdd() {
	mark[InputCount] = score;
	recording[InputCount] = userInput;
	InputCount++;
	aftercombostep--;
	if (aftercombostep <= 0) { aftercombostep = 0; }
	if (Comboc <= 0) { Comboc = 1; }
	//cout << "Before If" << aftercombostep << " / " << Comboc << endl;
	if (InputCount > 2) {
		if (aftercombostep >= 1 && Comboc >= 2) {
			addScore(score, Comboc);
			//cout << "Have Combo: " << aftercombostep << " / " << Comboc << endl;
		}
		if (aftercombostep <= 1) {
			//cout << "Before Clear Combo: " << aftercombostep << " / " << Comboc << endl;
			Comboc = 1;
			addScore(score, Comboc);
			aftercombostep = 2;
			//cout << "After Clear Combo: " << aftercombostep << " / " << Comboc << endl;
		}
	}
}






