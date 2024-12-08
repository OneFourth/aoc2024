#pragma once

import std;

using Pos = std::pair<int, int>;

struct Day08 {
    static constexpr std::uint8_t number = 8;
    void input(const std::string_view input);
    void part1() const;
    void part2() const;

    std::set<Pos> antinodes(const int extrapolation_start, const int extrapolation_count) const;
    void print_map(const std::set<Pos>& antinodes) const;

    std::size_t width;
    std::size_t height;
    std::unordered_map<char, std::vector<Pos>> antenna;
};
