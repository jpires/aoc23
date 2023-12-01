#include "day01_input.h"
#include "fmt/core.h"
#include <algorithm>
#include <charconv>
#include <string>
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

std::string convert_text_to_decimal(std::string_view str)
{
    std::string final;
    for(auto c = str.cbegin(); c != str.cend(); c++)
    {
        if(std::distance(c, str.cend()) < 3)
        {
            final += *c;
            continue;
        }

        if(c[0] == 'o' && c[1] == 'n' && c[2] == 'e')
        {
            final += '1';
            continue;
        }
        if(c[0] == 't' && c[1] == 'w' && c[2] == 'o')
        {
            final += '2';
            continue;
        }
        if(c[0] == 's' && c[1] == 'i' && c[2] == 'x')
        {
            final += '6';
            continue;
        }
        if(std::distance(c, str.cend()) < 4)
        {
            final += *c;
            continue;
        }
        if(c[0] == 'f' && c[1] == 'o' && c[2] == 'u' && c[3] == 'r')
        {
            final += '4';
            continue;
        }
        if(c[0] == 'f' && c[1] == 'i' && c[2] == 'v' && c[3] == 'e')
        {
            final += '5';
            continue;
        }
        if(c[0] == 'n' && c[1] == 'i' && c[2] == 'n' && c[3] == 'e')
        {
            final += '9';
            continue;
        }

        if(std::distance(c, str.cend()) < 5)
        {
            final += *c;
            continue;
        }
        if(c[0] == 't' && c[1] == 'h' && c[2] == 'r' && c[3] == 'e' && c[4] == 'e')
        {
            final += '3';
            continue;
        }
        if(c[0] == 's' && c[1] == 'e' && c[2] == 'v' && c[3] == 'e' && c[4] == 'n')
        {
            final += '7';
            continue;
        }
        if(c[0] == 'e' && c[1] == 'i' && c[2] == 'g' && c[3] == 'h' && c[4] == 't')
        {
            final += '8';
            continue;
        }
        final += *c;
    }
    return final;
}

char get_first_digit(std::string_view str)
{
    auto first = std::find_if(str.begin(), str.end(), ::isdigit);
    return *first;
}

char get_last_digit(std::string_view str)
{
    auto last = std::find_if(str.rbegin(), str.rend(), ::isdigit);
    return *last;
}

int main()
{
    std::string_view a = input;
    auto lines = split(a, '\n');

    int sum = 0;
    for (const auto &l : lines)
    {
        auto reformated = convert_text_to_decimal(l);

        auto first = get_first_digit(reformated);
        auto last = get_last_digit(reformated);

        auto number_str = fmt::format("{}{}", first, last);

        int value = 0;
        std::from_chars(number_str.data(), number_str.data() + number_str.size(), value, 10);

        fmt::print("{} -> {} - > {}\n",l, reformated, number_str);
        sum += value;
    }

    fmt::print("Final Sum: {}", sum);
}
