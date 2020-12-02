#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCommandLineParser>
#include <QQuickWindow>

#include "backend.h"

int main(int argc, char *argv[]) {
    // processing command line inputs
    bool fullscreen = false;

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    // initialize the QCommandLineParser
    QCommandLineParser parser;

    // create the command line options
    QCommandLineOption fullscreenOption(QStringList() << "fullscreen", "start application in fullscreen mode");

    // assign the command line options to the parser
    parser.addHelpOption();
    parser.addOptions({
        fullscreenOption
    });

    // assign the parser process
    parser.process(app);

    // command line actions
    // command : fullscreen
    if(parser.isSet(fullscreenOption)){
        fullscreen = true;
    }

    qmlRegisterType<BackEnd>("io.qt.examples.backend", 1, 0, "BackEnd");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                if (!obj && url == objUrl)
                    QCoreApplication::exit(-1);
            }, Qt::QueuedConnection);
    engine.load(url);

    auto *wnd1 = engine.rootObjects()[0]->findChild<QQuickWindow *>("applicationWindow1");
    if(wnd1) {
        wnd1->setTitle("Touchscreen Determination 1");
        if (fullscreen) {
            wnd1->setVisibility(QWindow::FullScreen);
        }
    }
    auto *wnd2 = engine.rootObjects()[0]->findChild<QQuickWindow *>("applicationWindow2");
    if(wnd2) {
        wnd2->setTitle("Touchscreen Determination 2");
        if (fullscreen) {
            wnd2->setVisibility(QWindow::FullScreen);
        }
    }

    return QGuiApplication::exec();
}
