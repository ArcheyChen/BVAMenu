#include "common.h"
#include "smgbalib.h"
IWRAM_CODE void gotoChipOffset(u32 chipAddr,char Lock)
{
    union{
		u32 addr;
		u8 byte[4];
	}addr;
	addr.addr = chipAddr;
	*(vu8*)0x0A000002 = addr.byte[3];
	*(vu8*)0x0A000003 = addr.byte[2];
	*(vu8*)0x0A000004 = addr.byte[1];
    
    *(MapperReg1)=addr.byte[3];
    *(MapperReg2)=addr.byte[2];
    *(MapperReg3)=addr.byte[1];
    if(Lock)
        *(MapperReg2)=addr.byte[2] | 0x80;
    
    //为什么这要重复两遍呢
    *(MapperReg1)=addr.byte[3];
    *(MapperReg2)=addr.byte[2];
    *(MapperReg3)=addr.byte[1];
    
    __asm("SWI 0");

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
    u8 MB_Offset;
    u8 i;
    for(MB_Offset = 4 ;MB_Offset < 256; MB_Offset += 4){
        u32 chipAddr = (MB_Offset/32 * 0x10000000) + (0x4000C0 + (MB_Offset & 31) * 0x20202);
        gotoChipOffset(chipAddr,0);
        if(isGame){
            char *romName = (char*)0x80000A0;
            for(i=0;i<12;i++){
                gameEntries[gameCnt].name[i] = romName[i];
            }
            gameEntries[gameCnt].name[13] = 0;
            gameEntries[gameCnt].MB_offset = MB_Offset;
            gameCnt++;
        }
    }
    gotoChipOffset(0,0);//返回menu
}