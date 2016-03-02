#include "linkslooker.h"


linkslooker::linkslooker(QThread *thread){
    this->mainThread = thread;
    GetWords();
}

void linkslooker::Loop(){
    QEventLoop event;
    foreach(QString word, words){
        qDebug() << "Read data for" << GOOGLE_SEARCH + word;

        QUrl gSearch(GOOGLE_SEARCH + word); //url creating
        QNetworkRequest req(gSearch); //request creating
        QObject::connect(&qnam, SIGNAL(finished(QNetworkReply*)), &event, SLOT(quit())); //loop to wait till recieve and not making signal/slots
        reply = qnam.get(req); //Get request

        event.exec(); // blocks stack until "finished()" has been called

        if(reply->error() != QNetworkReply::NoError)
        qDebug("network error!"); //There are no errors

        QByteArray googleReply = reply->readAll();

        QStringList wordList = serialize2(googleReply,"results","responseData");
        if(wordList.count() == 0){
           crawler *c = new crawler("http://api.jquery.com/on/");
           break;
        }
        foreach(QString res, wordList){

            if(!this->websites.contains(res)){
                this->websites.append(res);
                crawler *c = new crawler(res);
                this->crawlInstances.append(c);
            }
            break;
        }


    }
}
int linkslooker::getRunningThreads()
{
    int i=0;
        foreach(crawler *c,this->crawlInstances)
        {
            if(c->isRunning()) i++;
        }
    return i;
}

void linkslooker::GetWords(){
        QNetworkRequest req(GENERATOR_URL);
        reply = qnam.get(req); //Get request
        if(reply->error() != QNetworkReply::NoError)
          qDebug("network error!"); //There are no errors

        connect(reply, SIGNAL(finished()),
                SLOT(httpFinished()));
        connect(reply, SIGNAL(readyRead()),
                this, SLOT(httpReadyRead()));
        connect(reply, SIGNAL(downloadProgress(qint64,qint64)),
                this, SLOT(updateDataReadProgress(qint64,qint64)));
        connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
                this, SLOT(slotError(QNetworkReply::NetworkError)));

}

QStringList linkslooker::serialize(QByteArray toserialize,QString propName, QString data) const {

   QStringList words;
  // Parse document
  QJsonDocument doc(QJsonDocument::fromJson(toserialize));
  // Get JSON object
  QJsonObject json = doc.object();
  QJsonArray jsonArray = json[data].toArray();
  foreach (const QJsonValue & value, jsonArray) {
      QJsonObject obj = value.toObject();
      words.append(obj[propName].toString());
  }

  return words;
}


QStringList linkslooker::serialize2(QByteArray toserialize,QString propName, QString data) const {
   QStringList words;
  // Parse document
  QJsonDocument doc(QJsonDocument::fromJson(toserialize));
  // Get JSON object

  QJsonObject json = doc.object()[data].toObject();
  QJsonArray jsonArray = json[propName].toArray();
  foreach (const QJsonValue &value, jsonArray) {
      QJsonObject obj = value.toObject();
      words.append(obj["url"].toString());
  }

  return words;
}

void linkslooker::httpFinished(){
    this->words = serialize(m_data,"word");

      Loop(); //Start looping on new words


}

void linkslooker::slotError(QNetworkReply::NetworkError e) {
    qDebug() << "slotError" << e ;
}
void linkslooker::httpReadyRead()
{
   m_data.append(reply->readAll());
}

void linkslooker::updateDataReadProgress(qint64 bytesRead, qint64 totalBytes)
{
    if (httpRequestAborted)
        qDebug() << "Network request Aborted";
        qDebug() << "Have read " << bytesRead << "Out of " << totalBytes;
}


linkslooker::~linkslooker(){
    QObject::disconnect(&qnam, SIGNAL(finished(QNetworkReply*)), &event, SLOT(quit())); //loop to wait till recieve and not making signal/slots
    disconnect(reply,SIGNAL(finished()),this,SLOT(httpFinished()));
     QObject::disconnect(reply, SIGNAL(readyRead()),
            this, SLOT(httpReadyRead()));
     QObject::disconnect(reply, SIGNAL(downloadProgress(qint64,qint64)),
            this, SLOT(updateDataReadProgress(qint64,qint64)));
     QObject::disconnect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(slotError(QNetworkReply::NetworkError)));
}
