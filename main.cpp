#include <iostream>
#include "settings.h"
#include "manager.h"


int main(int argc, char **argv)
{
	
	settings::builder *factory =  new settings::builder; //Установка настоек 
	settings* Settings = factory->
		set_speed(20)->
		set_increese(5)->set_amout_of_blocks_into_lineX(10)->set_amout_of_blocks_into_lineY(20)->build();
	delete factory;

	manager Manager(new controller(),new render(argc,argv,new as_color(0.0,0.0,0.0)));
	Manager.setSettings(Settings);
	Manager.start();
	std::system("pause");
	return 0;
}