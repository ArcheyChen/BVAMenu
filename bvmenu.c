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
#define EntriesPerPage 12
#define BytesPerEntry 32



//! Put function in IWRAM.
#define IWRAM_CODE __attribute__((section(".iwram"), long_call))

//! Put function in EWRAM.
#define EWRAM_CODE __attribute__((section(".ewram"), long_call))


int* KEYpad =     (int*)0x04000130;
char* MapperReg1 = (char*)0x0E000002;
char* MapperReg2 = (char*)0x0E000003;
char* MapperReg3 = (char*)0x0E000004;


char MapReg1=0;
char MapReg2=0;
char MapReg3=0;
char MapReg4=0;


int ROMTableStart = 0x08010000;
int ROMTableOffset=0;
int ROMpage =0;
int ROMPointer=0;
int x=0;
int y=0;
char string[]="        ";
int Keyhold=0;


IWRAM_CODE void MapperSet(char Reg1,char Reg2,char Reg3,char Reg4);

void Redraw(){
    char t=0;
            EraseScreenNoPaletteNoFlip();

        WriteStringWide( 20, 8, "Select ROM, Press A" );
        
        for (y=0;y<EntriesPerPage*10;y+=10){
            
            ROMTableOffset=ROMTableStart + (BytesPerEntry * EntriesPerPage * ROMpage) + (t*BytesPerEntry);
            t++;
            Itoa(string,ROMpage);
            WriteStringWide(0,0,"Page");
            WriteStringWide(20,0,string);
            WriteStringWide(0,24+(ROMPointer*10),">");
            WriteStringWide( 8, 24+y, (unsigned char*)ROMTableOffset );
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
    Initialize();
    Redraw();
    

    //while(1);
    
    while(1) {
        if(!((*KEYpad) & KEY_RIGHT)) {
            ROMpage++;
            ROMPointer=0;
            if (*(unsigned char*)(ROMTableStart + (BytesPerEntry * EntriesPerPage * ROMpage))==0){ROMpage--;}
            PlayNote(2000,5);
            Redraw();
            while(!((*KEYpad)& KEY_RIGHT)){Keyhold++;if(Keyhold==100000){Keyhold=0;break;}}
            }
        if(!((*KEYpad) & KEY_LEFT)) {
            ROMpage--;
            ROMPointer=0;
            if (ROMpage<0){ROMpage=0;}
            PlayNote(2000,5);
            Redraw();
            while(!((*KEYpad)& KEY_LEFT)){Keyhold++;if(Keyhold==100000){Keyhold=0;break;}}
            }
        if(!((*KEYpad) & KEY_UP)) {
            ROMPointer--;
            if (ROMPointer<0){ROMPointer=EntriesPerPage-1;}

            while(*(unsigned char*)(ROMTableStart + (BytesPerEntry * EntriesPerPage * ROMpage)+(ROMPointer*32))==0){ROMPointer--;}


            PlayNote(2000,5);
            Redraw();
            while(!((*KEYpad)& KEY_UP)){Keyhold++;if(Keyhold==50000){Keyhold=0;break;}}
            }
        if(!((*KEYpad) & KEY_DOWN)) {
            ROMPointer++;
            if (*(unsigned char*)(ROMTableStart + (BytesPerEntry * EntriesPerPage * ROMpage)+(ROMPointer*32))==0){ROMPointer=0;}

            if (ROMPointer==EntriesPerPage){ROMPointer=0;}
            PlayNote(2000,5);
            Redraw();
            while(!((*KEYpad)& KEY_DOWN)){Keyhold++;if(Keyhold==50000){Keyhold=0;break;}}
            }

            if(!((*KEYpad) & KEY_A)) {
                
                MapReg1=(*(unsigned char*)(ROMTableStart + (BytesPerEntry * EntriesPerPage * ROMpage)+(ROMPointer*32)+28));
                MapReg2=(*(unsigned char*)(ROMTableStart + (BytesPerEntry * EntriesPerPage * ROMpage)+(ROMPointer*32)+29));
                MapReg3=(*(unsigned char*)(ROMTableStart + (BytesPerEntry * EntriesPerPage * ROMpage)+(ROMPointer*32)+30));
                MapReg4=(*(unsigned char*)(ROMTableStart + (BytesPerEntry * EntriesPerPage * ROMpage)+(ROMPointer*32)+31));
                REG_IE=0;
                MapperSet(MapReg1,MapReg2,MapReg3,MapReg4);
        
        }
    


    }
    
    return 0;
}
IWRAM_CODE void MapperSet(char Reg1,char Reg2,char Reg3,char Reg4)
{
    
    u8 temp1=*(MapperReg1);
    u8 temp2=*(MapperReg2);
    u8 temp3=*(MapperReg3);
    
    *(MapperReg1)=Reg1;
    *(MapperReg2)=Reg2;
    *(MapperReg3)=Reg3;
    *(MapperReg2)=Reg2 | 0x80;
    
    *(MapperReg1)=temp1;
    *(MapperReg2)=temp2;
    *(MapperReg3)=temp3;
    
    
    __asm("SWI 0");
    return;
}
