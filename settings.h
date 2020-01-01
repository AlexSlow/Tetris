#pragma once
#include "structs.h"
class settings
{
	class builder;
	friend builder;
public:


class builder
	{
		
	public:
		builder();
		~builder();
		builder(const builder &ref);

	builder* set_width(int);
	builder* set_height(int);
	builder* set_speed(int);
	builder* set_increese(int);
	builder* set_color(as_color *color);
	settings* build();
	private:
		settings* Settings;

	};


	explicit settings();
	~settings();
	settings(const settings &ref);
	int  get_width();
	int get_height();
	int get_speed();
	int get_increese();
	settings& operator=(settings& ref);
	

private:
	int display_width;
	int display_height;
	int base_speed;
	int speed_increese;
	as_color* color;
};
