//
// THIS IS A DEMO SOURCE CODE FOR GMP LIBRARY.
//
// User should add all definitions of peripheral objects in this file.
//
// User should implement the peripheral objects initialization in setup_peripheral function.
//
// This file is platform-related.
//

// GMP basic core header
#include <gmp_core.h>

// user main header
#include "user_main.h"

#include <xplt.peripheral.h>

//////////////////////////////////////////////////////////////////////////
// definitions of peripheral
//

// SIL standard port for Motor control

// tri_ptr_adc_channel_t uabc;
// tri_ptr_adc_channel_t iabc;
//
ptr_adc_channel_t uin;
ptr_adc_channel_t uc;
ptr_adc_channel_t il;
pwm_channel_t pwm_out;

// ADC RESULT INDEX
typedef enum _tag_adc_result_nameplate
{
    ADC_RESULT_IL  = 0,
    ADC_RESULT_UIN = 1,
    ADC_RESULT_UOUT = 2
}adc_result_nameplate_t;


//////////////////////////////////////////////////////////////////////////
// peripheral setup function
//

// User should setup all the peripheral in this function.
void setup_peripheral(void)
{
    //
// Step 1 Init all the ADC & PWM standard ports
//

    ctl_init_ptr_adc_channel(
        // ptr_adc object
        &il,
        // pointer to ADC raw data
        &simulink_rx_buffer.adc_result[ADC_RESULT_IL],
        // ADC Channel settings.
        // iqn is valid only when ctrl_gt is a fixed point type.
        2.5 / 0.1 / 10, 0.9/2.5, 12, 24); // ���� ƫ�� ADC�ֱ���

    ctl_init_ptr_adc_channel(
        // ptr_adc object
        &uin,
        // pointer to ADC raw data
        &simulink_rx_buffer.adc_result[ADC_RESULT_UIN],
        // ADC Channel settings.
        // iqn is valid only when ctrl_gt is a fixed point type.
        2.5/0.0109/100, 0.9943/2.5, 12, 24);

    ctl_init_ptr_adc_channel(
        // ptr_adc object
        &uc,
        // pointer to ADC raw data
        &simulink_rx_buffer.adc_result[ADC_RESULT_UOUT],
        // ADC Channel settings.
        // iqn is valid only when ctrl_gt is a fixed point type.
        2.5 / 0.0109 / 100, 0.9943/2.5, 12, 24);

    ctl_init_pwm_channel(&pwm_out, 0, CONTROLLER_PWM_CMP_MAX);

    // 
    // Step II Connect Standard Interface to controller
    //

    // Attach ADC channel to Boost Controller
    ctl_attach_boost_ctrl_input(
        // Boost controller
        &boost_ctrl,
        // output capacitor voltage
        &uc.control_port,
        // inductor current
        &il.control_port,
        // input voltage
        &uin.control_port);


}
