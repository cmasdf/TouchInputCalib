#include <QDebug>
#include <src/MainAreaBackend.h>

MainAreaBackend::MainAreaBackend(QObject *parent) : QObject(parent) {
    m_lastInput = QPointF(0,0);
}

MainAreaBackend::~MainAreaBackend() = default;

void MainAreaBackend::registerSingleton(QQmlEngine *qmlEngine) {
    QQmlContext *rootContext = qmlEngine->rootContext();
    rootContext->setContextProperty("MainAreaBackend", this);
}

QPointF MainAreaBackend::lastInput() {
    return m_lastInput;
}

void MainAreaBackend::setLastInput(QPointF lastInput) {
    if (lastInput != m_lastInput) {
        m_lastInput = lastInput;
        emit lastInputChanged();
    }
}
