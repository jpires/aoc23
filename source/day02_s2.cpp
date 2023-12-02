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

int game_power(std::string_view str)
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

    int max_red = 0;
    int max_green = 0;
    int max_blue = 0;

    for (auto p : pair)
    {
        if (p.color == "red")
        {
            if(p.n > max_red)
            {
                max_red = p.n;
                continue;
            }
        }
        if (p.color == "green")
        {
            if(p.n > max_green)
            {
                max_green = p.n;
                continue;
            }
        }
        if (p.color == "blue")
        {
            if(p.n > max_blue)
            {
                max_blue = p.n;
                continue;
            }
        }
    }

    return max_red * max_green * max_blue;
}

int main()
{
    auto lines = split(input, '\n');

    auto sum = 0;
    for (auto l : lines)
    {
        sum += game_power(l);
    }

    fmt::print("Sum: {}\n", sum);

    return 0;
}