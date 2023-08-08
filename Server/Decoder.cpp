#include "Decoder.h"

std::string Decoder::multiplyString(const char* str, int n = CONFIG::ENCODE_TIMES)
{
    std::string result;
    for(size_t i = 0; i != n; ++i) 
    {
        result += str;
    }
    return result;
}

void Decoder::decode(char* string_in, int n = CONFIG::ENCODE_TIMES)
{
    const int len = (int) strlen(string_in);
    const int word_len = len / n;
    const int size_symb = 8;
    const int bits_len = word_len * size_symb;
    std::vector<int> bits(bits_len);
    for(size_t i = 0; i != len; ++i) {
        char curr = string_in[i];
        for(int j = 0; j != size_symb; ++j) {
            bits[i % word_len * size_symb + j] += (curr >> (size_symb - 1 - j)) & 1;
        }
    }
    std::string res;
    for(size_t i = 0; i != word_len; ++i) {
        char c = 0;
        for(size_t j = 0; j != size_symb; ++j) {
            int bit = (int) std::round((double) bits[i * 8 + j]);
            c += bit << (size_symb - 1 - j);
        }
        res += c;
        c = 0;
    }
}
