#ifndef BOUNDRECT_H
#define BOUNDRECT_H
#include<QDebug>

#include "Point.h"

using namespace std;

class BoundRect
{
public:
    Point* p1,p2,p3,p4;
    Point* centre;
public:
//    BoundRect(Point* point1,Point* point2,Point* point3,Point* point4,Point* pointcentre) {
//        this->centre=new Point(pointcentre);
//        this->p1=new Point(point1);
//        this->p2=new Point(point2);
//        this->p3=new Point(point3);
//        this->p4=new Point(point4);
//    }
    BoundRect(double xmax,double xmin,double ymax,double ymin){
        p1=new Point(xmin,ymin,0);
        p2=new Point(xmin,ymax,0);
        p3=new Point(xmax,ymax,0);
        p4=new Point(xmax,ymin,0);
        centre=new Point((xmin+xmax)/2,(ymax+ymin)/2,0);
//        qDebug()<<centre->x<<","<<centre->y;
    }
    void toString(){

    }
};
#endif // BOUNDRECT_H
