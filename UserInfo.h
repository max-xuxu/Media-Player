#ifndef USERINFO_H
#define USERINFO_H

#include <QString>

class UserInfo
{
public:
    static UserInfo* getInstance();
    static void releaseInstance();
    inline void setUserid(QString userid){this->userid = userid;}
    inline QString getUserid(){return userid;}
private:
    UserInfo();
    UserInfo(const UserInfo& other){Q_UNUSED(other)}
    ~UserInfo(){}
    
    static UserInfo* instance;
    QString userid;
};

#endif // USERINFO_H
