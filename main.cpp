#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include <iostream>
#include<memory>
#include "settings.h"
#include "manager.h"
#include<mutex>


int main(int argc, char **argv)
{
	std::unique_ptr<settings::builder> factory(new settings::builder);
	//settings::builder *factory =  new settings::builder; //Установка настоек 
	std::unique_ptr<settings> Settings = factory->
		set_speed(20)->
		set_increese(20)->set_amout_of_blocks_into_lineX(10)->set_amout_of_blocks_into_lineY(20)->build();
	//delete factory;
	manager Manager(new render(argc,argv,std::unique_ptr<as_color>(new as_color(0.3,1,0.3))) );
	Manager.setSettings(*Settings.get());
	Manager.start();
	std::system("pause");
	return 0;
}