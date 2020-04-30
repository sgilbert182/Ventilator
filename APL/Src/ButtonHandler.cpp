/*******************************************************************************
* File          : ButtonHandler.cpp
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

/*******************************************************************************
INCLUDES
*******************************************************************************/

#include "ButtonHandler.hpp"

/*******************************************************************************
NAMESPACE
*******************************************************************************/

/*******************************************************************************
DEFINITIONS
*******************************************************************************/

/*******************************************************************************
TYPES
*******************************************************************************/

/*******************************************************************************
GLOBAL VARIABLES
*******************************************************************************/

/*******************************************************************************
MODULE VARIABLES
*******************************************************************************/

/*******************************************************************************
MODULE FUNCTION DECLARATIONS
*******************************************************************************/

/*******************************************************************************
FUNCTION DEFINITIONS
*******************************************************************************/

/**\brief   Constructor.
 *
 * \param   pName       - pointer to the task name
 * \param   freq        - task update frequency
 * \param   priority    - task priority
 * \param   pStack      - pointer to stack space
 * \param   stackSize   - stack size in bytes
 * \param   pWatchdog   - pointer to the watchdog hardware
 *
 * \return  None
 */
CbuttonHandler::CbuttonHandler(char const * const pName
                              , const float freq
                              , uint32_t priority
                              , void * const pStack
                              , const size_t stackSize
                              , CDebounceTask * pDebounceTask
                              , CPneumaticActuator * pActuator
                              , CWatchdogBase * pWatchdog)
    : threadCore::CTaskBase(pName, freq, priority, pStack, stackSize, pWatchdog)
    , m_changed(0)
    , m_buttonState(0)
    , m_previousButtonState(0)
    , m_buttonCount(0)
    , m_buttonCounter(GPIOTable, sizeof(GPIOTable))
    , m_pDebounceTask(pDebounceTask)
    , m_pActuator(pActuator)
{}

/**\brief   Constructor.
 *
 * \param   pName       - pointer to the task name
 * \param   freq        - task update frequency
 * \param   priority    - task priority
 * \param   pStack      - pointer to stack space
 * \param   stackSize   - stack size in bytes
 * \param   pWatchdog   - pointer to the watchdog hardware
 *
 * \return  None
 */
void CbuttonHandler::funcBegin(void)
{
//    this->subscribe(Button1_GPIO_Port, Button1_Pin, GPIO_PULLUP
//                    , _shortButtonPress
//                    , _longButtonPress);
//    this->subscribe(Button2_GPIO_Port, Button2_Pin, GPIO_PULLUP);
//    this->subscribe(Button3_GPIO_Port, Button3_Pin, GPIO_PULLUP);
//    this->subscribe(Button4_GPIO_Port, Button4_Pin, GPIO_PULLUP);
}

/**\brief   Registers a pin and port combination to be monitored by the button
 *          handler task. Independent callbacks can be registered for both short
 *          and long presses.
 *
 *
 * \param   GPIO_port           - pointer to the port struct
 * \param   GPIO_pin            - pin ID
 * \param   pull_up_down        - one of GPIO_NOPULL, GPIO_PULLUP or GPIO_PULLDOWN
 * \param   shortPressCallback  - short press callback function pointer
 * \param   longPressCallback   - long press callback function pointer
 *
 * \return  returns true if successful otherwise returns false
 */
void CbuttonHandler::subscribe(GPIO_TypeDef * GPIO_port
                               , uint16_t GPIO_pin
                               , uint32_t pull_up_down
                               , GPIOcallbackFuncPtr_t shortPressCallback
                               , GPIOcallbackFuncPtr_t longPressCallback)
{
    m_pDebounceTask->subscribe(GPIO_port, GPIO_pin, pull_up_down
                              , _release, this
                              , _press, this);

    CGPIOCallback GPIOState = {0
                                , shortPressCallback
                                , longPressCallback
                                , this};

    m_buttonCounter.pushToFront(&GPIOState);
}

/**\brief   Registers a pin and port combination to be monitored by the button
 *          handler task. Independent callbacks can be registered for both short
 *          and long presses.
 *
 * \param   pButtonData - pointer to a struct containing the button data.
 *
 * \return  returns true if successful otherwise returns false
 */
void CbuttonHandler::subscribe(buttonData_t * pButtonData)
{
    this->subscribe(pButtonData->GPIO_port, pButtonData->GPIO_pin, pButtonData->pull_up_down
                    , pButtonData->assertCallback, pButtonData->deassertCallback);
}

/**\brief   Sets the bit that indicates which button has been pressed.
 *
 * \param   None
 *
 * \return  None
 */
void CbuttonHandler::pressed(void)
{
    m_buttonState |= m_pDebounceTask->anyChangedState();
}

/**\brief   Clears the bit that indicates which button has been released.
 *
 * \param   None
 *
 * \return  None
 */
void CbuttonHandler::released(void)
{
    m_buttonState &= ~m_pDebounceTask->anyChangedState();
}

/**\brief   main thread function.
 *
 * \param   None
 *
 * \return  None
 */
void CbuttonHandler::funcMain(void)
{
    auto buttonState = m_buttonState;
    auto buttonCounter = 0u;

    while (buttonState)
    {
        if(buttonState && 0x01)
        {
            CGPIOCallback GPIOState;
            m_buttonCounter.peakFromNode(buttonCounter, &GPIOState);
            ++GPIOState.counter;
            m_buttonCounter.updateNode(buttonCounter, &GPIOState);

            // check for a long press (and still being held)
            if (LONG_PRESS_COUNT < GPIOState.counter)
            {
                if(GPIOState.longPressCallback)
                {
                    GPIOState.longPressCallback(GPIOState.pInstance);
                    GPIOState.counter = LONG_PRESS_COUNT / 2; // reset the timer so it now takes half the long press period, this allows the user to quickly move through a list without going too fast
                    m_buttonCounter.updateNode(buttonCounter, &GPIOState);
                }
            }
        }
        buttonState >>= 1;
        ++buttonCounter;
    }

    uint32_t releasedButtons = m_previousButtonState & (m_buttonState ^ m_previousButtonState);
    m_previousButtonState = m_buttonState;

    uint32_t buttonCount = 0;
    while (releasedButtons)
    {
        if(releasedButtons && 0x01)
        {
            CGPIOCallback GPIOState;
            m_buttonCounter.peakFromNode(buttonCount, &GPIOState);

            if ((SHORT_PRESS_COUNT < GPIOState.counter)
                    && (GPIOState.counter < SHORT_PRESS_COUNT))
            {
                if(GPIOState.shortPressCallback)
                {
                    GPIOState.shortPressCallback(GPIOState.pInstance);
                }
            }
            GPIOState.counter = 0;
            m_buttonCounter.updateNode(buttonCount, &GPIOState);

            releasedButtons >>= 1;
            ++buttonCount;
        }
    }
}

/**\brief   static function to call the class's press method.
 *
 * \param   pInstance   - class instance
 *
 * \return  None
 */
void CbuttonHandler::_press(void * pInstance)
{
    if(nullptr != pInstance)
    {
        ((CbuttonHandler *)pInstance)->pressed();
    }
}

/**\brief   static function to call the class's release method.
 *
 * \param   pInstance   - class instance
 *
 * \return  None
 */
void CbuttonHandler::_release(void * pInstance)
{
    if(nullptr != pInstance)
    {
        ((CbuttonHandler *)pInstance)->released();
    }
}

/**\brief   static function to call the class's short press method.
 *
 * \param   pInstance   - class instance
 * \param   button      - button ID
 *
 * \return  None
 */
//void CbuttonHandler::_shortButtonPress(void * pInstance, uint32_t button)
//{
//    CGPIOCallback GPIOState;
//
//    ((CbuttonHandler *)pInstance)->m_buttonCounter.peakFromNode(button, &GPIOState);
//
//    GPIOState.shortPressCallback(pInstance);
//}

/**\brief   static function to call the class's long press method.
 *
 * \param   pInstance   - class instance
 * \param   button      - button ID
 *
 * \return  None
 */
//void CbuttonHandler::_longButtonPress(void * pInstance, uint32_t button)
//{
//
//}
