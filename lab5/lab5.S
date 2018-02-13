.intel_syntax noprefix
.section .rodata

gw: .asciz "George Washington"

.section .text

//works
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

//broke
.global SelectionSort
SelectionSort:
    //for loop
    mov ecx, 0//step
    1:
        cmp ecx, esi
        jge 1f
        mov r8, rcx//smallest
        mov edx, ecx
        inc edx
        //for loop finds smallest
        2:
            cmp edx, esi
            jge 2f
            mov r9w, WORD PTR[rdi+rdx*2]//array[i]
            mov r10w, WORD PTR[rdi+r8*2]//array[smallest]
            cmp r9w, r10w
            jge 3f
                mov r8w, dx
            3:
            cmp r8w, cx
            je 4f //swap
                mov r11w, WORD PTR[rdi+rcx*2]//array[step]
                mov WORD PTR[rdi+rcx*2], r10w
                mov WORD PTR[rdi+r8*2], r11w
            4:
            inc edx
            jmp 2b
        2:
        inc ecx
        jmp 1b
    1:
    mov rax, 0
    ret

//works
.global InsertionSort
InsertionSort:
    mov rax, 1
    1:
        cmp rax, rsi
        jge 1f
        mov ecx, DWORD PTR[rdi+rax*4]
        mov rdx, rax
        dec rdx
        2:
            cmp rdx, 0
            js 2f
            mov r8d, DWORD PTR[rdi+rdx*4]
            cmp r8d, ecx
            jle 2f
            //while loop body
            mov DWORD PTR[rdi+rdx*4+4], r8d
            dec rdx
            jmp 2b
        2:
        mov DWORD PTR[rdi+rdx*4+4], ecx
        inc rax
        jmp 1b
    1:
    mov rax, 0
    ret
.global GreatestSum
GreatestSum:
    call InsertionSort
    mov edx, DWORD PTR[rdi+rsi*4-4]
    imul edx, 2
    mov DWORD PTR[rdi+rsi*4-4], edx
    mov ecx, 0
    1:
        cmp ecx, esi
        jge 1f
        add rax, []
        inc ecx
        jmp 1b
    1:
    ret
