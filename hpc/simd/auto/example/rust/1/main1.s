example::f:
        cmp     rsi, rcx
        cmovb   rcx, rsi
        cmp     rcx, r9
        cmovae  rcx, r9
        test    rcx, rcx
        je      .LBB0_11
        cmp     rcx, 8
        jae     .LBB0_3
        xor     eax, eax
        jmp     .LBB0_10
.LBB0_3:
        mov     rax, rcx
        and     rax, -8
        lea     rsi, [rax - 8]
        mov     r9, rsi
        shr     r9, 3
        inc     r9
        test    rsi, rsi
        je      .LBB0_4
        mov     r10, r9
        and     r10, -2
        xor     esi, esi
.LBB0_6:
        movdqu  xmm0, xmmword ptr [rdi + 4*rsi]
        movdqu  xmm1, xmmword ptr [rdi + 4*rsi + 16]
        movdqu  xmm2, xmmword ptr [rdx + 4*rsi]
        paddd   xmm2, xmm0
        movdqu  xmm0, xmmword ptr [rdx + 4*rsi + 16]
        paddd   xmm0, xmm1
        movdqu  xmmword ptr [r8 + 4*rsi], xmm2
        movdqu  xmmword ptr [r8 + 4*rsi + 16], xmm0
        movdqu  xmm0, xmmword ptr [rdi + 4*rsi + 32]
        movdqu  xmm1, xmmword ptr [rdi + 4*rsi + 48]
        movdqu  xmm2, xmmword ptr [rdx + 4*rsi + 32]
        paddd   xmm2, xmm0
        movdqu  xmm0, xmmword ptr [rdx + 4*rsi + 48]
        paddd   xmm0, xmm1
        movdqu  xmmword ptr [r8 + 4*rsi + 32], xmm2
        movdqu  xmmword ptr [r8 + 4*rsi + 48], xmm0
        add     rsi, 16
        add     r10, -2
        jne     .LBB0_6
        test    r9b, 1
        je      .LBB0_9
.LBB0_8:
        movdqu  xmm0, xmmword ptr [rdi + 4*rsi]
        movdqu  xmm1, xmmword ptr [rdi + 4*rsi + 16]
        movdqu  xmm2, xmmword ptr [rdx + 4*rsi]
        paddd   xmm2, xmm0
        movdqu  xmm0, xmmword ptr [rdx + 4*rsi + 16]
        paddd   xmm0, xmm1
        movdqu  xmmword ptr [r8 + 4*rsi], xmm2
        movdqu  xmmword ptr [r8 + 4*rsi + 16], xmm0
.LBB0_9:
        cmp     rcx, rax
        je      .LBB0_11
.LBB0_10:
        mov     esi, dword ptr [rdx + 4*rax]
        add     esi, dword ptr [rdi + 4*rax]
        mov     dword ptr [r8 + 4*rax], esi
        lea     rsi, [rax + 1]
        mov     rax, rsi
        cmp     rcx, rsi
        jne     .LBB0_10
.LBB0_11:
        ret
.LBB0_4:
        xor     esi, esi
        test    r9b, 1
        jne     .LBB0_8
        jmp     .LBB0_9
