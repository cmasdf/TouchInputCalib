/**
 * @file InputDevice.h
 * @author Daniel Matthes
 * @date 07.12.2020
 * @brief detection of input devices (touch screens)
 */
#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

#include <X11/extensions/XInput.h>
#include <X11/Xlib.h>

typedef struct {
    XID     id;
    Atom    type;
    char*   name;
} InputDevices_t;

class InputDevice {
public:
    InputDevice();
    ~InputDevice();

private:
    QVector<InputDevices_t> m_listOfInputDevices = {};
};


#endif //INPUTDEVICE_H
