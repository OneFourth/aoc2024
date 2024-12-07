import std;

#include "day05.hpp"
#include "log.hpp"
#include "convert.h"

void Day05::input(const std::string_view input) {
    const auto parts_index = input.find("\n\n");
    const auto rule_part = input.substr(0, parts_index);
    const auto update_part = input.substr(parts_index + 2);

    const auto convert_s = [](const auto v) { return convert(std::string_view(v)); };

    for (auto s: std::ranges::views::split(rule_part, std::string_view("\n"))) {
        const auto line = std::string_view(s);
        auto converted = std::ranges::views::split(line, std::string_view("|"))
            | std::ranges::views::transform(convert_s);

        auto i = converted.begin();
        auto l = *i;
        auto r = *(++i);
        this->rules.push_back(std::pair(l, r));
    }

    for (auto s : std::ranges::views::split(update_part, std::string_view("\n"))) {
        const auto line = std::string_view(s);

        if (!line.empty()) {
            this->updates.push_back(
                std::ranges::views::split(line, std::string_view(","))
                | std::ranges::views::transform(convert_s)
                | std::ranges::to<std::vector>()
            );
        }
    }
}

bool Day05::is_valid(const std::vector<int>& update) const {
    return std::ranges::all_of(this->rules, [&](const auto rule) {
        auto li = std::ranges::find(update, rule.first);
        auto ri = std::ranges::find(update, rule.second);
        return li == update.end() || ri == update.end() || li < ri;
    });
}

void Day05::part1() const {
    auto total = 0;

    for (const auto& update : this->updates) {
        if (is_valid(update)) {
            total += update[(update.size() / 2)];
        }
    }

    info("Part 1: {}", total);
}

void Day05::part2() const {
    auto copy_updates = std::ranges::views::filter(
                            this->updates,
                            [&](const auto& update) { return !is_valid(update); }
                        )
        | std::ranges::to<std::vector<std::vector<int>>>();

    auto total = 0;

    for (auto& update : copy_updates) {
        std::ranges::sort(update, [&](const auto a, const auto b) {
            const auto lr_value = std::pair{ a, b };
            const auto lr = std::ranges::find(this->rules, lr_value);
            if (lr != this->rules.end()) {
                return true;
            }
            const auto rl_value = std::pair{ b, a };
            const auto rl = std::ranges::find(this->rules, rl_value);
            if (rl != this->rules.end()) {
                return false;
            }

            return true;
            });

        total += update[(update.size() / 2)];
    }

    info("Part 2: {}", total);
}
