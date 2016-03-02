#include "crawler.h"

crawler::crawler(QString url)
{
this->url = url;
    run();
}

crawler::~crawler()
{
    this->qnam.disconnect(SIGNAL(finished(QNetworkReply*)), &event, SLOT(quit())); //loop to wait till recieve and not making signal/slots
}

void crawler::run(){


    QUrl *gSearch;
    if(url.contains("http")){
     gSearch = new QUrl(url);
    }
    else{
       gSearch = new QUrl(QUrl::fromPercentEncoding(this->url.toUtf8())); //url creating
    }
    QNetworkRequest req(*gSearch); //request creating
    QObject::connect(&qnam, SIGNAL(finished(QNetworkReply*)), &event, SLOT(quit())); //loop to wait till recieve and not making signal/slots
    this->reply = qnam.get(req); //Get request

    this->event.exec(); // blocks stack until "finished()" has been called

    QString uHtml = QString::fromUtf8(reply->readAll());     //AT THIS POINT I GOT THE HTML CODE

    QStringList scripts = extractScripts(uHtml);
    foreach(QString script, scripts){
        qDebug() << "Adding to sql" << script;
    sqlhandle s;
    s.appendScriptUrl(gSearch->toString(),script);
    }
}

bool crawler::isRunning(){
    return waitResponse;
}

QStringList crawler::extractScripts(QString html){
    QStringList strings;
    QRegExp rx("<script[^>]*>");
    QStringList list;
    int pos = 0;

    while ((pos = rx.indexIn(html, pos)) != -1) {
        QString scripttag = rx.cap(0);
        if(!scripttag.contains("src=")){ pos += rx.matchedLength(); continue;}
        QString linkscript = scripttag.remove(0,scripttag.indexOf("src=") + 4).replace("'","")
                .replace("\"",""); //remove start and '/"
        QString afterscript = linkscript.remove(linkscript.indexOf(".js") + 3,
                                             linkscript.length());
        afterscript =  afterscript.split("/").last();
        strings << afterscript;
        pos += rx.matchedLength();

    }
    qDebug() << "TEST" << strings;

    return strings;
}
