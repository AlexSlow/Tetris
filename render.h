#pragma once
#include <windows.h>
#include <GL\glut.h>
#include "structs.h"
class render
{
public:
	render();
	~render() {};
	void createWindow  (int x,int y,int w,int h, const as_color * const color)const;

};
