#ifndef _GAME
#define _GAME

#include "rsdl.hpp"
#include "functions.hpp"
#include "Ball.hpp"
#include "Player.hpp"
#include "Field.hpp"
#include "Macros.hpp"

#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

class Game{

public:
	Game(Field _field, TEAM_FIELD_SIDE _current_team_turn, int _player_number,
	int _rounds_number, int _goals_to_win, std::vector<int> _teams_scores = {0, 0},
	std::vector<int> _current_round_goals = {0, 0});
	void play_game();
	void update_game();
	bool game_is_over();
	void change_team();
	bool check_if_goal();
	TEAM_FIELD_SIDE goal_place();
	void add_goal_to_team();
	void print_winner(int team_number);
	void score_round_winner(int index);
	bool round_is_over();
	void change_round();
	void print_goal();
	void draw_boards();
	void draw_score_board();
	void draw_goal_board();


private:
	Field field;
	TEAM_FIELD_SIDE current_team_turn;
	int player_number;
	int goals_to_win;
	std::vector<int> current_round_goals;
	std::vector<int> teams_scores;
	int rounds_number;
	Window* window;
};

#endif