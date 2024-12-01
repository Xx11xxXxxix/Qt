#include "audioplayer.h"
#include <QStyle>
#include "audioplayer.h"
#include <QTime>

#include <QUrl>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QAudioOutput>
    AudioPlayer::AudioPlayer(QWidget *parent) : QWidget(parent) {
    // 播放qi
    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);

    audioOutput->setVolume(lastVolume/100.0);
    setupUI();
    setupStyle();
    setupConnections();
}

void AudioPlayer::setupUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(4);
    mainLayout->setContentsMargins(10,10,10,10);


    QHBoxLayout* controlLayout = new QHBoxLayout();
    controlLayout->setSpacing(10);

    // 暂停
    playButton = new QPushButton(this);
    playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    playButton->setIconSize(QSize(32,32));
    playButton->setFixedSize(40,40);

    // 进度条
    progressSlider = new QSlider(Qt::Horizontal, this);
    progressSlider->setMinimum(0);

    // 时间标签
    timeLabel = new QLabel("0:00", this);
    durationLabel = new QLabel("0:00", this);
    timeLabel->setFixedWidth(50);
    durationLabel->setFixedWidth(50);

    //音量
    volumeButton=new QPushButton(this);
    volumeButton->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    volumeButton->setIconSize(QSize(20,20));
    volumeButton->setFixedSize(30,30);

    volumeSlider=new QSlider(Qt::Horizontal,this);
    volumeSlider->setRange(0,100);
    volumeSlider->setValue(lastVolume);
    volumeSlider->setFixedWidth(80);


    // 下面是布局
    controlLayout->addWidget(playButton);
    controlLayout->addWidget(timeLabel);
    controlLayout->addWidget(progressSlider);
    controlLayout->addWidget(durationLabel);
    controlLayout->addWidget(volumeButton);
    controlLayout->addWidget(volumeSlider);;

    mainLayout->addLayout(controlLayout);

}

void AudioPlayer::setupConnections() {
    connect(playButton, &QPushButton::clicked, this, [this]() {
        if (isPlaying) {
            pause();
        } else     play();

    });

    connect(player, &QMediaPlayer::positionChanged, this, &AudioPlayer::onPositionChanged);
    connect(player, &QMediaPlayer::durationChanged, this, &AudioPlayer::onDurationChanged);
    connect(progressSlider, &QSlider::sliderMoved, this, &AudioPlayer::onSliderMoved);

    connect(volumeButton, &QPushButton::clicked,this,&AudioPlayer::toggleMute);
    connect(volumeSlider,&QSlider::valueChanged,this,&AudioPlayer::onVolumeChanged);
}
void AudioPlayer::onVolumeChanged(int volume){
    if(!isMuted){
        lastVolume=volume;
        audioOutput->setVolume(volume/100.0);
    }
    updateVolumeIcon();
}

void AudioPlayer::toggleMute(){
    isMuted=!isMuted;
    if(isMuted){
        audioOutput->setVolume(0);
    }else{
        audioOutput->setVolume(lastVolume/100.0);
        volumeSlider->setValue(lastVolume);
    }
    updateVolumeIcon();
}
void AudioPlayer::updateVolumeIcon(){
    QStyle::StandardPixmap  icon;
    if(isMuted || volumeSlider->value()==0){
        icon=QStyle::SP_MediaVolumeMuted;
    }else if (volumeSlider->value()<50){
        icon=QStyle::SP_MediaVolume;
    }else{
        icon=QStyle::SP_MediaVolume;
    }
    volumeButton->setIcon(style()->standardIcon(icon));
}
void AudioPlayer::setSource(const QString& url) {
    player->setSource(QUrl(url));
    play();
}

void AudioPlayer::play() {
    player->play();
    isPlaying = true;
    updatePlayButtonIcon();
}

void AudioPlayer::pause() {
    player->pause();
    isPlaying = false;
    updatePlayButtonIcon();
}

void AudioPlayer::stop() {
    player->stop();
    isPlaying = false;
    updatePlayButtonIcon();
}
QString AudioPlayer::formatTime(qint64 milliseconds){
    QTime time(0,0);
    time=time.addMSecs(milliseconds);
    return time.toString(time.hour()>0?"h:mm:ss":"m:ss");
}

void AudioPlayer::onPositionChanged(qint64 position) {
    progressSlider->setValue(position);
    timeLabel->setText(formatTime(position));
}

void AudioPlayer::onDurationChanged(qint64 duration) {
    progressSlider->setMaximum(duration);
    durationLabel->setText(formatTime(duration));
}



void AudioPlayer::onSliderMoved(int position) {
    player->setPosition(position);
}

void AudioPlayer::updatePlayButtonIcon() {
    playButton->setIcon(style()->standardIcon(
        isPlaying ? QStyle::SP_MediaPause : QStyle::SP_MediaPlay
        ));
}
void AudioPlayer::setupStyle() {
    setStyleSheet(R"(
        QWidget {
            background-color: transparent;
        }
        QPushButton {
            border: none;
            padding: 5px;
            border-radius: 4px;
            background-color: transparent;
        }
        QPushButton:hover {
            background-color: rgba(255, 255, 255, 0.1);
        }
        QSlider::groove:horizontal {
            border: none;
            height: 4px;
            background: rgba(255, 255, 255, 0.2);
            margin: 0px;
            border-radius: 2px;
        }
        QSlider::handle:horizontal {
            background: white;
            border: none;
            width: 12px;
            height: 12px;
            margin: -4px 0;
            border-radius: 6px;
        }
        QSlider::sub-page:horizontal {
            background: white;
            border-radius: 2px;
        }
        QLabel {
            color: white;
            font-size: 12px;
        }
    )");
}
