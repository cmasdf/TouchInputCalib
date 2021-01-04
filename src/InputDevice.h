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

/**
 * @brief input device item data structure
 */
typedef struct {
    XID     id;
    Atom    type;
    char*   name;
} InputDevices_t;

/**
 * @class Input device (touch screen) detection
 *
 * @brief This class is creation a list of touch input devices by using X11 and Xi library
 */
class InputDevice {
public:
    /**
     * @brief Constructor
     */
    InputDevice();

    /**
     * @brief Destructor
     */
    ~InputDevice();

    /**
     * @brief Get list of all touch input device items
     * @return
     */
    QVector<InputDevices_t> getListOfInputDevices();

private:
    QVector<InputDevices_t> m_listOfInputDevices = {};          ///< list containing specification of all touch screens
};

#endif //INPUTDEVICE_H
