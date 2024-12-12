#include "flash.h"

FLASH_STATE Flash_Init(void)
{
    return FLASH_STATE_OK;
}

FLASH_STATE Flash_Get_Status()
{
    uint8_t cmd[] = {READ_STATUS_REG1_CMD};
    uint8_t status;

    Flash_Enable();

    if (HAL_SPI_Transmit(&hspi1, cmd, 1, FLASH_TIMEOUT) != HAL_OK)
    {
        printf("Flash Transmit CMD Fail! \r\n");
        return FLASH_STATE_ERROR;
    }
    if (HAL_SPI_Receive(&hspi1, &status, 1, FLASH_TIMEOUT) != HAL_OK)
    {
        printf("Flash Read Status Fail! \r\n");
        return FLASH_STATE_ERROR;
    }

    Flash_Disable();

    if ((status & FLASH_FSR_BUSY) != 0)
    {
        printf("Flash Status Register: 0x%02X\r\n", status);
        return FLASH_STATE_BUSY;
    }
    else
    {
        printf("OK Flash Status Register: 0x%02X\r\n", status);
        return FLASH_STATE_OK;
    }
}

FLASH_STATE Flash_Write_Enable()
{
    uint8_t cmd[1] = {WRITE_ENABLE_CMD};
    uint32_t tickstart = HAL_GetTick();

    Flash_Enable();

    if (HAL_SPI_Transmit(&hspi1, cmd, 1, FLASH_TIMEOUT) != HAL_OK)
    {
        printf("Flash Transmit CMD Fail! \r\n");
        return FLASH_STATE_ERROR;
    }

    Flash_Disable();

    while (Flash_Get_Status() == FLASH_STATE_BUSY)
    {
        if (HAL_GetTick() - tickstart > FLASH_TIMEOUT)
        {
            printf("WriteEnable Fail!!\r\n");
            return FLASH_STATE_TIMEOUT;
        }
        HAL_Delay(0);
    }
    printf("Write Enable Successfuly\r\n");
    return FLASH_STATE_OK;
}

void Flash_Read_ID(uint8_t *id)
{
    uint8_t cmd[4] = {READ_ID_CMD, 0x00, 0x00, 0x00};

    Flash_Enable();

    if (HAL_SPI_Transmit(&hspi1, cmd, 4, FLASH_TIMEOUT) != HAL_OK)
    {
        printf("Flash Transmit CMD Fail! \r\n");
        return;
    }
    if (HAL_SPI_Receive(&hspi1, id, 2, FLASH_TIMEOUT) != HAL_OK)
    {
        printf("Flash Read ID Fail! \r\n");
        return;
    }

    Flash_Disable();
}

FLASH_STATE Flash_Chip_Erase(void)
{
    uint8_t cmd[1] = {CHIP_ERASE_CMD};
    uint32_t tickstart = HAL_GetTick();

    Flash_Write_Enable();

    Flash_Enable();
    if (HAL_SPI_Transmit(&hspi1, cmd, 1, FLASH_TIMEOUT) != HAL_OK)
    {
        printf("Flash Erase Fail! \r\n");
        return FLASH_STATE_ERROR;
    }

    Flash_Disable();

    while (Flash_Get_Status() == FLASH_STATE_BUSY)
    {
        int i = 0;
        if (i % 100 == 0)
        {
            printf("please waiting,erase executing...\r\n");
        }
        if (i == 100000)
        {
            printf("erase timeout!\r\n");
            return FLASH_STATE_TIMEOUT;
        }
        i++;
    }

    printf("chip erase scussful!\r\n");

    return FLASH_STATE_OK;
}

void Flash_Read_Bytes(uint8_t *addr, uint8_t *bytes, uint32_t lenght)
{
    uint8_t cmd[4] = {READ_CMD, addr[0], addr[1], addr[2]};
    Flash_Enable();
    if (HAL_SPI_Transmit(&hspi1, cmd, 4, FLASH_TIMEOUT) != HAL_OK)
    {
        printf("Flash Read Bytes Fail! \r\n");
        return;
    }
    if (HAL_SPI_Receive(&hspi1, bytes, 256, FLASH_TIMEOUT) != HAL_OK)
    {
        printf("Flash Read ID Fail! \r\n");
        return;
    }
    Flash_Disable();
}