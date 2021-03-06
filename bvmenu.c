#include "smgbalib.h"
#include "common.h"
__attribute__ ((section(".devkitadv.config"))) int __gba_multiboot;
// MULTIBOOT
int ROMpage =0;
int ROMPointer=0;
int x=0;
int y=0;
int Keyhold=0;

void Redraw();
void keyPadSelect();
void Redraw(){
        char t=0;
        int MB_Offset = 4;//前4个MB是Menu的，从4MB后开始找
        int gameIdx = 0;
        const int menuBaseY = 20;
        EraseScreenNoPaletteNoFlip();

        WriteStringWide(5,0,"BennVenn's Menu Mod by Ausar");
        
        if(gameCnt==0){
            WriteStringWide(0,0,"No games found");
        }
        for (y=0,gameIdx=EntriesPerPage * ROMpage + t;y<EntriesPerPage*10 && gameIdx < gameCnt;y+=10,t++,gameIdx = EntriesPerPage * ROMpage + t){
            
            WriteStringWide(0,menuBaseY+(ROMPointer*10),">");
            WriteStringWide( 8, menuBaseY+y, gameEntries[EntriesPerPage * ROMpage + t].name);

            Itoa(string,gameEntries[EntriesPerPage * ROMpage + t].MB_offset);
            WriteStringWide(8+80,menuBaseY+y,string);
            WriteStringWide(8+95,menuBaseY+y,"MB");
        }
        Itoa(string,ROMpage);
        WriteStringWide(5,145,"Page");
        WriteStringWide(25,145,string);//第几页
        WriteStringWide(20, 133, "Select ROM, Press A" );
        Keyhold=0;
        Flip();
}
int main() {
    
    EraseScreenNoPaletteNoFlip();
    Initialize();
    WriteStringWide( 20, 8, "Loading Roms" );
    
    Flip();
    findGames();
    
    Redraw();
    keyPadSelect();
    
    
    return 0;
}

void keyPadSelect(){
    while(1) {
        if(!((*KEYpad) & KEY_RIGHT)) {
            ROMpage++;
            ROMPointer=0;
            if (*(unsigned char*)(gameEntries[EntriesPerPage*ROMpage+ROMPointer].name)==0){ROMpage--;}
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

            // while(*(unsigned char*)(ROMTableStart + (BytesPerEntry * EntriesPerPage * ROMpage)+(ROMPointer*32))==0){ROMPointer--;}
            while(*(unsigned char*)(gameEntries[EntriesPerPage*ROMpage+ROMPointer].name)==0){ROMPointer--;}


            PlayNote(2000,5);
            Redraw();
            while(!((*KEYpad)& KEY_UP)){Keyhold++;if(Keyhold==50000){Keyhold=0;break;}}
        }
        if(!((*KEYpad) & KEY_DOWN)) {
            ROMPointer++;
            if (*(unsigned char*)(gameEntries[EntriesPerPage*ROMpage+ROMPointer].name)==0){ROMPointer=0;}

            if (ROMPointer==EntriesPerPage){ROMPointer=0;}
            PlayNote(2000,5);
            Redraw();
            while(!((*KEYpad)& KEY_DOWN)){Keyhold++;if(Keyhold==50000){Keyhold=0;break;}}
        }

        if(!((*KEYpad) & KEY_A)) {
            REG_IE=0;
            gotoChipOffset(gameEntries[EntriesPerPage*ROMpage+ROMPointer].MB_offset,1);
        
        }
    }
}