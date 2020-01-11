#pragma once
#include <windows.h>
#include <sstream>
#include <string>
#include <memory>
#include <GL\glut.h>
#include "object.h"
#include "structs.h"
#include "manager.h"

class manager;
class render
{
public:
	render(int argc, char** argv, std::unique_ptr<as_color>& color);
//	~render() { delete[] map; }
	static void createWindow  (int x,int y,int nx,int ny,manager* m);
	static void repaint();
	static std::unique_ptr<as_color> background_color;
	static void reshape(int w, int h);
	static int width;
	static int height;
	static std::unique_ptr<as_color>& getColor() { return background_color; }
	static void revalidate();
	static manager* _manager;

private:
	static int argc;
	static char ** argv;
	//static std::shared_ptr<object> *ptr_shape;
	
	static  object *Shape;
	static int amout_into_lineX;
	static int amout_into_lineY;
	static void clean_map()
{
	for (int i = 0; i < amout_into_lineX; i++)
	{
		for (int j = 0; j < amout_into_lineY; j++)
		{
			map[i][j].is_empty = true;
		}
	}
}
	
	friend void controller(int key, int wParam, int lParam);

};

void controller_keys(unsigned char key, int wParam, int lParam);
void drawText(const char *text, int length, int x, int y, void* font);
template <typename T>
std::string toString(T val);
template<typename T>
T fromString(const std::string& s);

