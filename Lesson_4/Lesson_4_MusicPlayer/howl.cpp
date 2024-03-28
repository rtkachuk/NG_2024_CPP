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

    connect (ui->b_add, &QPushButton::clicked, this, &Howl::addSong);
    connect (ui->s_volume, &QSlider::valueChanged, this, &Howl::updateVolume);
    connect (ui->b_playPause, &QPushButton::clicked, this, &Howl::playPause);
    connect (m_player, &QMediaPlayer::positionChanged, this, &Howl::updatePosition);
    connect (ui->lw_playlist, &QListWidget::currentTextChanged, ui->l_songName, &QLabel::setText);
    connect (ui->lw_playlist, &QListWidget::currentTextChanged, this, &Howl::setCurrentSong);
    connect (ui->lw_playlist, &QListWidget::currentTextChanged, this->m_player, &QMediaPlayer::stop);
}

Howl::~Howl()
{
    delete ui;
}

void Howl::playPause()
{
    if (m_player->isPlaying()) {
        m_player->pause();
        ui->b_playPause->setText(">");
    } else {
        m_player->play();
        ui->b_playPause->setText("||");
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

void Howl::addSong()
{
    QStringList songs = QFileDialog::getOpenFileNames(this, "Chto budem igrat'?", QDir::homePath(), "*.mp3");
    m_songs.append(songs);
    ui->lw_playlist->addItems(songs);
    //m_player->setSource(QUrl::fromLocalFile(path));
}

void Howl::setCurrentSong(QString path)
{
    m_player->setSource(QUrl::fromLocalFile(path));
}

void Howl::updateVolume(float volume)
{
    m_audioOutput->setVolume(volume/100);
}
