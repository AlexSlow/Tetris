
#include "object.h"
//extern std::mutex my_mutex;
using namespace std;
int object::points=0;

bool comp( field f1,  field f2) {

	return f1.Ycoord > f2.Ycoord;

}
object::object(int l) :size(0), NX(0), NY(0),level(l){

}
object::~object() {  }
void object::setKeys(std::vector<field> r) {
for (field& key : r)
{
	for ( field& item:fields)
	{
		if (key == item)
		{

			r_keys.push_back(new field(item));
		}
	}
}
}
void object::setCoords(std::unique_ptr<field[]> points) {
	//lock_guard<mutex> lock(my_mutex);
	//r_keys.clear();
	fields.clear();
	fields.reserve(size);
	for (int i = 0; i < size; i++)
	{
		fields.push_back(points[i]);
	}
	for (const field& item : fields)
	{
		//as_color color((double)(rand()) / RAND_MAX, (double)(rand()) / RAND_MAX, (double)(rand()) / RAND_MAX);
		map[item.Xcoord][item.Ycoord].is_empty = false;
		map[item.Xcoord][item.Ycoord].color = item.color;
	}
	//render::reshape(200, 200);

	return;

}
std::vector<field>& object::getCoords()
{
	return fields;
}
void object::setSize(int s) { this->size = s; }
void object::setColor(as_color s) { def_color = s;
}
int object::getSize() { return size; }
void object::setXY(int x, int y) { NX = x; NY = y;}



//метод опускания на 1
bool object::down()
{

	//my_mutex.lock();
	for (const field& item : fields)
	{
		int n = item.Ycoord + 1;
		if ((item.Ycoord == (NY-1)) || (!map[item.Xcoord][n].is_empty))
		{
			//Устроим проверку свой это объект или нет
			bool is_have = false;
			for (const field& item1 : fields)
			{
				if ((item1.Xcoord == item.Xcoord) && (item1.Ycoord == n)) { is_have = true; break; }
			}
			if (!is_have)
			{
			check_and_remove();
			fields.clear();


			r_keys.clear();//r
			return true;
			}
			
			
		}
	}

	// движение вниз

	sort(fields.begin(), fields.end(),comp);  // сортировка

	for (field& item : fields)
	{
		map[item.Xcoord][item.Ycoord].is_empty = true;

		item.Ycoord++;
		map[item.Xcoord][item.Ycoord].is_empty = false;
		map[item.Xcoord][item.Ycoord].color = item.color;
	}
	for (field* item : r_keys)
	{
		item->Ycoord ++;
		//cout <<"Y "<< item->Ycoord << endl;
	}
	//my_mutex.unlock();
	return false;
}

//метод опускания на 1
bool object::horizontal_move(int i)
{
	///my_mutex.lock();
	std::vector<field> distinct_field;

	for (const field& item : fields)
	{
		const field* temp=&item;
		//Ищем макс или мин
		for (const field& item1 : fields)
		{
			if (contains_row(distinct_field, temp)) continue;
			if (i > 0)
			{
				if (temp->Xcoord < item1.Xcoord)
				{
					temp = &item1;
				}
			}
			else
			{
				if (temp->Xcoord > item1.Xcoord)
				{
					temp = &item1;
				}
			}
			
		}
		if (!contains(distinct_field,*temp))
		{ 	distinct_field.push_back(*temp);}
		//Помещаем если 
		
		

	}
	//проверка
	for (const field& item : distinct_field)
	{
		int k = item.Xcoord + i;//Тут неточность
		if ((k >= NX)||(k<0)) return true;
		if (!map[k][item.Ycoord].is_empty)
		{
			return true;
		}

	}
	 //Сразу освобобим карту
	for (field& item : fields)
	{
		map[item.Xcoord][item.Ycoord].is_empty = true;
	}
	for (field& item : fields)
	{
		item.Xcoord+=i;
		map[item.Xcoord][item.Ycoord].is_empty = false;
		map[item.Xcoord][item.Ycoord].color = item.color;

	}
	for (field* item : r_keys)
	{
		item->Xcoord += i;
	}

	//my_mutex.unlock();
	return false;
}
bool object::right()
{
	return this->horizontal_move(1);
}
bool object::left()
{
	return this->horizontal_move(-1);
}
void object::check_and_remove()
{
	//Сначала проверим 
	for (int j = NY - 1; j >= 0; j--)
	{
		
		bool is_row_full = true;
		for (int i = NX - 1; i >= 0; i--)
		{
			if (map[i][j].is_empty) is_row_full = false;
		}
		if (is_row_full)
		{
			if (j == 0)break;
			
				//Почистим строку
				for (int k = 0; k < NX; k++)
				{
					map[k][j].is_empty = true;
					points += (increase*level);
				}	
		//Видимо, это смещение на 1 клетку вниз
				for (int m = j; m >= 0; m--)
				{
					
					bool is_row_empty = true;
				
					for (int n = 0; n < NX; n++)
					{
						//cout << m<<" "<<n << endl;
						if (!map[n][m - 1].is_empty)
						{
							is_row_empty - false;
							map[n][m] = map[n][m-1];
							map[n][m-1] = true;
						}

					}
					if (!is_row_empty) break;
				}
				j=NY;//Что бы сразу все строки проверили
			//break;
		}
	}
}
 void  object::rotate()
{
}
bool contains(const std::vector<field> &vector,const field &f) {
	for (const field& item : vector)
	{
		if (item == f)  return true;
	}
	return false;
}
//Проверка строки на обработанность  для оптимизации
bool contains_row(const std::vector<field> &vector, const field *temp)
{
	for (const field& item : vector)
	{
		if (temp->Xcoord == item.Xcoord) return true;
	}
	return false;
}


