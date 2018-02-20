.intel_syntax noprefix
.section .rodata
 equ: .asciz  "%c = %d \n"
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
	push sil
    mov sil, '*'
	call asm_Get
	cmp rax, 0
	js 2f
	cmp rax, 20
	jge 2f
		pop sil
		mov BYTE PTR[rdi+rax*8], sil
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

    ret
