f(std::vector<int, std::allocator<int> >&, std::vector<int, std::allocator<int> >&, std::vector<int, std::allocator<int> >&):
        mov     rax, QWORD PTR [rdi]
        mov     r8, QWORD PTR [rdi+8]
        mov     r9, rsi
        mov     rcx, QWORD PTR [rsi]
        mov     rsi, QWORD PTR [rdx]
        cmp     rax, r8
        je      .L1
        mov     r9, QWORD PTR [r9+8]
        jmp     .L3
.L6:
        cmp     QWORD PTR [rdx+8], rsi
        je      .L1
        mov     edi, DWORD PTR [rcx]
        add     rax, 4
        add     edi, DWORD PTR [rax-4]
        add     rsi, 4
        mov     DWORD PTR [rsi-4], edi
        add     rcx, 4
        cmp     r8, rax
        je      .L1
.L3:
        cmp     r9, rcx
        jne     .L6
.L1:
        ret
