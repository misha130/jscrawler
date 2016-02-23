#ifndef CRAWLER_H
#define CRAWLER_H
#include <QDebug>
#include <QtNetwork>
#include <QThread>
#include <QtCore>
#include <QList>

class crawler
{
public:
     crawler();
    ~crawler();
     void run();
     bool createInstance(QString);
private:
    QList<QThread> threads;
};

#endif // CRAWLER_H
