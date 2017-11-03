#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "videowidget.h"
#include <QMediaPlayer>
#include <QProgressBar>
#include <QSlider>
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include <QKeyEvent>
#include <QStringList>
#include <QStandardPaths>
#include <QDebug>
#include <sstream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("TeMedia");
    this->setMinimumSize(QSize(WINDOW_WIDTH_MIN, WINDOW_HEIGHT_MIN));

    m_player = new QMediaPlayer(this);
    m_video_widget = new VideoWidget(this);
    m_player->setVideoOutput(m_video_widget);
    m_player->setVolume(50);
    this->setCentralWidget(m_video_widget);

    m_current_play_time_label = new QLabel(this);
    m_seek_bar = new QProgressBar(this);
    m_seek_slider = new QSlider(this);
    m_seek_slider->setOrientation(Qt::Horizontal);
    m_seek_slider->setMaximum(100);
    m_seek_slider->setMinimumWidth(250);
    m_remaining_time_label = new QLabel(this);

    m_volume_label = new QLabel("Volume:50%",this);
    m_volume_slider = new QSlider(this);
    m_volume_slider->setOrientation(Qt::Horizontal);
    m_volume_slider->setMaximumWidth(70);
    m_volume_slider->setMaximum(100);
    m_volume_slider->setMinimum(0);
    m_volume_slider->setValue(50);

    ui->statusBar->addPermanentWidget(m_seek_bar);
    ui->statusBar->addPermanentWidget(m_current_play_time_label);
    ui->statusBar->addPermanentWidget(m_seek_slider);
    ui->statusBar->addPermanentWidget(m_remaining_time_label);
    ui->statusBar->addPermanentWidget(m_volume_label);
    ui->statusBar->addPermanentWidget(m_volume_slider);

    connect(m_player, &QMediaPlayer::positionChanged, this, &MainWindow::update_seek_slider_value);
    connect(m_player, &QMediaPlayer::positionChanged, this, &MainWindow::update_time_labels);
    connect(m_seek_slider, &QSlider::sliderMoved, this, &MainWindow::update_player_pos);
    //connect(m_seek_slider, &QSlider::valueChanged, this, &MainWindow::update_player_pos);
    //connect(m_seek_slider, &QSlider::sliderPressed, this, &MainWindow::update_player_pos2);
    connect(m_player, &QMediaPlayer::durationChanged, m_seek_bar, &QProgressBar::setMaximum);
    connect(m_player, &QMediaPlayer::positionChanged, m_seek_bar, &QProgressBar::setValue);
    connect(m_video_widget, &VideoWidget::pauseRequestInFullscreenMode,
            this, &MainWindow::on_actionPause_triggered);
    connect(m_player, &QMediaPlayer::volumeChanged, m_volume_slider, &QSlider::setValue);
    connect(m_volume_slider, &QSlider::sliderMoved, m_player, &QMediaPlayer::setVolume);
    connect(m_volume_slider, &QSlider::valueChanged, m_player, &QMediaPlayer::setVolume);
    connect(m_volume_slider, &QSlider::valueChanged, this, &MainWindow::update_volume_label);
    connect(m_video_widget, &VideoWidget::volumeLevelChanged, this, &MainWindow::change_volume_level);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    auto dir = QStandardPaths::standardLocations(QStandardPaths::MoviesLocation)
            .value(0, QDir::homePath());

    QString fileName = QFileDialog::getOpenFileName(this, "Open a file", dir,
                                                    "Video files (*.mp4 *.flv *\
                                                    .avi *.mpeg);;All files (*.*)");
    on_actionStop_triggered();
    m_player->setMedia(QUrl::fromLocalFile(fileName));
    on_actionPlay_triggered();
    this->setWindowTitle(QString("TeMedia - ") + QString(fileName));
}

void MainWindow::on_actionPlay_triggered()
{
    m_player->play();
    ui->statusBar->showMessage("Playing ...");
}

void MainWindow::on_actionPause_triggered()
{
    if(m_player->state() == QMediaPlayer::State::PlayingState)
    {
        m_player->pause();
        ui->statusBar->showMessage("Paused");
    }
    else if(m_player->state() == QMediaPlayer::State::PausedState)
    {
       m_player->play();
       ui->statusBar->showMessage("Playing ...");
    }
}

void MainWindow::on_actionStop_triggered()
{
    m_player->stop();
    ui->statusBar->showMessage("Stop");
}

void MainWindow::update_volume_label(int curr_vol)
{
    m_volume_label->setText(QString("Volume:") + QString::number(curr_vol) + QString("%"));
}

void MainWindow::change_volume_level(int delta)
{
    if(delta > 0)
    {
        m_volume_slider->setValue(m_volume_slider->value() + 2);
    }
    else
    {
        m_volume_slider->setValue(m_volume_slider->value() - 2);
    }
}

void MainWindow::update_seek_slider_value(qint64 curr_player_pos)
{
     m_seek_slider->setValue((int)((float)curr_player_pos / m_player->duration() * 100));
}

void MainWindow::update_player_pos(int seek_slider_pos)
{
    auto p = m_player->duration() * seek_slider_pos / 100;
    qDebug() << "new player pos = " << p;
    m_player->setPosition(p);
}

/*void MainWindow::update_player_pos2()
{
    auto p = m_player->duration() * m_seek_slider->value() / 100;
    qDebug() << "new player pos = " << p;
    m_player->setPosition(p);
}*/


void MainWindow::update_time_labels(int curr_player_pos)
{
    auto curr_pos = curr_player_pos / 1000;
    std::stringstream ss_curr_pos;
    ss_curr_pos << curr_pos / 3600 << "h:" << (curr_pos % 3600) / 60 << "m:" <<
        (curr_pos % 3600) % 60 << "s";
    auto total_duration = m_player->duration() / 1000;
    std::stringstream ss_total_dur;
    ss_total_dur << total_duration / 3600 << "h:" << (total_duration % 3600) / 60 << "m:" <<
        (total_duration % 3600) % 60 << "s";
    auto remaining_time = total_duration - curr_pos;
    std::stringstream ss_remains;
    ss_remains << remaining_time / 3600 << "h:" << (remaining_time % 3600) / 60 << "m:" <<
        (remaining_time % 3600) % 60 << "s";
    m_current_play_time_label->setText(QString::fromStdString(ss_curr_pos.str()));
    m_remaining_time_label->setText(QString("Remains:%1/(Total:%2)")
                                    .arg(QString::fromStdString(ss_remains.str()))
                                    .arg(QString::fromStdString(ss_total_dur.str())));
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MouseButton::MiddleButton)
    {
        on_actionPause_triggered();
    }
    else
    {
        QMainWindow::mouseReleaseEvent(event);
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space){
        on_actionPause_triggered();
    }
    else if(event->key() == Qt::Key_F && !this->isFullScreen())
    {
        m_video_widget->toggleFullScreenMode();
        event->accept();
    }
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    change_volume_level(event->angleDelta().y());
}

/*void MainWindow::resizeEvent(QResizeEvent *event)
{
    qDebug() << "w = " << this->width() << " h = " << this->height();
    QMainWindow::resizeEvent(event);
}*/
