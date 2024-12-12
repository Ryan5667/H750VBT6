#include "flash.h"
#include <stdio.h>

FLASH_STATE Flash_Init(void)
{
    return FLASH_STATE_OK;
}

void Flash_Read_ID(uint8_t *id)
{
    uint8_t cmd[4] = {READ_ID_CMD, 0x00, 0x00, 0x00};

    Flash_Enable();

    if (HAL_SPI_Transmit(&hspi1, cmd, 4, HAL_TIMEOUT) != HAL_OK)
    {
        printf("Flash Transmit CMD Fail! \r\n");
        return;
    }
    if (HAL_SPI_Receive(&hspi1, id, 2, HAL_TIMEOUT) != HAL_OK)
    {
        printf("Flash Read ID Fail! \r\n");
        return;
    }

    Flash_Disable();
}

void Flash_Chip_Erase(void)
{
    Flash_Enable();
    uint8_t cmd[1] = {CHIP_ERASE_CMD};

    if (HAL_SPI_Transmit(&hspi1, cmd, 1, HAL_TIMEOUT) != HAL_OK)
    {
        printf("Flash Erase Fail! \r\n");
        return;
    }

    printf("chip erase scussful!\r\n");

    Flash_Disable();
}
