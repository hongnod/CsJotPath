#include "database.h"

QSqlError DataLayer::initdbcon()
{
    qDebug() << QSqlDatabase::drivers();

    selfdb = QSqlDatabase::addDatabase("QSQLITE");
    selfdb.setDatabaseName("transdb.db3");

    if(!selfdb.open()){
        qDebug() << "Can not open connection.";
        //exit(CONNECTION_FAILED);
        return selfdb.lastError();
    }

    CreateTables();


 /*   query.exec("select id, name from mapping");
    while (query.next()) {
        qDebug() << query.value(0).toInt() << ": " << query.value(1).toString();
    }*/
    return QSqlError();
}

void DataLayer::closedbcon()
{
    selfdb.close();
}

QSqlDatabase  DataLayer::db()
{
    return selfdb;
}

bool DataLayer::CreateTables()
{
    if(!createplacetable()) return false;
    if(!createnettable()) return false;
    return true;
}

bool DataLayer::createplacetable()
{
    QSqlQuery query;
    query.exec("	CREATE TABLE place(selfId integer primary key, parentId integer, name varchar, type int,edgetype tinyint)");
    qDebug() << selfdb.databaseName() << selfdb.tables();
    if(QSqlError().isValid())
    {
        qDebug() << QSqlError();
        return false;
    }
    return true;
}

bool DataLayer::createnettable()
{
    QSqlQuery query;
    query.exec("	CREATE TABLE network(selfId integer primary key, parentId integer, name varchar, type int)");
    qDebug() << selfdb.databaseName() << selfdb.tables();
    if(QSqlError().isValid())
    {
        qDebug() << QSqlError();
        return false;
    }
    return true;
}
