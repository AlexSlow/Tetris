#pragma once
#include <iostream>
#include<vector>
#include<memory>
#include <ctime>
#include"structs.h"
//#include "manager.h"


extern   map_field** map;
class object
{
public:
	//virtual void  rotate() = 0;
	object();
	
	void setCoords(std::unique_ptr<field[]> points);
	std::vector<field>& getCoords();
	void setSize(int s);
	void setColor(as_color s);
	int getSize();
	void setXY(int x, int y);

	//метод опускания на 1
	bool down();
	bool left();
	bool right();
	bool is_created;

private:
	as_color def_color;
	int size;
	int NX, NY;
	std::vector<field> fields;

	bool horizontal_move(int i);//перемещение влево вправо
	void check_and_remove();
};
