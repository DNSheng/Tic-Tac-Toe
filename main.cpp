#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

bool gameOver, newGame;
char matrix[3][3] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
char player1, player2, currentPlayer;
int desiredField, moveCounter = 0;
string restart;

void Draw()
{
	//Draws the tic-tac-toe box using the matrix
	//Any updates to the matrix will be seen
	system("cls");
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			cout << matrix[i][j] << "\t";
		}
		cout << "\n\n";
		cout << endl;
	}
}

void firstPlayer()
{
	//Randomly chooses who goes first and appropriately assigns
	//them as player1 and player2. Also tells the users.
	//This is is only run once.
	srand(time(NULL));
	int randNumber = rand() % 100;
	if(randNumber % 2 == 0)
	{
		cout << "X starts first" << endl;
		player1 = 'X';
		player2 = 'O';
	}
	else
	{
		cout << "O starts first" << endl;
		player1 = 'O';
		player2 = 'X';
	}

}
void Input();

void Fill(int x, int y)
{
	//Checks to see if someone already moved in a spot
	if((matrix[x][y] == 'X') || (matrix[x][y] == 'O'))
	{
		//Already filled
		cout << "Field is full! Choose another area.\n\n" << endl;
		Draw();
		Input();
	}
	else
	{
		//Empty, fills the current area with player's piece
		matrix[x][y] = currentPlayer;

		//Makes it the next player's turn after a move has been made
		if(currentPlayer == player1)
		{
			currentPlayer = player2;
			moveCounter++;
		}
		else if(currentPlayer == player2)
		{
			currentPlayer = player1;
			moveCounter++;
		}
	}
}

void Input()
{

	//Check for new game, sets the current player
	if(newGame == true)
	{
		firstPlayer();
		currentPlayer = player1;
		newGame = false;
	}

	//Dialogue for user to input changed field
	//cout << "Move counter: " << moveCounter;					//Debugging line
	cout << "It is Player " << currentPlayer << "'s turn.\n";
	cout << "\nPress the number of the field: ";
	cin >> desiredField;
	cout << endl;

	//Changes fields based on user input
	if(desiredField % 3 == 0)
	{
		Fill((desiredField/3)-1, 2);
		//matrix[(desiredField/3)-1][2] = currentPlayer;
	}
	else if(desiredField == 2)
	{
		Fill(0, 1);
		//matrix[0][1] = currentPlayer;
	}
	else if(desiredField == 4)
	{
		Fill(1, 0);
		//matrix[1][0] = currentPlayer;
	}
	else if(desiredField == 5)
	{
		Fill(1, 1);
		//matrix[1][1] = currentPlayer;
	}
	else if(desiredField == 1)
	{
		Fill(0, 0);
		//matrix[0][0] = currentPlayer;
	}
	else if(desiredField == 7)
	{
		Fill(2, 0);
		//matrix[2][0] = currentPlayer;
	}
	else
	{
		Fill(2, 1);
		//matrix[2][1] = currentPlayer;
	}

}

void restartPrompt()
{
	if(gameOver)
	{
		//Game has ended, asks if players want to restart
		cout << "Game Over. Restart? (Y/N)" << endl;
		cin >> restart;
		if(restart == "Y")
		{
			//Restart
			//Reset matrix, make it a new game for randomizing, make gameOver false to continue
			//while loop, reset moveCount, and change restart to something different for next restart prompt
			matrix[0][0] = '1';		matrix[0][1] = '2';		matrix[0][2] = '3';
			matrix[1][0] = '4';		matrix[1][1] = '5';		matrix[1][2] = '6';
			matrix[2][0] = '7';		matrix[2][1] = '8';		matrix[2][2] = '9';
			newGame = true;
			gameOver = false;
			restart = 'O';
			moveCounter = 0;
		}
		else if(restart == "N")
		{
			//No restart, exit instead
			exit(0);
		}
		else
		{
			//Invalid input, ask again
			restartPrompt();
		}
	}
}

void Logic()
{
	//Checks after every input to see if someone won the game
	if(matrix[0][0] == matrix[0][1] && matrix[0][1] == matrix[0][2])
	{
		//Top row the same
		Draw();
		cout << "Player " << matrix[0][0] << " wins!" << endl;
		gameOver = true;
	}
	else if(matrix[1][0] == matrix[1][1] && matrix[1][1] == matrix[1][2])
	{
		//Middle row
		Draw();
		cout << "Player " << matrix[1][0] << " wins!" << endl;
		gameOver = true;
	}
	else if(matrix[2][0] == matrix[2][1] && matrix[2][1] == matrix[2][2])
	{
		//Bottom row
		Draw();
		cout << "Player " << matrix[2][0] << " wins!" << endl;
		gameOver = true;
	}
	else if(matrix[0][0] == matrix[1][1] && matrix[1][1] == matrix[2][2])
	{
		//Diagonal left to right
		Draw();
		cout << "Player " << matrix[0][0] << " wins!" << endl;
		gameOver = true;
	}
	else if(matrix[0][2] == matrix[1][1] && matrix[1][1] == matrix[2][0])
	{
		//Diagonal right to left
		Draw();
		cout << "Player " << matrix[0][2] << " wins!" << endl;
		gameOver = true;
	}
	else if(matrix[0][0] == matrix[1][0] && matrix[1][0] == matrix[2][0])
	{
		//First column
		Draw();
		cout << "Player " << matrix[0][0] << " wins!" << endl;
		gameOver = true;
	}
	else if(matrix[0][1] == matrix[1][1] && matrix[1][1] == matrix[2][1])
	{
		//Second column
		Draw();
		cout << "Player " << matrix[0][1] << " wins!" << endl;
		gameOver = true;
	}
	else if(matrix[0][2] == matrix[1][2] && matrix[1][2] == matrix[2][2])
	{
		//Last column
		Draw();
		cout << "Player " << matrix[0][2] << " wins!" << endl;
		gameOver = true;
	}
	else if(moveCounter == 9)
	{
		//Board is filled, therefore tie
		Draw();
		cout << "A tie game!" << endl;
		gameOver = true;
	}
	else
	{
		//No one won yet, continue
	}
	//Prompt asking players if they want to restart
	restartPrompt();
}

int main()
{
	//The newGame is for generating player1 and player2.
	//The game cycles between Draw(), Input(), and Logic()
	//Instead of a constant loop, has pauses inbetween and only continues if there
	//is valid input.
	newGame = true;
	gameOver = false;
	while(!gameOver)
	{
		Draw();
		Input();
		Logic();
	}
	return 0;
}
