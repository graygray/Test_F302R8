#include "global.h"

// global vars
int testCounter = 0;
// bool testBool = false;
int testInt = 0;
int testCase = 0;


#ifdef __GNUC__
int __io_putchar(int ch)
{
    HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xffff);
    return ch;
}
#else
int fputc(int ch, FILE *stream)
{
    HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xffff);
    return ch;
}
#endif


void printInfo()
{
    xlog("%s:%d, ========================== \n\r", __func__, __LINE__);

    if (testCase == 0){
        xlog("%s:%d, SystemCoreClock:%ld \n\r", __func__, __LINE__, SystemCoreClock);

    } else if (testCase == 2) {
        testCounter +=1;
    } else if (testCase == 1) {
        testInt +=1;
    }

}

void setUserLED(LEDState state)
{
    #if defined(F302R8)
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, (state == LED_On) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    #endif // F302R8

    #if defined(G431RB)
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, (state == LED_On) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    #endif // G431RB
    
}
void toggleUserLED()
{
    #if defined(F302R8)
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13);
    #endif // F302R8

    #if defined(G431RB)
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
    #endif // G431RB
}

#if defined(MCSDK)

char *printMotorState(MCI_State_t state)
{
    switch (state)
    {
    case ICLWAIT:
        return toString(ICLWAIT);
    case IDLE:
        return toString(IDLE);
    case ALIGNMENT:
        return toString(ALIGNMENT);
    case CHARGE_BOOT_CAP:
        return toString(CHARGE_BOOT_CAP);
    case OFFSET_CALIB:
        return toString(OFFSET_CALIB);
    case START:
        return toString(START);
    case SWITCH_OVER:
        return toString(START);
    case RUN:
        return toString(RUN);
    case STOP:
        return toString(STOP);
    case FAULT_NOW:
        return toString(FAULT_NOW);
    case FAULT_OVER:
        return toString(FAULT_OVER);
    case WAIT_STOP_MOTOR:
        return toString(WAIT_STOP_MOTOR);
    default:
        break;
    }

    return "N/A";
}

void printMotorError(uint16_t errors)
{
    if (errors == MC_NO_ERROR)
    {
        xlog("%s:%d, MC_NO_ERROR \n\r", __func__, __LINE__);
        return;
    }

    char s[128] = "";
    if (errors & MC_DURATION)
    {
        strcat(s, " # ");
        strcat(s, toString(MC_DURATION));
        // xlog("%s:%d, MC_DURATION \n\r", __func__, __LINE__);
    }
    if (errors & MC_OVER_VOLT)
    {
        strcat(s, " # ");
        strcat(s, toString(MC_OVER_VOLT));
        // xlog("%s:%d, MC_OVER_VOLT \n\r", __func__, __LINE__);
    }
    if (errors & MC_UNDER_VOLT)
    {
        strcat(s, " # ");
        strcat(s, toString(MC_UNDER_VOLT));
        // xlog("%s:%d, MC_UNDER_VOLT \n\r", __func__, __LINE__);
    }
    if (errors & MC_OVER_TEMP)
    {
        strcat(s, " # ");
        strcat(s, toString(MC_OVER_TEMP));
        // xlog("%s:%d, MC_OVER_TEMP \n\r", __func__, __LINE__);
    }
    if (errors & MC_START_UP)
    {
        strcat(s, " # ");
        strcat(s, toString(MC_START_UP));
        // xlog("%s:%d, MC_START_UP \n\r", __func__, __LINE__);
    }
    if (errors & MC_SPEED_FDBK)
    {
        strcat(s, " # ");
        strcat(s, toString(MC_SPEED_FDBK));
        // xlog("%s:%d, MC_SPEED_FDBK \n\r", __func__, __LINE__);
    }
    //    if (errors & MC_BREAK_IN)
    //    {
    //        strcat(s, " # ");
    //        strcat(s, toString(MC_BREAK_IN));
    //        // xlog("%s:%d, MC_BREAK_IN \n\r", __func__, __LINE__);
    //    }
    if (errors & MC_SW_ERROR)
    {
        strcat(s, " # ");
        strcat(s, toString(MC_SW_ERROR));
        // xlog("%s:%d, MC_SW_ERROR \n\r", __func__, __LINE__);
    }

    xlog("%s:%d, error occur:%s \n\r", __func__, __LINE__, s);
}

#endif // MCSDK
