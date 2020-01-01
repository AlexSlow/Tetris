#pragma once
#include "controller.h"
class manager
{
public:
	manager(controller CONTROLLER);
	~manager();
	manager(const manager &ref);
	controller get_controller();

	void create_window();
private:
	controller key_handler;
};
