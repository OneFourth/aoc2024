#pragma once

import std;

struct Report {
    std::vector<int> values;
};

struct Day02 {
    static constexpr std::uint8_t number = 2;
    void input(const std::string_view input);
    void part1() const;
    void part2() const;

    std::vector<Report> reports;
};
