#pragma once
#include <QString>
#include <array>

class Playfair {
public:
    explicit Playfair(const QString& key1, const QString& key2, const QString& key3, const QString& key4);

    QString encrypt(const QString& plaintext);
    QString decrypt(const QString& ciphertext);

private:
    using Table = std::array<std::array<QChar, 5>, 5>;

    static void fillTable(Table& t, const QString& key);
    static const QString& alphabet();
    Table t1, t2, t3, t4;
};