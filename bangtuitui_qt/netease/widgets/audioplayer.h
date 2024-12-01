#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QWidget>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QAudioOutput>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

class AudioPlayer : public QWidget {
    Q_OBJECT
public:
    explicit AudioPlayer(QWidget *parent = nullptr);
    void setSource(const QString& url);

public slots:
    void play();
    void pause();
    void stop();

private slots:
    void onPositionChanged(qint64 position);
    void onDurationChanged(qint64 duration);
    void onSliderMoved(int position);
    void updatePlayButtonIcon();
    void onVolumeChanged(int volume);
    void toggleMute();
    void updateVolumeIcon();


private:
    void setupUI();
    void setupConnections();
    QString formatTime(qint64 milliseconds);
    void setupStyle();

    QMediaPlayer* player;
    QAudioOutput* audioOutput;
    QWidget* controlPanel;


    // UI elements
    QPushButton* playButton;
    QPushButton* volumeButton;
    QSlider* volumeSlider;
    QSlider* progressSlider;
    QLabel* timeLabel;
    QLabel* durationLabel;

    bool isMuted=false;
    int lastVolume=100;
    bool isPlaying = false;
};

#endif
