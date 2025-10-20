#include "DBFactory.h"

DBFactory* DBFactory::instance = nullptr;

DBFactory *DBFactory::getInstance()
{
    if(instance == nullptr)
    {
        instance = new DBFactory;
    }
    return instance;
}

void DBFactory::releaseInstance()
{
    if(instance != nullptr)
    {
        delete instance;
        instance = nullptr;
    }
}

DBFactory::DBFactory()
{
    //打开数据库
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("sea.db");
    db.open();
    
    userDao = new UserDao;
    historyDao = new HistoryDao;
}

DBFactory::~DBFactory()
{
    delete userDao;
    delete historyDao;
    //关闭数据库
    db.close();
}

