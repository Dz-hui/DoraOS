#ifndef _DEBUG_H_
#define _DEBUG_H_
/************************************************************
  * @brief   debug.h
  * @author  jiejie
  * @github  https://github.com/jiejieTop
  * @date    2018-xx-xx
  * @version v1.0
  * @note    printf debug/err/information
  ***********************************************************/
/**
* @name Debug print
* @{
*/
#include <stdio.h>
#include <salof.h>

#define DOS_PRINT_DEBUG_ENABLE    1
#define DOS_PRINT_ERR_ENABLE      0
#define DOS_PRINT_INFO_ENABLE     0


#if DOS_PRINT_DEBUG_ENABLE
#define DOS_PRINT_DEBUG(fmt, args...)   do{(Dos_Salof("\n[DEBUG] >> "), Dos_Salof(fmt, ##args));}while(0)
#else
#define DOS_PRINT_DEBUG(fmt, ...)
#endif

#if DOS_PRINT_ERR_ENABLE
#define DOS_PRINT_ERR(fmt, ...)     do{(Dos_Salof("\n[ERR] >> "), Dos_Salof(fmt, ##args));}while(0)
#else
#define DOS_PRINT_ERR(fmt, ...)
#endif

#if DOS_PRINT_INFO_ENABLE
#define DOS_PRINT_INFO(fmt, ...)    do{(Dos_Salof("\n[INFO] >> "), Dos_Salof(fmt, ##args));}while(0)
#else
#define DOS_PRINT_INFO(fmt, ...)
#endif

/**@} */

#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
#include <stdint.h>
#endif


typedef enum {
    ASSERT_ERR = 0,
    ASSERT_SUCCESS = !ASSERT_ERR
} Assert_ErrorStatus;

typedef enum {
    FALSE = 0,
    TRUE = !FALSE
} bool;

#endif /* __DEBUG_H_ */

