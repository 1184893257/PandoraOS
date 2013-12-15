all: DBRFAT12.BIN DBRFAT16.BIN DBRFAT32.BIN

%.BIN: %.ASM
	nasm -s -I./ -I../INCLUDE/ $< -o $*.BIN

clean:
	del *.BIN
