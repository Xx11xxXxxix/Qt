#ifndef SONGAPI_H
#define SONGAPI_H

#include <QObject>
#include <QNetworkAccessManager>
#include<QNetworkReply>
#include"models/song.h"

class SongAPI:public QObject{
    Q_OBJECT
public:
    static SongAPI& instance();
    void getSongUrl(qint64 songId);

signals:
    void songUrlReceived(qint64 songId,const QString& url);

private:
    explicit SongAPI(QObject *parent=nullptr);

    QNetworkAccessManager* networkManager;
    QString getLastLoginCookie();
};

#endif
