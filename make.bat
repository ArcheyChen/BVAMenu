@path=C:\devkitadv\bin

@REM Clean binaries
@cls
@del *.o
@del *.elf
@del *.gba

@REM Compile game
gcc -c -O3 bvmenu.c utils.c common.c -marm
@REM link to smgbalib
gcc -o bvmenu.elf bvmenu.o utils.o common.o smgbalib.a

@REM Translate executable to GBA rom format
objcopy -O binary bvmenu.elf bvmenu.gba


@REM Fix header
gbafix.exe bvmenu.gba -tBVAMENU -cMROM -mCN -r11 -p

@REM Clean binaries
@del *.o
@del *.elf
