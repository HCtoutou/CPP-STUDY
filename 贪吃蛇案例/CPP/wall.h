#pragma once
#include<iostream>

using namespace std;

class Wall // ǽ����
{
public:
	enum { ROW = 26, COL = 26 };

	void initWall(); // ��ʼ��ǽ��
	void drawWall(); // ����ǽ��
	void setWall(int x, int y, char c); // �����������ö�ά�����ڵ�����
	char getWall(int x, int y); // ����������ȡ��ǰλ�õ�����
private:
	char gameArray[ROW][COL];
};