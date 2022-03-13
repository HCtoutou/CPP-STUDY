#include<iostream>
#include<conio.h>
#include<Windows.h>
#include"wall.h"
#include"snake.h"
#include"food.h"
using namespace std;

void gotoxy(HANDLE hOut, int x, int y)
{
	COORD pos;
	pos.X = x; // 纵坐标
	pos.Y = y; // 纵坐标
	SetConsoleCursorPosition(hOut, pos);
}
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // 定义显示器句柄变量

int main()
{
	bool isDead = false; // 是否死亡标识
	char preKey = NULL; // 上一次按键标识
	Wall wall; // 游戏区域对象
	wall.initWall(); // 游戏区域初始化
	wall.drawWall();

	Food food(wall);  // 食物对象
	food.setFood(); // 设置初始食物出现的位置

	Snake snake(wall, food); // 蛇对象
	snake.initSnake();  // 初始化蛇对象

	// 测试代码
	/*snake.move('w');
	snake.move('w');
	snake.move('a');*/

	 //wall.drawWall();
	gotoxy(hOut, 0, Wall::ROW);
	cout << "得分：" << snake.getScore() << endl;

	// gotoxy(hOut, 10, 5); // 屏幕坐标系 与二维数组坐标系相反

	while (!isDead)
	{
		// 接受用户输入
		char key = _getch();

		// 判断 如果第一次按了 左键 不能激活游戏
		// 判断 上一次移动方向
		if (preKey == NULL && key == snake.LEFT)
			continue;


		do
		{
			if (key == snake.UP || key == snake.DOWN || key == snake.LEFT || key == snake.RIGHT)
			{
				if (key == snake.LEFT && preKey == snake.RIGHT ||
					key == snake.RIGHT && preKey == snake.LEFT ||
					key == snake.DOWN && preKey == snake.UP ||
					key == snake.UP && preKey == snake.DOWN)
					key = preKey;
				else
					preKey = key; // 不是冲突按键，可以更新按键

				if (snake.move(key))
				{
					// 移动成功 1、清屏 2、重新绘制
					//system("cls");
					//wall.drawWall();
					gotoxy(hOut, 0, Wall::ROW);
					cout << "得分：" << snake.getScore() << endl;
					Sleep(snake.getSleepTime());
				}
				else
				{
					isDead = true;
					break;
				}
			}
			else
				key = preKey; // 强制将错误按键变为上一次的按键
		} while (!_kbhit()); // _kbhit()当没有键盘输入的时候，返回0

	}

	return 0;
}