#pragma once

import std;

struct Day04 {
    static constexpr std::uint8_t number = 4;
    void input(const std::string_view input);
    void part1() const;
    void part2() const;

    std::string data;
    std::size_t width;
    std::size_t height;

    auto get_span() const {
        return std::mdspan(this->data.data(), this->width, this->height);
    };

    template<typename... Args>
    bool check_line(const std::string_view word, Args&&... position) const {
        auto span = this->get_span();

        if (((position.first >= span.extent(0) || position.second >= span.extent(1)) || ...)) {
            return false;
        }

        const auto test = std::array<char, sizeof...(position)> {
            { span[position.first, position.second]... }
        };

        const auto comp = std::string_view(test.data(), test.size());

        return comp == word;
    };
};
