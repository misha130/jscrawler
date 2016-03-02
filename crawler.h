#ifndef CRAWLER_H
#define CRAWLER_H
#include <QtCore>
#include <QCoreApplication>
#include <QDebug>
#include <QtNetwork>
#include <QStringList>
#include "sqlhandle.h"
class crawler:public QObject
{
    Q_OBJECT
public:
    crawler(QString);
    ~crawler();
    void run();
    bool isRunning();
private:
    QString url;
    bool waitResponse = false;
    QEventLoop event;
    QStringList extractScripts(QString html);
    QNetworkAccessManager qnam;
    QNetworkReply* reply;
signals:
    void resultReady(const QString &s);
};
#endif //crawler_h
