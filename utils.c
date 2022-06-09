#include "smgbalib.h"
#include "common.h"

IWRAM_CODE void gotoChipOffset(u8 MB_Offset,char Lock)
{
    
    u32 chipAddr = (MB_Offset/32 * 0x10000000) + (0x4000C0 + (MB_Offset & 31) * 0x020202);
    union{
		u32 addr;
		u8 byte[4];
	}addr;
	addr.addr = chipAddr;
    
    u8 backup[3];
    backup[0] = *MapperReg1;
    backup[1] = *MapperReg2;
    backup[2] = *MapperReg3;

    u8 bankId = MB_Offset/32;
    u8 bankOffset = MB_Offset & 31;

    *(MapperReg1)=addr.byte[3];
    *(MapperReg2)=addr.byte[2];
    *(MapperReg3)=addr.byte[1];
    if(Lock)
        *(MapperReg2)=addr.byte[2] | 0x80;
    
    //还原
    // *(MapperReg1)=backup[0];
    // *(MapperReg2)=backup[1];
    // *(MapperReg3)=backup[2];
    
    if(Lock)
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
    u16 MB_Offset;
    u8 i;
    for(MB_Offset = 4 ;MB_Offset < 256; MB_Offset += 4){
        REG_IE = 0;
        gotoChipOffset(MB_Offset,0);
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
    
    REG_IE = 0;
    gotoChipOffset(0,0);//返回menu
    return;
}
IWRAM_CODE void test(){
    int i;
    REG_IE = 0;
    gotoChipOffset(4,0);
    if(isGame){
        char *romName = (char*)0x80000A0;
        for(i=0;i<12;i++){
            gameEntries[gameCnt].name[i] = romName[i];
        }
        gameEntries[gameCnt].name[13] = 0;
        gameEntries[gameCnt].MB_offset = 4;
        gameCnt++;
    }
    REG_IE = 0;
    gotoChipOffset(0,0);
    return;
}