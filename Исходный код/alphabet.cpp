#include "alphabet.h"
#include <QSet>

const QString& Alphabet::english() {
    static const auto eng = QStringLiteral("ABCDEFGHIKLMNOPQRSTUVWXYZ"); // J -> I
    return eng;
}

const QString& Alphabet::russian() {
    static const auto rus = QStringLiteral("АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ");
    return rus;
}

QString Alphabet::normalize(const QString& s, const QString& alpha) {
    QString res;
    QSet<QChar> alphaSet;
    for (QChar ch : alpha) {
        alphaSet.insert(ch);
    }
    for (QChar ch : s) {
        QChar upper = ch.toUpper();
        if (upper == u'J') upper = u'I';
        if (alphaSet.contains(upper)) {
            res += upper;
        }
    }
    return res;
}

int Alphabet::indexOf(QChar c, const QString& alpha) { return alpha.indexOf(c); }