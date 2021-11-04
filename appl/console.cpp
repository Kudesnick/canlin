/*
 * console.cpp
 *
 *  Created on: Oct 12, 2021
 *      Author: kudesnick
 */

#include <param.h>
#include "console.h"

#include <cstring>
#include <cstdio>

#include "microrl.h"

uint32_t test_param_val;
bool test_bool_val;
param<uint32_t> test_param = param<uint32_t>(test_param_val, (strbuf_t)"param");
param<bool> test_bool = param<bool>(test_bool_val, (strbuf_t)"flag");

class console_cpp;
class console_cpp
{
private:
    microrl_t microrl_hndl;

    char buf[4];
    int len;

    console_cpp()
    {
        microrl_init(&this->microrl_hndl, &console_cpp::microrl_print);
        microrl_set_execute_callback(&this->microrl_hndl, &console_cpp::microrl_execute);
    }

    console_cpp(const console_cpp&) = delete;
    console_cpp& operator =(const console_cpp&) = delete;

    static void microrl_print(const char *_str)
    {
        printf(_str);
    }

    static int microrl_execute(int argc, const char *const argv[])
    {
        if (test_param.find(argc, argv))
        {
            test_param.print();
            printf("\r");
        }

        if (test_bool.find(argc, argv))
        {
            test_bool.print();
            printf("\r");
        }

        return 0;
    }

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
