LINKLIST = entry.obj video.obj C_ENTRY.OBJ

all: OUT\LOADER.SYS

OUT\LOADER.SYS: $(LINKLIST)
	TLINK /x /n /3 /c $(LINKLIST), OUT\LOADER.EXE
	..\..\Tools\OUT\exe2bin -o0:7c00 OUT\LOADER.EXE OUT\LOADER.RAW
	del OUT\LOADER.EXE
	nasm final.asm -o OUT\LOADER.SYS
	del oUT\LOADER.RAW

%.OBJ: %.C
	TCC -C -G -O -c $<

%.obj: %.asm
	nasm -f obj $< -o $*.obj

clean:
	del OUT\LOADER.SYS
	del *.obj
