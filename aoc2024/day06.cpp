import std;

#include "day06.hpp"
#include "log.hpp"

void Day06::input(const std::string_view input) {
    this->tiles = input;
    this->width = input.find("\n");
    this->height = std::ranges::count(input, '\n');

    std::erase(this->tiles, '\n');
}

static Point find_start(const auto span) {
    for (auto i = 0; i < span.extent(0); i++) {
        for (auto j = 0; j < span.extent(1); j++) {
            if (span[i, j] == '^') {
                return { i, j };
            }
        }
    }

    return {};
}

static void print_tiles(const auto span, const std::set<PointWithDirection> unique_positions) {
    for (auto i = 0; i < span.extent(0); i++) {
        for (auto j = 0; j < span.extent(1); j++) {
            auto c = span[i, j];

            auto found = std::ranges::find(unique_positions, std::pair { i, j }, [](const auto& t) {
                auto [y, x, _] = t;
                return std::pair { y, x };
            });

            if (found != unique_positions.end()) {
                c = 'X';
            }
            std::print("{}", c);
        }
        std::println();
    }
}

std::pair<bool, std::set<PointWithDirection>> get_route(const auto span) {
    auto [pos_y, pos_x] = find_start(span);
    auto direction = Direction::Up;

    std::set<PointWithDirection> unique_positions;

    bool loop = false;

    while (true) {
        auto [_, inserted] = unique_positions.emplace(pos_y, pos_x, direction);

        auto next_pos_x = pos_x;
        auto next_pos_y = pos_y;
        auto next_direction = Direction::Up;

        switch (direction) {
        case Direction::Up:
            next_pos_y--;
            next_direction = Direction::Right;
            break;
        case Direction::Right:
            next_pos_x++;
            next_direction = Direction::Down;
            break;
        case Direction::Down:
            next_pos_y++;
            next_direction = Direction::Left;
            break;
        case Direction::Left:
            next_pos_x--;
            next_direction = Direction::Up;
            break;
        }

        if (next_pos_y >= span.extent(0) || next_pos_x >= span.extent(1)) {
            break;
        }

        if (span[next_pos_y, next_pos_x] == '#') {
            direction = next_direction;
        } else {
            pos_x = next_pos_x;
            pos_y = next_pos_y;
        }

        if (unique_positions.contains({ pos_y, pos_x, direction })) {
            loop = true;
            break;
        }
    }

    return { loop, unique_positions };
}

static std::set<Point> initial_route(const auto span) {
    auto [_, unique_positions] = get_route(span);

    return std::ranges::views::transform(
               unique_positions,
               [](const auto& t) {
                   auto [y, x, _] = t;
                   return std::pair { y, x };
               }
           )
        | std::ranges::to<std::set<Point>>();
}

void Day06::part1() const {
    const auto span = this->get_span();

    info("Part 1: {}", initial_route(span).size());
}

void Day06::part2() const {
    const auto span = this->get_span();
    const auto start = find_start(span);
    auto route = initial_route(span);

    auto tested = 0;
    auto total = 0;
    for (const auto p : route) {
        if (p == start) {
            continue;
        }

        auto new_tiles = this->tiles;
        auto new_span = std::mdspan(new_tiles.data(), this->width, this->height);
        auto [x, y] = p;
        new_span[x, y] = '#';

        auto [loop, _] = get_route(new_span);

        if (loop) {
            total++;
        }
    }

    info("Part 2: {}", total);
}

