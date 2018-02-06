.intel_syntax noprefix

.section .rodata
hello: .asciz "Value = %1d\n"

.section .text

.global main
main:
	lea rdi, [rip+hello]
	mov rax, 0
	//12 + (7 << (2+1))
	mov rsi, 2
	add rsi, 1
	//right hand operand must be in cl register, 8bit
	//sil is lower 8 bits of rsi
	mov cl, sil
	mov rsi, 7
	shl rsi, cl 
	add rsi, 12
	mov rax, 0
	call printf@plt
	ret
