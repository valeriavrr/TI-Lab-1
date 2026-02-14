#include "playfair.h"
#include "alphabet.h"

Playfair::Playfair(const QString& key1, const QString& key2, const QString& key3, const QString& key4) {
    fillTable(t1, key1);
    fillTable(t2, key2);
    fillTable(t3, key3);
    fillTable(t4, key4);
}

const QString& Playfair::alphabet() { return Alphabet::english(); }

void Playfair::fillTable(Table& t, const QString& key) {
    QString clean = Alphabet::normalize(key, alphabet());
    QString used;
    for (QChar ch : clean) {
        if (!used.contains(ch))
            used += ch;
    }
    for (QChar ch : alphabet()) {
        if (!used.contains(ch))
            used += ch;
    }
    int idx = 0;
    for (int i = 0; i < 25; ++i) {
        t[i / 5][i % 5] = used[idx++];
    }
}

QString Playfair::encrypt(const QString& plaintext) {
    QString str = Alphabet::normalize(plaintext, alphabet());
    if (str.size() % 2 == 1)
        str += u'X';
    QString result;
    for (int i = 0; i < str.size(); i += 2) {
        QChar a = str[i];
        QChar b = str[i + 1];
        int row1 = -1, col1 = -1, row2 = -1, col2 = -1;
        for (int row = 0; row < 5; ++row) {
            for (int col = 0; col < 5; ++col) {
                if (t2[row][col] == a) { row1 = row; col1 = col; }
                if (t4[row][col] == b) { row2 = row; col2 = col; }
            }
        }
        result += t1[row1][col2];
        result += t3[row2][col1];
    }
    return result;
}

QString Playfair::decrypt(const QString& ciphertext) {
    QString str = Alphabet::normalize(ciphertext, alphabet());
    if (str.size() % 2 != 0) return {};
    QString result;
    for (int i = 0; i < str.size(); i += 2) {
        QChar a = str[i];
        QChar b = str[i + 1];
        int row1 = -1, col1 = -1, row2 = -1, col2 = -1;
        for (int row = 0; row < 5; ++row) {
            for (int col = 0; col < 5; ++col) {
                if (t1[row][col] == a) { row1 = row; col1 = col; }
                if (t3[row][col] == b) { row2 = row; col2 = col; }
            }
        }
        result += t2[row1][col2];
        result += t4[row2][col1];
    }
    return result;
}