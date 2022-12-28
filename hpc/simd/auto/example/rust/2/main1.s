core::ptr::drop_in_place<alloc::vec::Vec<i32>>:
        mov     rsi, qword ptr [rdi + 8]
        test    rsi, rsi
        je      .LBB0_1
        mov     rdi, qword ptr [rdi]
        shl     rsi, 2
        mov     edx, 4
        jmp     qword ptr [rip + __rust_dealloc@GOTPCREL]
.LBB0_1:
        ret

example::f:
        push    rbp
        push    r15
        push    r14
        push    r13
        push    r12
        push    rbx
        sub     rsp, 24
        mov     r14, rsi
        mov     r15, rdi
        mov     r13, qword ptr [rsi]
        mov     rax, qword ptr [rsi + 16]
        mov     rbx, qword ptr [rdx]
        mov     qword ptr [rsp + 16], rdx
        mov     r12, qword ptr [rdx + 16]
        cmp     rax, r12
        cmovb   r12, rax
        test    r12, r12
        je      .LBB1_6
        mov     qword ptr [rsp + 8], r14
        movabs  rax, 2305843009213693952
        dec     rax
        xor     ebp, ebp
        cmp     r12, rax
        setbe   al
        ja      .LBB1_2
        lea     r14, [4*r12]
        mov     bpl, al
        shl     rbp, 2
        mov     rdi, r14
        mov     rsi, rbp
        call    qword ptr [rip + __rust_alloc@GOTPCREL]
        test    rax, rax
        je      .LBB1_5
        mov     qword ptr [r15], rax
        mov     qword ptr [r15 + 8], r12
        cmp     r12, 12
        jae     .LBB1_9
        xor     ecx, ecx
        mov     r14, qword ptr [rsp + 8]
.LBB1_19:
        mov     rdx, rcx
        not     rdx
        add     rdx, r12
        mov     rdi, r12
        and     rdi, 3
        je      .LBB1_20
.LBB1_21:
        lea     rsi, [rcx + 1]
        mov     ebp, dword ptr [rbx + 4*rcx]
        add     ebp, dword ptr [r13 + 4*rcx]
        mov     dword ptr [rax], ebp
        add     rax, 4
        mov     rcx, rsi
        dec     rdi
        jne     .LBB1_21
        cmp     rdx, 3
        jae     .LBB1_23
        jmp     .LBB1_25
.LBB1_6:
        mov     qword ptr [r15], 4
        mov     qword ptr [r15 + 8], 0
        jmp     .LBB1_25
.LBB1_9:
        mov     rdx, rax
        sub     rdx, r13
        xor     ecx, ecx
        cmp     rdx, 32
        mov     r14, qword ptr [rsp + 8]
        jb      .LBB1_19
        mov     rdx, rax
        sub     rdx, rbx
        cmp     rdx, 32
        jb      .LBB1_19
        mov     rcx, r12
        and     rcx, -8
        lea     rdx, [rcx - 8]
        mov     rsi, rdx
        shr     rsi, 3
        inc     rsi
        test    rdx, rdx
        je      .LBB1_12
        mov     rdi, rsi
        and     rdi, -2
        xor     edx, edx
.LBB1_14:
        movdqu  xmm0, xmmword ptr [r13 + 4*rdx]
        movdqu  xmm1, xmmword ptr [r13 + 4*rdx + 16]
        movdqu  xmm2, xmmword ptr [rbx + 4*rdx]
        paddd   xmm2, xmm0
        movdqu  xmm0, xmmword ptr [rbx + 4*rdx + 16]
        paddd   xmm0, xmm1
        movdqu  xmmword ptr [rax + 4*rdx], xmm2
        movdqu  xmmword ptr [rax + 4*rdx + 16], xmm0
        movdqu  xmm0, xmmword ptr [r13 + 4*rdx + 32]
        movdqu  xmm1, xmmword ptr [r13 + 4*rdx + 48]
        movdqu  xmm2, xmmword ptr [rbx + 4*rdx + 32]
        paddd   xmm2, xmm0
        movdqu  xmm0, xmmword ptr [rbx + 4*rdx + 48]
        paddd   xmm0, xmm1
        movdqu  xmmword ptr [rax + 4*rdx + 32], xmm2
        movdqu  xmmword ptr [rax + 4*rdx + 48], xmm0
        add     rdx, 16
        add     rdi, -2
        jne     .LBB1_14
        test    sil, 1
        je      .LBB1_17
.LBB1_16:
        movdqu  xmm0, xmmword ptr [r13 + 4*rdx]
        movdqu  xmm1, xmmword ptr [r13 + 4*rdx + 16]
        movdqu  xmm2, xmmword ptr [rbx + 4*rdx]
        paddd   xmm2, xmm0
        movdqu  xmm0, xmmword ptr [rbx + 4*rdx + 16]
        paddd   xmm0, xmm1
        movdqu  xmmword ptr [rax + 4*rdx], xmm2
        movdqu  xmmword ptr [rax + 4*rdx + 16], xmm0
.LBB1_17:
        cmp     r12, rcx
        je      .LBB1_25
        lea     rax, [rax + 4*rcx]
        jmp     .LBB1_19
.LBB1_20:
        mov     rsi, rcx
        cmp     rdx, 3
        jb      .LBB1_25
.LBB1_23:
        mov     rcx, r12
        sub     rcx, rsi
        lea     rdx, [rbx + 4*rsi]
        add     rdx, 12
        lea     rsi, [4*rsi + 12]
        add     rsi, r13
        xor     edi, edi
.LBB1_24:
        mov     ebp, dword ptr [rdx + 4*rdi - 12]
        add     ebp, dword ptr [rsi + 4*rdi - 12]
        mov     dword ptr [rax + 4*rdi], ebp
        mov     ebp, dword ptr [rdx + 4*rdi - 8]
        add     ebp, dword ptr [rsi + 4*rdi - 8]
        mov     dword ptr [rax + 4*rdi + 4], ebp
        mov     ebp, dword ptr [rdx + 4*rdi - 4]
        add     ebp, dword ptr [rsi + 4*rdi - 4]
        mov     dword ptr [rax + 4*rdi + 8], ebp
        mov     ebp, dword ptr [rdx + 4*rdi]
        add     ebp, dword ptr [rsi + 4*rdi]
        mov     dword ptr [rax + 4*rdi + 12], ebp
        add     rdi, 4
        cmp     rcx, rdi
        jne     .LBB1_24
.LBB1_25:
        mov     qword ptr [r15 + 16], r12
        mov     rax, qword ptr [rsp + 16]
        mov     rsi, qword ptr [rax + 8]
        test    rsi, rsi
        je      .LBB1_27
        shl     rsi, 2
        mov     edx, 4
        mov     rdi, rbx
        call    qword ptr [rip + __rust_dealloc@GOTPCREL]
.LBB1_27:
        mov     rsi, qword ptr [r14 + 8]
        test    rsi, rsi
        je      .LBB1_29
        shl     rsi, 2
        mov     edx, 4
        mov     rdi, r13
        call    qword ptr [rip + __rust_dealloc@GOTPCREL]
.LBB1_29:
        mov     rax, r15
        add     rsp, 24
        pop     rbx
        pop     r12
        pop     r13
        pop     r14
        pop     r15
        pop     rbp
        ret
.LBB1_12:
        xor     edx, edx
        test    sil, 1
        jne     .LBB1_16
        jmp     .LBB1_17
.LBB1_2:
        call    qword ptr [rip + alloc::raw_vec::capacity_overflow@GOTPCREL]
        jmp     .LBB1_3
.LBB1_5:
        mov     rdi, r14
        mov     rsi, rbp
        call    qword ptr [rip + alloc::alloc::handle_alloc_error@GOTPCREL]
.LBB1_3:
        ud2
        mov     rbx, rax
        mov     rdi, qword ptr [rsp + 16]
        call    core::ptr::drop_in_place<alloc::vec::Vec<i32>>
        mov     rdi, qword ptr [rsp + 8]
        call    core::ptr::drop_in_place<alloc::vec::Vec<i32>>
        mov     rdi, rbx
        call    _Unwind_Resume@PLT
        ud2
        call    qword ptr [rip + core::panicking::panic_no_unwind@GOTPCREL]
        ud2

DW.ref.rust_eh_personality:
        .quad   rust_eh_personality
