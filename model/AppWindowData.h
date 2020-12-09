/**
 * @file AppWindowData.h
 * @author Daniel Matthes
 * @date 09.12.2020
 * @brief Application window data item class
 */
#ifndef APPWINDOWDATA_H
#define APPWINDOWDATA_H

#include <QString>
#include <utility>

/**
 * @class Application window data item
 *
 * @brief Application window data item class
 */
class AppWindowData {
public:
    /**
     * @brief Constructor
     */
    AppWindowData();

    /**
     * @brief Copy constructor
     * @param title - window title
     * @param objectName - object name
     * @param deviceInfo - device info
     * @param width - window width
     * @param height - window height
     * @param x - window x offset
     * @param y - window y offset
     */
    AppWindowData(QString title, QString objectName, QString deviceInfo, int width, int height, int x, int y);

    /**
     * @brief Get application window title
     * @return application window title
     */
    QString title() const;

    /**
     * @brief Get application window object name
     * @return application window object name
     */
    QString objectName() const;

    /**
     * @brief Get application window device info
     * @return application window device info
     */
    QString deviceInfo() const;

    /**
     * @brief Get application window width
     * @return application window width
     */
    int width() const;

    /**
     * @brief Get application window height
     * @return application window height
     */
    int height() const;

    /**
     * @brief Get application window x offset
     * @return application window x offset
     */
    int x() const;

    /**
     * @brief Get application window y offset
     * @return application window y offset
     */
    int y() const;

    /**
     * @brief Set application window title
     * @param title - application window title
     */
    inline void setTitle(QString title) {m_title = std::move(title);}

    /**
     * @brief Set application window object name
     * @param objectName - application window object name
     */
    inline void setObjectName(QString objectName) {m_objectName = std::move(objectName);}

    /**
     * @brief Set application window device info
     * @param objectName - application window device info
     */
    inline void setDeviceInfo(QString deviceInfo) {m_deviceInfo = std::move(deviceInfo);}

    /**
     * @brief Set application window width
     * @param width - application window width
     */
    inline void setWidth(int width) {m_width = width;}

    /**
     * @brief Set application window height
     * @param height - application window height
     */
    inline void setHeight(int height) {m_height = height;}

    /**
     * @brief Set application window x offset
     * @param x - application window x offset
     */
    inline void setX(int x) {m_x = x;}

    /**
     * @brief Set application window y offset
     * @param y - application window y offset
     */
    inline void setY(int y) {m_y = y;}

private:
    QString m_title;        ///< application window title
    QString m_objectName;   ///< application window objectName
    QString m_deviceInfo;   ///< application window deviceInfo
    int m_width;            ///< application window width
    int m_height;           ///< application window height
    int m_x;                ///< application window x offset
    int m_y;                ///< application window y offset
};

#endif //APPWINDOWDATA_H
