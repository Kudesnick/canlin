/*
 * console.h
 *
 *  Created on: Oct 13, 2021
 *      Author: kudes
 */

#ifndef APPL_CONSOLE_H_
#define APPL_CONSOLE_H_

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif

extern void console_init(void);
extern void console_insert_data(uint8_t* Buf, uint32_t *Len);
extern bool console_routine(void);

#ifdef __cplusplus
}
#endif

#endif /* APPL_CONSOLE_H_ */
