#include "backend.h"
#include <QGuiApplication>
#include <QDebug>
#include <X11/extensions/Xrandr.h>
#include <X11/Xlib.h>

BackEnd::BackEnd(QObject *parent) : QObject(parent) {}

void BackEnd::buttonClicked(QPointF point) {
    qDebug() << "Button clicked at" << point;

    XRRMonitorInfo *monitorInfo;
    Display *display;
    Window root;
    int n_monitors = 0;

    display = XOpenDisplay(0);
    root = DefaultRootWindow(display);

    monitorInfo = XRRGetMonitors(display, root, true, &n_monitors);

    for (int i = 0; i < n_monitors; i++) {
        char* name;
        name = XGetAtomName(display, monitorInfo->name);
        qDebug() << name << monitorInfo->width << "x" << monitorInfo->height << "+" << monitorInfo->x
                 << "+" << monitorInfo->y;
        monitorInfo++;
    }
}

BackEnd::~BackEnd() = default;
