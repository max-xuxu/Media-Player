#include "LoginDialog.h"
#include "ShutdownManager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);

    // 初始化定时关闭管理器
    ShutdownManager::getInstance();

    LoginDialog ld;
    ld.show();

    return a.exec();
}
