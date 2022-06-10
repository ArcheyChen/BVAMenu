
#ifndef BVHEADER_H_
#define BVHEADER_H_
#include "smgbalib.h"

#define KEY_A 1
#define KEY_B 2
#define KEY_SELECT 4
#define KEY_START 8
#define KEY_RIGHT 16
#define KEY_LEFT 32
#define KEY_UP 64
#define KEY_DOWN 128
#define KEY_R 256
#define KEY_L 512
#define EntriesPerPage 11
#define BytesPerEntry 32
#define GAME_NAME_LEN 16


struct GameEntry{
    char name[GAME_NAME_LEN + 1];
    u8 MB_offset;
}gameEntries[64];//最多64个游戏

u8 sramBackup[3];
extern char string[];
extern u8 gameCnt;
extern int* KEYpad;
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
#endif
