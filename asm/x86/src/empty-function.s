	.file	"empty-function.c"					; Specifies the name of the source file. This allows debuggers to correlate the compiled code with the original source file.
	.intel_syntax noprefix						; Switch assembly to Intel and return all intel registers without a '%'. The other format being AT&T, where registers are prefixed with a '$'.
	.text										; Marks the beginning of the text section, which is where the executable code is placed. Everything preceeding .text will be included within the executable's code, until another section is encountered. 
	.globl	main								; Sets the main symbol global, so that it is accessible from other symbols.
	.type	main, @function						; Tells the assembler what the type of main is. In this case, a function.
main:											; Marks the beginning of the main() function.
.LFB0:											; Marks the beginning of the main function's prologue.
	.cfi_startproc           					; Start of a new procedure for Call Frame Information (CFI)
	push	ebp             					; Save the current base pointer (ebp) value on the stack. This is done to preserve the base pointer of the calling function.
	.cfi_def_cfa_offset 8   					; Adjust the CFI definition of the stack pointer offset
	.cfi_offset 5, -8       					; Record the location of the saved ebp in CFI data
	mov	ebp, esp            					; Set up a new stack frame by making ebp point to the top of the stack
	.cfi_def_cfa_register 5 					; Update the CFI definition to reflect the new stack frame base in ebp
	call	__x86.get_pc_thunk.ax 				; Call a helper function for position-independent code
	add	eax, OFFSET FLAT:_GLOBAL_OFFSET_TABLE_ 	; Adjust eax to point to the global offset table for position-independent code
	nop                     					; No operation (often used for alignment)
	pop	ebp                						; Restore the old base pointer value from the stack
	.cfi_restore 5         						; Restore the CFI state for the ebp register
	.cfi_def_cfa 4, 4      						; Update the CFI definition to reflect the restored stack frame state
	ret                    						; Return from the function
	.cfi_endproc           						; End of the procedure for Call Frame Information (CFI)
.LFE0											; Marks the end of the main function prologue.
	.size	main, .-main
	.section	.text.__x86.get_pc_thunk.ax,"axG",@progbits,__x86.get_pc_thunk.ax,comdat
	.globl	__x86.get_pc_thunk.ax
	.hidden	__x86.get_pc_thunk.ax
	.type	__x86.get_pc_thunk.ax, @function
__x86.get_pc_thunk.ax:
.LFB1:
	.cfi_startproc
	mov	eax, DWORD PTR [esp]
	ret
	.cfi_endproc
.LFE1:
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
