#ifndef ADMINUSER_H
#define ADMINUSER_H

#include <QObject>
#include <QSqlDatabase>
#include <QDateTime>
#include <QJsonDocument>

class AdminUser {
public:
    QString id;
    QString username;
    QString neteaseId;
    int loginCounts;
    QDateTime lastLoginTime;

    static bool isValidMobile(const QString& mobile){
        return mobile.length()==11&&
               mobile.startsWith("1")&&
               mobile.toLongLong()!=0;
    }


};

#endif
