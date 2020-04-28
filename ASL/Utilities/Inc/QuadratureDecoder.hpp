/*******************************************************************************
* File          : QuadratureDecoder.hpp
*
* Description   : 
*
* Project       : 
*
* Author        : s.gilbert
*
* Created on    : 28 Apr 2020
*
*******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef QUADRATUREDECODER_HPP
#define QUADRATUREDECODER_HPP

/*******************************************************************************
INCLUDES
*******************************************************************************/

#include "DebounceTask.hpp"

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
NAMESPACE
*******************************************************************************/

class CQuadratureDecoder
{
public:
    CQuadratureDecoder(CDebounceTask * pDebounceTask
                       , GPIO_TypeDef * A_port, uint16_t A_pin
                       , GPIO_TypeDef * B_port, uint16_t B_pin);
    ~CQuadratureDecoder() = default;

private:
    static void _callbackA(void * pArgs);
    static void _callbackB(void * pArgs);
    void calc(uint32_t channel);

private:
    CDebounceTask * m_pDebounceTask;
    GPIO_TypeDef * m_APort;
    uint16_t m_APin;
    GPIO_TypeDef * m_BPort;
    uint16_t m_BPin;
    int32_t m_count;
};

/*******************************************************************************
INLINE FUNCTION DEFINITIONS
*******************************************************************************/


#endif /* QUADRATUREDECODER_HPP */
