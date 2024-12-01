#ifndef RECOMMENDAPI_H
#define RECOMMENDAPI_H
#include <QtNetwork>
#include <QtNetwork/QNetworkAccessManager>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QObject>


#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "../models/song.h"

class RecommendAPI : public QObject {
    Q_OBJECT
private:
    explicit RecommendAPI(QObject *parent = nullptr);
    QNetworkAccessManager* networkManager=nullptr;


public:
    static RecommendAPI& instance();
    void getDailySongs();

//拿cookie
public:
    static QString getLastLoginCookie();
private:
    static QString parseCookieFromJson(const QJsonObject& obj);
signals:
    void dailySongsReceived(const QList<Song>& songs);
};

#endif
