/*
 * J3_HC06.h
 *
 *  Created on: Dec 3, 2022
 *      Author: Nelson Lima
 */

#ifndef INC_USR_J3_HC06_H_
#define INC_USR_J3_HC06_H_

#include "usart.h"
#include "stdbool.h"

enum boudRate {br1200, br2400, br4800, br9600, br19200, br38400, br57600, br115200, br230400, br460800, br921600, br1382400 };
typedef enum boudRate boudrate_t;
#define BOUND_RATE_T_COUNT 12 /* Somente para contar a quantidades de boundRate_t */

struct THC06{
  UART_HandleTypeDef* uart;
  char* nome;
  boudrate_t boudRate;
  uint8_t* bufferTx;
  uint16_t bufferSizeTx;
  uint8_t* bufferRx;
  uint16_t bufferSizeRx;
  bool busy;
};
typedef struct THC06 THC06;


THC06* J3_HC06_new(UART_HandleTypeDef* _uart, char* _nome); /* Retorna um ponteiro para um THC06 */
bool J3_HC06_ini(THC06* _hc06);
bool J3_HC06_statusOK(THC06* _hc06);
bool J3_HC06_setName(THC06* _hc06);

#endif /* INC_USR_J3_HC06_H_ */
