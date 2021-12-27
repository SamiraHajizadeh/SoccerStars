#include "Line.hpp"



/*Line::Line(float _slope, Point _point){
	slope = _slope;
	point = _point;	
}


Point Line::intersection(Line l1, Line l2){


	float a = l1.get_slope(), b = l2.get_slope();
	float c = (a * l1.get_point().x) - l1.get_point().y;
	float d = (b * l2.get_point().x) - l2.get_point().y;


	return Point((d - c)/(a - b), a *(d - c)/ (a - b) + c); 
}




float Line::distance_to_line(Point _point){
	Point p = intersection(Line(- 1 / slope, _point), *this);
	return distance(p, _point);
}*/