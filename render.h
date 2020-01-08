#pragma once
#include <windows.h>
#include <memory>
#include <GL\glut.h>
#include "object.h"
#include "structs.h"
//#include "manager.h"
class render
{
public:
	render(int argc, char** argv, std::unique_ptr<as_color>& color);
//	~render() { delete[] map; }
	static void createWindow  (int x,int y,int nx,int ny, std::shared_ptr<object> ptr_shape);
	static void repaint();
	static std::unique_ptr<as_color> background_color;
	static void reshape(int w, int h);
	static int width;
	static int height;
	static std::unique_ptr<as_color>& getColor() { return background_color; }
	static void revalidate();
	

private:
	static int argc;
	static char ** argv;
	static std::shared_ptr<object> ptr_shape;
	static int amout_into_lineX;
	static int amout_into_lineY;
	
	
	friend void controller(int key, int wParam, int lParam);

};

void controller_keys(unsigned char key, int wParam, int lParam);
