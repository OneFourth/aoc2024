#pragma once

import std;

struct Equation {
    std::uint64_t result;
    std::vector<std::uint64_t> values;
};

struct Day07 {
    static constexpr std::uint8_t number = 7;
    void input(const std::string_view input);
    void part1() const;
    void part2() const;

    std::vector<Equation> equations;
};
