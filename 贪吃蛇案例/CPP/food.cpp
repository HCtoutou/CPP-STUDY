#include<Windows.h>
#include"food.h"

void gotoxy2(HANDLE hOut2, int x, int y)
{
	COORD pos;
	pos.X = x; // 横坐标
	pos.Y = y; // 纵坐标
	SetConsoleCursorPosition(hOut2, pos);
}
HANDLE hOut2 = GetStdHandle(STD_OUTPUT_HANDLE); // 定义显示器句柄变量

Food::Food(Wall& tempWall):wall(tempWall){}

void Food::setFood() // 设置食物出现的坐标(坐标随机生成)
{
	// 添加随机种子
	srand((unsigned int)time(NULL));

	while (true)
	{
		foodX = rand() % (Wall::ROW - 2);
		foodY = rand() % (Wall::COL - 2);

		// 如果随机生成的位置与蛇产生冲突，则重新生成随机数
		if (wall.getWall(foodX, foodY) == ' ')
		{
			wall.setWall(foodX, foodY, '#');
			gotoxy2(hOut2, foodY * 2, foodX);
			cout << "#";
			break;
		}
	}
}
