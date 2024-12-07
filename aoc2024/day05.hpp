#pragma once

import std;

struct Day05 {
    static constexpr std::uint8_t number = 5;
    void input(const std::string_view input);
    void part1() const;
    void part2() const;

    std::vector<std::pair<int, int>> rules;
    std::vector<std::vector<int>> updates;

    bool is_valid(const std::vector<int>& update) const;
};
