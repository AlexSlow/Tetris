#include "manager.h"
#include <exception>
#include <iostream>

manager::manager(controller* const ptr_controler, const render * const ptrrender)
	:ptrSettings(nullptr), key_handler (ptr_controler),ptr_render(ptrrender) {  };

//manager::manager(const manager &ref):ptrSettings(nullptr) {}
manager::~manager() { delete key_handler; if (ptrSettings != nullptr) delete ptrSettings; }

 settings* manager::getSettings() const { return this->ptrSettings; }
void manager::setSettings( settings*  ptrsettings) {

	if (ptrsettings == nullptr) throw std::exception("null");
	if (ptrSettings != nullptr)
	{
		delete ptrSettings;
	}
	this->ptrSettings = ptrsettings; }
controller* manager::get_controller()
{
	return this->key_handler;
}
void manager::create_window()
{
	render::reshape(550,500);
	this->ptr_render->createWindow(50,50,ptrSettings->get_amout_blocks_into_lineX(), ptrSettings->get_amout_blocks_into_lineY());
	
}
void manager::start()
{
	create_window();
}