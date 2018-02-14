.intel_syntax noprefix

.section .text

.global BubbleSort
//void BubbleSort(char *array, int size)
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
            jle 3f //if(array[i-1] > array[i])
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
//void SelectionSort(short *array, int size)
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
            inc edx
            jmp 2b
        2:
        cmp r8w, cx
        je 4f //swap if(smallest != step)
            mov r10w, WORD PTR[rdi+r8*2]//array[smallest]
            mov r11w, WORD PTR[rdi+rcx*2]//array[step]
            mov WORD PTR[rdi+rcx*2], r10w
            mov WORD PTR[rdi+r8*2], r11w
        4:
        inc ecx
        jmp 1b
    1:
    mov rax, 0
    ret

.global InsertionSort
//void InsertionSort(int *array, int size)
InsertionSort:
    mov rax, 1
    1://for(int step=1; step<size; step++)
        cmp rax, rsi
        jge 1f
        mov ecx, DWORD PTR[rdi+rax*4]
        mov rdx, rax
        dec rdx
        2://while(i>=0 && array[i] > currentElement)
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
//long GreatestSum(int *array, int size)
GreatestSum:
    call InsertionSort
    mov edx, DWORD PTR[rdi+rsi*4-4]
    imul edx, 2 //multiplies last (and thus largest)element by 2
    mov DWORD PTR[rdi+rsi*4-4], edx
    mov ecx, 0
    1://for loop, sums elements of array
        cmp ecx, esi
        jge 1f
        movsx r8, DWORD PTR[rdi+rcx*4]
        add rax, r8
        inc ecx
        jmp 1b
    1:
    ret
