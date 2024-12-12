#ifndef __Flash_H
#define __Flash_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"

/* Reset Operations */
#define RESET_ENABLE_CMD 0x66
#define RESET_MEMORY_CMD 0x99

#define ENTER_QPI_MODE_CMD 0x38
#define EXIT_QPI_MODE_CMD 0xFF

/* Identification Operations */
#define READ_ID_CMD 0x90
#define DUAL_READ_ID_CMD 0x92
#define QUAD_READ_ID_CMD 0x94
#define READ_JEDEC_ID_CMD 0x9F

/* Read Operations */
#define READ_CMD 0x03
#define FAST_READ_CMD 0x0B
#define DUAL_OUT_FAST_READ_CMD 0x3B
#define DUAL_INOUT_FAST_READ_CMD 0xBB
#define QUAD_OUT_FAST_READ_CMD 0x6B
#define QUAD_INOUT_FAST_READ_CMD 0xEB

/* Write Operations */
#define WRITE_ENABLE_CMD 0x06
#define WRITE_DISABLE_CMD 0x04

/* Register Operations */
#define READ_STATUS_REG1_CMD 0x05
#define READ_STATUS_REG2_CMD 0x35
#define READ_STATUS_REG3_CMD 0x15

#define WRITE_STATUS_REG1_CMD 0x01
#define WRITE_STATUS_REG2_CMD 0x31
#define WRITE_STATUS_REG3_CMD 0x11

/* Program Operations */
#define PAGE_PROG_CMD 0x02
#define QUAD_INPUT_PAGE_PROG_CMD 0x32

/* Erase Operations */
#define SECTOR_ERASE_CMD 0x20
#define CHIP_ERASE_CMD 0xC7

#define PROG_ERASE_RESUME_CMD 0x7A
#define PROG_ERASE_SUSPEND_CMD 0x75

#define FLASH_TIMEOUT 1000
#define FLASH_FSR_BUSY ((uint8_t)0x01) /*!< busy */
#define FLASH_FSR_WREN ((uint8_t)0x02) /*!< write enable */

#define Flash_Enable() HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);
#define Flash_Disable() HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);

    typedef enum
    {
        FLASH_STATE_OK = 0, // 闪存状态正常
        FLASH_STATE_ERROR,  // 闪存状态错误
        FLASH_STATE_BUSY,
        FLASH_STATE_TIMEOUT,
    } FLASH_STATE;

    void Flash_Read_ID(uint8_t *id);
    FLASH_STATE Flash_Chip_Erase(void);
    void Flash_Read_Bytes(uint8_t *addr, uint8_t *bytes, uint32_t lenght);
    FLASH_STATE Flash_Get_Status();

#ifdef __cplusplus
}
#endif

#endif /* __W25Qx_H */