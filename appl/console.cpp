/*
 * console.cpp
 *
 *  Created on: Oct 12, 2021
 *      Author: kudesnick
 */

#include "console.h"

#include <cstring>
#include <cstdio>

#include "microrl.h"

/// Тип длины строки
typedef uint8_t strsize_t;

/// Тип строкового буфера
typedef char *const strbuf_t;

/**
 * Парсинг командной строки
 */
template<typename T>
class param
{
private:
    /// Имя параметра
    const strbuf_t name;
public:
    /// Значение параметра
    /// Ссылочное значение дает возможность использовать поля внешних структур
    T &value;

    /// Конструктор
    param(T &_value, const strbuf_t _name) :
        name(_name), value(_value)
    {
    }

    /// Парсинг параметра (зависит от типа параметра)
    bool parse_val(int argc, const char *const argv[]);
    /// Вывести значение параметра (зависит от типа)
    int print_val();

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
    int print()
    {
        auto result = printf("%s ", name);

        if (result >= 0)
        {
            result += print_val();
        }

        return result;
    }
};

/// Парсинг десятичного или hex числа
template<>
bool param<uint32_t>::parse_val(int argc, const char *const argv[])
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

template<>
int param<uint32_t>::print_val()
{
    return printf("%lu", value);
}

uint32_t test_param_val;
param<uint32_t> test_param = param<uint32_t>(test_param_val, strbuf_t("param"));

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

        return 0;
    }

    bool routine()
    {
        fread(buf, 1, sizeof(buf), stdin);

        for (size_t i = 0; i < sizeof(buf); i++)
        {
            microrl_insert_char(&microrl_hndl, buf[i]);
        }

        return strlen(buf) > 0;
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
