#include <iostream>
#include "settings.h"

settings::settings() {
	this->base_speed = 0;
	this->speed_increese = 0;
	this->display_height = 0;
	this->display_width = 0;
	this->color = nullptr;
}
  
settings::~settings() {
}
settings::settings(const settings &ref) {
	this->color = ref.color;
	this->display_height = ref.display_height;
	this->display_width = ref.display_width;
	this->base_speed = ref.base_speed;
	this->speed_increese = ref.speed_increese;
	this->color = ref.color;
}
int settings::get_width() { return this->display_width; }
int settings::get_height() { return this->display_height; }
int settings::get_speed() { return this->base_speed; }
int settings::get_increese() { return this->speed_increese; }

 settings&  settings:: operator=(settings& ref) {
	 this->color = ref.color;
	 this->display_height = ref.display_height;
	 this->display_width = ref.display_width;
	 this->base_speed = ref.base_speed;
	 this->speed_increese = ref.speed_increese;
	 this->color = ref.color;
	 return *this;
}


//BUILDER
settings::builder:: builder() {
	this->Settings = new settings;
}
settings::builder:: ~builder() {
	
//delete Settings;
}
settings::builder::builder(const builder &ref) {

}

settings::builder* settings::builder::set_width(int w) { this->Settings->display_width = w; return this; }
settings::builder* settings::builder::set_height(int h) { this->Settings->display_height=h; return this;}
settings::builder* settings::builder::set_speed(int s) {  this->Settings->base_speed=s; return this;}
settings::builder* settings::builder::set_increese(int i) {  this->Settings->speed_increese=i; return this;}

settings::builder*  settings::builder::set_color(as_color* color) { this->Settings->color = color; return this; }
settings* settings::builder::build() { return Settings; }