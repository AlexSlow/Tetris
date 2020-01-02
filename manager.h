#pragma once
#include <iostream>
#include "controller.h"
#include "settings.h"
#include "render.h"
class manager
{

public:
	manager(controller* const ptr_contrlooer,const render * const ptrrender );
	~manager();
	//manager(const manager &ref);
	controller* get_controller();
	void setSettings(const settings*  ptrsettings);
	const settings* getSettings() const;
	void create_window();
	void start();
private:
	controller* key_handler;
	const settings*  ptrSettings;
	const render * const ptr_render;

	
};

