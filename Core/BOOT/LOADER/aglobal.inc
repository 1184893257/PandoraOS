;##############################################################################
;
;aglobal.inc
;汇编部分的共用全局头文件。设置了一些基本的设定，提供了一些宏
;并且对各个段的属性都进行了定义。
;
;##############################################################################

%ifndef	_ASSEMBLY_COMMON_HEADER_
%define	_ASSEMBLY_COMMON_HEADER_

%define	STACKSIZE	0xFFFE
%define	MODEL_NEAR

segment	_TEXT			class=CODE
segment	_DATA			class=DATA
segment	_BSS			class=BSS
segment	_STACK	STACK	class=STACK
group	DGROUP	_DATA _BSS
segment	_TEXT

%ifdef	MODEL_NEAR
	%idefine model near
	%imacro call 1
		call model %1
	%endmacro
	%imacro jmp 1
		jmp model %1
	%endmacro
	%imacro ret 0-1
		%if %0==0
			retn
		%else
			retn %1
		%endif
	%endmacro
	%idefine arg(x) (bp+4+x*2)
%elifdef MODEL_FAR
	%idefine model far
	%imacro call 1
		call model %1
	%endmacro
	%imacro jmp 1
		jmp model %1
	%endmacro
	%imacro ret 0-1
		%if %0==0
			retf
		%else
			retf %1
		%endif
	%endmacro
	%idefine arg(x) (bp+6+x*2)
%else	;MODEL_*
	%error Please define one of the model: MODEL_NEAR or MODEL_FAR
%endif	;MODEL_*

%imacro proc 1
	global %1
%1:
	push bp
	mov bp,sp
%endmacro
%imacro endproc 0-1
	pop bp
	%if %0==0
		ret
	%else
		ret %1
	%endif
%endmacro

%endif
