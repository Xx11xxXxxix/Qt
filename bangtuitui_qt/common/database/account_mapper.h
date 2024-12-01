#ifndef ACCOUNTMAPPER_H
#define ACCOUNTMAPPER_H

#include <QObject>
#include <QSqlDatabase>
#include <QDateTime>
#include <QJsonDocument>

class AccountMapper {
public:
    bool linkAccounts(const QString& adminId, const QString& neteaseId);
    QStringList getNeteaseAccounts(const QString& adminId);

};

#endif
