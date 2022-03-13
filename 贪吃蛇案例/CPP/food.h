#pragma once
#include<iostream>
#include<ctime>
#include"wall.h"
using namespace std;

class Food
{
public:
	Food(Wall &tempWall);
	void setFood();

	int foodX;
	int foodY;
	Wall& wall;
};