
#pragma once

#include "param.h"

/// environment
struct cmd_test
{
    uint32_t param; ///< test uint32_t parameter
    bool flag; ///< test boolean flag
};

/// Object of command
extern param<cmd_test> param_cmd_test;
