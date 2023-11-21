#pragma once

#include <stdio.h>
#include <string.h>
#include <main.h>

// define for different project
// #define G431RB
#define F302R8
// #define MCSDK

#ifdef G431RB

#define ENABLE_M_ALL            // enable two motor simultaneously
// #define ENABLE_M1_ONLY
// #define ENABLE_M2_ONLY

#if defined(ENABLE_M_ALL)
  #define ENABLE_M1_TASKS
  #define ENABLE_M2_TASKS
  // #define ENABLE_M2_SAFETY
#endif // ENABLE_M_ALL

#if defined(ENABLE_M1_ONLY)
  #define ENABLE_M1_TASKS
#endif // ENABLE_M1_ONLY

#if defined(ENABLE_M2_ONLY)
  #define ENABLE_M2_TASKS
  // #define ENABLE_M2_SAFETY
#endif // ENABLE_M2_ONLY

// #define ENABLE_M2_CP_M1

#define USE_R3_1
// #define USE_R3_2

#include "stm32g4xx.h"
#include "stm32g431xx.h"
#include "stm32g4xx_hal_gpio.h"
#include "stm32g4xx_hal_uart.h"

#endif // G431RB

#ifdef F302R8

#include "stm32f3xx.h"
#include "stm32f3xx_hal_gpio.h"

#endif // F302R8

#if defined(MCSDK)

#include "mc_type.h"
#include "mc_interface.h"
#include "motorcontrol.h"
#include "mc_config.h"

extern uint8_t mcp_motorID;

#endif // MCSDK


#define DEBUGX

#ifndef DEBUGX
  #define xlog
#else
  #define xlog printf
#endif

#define toString(x) #x

typedef enum
{
  LED_Off  = 0U,
  LED_On
} LEDState;

extern int testCase;
extern int testInt;
extern int testCounter;

extern UART_HandleTypeDef huart2;

void printInfo(void);
void setUserLED(LEDState);
void toggleUserLED(void);

#if defined(MCSDK)

char* printMotorState(MCI_State_t);
void printMotorError(uint16_t);

#endif // MCSDK



