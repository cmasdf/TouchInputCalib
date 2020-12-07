#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QEvent>
#include <QPointF>

class Backend : public QObject {
Q_OBJECT
public:
    explicit Backend(QObject *parent = nullptr);
    ~Backend() override;

public slots:
    void buttonClicked(QPointF point);
};

#endif // BACKEND_H
