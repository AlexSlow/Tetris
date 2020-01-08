#pragma once
#include <memory>
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
	//	builder* set_color(as_color&);
	//	builder* set_color(int a,int b,int c);
	builder* set_speed(float);
	builder* set_increese(float);
	builder* set_amout_of_blocks_into_lineX(int);
	builder* set_amout_of_blocks_into_lineY(int);
	std::unique_ptr<settings>  build();
	private:
		std::unique_ptr<settings>  Settings;

	};


	 settings();
	~settings();
	settings(const settings &ref);
	float get_speed() const;
	//const as_color& get_color() const;
	float get_increese() const;
	int get_amout_blocks_into_lineX() const;
	int get_amout_blocks_into_lineY() const;

	settings& operator=(settings& ref);
	

private:
	// as_color color;
	float base_speed;
	float speed_increese;
	int amout_of_blocks_into_lineX;
	int amout_of_blocks_into_lineY;
};
