#include "render.h"
#include <iostream>
#include <iomanip>
using namespace std;
render::render(){}
void render::createWindow  (int x, int y, int w, int h, const as_color * const color) const{
	glutInit(0,NULL);
	//cout << x<<setw(5) << y<<setw(5) << w<<set << h <<<< endl;
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(w, h);		//Указываем размер окна
	glutInitWindowPosition(x, y);	//Позиция окна
	glutCreateWindow("Тетрис");		//Имя окна
	glClearColor(color->r,color->g, color->b, 1.0);
	//Установить проекцию
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
	//Initialize();						//Вызов функции Initialize
	//glutKeyboardFunc(key);
	//glutDisplayFunc(Draw);				//Вызов функции отрисовки
	glutMainLoop();
}