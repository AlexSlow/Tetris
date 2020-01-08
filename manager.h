#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include <mutex>
#include<memory>
#include "settings.h"
#include "render.h"
#include "object.h"
class manager
{

public:
	friend void run( manager &m);
	friend bool one_line_generate(manager &m);
	manager( const render* const Rende);
	~manager();
	void setSettings(settings&  ptrsettings);
	settings* getSettings() const;
	void create_window();
	void start();
private:
	std::unique_ptr<settings> ptrSettings;
	const std::unique_ptr<const render> ptr_render; //1-Это константный указатель 2 это константные данные
	std::shared_ptr<object> shape;
	//bool is_created;
	std::vector<std::function<bool(manager &m)>> f_list;
	int level;


	
};

