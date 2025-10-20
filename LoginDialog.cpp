#include "LoginDialog.h"
#include "ui_LoginDialog.h"
#include "DBFactory.h"
#include <QMessageBox>
#include "MainWindow.h"
#include "RegisterDialog.h"
#include "UserInfo.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pushButton_login_clicked()
{
    QString userid = ui->lineEdit_userid->text();
    QString pwd = ui->lineEdit_pwd->text();
    UserEntity ue;//创建数据库的数据对象
    ue.userid = userid;
    ue.pwd = pwd;
    bool ok;//查询结果
    DBFactory::getInstance()->getUserDao()->checkUser(ue, ok);
    
    if(!ok)
    {
        QMessageBox::warning(this, "登录失败", "账号或密码错误!");
    }
    else
    {
        MainWindow* mw = new MainWindow;
        mw->show();
        UserInfo::getInstance()->setUserid(userid);//保存用户账号
        close();
    }
}

void LoginDialog::on_pushButton_register_clicked()
{
    RegisterDialog* rd = new RegisterDialog(this);
    rd->show();
}
