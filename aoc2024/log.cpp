#include "log.hpp"

std::string date() {
    auto now = std::chrono::system_clock::now();

    return std::format(
        "{:%Y/%m/%d %H:%M:%S}",
        std::chrono::round<std::chrono::seconds>(now)
    );
}
