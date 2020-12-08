#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCommandLineParser>
#include <QQuickWindow>

#include <src/Monitor.h>
#include <src/InputDevice.h>
#include <src/Mapping.h>
#include <src/Backend.h>

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

    auto monitor = Monitor();
    auto inputDev = InputDevice();

    qmlRegisterType<Backend>("io.qt.examples.backend", 1, 0, "Backend");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                if (!obj && url == objUrl)
                    QCoreApplication::exit(-1);
            }, Qt::QueuedConnection);
    engine.load(url);

    QVector<Monitor_t> monitors = monitor.getListOfMonitors();

    for (int i=0; i<monitors.size(); i++) {
        QString objectName = "applicationWindow" + QString::number(i);
        auto wnd = engine.rootObjects()[0]->findChild<QQuickWindow *>(objectName);
        if (wnd) {
            wnd->setTitle("Touchscreen Determination" + QString::number(i));
            QString deviceInfo = QString(monitors[i].nameString) + ": " + QString::number(monitors[i].width) + "x" +
                                 QString::number(monitors[i].height) + "+" + QString::number(monitors[i].x) + "+" +
                                 QString::number(monitors[i].y);
            wnd->setProperty("device", deviceInfo);
            wnd->setWidth(monitors[i].width);
            wnd->setHeight(monitors[i].height);
            wnd->setX(monitors[i].x);
            wnd->setY(monitors[i].y);
            if (fullscreen) {
                wnd->setVisibility(QWindow::FullScreen);
            }
        }
    }

    auto mapping = Mapping(monitor.getListOfMonitors(), inputDev.getListOfInputDevices());

    return QGuiApplication::exec();
}
