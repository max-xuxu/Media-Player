#include "RegisterDialog.h"
#include "ui_RegisterDialog.h"
#include <QMessageBox>
#include "DBFactory.h"

RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::on_pushButton_ok_clicked()
{
    QString userid = ui->lineEdit_userid->text();
    QString pwd = ui->lineEdit_pwd->text();
    QString repwd = ui->lineEdit_repwd->text();
    if(userid.isEmpty() || pwd.isEmpty() || repwd.isEmpty())
    {
        QMessageBox::warning(this, "警告", "账号密码不能为空");
        return;
    }
    if(pwd != repwd)
    {
        QMessageBox::warning(this, "警告", "两次密码不一致");
        return;
    }
    UserEntity ue;
    ue.userid = userid;
    ue.pwd = pwd;
    bool ok;
    DBFactory::getInstance()->getUserDao()->addUser(ue, ok);
    if(!ok)
    {
        QMessageBox::warning(this, "警告", "账号已经存在");
    }
    else
    {
        QMessageBox::information(this, "恭喜", "注册成功！！！");
    }
}
