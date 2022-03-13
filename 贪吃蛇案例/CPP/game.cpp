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
	pos.X = x; // ������
	pos.Y = y; // ������
	SetConsoleCursorPosition(hOut, pos);
}
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // ������ʾ���������

int main()
{
	bool isDead = false; // �Ƿ�������ʶ
	char preKey = NULL; // ��һ�ΰ�����ʶ
	Wall wall; // ��Ϸ�������
	wall.initWall(); // ��Ϸ�����ʼ��
	wall.drawWall();

	Food food(wall);  // ʳ�����
	food.setFood(); // ���ó�ʼʳ����ֵ�λ��

	Snake snake(wall, food); // �߶���
	snake.initSnake();  // ��ʼ���߶���

	// ���Դ���
	/*snake.move('w');
	snake.move('w');
	snake.move('a');*/

	 //wall.drawWall();
	gotoxy(hOut, 0, Wall::ROW);
	cout << "�÷֣�" << snake.getScore() << endl;

	// gotoxy(hOut, 10, 5); // ��Ļ����ϵ ���ά��������ϵ�෴

	while (!isDead)
	{
		// �����û�����
		char key = _getch();

		// �ж� �����һ�ΰ��� ��� ���ܼ�����Ϸ
		// �ж� ��һ���ƶ�����
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
					preKey = key; // ���ǳ�ͻ���������Ը��°���

				if (snake.move(key))
				{
					// �ƶ��ɹ� 1������ 2�����»���
					//system("cls");
					//wall.drawWall();
					gotoxy(hOut, 0, Wall::ROW);
					cout << "�÷֣�" << snake.getScore() << endl;
					Sleep(snake.getSleepTime());
				}
				else
				{
					isDead = true;
					break;
				}
			}
			else
				key = preKey; // ǿ�ƽ����󰴼���Ϊ��һ�εİ���
		} while (!_kbhit()); // _kbhit()��û�м��������ʱ�򣬷���0

	}

	return 0;
}