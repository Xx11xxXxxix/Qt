#include"songapi.h"
#include <QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>
#include<QSqlQuery>
#include<QSqlError>
#include<QDebug>


SongAPI& SongAPI::instance(){
    static SongAPI instance;
    return instance;
}

SongAPI::SongAPI(QObject *parent):QObject(parent){
    networkManager=new QNetworkAccessManager(this);

}
void SongAPI::getSongUrl(qint64 songId) {
    QString cookie = getLastLoginCookie();
    QString urlStr = QString("http://127.0.0.1:3000/song/url?id=%1&cookie=%2")
                         .arg(songId)
                         .arg(cookie);
      qDebug() << "API URL:" << urlStr;
    QUrl url(urlStr);
    QNetworkRequest request(url);

    QNetworkReply* reply = networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply, songId]() {
        reply->deleteLater();
        if (reply->error() == QNetworkReply::NoError) {
            QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
            QJsonArray data = doc.object()["data"].toArray();
            if (!data.isEmpty()) {
                QString url = data.first().toObject()["url"].toString();
                emit songUrlReceived(songId, url);
            }
        }
    });
}

QString SongAPI::getLastLoginCookie(){
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE","cookie_check");
    db.setDatabaseName("api_logs.db");
    if(!db.open())return QString();
    QSqlQuery query(db);
    query.prepare("SELECT response_data FROM api_logs WHERR api_name='qr_status_check'" "AND status_code=803 ORDER BY time DESC LIMIT 1");
    if(query.exec() && query.next()){
        QJsonDocument doc =QJsonDocument::fromJson(query.value(0).toString().toUtf8());
        return doc.object()["cookie"].toString();

    }
    db.close();
    return QString();
}
