#ifndef HOWL_H
#define HOWL_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QSlider>

QT_BEGIN_NAMESPACE
namespace Ui {
class Howl;
}
QT_END_NAMESPACE

class Howl : public QMainWindow
{
    Q_OBJECT

public:
    Howl(QWidget *parent = nullptr);
    ~Howl();

private:
    Ui::Howl *ui;
    QMediaPlayer *m_player;
    QAudioOutput *m_audioOutput;

    QStringList m_songs;

private slots:
    void playPause();
    void next();
    void previous();
    void updatePosition(qint64 pos);
    void addSong();
    void setCurrentSong(QString path);
    void updateVolume(float volume);
};
#endif // HOWL_H
