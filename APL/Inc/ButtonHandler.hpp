/*******************************************************************************
* File          : ButtonHandler.hpp
*
* Description   : 
*
* Project       : 
*
* Author        : s.gilbert
*
* Created on    : 4 Apr 2020
*
*******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef BUTTONHANDLER_HPP
#define BUTTONHANDLER_HPP

/*******************************************************************************
INCLUDES
*******************************************************************************/

#include "TaskBase.hpp"
#include "DebounceTask.hpp"
#include "LinkedList.hpp"
#include "DebounceTask.hpp"
#include "PneumaticActuator.hpp"
#include "stdint.h"

/*******************************************************************************
DEFINITIONS
*******************************************************************************/

typedef void (* GPIOcallbackFuncPtr_t)(void *);//(void *, uint32_t);
#define BUTTONTASK_FREQUENCY_HZ (1000u)
#define BUTTONTASK_PERIOD_MS    ((float)(1.0f / BUTTONTASK_FREQUENCY_HZ))

#define SHORT_PRESS_MS          (100.0f)
#define LONG_PRESS_MS           (2000.0f)

#define SHORT_PRESS_FREQ_HZ     ((float)(1.0f / (SHORT_PRESS_MS / 1000)))
#define LONG_PRESS_FREQ_HZ      ((float)(1.0f / (LONG_PRESS_MS / 1000)))

#define SHORT_PRESS_COUNT       (BUTTONTASK_FREQUENCY_HZ * SHORT_PRESS_FREQ_HZ)
#define LONG_PRESS_COUNT        (BUTTONTASK_FREQUENCY_HZ * LONG_PRESS_FREQ_HZ)

#define MAX_BUTTONS (16)

/*******************************************************************************
TYPES
*******************************************************************************/

typedef struct
{
    GPIO_TypeDef * GPIO_port;
    uint16_t GPIO_pin;
    uint32_t pull_up_down;
    callbackFuncPtr_t assertCallback;
    callbackFuncPtr_t deassertCallback;
}buttonData_t;

/*******************************************************************************
GLOBAL VARIABLES
*******************************************************************************/

/*******************************************************************************
NAMESPACE
*******************************************************************************/

class CbuttonHandler
        : public threadCore::CTaskBase
{
public:
    class CGPIOCallback
    {
    public:
        uint32_t counter;
        GPIOcallbackFuncPtr_t shortPressCallback;
        GPIOcallbackFuncPtr_t longPressCallback;
        void * pInstance;
    };

    CbuttonHandler(char const * const pName
                  , const float freq
                  , uint32_t priority
                  , void * const pStack
                  , const size_t stackSize
                  , CDebounceTask * pDebounceTask
                  , CPneumaticActuator * pActuator = nullptr
                  , CWatchdogBase * pWatchdog = nullptr);
    ~CbuttonHandler(void) = default;
    void funcBegin(void) override;
    void funcMain(void) override;
    void subscribe(GPIO_TypeDef * GPIO_port
                   , uint16_t GPIO_pin
                   , uint32_t pull_up_down
                   , GPIOcallbackFuncPtr_t shortPressCallback = nullptr
                   , GPIOcallbackFuncPtr_t longPressCallback = nullptr);
    void subscribe(buttonData_t * pButtonData);

private:
    void pressed();
    void released();
    static void _press(void * pInstance);
    static void _release(void * pInstance);
//    static void _shortButtonPress(void * pInstance, uint32_t button);
//    static void _longButtonPress(void * pInstance, uint32_t button);

private:
    uint32_t m_changed;
    uint32_t m_buttonState;
    uint32_t m_previousButtonState;
    size_t m_buttonCount;
    CLinkedList<CGPIOCallback> m_buttonCounter;
    CDebounceTask * m_pDebounceTask;
    CPneumaticActuator * m_pActuator;
    uint8_t GPIOTable[MAX_BUTTONS * sizeof(CNode<CbuttonHandler::CGPIOCallback>)];
};

/*******************************************************************************
INLINE FUNCTION DEFINITIONS
*******************************************************************************/


#endif /* BUTTONHANDLER_HPP */
