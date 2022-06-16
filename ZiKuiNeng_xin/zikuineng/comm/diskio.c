/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2016        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* Declarations of disk functions */
#include "include.h"
#include "sdcard.h"
#include "ff.h"
#include "ffconf.h"


/* Definitions of physical drive number for each drive */
#define   SD_CARD   0	/* Example: Map Ramdisk to physical drive 0 */


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	return RES_OK;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;

	switch (pdrv) {
	case SD_CARD :
		stat = SD_Init();
    break;
	}
  
  if(stat == RES_OK) return RES_OK;
  else return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	uint8_t res;
  uint8_t cycle_num = 10;
	switch (pdrv) {
    case SD_CARD :
			res=SD_ReadMultiBlock(sector,buff,count);
			while(res && cycle_num > 0)//读出错
			{
        SD_Init();	//重新初始化SD卡
        res=SD_ReadMultiBlock(sector,buff,count);
        cycle_num--;
			}
      break;
    default:
			res=1; 
	}
  if(res == 0) return RES_OK;
  else return RES_PARERR;

}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	uint8_t res;
  uint8_t cycle_num = 10;
	switch (pdrv) {
    case SD_CARD :
			res = SD_WriteMultiBlock(sector, (uint8_t*)buff, count);

			while(res && cycle_num > 0)//
			{
				SD_Init();
				res=SD_WriteMultiBlock(sector, (uint8_t*)buff, count);
				cycle_num--;
			}
    break;
	}

  if(res == 0) return RES_OK;
  else return RES_PARERR;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/
DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;

	if(pdrv == SD_CARD) 
  {
    switch(cmd)
    {
      case CTRL_SYNC:
      res = RES_OK; 
          break;	 
      case GET_SECTOR_SIZE:
      *(DWORD*)buff = 512; 
          res = RES_OK;
          break;	 
      case GET_BLOCK_SIZE:
      *(WORD*)buff = SDCardInfo.CardBlockSize;
          res = RES_OK;
          break;	 
      case GET_SECTOR_COUNT:
          *(DWORD*)buff = SDCardInfo.CardCapacity/512;
          res = RES_OK;
          break;
      default:
          res = RES_PARERR;
          break;
    }
  }
  else
    res = RES_PARERR;

	return res;
}



DWORD get_fattime (void)
{
  return 0;
}

