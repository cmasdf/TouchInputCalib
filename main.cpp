#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QCommandLineParser>
#include <QQuickWindow>
#include <QtTest/QAbstractItemModelTester>

#include <src/Monitor.h>
#include <src/InputDevice.h>
#include <src/Mapping.h>
#include <src/MainAreaBackend.h>
#include <model/AppWindowModel.h>
#include <model/AppWindowData.h>

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    // create list of active monitors
    auto monitor = Monitor();
    // create list of touch input devices
    auto inputDev = InputDevice();

    QQmlApplicationEngine engine;

    // app window model
    AppWindowModel appWindowModel;
    engine.rootContext()->setContextProperty("ApplicationDataModel", &appWindowModel);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                if (!obj && url == objUrl)
                    QCoreApplication::exit(-1);
            }, Qt::QueuedConnection);

    QVector<Monitor_t> monitors = monitor.getListOfMonitors();

    // create a fullscreen application window on each display
    for (int i=0; i<monitors.size(); i++) {
        AppWindowData appWindowData("Touchscreen Determination" + QString::number(i),
                                    "applicationWindow" + QString::number(i),
                                    QString(monitors[i].nameString) + ": " + QString::number(monitors[i].width) + "x" +
                                    QString::number(monitors[i].height) + "+" + QString::number(monitors[i].x) + "+" +
                                    QString::number(monitors[i].y),
                                    monitors[i].width, monitors[i].height, monitors[i].x, monitors[i].y);

        appWindowModel.addAppWindowData(appWindowData);
    }

    // register main area backend
    auto *mainAreaBackend = new MainAreaBackend();
    mainAreaBackend->registerSingleton(&engine);

    engine.load(url);

    // initialize mapping
    auto* mapping = new Mapping(monitor.getListOfMonitors(), inputDev.getListOfInputDevices(), mainAreaBackend, &engine);

    auto rootObject = engine.rootObjects()[0];
    rootObject->setProperty("visibility", QWindow::FullScreen);

    // start mapping
    mapping->mappingStart();

    return QGuiApplication::exec();
}
