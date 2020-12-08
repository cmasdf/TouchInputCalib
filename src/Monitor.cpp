/**
 * @file Monitor.cpp
 * @author Daniel Matthes
 * @date 07.12.2020
 */

#include <QDebug>
#include <src/Monitor.h>

Monitor::Monitor() {
    XRRMonitorInfo *monitorInfo;
    Display *display;
    Window root;
    int n_monitors = 0;

    display = XOpenDisplay(nullptr);
    root = DefaultRootWindow(display);

    monitorInfo = XRRGetMonitors(display, root, true, &n_monitors);

    for (int i = 0; i < n_monitors; i++) {
        char* name;
        name = XGetAtomName(display, monitorInfo->name);

        Monitor_t tmp_Monitor;
        tmp_Monitor.name = monitorInfo->name;
        tmp_Monitor.nameString = name;
        tmp_Monitor.width = monitorInfo->width;
        tmp_Monitor.height = monitorInfo->height;
        tmp_Monitor.x = monitorInfo->x;
        tmp_Monitor.y = monitorInfo->y;



        qDebug() << tmp_Monitor.name << "-" << tmp_Monitor.nameString << ":" << tmp_Monitor.width << "x"
                 << tmp_Monitor.height << "+" << tmp_Monitor.x << "+" << tmp_Monitor.y;

        m_listOfMonitors.push_back(tmp_Monitor);

        monitorInfo++;
    }
}

Monitor::~Monitor() = default;

QVector<Monitor_t> Monitor::getListOfMonitors() {
    return m_listOfMonitors;
}