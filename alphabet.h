#pragma once
#include <QString>

class Alphabet {
public:
    static const QString& english();
    static const QString& russian();

    static QString normalize(const QString& s, const QString& alpha);
    static int indexOf(QChar c, const QString& alpha);
};