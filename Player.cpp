#include "Player.hpp"
#include "functions.hpp"
#include <string>
#include <vector>



using namespace std;


Player::Player(Point _place, float _radius, TEAM_FIELD_SIDE _team_number, float _mass, float _vx, float _vy){
	place = _place;
	vx = _vx;
	vy = _vy;
	mass = _mass;
	team_number = _team_number;
	radius = _radius;
}

bool Player::is_inside_field(float window_width, float window_height){
	if ( 0 <= place.x - radius && place.x + radius <= window_width && place.y - radius >= 0 && place.y + radius <= window_height){
		return true;
	}
	return false;
}


bool Player::is_inside_rect(Rectangle rect){
	return (place.x - radius) >= rect.x && (place.x + radius) <= rect.x + rect.w 
	&& (place.y - radius) >= rect.y && (place.y + radius) <= rect.y + rect.h;
}


bool Player::is_inside_player(Point p){

	if (distance(p, place) < radius){
		return true;
	}
	return false;
	
}

void Player::set_place(Point new_place){
	place = new_place;
}

void Player::stop(){
	vx = 0;
	vy = 0;
}


void Player::initialize_velocity(Point mouse_position){
	float d = distance(mouse_position, place);

	if (d < THROW_RADIUS)
		d = THROW_RADIUS;

	vx = -(mouse_position.x - place.x)/d * MAX_INITIAL_SPEED;
	vy = -(mouse_position.y - place.y)/d * MAX_INITIAL_SPEED;
}

void Player::set_velocity(float _vx, float _vy){
	vx = _vx;
	vy = _vy;
}


bool Player::is_inside_goal(float window_width, float window_height){

	if((place.y > window_height/3 && place.y < 2*window_height/3)
	&&(distance( Point(0,   window_height/3) , place) > radius 
	|| distance( Point(0, 2*window_height/3) , place) > radius
	|| distance( Point(window_width,   window_height/3) , place) > radius 
	|| distance( Point(window_width, 2*window_height/3) , place) > radius)){
		return true;
	}
	return false;
}



void Player::correct_place(Rectangle rect){
	double go_right = rect.x + radius - place.x;
	double go_left = place.x + radius - rect.x - rect.w;
	double go_up = place.y + radius - rect.y - rect.h;
	double go_down = rect.y + radius - place.y;

	while (!is_inside_rect(rect)){
		if (rect.x > place.x - radius){
			place.x += go_right;
			vx = -vx;
		}
		if (place.x + radius > rect.x + rect.w){
			place.x -= go_left;
			vx = -vx;
		}
		if (place.y - radius < rect.y){
			place.y += go_down;
			vy = -vy;
		}
		if (place.y + radius > rect.y + rect.h){
			place.y -= go_up;
			vy = -vy;
		}
	}
}


void Player::update_place(float window_width, float window_height){
	place.x += vx * TIME_PIECE;
	place.y += vy * TIME_PIECE;
	correct_place(Rectangle(0, 0, window_width, window_height));
}



void Player::update_velocity(){
	if (vx != 0){
		if (abs(vx) >= ACCELERATION * TIME_PIECE)
			vx = (abs(vx) - ACCELERATION * TIME_PIECE) 
			* copysign(1, vx);
		else
			vx = 0;
	}
	if (vy != 0){
		if (abs(vy) >= ACCELERATION * TIME_PIECE)
			vy = (abs(vy) - ACCELERATION * TIME_PIECE) 
			* copysign(1, vy);
		else
			vy = 0;
	}
}

string Player::create_player_file_name(){
	string file_name = "Player";
	file_name += '1' + team_number;
	file_name += ".png";
	return file_name;
}

void Player::draw_player(Window* window){

	if (is_inside_player(get_current_mouse_position())){
		window->fill_circle(place, radius + 3, BLUE);
	}
	window->draw_img(create_player_file_name(),
	 Rectangle(place.x - radius, place.y - radius,
	 	2 * radius, 2 * radius));
}
