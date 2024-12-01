#include "admin_api.h"
#include <QDebug>

AdminAPI::AdminAPI(QObject *parent) : QObject(parent) {}

QString AdminAPI::generateVerificationCode(const QString& mobile) {
    if (!AdminUser::isValidMobile(mobile)) {
        return QString();
    }

    QString code = generateRandomCode();
    verificationCodes[mobile] = code;

    // TODO: 在实际应用中，这里应该调用SMS服务发送验证码
    qDebug() << "Verification code for" << mobile << ":" << code;

    return code;
}

bool AdminAPI::loginWithCode(const QString& mobile, const QString& code) {
    // 验证手机号格式
    if (!AdminUser::isValidMobile(mobile)) {
        qDebug() << "Invalid mobile number";
        return false;
    }

    // 验证验证码
    if (!verificationCodes.contains(mobile) ||
        verificationCodes[mobile] != code) {
        qDebug() << "Invalid verification code";
        return false;
    }

    // 验证成功后清除验证码
    verificationCodes.remove(mobile);

    // 检查用户是否存在，不存在则创建
    if (!users.contains(mobile)) {
        users[mobile] = createUser(mobile);
    }

    // 更新登录信息
    AdminUser& user = users[mobile];
    user.loginCounts++;
    user.lastLoginTime = QDateTime::currentDateTime();

    qDebug() << "User" << mobile << "logged in successfully";
    return true;
}
