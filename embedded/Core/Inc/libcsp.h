
#ifndef _LIBCSP_H_
#define _LIBCSP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <csp/csp.h>
#include <csp/csp_types.h>
#include <csp/interfaces/csp_if_can.h>
#include <csp/csp_iflist.h>
#include <csp/csp_debug.h>
#include "main.h"
#include "stm32f1xx_hal.h"

#define LOCAL_NODE_ID 10
#define SERVER_NODE_ID 20
#define SERVER_PORT 25

extern UART_HandleTypeDef huart3;

#ifdef __cplusplus
}
#endif

#endif /* _LIBCSP_H_ */
