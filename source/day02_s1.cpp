#include "day02_input.h"
#include <algorithm>
#include <charconv>
#include <fmt/core.h>
#include <ranges>
#include <string_view>
#include <vector>

std::vector<std::string_view> split(std::string_view str, char delim)
{
    std::vector<std::string_view> vec;

    if (str.empty())
    {
        return vec;
    }

    std::string_view::size_type start = 0;
    std::string_view::size_type pos = str.find(delim, start);
    while (pos != std::string_view::npos)
    {
        vec.emplace_back(str.data() + start, pos - start);
        start = pos + 1;
        pos = str.find(delim, start);
    }

    vec.emplace_back(str.data() + start, str.size() - start);

    return vec;
}

struct pair
{
    int n;
    std::string color;
};

std::optional<int> game_power(std::string_view str)
{
    auto p = split(str, ':');
    auto game = p.at(0);
    auto dices = p.at(1);

    std::vector<std::string> numbers;
    std::vector<std::string> colors;
    for (auto a : split(dices, ';'))
    {
        for (auto f1 : split(a, ','))
        {
            for (auto f2 : split(f1, ' '))
            {
                if (f2.empty())
                {
                    continue;
                }
                fmt::print("{}\n ", f2);
                if (isdigit(f2[0]))
                {
                    numbers.emplace_back(f2);
                }
                else
                {
                    colors.emplace_back(f2);
                }
            }
        }
    }
    std::vector<pair> pair;
    for (int i = 0; i < numbers.size(); i++)
    {
        int value = 0;
        std::from_chars(numbers[i].data(), numbers[i].data() + numbers[i].size(), value, 10);
        pair.emplace_back(value, colors[i]);
    }

    for (auto p : pair)
    {
        if (p.color == "red" && p.n > 12)
        {
            return std::nullopt;
        }
        if (p.color == "green" && p.n > 13)
        {
            return std::nullopt;
        }

        if (p.color == "blue" && p.n > 14)
        {
            return std::nullopt;
        }
    }

    auto game_p = split(game, ' ');
    int value = 0;
    std::from_chars(game_p[1].data(), game_p[1].data() + game_p[1].size(), value, 10);
    return value;
}

int main()
{
    auto lines = split(input, '\n');

    auto sum = 0;
    for (auto l : lines)
    {
        auto game_n = game_power(l);
        if (game_n.has_value())
        {
            sum += game_n.value();
        }
    }

    fmt::print("Sum: {}\n", sum);

    return 0;
}