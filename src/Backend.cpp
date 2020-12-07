#include <QDebug>
#include <src/Backend.h>

Backend::Backend(QObject *parent) : QObject(parent) {}

Backend::~Backend() = default;

void Backend::buttonClicked(QPointF point) {
    qDebug() << "Button clicked at" << point;
}

