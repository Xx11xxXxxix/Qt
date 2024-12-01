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
    if (!AdminUser::isValidMobile(mobile)) {
        qDebug() << "Invalid mobile number";
        return false;
    }

    if (!verificationCodes.contains(mobile) || verificationCodes[mobile] != code) {
        qDebug() << "Invalid verification code";
        return false;
    }

    verificationCodes.remove(mobile);

    // 从数据库加载或创建新用户
    AdminUser user = AdminUser::loadFromDatabase(mobile);
    if (user.id.isEmpty()) {
        user = createUser(mobile);
    }

    user.loginCounts++;
    user.lastLoginTime = QDateTime::currentDateTime();
    user.saveToDatabase();

    qDebug() << "User" << mobile << "logged in successfully";
    return true;
}
