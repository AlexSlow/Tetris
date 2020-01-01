#include <iostream>
#include "settings.h";


int main(int argc, char **argv)
{
	settings::builder *factory =  new settings::builder; //Установка настоек 
	settings* Settings = factory->
		set_color(new as_color(40, 40, 40))->
		set_height(200)->
		set_width(200)->set_speed(20)->
		set_increese(5)->build();
	delete factory;
	std::cout << Settings->get_height();
	std::system("pause");
	return 0;
}