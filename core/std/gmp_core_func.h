
#ifndef _FILE_GMP_CORE_H_
#define _FILE_GMP_CORE_H_

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

    //extern ctl_object_nano_t *ctl_nano_handle;

    // This function should be called when Chip setup is completed.
    GMP_STATIC_INLINE
    void gmp_base_entry(void)
    {
#ifdef SPECIFY_PC_ENVIRONMENT
        uint32_t loop_tick;
#endif // SPECIFY_PC_ENVIRONMENT

#ifndef SPECIFY_DISABLE_CSP
        // CSP Startup function
        //
        gmp_csp_startup();
#endif // SPECIFY_DISABLE_CSP

        // platform related function, initialize peripheral
        // This function is defined by user.
        // if CSP is disabled, user should implement chip setup routine
        // in this function.
        //
        setup_peripheral();

        // TODO: setup GMP library memory management module
        //

#ifndef SPECIFY_DISABLE_GMP_LOGO
        // Debug information print
        //
        gmp_base_show_label();
#endif // SPECIFY_DISABLE_GMP_LOGO

#if !defined SPECIFY_DISABLE_GMP_CTL
        // Call CTL(Controller template library) initialization function
        //
        ctl_init();

#endif // SPECIFY_DISABLE_GMP_CTL

        // Call user initialization function
        //
        init();

#ifndef SPECIFY_DISABLE_CSP
        // latest function before Main loop, CSP may use this function to enable interrupt.
        //
        gmp_csp_post_process();
#endif // SPECIFY_DISABLE_CSP

#if !defined SPECIFY_DISABLE_GMP_CTL
#ifdef SPECIFY_ENABLE_CTL_FRAMEWORK_NANO
        ctl_fm_controller_inspection(ctl_nano_handle);
#endif // SPECIFY_ENABLE_CTL_FRAMEWORK_NANO
#endif // SPECIFY_DISABLE_GMP_CTL

#ifdef SPECIFY_PC_ENVIRONMENT
        // PC simulate environment, finite iteration
        for (loop_tick = 0; loop_tick < PC_ENV_MAX_ITERATION; ++loop_tick)
#else  // SPECIFY_PC_ENVIRONMENT
    // real processor routine
    for (;;)
#endif // SPECIFY_PC_ENVIRONMENT

        {

#ifndef SPECIFY_DISABLE_CSP
            // Call GMP CSP module loop routine
            //
            gmp_csp_loop();

#endif // SPECIFY_DISABLE_CSP

#if !defined SPECIFY_DISABLE_GMP_CTL
#ifdef SPECIFY_ENABLE_CTL_FRAMEWORK_NANO
            ctl_fm_state_dispatch(ctl_nano_handle);
#endif // SPECIFY_ENABLE_CTL_FRAMEWORK_NANO
#endif // SPECIFY_DISABLE_GMP_CTL

            // Call user general loop routine
            //
            mainloop();

#if !defined SPECIFY_DISABLE_GMP_CTL
            // Call controller loop routine
            //
            ctl_mainloop();
#endif // SPECIFY_DISABLE_GMP_CTL
        }

#if !defined SPECIFY_DISABLE_CSP
        // This function is unreachable.
        gmp_csp_exit();
#endif // SPECIFY_DISABLE_CSP
    }

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _FILE_GMP_CORE_H_
