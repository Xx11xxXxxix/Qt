#include "recommendwidget.h"
#include <QVBoxLayout>
#include <QLabel>

RecommendWidget::RecommendWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    listWidget = new QListWidget(this);
    layout->addWidget(listWidget);
    connect(listWidget, &QListWidget::itemClicked,
            this, &RecommendWidget::onListItemClicked);
}

void RecommendWidget::createSongItem(const Song& song) {
    QWidget* itemWidget = new QWidget;
    QHBoxLayout* layout = new QHBoxLayout(itemWidget);


    QVBoxLayout* infoLayout = new QVBoxLayout;
    QLabel* nameLabel = new QLabel(song.name);
    QLabel* artistLabel = new QLabel(song.artists);

    nameLabel->setStyleSheet("font-size: 14px; font-weight: bold; font-family: KaiTi;");
    artistLabel->setStyleSheet("color: gray;");

    infoLayout->addWidget(nameLabel);
    infoLayout->addWidget(artistLabel);

    layout->addLayout(infoLayout);

    QListWidgetItem* item = new QListWidgetItem(listWidget);
    item->setSizeHint(itemWidget->sizeHint());
    listWidget->setItemWidget(item, itemWidget);
}

void RecommendWidget::setSongs(const QList<Song>& songs) {
    currentSongs=songs;
    listWidget->clear();
    for(const Song& song : songs) {
        QListWidgetItem* item=new QListWidgetItem(song.name);
        item->setData(Qt::UserRole,song.id);
        listWidget->addItem(item);
    }
}
void RecommendWidget::onListItemClicked(QListWidgetItem* item) {
    if (item) {
        qint64 songId = item->data(Qt::UserRole).toLongLong();
        emit songClicked(songId);  // 发出信号
    }
}
