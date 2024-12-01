#ifndef APILOGGER_H
#define APILOGGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QDateTime>
#include <QJsonDocument>

class APILogger : public QObject {
    Q_OBJECT
public:
    static APILogger& instance();

    void logAPI(const QString& apiName,
                const QString& requestParams,
                const QJsonDocument& responseData,
                int statusCode,
                const QString& errorMessage = QString());

private:
    explicit APILogger(QObject *parent = nullptr);
    bool initDatabase();
    bool createTable();

    QSqlDatabase db;
};
#endif // APILOGGER_H
