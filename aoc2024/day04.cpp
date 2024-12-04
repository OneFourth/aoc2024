import std;

#include "day04.hpp"
#include "log.hpp"

void Day04::input(const std::string_view input) {
    this->data = input;
    this->width = input.find("\n");
    this->height = std::ranges::count(input, '\n');

    std::erase(this->data, '\n');
}

void Day04::part1() const {
    auto span = this->get_span();

    std::size_t count = 0;

    for (auto i = 0; i != span.extent(0); i++) {
        for (auto j = 0; j != span.extent(1); j++) {
            if (span[i, j] == 'X') {
                const auto checks = std::array {
                    this->check_line(
                        "XMAS",
                        std::pair { i, j },
                        std::pair { i - 1, j },
                        std::pair { i - 2, j },
                        std::pair { i - 3, j } // up
                    ),
                    this->check_line(
                        "XMAS",
                        std::pair { i, j },
                        std::pair { i - 1, j + 1 },
                        std::pair { i - 2, j + 2 },
                        std::pair { i - 3, j + 3 } // up right
                    ),
                    this->check_line(
                        "XMAS",
                        std::pair { i, j },
                        std::pair { i, j + 1 },
                        std::pair { i, j + 2 },
                        std::pair { i, j + 3 } // right
                    ),
                    this->check_line(
                        "XMAS",
                        std::pair { i, j },
                        std::pair { i + 1, j + 1 },
                        std::pair { i + 2, j + 2 },
                        std::pair { i + 3, j + 3 } // down right
                    ),
                    this->check_line(
                        "XMAS",
                        std::pair { i, j },
                        std::pair { i + 1, j },
                        std::pair { i + 2, j },
                        std::pair { i + 3, j } // down
                    ),
                    this->check_line(
                        "XMAS",
                        std::pair { i, j },
                        std::pair { i + 1, j - 1 },
                        std::pair { i + 2, j - 2 },
                        std::pair { i + 3, j - 3 } // down left
                    ),
                    this->check_line(
                        "XMAS",
                        std::pair { i, j },
                        std::pair { i, j - 1 },
                        std::pair { i, j - 2 },
                        std::pair { i, j - 3 } // left
                    ),
                    this->check_line(
                        "XMAS",
                        std::pair { i, j },
                        std::pair { i - 1, j - 1 },
                        std::pair { i - 2, j - 2 },
                        std::pair { i - 3, j - 3 } // up left
                    ),
                };
                count += std::ranges::count(checks, true);
            }
        }
    }

    info("Part 1: {}", count);
}

void Day04::part2() const {
    auto span = this->get_span();

    std::size_t count = 0;

    for (auto i = 0; i != span.extent(0); i++) {
        for (auto j = 0; j != span.extent(1); j++) {
            if (span[i, j] == 'A') {
                auto tl_br_diagonal =
                    (this->check_line(
                         "MAS",
                         std::pair { i - 1, j - 1 },
                         std::pair { i, j },
                         std::pair { i + 1, j + 1 } // top left to bottom right
                     )
                     || this->check_line(
                         "MAS",
                         std::pair { i + 1, j + 1 },
                         std::pair { i, j },
                         std::pair { i - 1, j - 1 } // bottom right to top left
                     ));
                auto tr_bl_diagonal =
                    (this->check_line(
                         "MAS",
                         std::pair { i - 1, j + 1 },
                         std::pair { i, j },
                         std::pair { i + 1, j - 1 } // top right to bottom left
                     )
                     || this->check_line(
                         "MAS",
                         std::pair { i + 1, j - 1 },
                         std::pair { i, j },
                         std::pair { i - 1, j + 1 } // top right to bottom left
                     ));

                if (tl_br_diagonal && tr_bl_diagonal) {
                    count++;
                }
            }
        }
    }

    info("Part 2: {}", count);
}
