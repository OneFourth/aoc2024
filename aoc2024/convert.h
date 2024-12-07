#pragma once

import std;

template<typename T = int>
auto convert(std::string_view v) {
    T output{};
    std::from_chars(v.data(), v.data() + v.size(), output);
    return output;
}
