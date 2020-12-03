#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QEvent>
#include <QPointF>

class BackEnd : public QObject {
Q_OBJECT
public:
    explicit BackEnd(QObject *parent = nullptr);
    ~BackEnd() override;

public slots:
    void buttonClicked(QPointF point);
};

#endif // BACKEND_H
