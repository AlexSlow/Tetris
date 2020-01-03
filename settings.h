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
	builder* set_speed(int);
	builder* set_increese(int);
	builder* set_amout_of_blocks_into_lineX(int);
	builder* set_amout_of_blocks_into_lineY(int);
	settings* build();
	private:
		settings* Settings;

	};


	explicit settings();
	~settings();
	settings(const settings &ref);
	int get_speed() const;
	int get_increese() const;
	int get_amout_blocks_into_lineX() const;
	int get_amout_blocks_into_lineY() const;

	settings& operator=(settings& ref);
	

private:
	int base_speed;
	int speed_increese;
	int amout_of_blocks_into_lineX;
	int amout_of_blocks_into_lineY;
};
