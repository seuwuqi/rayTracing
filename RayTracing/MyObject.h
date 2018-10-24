#pragma once
#include <vector>
#include "Point.h"
#include "Edge.h"
using namespace std;
class MyObject
{
public:
	vector<Point*> pointList;
	vector<Edge*> edgeList;
	double z;
	int index;
public:
	MyObject(){}
	MyObject(vector<Point*> pointList, int index) {
		this->pointList = pointList;
		this->index = index;
		this->z = pointList.front()->z;
	}
	~MyObject(){}
	void setEdgeList(vector<Point*> pointList) {
		int count = 0;
        for(int i=0;i<pointList.size();i++)
		{
            Point *point=pointList.at(i);
			if (count == pointList.size()) {
				Edge *edge = new Edge(point, pointList[0]);
				edgeList.push_back(edge);
			}
			Edge *edge = new Edge(point, pointList[count + 1]);
			edge->index = index;
			edgeList.push_back(edge);
			count++;
		}
	}
	void scale(double k, double x_v, double y_v) {
		for (int i = 0; i < pointList.size(); i++) {
			pointList[i]->x *= k;
			pointList[i]->x += x_v;
			pointList[i]->y *= k;
			pointList[i]->y += y_v;
		}
		setEdgeList(pointList);
	}
	void scale(double k) {
		z = z * k;
		for (int i = 0; i < pointList.size(); i++) {
			pointList[i]->x *= k;
			pointList[i]->y *= k;
			pointList[i]->z *= k;
		}
		edgeList.clear();
		setEdgeList(pointList);
	}
};

