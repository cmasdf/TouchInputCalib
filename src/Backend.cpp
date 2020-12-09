#include <QDebug>
#include <src/Backend.h>

Backend::Backend(QObject *parent) : QObject(parent) {
    m_lastInput = QPointF(0,0);
}

Backend::~Backend() = default;

void Backend::registerSingleton(QQmlEngine *qmlEngine) {
    QQmlContext *rootContext = qmlEngine->rootContext();
    rootContext->setContextProperty("Backend", this);
}

QPointF Backend::lastInput() {
    return m_lastInput;
}

void Backend::setLastInput(QPointF lastInput) {
    if (lastInput != m_lastInput) {
        m_lastInput = lastInput;
        emit lastInputChanged();
    }
}

void Backend::touchAreaClicked() {
    qDebug() << "Touch area clicked at" << m_lastInput;
}

