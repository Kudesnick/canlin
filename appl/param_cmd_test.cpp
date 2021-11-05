/**
 * @file param_cmd_test.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <param.h>
#include <cstring>
#include <cstdio>
#include "param_cmd_test.h"


/// environment
struct cmd_test
{
    uint32_t param; ///< test uint32_t parameter
    bool flag; ///< test boolean flag
};

/// Environment
cmd_test cmd_test_val;

/// Parser of parameter "param"
param<uint32_t> test_param = param<uint32_t>(cmd_test_val.param, (strbuf_t)"param");
/// Parser of parameter "flag"
param<bool> test_bool = param<bool>(cmd_test_val.flag, (strbuf_t)"flag");

/// Object of command "test"
param<cmd_test> param_cmd_test = {cmd_test_val, (strbuf_t)"test"};

/// Parsing of parameter.
template<> bool param<cmd_test>::parse_val(int argc, strbuf_t argv[])
{
    bool result = false;

    result |= test_param.find(argc, argv);
    result |= test_bool.find(argc,argv);

    if (result) print();

    return result;
}

/// Printing value.
template<> int param<cmd_test>::print_val(strbuf_t _end)
{
    int result = 0;

    result += printf(_end);
    result += test_param.print();
    result += test_bool.print();

    return result;
}

bool param_cmd_test_find(int argc, strbuf_t argv[])
{
    return param_cmd_test.find(argc, argv);
}
