
#ifndef BVHEADER_H_
#define BVHEADER_H_
#include "smgbalib.h"

struct GameEntry{
    char name[13];
    u8 MB_offset;
}gameEntries[64];//最多64个游戏
extern char string[];
extern u8 gameCnt;
extern char* MapperReg1;
extern char* MapperReg2;
extern char* MapperReg3;
//! Put function in IWRAM.
#define IWRAM_CODE __attribute__((section(".iwram"), long_call))

//! Put function in EWRAM.
#define EWRAM_CODE __attribute__((section(".ewram"), long_call))
IWRAM_CODE void findGames();
IWRAM_CODE void gotoChipOffset(u8 MB_Offset,char Lock);
IWRAM_CODE char isGame();
IWRAM_CODE void test();
#endif
