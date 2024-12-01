#ifndef RECOMMENDWIDGET_H
#define RECOMMENDWIDGET_H


#include <QWidget>
#include<QListWidget>
#include"../models/song.h"
#include<QVBoxLayout>


class RecommendWidget:public QWidget{
    Q_OBJECT
public:
    explicit RecommendWidget(QWidget *parent=nullptr);
    void setSongs(const QList<Song>& songs);

private:
    QListWidget* listWidget;
    void createSongItem(const Song& song);
    QList<Song> currentSongs;
signals:
    void songClicked(qint64 songId);
private slots:
    void onListItemClicked(QListWidgetItem* item);

};

#endif
