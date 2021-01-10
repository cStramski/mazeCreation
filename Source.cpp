/**
*
* Solution to course project # 4
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2020/2021
*
* @author Tsvetan Stramski	
* @idnumber 62586
* @compiler VC
*
* Core file
*
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>


//By defenition
const int rows = 18;
const int cols = 39;
int maze[rows][cols] = {};
//Used only by the recursive calls 
int emptySpaceCount = 0;
int lastDirection = 0;

using namespace std;
void printMaze()
{
	//If the "maze.txt" is not present it will be created, and it is overwritten everytime.
	ofstream myfile("maze.txt");
	maze[0][0] = -1; //Start decleration
	maze[17][38] = -2; //End deckeratuib
	myfile << string(80, '-') << endl;
	for (int i = 0; i < rows; i++)
	{
		myfile << '|';
		//-1 Start
		//-2 End
		//0 Empty
		//1 Wall
		for (int j = 0; j < cols; j++)
		{
			if (maze[i][j] == 1)
			{
				myfile << "##";
			}
			else if (maze[i][j] == -1)
			{
				myfile << "S ";
			}
			else if (maze[i][j] == -2)
			{
				myfile << " E";
			}
			else
			{
				myfile << "  ";
			}
		}
		myfile << '|' << endl;
	}
	myfile << string(80, '-') << endl;
	myfile.close();
}
bool emptySpaceCheck()
{
	//Checks for open spaces like squares, returns false if there are big empty spaces
	for (int i = 0; i < rows-1; i++)
	{
		for (int j = 0; j < cols-1; j++)
		{
			if (maze[i][j] == 0 && maze[i][j + 1] == 0 && maze[i + 1][j] == 0 && maze[i + 1][j + 1] == 0)
			{
				return false;
			}
		}
	}
	return true;
}
bool pathCreation(int x, int y, int level)
{
	/*  Returning true if the maze created meets the creteria (no big empty spaces, path from s to e, and level of depth above 30)
		Each call creates path whit random length to a random direction from the current position                                  */

	// 1 - UP
	// 2 - RIGHT
	// 3 - DOWN
	// 4 - LEFT

	//In the maze the open space is marked whit 1 and the empty whit 0
	int nextX = x;
	int nextY = y;
	int direction = (rand() % 4) + 1; // 1-4
	int length = (rand() % 10) + 1; //1-10
	switch (direction)
	{
	case 1:
		for (int i = 1; i < length; i++)
		{
			//Out of bounds check
			if ((y - i )<0)
			{
				break;
			}
			nextY = y - i;
			//Useless action check(removing already removed walls)
			if (maze[nextY][x] == 0)
			{
				break;
			}
			maze[nextY][x] = 0;
			emptySpaceCount++;
		}
		break;
	case 2:
		//Same checks for all directions
		for (int i = 1; i < length; i++)
		{			
			if ((x + i)>38)
			{
				break;
			}
			nextX = x + i;
			if (maze[y][nextX] == 0)
			{
				break;
			}
			maze[y][nextX] = 0;
			emptySpaceCount++;
		}
		break;
	case 3:
		for (int i = 1; i < length; i++)
		{
			
			if ((y + i)>17)
			{
				break;
			}
			nextY = y + i;
			if (maze[nextY][x] == 0)
			{
				break;
			}
			maze[nextY][x] = 0;
			emptySpaceCount++;
		}
		break;
	case 4:
		for (int i = 1; i < length; i++)
		{
			if ((x - i) < 0)
			{
				break;
			}
			nextX = x - i;
			if (maze[y][nextX] == 0)
			{
				break;
			}
			//Removing walls and recording their count
			maze[y][nextX] = 0;
			emptySpaceCount++;
		}
		break;
	}
	//Stackoverflow protection
	if (level == 1000)
	{
		return false;
	}
	//Maze Creteria
	if ((maze[17][37] == 0 || maze[16][38] == 0) && level > 30)
	{
		if (emptySpaceCheck())
		{
			if (emptySpaceCount > 150)
			{
				return true;
			}
		}
		return false;
	}
	//Recursive call whit current position in the maze, whit increased level of depth expecting the value of the root of the recursion.
	return pathCreation(nextX, nextY, level + 1);
}
int main()
{
	//Random seed initialization
	srand((int)time(0));

	//Infinite maze creation until one meets all the creteria.
	bool isReady = false;
	while (!isReady)
	{
		//Reset
		emptySpaceCount = 0;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				maze[i][j] = 1;
			}
		}
		//Calling the recursive function whit position (0,0) and level of depth 0
		isReady = pathCreation(0, 0, 0);
	}
	printMaze();
	return 0;
}