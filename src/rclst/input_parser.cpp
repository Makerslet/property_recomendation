#include "input_parser.h"
#include <stdexcept>

input_parser::input_parser(int argc, char** argv) :
    _count(argc), _values(argv)
{}

input_result input_parser::parse()
{
    input_result result;
    pre_parse_check();
    result.num_clusters = parse_num_clusters();
    result.model_name = parse_model_name();
    return result;
}

void input_parser::pre_parse_check()
{
    if(_count != 3)
    {
        throw std::invalid_argument("error: number of clusters or modelname were not set, "
                     "please pass number of clusters and modelname");
    }
}

int input_parser::parse_num_clusters()
{
    try {
        int num_clusters;
        std::string num_clusters_str(_values[1]);
        num_clusters = std::stoi(num_clusters_str);

        if(num_clusters < 0)
            throw std::invalid_argument("error: you can't use negative number, please use positive number");

        return  num_clusters;
    }
    catch(const std::invalid_argument& ex) {
        std::string error = std::string("error: number of clusters ");
        throw std::invalid_argument(error + ex.what());
    }
    catch(const std::out_of_range& ex) {
        std::string error = std::string("error: number of clusters ");
        throw std::invalid_argument(error + ex.what());
    }
}

std::string input_parser::parse_model_name()
{
    std::string model_name(_values[2]);
    model_name += ".dat";
    return  model_name;
}
