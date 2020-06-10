#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H

#include <string>

struct input_result
{
    int num_clusters;
    std::string model_name;
};

class input_parser
{
public:
    input_parser(int argc, char** argv);
    input_result parse();

private:
    void pre_parse_check();
    int parse_num_clusters();
    std::string parse_model_name();

private:
    int _count;
    char** _values;
};

#endif // INPUT_PARSER_H
