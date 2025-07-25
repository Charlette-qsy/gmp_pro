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

#include <xplt.peripheral.h>

#include <ctl/component/digital_power/single_phase/spll.h>

#include <ctl/component/intrinsic/discrete/proportional_resonant.h>

#include <ctl/component/intrinsic/discrete/stimulate.h>

#ifndef _FILE_CTL_MAIN_H_
#define _FILE_CTL_MAIN_H_

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

	//// speed encoder
	// extern spd_calculator_t spd_enc;
	//
	//// PMSM servo objects
	//// extern pmsm_fm_t pmsm;
	//
	// #if defined OPENLOOP_CONST_FREQUENCY
	//
	//// PMSM const frequency controller
	// extern ctl_const_f_controller const_f;
	//
	// #else // OPENLOOP_CONST_FREQUENCY
	//
	//// PMSM const frequency slope controller
	// extern ctl_slope_f_controller slope_f;
	//
	// #endif // OPENLOOP_CONST_FREQUENCY
	//
	// #ifdef PMSM_CTRL_USING_QEP_ENCODER
	//// Auto - turn encoder
	// extern pos_autoturn_encoder_t pos_enc;
	// #endif // PMSM_CTRL_USING_QEP_ENCODER
	//
	//// PMSM controller
	// extern pmsm_bare_controller_t pmsm_ctrl;

	extern adc_bias_calibrator_t adc_calibrator;
	extern fast_gt flag_enable_adc_calibrator;
	extern fast_gt index_adc_calibrator;

	extern pid_regular_t current_pid, voltage_pid, sinv_vlotage_pid;

	extern ctl_single_phase_pll spll;
	extern ctrl_gt ac_input;

	extern ctrl_gt pwm_out_pu;

	// extern ptr_adc_channel_t uin;
	// extern ptr_adc_channel_t uout;
	// extern ptr_adc_channel_t idc;
	extern ptr_adc_channel_t sinv_uc;

	extern ptr_adc_channel_t sinv_il;
	
		extern ptr_adc_channel_t sinv_ig;

	extern ptr_adc_channel_t sinv_udc;

	extern ctrl_gt sinv_pwm_pu[2];
	extern pr_ctrl_t sinv_pr_base;
	extern qpr_ctrl_t sinv_qpr_base;

	extern ctrl_gt modulate_target;

	extern ctrl_gt sinv_current_ref;

	extern ctl_src_rg_t rg;
	
	extern volatile fast_gt flag_error;

	typedef enum _tag_adc_index
	{
		MTR_ADC_UA = 0,
		MTR_ADC_UB,
		MTR_ADC_UC,
		MTR_ADC_IA,
		MTR_ADC_IB,
		MTR_ADC_IC,
		MTR_ADC_UDC,
		MTR_ADC_IDC
	} adc_index_t;

	extern ctrl_gt v_set;
	
	// periodic callback function things.
	GMP_STATIC_INLINE
		void ctl_dispatch(void)
	{
//		if(flag_error == 0)
//		{
			//ctl_step_single_phase_pll(
			//	// handle of Single phase PLL object
			//	&spll,
			//	// input AC value
			//	ctl_sin(ctl_step_ramp_gen(&rg)));

			 ctl_step_single_phase_pll(
					 // handle of Single phase PLL object
					 &spll,
					 // input AC value
					 sinv_uc.control_port.value);

			// Voltage Openloop
			//modulate_target = ctl_mul(spll.phasor.dat[phase_alpha], v_set);
			//modulate_target = ctl_mul(spll.phasor.dat[0], v_set);

//			// current Loop,ADC sample is negative 
//			modulate_target = ctl_step_qpr_controller(&sinv_qpr_base, ctl_mul(spll.phasor.dat[0], float2ctrl(v_set)) +
//				sinv_ig.control_port.value);
			
			// DC Voltage Closeloop
			sinv_current_ref = ctl_step_pid_ser(&sinv_vlotage_pid, float2ctrl(0.42) - sinv_udc.control_port.value);
			modulate_target = ctl_step_qpr_controller(&sinv_qpr_base, ctl_mul(spll.phasor.dat[0], sinv_current_ref) +
				sinv_ig.control_port.value);	



			// ADC sample is negative 
			//modulate_target = ctl_step_qpr_controller(&sinv_qpr_base, ctl_mul(spll.phasor.dat[0], float2ctrl(v_set)) +
			//	sinv_il.control_port.value);
			// 
			// 
	//		modulate_target = ctl_step_qpr_controller(&sinv_qpr_base, ctl_mul(spll.phasor.dat[0], float2ctrl(v_set)) + sinv_ig.control_port.value +
	//                                sinv_uc.control_port.value + sinv_udc.control_port.value);

		// modulate_target = ctl_step_pr_controller(&sinv_pr_base, ctl_mul(spll.phasor.dat[0], float2ctrl(0.05)) -
		//                                                             sinv_il.control_port.value)+ctl_mul(float2ctrl(0.8),sinv_uc.control_port.value);
		// gird connectted without dc voltage control


			
			// modulate_target = ctl_step_pr_controller(&sinv_pr_base, ctl_mul(spll.phasor.dat[0], float2ctrl(0.2)) -
			//                                                            sinv_il.control_port.value);

			// modulate_target = ctl_step_qpr_controller(&sinv_qpr_base, ctl_mul(spll.phasor.dat[0], float2ctrl(0.2)) -
			//                                                             sinv_il.control_port.value)+ctl_mul(float2ctrl(0.00001),sinv_uc.control_port.value);

			// modulate_target = ctl_step_pr_controller(&sinv_pr_base, ctl_mul(spll.phasor.dat[0], float2ctrl(0.05)) -
			//                                                             sinv_il.control_port.value)+ctl_mul(float2ctrl(0.8),sinv_uc.control_port.value);
			// gird conencted without dc voltage control

			// gird conencted with dc voltage control
			// ��ѹ�������Ϊ���������ķ�ֵ��������������λͨ�����໷+�������ؽ�ȷ����
			//sinv_current_ref = -ctl_step_pid_ser(&sinv_vlotage_pid, float2ctrl(0.8) - sinv_udc.control_port.value);
			//modulate_target = ctl_step_qpr_controller(&sinv_qpr_base, ctl_mul(spll.phasor.dat[0], sinv_current_ref) -
			//                                                              sinv_il.control_port.value);

			//
			// Unipolar SPWM 1
			sinv_pwm_pu[0] = ctl_div2(-modulate_target + float2ctrl(1));
			sinv_pwm_pu[1] = ctl_div2(modulate_target + float2ctrl(1));

			// Unipolar SPWM 2
				//sinv_pwm_pu[0] = -modulate_target;
				//sinv_pwm_pu[1] = modulate_target;
//		}
//		else
//		{
//			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
//			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
//			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
//		}
	}

#ifdef __cplusplus
}
#endif // _cplusplus

#endif // _FILE_CTL_MAIN_H_
