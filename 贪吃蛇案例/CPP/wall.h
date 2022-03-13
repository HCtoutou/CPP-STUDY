#pragma once
#include<iostream>

using namespace std;

class Wall // 墙体类
{
public:
	enum { ROW = 26, COL = 26 };

	void initWall(); // 初始化墙壁
	void drawWall(); // 绘制墙体
	void setWall(int x, int y, char c); // 根据索引设置二维数组内的内容
	char getWall(int x, int y); // 根据索引获取当前位置的内容
private:
	char gameArray[ROW][COL];
};