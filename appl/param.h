/**
 * @file param.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <cstring>
#include <cstdio>

/// String buffer
typedef char *const strbuf_t;

/**
 * @brief Command line parser
 * @details This template find parameter of name from command line
 * 
 * @tparam T - type of parameter
 */
template<typename T>
class param
{
private:
    const strbuf_t name; ///< Name of finded parameter

    /**
     * @brief Parsing of parameter. Depends of parameter type
     * 
     * @param argc - count of arguments
     * @param argv - argument list
     * @return true - Parameter is founded
     * @return false - parameter not founded
     */
    bool parse_val(int argc, const char *const argv[]);

    /**
     * @brief Print text of parameter value to console. Depends of parameter type
     * 
     * @return int - count of outputed characters
     */
    int print_val();

public:
    /**
     * @brief Value of parameter
     * @details If this type listed as link, can be use external register or variable
     */
    T &value;

    /**
     * @brief Construct a new param object
     * 
     * @param _value link to value
     * @param _name name of parameter
     */
    param(T &_value, const strbuf_t _name);

    /**
     * @brief Find parameter from argument list
     * 
     * @param argc - count of arguments
     * @param argv - argument list
     * @return true - Parameter is founded
     * @return false - parameter not founded
     */
    bool find(int argc, const char *const argv[]);

    /**
     * @brief Print text of parameter name and value to console
     * 
     * @return int - count of outputed characters
     */
    int print();
};


template<typename T> param<T>::param(T &_value, const strbuf_t _name) :
    name(_name), value(_value)
{
}

template<typename T> bool param<T>::find(int argc, const char *const argv[])
{
    bool result = false;

    for (auto i = 0; i < argc; i++)
    {
        if (strcmp(name, argv[i]) == 0)
        {
            result = parse_val(argc - i, &argv[i]);
            break;
        }
    }

    return result;
}

template<typename T> int param<T>::print()
{
    auto result = printf("%s ", name);

    if (result >= 0)
    {
        result += print_val();
    }

    return result;
}
