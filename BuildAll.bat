@echo q|debug >nul

@cd Core\TOOLS
@call BUILD.BAT
@cd ..

@cd BOOT
@call BUILD.BAT

@cd LOADER
@call BUILD.BAT
@cd ..\..

@echo compile finished.
@pause