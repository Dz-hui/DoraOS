/**
 * format: printf("\033[background color; font color m string \033[0m" );
 * E.g:
 *  printf("\033[47;31mThis is a color test.\033[0m");
 *
 * Partial color code:
 * background color: 40--49
 *      40: Black
 *      41: Red
 *      42: Green
 *      43: Yellow
 *      44: Blue
 *      45: Purple
 *      46: Dark Green
 *      47: White
 * font color: 30--39
 *      30: Black
 *      31: Red
 *      32: Green
 *      33: Yellow
 *      34: Blue
 *      35: Purple
 *      36: Dark Green
 *      37: White
 */

#ifndef _LOG_H_
#define _LOG_H_

#include <dos_config.h>

#if DOS_USE_LOG

#if DOS_USE_SALOF
#include <salof.h>

#define     PRINT_LOG       Dos_Salof
#else

#if ((!DOS_USE_SALOF)&&(!PRINT_LOG))
#define         PRINT_LOG                       printf
#endif

#ifndef PRINT_LOG
#error "If the DOS_USE_LOG macro definition is turned on, you must define PRINT_LOG as the LOG output, such as #definePRINT_LOG printf"
#endif
#endif


#if DOS_LOG_TS || DOS_LOG_TAR
#include <task.h>
#endif

#define     FC_BLACK    30       /** font color */
#define     FC_RED      31
#define     FC_GREEN    32
#define     FC_YELLOW   33
#define     FC_BLUE     34
#define     FC_PURPLE   35
#define     FC_DARK     36
#define     FC_WHITE    37


#ifndef DOS_LOG_COLOR
#define DOS_LOG_COLOR  (0U)
#endif

#if DOS_LOG_COLOR
#define DOS_LOG_S(l, c) PRINT_LOG("\033\n["#c"m["#l"] >> ")
#define DOS_LOG_E   PRINT_LOG("\033[0m")
#else
#define DOS_LOG_S(l, c) Dos_Salof("\n["#l"] >> ")
#define DOS_LOG_E
#endif

#if DOS_LOG_TS && DOS_LOG_TAR
#define DOS_LOG_T   PRINT_LOG("[TS: %ld] [TAR: %s] ",dos_get_tick(), dos_get_task_name())
#elif DOS_LOG_TS
#define DOS_LOG_T   PRINT_LOG("[TS: %ld] ", dos_get_tick())
#elif DOS_LOG_TAR
#define DOS_LOG_T   PRINT_LOG("[TAR: %s] ", dos_get_task_name())
#else
#define DOS_LOG_T
#endif


#define DOS_LOG_LINE(l, c, fmt, ...)        \
    do                                      \
    {                                       \
        DOS_LOG_S(l, c);                    \
        DOS_LOG_T;                          \
        PRINT_LOG(fmt, ##__VA_ARGS__);      \
        DOS_LOG_E;                          \
    }                                       \
    while (0)


#define DOS_BASE_LEVEL  (0)

#define DOS_ASSERT_LEVEL  (DOS_BASE_LEVEL + 1)

#define DOS_ERR_LEVEL     (DOS_ASSERT_LEVEL + 1)

#define DOS_WARN_LEVEL    (DOS_ERR_LEVEL + 1)

#define DOS_INFO_LEVEL    (DOS_WARN_LEVEL + 1)

#define DOS_DEBUG_LEVEL   (DOS_INFO_LEVEL + 1)

#ifndef DOS_LOG_LEVEL
#define DOS_LOG_LEVEL   DOS_WARN_LEVEL
#endif

#if DOS_LOG_LEVEL < DOS_DEBUG_LEVEL
#define DOS_LOG_DEBUG(fmt, ...)
#else
#define DOS_LOG_DEBUG(fmt, ...)     DOS_LOG_LINE(D, 0, fmt, ##__VA_ARGS__)
#endif

#if DOS_LOG_LEVEL < DOS_INFO_LEVEL
#define DOS_LOG_INFO(fmt, ...)
#else
#define DOS_LOG_INFO(fmt, ...)      DOS_LOG_LINE(I, FC_GREEN, fmt, ##__VA_ARGS__)
#endif

#if DOS_LOG_LEVEL < DOS_WARN_LEVEL
#define DOS_LOG_WARN(fmt, ...)
#else
#define DOS_LOG_WARN(fmt, ...)      DOS_LOG_LINE(W, FC_YELLOW, fmt, ##__VA_ARGS__)
#endif

#if DOS_LOG_LEVEL < DOS_ERR_LEVEL
#define DOS_LOG_ERR(fmt, ...)
#else
#define DOS_LOG_ERR(fmt, ...)       DOS_LOG_LINE(E, FC_RED, fmt, ##__VA_ARGS__)
#endif

#if DOS_LOG_LEVEL < DOS_ASSERT_LEVEL
#define DOS_LOG_ASSERT(fmt, ...)
DOS_ASSERT(x)
#else
#define DOS_LOG_ASSERT(fmt, ...)    DOS_LOG_LINE(A, FC_RED, fmt, ##__VA_ARGS__)
#define DOS_ASSERT(x)     if((x)==0) DOS_LOG_ASSERT("%s, %d\n",__FILE__,__LINE__)
#endif

#if DOS_LOG_LEVEL < DOS_BASE_LEVEL
#define DOS_LOG(fmt, ...)
#else
#define DOS_LOG(fmt, ...)           PRINT_LOG(fmt, ##__VA_ARGS__)
#endif

#else

#define DOS_LOG_DEBUG(fmt, ...)
#define DOS_LOG_INFO(fmt, ...)
#define DOS_LOG_WARN(fmt, ...)
#define DOS_LOG_ERR(fmt, ...)
#define DOS_LOG(fmt, ...)
#define DOS_ASSERT(x)

#endif


#endif // !_LOG_H_

