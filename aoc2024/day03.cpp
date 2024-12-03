import std;

#include "day03.hpp"
#include "log.hpp"
#include "convert.h"

void Day03::input(const std::string_view input) {
    this->raw_instructions = input;
}

void Day03::part1() const {
    std::regex r("mul\\((\\d+),(\\d+)\\)");
    auto it = std::sregex_iterator(this->raw_instructions.begin(), this->raw_instructions.end(), r);
    auto convert_match = [&](const int index) {
         return convert(std::string_view((*it)[index].first, (*it)[index].second));
    };

    auto total = 0;

    for (; it != std::sregex_iterator(); it++) {
        total += convert_match(1) * convert_match(2);
    }

    info("Part 1: {}", total);
}

void Day03::part2() const {
    std::regex r("mul\\((\\d+),(\\d+)\\)|do\\(\\)|don't\\(\\)");
    auto it = std::sregex_iterator(this->raw_instructions.begin(), this->raw_instructions.end(), r);
    auto view = [&](const int index) {
         return std::string_view((*it)[index].first, (*it)[index].second);
    };

    auto total = 0;
    bool enabled = true;

    for (; it != std::sregex_iterator(); it++) {
        const auto full_string = view(0);
        if (full_string == "do()") {
            enabled = true;
        } else if (full_string == "don't()") {
            enabled = false;
        } else if (enabled) {
            total += convert(view(1)) * convert(view(2));
        }
    }

    info("Part 2: {}", total);
}
