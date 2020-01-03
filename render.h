#pragma once
#include <windows.h>
#include <GL\glut.h>
#include "structs.h"
class render
{
public:
	render(int argc, char** argv,  as_color *  ptr_color);
	~render() { delete background_color,map; }
	static void createWindow  (int x,int y,int nx,int ny);
	static void repaint();
	static  as_color* background_color;
	static void reshape(int w, int h);
	static int width;
	static int height;
	static bool ** get_map();
private:
	static int argc;
	static char ** argv;
	static bool** map;
	static int amout_into_lineX;
	static int amout_into_lineY;
	

};
