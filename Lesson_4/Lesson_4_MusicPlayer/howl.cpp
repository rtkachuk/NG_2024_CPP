#include "howl.h"
#include "ui_howl.h"

Howl::Howl(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Howl)
{
    ui->setupUi(this);

    m_player = new QMediaPlayer(this);
    m_audioOutput = new QAudioOutput(this);

    m_player->setAudioOutput(m_audioOutput);
    ui->s_volume->setValue(m_audioOutput->volume());
    ui->p_position->setValue(0);
    ui->s_volume->setRange(0, 100);

    connect (ui->b_select, &QPushButton::clicked, this, &Howl::setSong);
    connect (ui->s_volume, &QSlider::valueChanged, this, &Howl::updateVolume);
    connect (ui->b_playPause, &QPushButton::clicked, this, &Howl::playPause);
    connect (m_player, &QMediaPlayer::positionChanged, this, &Howl::updatePosition);
}

Howl::~Howl()
{
    delete ui;
}

void Howl::playPause()
{
    if (m_player->isPlaying()) {
        m_player->pause();
    } else {
        m_player->play();
    }
}

void Howl::next()
{

}

void Howl::previous()
{

}

void Howl::updatePosition(qint64 pos)
{
    ui->p_position->setValue(pos / (m_player->duration() / 100));
}

void Howl::setSong()
{
    QString path = QFileDialog::getOpenFileName(this, "Chto budem igrat'?", QDir::homePath(), "*.mp3");
    ui->l_songName->setText(path);
    m_player->setSource(QUrl::fromLocalFile(path));
}

void Howl::updateVolume(float volume)
{
    m_audioOutput->setVolume(volume/100);
}
