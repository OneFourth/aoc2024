import std;

#include "day01.hpp"
#include "log.hpp"

int convert(std::string_view v) {
    int output{};
    std::from_chars(v.data(), v.data() + v.size(), output);
    return output;
}

void Day01::input(const std::string_view input) {
    for (const auto s : std::ranges::views::split(input, '\n')) {
        auto line = std::string_view(s);
        if (!line.empty())
        {
            for (auto split : std::ranges::views::split(line, std::string_view("   "))) {
                if (this->left.size() > this->right.size()) {
                    this->right.push_back(convert(std::string_view(split)));
                }
                else {
                    this->left.push_back(convert(std::string_view(split)));
                }
            }
        }
    }
}

void Day01::part1() const {
    auto copy_left = this->left;
    auto copy_right = this->right;

    std::ranges::sort(copy_left);
    std::ranges::sort(copy_right);

    auto total = 0;
    for (const auto [l, r] : std::ranges::views::zip(copy_left, copy_right)) {
        total += std::abs(l - r);
    }

    info("Part 1: {}", total);
}

void Day01::part2() const {
    auto total = 0;
    for (const auto l : this->left) {
        total += l * std::ranges::count(this->right, l);
    }

    info("Part 2: {}", total);
}
