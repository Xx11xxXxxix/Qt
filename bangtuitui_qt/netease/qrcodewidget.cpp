#include "qrcodewidget.h"
#include <QPainter>
#include <QDebug>

QRCodeWidget::QRCodeWidget(QWidget *parent)
    : QWidget(parent)
    , hasError(false)
{
    setMinimumSize(200, 200);
    setMaximumSize(200, 200);
}

void QRCodeWidget::setQRCode(const QByteArray &imageData)
{
    hasError = false;
    if (!qrPixmap.loadFromData(imageData)) {
        hasError = true;
        errorMessage = "NO!!!";
        qDebug() << "NO!!!!!:" << imageData.size();
    } else {
        qDebug() << "Done!A!!!:" << qrPixmap.size();
    }
    update();
}

void QRCodeWidget::clear()
{
    qrPixmap = QPixmap();
    hasError = false;
    update();
}

void QRCodeWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    if (!qrPixmap.isNull()) {
        QRect rect = this->rect();
        int x = (rect.width() - qrPixmap.width()) / 2;
        int y = (rect.height() - qrPixmap.height()) / 2;

        painter.drawPixmap(x, y, qrPixmap);

        painter.setPen(Qt::red);
        painter.drawText(10, 20,
                         QString("Size: %1x%2").arg(qrPixmap.width()).arg(qrPixmap.height()));
    } else {
        painter.fillRect(rect(), Qt::white);
        if (hasError) {
            painter.drawText(rect(), Qt::AlignCenter, errorMessage);
        } else {
            painter.drawText(rect(), Qt::AlignCenter, "wait!!...");
        }
    }
}
