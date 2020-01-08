#include "manager.h"
#include <exception>
#include <iostream>
#include <ctime>
#include<thread>
#include<chrono>
#define min_speed 100
	extern   map_field** map;
	std::mutex my_mutex;

manager::manager(const render  *const Render)
	:ptrSettings(nullptr), ptr_render(Render), shape(new object()),level(0) {
	
};
	

//manager::manager(const manager &ref):ptrSettings(nullptr) {}
manager::~manager() {}


 settings* manager::getSettings() const { return this->ptrSettings.get(); }
void manager::setSettings( settings&  ptrsettings) {

	this->ptrSettings = std::make_unique<settings>(ptrsettings);//Тут происходит копирование
	shape->setXY(ptrSettings->get_amout_blocks_into_lineX(), ptrSettings->get_amout_blocks_into_lineY());
	as_color* color = render::background_color.get();
	shape->setColor(*color);
	
}

void manager::create_window()
{
	my_mutex.lock(); 
std::thread tr(run,std::ref(*this));
tr.detach();

//std::thread repaint_thread(repaint_every_one_sec);
//repaint_thread.detach();


this->f_list.push_back(one_line_generate);
	render::reshape(250,450);

	this->ptr_render->createWindow(400,150,ptrSettings->get_amout_blocks_into_lineX(), 
		ptrSettings->get_amout_blocks_into_lineY(),shape);


	
	
}
void manager::start()
{
	create_window();

}
void run( manager &m)
{

	my_mutex.lock();
	my_mutex.unlock();
	
	//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	std::srand(unsigned(std::time(0)));
//Пауза когда выведется экран начинаем
	while (true)
	{
		
	if (!m.shape->is_created)
	{
//Если объект не создан тогда
		m.level++;
		if (m.f_list.size() > 0)
		{
			std::srand(unsigned(std::time(0)));
			int i = rand() % m.f_list.size();
			if (m.f_list.at(i)(m)){break;}
			render::revalidate();

		}
	}
	else
	{
		
		if (m.shape->down() == true)
		//if (m.shape->left() == true)
		{
			m.shape->is_created = false;
		}
		render::revalidate();
		//Если мы создали объект
	}
	int mill = (int)(m.ptrSettings->get_speed() / (m.level*(m.ptrSettings->get_increese() / 1000)));
	if (mill < min_speed) mill= min_speed;
	std::this_thread::sleep_for(std::chrono::milliseconds(mill));
	}
	
	
}
//Генерация на одной линии случайной величины 
bool one_line_generate(manager &m)
{
	
	
	if (m.ptrSettings->get_amout_blocks_into_lineY() <= 0)
	{
		return true;
	}
	for (int i = 0; i < m.ptrSettings->get_amout_blocks_into_lineX(); i++)
	{
	
		if (!map[i][0].is_empty) { return true; }
	}

	int i = rand() % (m.ptrSettings->get_amout_blocks_into_lineX()-1);
	int j = rand() % (m.ptrSettings->get_amout_blocks_into_lineX() - i-1);//количество
	j++;
	if (i + j >= m.ptrSettings->get_amout_blocks_into_lineX())
	{
		j = m.ptrSettings->get_amout_blocks_into_lineX();
	}
	//std::cout << i<<"  "<<j << std::endl;
	std::unique_ptr<field[]> points (new field[j]);
	for (int k = 0; k < j; k++)
	{
		as_color color ((double)(rand()) / RAND_MAX, (double)(rand()) / RAND_MAX, (double)(rand()) / RAND_MAX);
		points[k].color = color;
		points[k].Ycoord = 0;
		points[k].Xcoord = k + i;
	}
	m.shape->setSize(j);
	m.shape->setCoords(std::move(points));
	
	m.shape->is_created = true;
	return false;
}
void repaint_every_one_sec()
{
	my_mutex.lock();
	my_mutex.unlock();
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		render::revalidate();
	}
}
