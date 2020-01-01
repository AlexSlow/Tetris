#include "manager.h"
manager::manager(controller CONTROLLER) {}
manager::~manager() {}
manager::manager(const manager &ref) {}
controller manager::get_controller()
{
	return this->key_handler;
}
void manager::create_window()
{

}