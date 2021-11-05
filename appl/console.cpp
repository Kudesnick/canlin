/**
 * @file console.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <param.h>
#include "console.h"

#include <cstring>
#include <cstdio>

#include "microrl.h"

// Include command's headers
#include "param_cmd_test.h"

/**
 * @brief Main class for parsing and execution command from  console input
 * @details This class is singtone
 */
class console_cpp
{
private:
    ///  Console context
    microrl_t microrl_hndl;

    /// Input buffer
    char buf[4];

    /// Default constructor
    console_cpp()
    {
        microrl_init(&this->microrl_hndl, &console_cpp::microrl_print);
        microrl_set_execute_callback(&this->microrl_hndl, &console_cpp::microrl_execute);
    }

    console_cpp(const console_cpp&) = delete; ///< Drop operator "="
    console_cpp& operator =(const console_cpp&) = delete; ///< Drop operator "="

    /**
     * @brief Callback for console output
     * 
     * @param _str - pointer to output buffer
     */
    static void microrl_print(const char *_str)
    {
        printf(_str);
    }

    /**
     * @brief Callback for consol command execute
     * 
     * @param argc - count of arguments
     * @param argv - list of arguments
     * @return int - zero or error code
     */
    static int microrl_execute(int argc, const char *const argv[])
    {
        // insert comand's parsers
        param_cmd_test_find(argc, argv);

        return 0;
    }

    /**
     * @brief routine of console input parsing
     * 
     * @return true - new symbol(s) parsed
     * @return false - no symbols to parse
     */
    bool routine()
    {
        fread(buf, 1, sizeof(buf), stdin);

        bool result = false;

        for (size_t i = 0; i < sizeof(buf); i++)
        {
            if (buf[i] != '\0')
            {
                microrl_insert_char(&microrl_hndl, buf[i]);
                result = true;
            }
        }

        return result;
    }

    friend bool console_routine(void);

public:
    /**
     * @brief instance and access to singltone object
     * 
     * @return console_cpp& - lnk to singltone object
     */
    static console_cpp& instance()
    {
        static console_cpp console;
        return console;
    }
};


extern "C"
{

bool console_routine(void)
{
    console_cpp &con = console_cpp::instance();
    return con.routine();
}

} // extern "C"
