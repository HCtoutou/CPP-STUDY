#include"wall.h"

void Wall::initWall()
{
	// 绘制墙体的二维数组 
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
			if (i == 0 || j == 0 || i == ROW - 1 || j == COL - 1)
				gameArray[i][j] = '*';
			else
				gameArray[i][j] = ' ';
	}
}

void Wall::drawWall()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
			cout << gameArray[i][j] << " ";
		if (i == 4)cout << "版本号:1.0";
		if (i == 5) cout << "Author: H_W";
		if (i == 6)cout << "游戏玩法：wasd控制方向";
		cout << endl;
	}
}

void Wall::setWall(int x, int y, char c)
{
	gameArray[x][y] = c;
}

char Wall::getWall(int x, int y)
{
	return gameArray[x][y];
}
