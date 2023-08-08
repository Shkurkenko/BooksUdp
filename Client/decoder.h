#ifndef DECODER_H
#define DECODER_H

#include <string>

#include <QString>
#include <QByteArray>
#include <QDebug>

class Decoder
{
private:
    Decoder();

public:
    static QString decode(const std::string& string_in, int n)
    {
        const size_t len = string_in.length();
        const size_t word_len = len / n;
        const size_t size_symb = 8;
        const size_t bits_len = word_len * size_symb;
        QByteArray<int> bits(bits_len);
        for(size_t i = 0; i != len; ++i) {
            char curr = string_in[i];
            for(size_t j = 0; j != size_symb; ++j) {
                bits[i % word_len * size_symb + j] += (curr >> (size_symb - 1 - j)) & 1;
            }
        }
        std::string res;
        for(size_t i = 0; i != word_len; ++i) {
            char c = 0;
            for(size_t j = 0; j != size_symb; ++j) {
                int bit = (int)std::round((double) bits[i * 8 + j] / n);
                c += bit << (size_symb - 1 - j);
            }
            res += c;
            c = 0;
        }
        auto qstr_res = QString::fromStdString(res);
        return qstr_res;
    }

    static QByteArray encode(const QString &str, int n)
    {
        QString result;
        for(size_t i = 0; i < n; ++i) {
            result += str;
        }
        return result.data();
    }

};

#endif // DECODER_H
