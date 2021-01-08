#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

const int rows = 18;
const int cols = 39;
int maze[rows][cols] = {};
int emptySpaceCount = 0;
int lastDirection = 0;

using namespace std;
void printMaze()
{
	cout << string(80, '-') << endl;
	for (int i = 0; i < rows; i++)
	{
		cout << '|';
		for (int j = 0; j < cols; j++)
		{
			if (maze[i][j] == 1)
			{
				cout << "##";
			}
			else
			{
				cout << "  ";
			}
		}
		cout << '|' << endl;
	}
	cout << string(80, '-') << endl;
	int a = 5;
	cin >> a;
}
bool emptySpaceCheck()
{
	for (int i = 0; i < rows-1; i++)
	{
		for (int j = 0; j < cols-1; j++)
		{
			if (maze[i][j]==0&&maze[i][j+1]==0&&maze[i+1][j]==0&&maze[i+1][j+1]==0)
			{
				return false;
			}
		}
	}
	return true;
}
void pathCreation(int x,int y,int level)
{

	// 1 - UP
	// 2 - RIGHT
	// 3 - DOWN
	// 4 - LEFT
	int nextX = x;
	int nextY = y;
	int direction = (rand() % 4) + 1;
	int length = (rand() % 10) + 1;
	switch (direction)
	{
	case 1:
		for (int i = 1; i < length; i++)
		{
			if ((y - i )<0)
			{
				break;
			}
			nextY = y - i;
			if (maze[nextY][x] == 0)
			{
				break;
			}
			maze[nextY][x] = 0;
			emptySpaceCount++;
		}
		break;
	case 2:
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
			
			if ((y+i)>17)
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
			if ((x-i) <0)
			{
				break;
			}
			nextX = x - i;
			if (maze[y][nextX] == 0)
			{
				break;
			}
			maze[y][nextX] = 0;
			emptySpaceCount++;
		}
		break;
	}
	//cout << direction << "  " << length <<"  "<<level<< endl;
	//printMaze();
	if (level == 800)
	{
		return;
	}
	if ((maze[17][37] == 0 || maze[16][38] == 0) && level >30 )
	{
		if (emptySpaceCheck())
		{
			
			if (emptySpaceCount>130)
			{
				cout << emptySpaceCount << endl;
				printMaze();
			}
		}
		return;
	}
	pathCreation(nextX,nextY,level + 1);
}
int main()
{
	srand((int)time(0));
	while (true)
	{
		emptySpaceCount = 0;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				maze[i][j] = 1;
			}
		}
		pathCreation(0, 0, 0);
	}
	printMaze();
	return 0;
}