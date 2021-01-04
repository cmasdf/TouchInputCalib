/**
 * @file MainAreaBackend.h
 * @author Daniel Matthes
 * @date 02.12.2020
 * @brief Backend for calibration areas
 */
#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QPointF>
#include <QQmlApplicationEngine>
#include <QQmlContext>

/**
 * @class Main area backend
 *
 * @brief Backend for calibration Areas
 */
class MainAreaBackend : public QObject {
Q_OBJECT
public:
    /**
     * @brief last input
     * @accessors lastInput(), setLastInput(), lastInputChanged()
     */
    Q_PROPERTY(QPointF lastInput READ lastInput WRITE setLastInput NOTIFY lastInputChanged)

    /**
     * @brief Constructor
     * @param parent - QObject
     */
    explicit MainAreaBackend(QObject *parent = nullptr);

    /**
     * @brief Destructor
     */
    ~MainAreaBackend() override;

    /**
     * @brief Register instance of this class as QML singleton
     */
    void registerSingleton(QQmlEngine *qmlEngine);

    /**
     * @brief Get last input
     * @return Coordinates of last inptr
     */
    QPointF lastInput();

    /**
     * @brief Set last input
     * @param lastInput - coordinates of last input
     */
    void setLastInput(QPointF lastInput);

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"
signals:

    /**
     * @brief Touch point clicked signal
     * @param point - touch point coordinate
     */
    void touchAreaClicked(QPointF point);

    /**
     * @brief Last input changed signal
     */
    void lastInputChanged();

#pragma clang diagnostic pop

private:
    QPointF m_lastInput;            ///< Last touch input value
};

#endif // BACKEND_H
