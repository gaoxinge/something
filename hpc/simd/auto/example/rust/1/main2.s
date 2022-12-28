example::sum_iter:
  test rsi, rsi
  je .LBB0_1
  shl rsi, 2
  xorps xmm0, xmm0
  xor eax, eax
.LBB0_3:
  movss xmm1, dword ptr [rdi + rax]
  mulss xmm1, xmm1
  addss xmm0, xmm1
  add rax, 4
  cmp rsi, rax
  jne .LBB0_3
  ret
.LBB0_1:
  xorps xmm0, xmm0
  ret
