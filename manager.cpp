#include "manager.h"
//#include <exception>
#include <iostream>
#include <ctime>
#include<thread>
#include<chrono>
#include<vector>
	extern   map_field** map;
	std::mutex my_mutex;

manager::manager(const render  *const Render)
	:ptrSettings(nullptr), ptr_render(Render), shape(nullptr),level(0),is_game_over(false) {
};
	

///manager::manager(const manager &ref) { this->shape = ref.shape; }
manager::~manager() {}


 settings* manager::getSettings() const { return this->ptrSettings.get(); }
 object* manager::get_shape() { return shape.get(); }
void manager::setSettings( settings&  ptrsettings) {

	this->ptrSettings = std::make_unique<settings>(ptrsettings);//Тут происходит копирование
}

void manager::create_window()
{

//std::thread repaint_thread(repaint_every_one_sec);
//repaint_thread.detach();

	my_mutex.lock();
	std::thread tr(run, std::ref(*this),true);
	tr.detach();
this->f_list.push_back(one_line_generate);
	render::reshape(400,400);

	this->ptr_render->createWindow(400,150,ptrSettings->get_amout_blocks_into_lineX(), 
		ptrSettings->get_amout_blocks_into_lineY(),this);


	
	
}
void manager::start_level()
{
	std::thread tr(run, std::ref(*this),false);
	tr.detach();
}
void manager::start()
{
	create_window();

}
void run( manager &m,bool delay)
{
	//if (delay) {
my_mutex.lock();
	my_mutex.unlock();
	//}
	
	
	m.level = 0;
	object::points = 0;
	m.is_game_over = false;
	
//Пауза когда выведется экран начинаем
	while (true)
	{
		
	if (m.shape.get()==nullptr)
	{
//Если объект не создан тогда
		m.level++;
		if (m.f_list.size() > 0)
		{
			int i = rand() % m.f_list.size();
			//if (m.f_list.at(i)(m)){break;}
			//test(m);
			break;
			render::revalidate();

		}
	}
	else
	{
		
		if (m.shape->down() == true)
		{
			m.remove_shape();
		}
		render::revalidate();
		//Если мы создали объект
	}
	int mill = (int)(m.ptrSettings->get_speed() / (m.level*(m.ptrSettings->get_increese() / 1000)));
	if (mill < min_speed) mill= min_speed;
	std::this_thread::sleep_for(std::chrono::milliseconds(mill));
	}
	
	m.is_game_over = true;
	render::revalidate();
	m.start_level();
}
//Генерация на одной линии случайной величины 
bool one_line_generate(manager &m)
{
	std::srand(time(0));

	if (m.ptrSettings->get_amout_blocks_into_lineY() <= 0)
	{
		return true;
	}
	int z = 1+rand()%2;
	
	//int z = 2;
//Выделение места
	int i = rand() % (m.ptrSettings->get_amout_blocks_into_lineX()-1);
	int j = rand() % (m.ptrSettings->get_amout_blocks_into_lineX() - i-1);//количество
	//Проверка занимаемого места
	for (int t = 0; t < z; t++)
	{
		for (int k = i; k < j; k++)
		{

			if (!map[k][t].is_empty) { return true; }
		}
	}
	
	j++;
	if (i + j >= m.ptrSettings->get_amout_blocks_into_lineX())
	{
		j = m.ptrSettings->get_amout_blocks_into_lineX();
	}
	//std::cout << i<<"  "<<j << std::endl;
	int amout = j * z;
	std::unique_ptr<field[]> points (new field[amout]);
	
	int k = 0;
	int temp_j = j;
	for (int t = 0; t < z; t++)
	{
		int amout_members_into_row = 0;
		for ( k; k < temp_j; k++)
		{
			as_color color((double)(rand()) / RAND_MAX, (double)(rand()) / RAND_MAX, (double)(rand()) / RAND_MAX);
			points[k].color = color;
			points[k].Ycoord = t;
			points[k].Xcoord = amout_members_into_row + i;
			amout_members_into_row++;
		}
		temp_j *= 2;
	}
	

std::vector<field>keys;
	keys.reserve(z);
	k = j / 2;
	keys.push_back(points[k]);
	if (j != 1)
	{
		for (int t = 1; t < z; t++)
		{
			int k1 = j*t + k;
			keys.push_back(points[k1]);
		}
	}
	m.shape = std::make_shared<line_object>(m.level);
	m.shape->setXY(m.ptrSettings->get_amout_blocks_into_lineX(), m.ptrSettings->get_amout_blocks_into_lineY());
	as_color* color = render::background_color.get();
	m.shape->setColor(*color);
	m.shape->setSize(j*z);
	m.shape->setCoords(std::move(points));
	m.shape->setKeys(keys);
	return false;
}

bool test(manager &m)
{
	/*
	as_color color(04, 04, 04);
	std::unique_ptr<field[]> points(new field[6]);
	for (int j = 0; j < 3; j++)
	{
		points[j].color = color;
		points[j].Ycoord = 5;
		points[j].Xcoord = 2 + j;
	}
	for (int j = 3; j < 6; j++)
	{
		points[j].color = color;
		points[j].Ycoord = 6;
		points[j].Xcoord = 2 + j-3;
	}
	std::vector<field> key;
	key.push_back(points[1]);
	key.push_back(points[4]);
	m.shape->setSize(6);
	m.shape->setCoords(std::move(points));
	m.shape->setKeys(key);
	*/
	return true;
}


