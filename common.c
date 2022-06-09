#include "common.h"

u8 gameCnt = 0;
int* KEYpad =     (int*)0x04000130;
char* MapperReg1 = (char*)0x0E000002;//Bank 选择信号
char* MapperReg2 = (char*)0x0E000003;// 与上0x80=Lock
char* MapperReg3 = (char*)0x0E000004;

char string[]="        ";
char Dummy_SaveType[]="SRAM_V113";