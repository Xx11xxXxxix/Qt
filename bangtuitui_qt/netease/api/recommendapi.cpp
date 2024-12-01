#include "recommendapi.h"
#include <QNetworkRequest>
#include <QNetworkAccessManager>

#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
RecommendAPI& RecommendAPI::instance() {
    static RecommendAPI instance;
    return instance;
}

RecommendAPI::RecommendAPI(QObject *parent) : QObject(parent) {
    networkManager = new QNetworkAccessManager(this);
}

void RecommendAPI::getDailySongs() {
    QString cookie=getLastLoginCookie();
    QString urlStr = QString("http://127.0.0.1:3000/recommend/songs?cookie=%1").arg(cookie);
    QUrl url(urlStr);

  QNetworkRequest request(url);

    QNetworkReply* reply = networkManager->get(request);


    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        reply->deleteLater();
        if (reply->error() == QNetworkReply::NoError) {
            QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
            QJsonArray songs = doc.object()["data"].toObject()["dailySongs"].toArray();

            QList<Song> songList;
            for (const auto& songValue : songs) {
                QJsonObject songObj = songValue.toObject();
                Song song;
                song.name = songObj["name"].toString();
                song.id = songObj["id"].toInteger();
                songList.append(song);
            }
            emit dailySongsReceived(songList);
        }
    });
}

QString RecommendAPI::getLastLoginCookie() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "cookie_check");
    db.setDatabaseName("api_logs.db");

    if (!db.open()) return QString();

    QSqlQuery query(db);
    query.prepare("SELECT response_data FROM api_logs WHERE api_name = 'qr_status_check' "
                  "AND status_code = 803 ORDER BY time DESC LIMIT 1");

    if (query.exec() && query.next()) {
        QJsonDocument doc = QJsonDocument::fromJson(query.value(0).toString().toUtf8());
        return doc.object()["cookie"].toString();
    }

    db.close();
    return QString();
}
