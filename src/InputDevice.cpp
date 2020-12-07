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

    display = XOpenDisplay(0);

    devices = XListInputDevices(display, &ndevices);

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