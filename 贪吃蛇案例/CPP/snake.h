#pragma once
#include<iostream>
#include"wall.h"
#include"food.h"
using namespace std;

class Snake
{
public:
	Snake(Wall& tempWall,Food& tempFood); // 构造函数
	enum { UP = 'w', DOWN = 's', LEFT = 'a', RIGHT = 'd' };
	struct Point // 节点
	{
		int x; // x坐标
		int y; // y坐标

		Point* next; // 下一个节点
	};

	void initSnake(); // 初始化
	void addPoint(int x, int y); // 添加节点
	bool move(char key); // 移动蛇操作
	void destroyPoint(); // 销毁节点
	void delPoint(); // 删除节点

	// 设定难度
	int getSleepTime(); // 获取刷屏时间
	int countList(); // 获取蛇身段
	int getScore(); // 获取分数

	Point* pHead;
	Wall& wall;
	Food& food;
	bool isRool; // 判断循环标识
};