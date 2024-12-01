#pragma once

import std;

struct Day01 {
    static constexpr std::uint8_t number = 1;
    void input(const std::string_view input);
    void part1() const;
    void part2() const;

    std::vector<int> left;
    std::vector<int> right;
};
