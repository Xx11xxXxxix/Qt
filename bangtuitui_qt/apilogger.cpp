#include "apilogger.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

APILogger::APILogger(QObject *parent) : QObject(parent) {
    if (!initDatabase()) {
        qWarning() << "JIEXISHIBAI!!!!";
    }
}

APILogger& APILogger::instance() {
    static APILogger instance;
    return instance;
}

bool APILogger::initDatabase() {
    db = QSqlDatabase::addDatabase("QSQLITE", "logger");
    db.setDatabaseName("D:/Qt/SQLite/api_logs.db");

    if (!db.open()) {
        qWarning() << "bAOUCNshibai!!!!:" << db.lastError().text();
        return false;
    }

    return createTable();
}

bool APILogger::createTable() {
    QSqlQuery query(db);
    return query.exec(
        "CREATE TABLE IF NOT EXISTS api_logs ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "api_name TEXT NOT NULL,"
        "request_params TEXT,"
        "response_data TEXT,"
        "time DATETIME DEFAULT CURRENT_TIMESTAMP,"
        "status_code INTEGER,"
        "error_message TEXT"
        ")"
        );
}

void APILogger::logAPI(const QString& apiName,
                       const QString& requestParams,
                       const QJsonDocument& responseData,
                       int statusCode,
                       const QString& errorMessage) {
    try {
        QSqlQuery query(db);
        query.prepare(
            "INSERT INTO api_logs (api_name, request_params, response_data, "
            "status_code, error_message) "
            "VALUES (?, ?, ?, ?, ?)"
            );

        query.addBindValue(apiName);
        query.addBindValue(requestParams);
        query.addBindValue(responseData.toJson(QJsonDocument::Compact));
        query.addBindValue(statusCode);
        query.addBindValue(errorMessage);

        if (!query.exec()) {
            qWarning() << "JILUSHIBAI!!!!:" << query.lastError().text();
        }
    } catch (const std::exception& e) {
        qWarning() << "JILUSHIBAI!!!222" << e.what();
    }
}
