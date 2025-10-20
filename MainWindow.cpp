#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <QDir>
#include "DBFactory.h"
#include "UserInfo.h"
#include "HistoryDialog.h"
#include <QDebug>
#include <QDateTime>
#include "ShutdownDialog.h"
#include "ShutdownManager.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initMedia();//初始化媒体
    //初始化随机种子
    QDateTime currentDateTime = QDateTime::currentDateTime();
    qint64 timestamp = currentDateTime.toSecsSinceEpoch();
    qsrand(timestamp);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_browser_clicked()
{
    //选择要播放文件的文件夹
    QString dirPath = QFileDialog::getExistingDirectory(this, "选择播放文件夹", ".");
    //创建文件夹对象
    QDir dir(dirPath);
    //获得所有文件的名字
    QStringList sl = dir.entryList(QDir::Files);
    ui->listWidget_names->addItems(sl);//添加文件列表
    addToPlaylist(dirPath);//添加到播放列表
}

void MainWindow::initMedia()    
{
    //创建对象
    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(this);
    vWidget = new QVideoWidget(this);
    vWidget->setGeometry(0, 0, 400, 400);
    //关联player和播放列表
    player->setPlaylist(playlist);
    //关联player和播放控件
    player->setVideoOutput(vWidget);
    vWidget->show();//显示控件
    //媒体播放进度发生改变的信号
    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::onPositionChange);
    connect(player, &QMediaPlayer::mediaStatusChanged, this, &MainWindow::onMediaStatusChanged);
}

void MainWindow::addToPlaylist(QString dir)
{
    QDir dirObj(dir);//创建文件夹对象
    QStringList sl = dirObj.entryList(QDir::Files);
    for(auto file : sl)//遍历所有文件名
    {
        QString filePath = dir+"/"+file;//构建完整路径
        playlist->addMedia(QUrl::fromLocalFile(filePath));//添加到播放列表
    }
}

void MainWindow::showTime()
{
    int totalTime = player->duration();//获得总时长
    int nowTime = player->position();//当前时间 
    //总时间
    //将毫秒转换为总秒数
    int totalSeconds = totalTime / 1000;
    //分别计算小时、分钟和秒
    int thours = totalSeconds / 3600;
    int tminutes = (totalSeconds % 3600) / 60;
    int tseconds = totalSeconds % 60; 
    //当前时间
    int nowSeconds = nowTime / 1000;
    //分别计算小时、分钟和秒
    int nhours = nowSeconds / 3600;
    int nminutes = (nowSeconds % 3600) / 60;
    int nseconds = nowSeconds % 60;
    QString data = QString("%1:%2:%3/%4:%5:%6").arg(nhours).arg(nminutes).arg(nseconds)
            .arg(thours).arg(tminutes).arg(tseconds);
    
    ui->label_time->setText(data);
}

void MainWindow::addToHistory()
{
    HistoryEntity he;
    he.userid = UserInfo::getInstance()->getUserid();
    he.name = ui->listWidget_names->currentItem()->text();
    DBFactory::getInstance()->getHistoryDao()->addHistory(he);
}

void MainWindow::nextMode()
{
    if(ui->radioButton_repeat->isChecked())//单曲循环按钮被选中
    {
        playlist->setCurrentIndex(playlist->currentIndex());//继续使用当前的下标  
    }
    else if(ui->radioButton_random->isChecked())//随机
    {
        playlist->setCurrentIndex(qrand()%playlist->mediaCount());
    }
    else if(ui->radioButton_next->isChecked())//下一曲
    {
        on_pushButton_next_clicked();
    }
    ui->listWidget_names->setCurrentRow(playlist->currentIndex());
}

void MainWindow::on_listWidget_names_itemDoubleClicked(QListWidgetItem *item)
{
    //获得点击条目的索引
    int index = ui->listWidget_names->row(item);
    //设置播放列表为当前选中的媒体
    playlist->setCurrentIndex(index);
    player->play();//播放歌曲
    addToHistory();
    ui->pushButton_play->setIcon(QIcon(":/icon/pause.png"));
}

void MainWindow::on_pushButton_add_clicked()
{
    QString urlStr = ui->lineEdit_url->text();//获得网址
    //QListWidget显示
    QStringList sl = urlStr.split('/');
    ui->listWidget_names->addItem(sl.last());//将文件名显示在列表中
    //添加到playlist
    playlist->addMedia(QUrl(urlStr));
}
//调整进度
void MainWindow::on_horizontalSlider_progress_sliderReleased()
{
    //设置当前的进度
    player->setPosition(ui->horizontalSlider_progress->value());
}

//播放进度发生改变
void MainWindow::onPositionChange(qint64 pos)
{
    showTime();//显示时间
    //设置进度条的位置
    ui->horizontalSlider_progress->setValue(pos);
}

void MainWindow::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    qDebug() << status;

    // 加载完毕
    if(status == QMediaPlayer::BufferedMedia)
    {
        // 设置显示的最大时长
        ui->horizontalSlider_progress->setMaximum(player->duration());
    }
    else if(status == QMediaPlayer::EndOfMedia) // 播放结束
    {
        // 检查是否需要关闭程序
        ShutdownManager::getInstance()->checkMediaFinished();

        nextMode();
    }
}

void MainWindow::on_pushButton_pre_clicked()
{
    int index = playlist->currentIndex()==0?
                playlist->mediaCount()-1:
                playlist->previousIndex();
    playlist->setCurrentIndex(index);
    ui->listWidget_names->setCurrentRow(playlist->currentIndex());
    player->play();
    addToHistory();
}

void MainWindow::on_pushButton_play_clicked()
{
    if(player->state() == QMediaPlayer::PlayingState)
    {
        player->pause();//暂停
        ui->pushButton_play->setIcon(QIcon(":/icon/play.png"));
    }
    else
    {
        player->play();//播放
        addToHistory();
        ui->pushButton_play->setIcon(QIcon(":/icon/pause.png"));
    }
}

void MainWindow::on_pushButton_next_clicked()
{
    int index = playlist->currentIndex()==playlist->mediaCount()-1?
                0:
                playlist->nextIndex();
    playlist->setCurrentIndex(index);
    ui->listWidget_names->setCurrentRow(playlist->currentIndex());
    player->play();
    addToHistory();
}

void MainWindow::on_pushButton_history_clicked()
{
    HistoryDialog* hd = new HistoryDialog(this);
    hd->show();
}



void MainWindow::on_pushButton_close_clicked()
{
    ShutdownDialog* sd = new ShutdownDialog(this);
    sd->exec();  // 使用 exec() 以模态方式显示，或使用 show() 非模态显示
    // 如果使用 show()，则改为：sd->show();
}
