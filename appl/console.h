/**
 * @file console.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#ifdef __cplusplus
#include <cstdint>
#include <cstdbool>
#else
	#include <stdint.h>
	#include <stdbool.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief Callback routine of console input parsing
 * 
 * @return true - new symbol(s) parsed
 * @return false - no symbols to parse
 */
bool console_routine(void);

#ifdef __cplusplus
}
#endif
