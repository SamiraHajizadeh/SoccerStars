#include "rsdl.hpp"
#include "functions.hpp"
#include "Macros.hpp"
#include "Player.hpp"
#include "Ball.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <complex>
#include <cmath>


#include "Field.hpp"

using namespace std;

Field::Field(float _width, float _height, TEAM_FIELD_SIDE _current_team_turn){
	width = _width;
	height = _height;
	current_team_turn = _current_team_turn;
	move_is_done = false;
}

void Field::set_ball(Ball _ball){
	ball = _ball;
}


void Field::add_player(Player player){
	players.push_back(player);
}

void Field::set_lclicked_point(Point point){
	lclicked_point = point;
}


void Field::set_lreleased_point(Point point){
	lreleased_point = point;
}


Player* Field::find_clicked_player(){
	if (lclicked_point.x != -1){
		for (int i = 0; i < players.size(); i++){
			if (players[i].is_inside_player(lclicked_point)){
				return &players[i];
			}
		}
	}
	return nullptr;
}


bool Field::no_movement(){
	for (Player p : players){
		if (p.get_vx() != 0 || p.get_vy() != 0)
			return false;
	}
	if (ball.get_vy() != 0 || ball.get_vy() != 0)
		return false;

	return true;
}


void Field::change_team(){
	lclicked_point = Point(-1, -1);
	move_is_done = false;
	if (current_team_turn == LEFT)
		current_team_turn = RIGHT;
	else
		current_team_turn = LEFT;
}


Player* Field::player_overlaps(int index){
	
	for (int i = 0; i < players.size(); i++){
		if (i != index && distance(players[index].get_place(), players[i].get_place())
		< players[index].get_radius() + players[i].get_radius() - 2)
			return &players[i];
	}
	return nullptr;

}


bool Field::players_overlap(){
	for (int i = 0; i < players.size(); i++){
		if (player_overlaps(i) != nullptr){
			return true;
		}
	}
	return false;
}

Player* Field::ball_overlaps(){

	for (int i = 0; i < players.size(); i++){
		if (distance(players[i].get_place(), ball.get_place())
			< players[i].get_radius() + ball.get_radius() - 2){
			return &players[i];
		}
	}
	return nullptr;
}



void Field::set_place_after_2players_hit(Player* p1, Player* p2){
	float d = distance(p1->get_place(), p2->get_place());


	float common_part =(2 * PLAYER_MASS /(PLAYER_MASS + PLAYER_MASS))
			*((p1->get_vx() - p2->get_vx())*(p1->get_place().x - p2->get_place().x) 
			+ (p1->get_vy() - p2->get_vy())*(p1->get_place().y - p2->get_place().y))
			/(d * d);

	if (d != 0){

		float new_v1x = p1->get_vx() - common_part
			*(p1->get_place().x - p2->get_place().x);

		float new_v1y = p1->get_vy() - common_part
		*(p1->get_place().y - p2->get_place().y);
	
		float new_v2x = p2->get_vx() - common_part
		*(p2->get_place().x - p1->get_place().x);
		
		float new_v2y = p2->get_vy() - common_part
		*(p2->get_place().y - p1->get_place().y);

		p1->set_velocity(new_v1x, new_v1y);
		p2->set_velocity(new_v2x, new_v2y);
	}	
}

void Field::remove_2players_overlap(Player* p1, Player* p2){

	double v2 = sqrt(p2->get_vx() * p2->get_vx() + p2->get_vy() * p2->get_vy());
	double v1 = sqrt(p1->get_vx() * p1->get_vx() + p1->get_vy() * p1->get_vy());
	double d = distance(p1->get_place(), p2->get_place());

	double should_move = p1->get_radius() + p2->get_radius() - d;
	double t;
	if (v1 + v2 != 0)
		t = should_move / (v1 + v2);
	else
		t = 0;

	p1->set_place(Point(p1->get_place().x - t * p1->get_vx(),
		                p1->get_place().y - t * p1->get_vy()));
	p2->set_place(Point(p2->get_place().x - t * p2->get_vx(),
	                    p2->get_place().y - t * p2->get_vy()));
	set_place_after_2players_hit(p1, p2);
}


void Field::remove_players_overlap(){

	Player* p;
	while(players_overlap()){
		for (int i = 0; i < players.size(); i++){
			if ((p = player_overlaps(i)) != nullptr){
				remove_2players_overlap(p, &players[i]);
			}
		}
	}
}


void Field::set_place_after_player_and_ball_hit(Player* p){
	float d = distance(p->get_place(), ball.get_place());

	float common_part =((p->get_vx() - ball.get_vx())*(p->get_place().x - ball.get_place().x) 
			+ (p->get_vy() - ball.get_vy())*(p->get_place().y - ball.get_place().y))
			/(d * d);

	if (d != 0){
		float new_vx_player = p->get_vx() - (2*BALL_MASS/(PLAYER_MASS + BALL_MASS))
		* common_part *(p->get_place().x - ball.get_place().x);

		float new_vy_player = p->get_vy() - (2*BALL_MASS /(PLAYER_MASS + BALL_MASS))
		* common_part *(p->get_place().y - ball.get_place().y);

		float new_vx_ball = ball.get_vx() - (2*PLAYER_MASS /(PLAYER_MASS + BALL_MASS))
		* common_part *(ball.get_place().x - p->get_place().x);

		float new_vy_ball = ball.get_vy() - (2*PLAYER_MASS /(PLAYER_MASS + BALL_MASS))
		* common_part *(ball.get_place().y - p->get_place().y);

		p->set_velocity(new_vx_player, new_vy_player);
		ball.set_velocity(new_vx_ball, new_vy_ball);
	}
}

void Field::remove_ball_overlap(){

	Player* p;
	while((p = ball_overlaps()) != nullptr){

		float v_player = sqrt(p->get_vx() * p->get_vx() + p->get_vy() * p->get_vy());
		float v_ball = sqrt(ball.get_vx() * ball.get_vx() + ball.get_vy() * ball.get_vy());
		float d = distance(p->get_place(), ball.get_place());

		double should_move = p->get_radius() + ball.get_radius() - d;
		double t;
		if (v_player + v_ball != 0)
			t = should_move / (v_player + v_ball);
		else
			t = 0;

		p->set_place(Point( p->get_place().x - t * p->get_vx(),
		                    p->get_place().y - t * p->get_vy()));
		ball.set_place(Point(ball.get_place().x - t * ball.get_vx(),
	                         ball.get_place().y - t * ball.get_vy()));


		set_place_after_player_and_ball_hit(p);
	}
}


vector<int> Field::find_not_overlaped_players_index(){
	vector<int> indexes;
	for (int i = 0; i < players.size(); i++){
		if (player_overlaps(i) == nullptr)
			indexes.push_back(i);
	}
	return indexes;
}

bool Field::ball_in_goal(float width, float height){
	return ball.is_goal(width, height);
}

void Field::initialize_ball_place(){
	ball.set_place(Point(width/2, height/2));
}

void Field::initialize_players_place(){
	Point place;
	for (int i = 0; i < 5; i++){
		players[i].set_place(Point(LEFT_PLAYER_INITIAL_COORDINATES[i][0]
			               , LEFT_PLAYER_INITIAL_COORDINATES[i][1]));
	}

	for (int i = 0; i < 5; i++){
		players[i + 5].set_place(Point(RIGHT_PLAYER_INITIAL_COORDINATES[i][0]
			               , RIGHT_PLAYER_INITIAL_COORDINATES[i][1]));
	}
}

void Field::initialize_velocities(){
	for (int i = 0; i < players.size(); i++){
		players[i].stop();
	}
	ball.stop();
}

void Field::initialize_field(){
	initialize_ball_place();
	initialize_players_place();
	initialize_velocities();

}


void Field::remove_overlaps(){
	while (players_overlap() || ball_overlaps() != nullptr){
		remove_players_overlap();
		remove_ball_overlap();
	}
}

void Field::update_places(){
	for (int i = 0; i < players.size(); i++){
		players[i].update_place(width, height);
	}
	ball.update_place(width, height);
}


void Field::update_velocities(vector<int> not_overlaped_players_index){
	for (int j = 0; j < not_overlaped_players_index.size(); j++){
		players[not_overlaped_players_index[j]].update_velocity();
	}
	ball.update_velocity();
}

void Field::handle_clicked_place(){
	Player* p = find_clicked_player();

	if (p != nullptr && lreleased_point.x != -1 
		&& current_team_turn == p->get_team_number()
		&& move_is_done == false){
		p->initialize_velocity(lreleased_point);
		move_is_done = true;
	}
}

void Field::update_field(){

	vector<int> not_overlaped_players_index = find_not_overlaped_players_index();
	
	handle_clicked_place();
	update_places();
	remove_overlaps();
	update_velocities(not_overlaped_players_index);
}

void Field::draw_dotted_circle(Window* window){
	Player* p = find_clicked_player();

	if (p != nullptr && lreleased_point.x == -1 && 
		current_team_turn == p->get_team_number()){

		Point mouse_position = get_current_mouse_position();
		float d = distance(mouse_position, p->get_place());
		if (d > THROW_RADIUS)
				d = THROW_RADIUS;
		window->draw_img(DOTTED_CIRCLE_NAME, Rectangle(p->get_place().x - d,
			p->get_place().y - d, 2 * d, 2 * d));
	}
}

void Field::draw_players(Window* window){
	for (Player x : players){
		x.draw_player(window);
	}
}


void Field::draw_field(Window* window){

	window->draw_img(FIELD_PIC_NAME, Rectangle(0, 0, WIDTH, HEIGHT));
	draw_dotted_circle(window);
	draw_players(window);
	ball.draw_ball(window);
	window->update_screen();
}