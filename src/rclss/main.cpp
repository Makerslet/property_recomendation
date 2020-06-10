#include "property_description.h"

#include <iostream>
#include <experimental/filesystem>
#include <stdexcept>
#include <unordered_map>

namespace filesystem = std::experimental::filesystem;

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cout << "Wrong number of arguments" << std::endl;
        return 1;
    }

    std::string name = argv[1];
    std::string model_name = name + ".dat.model";
    std::string data_name = name + ".dat.data";

    filesystem::path model_path = filesystem::current_path().append(model_name);
    filesystem::path data_path = filesystem::current_path().append(data_name);

    if(!filesystem::exists(model_path))
    {
        std::cout << "File with model doesnt't exists" << std::endl;
        return 1;
    }

    if(!filesystem::exists(data_path))
    {
        std::cout << "File with data doesn't exists" << std::endl;
        return 1;
    }

    dlib::kcentroid<property_kernel> model_k_centroids(property_kernel(), 0.01, 8);
    dlib::kkmeans<property_kernel> model(model_k_centroids);
    dlib::deserialize(model_name) >> model;

    property_entries entries;
    dlib::deserialize(data_name) >> entries;

    if(entries.empty())
    {
        std::cout << "Data pack is empty, can't continue" << std::endl;
        return 1;
    }

    auto check_is_invalid = filter();
    auto convertor = string_to_property_lambda();

    std::unordered_map<int, std::vector<property_entry>> clusters;
    for (const property_entry& entry: entries)
        clusters[model(entry)].emplace_back(entry);

    property_entry input_entry;
    std::string input;

    std::cout << "Please type your parameters" << std::endl;
    while(std::getline(std::cin, input))
    {
        if(check_is_invalid(input))
        {
            std::cout << "Passed string is not valid" << std::endl;
            continue;
        }

        input_entry = convertor(input);
        auto& cluster_entries = clusters[model(input_entry)];

        auto predicate = [input_entry](const property_entry& lhs, const property_entry& rhs) {
            return distance(input_entry, lhs) < distance(input_entry, rhs);
        };
        std::sort(cluster_entries.begin(), cluster_entries.end(), predicate);

        std::cout << "Results sorted by location:" << std::endl;
        for (const auto& entry : cluster_entries)
            std::cout << to_string(entry) << std::endl;

        std::cout << std::endl;
    }
}
