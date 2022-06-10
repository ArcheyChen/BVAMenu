# BVAMenu
威力加强版的BVMenu（BennVenn's Menu)，由Ausar添加了自动搜索游戏的功能。

支持国产蓝色山寨的多合一2048Mbit卡带，我测试用的卡带是淘宝34块钱一张的卡。

原作者：bennvenn.myshopify.com/products/gba-flash-cart-256mbyte-rom-64kbytes-sram-save-backorder?variant=39273652158567

感谢作者提供了源码，原版的代码需要手动添加菜单，而在我这一版中，会自动地以4MB的步长去搜索可能存在的游戏，并添加到菜单中去。

将devkitadv解压到C盘根目录，然后运行make.bat即可生成菜单。

或者直接去Release中下载我已编译好的文件。

推荐采用**GBABF**https://gitlab.com/Fexean/gbabf/-/tree/master 配合NDSL烧录使用，选择里面的Multi Rom选项，然后将游戏烧录到对应的偏移即可。

注意，卡带是以32MB为边界，因此烧录时注意游戏的位置不能横跨边界。

然后将该菜单烧录到卡带最开始的位置即可。

如果要删除游戏，那么可以用Release中附带的空白文件烧录进去，因为GBABF这玩意儿没有定点清除的功能。

要对该软件进行重新修改，请保留原作者相关信息。
