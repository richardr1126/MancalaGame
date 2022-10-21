#ifndef MARBLE_H
#define MARBLE_H

#include <QObject>

class Marble : public QObject
{
    Q_OBJECT
public:
    explicit Marble(QObject *parent = nullptr);

signals:

};

#endif // MARBLE_H
