#ifndef HISTORYDAO_H
#define HISTORYDAO_H

#include <QString>
#include <QDateTime>
#include <vector>

using namespace std;

struct HistoryEntity
{
    QString userid;//用户id  区分是哪个用户的历史信息
    QString name;//歌曲的名字
    QDateTime dateTime;//听歌的时间
};

class HistoryDao
{
public:
    HistoryDao();
    /*
        插入历史信息
    */
    bool addHistory(HistoryEntity& he);
    /*
        查找所有历史信息
        参数1：用户信息
        参数2：返回的数据
    */
    bool findHistory(HistoryEntity& he, vector<HistoryEntity>& vec);
    /*
        清空历史信息
        参数1：用户信息
    */
    bool clearHistory(HistoryEntity& he);
};

#endif // HISTORYDAO_H
