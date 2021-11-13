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
#include <map>
#include "param.h"
#include "main.h"

enum class can_litera: char
{
    A,
    B,
    C,
};

class can_iface_cpp: public param_cmd<can_litera>
{
private:
   FDCAN_HandleTypeDef &hfdcan;

   param<uint32_t> baud_head = {"sett", 0};
   param<uint32_t> baud_data = {"fd", 0};

public:
    can_iface_cpp(can_litera value, FDCAN_HandleTypeDef hfdcan):
        param_cmd<can_litera>("CAN", value),
        hfdcan(hfdcan)
    {};

    bool find(int argc, strbuf_t argv[]);

} can_iface[] =
{
    {can_litera::A, hfdcan1},
    {can_litera::B, hfdcan2},
    {can_litera::C, hfdcan3},
};

/// Parsing of parameter.
template<> bool param<can_litera>::find(int argc, strbuf_t argv[])
{
    return (can_iface_cpp *)this->find(argc, argv);
}

bool can_iface_cpp::find(int argc, strbuf_t argv[])
{
    bool result = false;

    const char str[] = {(char)value + 'A', '\0'};

    if (true
        && argc >= 3
        && strcmp(argv[1], str) ==  0
        )
    {
        if (baud_head.find(argc, argv))
        {
            struct
            {
                uint32_t baud_head;
                uint32_t baud_data;
                bool is_fd;
                bool terminator;
            }sett;

            sett.baud_head = baud_head.val;

            result = true;
            if (baud_data.find(argc, argv))
            {
                sett.baud_data = baud_data.val;
                sett.is_fd = true;
            }
            else
            {
                sett.baud_data = sett.baud_head;
                sett.is_fd = false;
            }
        }
    }

    return result;
}
