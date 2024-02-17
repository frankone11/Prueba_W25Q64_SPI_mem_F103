/*
 * w25q64.h
 *
 *  Created on: Feb 16, 2024
 *      Author: paco
 */

#ifndef INC_W25Q64_H_
#define INC_W25Q64_H_


//Change this values for your application
#define W25Q64_CS_PORT	GPIOA
#define W25Q64_CS_PIN	GPIO_PIN_4

#ifdef __W25Q64_EXT__
extern SPI_HandleTypeDef hspi1;
#endif

#define hspi &hspi1



#define W25Q64_ID	0xEFU


//Defining the MEM SPI instructions

#define W25Q64_WRITE_ENABLE		0x06U
#define W25Q64_VSR_WRITE_ENABLE	0x50U
#define W25Q64_WRITE_DISABLE	0x04U
#define W25Q64_READ_STATUS_REG1	0x05U
#define W25Q64_READ_STATUS_REG2	0x35U
#define W25Q64_WRITE_STATUS_REG	0x01U
#define W25Q64_PAGE_PROGRAM		0x02U
#define W25Q64_SECTOR_ERASE		0x20U
#define W25Q64_BLOCK_ERASE_32	0x52U
#define W25Q64_BLOCK_ERASE_64	0xD8U
#define W25Q64_CHIP_ERASE		0x60U
#define W25Q64_ERASE_PROG_SUSP	0x75U
#define W25Q64_ERASE_PROG_RES	0x7AU
#define W25Q64_POWER_DOWN		0xB9U
#define W25Q64_READ_DATA		0x03U
#define W25Q64_FAST_READ		0x0BU
#define W25Q64_RELEASE_PDID		0xABU
#define W25Q64_MANUFACTURER_ID	0x90U
#define W25Q64_READ_UNIQUE_ID	0x4BU
#define W25Q64_READ_SPDP_REG	0x5AU
#define W25Q64_ERASE_SEC_REGS	0x44U
#define W25Q64_PROG_SEC_REGS	0x42U
#define W25Q64_READ_SEC_REGS	0x48U
#define W25Q64_ENABLE_QPI		0x38U
#define W25Q64_ENABLE_RESET		0x66U
#define W25Q64_RESET			0x99U
#define W25Q64_DISABLE_QPI		0xFFU


typedef struct _W25Q64_IDstr
{
	uint8_t ManufacturerID;
	uint8_t DevId;
} W25Q64_IDstr, *ApW25Q64_IDstr;

typedef union _W25Q64_Data32
{
	uint32_t data;
	struct
	{
		uint16_t dat1;
		uint16_t dat2;
	}dat16;
	struct
	{
		uint8_t dat1;
		uint8_t dat2;
		uint8_t dat3;
		uint8_t dat4;
	}dat8;
} W25Q64_Data32, *apW25Q64_Data32;


/**
 * @brief Function that reads the Mem ID and ManufID
 *
 * @param id pointer to the W25Q64_ID Structure
 */
void W25Q64_ReadMFID(ApW25Q64_IDstr id);

/**
 * @brief Function that reads the Mem ID
 *
 * @param uniqid vector 64 bits (8 bytes)
 */
void W25Q64_ReadUniqID(uint8_t *uniqid);

/**
 * @brief Sends a command to the Mem
 *
 * @param command to send
 */
void W25Q64_SendCommand(uint8_t command);

/**
 * @brief Sends a command and address to the Mem
 *
 * @param command to send
 * @param address to send
 */
void W25Q64_SendCommandAddress(uint8_t cmd, uint32_t address);

/**
 * @brief Reads the status register of the Mem
 */
uint8_t W25Q64_ReadStatus();

/**
 * @brief Read data from Mem
 *
 * @param address to read
 * @param buffer to store data
 * @param size of data buffer (num of bytes to read)
 */
void W25Q64_ReadData(uint32_t address, uint8_t *buffer, uint32_t size);

/**
 * @brief Read data from Mem Fast Mode
 *
 * @param address to read
 * @param buffer to store data
 * @param size of data buffer (num of bytes to read)
 */
void W25Q64_FastReadData(uint32_t address, uint8_t *buffer, uint32_t size);

/**
 * @brief Allows form one byte to 256 bytes (a page) of data to be programmed.
 *
 * @param address to read
 * @param buffer to read data
 * @param size of data buffer (max 256 bytes), CERO writes 256 bytes
 */
void W25Q64_PageProgram(uint32_t address, uint8_t *buffer, uint8_t size);



#define W25Q64_WakeUp() W25Q64_SendCommand(W25Q64_RELEASE_PDID)
#define W25Q64_WriteEnable() W25Q64_SendCommand(W25Q64_WRITE_ENABLE)
#define W25Q64_WriteDisable() W25Q64_SendCommand(W25Q64_WRITE_DISABLE)
#define W25Q64_EnableReset() W25Q64_SendCommand(W25Q64_ENABLE_RESET)
#define W25Q64_Cmd_Reset() W25Q64_SendCommand(W25Q64_RESET)
#define W25Q64_Busy() W25Q64_ReadStatus() & 1
#define W25Q64_ChipErase() W25Q64_SendCommand(W25Q64_CHIP_ERASE)
#define W25Q64_SectorErase(a) W25Q64_SendCommandAddress(W25Q64_SECTOR_ERASE, a)
#define W25Q64_BlockErase32(a) W25Q64_SendCommandAddress(W25Q64_BLOCK_ERASE_32, a)
#define W25Q64_BlockErase64(a) W25Q64_SendCommandAddress(W25Q64_BLOCK_ERASE_64, a)


#endif /* INC_W25Q64_H_ */
