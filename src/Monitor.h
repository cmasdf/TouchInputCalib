/**
 * @file Monitor.h
 * @author Daniel Matthes
 * @date 07.12.2020
 * @brief detection of active monitors
 */
#ifndef MONITOR_H
#define MONITOR_H

#include <X11/extensions/Xrandr.h>
#include <X11/Xlib.h>

typedef struct {
    Atom name;
    char* nameString;
    int width;
    int height;
    int x;
    int y;
} Monitor_t;

class Monitor {
public:
    Monitor();
    ~Monitor();

    QVector<Monitor_t> getListOfMonitors();

private:
    QVector<Monitor_t> m_listOfMonitors = {};
};


#endif //MONITOR_H
