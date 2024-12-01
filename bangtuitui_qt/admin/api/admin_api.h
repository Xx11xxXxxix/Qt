#ifndef ADMINAPI_H
#define ADMINAPI_H
#include <QObject>
#include <QMap>
#include <random>
#include "../models/admin_user.h"

class AdminAPI : public QObject {
    Q_OBJECT
public:
    explicit AdminAPI(QObject *parent = nullptr);

    // 生成验证码
    QString generateVerificationCode(const QString& mobile);

    // 验证码登录（自动注册）
    bool loginWithCode(const QString& mobile, const QString& code);

private:
    QMap<QString, QString> verificationCodes; // 存储手机号-验证码映射
    QMap<QString, AdminUser> users;  // 模拟数据库存储

    // 生成6位随机验证码
    QString generateRandomCode() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(100000, 999999);
        return QString::number(dis(gen));
    }

    // 创建新用户
    AdminUser createUser(const QString& mobile) {
        AdminUser user;
        user.id = QString::number(QDateTime::currentMSecsSinceEpoch());
        user.mobile = mobile;
        user.loginCounts = 0;
        return user;
    }
};
#endif
