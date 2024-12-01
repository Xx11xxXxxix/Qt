#include "mainpage.h"
#include <QNetworkRequest>
#include<QUrl>
#include "widgets/recommendwidget.h"
#include <QLabel>
#include "../api/songapi.h"
MainPage::MainPage(QWidget *parent) : QWidget(parent) {
    setupUI();
    recommendWidget=new RecommendWidget(this);
    audioPlayer=new AudioPlayer(this);
    //介是播放器
    layout->addWidget(audioPlayer);
       layout->addWidget(recommendWidget);
    connect(&RecommendAPI::instance(), &RecommendAPI::dailySongsReceived,
            this, &MainPage::onRecommendReceived);
       connect(recommendWidget, &RecommendWidget::songClicked,
               this, &MainPage::onSongClicked);
       connect(&SongAPI::instance(), &SongAPI::songUrlReceived,
               this, [this](qint64 songId, const QString& url) {
                   qDebug() << "SongURL!!!!:" << url;
           if(!url.isEmpty()){
               //放歌
               audioPlayer->setSource(url);
           }
               });
}

void MainPage::setupUI() {
    layout=new QVBoxLayout(this);
    QLabel* welcomeLabel = new QLabel(tr("你来啦!"));
    recommendButton = new QPushButton(tr("今天的破歌"), this);

    layout->addWidget(welcomeLabel);
    layout->addWidget(recommendButton);

    connect(recommendButton, &QPushButton::clicked,
            this, &MainPage::onRecommendButtonClicked);
}

void MainPage::onRecommendButtonClicked() {
    RecommendAPI::instance().getDailySongs();
}

void MainPage::onRecommendReceived(const QList<Song>& songs) {
    qDebug() << "RITTUI!!!!" << songs.size() << "LAILA";
    recommendWidget->setSongs(songs);
}
void MainPage::onSongClicked(qint64 songId){
    SongAPI::instance().getSongUrl(songId);
}
