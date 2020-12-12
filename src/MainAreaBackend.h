#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QPointF>
#include <QQmlApplicationEngine>
#include <QQmlContext>

class MainAreaBackend : public QObject {
Q_OBJECT
public:
    Q_PROPERTY(QPointF lastInput READ lastInput WRITE setLastInput NOTIFY lastInputChanged)

    explicit MainAreaBackend(QObject *parent = nullptr);
    ~MainAreaBackend() override;

    /**
     * @brief Register instance of this class as QML singleton
     */
    void registerSingleton(QQmlEngine *qmlEngine);

    QPointF lastInput();

    void setLastInput(QPointF lastInput);

public slots:


#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"
signals:
    void touchAreaClicked(QPointF point);

    void lastInputChanged();

#pragma clang diagnostic pop

private:
    QPointF m_lastInput;
};

#endif // BACKEND_H
