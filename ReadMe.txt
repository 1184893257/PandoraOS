内核的代码和说明都在Core文件夹里面。
无视SETENV.BAT。这个批命令用于设置编译的环境变量。
Core\INCLUDE文件夹是包含的头文件，INC后缀的是汇编NASM的包含文件，有一些定义。
Core\PROC16文件夹是一些16位的小程序的实现部分。用%include包含里面的文件可以获取相应的功能。
Core\BOOT文件夹里面的文件是引导部分的程序，目前C的部分已经弄出来了。
Core\TOOLS文件夹里面是一些用得到的工具。
Core\BOOT\LOADER文件夹里面是16位子系统的程序。