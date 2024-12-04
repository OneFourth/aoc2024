#pragma once

import std;

std::string date();

void info(const std::string_view fmt, auto&&... args) {
    std::println("\x1b[1m\x1b[30m{}\x1b[0m [\x1b[1m\x1b[32mINFO   \x1b[0m] {}", date(), std::vformat(fmt, std::make_format_args(args...)));
}

void warn(const std::string_view fmt, auto&&... args) {
    std::println("\x1b[1m\x1b[30m{}\x1b[0m [\x1b[1m\x1b[33mWARNING\x1b[0m] {}", date(), std::vformat(fmt, std::make_format_args(args...)));
}

void error(const std::string_view fmt, auto&&... args) {
    std::println("\x1b[1m\x1b[30m{}\x1b[0m [\x1b[1m\x1b[31mERROR  \x1b[0m] {}", date(), std::vformat(fmt, std::make_format_args(args...)));
}
