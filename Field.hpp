#ifndef _FIELD
#define _FIELD

#include "rsdl.hpp"
#include "functions.hpp"
#include "Player.hpp"
#include "Ball.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <complex>


class Field{

public:
	Field(float _width = 0, float _height = 0, TEAM_FIELD_SIDE _current_team_turn = LEFT);
	Ball get_ball() const{ return ball;}
	float get_height() const{ return height;}
	float get_width() const{ return width;}
	void set_lclicked_point(Point point);
	void set_lreleased_point(Point point);
	void add_player(Player player);
	void set_ball(Ball _ball);
	void move_player(Player* player);
	Player* find_clicked_player();
	bool identical_players(Player p1, Player p2);
	bool no_movement();
	void update_field();
	bool move_is_valid(Player* player, Ball* ball);
	std::vector<int> find_not_overlaped_players_index();
	void remove_ball_overlap();
	void remove_players_overlap();
	void remove_2players_overlap(Player* p1, Player* p2);
	Player* ball_overlaps();
	bool players_overlap();
	Player* player_overlaps(int i);
	std::vector<Player> get_players() const { return players;}
	bool ball_in_goal(float width, float height);
	void draw_players(Window* window);
	void draw_field(Window* window);
	bool is_next_to_wall(Player* p, char side = ' ');
	bool player_is_stuck_between_wall_and_player(int player_index);
	void draw_circle_and_arrow(Window* window);
	void change_team();
	bool is_move_done(){return move_is_done;}
	void initialize_ball_place();
	void initialize_players_place();
	void initialize_field();
	void initialize_velocities();
	void remove_overlaps();
	void update_places();
	void update_velocities(std::vector<int> not_overlaped_players_index);
	void handle_clicked_place();
	void set_place_after_2players_hit(Player* p1, Player* p2);
	void set_place_after_player_and_ball_hit(Player* p);
	void draw_dotted_circle(Window* window);

private:
	float width, height;
	std::vector<Player> players;
	Ball ball;
	Point lclicked_point;
	Point lreleased_point;
	TEAM_FIELD_SIDE current_team_turn;
	bool move_is_done;
};

#endif