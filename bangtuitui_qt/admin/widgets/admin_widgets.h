#ifndef ADMINWIDGET_H
#define ADMINWIDGET_H

#include <QObject>
#include <QSqlDatabase>
#include <QDateTime>
#include <QJsonDocument>

class AdminWidget : public QWidget {
    Q_OBJECT
public:
    void generateQRCode();
    void handleNeteaseLogin();
signals:
    void neteaseAccountLinked(const QString& neteaseId);
    // ...
};

#endif
