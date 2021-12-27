#ifndef _PLAYER
#define _PLAYER

#include "rsdl.hpp"
#include "functions.hpp"
#include "Macros.hpp"
#include <cstdlib>


class Player{

public:
	Player(Point _place, float _radius, TEAM_FIELD_SIDE _team_number, float _mass, float _vx = 0,  float _vy = 0);
	bool is_inside_field(float window_width, float window_height);
	TEAM_FIELD_SIDE get_team_number(){ return team_number;}
	Point get_place(){ return place;}
	float get_radius(){ return radius;}
	float get_vx(){ return vx;}
	float get_vy(){ return vy;}
	float get_mass(){ return mass;}
	void set_place(Point new_place);
	void set_velocity(float _vx, float _vy);
	void draw_player(Window* window);
	bool is_inside_player(Point p);
	void initialize_velocity(Point mouse_position);
	void update_place(float window_width, float window_height);
	void update_velocity();
	void correct_place(Rectangle rect);
	bool is_inside_goal(float window_width, float window_height);
	bool is_inside_rect(Rectangle rect);
	std::string create_player_file_name();
	void stop();

private:

	Point place;
	float vx;
	float vy;
	float mass;
	TEAM_FIELD_SIDE team_number;
	float radius;

};


#endif