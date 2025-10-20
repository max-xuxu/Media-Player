#ifndef HISTORYDIALOG_H
#define HISTORYDIALOG_H

#include <QDialog>

namespace Ui {
class HistoryDialog;
}

class HistoryDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit HistoryDialog(QWidget *parent = nullptr);
    ~HistoryDialog();
    
private slots:
    void on_pushButton_clear_clicked();
    
    void on_pushButton_select_clicked();
    
private:
    Ui::HistoryDialog *ui;
};

#endif // HISTORYDIALOG_H
