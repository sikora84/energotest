#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "library_wrap.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("LibraryWrapper", new LibraryWrapper);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);

    return app.exec();
}
