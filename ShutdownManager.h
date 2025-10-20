#ifndef SHUTDOWNMANAGER_H
#define SHUTDOWNMANAGER_H

#include <QObject>
#include <QTimer>
#include <QTime>
#include <QMessageBox>

class ShutdownManager : public QObject
{
    Q_OBJECT

public:
    static ShutdownManager* getInstance();
    void setShutdownTime(const QTime& time);
    void setShutdownAfterCurrentMedia();
    void cancelShutdown();
    bool isShutdownScheduled() const;
    QTime getScheduledTime() const;
    bool isShutdownAfterMedia() const;
    void checkMediaFinished();

private slots:
    void checkShutdownTime();

private:
    void performShutdown();
    ShutdownManager(QObject* parent = nullptr);
    static ShutdownManager* instance;
    QTimer* timer;
    QTime shutdownTime;
    bool scheduled;
    bool shutdownAfterMedia;
};

#endif // SHUTDOWNMANAGER_H
