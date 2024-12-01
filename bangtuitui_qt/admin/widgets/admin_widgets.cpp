#include "admin_widgets.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class AdminWidget {
private:
    QLabel* qrCodeLabel;
    QPushButton* generateQRCodeBtn;
    QListWidget* linkedAccountsList;

    void setupUI() {
        // 创建二维码显示区域
        // 创建账号列表
        // 创建操作按钮
    }

    void updateLinkedAccounts() {
        // 刷新关联账号列表
    }
};
