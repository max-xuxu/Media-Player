#include "UserInfo.h"

UserInfo* UserInfo::instance = nullptr;

UserInfo *UserInfo::getInstance()
{
    if(instance == nullptr)
        instance = new UserInfo;
    return instance;
}

void UserInfo::releaseInstance()
{
    if(instance != nullptr)
    {
        delete instance;
        instance = nullptr;
    }
}

UserInfo::UserInfo()
{
    
}
