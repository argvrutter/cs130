.intel_syntax noprefix

.section .rodata
hello: .asciz "Hello world\n"

.section .text

.global main
main:
	lea rdi, [rip+hello]
	mov rax, 0
	call printf@plt
	ret
