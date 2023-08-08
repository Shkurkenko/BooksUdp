#pragma once

#include <string>
#include <vector>
#include <cmath>

#include "Config.h"

namespace Decoder {

    std::string multiplyString(const char* str, int n = CONFIG::ENCODE_TIMES);

    void decode(char* string_in, const int n = CONFIG::ENCODE_TIMES);

}
