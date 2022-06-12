# BVAMenu
威力加强版的BVMenu（BennVenn's Menu)，由Ausar添加了自动搜索游戏的功能。

支持国产蓝色山寨的多合一2048Mbit卡带，我测试用的卡带是淘宝34块钱一张的卡。

原作者：bennvenn.myshopify.com/products/gba-flash-cart-256mbyte-rom-64kbytes-sram-save-backorder?variant=39273652158567

感谢作者提供了源码，原版的代码需要手动添加菜单，而在我这一版中，会自动地以4MB的步长去搜索可能存在的游戏，并添加到菜单中去。

同时，增加了一个小修补，使得相关的备份存档软件会认为该“游戏”是SRAM存储的，这使得导出存档变为可能。

将devkitadv解压到C盘根目录，然后运行make.bat即可生成菜单。

或者直接去Release中下载我已编译好的文件。

推荐采用**GBABF**https://gitlab.com/Fexean/gbabf/-/tree/master 配合NDSL烧录使用，选择里面的Multi Rom选项，然后将游戏烧录到对应的偏移即可。

注意，卡带是以32MB为边界，因此烧录时注意游戏的位置不能横跨边界。

然后将该菜单烧录到卡带最开始的位置即可。

如果要删除游戏，那么可以用Release中附带的空白文件烧录进去，因为GBABF这玩意儿没有定点清除的功能。


要对该软件进行重新修改，请保留原作者相关信息。

### 关于存档

要使用该软件，建议购买带电池的卡带。该软件支持Sram存储的游戏。如果不增加电池，那么会丢失存档，或者你可以选择烧录那种“芯片存档”的rom进去。

但是！
1. 由于只有一块SRAM芯片，因此**在游戏之间切换**时，会使得第二个游戏覆盖第一个游戏的sram存档，造成存档丢失！
2. ~~BVAMENU在搜索游戏的过程中，**也会破坏存档**，但是我设计了一个机制就是，当启动游戏的时候，会将存档还原。也就是说，不要在菜单界面关闭电源，一定要进了游戏后再关电源，否则会损坏存档。~~
   1.1版本将BVAMenu编译成了MultiRom的形式，所有的代码均运行在eworkram中，当搜索游戏完毕后可以恢复SRAM而不破坏程序的运行。因此此时在菜单界面关闭电源也不会损坏SRAM了。
