#include "ShutdownManager.h"
#include <QApplication>
#include <QMainWindow>

ShutdownManager* ShutdownManager::instance = nullptr;

ShutdownManager* ShutdownManager::getInstance()
{
    if (instance == nullptr)
    {
        instance = new ShutdownManager();
    }
    return instance;
}

ShutdownManager::ShutdownManager(QObject* parent)
    : QObject(parent), scheduled(false), shutdownAfterMedia(false)
{
    timer = new QTimer(this);
    timer->setInterval(1000); // 每秒检查一次是否到达关机时间
    connect(timer, &QTimer::timeout, this, &ShutdownManager::checkShutdownTime);
}

void ShutdownManager::setShutdownTime(const QTime& time)
{
    shutdownTime = time;
    scheduled = true;
    shutdownAfterMedia = false;
    if (!timer->isActive())
    {
        timer->start();
    }
    QMessageBox::information(nullptr, "定时关闭",
    QString("已设置定时关闭: %1").arg(time.toString("hh:mm")));
}


void ShutdownManager::setShutdownAfterCurrentMedia()
{
    scheduled = true;
    shutdownAfterMedia = true;
    shutdownTime = QTime();
    if (!timer->isActive())
    {
        timer->start();
    }
    QMessageBox::information(nullptr, "定时关闭",
        "已设置：播放完当前媒体后关闭");
}

void ShutdownManager::cancelShutdown()
{
    scheduled = false;
    shutdownAfterMedia = false;
    timer->stop();
    QMessageBox::information(nullptr, "定时关闭", "定时关闭已取消");
}

bool ShutdownManager::isShutdownScheduled() const
{
    return scheduled;
}

QTime ShutdownManager::getScheduledTime() const
{
    return shutdownTime;
}

bool ShutdownManager::isShutdownAfterMedia() const
{
    return shutdownAfterMedia;
}

void ShutdownManager::checkShutdownTime()
{
    if (!scheduled) return;
    if (!shutdownAfterMedia && QTime::currentTime() >= shutdownTime)
    {
        performShutdown();
    }
}

void ShutdownManager::performShutdown()
{
    timer->stop();
    scheduled = false;
    shutdownAfterMedia = false;
    // 查找并关闭主窗口
    QWidgetList widgets = QApplication::topLevelWidgets();
    for (QWidget* widget : widgets)
    {
        if (qobject_cast<QMainWindow*>(widget))
        {
            widget->close();
            break;
        }
    }
    QApplication::quit();
}

void ShutdownManager::checkMediaFinished()
{
    if (scheduled && shutdownAfterMedia)
    {
        performShutdown();
    }
}
