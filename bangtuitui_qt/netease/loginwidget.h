// loginwidget.h
#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QTimer>


class QRCodeWidget;

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();


signals:
    void backRequested();
private slots:
    void onLoginButtonClicked();
    void onQRCodeReceived(const QByteArray &data);
    void onCheckStatusTimeout();
    void onStatusCheckResponse(const QByteArray &data);

private:
    void setupUI();
    void requestQRCode();
    void checkQRStatus();
    void startStatusCheck();
    void stopStatusCheck();

    QRCodeWidget *qrCodeWidget;
    QLabel *statusLabel;
    QPushButton *refreshButton;
    QNetworkAccessManager *networkManager;
    QTimer *statusCheckTimer;
    QString currentUnikey;
    bool isChecking;
};

#endif // LOGINWIDGET_H
