#include "echoserver.h"
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include <QtCore/QDebug>
#include <QJsonObject>

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
        pClient->sendTextMessage(message);
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
    for(int i=0;i<scene->objList.size();i++){
        QMap<QString,QVariant> myMap;
        QList<QVariant> posList;
        for(int j=0;j<scene->objList[i]->pointList.size();j++){
            QPointF qf(scene->objList[i]->pointList[j]->x,scene->objList[i]->pointList[j]->y);
            QVariant a(qf);
            posList.append(qf);
        }
        QVariant xyL(posList);
        myMap.insert("xy",xyL);
        qDebug()<<QVariant(posList);
//        myMap.insert("z",QVariant(scene->objList[i]->z));
        mapMap.insert(QString(i),QVariant(myMap));
    }
    qDebug()<<"mapMap size is "<<mapMap.size();
    QJsonObject qjs;
    QJsonObject qjss=qjs.fromVariantMap(mapMap);
    qDebug()<<"QJsonObject size is "<<qjss;
}
