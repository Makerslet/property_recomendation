#ifndef PROPERTY_DESCRIPTION_H
#define PROPERTY_DESCRIPTION_H

#include "utils.h"

#include <dlib/matrix.h>

#include <string>
#include <vector>

using property_entry = dlib::matrix<double, 7, 1>;
using property_entries = std::vector<property_entry>;

using proto_filter = std::function<bool(const std::string&)>;

proto_filter filter()
{
    return [](const std::string& str)
    {
        std::vector<std::string> tokens = split(str, ';');
        if(tokens.size() != 8)
            return true;

        for(const std::string& token: tokens)
            if(token.empty())
                return true;

        return false;
    };
}

using proto_transform = std::function<property_entry(const std::string&)>;

proto_transform string_to_property_lambda()
{
    return [](const std::string& str)
    {
        std::vector<std::string> tokens = split(str, ';');

        property_entry entry;
        for(std::size_t i = 0; i < 6; ++i)
            entry(i) = std::stod(tokens[i]);

        double target_value = 1;
        int floor = std::stoi(tokens[6]);
        int number_floors = std::stoi(tokens[7]);
        if(floor == 1 || floor == number_floors)
            target_value = 0;

        entry(6) = target_value;

        return entry;
    };
}

#endif // PROPERTY_DESCRIPTION_H
