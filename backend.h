#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QEvent>

class BackEnd : public QObject
{
    Q_OBJECT
public:
    explicit BackEnd(QObject *parent = nullptr);
    ~BackEnd();
public slots:
    void buttonClicked();
signals:
    void counter_reached();
private:
    int m_counter;
};

#endif // BACKEND_H
