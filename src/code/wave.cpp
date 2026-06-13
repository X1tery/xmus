#include <wave.hpp>
#include <cmath>
#include <functional>
#include <unordered_map>

extern const std::unordered_map<std::string, std::function<double(double)>> wave::map{
    {"sin", wave::sin},
    {"tri", wave::tri},
    {"sqr", wave::sqr}
};

double wave::sin(double n) {
    const double nr{std::modf(n, &n)};
    return std::sin(2 * M_PI * nr);
}

double wave::tri(double n) {
    const double nr{std::modf(n, &n)};
    if (nr < 0.25)
        return 4 * nr;    
    else if (nr < 0.75)
        return 4 * (0.5 - nr);
    else
        return 4 * (nr - 1);
}

double wave::sqr(double n) {
    const double nr{std::modf(n, &n)};
    if (nr < 0.5)
        return 1.0;
    else
        return -1.0;
}