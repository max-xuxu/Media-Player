#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
private slots:
    void on_pushButton_browser_clicked();
    
    void on_listWidget_names_itemDoubleClicked(QListWidgetItem *item);
    
    void on_pushButton_add_clicked();
    
    void on_horizontalSlider_progress_sliderReleased();
    //播放进度发生改变
    void onPositionChange(qint64 pos);
    //媒体状态变化
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
    void on_pushButton_pre_clicked();
    
    void on_pushButton_play_clicked();
    
    void on_pushButton_next_clicked();
    
    void on_pushButton_history_clicked();
    
    void on_pushButton_close_clicked();

private:
    void initMedia();//初始化媒体播放
    void addToPlaylist(QString dir);//向playlist添加媒体的url
    void showTime();//显示播放的时间，包括总时间和当前时间
    void addToHistory();//添加历史记录
    void nextMode();//下一首歌
private:
    Ui::MainWindow *ui;
    QMediaPlayer* player;
    QMediaPlaylist* playlist;
    QVideoWidget* vWidget;
};
#endif // MAINWINDOW_H
