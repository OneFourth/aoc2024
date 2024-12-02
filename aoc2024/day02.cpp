import std;

#include "day02.hpp"
#include "log.hpp"
#include "convert.h"

enum class ReportType {
    Mixed,
    Increasing,
    Decreasing,
};

static ReportType report_type(const Report& r) {
    auto diff =
        std::ranges::views::adjacent_transform<2>(r.values, [](const auto a, const auto b) { return b - a; });

    std::optional<ReportType> type;
    for (const auto d : diff) {
        if (0 < d && d < 4 && ReportType::Increasing == type.value_or(ReportType::Increasing)) {
            type = ReportType::Increasing;
        } else if (-4 < d && d < 0 && ReportType::Decreasing == type.value_or(ReportType::Decreasing)) {
            type = ReportType::Decreasing;
        } else {
            type = ReportType::Mixed;
        }
    }

    return type.value();
}

static ReportType report_type_part2(const Report& r) {
    auto type = report_type(r);
    if (type != ReportType::Mixed) {
        return type;
    }
    else {
        for (auto i = 0; i < r.values.size(); i++) {
            auto new_report = r;
            new_report.values.erase(new_report.values.begin() + i);
            type = report_type(new_report);
            if (type != ReportType::Mixed) {
                return type;
            }
        }
    }
    return type;
}

void Day02::input(const std::string_view input) {
    for (const auto s : std::ranges::views::split(input, '\n')) {
        const auto line = std::string_view(s);
        if (!line.empty())
        {
            auto& report = this->reports.emplace_back();
            for (const auto number : std::ranges::views::split(line, ' ')) {
                report.values.push_back(convert(std::string_view(number)));
            }
        }
    }
}

void Day02::part1() const {
    const auto count = std::ranges::count_if(
        this->reports,
        [](const ReportType t) { return t != ReportType::Mixed; },
        &report_type
    );

    info("Part 1: {}", count);
}

void Day02::part2() const {
    const auto count = std::ranges::count_if(
        this->reports,
        [](const ReportType t) { return t != ReportType::Mixed; },
        &report_type_part2
    );

    info("Part 2: {}", count);

}
