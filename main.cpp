#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <cmath>
#include <sstream>

#include "rsdl.hpp"


using namespace std;

#include "functions.hpp"
#include "Field.hpp"
#include "Player.hpp"
#include "Game.hpp"



void create_initial_players(Field* field){

	Point place;
	for (int i = 0; i < LEFT_PLAYER_INITIAL_COORDINATES.size(); i++){
		place = Point(LEFT_PLAYER_INITIAL_COORDINATES[i][0],
			          LEFT_PLAYER_INITIAL_COORDINATES[i][1]);
		field->add_player(Player(place, PLAYER_RADIUS, LEFT, PLAYER_MASS));
	}
	for (int i = 0; i < LEFT_PLAYER_INITIAL_COORDINATES.size(); i++){
		place = Point(RIGHT_PLAYER_INITIAL_COORDINATES[i][0],
			          RIGHT_PLAYER_INITIAL_COORDINATES[i][1]);
		field->add_player(Player(place, PLAYER_RADIUS, RIGHT, PLAYER_MASS));
	}
}

void create_initial_ball(Field* field){
	field->set_ball(Ball(Point(WIDTH/2, HEIGHT/2), BALL_RADIUS));

}

void initialize_field(Field* field){
	create_initial_players(field);
	create_initial_ball(field);
}

void get_number_of_rounds_and_goals_to_win(int& rounds, int& goals){
	cout << "Please enter number of rounds and goals to win repectively: "<< endl;
	cin >> rounds >> goals;
}


Game* create_game(){
	Field field(WIDTH, HEIGHT);
	initialize_field(&field);
	int rounds_no, goals_to_win_no;
	get_number_of_rounds_and_goals_to_win(rounds_no, goals_to_win_no);
	Game* game = new Game(field, STARTER, PLAYERS_NUMBER, rounds_no, goals_to_win_no);
	return game;
}


int main(){
	create_game()->play_game();
	return 0;
}