import std;

#include "convert.h"

int convert(std::string_view v) {
    int output{};
    std::from_chars(v.data(), v.data() + v.size(), output);
    return output;
}
