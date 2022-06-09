#include "smgbalib.h"
#include "common.h"
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
#define EntriesPerPage 12
#define BytesPerEntry 32

u8 gameCnt = 0;
int* KEYpad =     (int*)0x04000130;
char* MapperReg1 = (char*)0x0E000002;//Bank 选择信号
char* MapperReg2 = (char*)0x0E000003;// 与上0x80=Lock
char* MapperReg3 = (char*)0x0E000004;
char MapReg1=0;
char MapReg2=0;
char MapReg3=0;
char MapReg4=0;


// int ROMTableStart = 0x08010000;
// int ROMTableOffset=0;
int ROMpage =0;
int ROMPointer=0;
int x=0;
int y=0;
char string[]="        ";
char Dummy_SaveType[]="SRAM_V113";
int Keyhold=0;

// struct Entry{

// };

// IWRAM_CODE extern void MapperSet(char Reg1,char Reg2,char Reg3,char Reg4,char Lock);

void Redraw(){
        char t=0;
        int MB_Offset = 4;//前4个MB是Menu的，从4MB后开始找
        EraseScreenNoPaletteNoFlip();

        WriteStringWide( 20, 8, "Select ROM, Press A" );
        
        if(gameCnt==0){
            WriteStringWide(0,0,"No games found");
        }
        for (y=0;y<EntriesPerPage*10;y+=10){
            
            // ROMTableOffset=ROMTableStart + (BytesPerEntry * EntriesPerPage * ROMpage) + (t*BytesPerEntry);
            if(t>gameCnt)
                break;
            t++;
            Itoa(string,ROMpage);
            WriteStringWide(0,0,"Page");
            WriteStringWide(20,0,string);//第几页
            
            WriteStringWide(0,24+(ROMPointer*10),">");
            WriteStringWide( 8, 24+y, (unsigned char*)gameEntries[EntriesPerPage * ROMpage + t].name);
        }
        Keyhold=0;
        Flip();
}
int main() {
    
                // MapReg1=0x10;
                // MapReg2=0x00;
                // MapReg3=0x00;
                // MapReg4=0x80;
                // REG_IE=0;
                // MapperSet(MapReg1,MapReg2,MapReg3,MapReg4);
    // REG_IE=0;
    // gotoChipOffset(240,1);
    EraseScreenNoPaletteNoFlip();
    Initialize();
    WriteStringWide( 20, 8, "Loading Roms" );
    
    Flip();
    // // gameCnt = 1;
    // // gameEntries[0].name[0]='N';
    // // gameEntries[0].name[1]='O';
    // // gameEntries[0].name[2]='G';
    // // gameEntries[0].name[3]='M';
    // // gameEntries[0].name[4]='\0';
    findGames();
    // test();
    // EraseScreenNoPaletteNoFlip();
    // if(gameCnt>0){
    //     WriteStringWide( 20, 0, gameEntries[0].name );
    //     WriteStringWide( 20, 16, gameEntries[1].name );
    //     WriteStringWide( 20, 32, gameEntries[2].name );
    // }
    // WriteStringWide( 20, 48, "Load Roms complete" );
    // Flip();
    
    // while(1){};
    Redraw();
    while(1){};
    
    // WriteStringWide( 0, 8, "Find Games Complete" );
    //     Keyhold=0;
    //     Flip();
    // Redraw();
    

    //while(1);
    
    // while(1) {
    //     if(!((*KEYpad) & KEY_RIGHT)) {
    //         ROMpage++;
    //         ROMPointer=0;
    //         if (*(unsigned char*)(gameEntries[EntriesPerPage*ROMpage+ROMPointer].name)==0){ROMpage--;}
    //         PlayNote(2000,5);
    //         Redraw();
    //         while(!((*KEYpad)& KEY_RIGHT)){Keyhold++;if(Keyhold==100000){Keyhold=0;break;}}
    //         }
    //     if(!((*KEYpad) & KEY_LEFT)) {
    //         ROMpage--;
    //         ROMPointer=0;
    //         if (ROMpage<0){ROMpage=0;}
    //         PlayNote(2000,5);
    //         Redraw();
    //         while(!((*KEYpad)& KEY_LEFT)){Keyhold++;if(Keyhold==100000){Keyhold=0;break;}}
    //         }
    //     if(!((*KEYpad) & KEY_UP)) {
    //         ROMPointer--;
    //         if (ROMPointer<0){ROMPointer=EntriesPerPage-1;}

    //         // while(*(unsigned char*)(ROMTableStart + (BytesPerEntry * EntriesPerPage * ROMpage)+(ROMPointer*32))==0){ROMPointer--;}
    //         while(*(unsigned char*)(gameEntries[EntriesPerPage*ROMpage+ROMPointer].name)==0){ROMPointer--;}


    //         PlayNote(2000,5);
    //         Redraw();
    //         while(!((*KEYpad)& KEY_UP)){Keyhold++;if(Keyhold==50000){Keyhold=0;break;}}
    //         }
    //     if(!((*KEYpad) & KEY_DOWN)) {
    //         ROMPointer++;
    //         if (*(unsigned char*)(gameEntries[EntriesPerPage*ROMpage+ROMPointer].name)==0){ROMPointer=0;}

    //         if (ROMPointer==EntriesPerPage){ROMPointer=0;}
    //         PlayNote(2000,5);
    //         Redraw();
    //         while(!((*KEYpad)& KEY_DOWN)){Keyhold++;if(Keyhold==50000){Keyhold=0;break;}}
    //         }

    //         if(!((*KEYpad) & KEY_A)) {
    //             REG_IE=0;
    //             gotoChipOffset(gameEntries[EntriesPerPage*ROMpage+ROMPointer].MB_offset,1);
        
    //     }
    // }
    
    return 0;
}
