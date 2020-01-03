#pragma once
struct as_color {
	float r;
	float g;
	float b;
	as_color(float R, float G, float B)
	{
		r = R;
		g = G;
		b = B;
	}
	as_color()
	{
		r = g = b = 0;
	}
	as_color(const as_color &ref)
	{
		r = ref.r;
		b = ref.b;
		g = ref.g;
	}
	as_color& operator=(as_color& ref)
	{
		r = ref.r;
		b = ref.b;
		g = ref.g;
		return *this;
	}
}; 
