import std;

#include "day09.hpp"
#include "log.hpp"

using Filesystem = std::vector<std::optional<std::size_t>>;

void Day09::input(const std::string_view input) {
    bool is_file = false;
    std::size_t i = 0;

    for (const auto c : input) {
        if (!std::isdigit(c)) {
            break;
        }

        const std::uint8_t digit = c - '0';
        is_file = !is_file;

        this->blocks.push_back(Block{
            .length = digit,
            .id = is_file ? std::optional{i} : std::nullopt,
        });

        if (is_file) {
            i++;
        }
    }
}

static void print_filesystem(Filesystem& filesystem) {
    std::string s;
    for (auto b: filesystem) {
        if (b) {
            s.append(1, '0' + *b);
        } else {
            s.append(1, '.');
        }
    }
    info("{}", s);
};

static Filesystem to_filesystem(const std::vector<Block>& blocks) {
    Filesystem filesystem;
    auto total_size = 0;
    for (const auto& b : blocks) {
        total_size += b.length;
    }
    filesystem.reserve(total_size);

    for (const auto& b : blocks) {
        for (auto i = 0; i < b.length; i++) {
            filesystem.push_back(b.id);
        }
    }

    return filesystem;
}

std::int64_t checksum(const Filesystem& filesystem) {
    std::int64_t total = 0;
    for (auto i = 0; i < filesystem.size(); i++) {
        total += i * filesystem[i].value_or(0);
    }

    return total;
}

void Day09::part1() const {
    auto filesystem = to_filesystem(this->blocks);
    auto l = filesystem.begin();
    auto r = filesystem.rbegin();

    while (l != r.base()) {
        if (l->has_value()) {
            l++;
            continue;
        }
        if (!r->has_value()) {
            r++;
            continue;
        }

        std::swap(*l, *r);
    }

    info("Part 1: {}", checksum(filesystem));
}

void Day09::part2() const {
    auto filesystem = to_filesystem(this->blocks);

    auto r = filesystem.rbegin();

    while (r != filesystem.rend()) {
        if (!r->has_value()) {
            r++;
            continue;
        } else {
            const auto r_end = r;
            while (r != filesystem.rend() && r->has_value() && *r == *r_end) {
                r++;
            }
            const auto r_size = r_end.base() - r.base();

            auto l = filesystem.begin();
            while (l != r.base()) {
                if (l->has_value()) {
                    l++;
                    continue;
                } else {
                    const auto l_begin = l;
                    while (!l->has_value()) {
                        l++;
                    }
                    const auto l_size = l - l_begin;

                    if (l_size >= r_size) {
                        std::ranges::swap_ranges(l_begin, l_begin + r_size, r.base(), r_end.base());
                        break;
                    }
                }
            }
        }
    }

    info("Part 2: {}", checksum(filesystem));
}
