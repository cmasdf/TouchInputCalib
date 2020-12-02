#include "backend.h"
#include <QGuiApplication>
#include <QDebug>

BackEnd::BackEnd(QObject *parent) : QObject(parent) {
    QObject::connect(this, SIGNAL(counter_reached()), QGuiApplication::instance(), SLOT(quit()));
}

void BackEnd::buttonClicked() {

}

BackEnd::~BackEnd() {
}
