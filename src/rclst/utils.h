#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

std::vector<std::string> split(const std::string& str, char delimeter)
{
    std::vector<std::string> result;

    if(str.empty())
        return result;

    std::string::size_type start_pos = 0;
    std::string::size_type stop_pos = str.find_first_of(delimeter);

    while(stop_pos != std::string::npos)
    {
        result.emplace_back(str.substr(start_pos, stop_pos - start_pos));

        start_pos = stop_pos + 1;
        stop_pos = str.find_first_of(delimeter, start_pos);
    }

    if(start_pos < str.size())
        result.emplace_back(str.substr(start_pos));

    return result;
}

#endif // UTILS_H
