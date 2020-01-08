#pragma once
struct as_color {
	float r;
	float g;
	float b;
	as_color(float  R, float G, float B)
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
	as_color& operator=(const as_color& ref)
	{
		r = ref.r;
		b = ref.b;
		g = ref.g;
		return *this;
	}
	bool operator==(const as_color& ref)const
	{
		if ((r == ref.r) && (g == ref.g) && (b == ref.b))
		{
			return true;
		}
		else return false;
	}
}; 
struct map_field
{
	as_color color;
	bool is_empty;
	map_field():is_empty(true)
	{
		
	}
	map_field(const map_field &field)
	{
		color = field.color;
		is_empty = field.is_empty;

	}
	map_field& operator=(const map_field& field)
	{
		color = field.color;
		is_empty = field.is_empty;
		return *this;
	}
	
	map_field& operator=(bool b)
	{
		is_empty = b;
		return *this;
	}
	
	bool operator==(bool b)
	{
		
		return is_empty == b;
	}
	
};
struct field
{
	as_color color;
	int Xcoord;
	int Ycoord;
	field(int x, int y, as_color &col)
	{
		color = col;
		 Xcoord=x;
		 Ycoord = y;;
	}
	field()
	{
		
		Xcoord = 0;
		Ycoord = 0;;
	}
	bool operator==(const field& field)const
	{

		if ((color == field.color) && (Xcoord == field.Xcoord)&&(Ycoord == field.Ycoord))
		{
			return true;
		}
		else return false;
	}
};
