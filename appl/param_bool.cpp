/**
 * @file param_bool.cpp
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

/// Parsing flag
template<> bool param<bool>::parse_val(int argc, strbuf_t argv[])
{
    bool result = (argc >= 1);

    if (result)
    {
        value = (argc < 2 || strcmp("n", argv[1]));
    }

    return result;
}

/// Printing value of bool
template<> int param<bool>::print_val(strbuf_t _end)
{
    return printf("%s", value ? "true" : "false");
}
