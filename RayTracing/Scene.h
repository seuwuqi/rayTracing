#pragma once
#include<QDebug>

#include "MyObject.h"
#include "Point.h"
#include<vector>
#include<algorithm>
#include "boundrect.h"
using namespace std;
class Scene
{
public:
    vector<MyObject*> objList;
public:
    Scene() {

    }
    Scene(vector<Point*> allPointList, vector<int> objIndex) {
        int startPosi = 0;
        int endPosi = 0;
        for (int i = 0; i < objIndex.size(); i++) {
            endPosi = objIndex[i];
            vector<Point*> b(endPosi-startPosi);
            copy(allPointList.begin() + startPosi, allPointList.begin() + endPosi, b.begin());
            MyObject *obj = new MyObject(b, i);
            objList.push_back(obj);
            startPosi = endPosi;
        }
    }
    ~Scene() {}
    vector<BoundRect*> getKDTreeDataSet(){
        vector<BoundRect*> boundRect;
        for(int i=0;i<objList.size();i++){
            double xmax=objList[i]->pointList[0]->x,ymax=objList[i]->pointList[0]->y,xmin=objList[i]->pointList[0]->x,ymin=objList[i]->pointList[0]->y;
            for(int j=0;j<objList[i]->pointList.size();j++){
                Point* temp=new Point(objList[i]->pointList[j]);
                if(temp->x<xmin)
                    xmin=temp->x;
                if(temp->x>xmax)
                    xmax=temp->x;
                if(temp->y<ymin)
                    ymin=temp->y;
                if(temp->y>ymax)
                    ymax=temp->y;
            }
            BoundRect *b=new BoundRect(xmax,xmin,ymax,ymin);
            boundRect.push_back(b);
        }
//        qDebug()<<"boundRect size:"<<boundRect.size();
//        for(int i=0;i<boundRect.size();i++){
//            qDebug()<<i<<":"<<boundRect.at(i)->centre->x<<","<<boundRect.at(i)->centre->y;
//        }
        return boundRect;
    }
};

