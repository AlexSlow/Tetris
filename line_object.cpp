#include"line_object.h"
void line_object::rotate() 
{
	//Узнаем тип преобразования 
	int width, height;
	{
		int x_max = 0, x_min = NX, y_max = 0, y_min = NY;

		for (const field& item : fields)
		{
			if (item.Xcoord > x_max) x_max = item.Xcoord;
			if (item.Xcoord < x_min) x_min = item.Xcoord;
			if (item.Ycoord > y_max) y_max = item.Ycoord;
			if (item.Ycoord < y_min) y_min = item.Ycoord;
		}
		width = x_max - x_min;
		height = y_max - y_min;
	}

	//Проверка	
	if (r_keys.size() == 0) return;
	if (fields.size() == 1)return;
	if (width == height) return;
	int r_key = 0;//Счетчик ключей
	field &key_base = *r_keys[0];

	if (width>height)
	{
		for (const field* key_item : r_keys)
		{
			field key_temp = *key_item;  //создадим копио объекта
			key_temp.Ycoord = key_base.Ycoord; //Формирование ключа
			key_temp.Xcoord = key_base.Xcoord + r_key; //Формирование ключа
			for (const field& item : fields)
			{
				//выбираем только однострочные с ключом элементы
				if ((*key_item).Ycoord == item.Ycoord)
				{
					int delta = item.Xcoord - key_temp.Xcoord;//+r_key;
					if ((item.Ycoord + delta >= this->NY) || (item.Ycoord + delta <= 0)) { return; };
					if (!map[key_temp.Xcoord][item.Ycoord + delta].is_empty)
					{
						bool is_have = false;
						for (const field& item1 : fields)
						{
							if ((item1.Xcoord == key_temp.Xcoord) && (item1.Ycoord == (item.Ycoord + delta))) { is_have = true; break; }
						}
						if (!is_have)
						{
							{ return; };
							return;
						}
					}
				}
			}
			r_key++;
		}


		std::vector<field> moved;//сюда положим копию объекта 
		std::vector<field> new_keys;//сюда положим копию объекта 
		r_key = 0;
		//Перестановка
		for (const field* key_item : r_keys)
		{
			//int old_val_y = key_item->Ycoord;
			field n_key(*key_item);
			n_key.Ycoord = key_base.Ycoord; //Формирование ключа
			n_key.Xcoord = key_base.Xcoord + r_key; //Формирование ключа
			new_keys.push_back(n_key);

			for (const field& item : fields)
			{
				//выбираем только однострочные с ключом элементы
				if (key_item->Ycoord == item.Ycoord)
				{
					int delta = item.Xcoord - key_item->Xcoord;
					map[item.Xcoord][item.Ycoord].is_empty = true;
					field n_field(item);

					n_field.Xcoord = n_key.Xcoord;
					n_field.Ycoord = n_key.Ycoord + delta;
					moved.push_back(n_field);
				}
			}
			r_key++;
		}
		for (const field& item : moved)
		{
			map[item.Xcoord][item.Ycoord].is_empty = false;
			map[item.Xcoord][item.Ycoord].color = item.color;
		}
		for (field* f : r_keys)
		{
			delete f; ///////////Освобождаю память!!!!!!!!!!!!!
		}
		r_keys.clear();
		fields = moved;

		for (field &item : new_keys)
		{
			for (const field &item1 : moved)
			{
				if (item == item1)
				{
					//r_keys.push_back(&field(item));
					r_keys.push_back(new field(item));
				}
			}
		}

		//	translate = true;
	}
	else//////YYYY-transform
	{

		for (const field* key_item : r_keys)
		{
			field key_temp = *key_item;  //создадим копио объекта
			key_temp.Xcoord = key_base.Xcoord; //Формирование ключа
			key_temp.Ycoord = key_base.Ycoord + r_key; //Формирование ключа
			for (const field& item : fields)
			{
				//выбираем только однострочные с ключом элементы
				if ((*key_item).Xcoord == item.Xcoord)
				{
					int delta = item.Ycoord - key_temp.Ycoord;//+r_key;
					if ((item.Xcoord + delta >= this->NX) || (item.Xcoord + delta <= 0)) { return; };
					if (!map[key_temp.Xcoord + delta][item.Ycoord].is_empty)
					{
						bool is_have = false;
						for (const field& item1 : fields)
						{
							if ((item1.Ycoord == key_temp.Ycoord) && (item1.Xcoord == (item.Xcoord + delta))) { is_have = true; break; }
						}
						if (!is_have)
						{
							{ return; };
							return;
						}
					}
				}
			}
			r_key++;
		}


		std::vector<field> moved;//сюда положим копию объекта 
		std::vector<field> new_keys;//сюда положим копию объекта 
		r_key = 0;
		//Перестановка
		for (const field* key_item : r_keys)
		{
			//int old_val_y = key_item->Ycoord;
			field n_key(*key_item);
			n_key.Xcoord = key_base.Xcoord; //Формирование ключа
			n_key.Ycoord = key_base.Ycoord + r_key; //Формирование ключа
			new_keys.push_back(n_key);

			for (const field& item : fields)
			{
				//выбираем только однострочные с ключом элементы
				if (key_item->Xcoord == item.Xcoord)
				{
					int delta = item.Ycoord - key_item->Ycoord;
					map[item.Xcoord][item.Ycoord].is_empty = true;
					field n_field(item);

					n_field.Ycoord = n_key.Ycoord;
					n_field.Xcoord = n_key.Xcoord + delta;
					moved.push_back(n_field);
				}
			}
			r_key++;
		}
		for (const field& item : moved)
		{
			map[item.Xcoord][item.Ycoord].is_empty = false;
			map[item.Xcoord][item.Ycoord].color = item.color;
		}
		for (field* f : r_keys)
		{
			delete f; ///////////Освобождаю память!!!!!!!!!!!!!
		}
		r_keys.clear();
		fields = moved;

		//Формирование новых ключей
		for (field &item : new_keys)
		{
			for (const field &item1 : moved)
			{
				if (item == item1)
				{
					//r_keys.push_back(&field(item));
					r_keys.push_back(new field(item));
				}
			}
		}
	}
}