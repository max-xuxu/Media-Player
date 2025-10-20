#include "ShutdownDialog.h"
#include "ui_ShutdownDialog.h"
#include "ShutdownManager.h"
#include <QTime>
#include <QMessageBox>

ShutdownDialog::ShutdownDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShutdownDialog)
{
    ui->setupUi(this);
    setWindowTitle("定时关闭设置");

    // 设置时间编辑器的属性
    ui->timeEdit->setTime(QTime::currentTime().addSecs(3600)); // 默认1小时后
    ui->timeEdit->setDisplayFormat("hh:mm");

    // 更新状态显示
    ShutdownManager* manager = ShutdownManager::getInstance();
    if (manager->isShutdownScheduled())
    {
        if (manager->isShutdownAfterMedia())
        {
            ui->statusLabel->setText("当前模式：播放完当前媒体后关闭");
            ui->radioButton_end->setChecked(true);
        }
        else
        {
            ui->statusLabel->setText(QString("当前定时: %1").arg(manager->getScheduledTime().toString("hh:mm")));
            ui->radioButton_end->setChecked(false);
        }
    }
    else
    {
        ui->statusLabel->setText("未设置定时关闭");
    }
}

ShutdownDialog::~ShutdownDialog()
{
    delete ui;
}

void ShutdownDialog::on_setButton_clicked()
{
    ShutdownManager* manager = ShutdownManager::getInstance();
    if (ui->radioButton_end->isChecked())
    {
        // 播放完当前媒体后关闭模式
        manager->setShutdownAfterCurrentMedia();
        ui->statusLabel->setText("已设置：播放完当前媒体后关闭");
    }
    else
    {
        // 时间模式
        QTime shutdownTime = ui->timeEdit->time();
        if (shutdownTime <= QTime::currentTime())
        {
            QMessageBox::warning(this, "错误", "请设置一个未来的时间！");
            return;
        }
        manager->setShutdownTime(shutdownTime);
        ui->statusLabel->setText(QString("已设置定时: %1").arg(shutdownTime.toString("hh:mm")));
    }
}

void ShutdownDialog::on_cancelButton_clicked()
{
    ShutdownManager::getInstance()->cancelShutdown();
    ui->statusLabel->setText("定时关闭已取消");
}
