/**
 * @file ctl_main.cpp
 * @author Javnson (javnson@zju.edu.cn)
 * @brief
 * @version 0.1
 * @date 2024-09-30
 *
 * @copyright Copyright GMP(c) 2024
 *
 */

// const F & VF controller
#include <ctl/component/motor_control/basic/vf_generator.h>

// speed encoder
#include <ctl\component\motor_control\basic\encoder.h>

// motor controller
#include <ctl/suite/mcs_pmsm/pmsm_ctrl.h>

#include <ctl/component/interface/pwm_channel.h>

#include <ctl/component/interface/adc_channel.h>

#include <ctl\component\digital_power\basic/boost.h>

#include <xplt.peripheral.h>

#include <ctl/component/intrinsic/continuous/continuous_pid.h>

#ifndef _FILE_CTL_MAIN_H_
#define _FILE_CTL_MAIN_H_

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

// ADC RESULT INDEX
typedef enum _tag_adc_result_nameplate
{
    ADC_RESULT_IL = 0,
    ADC_RESULT_UIN = 1,
    ADC_RESULT_UOUT = 2,
    ADC_BOOST_CHANNEL_NUM = 3
} adc_result_nameplate_t;

extern adc_bias_calibrator_t adc_calibrator;
extern fast_gt flag_enable_adc_calibrator;
extern fast_gt index_adc_calibrator;


extern pid_regular_t voltage_loop;
extern ptr_adc_channel_t uc;

// Boost Controller Suite
extern boost_ctrl_t boost_ctrl;

// periodic callback function things.
GMP_STATIC_INLINE
void ctl_dispatch(void)
{

    //ctrl_gt current_ref = ctl_step_pid_ser(&voltage_pid, float2ctrl(0.8) - uout.control_port.value);
    //pwm_out_pu = float2ctrl(1) - ctl_step_pid_ser(&current_pid, current_ref - idc.control_port.value);


    ////pwm_out_pu = float2ctrl(1) - ctl_step_pid_ser(&current_pid, idc.control_port.value - current_ref);
    /// 
    ctl_step_pid_ser(&voltage_loop, float2ctrl(0.3) - uc.control_port.value);
    ctl_step_boost_ctrl(&boost_ctrl);
}

#ifdef __cplusplus
}
#endif // _cplusplus

#endif // _FILE_CTL_MAIN_H_
