/**
 * @file AppWindowData.h
 * @author Daniel Matthes
 * @date 09.12.2020
 */

#include <model/AppWindowData.h>

AppWindowData::AppWindowData() : m_title("Touch Screen Determination 0"), m_objectName("applicationWindow0"),
                                 m_deviceInfo(""), m_width(1920), m_height(1080), m_x(0), m_y(0) {}

AppWindowData::AppWindowData(QString title, QString objectName, QString deviceInfo, int width, int height, int x, int y)
        : m_title(std::move(title)), m_objectName(std::move(objectName)), m_deviceInfo(std::move(deviceInfo)),
          m_width(width), m_height(height), m_x(x), m_y(y) {}

QString AppWindowData::title() const {
    return m_title;
}

QString AppWindowData::objectName() const {
    return m_objectName;
}

QString AppWindowData::deviceInfo() const {
    return m_deviceInfo;
}

int AppWindowData::width() const {
    return m_width;
}

int AppWindowData::height() const {
    return m_height;
}

int AppWindowData::x() const {
    return m_x;
}

int AppWindowData::y() const {
    return m_y;
}
