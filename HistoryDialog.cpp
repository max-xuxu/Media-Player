#include "HistoryDialog.h"
#include "ui_HistoryDialog.h"
#include "DBFactory.h"
#include "UserInfo.h"
#include <vector>

using namespace std;

HistoryDialog::HistoryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HistoryDialog)
{
    ui->setupUi(this);
}

HistoryDialog::~HistoryDialog()
{
    delete ui;
}

void HistoryDialog::on_pushButton_clear_clicked()
{
    HistoryEntity he;
    he.userid = UserInfo::getInstance()->getUserid();
    DBFactory::getInstance()->getHistoryDao()->clearHistory(he);
    ui->listWidget_history->clear();
}

void HistoryDialog::on_pushButton_select_clicked()
{
    HistoryEntity he;
    he.userid = UserInfo::getInstance()->getUserid();
    vector<HistoryEntity> vec;
    DBFactory::getInstance()->getHistoryDao()->findHistory(he, vec);
    
    ui->listWidget_history->clear();//清空原有的显示
    for(auto item : vec)
    {
        QString show = item.name + " " + item.dateTime.toString();
        ui->listWidget_history->addItem(show);
    }
}
