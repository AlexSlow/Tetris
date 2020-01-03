#include "render.h"
#include <iostream>
#include <iomanip>
using namespace std;
as_color* render::background_color;
//статические переменные класса
int render::width;
int render::height;
int render::argc;
int render::amout_into_lineX;
int render::amout_into_lineY;


char** render::argv;
bool** render:: map;
int global_nx;
int global_ny;


#define otstup_x 40
#define otstup_y 20

render::render(int c, char** v, as_color *  ptr_color) { argc = c; argv = v; background_color = ptr_color;

};



void render::reshape(int w,int h)
{
	//
	width = w;
	height = h;
}
void render::repaint()
{
	glViewport(0,0,width,height);
	cout << width / amout_into_lineX << setw(10) << width << endl;
	int rectangle_w = -otstup_x + width / (amout_into_lineX+1);
	int rectangle_h = -5 + height / amout_into_lineY;

	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	//cout << width << setw(10) << height << setw(10) << amout_into_lineX << endl;
	
	


	//Отрисовка квадрата 
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);//От любого цвета
	//glColor3f(0.0, 1.0, 0.0); //Выбираем белый цвет

	for (int i = 0; i <global_nx; i++)
	{
		for (int j = 0; j<global_ny; j++)
		{
			if (map[i][j] == true)
			{
				
			
	glColor3f(0.0, 1.0, 0.0); //Выбираем белый цвет
				glBegin(GL_QUADS);
		
glBegin(GL_QUADS);
/*
	glVertex2f(i*rectangle_w-rectangle_w/2-(width- rectangle_w / 2), j*rectangle_h+rectangle_h/2); //Координаты квадрата
	glVertex2f(i*rectangle_w - rectangle_w / 2 - (width - rectangle_w / 2), j*rectangle_h - rectangle_h / 2+(height-rectangle_h/2)); //Координаты квадрата
	glVertex2f(i*rectangle_w + rectangle_w / 2 - (width - rectangle_w / 2), j*rectangle_h - rectangle_h / 2 + (height - rectangle_h / 2)); //Координаты квадрата
	glVertex2f(i*rectangle_w + rectangle_w / 2 - (width - rectangle_w / 2), j*rectangle_h + rectangle_h / 2 + (height - rectangle_h / 2)); //Координаты квадрата
	*/
glVertex2f(i*rectangle_w - rectangle_w / 2, j*rectangle_h + rectangle_h / 2); //Координаты квадрата
glVertex2f(i*rectangle_w - rectangle_w / 2 , j*rectangle_h - rectangle_h / 2 ); //Координаты квадрата
glVertex2f(i*rectangle_w + rectangle_w / 2 , j*rectangle_h - rectangle_h / 2 ); //Координаты квадрата
glVertex2f(i*rectangle_w + rectangle_w / 2 , j*rectangle_h + rectangle_h / 2 ); //Координаты квадрата
	glEnd();
	

	glColor3f(1.0, 0.0, 0.0); //Выбираем белый цвет
	glLineWidth(2);       // ширину линии
	glBegin(GL_LINES);
	glVertex2f(i*rectangle_w - rectangle_w / 2, j*rectangle_h + rectangle_h / 2); //Координаты квадрата
	glVertex2f(i*rectangle_w - rectangle_w / 2, j*rectangle_h - rectangle_h / 2); //Координаты квадрата
		glEnd();
		//Левое ребро
		glBegin(GL_LINES);
		glVertex2f(i*rectangle_w - rectangle_w / 2, j*rectangle_h - rectangle_h / 2); //Координаты квадрата
		glVertex2f(i*rectangle_w + rectangle_w / 2, j*rectangle_h - rectangle_h / 2); //Координаты квадрата
		glEnd();

		//Нижнее ребро
		glBegin(GL_LINES);
		glVertex2f(i*rectangle_w - rectangle_w / 2, j*rectangle_h - rectangle_h / 2); //Координаты квадрата
		glVertex2f(i*rectangle_w + rectangle_w / 2, j*rectangle_h - rectangle_h / 2); //Координаты квадрата
		glEnd();

		//Верхнее ребро
		glBegin(GL_LINES);
		glVertex2f(i*rectangle_w - rectangle_w / 2, j*rectangle_h + rectangle_h / 2); //Координаты квадрата
		glVertex2f(i*rectangle_w + rectangle_w / 2, j*rectangle_h + rectangle_h / 2); //Координаты квадрата
		glEnd();

		//Правое  ребро
		glBegin(GL_LINES);
		glVertex2f(i*rectangle_w + rectangle_w / 2, j*rectangle_h + rectangle_h / 2); //Координаты квадрата
		glVertex2f(i*rectangle_w + rectangle_w / 2, j*rectangle_h - rectangle_h / 2); //Координаты квадрата
		glEnd();

			}	
		}
	}
	glFlush();
}

void render::createWindow  (int x, int y,int nx,int ny ) {
	global_nx = nx;
	global_ny = ny;
	
	map = new bool*[nx];
	amout_into_lineX = nx;
	amout_into_lineY = ny;
	for (int i = 0; i <  nx; i++)
	{
		map[i] = new bool[ny];
	}

	for (int i = 0; i <nx; i++)
	{
		for (int j = 0; j<ny; j++)
		{
			map[i][j] = false;
		}
	}
	
	for (int i = 0; i <nx; i++)
	{
			map[i][0] = true;
		
	}
	
	//map[0][0] = true;



	glutInit(&argc,argv);
	glutInitWindowSize(width, height);		//Указываем размер окна
	glutInitWindowPosition(x, y);	//Позиция окна
	glutCreateWindow("Тетрис");		//Имя окна
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);


	//intit
	glMatrixMode(GL_PROJECTION);//Все координаты относятся к этому проекту
	glLoadIdentity();
	//glOrtho(0, width, height, 0, -5.0, 5.0);
	glOrtho(-width/2, width/2, height/2, -height/2, -5.0, 5.0);
	glTranslatef(-width /2+otstup_x, -height / 2+ otstup_y, 0);
	
	//
	
	
	//glutKeyboardFunc(key);
	glutReshapeFunc(reshape);
	glutDisplayFunc(repaint);				//Вызов функции отрисовки
	glutMainLoop();
}
bool** render:: get_map()
{
	return map;
}
