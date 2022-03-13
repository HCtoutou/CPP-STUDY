#include<Windows.h>
#include"food.h"

void gotoxy2(HANDLE hOut2, int x, int y)
{
	COORD pos;
	pos.X = x; // ������
	pos.Y = y; // ������
	SetConsoleCursorPosition(hOut2, pos);
}
HANDLE hOut2 = GetStdHandle(STD_OUTPUT_HANDLE); // ������ʾ���������

Food::Food(Wall& tempWall):wall(tempWall){}

void Food::setFood() // ����ʳ����ֵ�����(�����������)
{
	// ����������
	srand((unsigned int)time(NULL));

	while (true)
	{
		foodX = rand() % (Wall::ROW - 2);
		foodY = rand() % (Wall::COL - 2);

		// ���������ɵ�λ�����߲�����ͻ�����������������
		if (wall.getWall(foodX, foodY) == ' ')
		{
			wall.setWall(foodX, foodY, '#');
			gotoxy2(hOut2, foodY * 2, foodX);
			cout << "#";
			break;
		}
	}
}
