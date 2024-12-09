#pragma once

import std;

struct Block {
    std::uint8_t length;
    std::optional<std::size_t> id;
};

struct Day09 {
    static constexpr std::uint8_t number = 9;
    void input(const std::string_view input);
    void part1() const;
    void part2() const;

    std::vector<Block> blocks;
};
