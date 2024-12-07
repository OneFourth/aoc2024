#pragma once

import std;

enum class Direction {
    Up,
    Right,
    Down,
    Left,
};

using Point = std::pair<std::size_t, std::size_t>;
using PointWithDirection = std::tuple<std::size_t, std::size_t, Direction>;

struct Day06 {
    static constexpr std::uint8_t number = 6;
    void input(const std::string_view input);
    void part1() const;
    void part2() const;

    std::string tiles;
    std::size_t width;
    std::size_t height;

    auto get_span() const {
        return std::mdspan(this->tiles.data(), this->width, this->height);
    };
};
