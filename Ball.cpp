#include "Ball.hpp"
#include "rsdl.hpp"
#include "Macros.hpp"


using namespace std;


Ball::Ball(Point _place, float _radius, float _vx, float _vy){
	place = _place;
	radius = _radius;
	vx = _vx;
	vy = _vy;
}

void Ball::stop(){
	vx = 0;
	vy = 0;
}


bool Ball::is_inside_ball(Point point){
	if (distance(point, place) < radius)
		return true;
	return false;
}


void Ball::set_place(Point _place){
	place = _place;
}

void Ball::set_velocity(float _vx, float _vy){
	vx = _vx;
	vy = _vy;
}


void Ball::draw_ball(Window* window) const{
	window->draw_img("ball.png", Rectangle(place.x - radius, place.y - radius, 2 * radius, 2 * radius));

}



bool Ball::is_goal(float window_width, float window_height){
	if ((place.y + radius <= 2 * window_height / 3 && place.y - radius >= window_height / 3) 
		&& (place.x <= 0 || place.x >= window_width)){
		return true;
	}
	return false;
}


bool Ball::is_inside_field(float window_width, float window_height){
	if ( 0 <= place.x - radius && place.x + radius <= window_width && place.y - radius >= 0 && place.y + radius <= window_height){
		return true;
	}
	return false;
}


bool Ball::is_going_inside_goal(float window_width, float window_height){

	if((place.y > window_height/3 && place.y < 2*window_height/3)
	&&(distance( Point(0,   window_height/3) , place) > radius 
	|| distance( Point(0, 2*window_height/3) , place) > radius
	|| distance( Point(window_width,   window_height/3) , place) > radius 
	|| distance( Point(window_width, 2*window_height/3) , place) > radius)){
 	
		return true;
	}
	return false;
}

void Ball::correct_place(float window_width, float window_height){

	if (is_going_inside_goal(window_width, window_height))
		return;

	double go_right = radius - place.x;
	double go_left = place.x + radius - window_width;
	double go_up = place.y + radius - window_height;
	double go_down = radius - place.y;

	while (!is_inside_field(window_width, window_height)){

		if (0 > place.x - radius){
			place.x += go_right;
			vx = -vx;
		}
		if (place.x + radius > window_width){
			place.x -= go_left;
			vx = -vx;
		}
		if (place.y - radius < 0){
			place.y += go_down;
			vy = -vy;
		}
		if (place.y + radius > window_height){
			place.y -= go_up;
			vy = -vy;
		}
	}
}


void Ball::update_place(float width, float height){

	place.x += vx * TIME_PIECE;
	place.y += vy * TIME_PIECE;
	correct_place(width, height);
}

void Ball::update_velocity(){

	if (vx != 0){
		if (abs(vx) >= ACCELERATION * TIME_PIECE)
			vx = (abs(vx) - ACCELERATION * TIME_PIECE) * copysign(1, vx);
		else
			vx = 0;
	}
	if (vy != 0){
		if (abs(vy) >= ACCELERATION * TIME_PIECE)
			vy = (abs(vy) - ACCELERATION * TIME_PIECE) * copysign(1, vy);
		else
			vy = 0;
	}
}
