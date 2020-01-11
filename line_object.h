#pragma once
#include "object.h"

 class  line_object :public object
{
public:
	line_object(int l) :object(l)
	{

	}
	virtual void  rotate() override;
	~line_object(){ for (field* f : r_keys) delete f; }
private:
};