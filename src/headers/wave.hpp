#pragma once
#include <string>
#include <functional>
#include <unordered_map>

namespace wave {
    extern const std::unordered_map<std::string, std::function<double(double)>> map;
    double sin(double n);
    double tri(double n);
    double sqr(double n);
}