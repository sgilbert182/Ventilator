/*******************************************************************************
* File          : PneumaticActuator.cpp
*
* Description   : 
*
* Project       : 
*
* Author        : s.gilbert
*
* Created on    : 30 Mar 2020
*
*******************************************************************************/

/*******************************************************************************
INCLUDES
*******************************************************************************/

#include "PneumaticActuator.hpp"

/*******************************************************************************
NAMESPACE
*******************************************************************************/

/*******************************************************************************
DEFINITIONS
*******************************************************************************/

#ifndef ARRAY_LEN
#define ARRAY_LEN(x) sizeof(x) / sizeof(x[0])
#endif

#define MAX_POS_VAL     (65536.0f)                  // 2^16 16 bit pwm
#define PWM_LSB         (0.02 / MAX_POS)            // 20mA / max pwm value
#define MIN_POS_VAL     (0.004 / PWM_LSB)           // 4mA / pwm bit wieght
#define DELTA_POS_VAL   (MAX_POS_VAL - MIN_POS_VAL) // 20mA - 4mA bit value

/*******************************************************************************
TYPES
*******************************************************************************/

/*******************************************************************************
GLOBAL VARIABLES
*******************************************************************************/

/*******************************************************************************
MODULE VARIABLES
*******************************************************************************/

uint32_t sinewave[] = {
        0, 2, 5, 9, 14, 20, 28, 37,
        47, 59, 71, 85, 100, 117, 134, 153,
        173, 195, 217, 241, 266, 292, 319, 348,
        378, 409, 441, 475, 510, 545, 583, 621,
        661, 701, 744, 787, 831, 877, 924, 972,
        1021, 1071, 1123, 1176, 1230, 1285, 1342, 1399,
        1458, 1518, 1579, 1641, 1705, 1769, 1835, 1902,
        1970, 2040, 2110, 2182, 2255, 2329, 2404, 2480,
        2557, 2636, 2715, 2796, 2878, 2961, 3045, 3131,
        3217, 3305, 3393, 3483, 3574, 3666, 3759, 3853,
        3948, 4044, 4142, 4240, 4340, 4440, 4542, 4645,
        4749, 4854, 4960, 5067, 5175, 5284, 5394, 5505,
        5617, 5730, 5844, 5960, 6076, 6193, 6311, 6431,
        6551, 6672, 6794, 6917, 7042, 7167, 7293, 7420,
        7548, 7677, 7807, 7938, 8069, 8202, 8336, 8470,
        8606, 8742, 8880, 9018, 9157, 9297, 9438, 9580,
        9722, 9866, 10010, 10155, 10301, 10448, 10596, 10745,
        10894, 11044, 11196, 11347, 11500, 11654, 11808, 11963,
        12119, 12276, 12433, 12591, 12750, 12910, 13070, 13232,
        13393, 13556, 13720, 13884, 14048, 14214, 14380, 14547,
        14715, 14883, 15052, 15222, 15392, 15563, 15735, 15907,
        16080, 16253, 16427, 16602, 16777, 16953, 17130, 17307,
        17485, 17663, 17842, 18022, 18202, 18382, 18563, 18745,
        18927, 19110, 19293, 19477, 19661, 19845, 20031, 20216,
        20402, 20589, 20776, 20964, 21152, 21340, 21529, 21718,
        21908, 22098, 22288, 22479, 22671, 22862, 23054, 23247,
        23439, 23632, 23826, 24020, 24214, 24408, 24603, 24798,
        24993, 25189, 25385, 25581, 25778, 25974, 26171, 26369,
        26566, 26764, 26962, 27160, 27358, 27557, 27756, 27955,
        28154, 28353, 28553, 28753, 28952, 29152, 29352, 29553,
        29753, 29953, 30154, 30355, 30555, 30756, 30957, 31158,
        31359, 31560, 31761, 31963, 32164, 32365, 32566, 32768,
        32969, 33170, 33371, 33572, 33774, 33975, 34176, 34377,
        34578, 34779, 34980, 35180, 35381, 35582, 35782, 35982,
        36183, 36383, 36583, 36782, 36982, 37182, 37381, 37580,
        37779, 37978, 38177, 38375, 38573, 38771, 38969, 39166,
        39364, 39561, 39757, 39954, 40150, 40346, 40542, 40737,
        40932, 41127, 41321, 41515, 41709, 41903, 42096, 42288,
        42481, 42673, 42864, 43056, 43247, 43437, 43627, 43817,
        44006, 44195, 44383, 44571, 44759, 44946, 45133, 45319,
        45504, 45690, 45874, 46058, 46242, 46425, 46608, 46790,
        46972, 47153, 47333, 47513, 47693, 47872, 48050, 48228,
        48405, 48582, 48758, 48933, 49108, 49282, 49455, 49628,
        49800, 49972, 50143, 50313, 50483, 50652, 50820, 50988,
        51155, 51321, 51487, 51651, 51815, 51979, 52142, 52303,
        52465, 52625, 52785, 52944, 53102, 53259, 53416, 53572,
        53727, 53881, 54035, 54188, 54339, 54491, 54641, 54790,
        54939, 55087, 55234, 55380, 55525, 55669, 55813, 55955,
        56097, 56238, 56378, 56517, 56655, 56793, 56929, 57065,
        57199, 57333, 57466, 57597, 57728, 57858, 57987, 58115,
        58242, 58368, 58493, 58618, 58741, 58863, 58984, 59104,
        59224, 59342, 59459, 59575, 59691, 59805, 59918, 60030,
        60141, 60251, 60360, 60468, 60575, 60681, 60786, 60890,
        60993, 61095, 61195, 61295, 61393, 61491, 61587, 61682,
        61776, 61869, 61961, 62052, 62142, 62230, 62318, 62404,
        62490, 62574, 62657, 62739, 62820, 62899, 62978, 63055,
        63131, 63206, 63280, 63353, 63425, 63495, 63565, 63633,
        63700, 63766, 63830, 63894, 63956, 64017, 64077, 64136,
        64193, 64250, 64305, 64359, 64412, 64464, 64514, 64563,
        64611, 64658, 64704, 64748, 64791, 64834, 64874, 64914,
        64952, 64990, 65025, 65060, 65094, 65126, 65157, 65187,
        65216, 65243, 65269, 65294, 65318, 65340, 65362, 65382,
        65401, 65418, 65435, 65450, 65464, 65476, 65488, 65498,
        65507, 65515, 65521, 65526, 65530, 65533, 65535
};

/*******************************************************************************
MODULE FUNCTION DECLARATIONS
*******************************************************************************/

/*******************************************************************************
FUNCTION DEFINITIONS
*******************************************************************************/

/**\brief   Constructor
 *
 * \param   pName       - pointer to the task name
 * \param   freq        - task update frequency
 * \param   priority    - task priority
 * \param   pStack      - pointer to stack space
 * \param   stackSize   - stack size in bytes
 * \param   phtim       - pointer to the timer handle
 * \param   pWatchdog   - pointer to the watchdog hardware
 *
 * \return  None
 */
CPneumaticActuator::CPneumaticActuator(char const * const pName
                     , const float freq
                     , uint32_t priority
                     , void * const pStack
                     , const size_t stackSize
                     , TIM_HandleTypeDef * phtim
                     , CActuatorDisplay * pActuatorDisplay
                     , CWatchdogBase * pWatchdog)
    : threadCore::CTaskBase(pName, freq, priority, pStack, stackSize, pWatchdog)
    , m_pTimer(phtim)
    , m_sineIndex(0)
    , m_speed(10)
    , m_amplitude(100)
    , m_breathPhase(true)
    , m_pActuatorDisplay(pActuatorDisplay)
{}

/**\brief   Single call function called before main task, starts timer in PWM
 *          mode.
 *
 * \param   None
 *
 * \return  None
 */
void CPneumaticActuator::funcBegin(void)
{
    HAL_TIM_PWM_Start(m_pTimer, TIM_CHANNEL_1);
}

/**\brief   Main routine, currently updates the timer PWM register with next
 *          value.
 *
 * \param   None
 *
 * \return  None
 */
void CPneumaticActuator::funcMain(void)
{
    uint32_t demandedPressure = (MIN_POS_VAL +
                                (((sinewave[(m_breathPhase) ? m_sineIndex : 0] * (DELTA_POS_VAL / MAX_POS_VAL)) * m_amplitude) / 100));
    __HAL_TIM_SET_COMPARE(m_pTimer, TIM_CHANNEL_1, demandedPressure);

    /* if incrementing the sine index exceeds the length of the array then
     * switch to exhalation mode and reset the indexer.
     */
    m_sineIndex = m_sineIndex + m_speed;
    if(ARRAY_LEN(sinewave) < (m_sineIndex + m_speed))
    {
        m_sineIndex = 0;
        m_breathPhase = !m_breathPhase;
    }

    if(m_pActuatorDisplay)
    {
        m_pActuatorDisplay->setPhaseValue(m_breathPhase);
//        m_pActuatorDisplay->setPressureValue(demandedPressure);
    }
}

/**\brief   Increment the speed at which the sinewave is indexed through.
 *
 * \param   None
 *
 * \return  None
 */
void CPneumaticActuator::smallIncrementSpeed(void)
{
    ++m_speed;
}

/**\brief   Decrement the speed at which the sinewave is indexed through.
 *
 * \param   None
 *
 * \return  None
 */
void CPneumaticActuator::smallDecrementSpeed(void)
{
    --m_speed;
}

/**\brief   Large increment the speed at which the sinewave is indexed through.
 *
 * \param   None
 *
 * \return  None
 */
void CPneumaticActuator::largeIncrementSpeed(void)
{
    m_speed += 10;
}

/**\brief   Large decrement the speed at which the sinewave is indexed through.
 *
 * \param   None
 *
 * \return  None
 */
void CPneumaticActuator::largeDecrementSpeed(void)
{
    m_speed -= 10;
}

/**\brief   Sets the speed at which the sinewave is indexed through.
 *
 * \param   speed   - task frequency multiplier
 *
 * \return  None
 */
void CPneumaticActuator::setSpeed(uint32_t speed)
{
    m_speed = speed;
}

/**\brief   Sets the max value of the sinewave in percent.
 *
 * \param   amplitude   - percent size of the sinewave
 *
 * \return  None
 */
void CPneumaticActuator::setAmplitude(uint32_t amplitude)
{
    m_amplitude = amplitude;
}

/**\brief   Increment the speed at which the sinewave is indexed through.
 *
 * \param   None
 *
 * \return  None
 */
void CPneumaticActuator::smallIncrementAmplitude(void)
{
    ++m_amplitude;
}

/**\brief   Decrement the speed at which the sinewave is indexed through.
 *
 * \param   None
 *
 * \return  None
 */
void CPneumaticActuator::smallDecrementAmplitude(void)
{
    --m_amplitude;
}

/**\brief   Large increment the speed at which the sinewave is indexed through.
 *
 * \param   None
 *
 * \return  None
 */
void CPneumaticActuator::largeIncrementAmplitude(void)
{
    m_amplitude += 10;
}

/**\brief   Large decrement the speed at which the sinewave is indexed through.
 *
 * \param   None
 *
 * \return  None
 */
void CPneumaticActuator::largeDecrementAmplitude(void)
{
    m_amplitude -= 10;
}
