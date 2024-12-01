#include "loginwidget.h"
#include "qrcodewidget.h"
#include <QtNetwork>
#include <QVBoxLayout>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include "apilogger.h"

LoginWidget::LoginWidget(QWidget *parent) : QWidget(parent), isChecking(false)
{
    setupUI();
    networkManager = new QNetworkAccessManager(this);
    statusCheckTimer = new QTimer(this);
    statusCheckTimer->setInterval(2000);
    connect(statusCheckTimer, &QTimer::timeout, this, &LoginWidget::checkQRStatus);
    requestQRCode();
}

void LoginWidget::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QPushButton *backButton = new QPushButton(tr("返回"), this);
    backButton->setFixedSize(60, 30);
    connect(backButton, &QPushButton::clicked, this, [this]() {
        emit backRequested();
    });


    qrCodeWidget = new QRCodeWidget(this);
    statusLabel = new QLabel(tr("用几把网易云扫"), this);
    statusLabel->setAlignment(Qt::AlignCenter);

    refreshButton = new QPushButton(tr("刷这个二维码好像也没用"), this);
    connect(refreshButton, &QPushButton::clicked, this, &LoginWidget::onLoginButtonClicked);

    QHBoxLayout *topLayout=new QHBoxLayout;
    topLayout->addWidget(backButton);
    topLayout->addStretch();
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(qrCodeWidget, 0, Qt::AlignCenter);
    mainLayout->addWidget(statusLabel);
    mainLayout->addWidget(refreshButton);

    setFixedSize(300, 400);
}

void LoginWidget::onLoginButtonClicked()
{
    requestQRCode();
}

void LoginWidget::onQRCodeReceived(const QByteArray &data)
{

    QJsonDocument doc = QJsonDocument::fromJson(data);
    APILogger::instance().logAPI(
        "qr_code_generate",
        QString("unikey: %1").arg(currentUnikey),
        doc,
        doc.object()["code"].toInt()
        );
    QJsonObject obj = doc.object();

    if (obj["code"].toInt() == 200) {
        QString qrimg = obj["data"].toObject()["qrimg"].toString();
        qDebug() << "long!!!!:" << qrimg.length();


        if (qrimg.startsWith("data:image/png;base64,")) {
            QString base64Data = qrimg.mid(qrimg.indexOf(",") + 1);
            qDebug() << "length!!!" << base64Data.length();

            QByteArray imageData = QByteArray::fromBase64(base64Data.toUtf8());
            qDebug() << "max::!!!!" << imageData.size();


            QFile file("debug_qrcode.png");
            if (file.open(QIODevice::WriteOnly)) {
                file.write(imageData);
                file.close();
                qDebug() << "SAVEED!!!!debug_qrcode.png";
            }

            qrCodeWidget->setQRCode(imageData);
            startStatusCheck();
        } else {
            qDebug() << "WRONG TYEP!!!";
            qDebug() << "RECIVED!!!!:" << qrimg.left(100) << "...";
        }
    } else {
        qDebug() << "code isn't !!!!200";
    }
}

void LoginWidget::onCheckStatusTimeout()
{
    checkQRStatus();
}

void LoginWidget::onStatusCheckResponse(const QByteArray &data)
{
    QJsonDocument doc = QJsonDocument::fromJson(data);
    APILogger::instance().logAPI(
        "qr_status_check",
        QString("unikey: %1").arg(currentUnikey),
                doc,
        doc.object()["code"].toInt()
        );
    QJsonObject obj = doc.object();

    int code = obj["code"].toInt();
    switch(code) {
    case 800:
        statusLabel->setText(tr("过期啦"));
        stopStatusCheck();
        break;
    case 801:
        statusLabel->setText(tr("快扫"));
        break;
    case 802:
        statusLabel->setText(tr("确认了吗"));
        break;
    case 803:
        statusLabel->setText(tr("牛逼"));
        stopStatusCheck();
        QString cookie = obj["cookie"].toString();

        break;
    }
}

void LoginWidget::requestQRCode()
{
    qDebug()<<"有二维码了吗";

    QNetworkRequest request(QUrl("http://127.0.0.1:3000/login/qr/key"));
    QNetworkReply *reply = networkManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        reply->deleteLater();

        if (reply->error() == QNetworkReply::NoError) {
            QByteArray data = reply->readAll();

            qDebug()<<"nuikey??"<<QString(data);

            QJsonDocument doc = QJsonDocument::fromJson(data);
            QJsonObject obj = doc.object();

            if (obj["code"].toInt() == 200) {
                currentUnikey = obj["data"].toObject()["unikey"].toString();

                qDebug()<<"unikeyyoule!!"<<currentUnikey;

                QNetworkRequest qrRequest(QUrl(QString("http://127.0.0.1:3000/login/qr/create?key=%1&qrimg=true")
                                                   .arg(currentUnikey)));

                qDebug()<<"base64!!"<<qrRequest.url().toString();

                QNetworkReply *qrReply = networkManager->get(qrRequest);
                connect(qrReply, &QNetworkReply::finished, this, [this, qrReply]() {
                    qrReply->deleteLater();
                    if (qrReply->error() == QNetworkReply::NoError) {
                        QByteArray response=qrReply->readAll();
                        qDebug()<<"erWEima!!"<<QString(response);
                        onQRCodeReceived(response);
                    }else{
                        qDebug()<<"ERROR!!!"<<qrReply->errorString();
                    }
                });
            }
        }
    });
}

void LoginWidget::checkQRStatus()
{
    if (!isChecking || currentUnikey.isEmpty()) return;
    qDebug() << "SCANNING.!!!.. Key:" << currentUnikey;
    QNetworkRequest request(QUrl(QString("http://127.0.0.1:3000/login/qr/check?key=%1")
                                     .arg(currentUnikey)));
    QNetworkReply *reply = networkManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        reply->deleteLater();
        if (reply->error() == QNetworkReply::NoError) {
               QByteArray responseData = reply->readAll();
             qDebug() << "Scan response:" << QString(responseData);
           onStatusCheckResponse(responseData);

        }
    });
}

void LoginWidget::startStatusCheck()
{
    isChecking = true;
    statusCheckTimer->start();
}

void LoginWidget::stopStatusCheck()
{
    isChecking = false;
    statusCheckTimer->stop();
}

LoginWidget::~LoginWidget()
{
    stopStatusCheck();
}
