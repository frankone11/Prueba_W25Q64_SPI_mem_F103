/*
 * w25q64.c
 *
 *  Created on: Feb 16, 2024
 *      Author: paco
 */


#include "main.h"
#define __W25Q64_EXT__
#include "w25q64.h"

#define CS_ON() HAL_GPIO_WritePin(W25Q64_CS_PORT, W25Q64_CS_PIN, GPIO_PIN_RESET)
#define CS_OFF() HAL_GPIO_WritePin(W25Q64_CS_PORT, W25Q64_CS_PIN, GPIO_PIN_SET)

//#define Nop() asm("NOP")

void W25Q64_ReadMFID(ApW25Q64_IDstr id)
{
	uint8_t command[5] = {W25Q64_MANUFACTURER_ID, 0, 0, 0};
	CS_ON();
	HAL_SPI_Transmit(hspi, command, 4, HAL_MAX_DELAY);
	HAL_SPI_Receive(hspi,(uint8_t *) id, 2, HAL_MAX_DELAY);
	CS_OFF();
}

void W25Q64_ReadUniqID(uint8_t *uniqid)
{
	uint8_t command[5] = {W25Q64_READ_UNIQUE_ID, 0, 0, 0, 0};
	CS_ON();
	HAL_SPI_Transmit(hspi, command, 5, HAL_MAX_DELAY);
	HAL_SPI_Receive(hspi,uniqid, 8, HAL_MAX_DELAY);
	CS_OFF();
}

void W25Q64_SendCommand(uint8_t command)
{
	CS_ON();
	HAL_SPI_Transmit(hspi, &command, 1, HAL_MAX_DELAY);
	CS_OFF();
}

uint8_t W25Q64_ReadStatus()
{
	uint8_t retval = 0;
	uint8_t command = W25Q64_READ_STATUS_REG1;
	CS_ON();
	HAL_SPI_Transmit(hspi, &command, 1, HAL_MAX_DELAY);
	HAL_SPI_Receive(hspi, &retval, 1, HAL_MAX_DELAY);
	CS_OFF();
	return retval;
}

void W25Q64_ReadData(uint32_t address, uint8_t *buffer, uint32_t size)
{
	uint8_t command[4];
	W25Q64_Data32 adr32;
	adr32.data = address;
	command[0] = W25Q64_READ_DATA;
	command[1] = adr32.dat8.dat3;
	command[2] = adr32.dat8.dat2;
	command[3] = adr32.dat8.dat1;

	CS_ON();
	HAL_SPI_Transmit(hspi, command, 4, HAL_MAX_DELAY);
	HAL_SPI_Receive(hspi,buffer, size, HAL_MAX_DELAY);
	CS_OFF();
}

void W25Q64_FastReadData(uint32_t address, uint8_t *buffer, uint32_t size)
{
	uint8_t command[5];
	W25Q64_Data32 adr32;
	adr32.data = address;
	command[0] = W25Q64_FAST_READ;
	command[1] = adr32.dat8.dat3;
	command[2] = adr32.dat8.dat2;
	command[3] = adr32.dat8.dat1;
	command[4] = 0;

	CS_ON();
	HAL_SPI_Transmit(hspi, command, 5, HAL_MAX_DELAY);
	HAL_SPI_Receive(hspi,buffer, size, HAL_MAX_DELAY);
	CS_OFF();
}

void W25Q64_PageProgram(uint32_t address, uint8_t *buffer, uint8_t size)
{
	uint8_t command[4];
	W25Q64_Data32 adr32;
	adr32.data = address;
	command[0] = W25Q64_PAGE_PROGRAM;
	command[1] = adr32.dat8.dat3;
	command[2] = adr32.dat8.dat2;
	command[3] = adr32.dat8.dat1;

	CS_ON();
	HAL_SPI_Transmit(hspi, command, 4, HAL_MAX_DELAY);
	if(size > 0)
		HAL_SPI_Transmit(hspi, buffer, size, HAL_MAX_DELAY);
	else
		HAL_SPI_Transmit(hspi, buffer, 256, HAL_MAX_DELAY);
	CS_OFF();

	HAL_Delay(6);
}

void W25Q64_SendCommandAddress(uint8_t cmd, uint32_t address)
{
	uint8_t command[4];
	W25Q64_Data32 adr32;
	adr32.data = address;
	command[0] = cmd;
	command[1] = adr32.dat8.dat3;
	command[2] = adr32.dat8.dat2;
	command[3] = adr32.dat8.dat1;

	CS_ON();
	HAL_SPI_Transmit(hspi, command, 4, HAL_MAX_DELAY);
	CS_OFF();
}


