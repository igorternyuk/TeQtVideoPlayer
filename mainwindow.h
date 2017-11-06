#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QMediaPlayer>

class PlaylistWindow;
class VideoWidget;
class QProgressBar;
class QSlider;
class QLabel;

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    //void resizeEvent(QResizeEvent *event) override;

private:
    enum {WINDOW_WIDTH_MIN = 940, WINDOW_HEIGHT_MIN = 600};
    Ui::MainWindow *ui;    
    QMediaPlayer *m_player;
    PlaylistWindow *m_pls_window;
    VideoWidget *m_video_widget;
    QLabel *m_current_play_time_label;
    QProgressBar *m_seek_bar;
    QLabel *m_remaining_time_label;
    QSlider *m_seek_slider;
    QLabel *m_volume_label;
    QSlider *m_volume_slider;
    void displayErrorMessage(const QString &msg);
private slots:
    void on_actionOpen_triggered();
    void on_actionPlay_triggered();
    void on_actionPause_triggered();
    void on_actionStop_triggered();
    void update_volume_label(int curr_vol);
    void change_volume_level(int delta);
    void update_seek_slider_value(qint64 curr_player_pos);
    void update_player_pos(int seek_slider_pos);
    void update_time_labels(int curr_player_pos);
    void update_title(QString newTitle);
    //void statusChanged(QMediaPlayer::MediaStatus status);
    //void handleCursor(QMediaPlayer::MediaStatus status);
    //void setStatusInfo(const QString &info);
    void on_action_seek_forwards_triggered();
    void on_action_seek_backwards_triggered();
    void on_action_show_playlist_triggered();
    void on_action_prev_triggered();
    void on_action_next_triggered();
};

#endif // MAINWINDOW_H
