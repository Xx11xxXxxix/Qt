#ifndef SONG_H
#define SONG_H
#include <QString>
#include<QListWidget>



struct Song {
    QString name;
    QString artistName;
    QString albumName;
    QString picUrl;
    QString artists;
    qint64 id;
    int duration;
};

#endif
