#include "functions.hpp"
//#define enum FIELD_SIDE{LEFT, RIGHT};

typedef Point ordered_pair;


struct Line{
	float slope;
	Point point;
};
typedef Line Line;


using namespace std;

float distance(Point p1, Point p2){

	float x = p1.x - p2.x;
	float y = p1.y - p2.y;

	return sqrt((x * x) + (y * y));
}

float mouse_from_point(Point p){
	Point current = get_current_mouse_position();
	return distance(current, p);
}


bool point_is_inside_rect(Rectangle rect, Point point){
	return point.x >= rect.x && point.x <= rect.x + rect.w 
	&& point.y >= rect.y && point.y <= rect.y + rect.h;
}