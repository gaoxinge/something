f(std::vector<int, std::allocator<int> >&, std::vector<int, std::allocator<int> >&, std::vector<int, std::allocator<int> >&, int):
        movsx   rax, ecx
        mov     r8, QWORD PTR [rdi]
        mov     rdi, QWORD PTR [rsi]
        mov     rsi, QWORD PTR [rdx]
        test    eax, eax
        jle     .L1
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
        mov     ecx, eax
        cmp     edx, 2
        jbe     .L11
        shr     ecx, 2
        xor     edx, edx
        sal     rcx, 4
.L5:
        movdqu  xmm0, XMMWORD PTR [r8+rdx]
        movdqu  xmm2, XMMWORD PTR [rdi+rdx]
        paddd   xmm0, xmm2
        movups  XMMWORD PTR [rsi+rdx], xmm0
        add     rdx, 16
        cmp     rcx, rdx
        jne     .L5
        mov     r11d, eax
        and     r11d, -4
        test    al, 3
        je      .L1
        lea     rdx, [0+r11*4]
        and     eax, 3
        lea     r10, [rdi+rdx]
        lea     r9, [r8+rdx]
        mov     ecx, eax
        add     rdx, rsi
        cmp     eax, 1
        je      .L7
.L4:
        movq    xmm0, QWORD PTR [r8+r11*4]
        movq    xmm1, QWORD PTR [rdi+r11*4]
        paddd   xmm0, xmm1
        movq    QWORD PTR [rsi+r11*4], xmm0
        test    cl, 1
        je      .L1
        and     ecx, -2
        sal     rcx, 2
        add     r10, rcx
        add     r9, rcx
        add     rdx, rcx
.L7:
        mov     eax, DWORD PTR [r10]
        add     eax, DWORD PTR [r9]
        mov     DWORD PTR [rdx], eax
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
        mov     rdx, rsi
        mov     r9, r8
        mov     r10, rdi
        xor     r11d, r11d
        jmp     .L4
