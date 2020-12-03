#include "backend.h"
#include <QGuiApplication>
#include <QDebug>

BackEnd::BackEnd(QObject *parent) : QObject(parent) {}

void BackEnd::buttonClicked(QPointF point) {
    qDebug() << "Button clicked at" << point;
}

BackEnd::~BackEnd() = default;
