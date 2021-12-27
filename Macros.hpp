#ifndef _MACROS
#define _MACROS


#define WIDTH 800
#define HEIGHT 480
#define GAME_NAME "SOCCER STARS"
#define PLAYERS_NUMBER 10
typedef enum TEAM_FIELD_SIDE{LEFT, RIGHT} TEAM_FIELD_SIDE;
#define STARTER LEFT
#define TIME_PIECE 0.01
#define THROW_RADIUS 60
#define MAX_INITIAL_SPEED 500
#define ACCELERATION 300
#define PLAYER_MASS 2
#define BALL_MASS 1.5
#define FIELD_PIC_NAME "field.jpg"
#define ARROW_NAME "arrow.jpg"
#define DOTTED_CIRCLE_NAME "dotted_circle3.png"
const std::vector<std::vector<float>> LEFT_PLAYER_INITIAL_COORDINATES = {{WIDTH/8, HEIGHT/2}, {WIDTH/6, HEIGHT/4}, {WIDTH/6, 3*HEIGHT/4}, {WIDTH/3, HEIGHT/3}, {WIDTH/3, 2*HEIGHT/3}};
const std::vector<std::vector<float>> RIGHT_PLAYER_INITIAL_COORDINATES = {{7*WIDTH/8, HEIGHT/2}, {5*WIDTH/6, HEIGHT/4}, {5*WIDTH/6, 3*HEIGHT/4}, {2*WIDTH/3, HEIGHT/3}, {2*WIDTH/3, 2*HEIGHT/3}};


#define GOAL_PIC_NAME "goal.png"
#define SCORE_BOARD_PIC "score_board.png"
#define GOAL_BOARD_PIC "goal_board.png"
#define FONT "FreeSans.ttf"
#define WINNER_PIC "winner.png"
#define BOARDS_MARGIN 50
#define PLAYER_RADIUS 15
#define BALL_RADIUS 10
#define MESSAGE_DELAY 3000
#define NOTIF_DELAY 1000

#endif