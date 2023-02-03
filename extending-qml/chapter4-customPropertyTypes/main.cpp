#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick/QQuickView>


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

//    QQmlApplicationEngine engine;
//    const QUrl url(u"qrc:/chapter1-basics/main.qml"_qs);
//    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
//                     &app, [url](QObject *obj, const QUrl &objUrl) {
//        if (!obj && url == objUrl)
//            QCoreApplication::exit(-1);
//    }, Qt::QueuedConnection);
//    engine.load(url);

    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl(u"qrc:/chapter1-basics/main.qml"_qs));
    view.show();

    return app.exec();
}
