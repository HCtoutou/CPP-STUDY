#include"wall.h"

void Wall::initWall()
{
	// ����ǽ��Ķ�ά���� 
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
		if (i == 4)cout << "�汾��:1.0";
		if (i == 5) cout << "Author: H_W";
		if (i == 6)cout << "��Ϸ�淨��wasd���Ʒ���";
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
