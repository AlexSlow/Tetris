#include <iostream>
#include "settings.h"

settings::settings() {
	this->base_speed = 0;
	this->speed_increese = 0;
}
  
settings::~settings() {
}
settings::settings(const settings &ref) {
	this->base_speed = ref.base_speed;
	this->speed_increese = ref.speed_increese;
}
int settings::get_speed() const { return this->base_speed; }
int settings::get_increese() const { return this->speed_increese; }
int settings::get_amout_blocks_into_lineX() const { return this->amout_of_blocks_into_lineX; }
int settings::get_amout_blocks_into_lineY() const { return this->amout_of_blocks_into_lineY; }


 settings&  settings:: operator=(settings& ref) {
	 this->base_speed = ref.base_speed;
	 this->speed_increese = ref.speed_increese;
	 return *this;
}


//BUILDER
settings::builder:: builder() {
	this->Settings = new settings;
}
settings::builder:: ~builder() {
}
settings::builder::builder(const builder &ref) {

}

settings::builder* settings::builder::set_speed(int s) {  this->Settings->base_speed=s; return this;}
settings::builder* settings::builder::set_increese(int i) {  this->Settings->speed_increese=i; return this;}
settings::builder* settings::builder::set_amout_of_blocks_into_lineX(int i) { this->Settings->amout_of_blocks_into_lineX = i; return this; }
settings::builder* settings::builder::set_amout_of_blocks_into_lineY(int i) { this->Settings->amout_of_blocks_into_lineY = i; return this; }

settings* settings::builder::build() { return Settings; }