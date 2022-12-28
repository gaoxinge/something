f(std::vector<int, std::allocator<int> >&, std::vector<int, std::allocator<int> >&, std::vector<int, std::allocator<int> >&, int):
        movsx   rax, ecx
        test    eax, eax
        jle     .L1
        mov     r8, QWORD PTR [rdi]
        mov     rdi, QWORD PTR [rsi]
        mov     rsi, QWORD PTR [rdx]
        cmp     eax, 1
        je      .L3
        lea     rcx, [rdi+4]
        mov     rdx, rsi
        sub     rdx, rcx
        cmp     rdx, 8
        jbe     .L3
        lea     rcx, [r8+4]
        mov     rdx, rsi
        sub     rdx, rcx
        cmp     rdx, 8
        jbe     .L3
        lea     edx, [rax-1]
        mov     r9d, eax
        cmp     edx, 2
        jbe     .L11
        mov     ecx, eax
        xor     edx, edx
        shr     ecx, 2
        sal     rcx, 4
.L5:
        movdqu  xmm0, XMMWORD PTR [r8+rdx]
        movdqu  xmm2, XMMWORD PTR [rdi+rdx]
        paddd   xmm0, xmm2
        movups  XMMWORD PTR [rsi+rdx], xmm0
        add     rdx, 16
        cmp     rdx, rcx
        jne     .L5
        mov     edx, eax
        and     edx, -4
        mov     ecx, edx
        cmp     eax, edx
        je      .L1
        sub     eax, edx
        mov     r9d, eax
        cmp     eax, 1
        je      .L7
.L4:
        mov     eax, ecx
        movq    xmm0, QWORD PTR [r8+rax*4]
        movq    xmm1, QWORD PTR [rdi+rax*4]
        paddd   xmm0, xmm1
        movq    QWORD PTR [rsi+rax*4], xmm0
        test    r9b, 1
        je      .L1
        and     r9d, -2
        add     edx, r9d
.L7:
        movsx   rax, edx
        mov     edx, DWORD PTR [rdi+rax*4]
        add     edx, DWORD PTR [r8+rax*4]
        mov     DWORD PTR [rsi+rax*4], edx
        ret
.L3:
        lea     rcx, [0+rax*4]
        xor     eax, eax
.L9:
        mov     edx, DWORD PTR [rdi+rax]
        add     edx, DWORD PTR [r8+rax]
        mov     DWORD PTR [rsi+rax], edx
        add     rax, 4
        cmp     rax, rcx
        jne     .L9
.L1:
        ret
.L11:
        xor     ecx, ecx
        xor     edx, edx
        jmp     .L4
