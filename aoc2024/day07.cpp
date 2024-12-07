import std;

#include "day07.hpp"
#include "log.hpp"
#include "convert.h"

void Day07::input(const std::string_view input) {
    for (const auto s : std::ranges::views::split(input, std::string_view("\n"))) {
        const auto line = std::string_view(s);
        if (line.empty()) {
            continue;
        }
        Equation e;

        const auto convert_s = [](const auto v) { return convert<std::uint64_t>(std::string_view(v)); };
        auto split = std::ranges::views::split(line, std::string_view(": "));
        auto i = split.begin();
        e.result = convert_s(*i);
        e.values = std::ranges::views::split(std::string_view(*(++i)), std::string_view(" "))
            | std::ranges::views::transform(convert_s)
            | std::ranges::to<std::vector<std::uint64_t>>();

        this->equations.push_back(e);
    }
}

static bool check_equation(const Equation& e) {
    auto op_count = e.values.size() - 1;
    for (auto op_set = 0; op_set < (2 << op_count); op_set++) {
        auto running_total = e.values[0];
        for (auto i = 1; i < e.values.size(); i++) {
            if ((op_set >> (i - 1)) & 1) {
                running_total += e.values[i];
            } else {
                running_total *= e.values[i];
            }
        }

        if (running_total == e.result) {
            return true;
        }
    }
    return false;
}

void Day07::part1() const {
    std::uint64_t total = 0;
    for (const auto& equation : this->equations) {
        if (check_equation(equation)) {
            total += equation.result;
        }
    }
    info("Part 1: {}", total);
}

static bool check_equation_part2(const Equation& e) {
    auto op_count = e.values.size() - 1;
    for (auto op_set = 0; op_set < std::pow(3, op_count); op_set++) {
        std::uint64_t running_total = e.values[0];
        for (auto i = 1; i < e.values.size(); i++) {
            const auto v =
                static_cast<std::uint64_t>(static_cast<double>(op_set) / std::pow(3, i - 1));
            if (v % 3 == 0) {
                running_total += e.values[i];
            } else if (v % 3 == 1) {
                running_total *= e.values[i];
            } else {
                auto zeros = std::max(1.0, std::ceil(std::log10(e.values[i] + 0.5)));
                const auto multiply_by =
                    static_cast<std::uint64_t>(std::pow(10.0, zeros));
                running_total *= multiply_by;
                running_total += e.values[i];
            }
            if (running_total > e.result) {
                break;
            }
        }

        if (running_total == e.result) {
            return true;
        }
    }
    return false;
}

void Day07::part2() const {
    std::uint64_t total = 0;
    auto part1_count = 0;
    auto part2_count = 0;
    auto i = 0;
    for (const auto& equation : this->equations) {
        if (check_equation(equation)) {
            total += equation.result;
            part1_count++;
        } else if (check_equation_part2(equation)) {
            total += equation.result;
            part2_count++;
        }
        i++;
    }
    info("Part 2: {}", total);
}
