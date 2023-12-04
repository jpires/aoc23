//
// Created by Joao on 03/12/2023.
//
#include "day03_input.h"
#include <algorithm>
#include <charconv>
#include <experimental/mdspan>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <ranges>
#include <string>
#include <unordered_map>
#include <vector>

bool is_symbol(char c)
{
    return c == '+' ||  c == '/' || c == '$' || c == '#' || c == '@' || c == '&' || c == '%' || c == '-' ||c == '*' || c == '=';
}

void print_unique_chars(std::string_view str)
{
    std::unordered_map<char, char> map;

    for(auto c : str)
    {
        if(map.contains(c) == false)
        {
            map.insert({c, c});
        }
    }

    fmt::print("{}\n", map);
}


std::vector<std::tuple<int, int>> get_numbers_locations(auto data)
{
    std::vector<std::tuple<int, int>> number_locations;
    for (std::size_t i = 0; i != data.extent(0); i++)
    {
        for (std::size_t j = 0; j != data.extent(1); j++)
        {
            if(is_symbol(data[i,j]))
            {
                // Need to check the 8 adjacent blocks
                //fmt::print("{}x{} - > {}\n", i, j, data[i,j]);

                if(isdigit(data[i-1, j-1]))
                {
                    number_locations.emplace_back(i-1, j-1);
                }
                if(isdigit(data[i-1, j]))
                {
                    number_locations.emplace_back(i-1, j);
                }
                if(isdigit(data[i-1, j+1]))
                {
                    number_locations.emplace_back(i-1, j+1);
                }

                if(isdigit(data[i, j-1]))
                {
                    number_locations.emplace_back(i, j-1);
                }
                if(isdigit(data[i, j+1]))
                {
                    number_locations.emplace_back(i, j+1);
                }

                if(isdigit(data[i+1, j-1]))
                {
                    number_locations.emplace_back(i+1, j-1);
                }
                if(isdigit(data[i+1, j]))
                {
                    number_locations.emplace_back(i+1, j);
                }
                if(isdigit(data[i+1, j+1]))
                {
                    number_locations.emplace_back(i+1, j+1);
                }
            }
        }
    }

    return number_locations;
}

std::vector<std::tuple<int, int>> remove_duplicates(const std::vector<std::tuple<int, int>> &in)
{
    std::vector<std::tuple<int, int>> deduplicated_number_locations;
    for(auto i = in.cbegin(); i < in.cend()-1; i++)
    {
        auto [x1, y1] = *i;
        auto [x2, y2] = *(i + 1);

        if(x1 == x2)
        {
            if (std::abs(y1 - y2) > 1)
            {
                deduplicated_number_locations.push_back(*(i));
            }
        }
        else
        {
            deduplicated_number_locations.push_back(*(i));
        }
    }

    auto [x1, y1] = *(in.end() - 1);
    auto [x2, y2] = *(in.end() - 2);

    if(x1 == x2)
    {
        if (std::abs(y1 - y2) <= 1)
        {
            deduplicated_number_locations.push_back(*(in.end() - 1));
        }
    }
    else
    {
        deduplicated_number_locations.push_back(*(in.end() - 1));
    }


    return deduplicated_number_locations;
}


int get_full_number(auto data, std::size_t x, std::size_t y)
{
    //fmt::print("x: {}, y: {} ", x, y);
    // find begining of the number
    std::size_t i = 0;
    while(true)
    {
        //fmt::print("data[{},{}] -> {}", x, y-i, data[x, y-i]);
        if(isdigit(data[x, y-i]) == false)
        {
            break;
        }

        i++;
    }
    i--;

    std::string n;

    std::size_t j = 0;
    while(true)
    {
        //fmt::print("data[{},{}] -> {}", x, y-i + j, data[x, y - i + j]);
        if(isdigit(data[x, y - i + j]) == false)
        {
            break;
        }
        n += data[x, y - i + j];
        j++;
    }

    int value = 0;
    std::from_chars(n.data(), n.data() + n.size(), value, 10);
    //fmt::print("Get_full_number: {}\n", n);
    return value;
}

int main()
{
    auto input_str = std::string{input};
    std::remove(input_str.begin(), input_str.end(), '\n');

    print_unique_chars(input_str);

    std::experimental::mdspan data{input_str.data(), 140, 140};

    std::vector<std::tuple<int, int>> number_locations = get_numbers_locations(data);

    std::vector<std::tuple<int, int>> deduplicated_number_locations = remove_duplicates(number_locations);

    std::vector<int> duplicated_numbers;
    // get the full numbers
    for(auto l : deduplicated_number_locations)
    {
        auto [x, y] = l;

        int number = get_full_number(data, x, y);
        duplicated_numbers.push_back(number);
    }

    //first answer wrong Sum 553208. Too low
    //second answer wrong Sum 868447. Too high
    //third answer wrong Sum 555071. Too low
    //fourth answer CORRECT Sum 556057.
    fmt::print("Sum {}\n", std::accumulate(duplicated_numbers.begin(), duplicated_numbers.end(), 0));
}