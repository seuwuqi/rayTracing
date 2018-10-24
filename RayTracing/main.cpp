#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWebEngine/qtwebengineglobal.h>
#include "FileManager.h"
#include "FilePoint.h"
#include "Scene.h"
#include "echoserver.h"

int main(int argc, char *argv[])
{
    FilePoint *filePoint = new FilePoint();
    FileManager *fileManager = new FileManager();
    fileManager->readDbfFile(filePoint);
    fileManager->readShpFile(filePoint);
    filePoint->uniformlize(50,50);
    Scene *scene = new Scene(filePoint->allPointList, filePoint->index);

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QtWebEngine::initialize();

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    EchoServer *server = new EchoServer(1234, true);
    QObject::connect(server, &EchoServer::closed, &app, &QGuiApplication::quit);
    return app.exec();
}


