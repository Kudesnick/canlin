/**
 * @file param_cmd_can.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <cstring>
#include <cstdio>
#include "param.h"

enum class can_litera: char
{
    can_a = 'A',
    can_b = 'B',
    can_c = 'C'
};

class can_iface_cpp: public param_cmd<can_litera>
{
private:
    can_litera name;
public:
    can_iface_cpp(const can_litera name):
        param_cmd<can_litera>(this->name, "CAN"),
        name(name)
    {};
} can_iface[] = {{can_litera::can_a}, {can_litera::can_b}, {can_litera::can_c}};

/// Parsing of parameter.
template<> bool param<can_litera>::parse_val(int argc, strbuf_t argv[])
{
    bool result = false;

    if (argc >= 1 && strlen(argv[0]) == 1 && argv[0][0] == (char)value)
    {

    }

    return result;
}

/// Printing value.
template<> int param<can_litera>::print_val(strbuf_t _end)
{
    int result = 0;

    return result;
}
