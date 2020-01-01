#pragma once
struct as_color {
	int r;
	int g;
	int b;
	as_color(int R, int G, int B)
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
}; 
