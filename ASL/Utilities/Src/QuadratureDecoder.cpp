/*******************************************************************************
* File          : QuadratureDecoder.cpp
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

/*******************************************************************************
INCLUDES
*******************************************************************************/

#include "QuadratureDecoder.hpp"

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

/**\brief   Constructor. Registers the IO's with an active debounce task.
 *
 * \param   pDebounceTask       - pointer to the debounce task to use
 * \param   pAPort              - pointer to the pin A's port struct
 * \param   APin                - pin A's ID
 * \param   pBPort              - pointer to the pin B's port struct
 * \param   BPin                - pin B's ID
 *
 * \return  None
 */
CQuadratureDecoder::CQuadratureDecoder(CDebounceTask * pDebounceTask
                                       , GPIO_TypeDef * pAPort, uint16_t APin
                                       , GPIO_TypeDef * pBPort, uint16_t BPin)
    : m_pDebounceTask(pDebounceTask)
    , m_APort(pAPort)
    , m_APin(APin)
    , m_BPort(pBPort)
    , m_BPin(BPin)
    , m_count(0)
{
    if(m_pDebounceTask)
    {
        if(m_APort)
        {
            m_pDebounceTask->subscribe(m_APort, m_APin, GPIO_NOPULL
                                       , nullptr, nullptr
                                       , this->_callback, this);
        }
        if(m_BPort)
        {
            m_pDebounceTask->subscribe(m_BPort, m_BPin, GPIO_NOPULL
                                       , nullptr, nullptr
                                       , nullptr, nullptr);
        }
    }
}

/**\brief   returns the counter value.
 *
 * \param   None
 *
 * \return  counter value
 */
int32_t CQuadratureDecoder::getPosition(void)
{
    return m_count;
}

/**\brief   Resets the counter.
 *
 * \param   None
 *
 * \return  None
 */
void CQuadratureDecoder::resetPosition(void)
{
    m_count = 0;
}

/**\brief   Reads the IO states of the incoming quadrature inputs.
 *
 * \param   channel - channel ID that triggered the calculation
 *
 * \return  None
 */
void CQuadratureDecoder::calc(uint32_t channel)
{
    /* if channel A is high and channel B is low, channel A is leading so
     * assume clockwise rotation.
     */
    m_count += m_pDebounceTask->getGPIOState(m_BPort, m_BPin) ? -1 : 1;
}

/**\brief   Callback triggered when IO A is asserted.
 *
 * \param   pArgs   - class to call
 *
 * \return  None
 */
void CQuadratureDecoder::_callback(void * pArgs)
{
    ((CQuadratureDecoder *)pArgs)->calc(1);
}
