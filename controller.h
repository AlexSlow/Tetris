#pragma once
class controller
{
public:
	controller();
	~controller();
	controller(const  controller &ref);
	void key_handler(unsigned char wParam, int x, int y);


};
