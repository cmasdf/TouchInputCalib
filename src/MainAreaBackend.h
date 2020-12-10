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

    Q_PROPERTY(bool clicked READ clicked WRITE setClicked NOTIFY clickedChanged)

    explicit MainAreaBackend(QObject *parent = nullptr);
    ~MainAreaBackend() override;

    /**
     * @brief Register instance of this class as QML singleton
     */
    void registerSingleton(QQmlEngine *qmlEngine);

    QPointF lastInput();

    bool clicked() const;

    void setLastInput(QPointF lastInput);

    void setClicked(bool clicked);

public slots:
    void touchAreaClicked();

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"
signals:
    void lastInputChanged();

    void clickedChanged();

#pragma clang diagnostic pop

private:
    QPointF m_lastInput;
    bool m_clicked;
};

#endif // BACKEND_H
