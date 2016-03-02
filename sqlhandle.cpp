#include "sqlhandle.h"

sqlhandle::sqlhandle(QObject *parent) : QObject(parent)
{
     db = QSqlDatabase::addDatabase("QPSQL");
     db.setDatabaseName("");
     db.setHostName("");
     db.setUserName(""); //Github removed
     db.setPassword("");
     db.setPort(5432);
     db.setConnectOptions("");
}
sqlhandle::~sqlhandle(){
    db.close();
}
bool sqlhandle::openConnection(){
    if(!db.open()){
     qDebug() << db.lastError().text();
      return false;
    }
    return db.isOpen();
}

QString sqlhandle::appendScript(QString Script){
    if(!db.isOpen())
    {
      if(!openConnection()) return false;
    }
    QSqlQuery mQuery(db);
    mQuery.prepare("INSERT INTO \"Scripts\"(\"Name\")VALUES (:name) RETURNING \"ID\";");
    mQuery.addBindValue(Script);
    mQuery.exec(); // EXECUTE QUERY
    mQuery.next(); // FORWARD RECORD BY 1
    return mQuery.value(0).toString();
}

QString sqlhandle::ScriptExistsOrCreate(QString Script){
    if(!db.isOpen())
    {
      if(!openConnection()) return false;
    }
     QSqlQuery mQuery(db);

     mQuery.exec("SELECT \"ID\" FROM \"Scripts\" WHERE \"Name\" = '" + Script + "';");
     mQuery.next(); //MOVE TO FIRST;
     if(mQuery.isNull(0)) return appendScript(Script);
     else return mQuery.value(0).toString();

}

bool sqlhandle::appendScriptUrl(QString URL, QString Script){
    if(!db.isOpen())
    {
      if(!openConnection()) return false;
    }
    QString scriptID = ScriptExistsOrCreate(Script);
    qDebug() << scriptID;
    QSqlQuery mQuery(db);
    mQuery.prepare("INSERT INTO \"UrlScripts\"(\"Url\",\"Script_ID\",\"DateUpdated\")VALUES (:url,:scriptid,:date);");

    mQuery.bindValue(":url", URL);
    mQuery.bindValue(":scriptid",scriptID);
    mQuery.bindValue(":date",QDateTime::currentDateTime());

    return mQuery.exec();
}
