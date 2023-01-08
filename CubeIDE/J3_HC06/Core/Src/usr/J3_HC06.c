/*
 * J3_HC06.c
 *
 *  Created on: Dec 3, 2022
 *      Author: Nelson Lima
 */

#include <usr/J3_HC06.h>
#include <string.h>
#include <stdlib.h>

#define J3_HC06_DELAY 1100 // Espera maxima da resposta.
#define BUFFER_TX_MAX 40
#define BUFFER_RX_MAX 40

void j3_hc06_tx(THC06* _hc06)
{
  HAL_UART_Transmit(_hc06->uart, (uint8_t *)_hc06->bufferTx, _hc06->bufferSizeTx, HAL_MAX_DELAY);
}

void j3_hc06_rx(THC06* _hc06)
{
  HAL_UART_Receive(_hc06->uart,_hc06->bufferRx,_hc06->bufferSizeRx, J3_HC06_DELAY);
}

uint32_t j3_hc06_getBoudRateInt(boudrate_t _baudRate)
{
  switch(_baudRate)
  {
    case br1200:
      return 1200;
    case br2400:
      return 2400;
    case br4800:
      return 4800;
    case br9600:
      return 9600;
    case br19200:
      return 19200;
    case br38400:
      return 38400;
    case br57600:
      return 57600;
    case br115200:
      return 115200;
    case br230400:
      return 230400;
    case br460800:
      return 460800;
    case br921600:
      return 921600;
    case br1382400:
      return 1382400;

    default:
      return 115200;
  }
}

THC06* J3_HC06_new(UART_HandleTypeDef* _uart, char* _nome)
{
  THC06* auxHC06;

  auxHC06 = malloc(sizeof(THC06));
  auxHC06->uart = _uart;
  auxHC06->nome = malloc(strlen(_nome));
  strcpy(auxHC06->nome, _nome);
  auxHC06->boudRate = br115200;
  auxHC06->bufferSizeTx = BUFFER_TX_MAX;
  auxHC06->bufferTx = malloc(auxHC06->bufferSizeTx * sizeof(uint8_t));
  auxHC06->bufferSizeRx = BUFFER_RX_MAX;
  auxHC06->bufferRx = malloc(auxHC06->bufferSizeRx * sizeof(uint8_t));
  memset(auxHC06->bufferRx, 0x00, auxHC06->bufferSizeRx);
  auxHC06->busy = false;

  return auxHC06;
}

bool J3_HC06_statusOK(THC06* _hc06)
{
  bool auxResult = false;
  char auxCmd[4] = "AT";
  _hc06->bufferSizeTx = strlen(auxCmd);
  memcpy(_hc06->bufferTx, auxCmd, _hc06->bufferSizeTx);
  _hc06->bufferSizeRx = 4;
  _hc06->busy = true;
  memset(_hc06->bufferRx, 0x00, _hc06->bufferSizeRx);
  //HAL_UART_Receive_IT(_hc06->uart, _hc06->bufferRx, _hc06->bufferSizeRx);
  j3_hc06_tx(_hc06);
  j3_hc06_rx(_hc06);
  _hc06->busy = false;
  auxResult = (memcmp(_hc06->bufferRx, "OK", 2) == 0);
  return auxResult;
}

bool J3_HC06_ini(THC06* _hc06)
{
  for(uint8_t i = 0; (i < BOUND_RATE_T_COUNT); i++)
  {
      HAL_UART_DeInit(_hc06->uart);
      _hc06->uart->Init.BaudRate = j3_hc06_getBoudRateInt(_hc06->boudRate);
      HAL_UART_Init(_hc06->uart);
      if (J3_HC06_statusOK(_hc06))
      {
	  J3_HC06_setName(_hc06);

	  HAL_UART_Receive_IT(_hc06->uart, _hc06->bufferRx, _hc06->bufferSizeRx);

	  return true;
      }
      else
      {
	  _hc06->boudRate = i;
      }
  }
  return false;
}

bool J3_HC06_setName(THC06* _hc06)
{
  bool auxResult = false;
  memset(_hc06->bufferTx, 0x00, BUFFER_TX_MAX);
  strcat(_hc06->bufferTx, "AT+NAME"); // Enviar => AT+NAMEname
  strcat(_hc06->bufferTx, _hc06->nome); // Enviar => AT+NAMEname
  _hc06->bufferSizeTx = strlen(_hc06->bufferTx);
  _hc06->bufferSizeRx =  5;
  j3_hc06_tx(_hc06);
  j3_hc06_rx(_hc06);
  auxResult = (memcmp(_hc06->bufferRx, "OKname", _hc06->bufferSizeRx) == 0);
  return auxResult;
}
