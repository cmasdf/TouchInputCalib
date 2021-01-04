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

/**
 * @brief monitor item data structure
 */
typedef struct {
    Atom name;
    char *nameString;
    int width;
    int height;
    int x;
    int y;
} Monitor_t;

/**
 * @class Monitor detection
 *
 * @brief This class is creating a list of active monitors by using the Xrandr library
 */
class Monitor {
public:
    /**
     * @brief Constructor
     */
    Monitor();

    /**
     * @brief Destructor
     */
    ~Monitor();

    /**
     * @brief Get list of all active monitor items
     * @return
     */
    QVector<Monitor_t> getListOfMonitors();

private:
    QVector<Monitor_t> m_listOfMonitors = {};       ///< list containing specification of all active monitors
};

#endif //MONITOR_H
