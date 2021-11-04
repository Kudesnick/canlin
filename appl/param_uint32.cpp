/**
 * @file param_uint32.cpp
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

/// Parsing decimal or hex parameter
template<> bool param<uint32_t>::parse_val(int argc, const char *const argv[])
{
    bool result = false;
    if (argc < 2) return result;

    const char *ptr = argv[1];
    uint32_t val = 0;
    const uint8_t base = (strstr(ptr, "0x") == ptr) ? 16 : 10;
    if (base == 16) ptr += 2;

    for (; *ptr != '\0'; ptr++)
    {
        result = true;
        uint8_t tmp;

        if (*ptr >= '0' && *ptr <= '9') tmp = *ptr - '0';
        else if (base == 16 && *ptr >= 'A' && *ptr <= 'F') tmp = *ptr + 10 - 'A';
        else if (base == 16 && *ptr >= 'a' && *ptr <= 'f') tmp = *ptr + 10 - 'a';
        else
        {
            result = false;
            break;
        }

        val *= base;
        val += tmp;
    }

    if (result) value = val;

    return result;
}

/// Printing value of uint32_t
template<> int param<uint32_t>::print_val(const strbuf_t _end)
{
    return printf("%lu", value);
}
