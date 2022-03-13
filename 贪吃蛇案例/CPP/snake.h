#pragma once
#include<iostream>
#include"wall.h"
#include"food.h"
using namespace std;

class Snake
{
public:
	Snake(Wall& tempWall,Food& tempFood); // ���캯��
	enum { UP = 'w', DOWN = 's', LEFT = 'a', RIGHT = 'd' };
	struct Point // �ڵ�
	{
		int x; // x����
		int y; // y����

		Point* next; // ��һ���ڵ�
	};

	void initSnake(); // ��ʼ��
	void addPoint(int x, int y); // ��ӽڵ�
	bool move(char key); // �ƶ��߲���
	void destroyPoint(); // ���ٽڵ�
	void delPoint(); // ɾ���ڵ�

	// �趨�Ѷ�
	int getSleepTime(); // ��ȡˢ��ʱ��
	int countList(); // ��ȡ�����
	int getScore(); // ��ȡ����

	Point* pHead;
	Wall& wall;
	Food& food;
	bool isRool; // �ж�ѭ����ʶ
};