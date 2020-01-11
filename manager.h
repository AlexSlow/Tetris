#pragma once
#include <iostream>
#include <ctime>
#include<thread>
#include<chrono>
#include <vector>
#include <functional>
#include <mutex>
#include<memory>
#include "settings.h"
#include "render.h"
#include "line_object.h"

class render;
class manager
{

public:
	friend void run( manager &m,bool dalay);
	friend bool one_line_generate(manager &m);
	friend bool test(manager &m);
	manager( const render* const Rende);
	//manager(const manager &ref);
	~manager();
	void setSettings(settings&  ptrsettings);
	settings* getSettings() const;
	object* get_shape();
	void remove_shape() { shape = nullptr; }
	void create_window();
	void start_level();
	void start();
	int level;
	bool is_game_over;
private:
	std::unique_ptr<settings> ptrSettings;
	const std::unique_ptr<const render> ptr_render; //1-Это константный указатель 2 это константные данные
	std::shared_ptr<object> shape;
	//bool is_created;
	std::vector<std::function<bool(manager &m)>> f_list;
	
	


	
};
#define min_speed 300
