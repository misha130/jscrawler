#ifndef SQLHANDLE_H
#define SQLHANDLE_H

#include <QObject>
#include <QDateTime>
#include <QSqlDatabase>

#include <QSql>
#include <QSqlError>
#include <QSqlResult>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>

class sqlhandle : public QObject
{
    Q_OBJECT
public:
    explicit sqlhandle(QObject *parent = 0);
    ~sqlhandle();
    bool appendScriptUrl(QString URL, QString Script);
private:
    QSqlDatabase db;
    QString ScriptExistsOrCreate(QString Script);
    QString appendScript(QString Script);
    bool openConnection();
signals:

public slots:
};

#endif // SQLHANDLE_H
