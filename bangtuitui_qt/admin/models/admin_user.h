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
    QString mobile;
    int loginCounts;
    QDateTime lastLoginTime;

    static bool isValidMobile(const QString& mobile){
        return mobile.length()==11&&
               mobile.startsWith("1")&&
               mobile.toLongLong()!=0;
    }

    bool saveToDatabase();
    static AdminUser loadFromDatabase(const QString& mobile);
    QList<QString> getLinkedNeteaseAccounts();
    bool linkNeteaseAccount(const QString& neteaseId);

};
// 实现数据库连接和初始化
bool initDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("admin.db");

    if (!db.open()) {
        return false;
    }

    // 创建主账号表
    db.exec("CREATE TABLE IF NOT EXISTS admin_users ("
            "id TEXT PRIMARY KEY,"
            "mobile TEXT UNIQUE,"
            "username TEXT,"
            "login_counts INTEGER,"
            "last_login_time DATETIME"
            ")");

    // 创建关联账号表
    db.exec("CREATE TABLE IF NOT EXISTS account_links ("
            "admin_id TEXT,"
            "netease_id TEXT,"
            "link_time DATETIME,"
            "PRIMARY KEY (admin_id, netease_id)"
            ")");

    return true;
}
bool saveToDatabase() {
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    query.prepare("INSERT OR REPLACE INTO admin_users "
                  "(id, mobile, login_counts, last_login_time) "
                  "VALUES (?, ?, ?, ?)");
    query.addBindValue(id);
    query.addBindValue(mobile);
    query.addBindValue(loginCounts);
    query.addBindValue(lastLoginTime);
    return query.exec();
}

static AdminUser loadFromDatabase(const QString& mobile) {
    AdminUser user;
    QSqlQuery query;
    query.prepare("SELECT * FROM admin_users WHERE mobile = ?");
    query.addBindValue(mobile);

    if (query.exec() && query.first()) {
        user.id = query.value("id").toString();
        user.mobile = query.value("mobile").toString();
        user.loginCounts = query.value("login_counts").toInt();
        user.lastLoginTime = query.value("last_login_time").toDateTime();
    }
    return user;
}
#endif
