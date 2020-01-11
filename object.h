#pragma once
#include <iostream>
#include<vector>
#include<memory>
#include <ctime>
#include <algorithm> //для сортировки
#include"structs.h"
//#include "manager.h"
#define increase 5


extern   map_field** map;
class object
{
public:
	virtual void  rotate()=0;
	virtual ~object()=0;
	object(int level);
	
	void setCoords(std::unique_ptr<field[]> points);
	std::vector<field>& getCoords();
	void setSize(int s);
	void setColor(as_color s);
	int getSize();
	void setXY(int x, int y);
	void setKeys(std::vector<field> r);
	//метод опускания на 1
	bool down();
	bool left();
	bool right();
	//bool is_created;
	static int points;
protected:
	as_color def_color;
	int size;
	int NX, NY;
	std::vector<field> fields;
	std::vector<field*> r_keys;
	bool horizontal_move(int i);//перемещение влево вправо
	void check_and_remove();
	int level;

};
bool contains(const std::vector<field> &vector, const field &f);
bool contains_row(const std::vector<field> &vector, const field *temp);
