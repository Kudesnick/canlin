/*
 * console.cpp
 *
 *  Created on: Oct 12, 2021
 *      Author: kudesnick
 */

#include "console.h"

#include <stdint.h>
#include <string.h>

#include "microrl.h"
#include "usbd_cdc_if.h"

/// Тип длины строки
typedef uint8_t strsize_t;

/// Тип строкового буфера
typedef char *const strbuf_t;

/**
 * Парсинг командной строки
 */
template <typename T>
class param
{
private:
	/// Имя параметра
	const strbuf_t name;
public:
	/// Значение параметра
	/// Ссылочное значение дает возможность использовать поля внешних структур
	T& value;

	/// Конструктор
	param(T& _value, const strbuf_t _name):
		name(_name),
		value(_value)
	{}

	/// Парсинг параметра (зависит от типа параметра)
	bool parse_val(int argc, const char *const argv[]);
	/// Вывести значение параметра (зависит от типа)
	strsize_t print_val(strbuf_t _str, const strsize_t _max_size);

	/// Ищем параметр в строке
	bool find(int argc, const char *const argv[])
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

	/// Печатаем параметр
	strsize_t print(strbuf_t _str, const strsize_t _max_size)
	{
		strsize_t result = snprintf(_str, _max_size, "%s ", name);

		if (result <= _max_size)
		{
			result += print_val(&_str[result], _max_size - result);
		}

		return result;
	}
};

/// Парсинг десятичного или hex числа
template <>
bool param<uint32_t>::parse_val(int argc, const char *const argv[])
{
	bool result = false;
	if (argc < 2) return result;

	const char* ptr = argv[1];
	uint32_t val = 0;
	const uint8_t base = (strstr(ptr, "0x") == ptr) ? 16 : 10;
	if (base == 16) ptr += 2;

	for (; *ptr != '\0'; ptr++)
	{
		result = true;
		uint8_t tmp;

		if (*ptr >= '0' && *ptr <= '9')
			tmp = *ptr - '0';
		else if (base == 16 && *ptr >= 'A' && *ptr <= 'F')
			tmp = *ptr + 10 - 'A';
		else if (base == 16 && *ptr >= 'a' && *ptr <= 'f')
			tmp = *ptr + 10 - 'a';
		else
		{
			result = false;
			break;
		}

		val *= base;
		val += tmp;
	}

	if (result)
		value = val;

	return result;
}

template<>
strsize_t param<uint32_t>::print_val(strbuf_t _str, const strsize_t _max_size)
{
	return snprintf(_str, _max_size, "%lu", value);
}

uint32_t test_param_val;
param<uint32_t> test_param = param<uint32_t>(test_param_val, strbuf_t("param"));

class console
{
private:
	microrl_t microrl_hndl;

	uint8_t *buf; uint32_t len;

	static void microrl_print(const char *_str)
	{
		while (CDC_Transmit_HS(reinterpret_cast<uint8_t*>(const_cast<char*>(_str)), strlen(_str)) != USBD_OK);
	}

	static int microrl_execute(int argc, const char *const argv[])
	{
		if (test_param.find(argc, argv))
		{
			char buf[32];
			test_param.print(buf, sizeof(buf) - 2);
			buf[strlen(buf)+1] = '\0';
			buf[strlen(buf)] = '\r';
			microrl_print(buf);
		}

		return 0;
	}

	bool routine()
	{
		if (len == 0) return false;

		for (uint32_t i = 0; i < len; i++)
		{
			microrl_insert_char(&microrl_hndl, buf[i]);
		}

		len = 0;
		return (CDC_Receive_Packet() == USBD_OK);
	}

	void init()
	{
		microrl_init(&this->microrl_hndl, &console::microrl_print);
		microrl_set_execute_callback(&this->microrl_hndl, &console::microrl_execute);
	}

	friend void console_init(void);

	friend void console_insert_data(uint8_t* Buf, uint32_t *Len);

	friend bool console_routine(void);

public:
} con;


extern "C"
{

void console_init(void)
{
	con.init();
}

void console_insert_data(uint8_t* Buf, uint32_t *Len)
{
	con.buf = Buf;
	con.len = *Len;
}

bool console_routine(void)
{
	return con.routine();
}

} // extern "C"
