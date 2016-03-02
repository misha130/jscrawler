#ifndef LINKSLOOKER_H
#define LINKSLOOKER_H
#include "crawler.h"
#include <QCoreApplication>
#include <QQueue>
#include <QtNetwork>
#include <QList>
#include <QNetworkAccessManager>
#include <QScriptEngine>
#include <QScriptValue>
#include <QScriptValueIterator>
class linkslooker:public QObject{

    Q_OBJECT
public:
    linkslooker(QThread *);
    ~linkslooker();

private:
    const QUrl GENERATOR_URL = "http://www.randomword.com/json/words.json";
    const QString GOOGLE_SEARCH = "https://ajax.googleapis.com/ajax/services/search/web?v=1.0&q=";
    void Loop();
    void GetWords();
    int getRunningThreads();
    QStringList words;
    QStringList serialize2(QByteArray toserialze,QString word,QString data = "data") const;
    QStringList serialize(QByteArray toserialze,QString word,QString data = "data") const;
    QThread *mainThread;
    QQueue<QString> websites;
    QList<QString> searched;
    QUrl url;
    QNetworkAccessManager qnam;
    QNetworkReply *reply; //reply of words look up
    bool httpRequestAborted;
    QEventLoop event;

    QByteArray m_data;
    QList<crawler *> crawlInstances;
private slots:
      void httpFinished();
      void httpReadyRead();
      void updateDataReadProgress(qint64 bytesRead, qint64 totalBytes);
      void slotError(QNetworkReply::NetworkError);

};

#endif // LINKSLOOKER_H
