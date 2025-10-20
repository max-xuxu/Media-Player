#ifndef DBFACTORY_H
#define DBFACTORY_H

#include <QSqlDatabase>
#include "UserDao.h"
#include "HistoryDao.h"
/*
数据库工厂类，使用简单工厂模式，封装成单例，用于工厂的类一般都是单例的
它要管理数据库的打开和关闭以及xxxDao的创建

工厂模式保证了数据库不会重复打开（单例模式）
保证数据库操作之前数据库一定是打开的，工厂的构造函数中先打开数据库，再创建xxxDao对象

*/
class DBFactory
{
public:
    static DBFactory* getInstance();
    static void releaseInstance();
    inline UserDao* getUserDao(){return userDao;}
    inline HistoryDao* getHistoryDao(){return historyDao;}
private:
    DBFactory();
    DBFactory(const DBFactory& other){Q_UNUSED(other)}
    ~DBFactory();
    static DBFactory* instance;
    QSqlDatabase db;
    //把Dao对象创建在堆空间，避免重复创建
    UserDao* userDao;
    HistoryDao* historyDao;
};

#endif // DBFACTORY_H
