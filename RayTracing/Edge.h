#pragma once
#include "Point.h"
#include "math.h"

class Edge
{
private:
	int MAX_K = 200000;
public:
	int index;
	Point *startPoint;
	Point *endPoint;
	double distanceFromS = 0;
	double xMin, yMin, xMax, yMax;//�߶εı߽�
	double k;//б��
	double b;//b
	double hight;
	bool vertical;
	double *direction = new double[2];//��������
	double dAngle;
	double nAngle; //�ⷨ����
public:
	Edge() {
		for (int i = 0; i < 2; i++) {
			direction[i] = 0;
		}
	}
	Edge(Point *p1, Point *p2) {
		startPoint = p1;
		endPoint = p2;
		direction[0] = endPoint->x - startPoint->x;
		direction[1] = endPoint->y - startPoint->y;//��������
		setAngle();
		xMin = p1->x < p2->x ? p1->x : p2->x;
		xMax = p1->x > p2->x ? p1->x : p2->x;
		yMin = p1->y < p2->y ? p1->y : p2->y;
		yMax = p1->y > p2->y ? p1->y : p2->y;
		if (p1->x - p2->x == 0) {
			k = MAX_K;
			vertical = true;
		}
		else {
			vertical = false;
			k = (p1->y - p2->y) / (p1->x - p2->x);
		}
		b = p1->y - k * p1->x;
		hight = p1->z;

	}
	~Edge(){}
	void setAngle() {
		if (direction[0] == 0) {
			if (direction[1] > 0) {
				dAngle = 90;
			}
			else {
				dAngle = 270;
			}
		}
		else {//�Ǵ�ֱ��
			double temp = abs(atan(direction[1] / direction[0]));
			temp = temp * 180.0 / 3.1415926;
			if (direction[0] > 0 && direction[1] >= 0) {//��һ����
				dAngle = temp;
			}
			else if (direction[0] > 0 && direction[1] < 0) {//��������
				dAngle = 360 - temp;
			}
			else if (direction[0] < 0 && direction[1] >= 0) {//�ڶ�����
				dAngle = 180 - temp;
			}
			else {//��������
				dAngle = 180 + temp;
			}
		}
		nAngle = dAngle + 90;
		if (nAngle > 360) {
			nAngle -= 360;
		}
	}
};

