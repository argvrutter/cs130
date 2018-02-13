.intel_syntax noprefix
.section .rodata

gw: .asciz "George Washington"

.section .text

.global BubbleSort
BubbleSort:
    //while loop
    mov al, 0
    1:
        cmp al, 0
        jne 1f
        mov eax, 1
        mov al, 1
        //for loop
        2:
            cmp eax, esi
            jge 2f
            mov r8b, BYTE PTR [rdi-1+rax]
            mov r9b, BYTE PTR [rdi+rax]
            cmp r8b, r9b
            jle 3f
                mov BYTE PTR [rdi-1+rax], r9b
                mov BYTE PTR [rdi+rax], r8b
                mov al, 0
            3:
            inc eax
            jmp 2b
        2:
        jmp 1b
    1:
    mov rax, 0
    ret

.global SelectionSort
SelectionSort:
    //for loop
    mov ecx, 0//step
    1:
        cmp ecx, esi
        jge 1f
        mov r8w, cx
        mov edx, ecx
        inc edx
        //for loop finds smallest
        2:
            cmp edx, esi
            jge 2f
            mov r9w, WORD PTR[rdi+edx]

            3:
            inc edx
            jmp 2b
        2:
        inc ecx
        jmp 1b
    1:
    ret

.global InsertionSort
InsertionSort:

    ret
.global GreatestSum
GreatestSum:

    ret
