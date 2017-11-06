#ifndef PLAYLISTWINDOW_H
#define PLAYLISTWINDOW_H

#include <QWidget>

namespace Ui
{
    class PlaylistWindow;
}

class QMediaPlayer;
class QStandardItemModel;
class QMediaPlaylist;

class PlaylistWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PlaylistWindow(QMediaPlayer *player, QWidget *parent = nullptr);
    ~PlaylistWindow();
signals:
    void current_movie_title_changed(QString title);

public slots:
    void add_to_playlist();
    void prev_movie();
    void next_movie();

protected:
    void closeEvent(QCloseEvent*) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void on_btnHide_clicked();
    void load_choosen_playlist();
    void save_playlist_as();
    void clear_playlist();
    void remove_selected_items_from_playlist();
    void remove_selected_items_from_hdd();
    void on_action_remove_selected_items_from_playlist_triggered();
    void on_action_remove_selected_items_from_HDD_triggered();
    void on_action_clear_playlist_triggered();

private:
    const QString mLastPlaylistFilePath{"currentPlaylist.dat"};
    Ui::PlaylistWindow *ui;
    QMediaPlayer *m_player;
    QStandardItemModel *m_playlist_model;
    QMediaPlaylist *m_playlist;
    int m_current_index{0};

    bool load_playlist_from_file(const QString &filePath);
    bool save_playlist_to_file(const QString &filePath);
    void configure_playlist_view();
};

#endif // PLAYLISTWINDOW_H
