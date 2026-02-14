#pragma once
#include "alphabet.h"

class Vigener {
public:
    explicit Vigener(const QString& key);

    QString encrypt(const QString& plaintext);
    QString decrypt(const QString& ciphertext);

private:
    QString key_;
    static const QString& alphabet();
};