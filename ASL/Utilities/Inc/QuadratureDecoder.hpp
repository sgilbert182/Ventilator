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

#include "PositionDecoder.hpp"
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
    : public CPositionDecoder
{
public:
    CQuadratureDecoder(CDebounceTask * pDebounceTask = nullptr
                       , GPIO_TypeDef * A_port = nullptr, uint16_t A_pin = 0
                       , GPIO_TypeDef * B_port = nullptr, uint16_t B_pin = 0);
    ~CQuadratureDecoder() = default;
    virtual int32_t getPosition(void) override;
    virtual void resetPosition(void) override;

private:
    static void _callback(void * pArgs);
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
