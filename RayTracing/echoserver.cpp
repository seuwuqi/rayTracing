#include "echoserver.h"
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include <QtCore/QDebug>
#include <QJsonObject>
#include <QJsonDocument>
QT_USE_NAMESPACE

//! [constructor]
EchoServer::EchoServer(quint16 port, bool debug, QObject *parent) :
    QObject(parent),
    m_pWebSocketServer(new QWebSocketServer(QStringLiteral("Echo Server"),
                                            QWebSocketServer::NonSecureMode, this)),
    m_debug(debug)
{
    if (m_pWebSocketServer->listen(QHostAddress::Any, port)) {
        if (m_debug)
            qDebug() << "Echoserver listening on port" << port;
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
                this, &EchoServer::onNewConnection);
        connect(m_pWebSocketServer, &QWebSocketServer::closed, this, &EchoServer::closed);
    }
    updatemapMap();
}
//! [constructor]

EchoServer::~EchoServer()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

//! [onNewConnection]
void EchoServer::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &EchoServer::processTextMessage);
    connect(pSocket, &QWebSocket::binaryMessageReceived, this, &EchoServer::processBinaryMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &EchoServer::socketDisconnected);

    m_clients << pSocket;
}
//! [onNewConnection]

//! [processTextMessage]
void EchoServer::processTextMessage(QString message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
        qDebug() << "Message received:" << message;
    if (pClient) {
        QJsonObject qjss=QJsonObject::fromVariantMap(mapMap);
        QJsonDocument doc(qjss);
        QString strJson(doc.toJson(QJsonDocument::Compact));
        pClient->sendTextMessage(strJson);
    }
}
//! [processTextMessage]

//! [processBinaryMessage]
void EchoServer::processBinaryMessage(QByteArray message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
        qDebug() << "Binary Message received:" << message;
    if (pClient) {
        pClient->sendBinaryMessage(message);
    }
}
//! [processBinaryMessage]

//! [socketDisconnected]
void EchoServer::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
        qDebug() << "socketDisconnected:" << pClient;
    if (pClient) {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}
//! [socketDisconnected]
void EchoServer::updatemapMap(){
    FilePoint *filePoint = new FilePoint();
    FileManager *fileManager = new FileManager();
    fileManager->readDbfFile(filePoint);
    fileManager->readShpFile(filePoint);
    filePoint->uniformlize(50,50);
    Scene *scene = new Scene(filePoint->allPointList, filePoint->index);
    QJsonObject qjs;
    for(int i=0;i<scene->objList.size();i++){
        QMap<QString,QVariant> myMap;
        QList<QVariant> posList;
        for(int j=0;j<scene->objList[i]->pointList.size();j++){
            QMap<QString,QVariant> tempMap;
            tempMap.insert(QString("x"),QVariant(scene->objList[i]->pointList[j]->x));
            tempMap.insert(QString("y"),QVariant(scene->objList[i]->pointList[j]->y));
            tempMap.insert(QString("z"),QVariant(scene->objList[i]->pointList[j]->z));

//            tempList.append(QVariant(scene->objList[i]->pointList[j]->x));
//            tempList.append(QVariant(scene->objList[i]->pointList[j]->y));
            //QPointF qf(scene->objList[i]->pointList[j]->x,scene->objList[i]->pointList[j]->y);
            posList.append(QVariant(tempMap));
        }
//        QVariant xyL(posList);
//        myMap.insert(QString("xy"),xyL);
//        myMap.key(
//        qDebug()<<QVariant(posList);
//        myMap.insert(QString("z"),QVariant(scene->objList[i]->z));
//        qDebug()<<QJsonObject::fromVariantMap(myMap);
        mapMap.insert(QString::number(i,10),QVariant(posList));
    }
//    qDebug()<<"mapMap size is "<<mapMap.size();
//    QJsonObject qjss=QJsonObject::fromVariantMap(mapMap);
//    QJsonDocument doc(qjss);
//    QString strJson(doc.toJson(QJsonDocument::Compact));
//    qDebug()<<"QJsonObject size is "<<strJson.size();
}
