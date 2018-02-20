.intel_syntax noprefix
.section .rodata
 output: .asciz  "%c = %d \n"
.section .text

//void asm_Construct(void *mymap_pointer)
.global asm_Construct
asm_Construct:
    mov rax, 0
    1://for(int i=0; i<20; i++)
        cmp rax, 20
        jge 1f
        mov BYTE PTR[rdi + rax*8], '*'
        mov DWORD PTR[rdi + rax*8 + 4], -1
        inc rax
    1:
    mov rax, 0
    ret
//void asm_Set(void *mymap_pointer, char key, int value)
.global asm_Set
asm_Set:
    call asm_Get
    cmp rax, 0
    js 1f //index >= 0
    cmp rax, 20
    jge 1f //index < 20
        mov DWORD PTR[rdi+rax*8 +4], edx
        jmp 2f
    1:
	mov sil, cl
    mov sil, '*'
	call asm_Get
	cmp rax, 0
	js 2f
	cmp rax, 20
	jge 2f
		mov BYTE PTR[rdi+rax*8], cl
		mov DWORD PTR[rdi+rax*8 +4], edx
	2:
    mov rax, 0
    ret

//int  asm_Get(const void *mymap_pointer, char key)
.global asm_Get
asm_Get:
    mov rax, 0
    1://for(int i=0; i<20; i++)
        cmp rax, 20
        jge 1f
        mov r8b, BYTE PTR[rdi+rax*8]
        cmp r8b, sil
        jne 2f
            ret
        2:
        inc rax
    1:
    mov rax, -1
    ret
//void asm_Erase(void *mymap_pointer, char key)
.global asm_Erase
asm_Erase:
    call asm_Get
	cmp rax, 0
	js 1f
	cmp rax, 20
	jge 1f
		mov BYTE PTR[rdi+rax*8], '*'
	1:
	mov rax, 0
    ret
//void asm_Print(const void *mymap_pointer)
.global asm_Print
asm_Print:
    mov r8, rdi
    mov r9, 0
    1://for(int i=0; i<20; i++)
        cmp r9, 20
        jge 1f
        mov	sil, BYTE PTR[r8+r9*8]
        mov edx, DWORD PTR[r9+r9*8 +4]
        lea	rdi, [rip+output]
        mov rax, 0
        call printf@plt
        inc r9
    1:
    mov rax, 0
    ret
