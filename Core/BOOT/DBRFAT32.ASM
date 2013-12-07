%include "SYSINF.INC"

org BOOT_ORG
bits 16

%include "BPBFAT32.INC"
Start:


times DBR_SIZE-($-$$)-2	nop
dw	FLAG_BOOTALBE
