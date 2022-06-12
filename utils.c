#include "smgbalib.h"
#include "common.h"

inline void backupSram(){
    sramBackup[0] = *MapperReg1;
    sramBackup[1] = *MapperReg2;
    sramBackup[2] = *MapperReg3;
    return;
}
inline void restoreSram(){
    *(MapperReg1)=sramBackup[0];
    *(MapperReg2)=sramBackup[1];
    *(MapperReg3)=sramBackup[2];
    return;
}

IWRAM_CODE void gotoChipOffset(u8 MB_Offset,char Lock)
{
    REG_IE = 0;
    u32 chipAddr = (MB_Offset/32 * 0x10000000) + (0x4000C0 + (MB_Offset & 31) * 0x020202);
    union{
		u32 addr;
		u8 byte[4];
	}addr;
	addr.addr = chipAddr;
	u16 data = *(vu16*)(0xBD|0x8000000);
    

    u8 bankId = MB_Offset/32;
    u8 bankOffset = MB_Offset & 31;

    *(MapperReg1)=addr.byte[3];
    *(MapperReg2)=addr.byte[2];
    *(MapperReg3)=addr.byte[1];
    if(Lock)
    {
        *(MapperReg2)=addr.byte[2] | 0x80;
    }
    
    //还原

	int timeout = 0x1000;
	while(timeout && (*(vu16*)(0xBD|0x8000000)) == data)timeout--;
    
    if(Lock){//Backup is done is findGames()
        restoreSram();
        __asm("SWI 0");
    }

    return;
}
IWRAM_CODE char isGame(){
	unsigned char* nintendo_logo = (unsigned char*)0x8000004;
	unsigned long checksum = 0;
    unsigned int i;
	for(i = 0;i<0x9C;i++){
		checksum += nintendo_logo[i];
	}
	return checksum == 0x4B1B;
}


IWRAM_CODE void findGames(){
	u32 checksum = 0;
    unsigned int i;
    u16 MB_Offset;
    backupSram();
    for(MB_Offset = 4 ;MB_Offset < 256; MB_Offset += 4){\
        gotoChipOffset(MB_Offset,0);
        if(isGame()){
            vu8 *romName = (unsigned char*)0x80000A0;
            for(i=0;i<GAME_NAME_LEN;i++){
                gameEntries[gameCnt].name[i] = romName[i];
            }
            gameEntries[gameCnt].name[GAME_NAME_LEN] = 0;
            gameEntries[gameCnt].MB_offset = MB_Offset;
            gameCnt++;
        }
    }
    
    gotoChipOffset(0,0);//返回menu
    restoreSram();
    return;
}
