#ifndef BACKEND_H
#define BACKEND_H
#include<QDebug>

#include <QObject>
#include <QString>
#include "FilePoint.h"
#include "FileManager.h"
#include "Scene.h"
#include "kdtree.h"
class BackEnd : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)

public:
    explicit BackEnd(QObject *parent = nullptr);
    bool readState=false;
    QList<qreal> centreX;
    QList<qreal> centreY;
    Q_INVOKABLE QList<qreal> getListX(){
        if(!readState){
            qDebug()<<"getListX";
            readKDTreeData();
        }
        return centreX;
    }
    Q_INVOKABLE QList<qreal> getListY(){
        if(!readState){
            qDebug()<<"getListY";
            readKDTreeData();
        }
        return centreY;
    }
    QString userName();
    KDTree *kdTree;
    void setUserName(const QString &userName);
    void readKDTreeData(){
        FilePoint *filePoint = new FilePoint();
        FileManager *fileManager = new FileManager();
        fileManager->readDbfFile(filePoint);
        fileManager->readShpFile(filePoint);
        filePoint->uniformlize(50,50);
        Scene *scene = new Scene(filePoint->allPointList, filePoint->index);
        kdTree=new KDTree(scene);
        for(int i=0;i<kdTree->positionList.size();i++){
            centreX.append(kdTree->positionList[i]->centre->x);
            centreY.append(kdTree->positionList[i]->centre->y);
        }
        readState=true;
    }


signals:
    void userNameChanged();

private:
    QString m_userName;
};


#endif // BACKEND_H
