#pragma once

#include <QObject>

class Point
{
public:
	double x = 0;
	double y = 0;
	double z = 0;
public:
    Point(){}
	Point(double x,double y,double z);
    Point(Point* p){
        x=p->x;
        y=p->y;
        z=p->z;
    }
	~Point();
};
