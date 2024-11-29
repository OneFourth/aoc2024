import std;

#include "log.hpp"
#include "day01.hpp"
#include "day02.hpp"
#include "day03.hpp"
#include "day04.hpp"
#include "day05.hpp"
#include "day06.hpp"
#include "day07.hpp"
#include "day08.hpp"
#include "day09.hpp"
#include "day10.hpp"
#include "day11.hpp"
#include "day12.hpp"
#include "day13.hpp"
#include "day14.hpp"
#include "day15.hpp"
#include "day16.hpp"
#include "day17.hpp"
#include "day18.hpp"
#include "day19.hpp"
#include "day20.hpp"
#include "day21.hpp"
#include "day22.hpp"
#include "day23.hpp"
#include "day24.hpp"
#include "day25.hpp"

void run(auto day) {
    std::ifstream data(std::format("input/day{:02}.in", day.number));
    std::stringstream s;

    s << data.rdbuf();
    const auto input = s.str();

    day.input(input);
    day.part1();
    day.part2();
}

int main(int argc, const char* argv[]) {
    const auto args = std::span(argv, argc);

    if (args.size() != 2) {
        error("Invalid number of arguments");
        error("Expected the day number");

        return 1;
    }

    const auto day_number = std::atoi(args[1]);

    info("Day {:02}", day_number);

    switch (day_number) {
        case 1:
            run(Day01 {});
            break;
        case 2:
            run(Day02 {});
            break;
        case 3:
            run(Day03 {});
            break;
        case 4:
            run(Day04 {});
            break;
        case 5:
            run(Day05 {});
            break;
        case 6:
            run(Day06 {});
            break;
        case 7:
            run(Day07 {});
            break;
        case 8:
            run(Day08 {});
            break;
        case 9:
            run(Day09 {});
            break;
        case 10:
            run(Day10 {});
            break;
        case 11:
            run(Day11 {});
            break;
        case 12:
            run(Day12 {});
            break;
        case 13:
            run(Day13 {});
            break;
        case 14:
            run(Day14 {});
            break;
        case 15:
            run(Day15 {});
            break;
        case 16:
            run(Day16 {});
            break;
        case 17:
            run(Day17 {});
            break;
        case 18:
            run(Day18 {});
            break;
        case 19:
            run(Day19 {});
            break;
        case 20:
            run(Day20 {});
            break;
        case 21:
            run(Day21 {});
            break;
        case 22:
            run(Day22 {});
            break;
        case 23:
            run(Day23 {});
            break;
        case 24:
            run(Day24 {});
            break;
        case 25:
            run(Day25 {});
            break;
        default:
            error("Invalid day number: {}", day_number);
            return 1;
    }

    return 0;
}