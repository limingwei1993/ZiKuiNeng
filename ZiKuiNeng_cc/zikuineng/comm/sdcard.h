#ifndef __SDCARD_H
#define __SDCARD_H

#include "DSP2833x_Device.h"     /* DSP2833x Headerfile Include File*/

typedef enum
{
/**
  * @brief  SD reponses and error flags
  */
  SD_RESPONSE_NO_ERROR      = (0x00),
  SD_IN_IDLE_STATE          = (0x01),
  SD_ERASE_RESET            = (0x02),
  SD_ILLEGAL_COMMAND        = (0x04),
  SD_COM_CRC_ERROR          = (0x08),
  SD_ERASE_SEQUENCE_ERROR   = (0x10),
  SD_ADDRESS_ERROR          = (0x20),
  SD_PARAMETER_ERROR        = (0x40),
  SD_RESPONSE_FAILURE       = (0xFF),

/**
  * @brief  Data response error
  */
  SD_DATA_OK                = (0x05),
  SD_DATA_CRC_ERROR         = (0x0B),
  SD_DATA_WRITE_ERROR       = (0x0D),
  SD_DATA_OTHER_ERROR       = (0xFF)
} SD_Error;

typedef enum
{
  NO_Card_Insert = 0,
  Card_Insert,
  Card_Init_Success,
  Fatfs_Load_Success,
  File_Open_Success,
  Card_Space_Short,
}SdCardStatus;

typedef enum
{
    SD_CMD_CRC_FAIL                    = (1), /*!< Command response received (but CRC check failed) */
    SD_DATA_CRC_FAIL                   = (2), /*!< Data bock sent/received (CRC check Failed) */
    SD_CMD_RSP_TIMEOUT                 = (3), /*!< Command response timeout */
    SD_DATA_TIMEOUT                    = (4), /*!< Data time out */
    SD_TX_UNDERRUN                     = (5), /*!< Transmit FIFO under-run */
    SD_RX_OVERRUN                      = (6), /*!< Receive FIFO over-run */
    SD_START_BIT_ERR                   = (7), /*!< Start bit not detected on all data signals in widE bus mode */
    SD_CMD_OUT_OF_RANGE                = (8), /*!< CMD's argument was out of range.*/
    SD_ADDR_MISALIGNED                 = (9), /*!< Misaligned address */
    SD_BLOCK_LEN_ERR                   = (10), /*!< Transferred block length is not allowed for the card or the number of transferred bytes does not match the block length */
    SD_ERASE_SEQ_ERR                   = (11), /*!< An error in the sequence of erase command occurs.*/
    SD_BAD_ERASE_PARAM                 = (12), /*!< An Invalid selection for erase groups */
    SD_WRITE_PROT_VIOLATION            = (13), /*!< Attempt to program a write protect block */
    SD_LOCK_UNLOCK_FAILED              = (14), /*!< Sequence or password error has been detected in unlock command or if there was an attempt to access a locked card */
    SD_COM_CRC_FAILED                  = (15), /*!< CRC check of the previous command failed */
    SD_ILLEGAL_CMD                     = (16), /*!< Command is not legal for the card state */
    SD_CARD_ECC_FAILED                 = (17), /*!< Card internal ECC was applied but failed to correct the data */
    SD_CC_ERROR                        = (18), /*!< Internal card controller error */
    SD_GENERAL_UNKNOWN_ERROR           = (19), /*!< General or Unknown error */
    SD_STREAM_READ_UNDERRUN            = (20), /*!< The card could not sustain data transfer in stream read operation. */
    SD_STREAM_WRITE_OVERRUN            = (21), /*!< The card could not sustain data programming in stream mode */
    SD_CID_CSD_OVERWRITE               = (22), /*!< CID/CSD overwrite error */
    SD_WP_ERASE_SKIP                   = (23), /*!< only partial address space was erased */
    SD_CARD_ECC_DISABLED               = (24), /*!< Command has been executed without using internal ECC */
//    SD_ERASE_RESET                     = (25), /*!< Erase sequence was cleared before executing because an out of erase sequence command was received */
    SD_AKE_SEQ_ERROR                   = (26), /*!< Error in sequence of authentication. */
    SD_INVALID_VOLTRANGE               = (27),
    SD_ADDR_OUT_OF_RANGE               = (28),
    SD_SWITCH_ERROR                    = (29),
    SD_SDIO_DISABLED                   = (30),
    SD_SDIO_FUNCTION_BUSY              = (31),
    SD_SDIO_FUNCTION_FAILED            = (32),
    SD_SDIO_UNKNOWN_FUNCTION           = (33),
    SD_INTERNAL_ERROR,
    SD_NOT_CONFIGURED,
    SD_REQUEST_PENDING,
    SD_REQUEST_NOT_APPLICABLE,
    SD_INVALID_PARAMETER,
    SD_UNSUPPORTED_FEATURE,
    SD_UNSUPPORTED_HW,
    SD_ERROR,
    SD_OK = 0
} SD_Error1;

typedef struct
{
    uint8_t  CSDStruct;            /*!< CSD structure */
    uint8_t  SysSpecVersion;       /*!< System specification version */
    uint8_t  Reserved1;            /*!< Reserved */
    uint8_t  TAAC;                 /*!< Data read access-time 1 */
    uint8_t  NSAC;                 /*!< Data read access-time 2 in CLK cycles */
    uint8_t  MaxBusClkFrec;        /*!< Max. bus clock frequency */
    uint16_t CardComdClasses;      /*!< Card command classes */
    uint8_t  RdBlockLen;           /*!< Max. read data block length */
    uint8_t  PartBlockRead;        /*!< Partial blocks for read allowed */
    uint8_t  WrBlockMisalign;      /*!< Write block misalignment */
    uint8_t  RdBlockMisalign;      /*!< Read block misalignment */
    uint8_t  DSRImpl;              /*!< DSR implemented */
    uint8_t  Reserved2;            /*!< Reserved */
    uint32_t DeviceSize;           /*!< Device Size */
    uint8_t  MaxRdCurrentVDDMin;   /*!< Max. read current @ VDD min */
    uint8_t  MaxRdCurrentVDDMax;   /*!< Max. read current @ VDD max */
    uint8_t  MaxWrCurrentVDDMin;   /*!< Max. write current @ VDD min */
    uint8_t  MaxWrCurrentVDDMax;   /*!< Max. write current @ VDD max */
    uint8_t  DeviceSizeMul;        /*!< Device size multiplier */
    uint8_t  EraseGrSize;          /*!< Erase group size */
    uint8_t  EraseGrMul;           /*!< Erase group size multiplier */
    uint8_t  WrProtectGrSize;      /*!< Write protect group size */
    uint8_t  WrProtectGrEnable;    /*!< Write protect group enable */
    uint8_t  ManDeflECC;           /*!< Manufacturer default ECC */
    uint8_t  WrSpeedFact;          /*!< Write speed factor */
    uint8_t  MaxWrBlockLen;        /*!< Max. write data block length */
    uint8_t  WriteBlockPaPartial;  /*!< Partial blocks for write allowed */
    uint8_t  Reserved3;            /*!< Reserded */
    uint8_t  ContentProtectAppli;  /*!< Content protection application */
    uint8_t  FileFormatGrouop;     /*!< File format group */
    uint8_t  CopyFlag;             /*!< Copy flag (OTP) */
    uint8_t  PermWrProtect;        /*!< Permanent write protection */
    uint8_t  TempWrProtect;        /*!< Temporary write protection */
    uint8_t  FileFormat;           /*!< File Format */
    uint8_t  ECC;                  /*!< ECC code */
    uint8_t  CSD_CRC;              /*!< CSD CRC */
    uint8_t  Reserved4;            /*!< always 1*/
} SD_CSD;

typedef struct
{
    uint8_t  ManufacturerID;       /*!< ManufacturerID */
    uint16_t OEM_AppliID;          /*!< OEM/Application ID */
    uint32_t ProdName1;            /*!< Product Name part1 */
    uint8_t  ProdName2;            /*!< Product Name part2*/
    uint8_t  ProdRev;              /*!< Product Revision */
    uint32_t ProdSN;               /*!< Product Serial Number */
    uint8_t  Reserved1;            /*!< Reserved1 */
    uint16_t ManufactDate;         /*!< Manufacturing Date */
    uint8_t  CID_CRC;              /*!< CID CRC */
    uint8_t  Reserved2;            /*!< always 1 */
} SD_CID;

typedef struct
{
  SD_CSD SD_csd;
  SD_CID SD_cid;
  long long CardCapacity;
  uint32_t CardBlockSize;
  uint16_t RCA;
  uint8_t CardType;
} SD_CardInfo;

extern SD_CardInfo SDCardInfo;

// SD¿¨Ö¸Áî±í
#define CMD0    (0x40 + 0)
#define CMD1    (0x40 + 1)
#define CMD8    (0x40 + 8)
#define CMD9    (0x40 + 9)
#define CMD10   (0x40 + 10)
#define CMD12   (0x40 + 12)
#define CMD16   (0x40 + 16)
#define CMD17   (0x40 + 17)
#define CMD18   (0x40 + 18)
#define CMD23   (0x40 + 23)
#define CMD24   (0x40 + 24)
#define CMD25   (0x40 + 25)
#define CMD41   (0x40 + 41)
#define CMD55   (0x40 + 55)
#define CMD58   (0x40 + 58)
#define CMD59   (0x40 + 59)

#define DELAY_TIME      20
#define TRY_TIME        20
#define SPI_HIGH        20  //10
#define SPI_LOW         2000   //1000

//ERROR CODE
//-------------------------------------------------------------
#define INIT_CMD0_ERROR     0x0001
#define INIT_CMD1_ERROR     0x0002
#define WRITE_BLOCK_ERROR   0x0003
#define READ_BLOCK_ERROR    0x0004
//-------------------------------------------------------------
#define RELEASE             1
#define UN_RELEASE          0


/* Card Type definitions */
#define SD_TYPE_ERR         0
#define SD_TYPE_MMC         1
#define SD_TYPE_V1          2
#define SD_TYPE_V2          3
#define SD_TYPE_V2HC        4

extern unsigned int SPI_Speed;
extern unsigned char SPI_ReadWriteByte(unsigned char data);
extern unsigned char SD_Write_Cmd(uint8_t cmd, uint32_t arg, uint8_t crc);
extern unsigned char SD_Write_Cmd_NoDeassert(uint8_t cmd, uint32_t arg, uint8_t crc);
extern unsigned char SD_Reset(void);
extern unsigned char SD_Init(void);
extern unsigned char SD_WriteSingleBlock(uint32_t sector, const uint8_t* data);
extern unsigned char SD_ReadSingleBlock(uint32_t sector, uint8_t* buffer);
extern uint8_t SD_ReceiveData(uint8_t* data, uint16_t len, uint8_t release);
extern uint8_t SD_GetCID(uint8_t* cid_data);
extern uint8_t SD_WaitReady(void);
extern unsigned char SD_WriteMultiBlock(uint32_t sector, const uint8_t* data, uint8_t count);
extern uint8_t SD_ReadMultiBlock(uint32_t sector, uint8_t* buffer, uint8_t count);
extern uint32_t SD_GetCapacity(void);
extern uint8_t SD_GetCSD(uint8_t *csd_data);

#endif


