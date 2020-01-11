#include "render.h"
#include <iostream>
#include <iomanip>
#include <memory>
#include <mutex>
using namespace std;

 map_field** map;
 extern std::mutex my_mutex;
//статические переменные класс
std::unique_ptr<as_color> render::background_color;
manager* render::_manager;
int render::width;
int render::height;
int render::argc;
int render::amout_into_lineX;
int render::amout_into_lineY;



char** render::argv;
int global_nx;
int global_ny;


#define otstup_x 5
#define otstup_y 15

render::render(int c, char** v, std::unique_ptr<as_color>& color)
{ argc = c; argv = v; background_color = std::move(color);
};



void render::reshape(int w,int h)
{
	//
	width = w;
	height = h;
	//repaint();
	
	glLoadIdentity();
	glOrtho(0, width, height+otstup_y, 0, -5.0, 5.0);//Ортоганальная система координат
	glTranslatef(0 + (width/100)*otstup_x, 0 + otstup_y, 0);//Центр координат

	glClearColor(background_color->r, background_color->g, background_color->b, 1);
	glClear(GL_COLOR_BUFFER_BIT);//От любого цвета
	
}
void render::repaint()
{
	//my_mutex.lock();

	
	//return;
	glClearColor(background_color->r, background_color->g, background_color->b, 1);
	glClear(GL_COLOR_BUFFER_BIT);//От любого цвета
	
	glColor3f(0,0,0.7);
	glViewport(0,0,width,height+otstup_y);

	string str("level ");
	str += toString(_manager->level);
	drawText(str.c_str(), str.size(), otstup_x*2, height-otstup_y, GLUT_BITMAP_9_BY_15);
	str = "points: " + toString(object::points);

	drawText(str.c_str(), str.size(), width / 2, height - otstup_y, GLUT_BITMAP_9_BY_15);

	if (_manager->is_game_over)
	{
		str = "GAME OVER";
		drawText(str.c_str(), str.size(), width/4, height/2, GLUT_BITMAP_TIMES_ROMAN_24);
		render::clean_map();
	}

	int rectangle_w = (width-otstup_x) / (amout_into_lineX);
	int rectangle_h = (height-otstup_y) / amout_into_lineY;

	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	for (int i = 0; i <global_nx; i++)
	{
		for (int j = 0; j<global_ny; j++)
		{
			if (map[i][j] == false)
			{
	glColor3f(map[i][j].color.r, map[i][j].color.g, map[i][j].color.b); //Выбираем белый цвет
				glBegin(GL_QUADS);
		
glBegin(GL_QUADS);

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

void render::createWindow  (int x, int y,int nx,int ny, manager* man) {
	
	//ptr_shape = Shape;//тут будет храниться объект
	//controller = cont;
	_manager = man;

	global_nx = nx;
	global_ny = ny;
	
	map = new map_field*[nx];
	amout_into_lineX = nx;
	amout_into_lineY = ny;
	for (int i = 0; i <  nx; i++)
	{
		map[i] = new map_field[ny];
	}
	for (int i = 0; i < nx; i++)
	{
		for (int j = 0; j < ny; j++)
		{
			map[i][j].color=*background_color;
		}
	}
	


	glutInit(&argc,argv);
	glutInitWindowSize(width, height+otstup_y);		//Указываем размер окна
	glutInitWindowPosition(x, y);	//Позиция окна
	glutCreateWindow("Тетрис");		//Имя окна
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);


	//intit
	glMatrixMode(GL_PROJECTION);//Все координаты относятся к этому проекту
	glOrtho(0, width, height, 0, -5.0, 5.0);
	
	
	glutKeyboardFunc(controller_keys);
	glutSpecialFunc(controller);
	glutReshapeFunc(reshape);
	glutDisplayFunc(repaint);				//Вызов функции отрисовки
	//glutIdleFunc(repaint);
	my_mutex.unlock();
	glutMainLoop();
	
}
void render::revalidate()
{
	//glutSwapBuffers();
	repaint();
	glutPostRedisplay();
	//glutSwapBuffers();
}
void controller_keys(unsigned char key, int wParam, int lParam)
{
	if (key == 27)
		exit(0);
	if (key == 32) {
		cout << "there" << endl;
		if (render::_manager->is_game_over)
		{
			render::_manager->start_level();
		};
	}
	
}
void controller(int key, int wParam, int lParam)
{
	if (render::_manager->get_shape() == nullptr) return;
	switch (key) {
	case GLUT_KEY_RIGHT:
		render::_manager->get_shape()->right();
		render::revalidate();
		break;
	case GLUT_KEY_LEFT:
		render::_manager->get_shape()->left();
		render::revalidate();
		break;
	case GLUT_KEY_DOWN:
		
		if (render::_manager->get_shape()->down())
		{

			render::_manager->remove_shape();
		}
		render::revalidate();
		break;

	case GLUT_KEY_UP:
		render::_manager->get_shape()->rotate();
		render::revalidate();
		break;
		
	}
}
void drawText(const char *text, int length, int x, int y,void* font)
{
	
	glRasterPos2i(x, y);
	for (int i = 0; i<length; i++)
	{
		glutBitmapCharacter(font, (int)text[i]);
	}
	

}
template <typename T>
std::string toString(T val)
{
	std::ostringstream oss;
	oss << val;
	return oss.str();
}
template<typename T>
T fromString(const std::string& s)
{
	std::istringstream iss(s);
	T res;
	iss >> res;
	return res;
}
