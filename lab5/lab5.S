.intel_syntax noprefix

.section .text

.global BubbleSort
BubbleSort:
    //while loop
    1:
        mov ecx, 1
        mov al, 1
        //for loop
        2:
            cmp ecx, edx
            jge 2f
            mov r8w, BYTE PTR [rsi-1+rcx]
            mov r9w, BYTE PTR [rsi+rcx]
            cmp r8w, r9w
            jle 3f
                mov BYTE PTR [rdi-1+rax], r9w
                mov BYTE PTR [rdi+rax], r8w
                mov al, 0
            3:
            inc ecx
        2:
    1:
    mov rax, 0
    ret

.global SelectionSort
SelectionSort:

.global InsertionSort
InsertionSort:

.global GreatestSum
GreatestSum:
