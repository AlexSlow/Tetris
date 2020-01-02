#include <iostream>
#include "settings.h"
#include "manager.h"


int main(int argc, char **argv)
{
	
	settings::builder *factory =  new settings::builder; //Установка настоек 
	settings* Settings = factory->
		set_color(new as_color(1.0, 0.0, 1.0))->
		set_height(200)->
		set_width(200)->set_speed(20)->
		set_increese(5)->build();
	delete factory;

	manager Manager(new controller(),new render());
	Manager.setSettings(Settings);
	Manager.start();
	std::system("pause");
	return 0;
}