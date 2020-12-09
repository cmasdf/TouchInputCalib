#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QPointF>
#include <QQmlApplicationEngine>
#include <QQmlContext>

class Backend : public QObject {
Q_OBJECT
public:
    Q_PROPERTY(QPointF lastInput READ lastInput WRITE setLastInput NOTIFY lastInputChanged)

    explicit Backend(QObject *parent = nullptr);
    ~Backend() override;

    /**
     * @brief Register instance of this class as QML singleton
     */
    void registerSingleton(QQmlEngine *qmlEngine);

    QPointF lastInput();

    void setLastInput(QPointF lastInput);

public slots:
    void touchAreaClicked();

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"
signals:
    void lastInputChanged();

#pragma clang diagnostic pop

private:
    QPointF m_lastInput;
};

#endif // BACKEND_H
