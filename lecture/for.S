.intel_syntax noprefix

.section .rodata
out: .asciz "%d\n"

.section .text
.global main
main:
    //ecx is counter
    1:
        push rcx
        mov ecx, 0
        cmp ecx, 20
        jge 1f

        lea rdi, [rip+out]
        call printf@plt
        //loop body
        pop rcx
        inc ecx
        jmp 1b
    1:
    ret
