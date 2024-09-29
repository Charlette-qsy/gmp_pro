
// This file contains all the peripheral implements

#ifndef _FILE_PERIPHERAL_MODEL_STM32_H_
#define _FILE_PERIPHERAL_MODEL_STM32_H_

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

// ....................................................................//
// PWM controller
//
// kernel functions:
// + Enable PWM output
// + Disable PWM output
// + Set Duty
// + Set frequency
//
#ifdef HAL_TIM_MODULE_ENABLED

#endif // HAL_TIM_MODULE_ENABLED

// ....................................................................//
// UART
//
// kernel functions:
// + Write
// + Read
//
#ifdef HAL_UART_MODULE_ENABLED

    /**
     * @brief STM32 UART handle
     *
     */
    typedef struct _tag_uart_stm32_t
    {
        //
        /**
         * @brief Handle of STM32 UART
         */
        UART_HandleTypeDef *uart_handle;

        /**
         * @brief TX DMA handle
         */
        DMA_HandleTypeDef *uart_tx_dma_handle;

        /**
         * @brief RX DMA handle
         */
        DMA_HandleTypeDef *uart_rx_dma_handle;

        /**
         * @brief This is a buffer pointer of duplex interface.
         * User may band to this buffer to get necessary informations.
         */
        duplex_ift *buffer;

        /**
         * @brief This is a buffer for receive.
         * This buffer should have the same length with duplex buffer.
         */
        data_gt *recv_buf;

    } stm32_uart_t;

/**
 * @brief Specify `stm32_uart_t` type as huart_gt type
 *
 */
#define GMP_PORT_HUART_T stm32_uart_t

    /**
     * @brief Setup GMP UART handle.
     * This function should be called in `peripheral_mapping.c`
     * @param huart handle of GMP handle
     * @param uart_handle STM32 handle of UART
     * @param uart_tx_dma_handle STM32 DMA handle of UART TX
     * @param uart_rx_dma_handle STM32 DMA handle of UART RX
     * @param data data buffer, DMA mode only
     * @param recv_buf data buffer, DMA mode only
     */
    void gmp_uart_setup(stm32_uart_t *huart, UART_HandleTypeDef *uart_handle, DMA_HandleTypeDef *uart_tx_dma_handle,
                        DMA_HandleTypeDef *uart_rx_dma_handle, half_duplex_ift *data_buffer, data_gt *recv_buf);

    //
    // The following function prototype is copy from gmp_csp_cport.
    // All these functions support async and sync UART transmition.
    //

    /**
     * @brief send data via UART
     * @param huart handle of UART
     * @param data half_duplex data interface
     */
    void gmp_uart_send(stm32_uart_t *huart, half_duplex_ift *data);

    /**
     * @brief receive data via UART
     * @param huart handle of UART
     * @param data half_duplex data interface
     */
    void gmp_uart_recv(stm32_uart_t *huart, half_duplex_ift *data);

    /**
     * @brief bind a duplex data buffer to UART channel.
     * @param huart handle of UART
     * @param data duplex data buffer
     */
    void gmp_uart_bind_duplex_dma(stm32_uart_t *huart, duplex_ift *data);

    /**
     * @brief start UART listen to receive routine
     * @param huart handle of UART
     */
    void gmp_uart_listen(stm32_uart_t *huart);

    /**
     * @brief Get UART listen status, return current receive bytes number.
     * @param huart
     * @return size_gt size of received bytes.
     */
    size_gt gmp_uart_get_listen_status(stm32_uart_t *huart);

    /**
     * @brief start UART consign to transmit routine.
     * @param huart handle of UART
     */
    void gmp_uart_consign(stm32_uart_t *huart);

    /**
     * @brief Get UART consign status, return if consign routine is free.
     * @param huart
     * @return fast_gt
     */
    fast_gt gmp_uart_get_consign_status(stm32_uart_t *huart);

#endif // HAL_UART_MODULE_ENABLED

// ....................................................................//
// SPI
//
// kernel functions:
// + Write
// + Read
// + ReadWrite
// + Set SPI Mode
//
#ifdef HAL_SPI_MODULE_ENABLED

    typedef struct _tag_spi_handle
    {
        // chip select
        gpio_model_stm32_t nchip_select;

        // SPI handle
        SPI_HandleTypeDef *hspi;
    } spi_handle_t;

    // length < 16
    size_gt spi_tx_direct(spi_handle_t *hspi, data_gt *data, size_gt length);

#define GMP_PORT_HSPI_T SPI_HandleTypeDef

#endif // HAL_SPI_MODULE_ENABLED

// ....................................................................//
// IIC
//
// kernel functions:
// + Write
// + Read
//
#ifdef HAL_I2C_MODULE_ENABLED

#endif // HAL_I2C_MODULE_ENABLED

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _FILE_PERIPHERAL_MODEL_STM32_H_
