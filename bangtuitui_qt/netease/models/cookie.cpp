#include "cookie.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QtNetwork>
#include <QVBoxLayout>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>


QString Cookie::extractMusicU(const QString& fullCookie) {
    QStringList cookies = fullCookie.split(';');
    for(const QString& cookie : cookies) {
        if(cookie.trimmed().startsWith("MUSIC_U=")) {
            return cookie.trimmed();
        }
    }
    return QString();
}

QString Cookie::parseCookieFromDB() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "cookie_check");
    db.setDatabaseName("api_logs.db");

    if (!db.open()) return QString();

    QSqlQuery query(db);
    query.prepare("SELECT response_data FROM api_logs WHERE api_name = 'qr_status_check' "
                  "AND status_code = 803 ORDER BY time DESC LIMIT 1");

    if (query.exec() && query.next()) {
        QJsonDocument doc = QJsonDocument::fromJson(query.value(0).toString().toUtf8());
        QString fullCookie = doc.object()["cookie"].toString();
        return extractMusicU(fullCookie);
    }

    db.close();
    return QString();
}

QString Cookie::getMusicU() {
    return parseCookieFromDB();
}
