import std;

#include "day08.hpp"
#include "log.hpp"

void Day08::input(const std::string_view input) {
    this->width = input.find("\n");
    this->height = std::ranges::count(input, '\n');

    auto x = 0;
    auto y = 0;
    for (auto c : input) {
        switch (c) {
        case '.':
            x++;
            break;
        case '\n':
            y++;
            x = 0;
            break;
        default:
            this->antenna[c].emplace_back(x, y);
            x++;
        }
    }
}

void Day08::print_map(const std::set<Pos>& antinodes) const {
    for (auto y = 0; y < this->height; y++) {
        for (auto x = 0; x < this->width; x++) {
            char c = '.';

            const auto pos = Pos{ x, y };

            for (auto [ch, v] : this->antenna) {
                if (std::ranges::contains(v, pos)) {
                    c = ch;
                    break;
                }
            }

            if (antinodes.contains(pos)) {
                c = '#';
            }

            std::print("{}", c);
        }
        std::println();
    }
}

std::set<Pos> Day08::antinodes(const int extrapolation_start, const int extrapolation_count) const {
    std::set<Pos> unique_positions;

    const auto in_grid = [&](const auto x, const auto y) {
        return x >= 0 && y >= 0 && x < this->width && y < this->height;
    };

    for (const auto [_, v] : this->antenna) {
        for (auto i = 0; i < v.size() - 1; i++) {
            for (auto j = i + 1; j < v.size(); j++) {
                const auto [x_a, y_a] = v[i];
                const auto [x_b, y_b] = v[j];

                for (auto k = extrapolation_start; k <= extrapolation_count; k++) {
                    const auto c_x = x_a - (k * (x_b - x_a));
                    const auto c_y = y_a - (k * (y_b - y_a));
                    const auto d_x = x_b - (k * (x_a - x_b));
                    const auto d_y = y_b - (k * (y_a - y_b));
                    if (in_grid(c_x, c_y)) {
                        unique_positions.emplace(c_x, c_y);
                    }
                    if (in_grid(d_x, d_y)) {
                        unique_positions.emplace(d_x, d_y);
                    }
                }
            }
        }
    }

    return unique_positions;
}

void Day08::part1() const {
    info("Part 1: {}", antinodes(1, 1).size());
}

void Day08::part2() const {
    info("Part 2: {}", antinodes(0, this->width).size());
}
