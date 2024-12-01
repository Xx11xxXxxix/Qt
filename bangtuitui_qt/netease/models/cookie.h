#ifndef COOKIE_H
#define COOKIE_H
#include <QString>



class Cookie {
public:
    static QString getMusicU();
    static void saveMusicU(const QString& cookie);
    static QString extractMusicU(const QString& fullCookie);
private:
    static QString parseCookieFromDB();
};

#endif
