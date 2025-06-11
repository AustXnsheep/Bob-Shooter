//
// Created by nick on 6/7/25.
//

#include <string>
#include <random>
#include <sstream>
#include <iomanip>
#include <chrono>

#include "uuid.h"

namespace UUID {
    std::string generateSimpleUUID() {
        std::stringstream ss;

        auto now = std::chrono::system_clock::now().time_since_epoch();
        const long millis = std::chrono::duration_cast<std::chrono::milliseconds>(now).count();

        ss << std::hex << millis;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 15);
        for (int i = 0; i < 8; ++i) {
            ss << std::hex << dis(gen);
        }

        return ss.str();
    }
} // UUID