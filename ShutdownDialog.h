#ifndef SHUTDOWNDIALOG_H
#define SHUTDOWNDIALOG_H

#include <QDialog>

namespace Ui {
class ShutdownDialog;
}

class ShutdownDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShutdownDialog(QWidget *parent = nullptr);
    ~ShutdownDialog();

private slots:
    void on_setButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::ShutdownDialog *ui;
};

#endif // SHUTDOWNDIALOG_H
