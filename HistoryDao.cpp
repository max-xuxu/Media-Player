#include "HistoryDao.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

HistoryDao::HistoryDao()
{
    //创建history表
    QSqlQuery query;
    query.exec("create table if not exists history("
               "userid char(20),"
               "name char(20),"
               "time datetime"
               ")");
}

bool HistoryDao::addHistory(HistoryEntity &he)
{
    QSqlQuery query;
    query.prepare("insert into history values(?,?,datetime('now'))");
    query.bindValue(0, he.userid);
    query.bindValue(1, he.name);
    bool execOk = query.exec();
    if(!execOk)
        return false;
    return true;
}

bool HistoryDao::findHistory(HistoryEntity &he, vector<HistoryEntity> &vec)
{
    QSqlQuery query;
    query.prepare("select * from history where userid = ?");
    query.bindValue(0, he.userid);
    bool execOk = query.exec();
    if(!execOk)
        return false;
    
    //遍历查询到的数据
    while(query.next())
    {
        HistoryEntity item;
        item.userid = query.record().value("userid").toString();
        item.name = query.record().value("name").toString();
        item.dateTime = query.record().value("time").toDateTime();
        
        vec.push_back(item);//将数据插入到主调函数的vector中
    }
    
    return true;
}

bool HistoryDao::clearHistory(HistoryEntity &he)
{
    QSqlQuery query;
    query.prepare("delete from history where userid = ?");
    query.bindValue(0, he.userid);
    bool execOk = query.exec();
    if(!execOk)
        return false;
    
    return true;
}
