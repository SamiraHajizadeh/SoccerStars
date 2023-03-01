#include "Game.hpp"


using namespace std;

Game::Game(Field _field, TEAM_FIELD_SIDE _current_team_turn, int _player_number,
int _rounds_number, int _goals_to_win, std::vector<int> _teams_scores,
std::vector<int> _current_round_goals){

	field = _field;
	current_team_turn = _current_team_turn;
	player_number = _player_number;
	rounds_number = _rounds_number;
	goals_to_win = _goals_to_win;
	teams_scores = _teams_scores;
	current_round_goals = _current_round_goals;

	window = new Window(WIDTH, HEIGHT + BOARDS_MARGIN, GAME_NAME);
}


void Game::print_winner(int team_number){
	stringstream str;
	str << "team number " <<  team_number << " has won " << teams_scores[team_number - 1] << " rounds!";
	window->clear();
	window->fill_rect(Rectangle(0, 0, field.get_width(), field.get_height() + BOARDS_MARGIN), WHITE);
	window->show_text(str.str(),Point(field.get_width()/3, field.get_height()/6), BLACK);
	window->draw_img(WINNER_PIC, Rectangle(field.get_width()/4, field.get_height()/3, field.get_width()/2, 2*field.get_height()/3));
	window->update_screen();
	delay(MESSAGE_DELAY);
}

bool Game::game_is_over(){

	for (int i = 0; i < teams_scores.size(); i++){
		if (teams_scores[i] == rounds_number/2){
			print_winner(i + 1);
			return true;
		}
	}
	return false;
}



void Game::update_game(){

	Point lclick(-1, -1), lrelease(-1, -1);
	while(window->has_pending_event()){
		Event e = window->poll_for_event();
		switch(e.get_type()){
			case Event::QUIT:
				exit(0);
				break;

			case Event::LCLICK:
				lclick = e.get_mouse_position();
				field.set_lclicked_point(lclick);
				field.set_lreleased_point(Point(-1, -1));
				break;

			case Event::LRELEASE:
				lrelease = e.get_mouse_position();
				field.set_lreleased_point(lrelease);
				break;
		}
	}

	field.update_field();
}

TEAM_FIELD_SIDE Game::goal_place(){
	if (field.get_ball().get_place().x >= field.get_width())
		return RIGHT;
	return LEFT;
}


bool Game::check_if_goal(){
	return field.get_ball().is_goal(field.get_width(), field.get_height());
}

void Game::add_goal_to_team(){
	int winner;
	if (goal_place() == 0)
		winner = 1;
	else
		winner = 0;
	current_round_goals[winner] += 1;
}


void Game::change_team(){
	if (current_team_turn == LEFT){
		current_team_turn = RIGHT;
	}
	else
		current_team_turn = LEFT;
	field.change_team();
}


void Game::score_round_winner(int index){
	teams_scores[index] += 1;
}


bool Game::round_is_over(){
	for (int i = 0; i < current_round_goals.size();i++){
		if (current_round_goals[i] == goals_to_win){
			score_round_winner(i);
			for (int i = 0; i < current_round_goals.size();i++){
				current_round_goals[i] = 0;
			}
			return true;
		}
	}
	return false;
}


void Game::change_round(){
	
	field.initialize_field();
	current_team_turn = STARTER;
}

void Game::print_goal(){
	window->draw_img(GOAL_PIC_NAME, Rectangle(0, 0, field.get_width(), field.get_height()));
	window->update_screen();
	delay(NOTIF_DELAY);
}

void Game::draw_score_board(){
	window->draw_img(SCORE_BOARD_PIC, Rectangle(3*field.get_width()/4, field.get_height(), field.get_width()/4, BOARDS_MARGIN));
	window->show_text(to_string(teams_scores[0]), Point(10*field.get_width()/12, field.get_height() + BOARDS_MARGIN/3), BLACK, FONT, 20);
	window->show_text(to_string(teams_scores[1]), Point(11*field.get_width()/12, field.get_height() + BOARDS_MARGIN/3), BLACK, FONT, 20);
	window->show_text("score board", Point(10.25*field.get_width()/12 - 10, field.get_height() + BOARDS_MARGIN/7), BLACK, FONT, 10);

	window->update_screen();
}


void Game::draw_goal_board(){
	window->draw_img(GOAL_BOARD_PIC, Rectangle(field.get_width()/3, field.get_height(), field.get_width()/3, BOARDS_MARGIN));
	window->show_text(to_string(current_round_goals[0]), Point(5*field.get_width()/12, field.get_height() + BOARDS_MARGIN/5), WHITE, FONT, 15);
	window->show_text(to_string(current_round_goals[1]), Point(7*field.get_width()/12, field.get_height() + BOARDS_MARGIN/5), WHITE, FONT, 15);
	window->show_text("goals", Point(field.get_width()/2 - 15, field.get_height() + BOARDS_MARGIN/4), BLACK, FONT, 10);
	window->update_screen();

}

void Game::draw_boards(){
	draw_score_board();
	draw_goal_board();
}

void Game::play_game(){

	current_team_turn = LEFT;
	while(!game_is_over()){

		update_game();
		field.draw_field(window);
		draw_boards();

		if (check_if_goal()){
			add_goal_to_team();
			field.initialize_field();
			print_goal();
		}
		if(field.no_movement() && field.is_move_done())
			change_team();
		if (round_is_over())
			change_round();
		delay(TIME_PIECE * 1000);
	}
}