#include "vigener.h"

const QString& Vigener::alphabet() {
    return Alphabet::russian();
}

Vigener::Vigener(const QString& key) {
    key_ = Alphabet::normalize(key, alphabet());
    if (key_.isEmpty()) key_ = "А";
}

QString Vigener::encrypt(const QString& plaintext) {
    QString str = Alphabet::normalize(plaintext, alphabet());
    QString result;
    int n = alphabet().size();
    for (int i = 0; i < str.size(); ++i) {
        int pi = Alphabet::indexOf(str[i], alphabet());
        int ki = Alphabet::indexOf(key_[i % key_.size()], alphabet());
        int ci = (pi + ki) % n;
        result += alphabet()[ci];
    }
    return result;
}

QString Vigener::decrypt(const QString& ciphertext) {
    QString str = Alphabet::normalize(ciphertext, alphabet());
    QString result;
    int n = alphabet().size();
    for (int i = 0; i < str.size(); ++i) {
        int ci = Alphabet::indexOf(str[i], alphabet());
        int ki = Alphabet::indexOf(key_[i % key_.size()], alphabet());
        int pi = (ci + n - ki) % n;
        result += alphabet()[pi];
    }
    return result;
}