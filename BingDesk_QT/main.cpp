#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QProcess>
#include <QDebug>
#include <QQmlContext>
#include <QObject>
#include "wallpapermanager.h"
#include <QtQuick/QQuickView>


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    WallpaperManager manager;

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/BingDesk_QT/Main.qml"));
    engine.rootContext()->setContextProperty("wallpaperManager", &manager);
    engine.load(url);
    // QQuickView view;
    // view.setResizeMode(QQuickView::SizeRootObjectToView);
    // view.setSource(QUrl("qrc:/BingDesk_QT/Main.qml"));
    // view.show();


    return app.exec();
}

