/**
 * @file InputDevice.cpp
 * @author Daniel Matthes
 * @date 07.12.2020
 */

#include <QDebug>
#include <src/InputDevice.h>

InputDevice::InputDevice() {
    XDeviceInfo* devices;
    Display* display;
    int ndevices = 0;

    // open display
    display = XOpenDisplay(nullptr);

    // get specification of all input devices
    devices = XListInputDevices(display, &ndevices);

    // extract specification of all touch displays and put it into the input device list
    for (int i = 0; i < ndevices; i++) {
        // add/show only TouchDisplays
        if (devices->type == 109) {
            InputDevices_t tmp_Devices;

            tmp_Devices.name = devices->name;
            tmp_Devices.id = devices->id;
            tmp_Devices.type = devices->type;

            qDebug() << tmp_Devices.name << tmp_Devices.id << tmp_Devices.type;

            m_listOfInputDevices.push_back(tmp_Devices);
        }
        devices++;
    }
}

InputDevice::~InputDevice() = default;

QVector<InputDevices_t> InputDevice::getListOfInputDevices() {
    return m_listOfInputDevices;
}