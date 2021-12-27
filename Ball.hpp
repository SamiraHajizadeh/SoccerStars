#ifndef _BALL
#define _BALL

#include "rsdl.hpp"
#include "functions.hpp"
#include "Player.hpp"


class Ball{

public:
	Ball(Point _place = Point(-1, -1), float _radius = 0, float _vx = 0,  float _vy = 0);
	void draw_ball(Window* window) const;
	Point get_place(){ return place;}
	float get_radius(){return radius;}
	float get_vx(){return vx;}
	float get_vy(){return vy;}
	bool is_inside_ball(Point point);
	void update_place(float width, float height);
	void update_velocity();
	void set_place(Point _place);
	void set_velocity(float _vx, float _vy);
	void correct_place(float window_width, float window_height);
	bool is_inside_field(float window_width, float window_height);
	bool is_goal(float window_width, float window_height);
	bool is_going_inside_goal(float window_width, float window_height);
	void stop();


private:
	Point place;
	float radius;
	float vx;
	float vy;
};



#endif