#include "manager.h"
#include <exception>

manager::manager(controller* const ptr_contrlooer, const render * const ptrrender)
	:ptrSettings(nullptr), key_handler (ptr_contrlooer),ptr_render(ptrrender) {  };

//manager::manager(const manager &ref):ptrSettings(nullptr) {}
manager::~manager() { delete key_handler; if (ptrSettings != nullptr) delete ptrSettings; }

const settings* manager::getSettings() const { return this->ptrSettings; }
void manager::setSettings(const settings*  ptrsettings) {

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

	this->ptr_render->createWindow(50,50,ptrSettings->get_width(),ptrSettings->get_height(),ptrSettings->get_color());
}
void manager::start()
{
	create_window();
}