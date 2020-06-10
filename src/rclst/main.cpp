
#include "input_parser.h"
#include "property_description.h"

#include <iostream>
#include <vector>

#include <dlib/clustering.h>
#include <dlib/rand.h>


using strings = std::vector<std::string>;
typedef dlib::linear_kernel<property_entry> property_kernel;

int main(int argc, char** argv)
{
    input_parser parser(argc, argv);
    try {
        auto input = parser.parse();

        strings strs;
        std::string input_str;
        while(std::getline(std::cin, input_str))
            strs.push_back(input_str);

        auto iter = std::remove_if(strs.begin(), strs.end(), filter());
        strs.erase(iter, strs.end());

        property_entries entries;
        std::transform(strs.begin(), strs.end(), std::back_inserter(entries), string_to_property_lambda());

        property_entries initial_centers;
        dlib::kcentroid<property_kernel> model_k_centroids(property_kernel(), 0.01, 8);
        dlib::kkmeans<property_kernel> model(model_k_centroids);

        model.set_number_of_centers(static_cast<size_t>(input.num_clusters));
        pick_initial_centers(input.num_clusters, initial_centers, entries, model.get_kernel());
        model.train(entries, initial_centers);

        dlib::serialize(input.model_name + ".model") << model;
        dlib::serialize(input.model_name + ".data") << entries;

    } catch (const std::invalid_argument& ex) {
        std::cout << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
