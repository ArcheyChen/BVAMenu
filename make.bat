@path=C:\devkitadv\bin

@REM Clean binaries
@cls
@del *.o
@del *.elf
@del *.gba

@REM Compile game
gcc -c -O3 bvmenu.c

@REM link to smgbalib
gcc -o bvmenu.elf bvmenu.o smgbalib.a

@REM Translate executable to GBA rom format
objcopy -O binary bvmenu.elf bvmenu.gba


@REM Fix header
gbafix.exe bvmenu.gba

@REM Clean binaries
@del *.o
@del *.elf
