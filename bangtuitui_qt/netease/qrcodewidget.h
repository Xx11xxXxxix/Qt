#ifndef QRCODEWIDGET_H
#define QRCODEWIDGET_H

#include <QWidget>
#include <QPixmap>


class QPainter;
class QPaintEvent;

class QRCodeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QRCodeWidget(QWidget *parent = nullptr);
    void setQRCode(const QByteArray &imageData);
    void clear();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap qrPixmap;
    bool hasError;
    QString errorMessage;
};

#endif // QRCODEWIDGET_H
