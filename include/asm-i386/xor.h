multiline_comment|/*&n; * include/asm-i386/xor.h&n; *&n; * Optimized RAID-5 checksumming functions for MMX and SSE.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * You should have received a copy of the GNU General Public License&n; * (for example /usr/src/linux/COPYING); if not, write to the Free&n; * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
multiline_comment|/*&n; * High-speed RAID5 checksumming functions utilizing MMX instructions.&n; * Copyright (C) 1998 Ingo Molnar.&n; */
DECL|macro|FPU_SAVE
mdefine_line|#define FPU_SAVE&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (!(current-&gt;flags &amp; PF_USEDFPU))&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__ (&quot; clts;&bslash;n&quot;);&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__ (&quot;fsave %0; fwait&quot;: &quot;=m&quot;(fpu_save[0]));&t;&bslash;&n;  } while (0)
DECL|macro|FPU_RESTORE
mdefine_line|#define FPU_RESTORE&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__ (&quot;frstor %0&quot;: : &quot;m&quot;(fpu_save[0]));&t;&t;&bslash;&n;&t;if (!(current-&gt;flags &amp; PF_USEDFPU))&t;&t;&t;&t;&bslash;&n;&t;&t;stts();&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
DECL|macro|LD
mdefine_line|#define LD(x,y)&t;&t;&quot;       movq   8*(&quot;#x&quot;)(%1), %%mm&quot;#y&quot;   ;&bslash;n&quot;
DECL|macro|ST
mdefine_line|#define ST(x,y)&t;&t;&quot;       movq %%mm&quot;#y&quot;,   8*(&quot;#x&quot;)(%1)   ;&bslash;n&quot;
DECL|macro|XO1
mdefine_line|#define XO1(x,y)&t;&quot;       pxor   8*(&quot;#x&quot;)(%2), %%mm&quot;#y&quot;   ;&bslash;n&quot;
DECL|macro|XO2
mdefine_line|#define XO2(x,y)&t;&quot;       pxor   8*(&quot;#x&quot;)(%3), %%mm&quot;#y&quot;   ;&bslash;n&quot;
DECL|macro|XO3
mdefine_line|#define XO3(x,y)&t;&quot;       pxor   8*(&quot;#x&quot;)(%4), %%mm&quot;#y&quot;   ;&bslash;n&quot;
DECL|macro|XO4
mdefine_line|#define XO4(x,y)&t;&quot;       pxor   8*(&quot;#x&quot;)(%5), %%mm&quot;#y&quot;   ;&bslash;n&quot;
r_static
r_void
DECL|function|xor_pII_mmx_2
id|xor_pII_mmx_2
c_func
(paren
r_int
r_int
id|bytes
comma
r_int
r_int
op_star
id|p1
comma
r_int
r_int
op_star
id|p2
)paren
(brace
r_int
r_int
id|lines
op_assign
id|bytes
op_rshift
l_int|7
suffix:semicolon
r_char
id|fpu_save
(braket
l_int|108
)braket
suffix:semicolon
id|FPU_SAVE
suffix:semicolon
id|__asm__
id|__volatile__
(paren
DECL|macro|BLOCK
macro_line|#undef BLOCK
DECL|macro|BLOCK
mdefine_line|#define BLOCK(i) &bslash;&n;&t;LD(i,0)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;LD(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;LD(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;LD(i+3,3)&t;&bslash;&n;&t;XO1(i,0)&t;&t;&t;&t;&bslash;&n;&t;ST(i,0)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;XO1(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;ST(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;XO1(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;ST(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;XO1(i+3,3)&t;&bslash;&n;&t;&t;&t;&t;ST(i+3,3)
l_string|&quot; .align 32&t;&t;&t;;&bslash;n&quot;
l_string|&quot; 1:                            ;&bslash;n&quot;
id|BLOCK
c_func
(paren
l_int|0
)paren
id|BLOCK
c_func
(paren
l_int|4
)paren
id|BLOCK
c_func
(paren
l_int|8
)paren
id|BLOCK
c_func
(paren
l_int|12
)paren
l_string|&quot;       addl $128, %1         ;&bslash;n&quot;
l_string|&quot;       addl $128, %2         ;&bslash;n&quot;
l_string|&quot;       decl %0               ;&bslash;n&quot;
l_string|&quot;       jnz 1b                ;&bslash;n&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|lines
)paren
comma
l_string|&quot;r&quot;
(paren
id|p1
)paren
comma
l_string|&quot;r&quot;
(paren
id|p2
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|FPU_RESTORE
suffix:semicolon
)brace
r_static
r_void
DECL|function|xor_pII_mmx_3
id|xor_pII_mmx_3
c_func
(paren
r_int
r_int
id|bytes
comma
r_int
r_int
op_star
id|p1
comma
r_int
r_int
op_star
id|p2
comma
r_int
r_int
op_star
id|p3
)paren
(brace
r_int
r_int
id|lines
op_assign
id|bytes
op_rshift
l_int|7
suffix:semicolon
r_char
id|fpu_save
(braket
l_int|108
)braket
suffix:semicolon
id|FPU_SAVE
suffix:semicolon
id|__asm__
id|__volatile__
(paren
DECL|macro|BLOCK
macro_line|#undef BLOCK
DECL|macro|BLOCK
mdefine_line|#define BLOCK(i) &bslash;&n;&t;LD(i,0)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;LD(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;LD(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;LD(i+3,3)&t;&bslash;&n;&t;XO1(i,0)&t;&t;&t;&t;&bslash;&n;&t;&t;XO1(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;XO1(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;XO1(i+3,3)&t;&bslash;&n;&t;XO2(i,0)&t;&t;&t;&t;&bslash;&n;&t;ST(i,0)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;XO2(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;ST(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;XO2(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;ST(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;XO2(i+3,3)&t;&bslash;&n;&t;&t;&t;&t;ST(i+3,3)
l_string|&quot; .align 32&t;&t;&t;;&bslash;n&quot;
l_string|&quot; 1:                            ;&bslash;n&quot;
id|BLOCK
c_func
(paren
l_int|0
)paren
id|BLOCK
c_func
(paren
l_int|4
)paren
id|BLOCK
c_func
(paren
l_int|8
)paren
id|BLOCK
c_func
(paren
l_int|12
)paren
l_string|&quot;       addl $128, %1         ;&bslash;n&quot;
l_string|&quot;       addl $128, %2         ;&bslash;n&quot;
l_string|&quot;       addl $128, %3         ;&bslash;n&quot;
l_string|&quot;       decl %0               ;&bslash;n&quot;
l_string|&quot;       jnz 1b                ;&bslash;n&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|lines
)paren
comma
l_string|&quot;r&quot;
(paren
id|p1
)paren
comma
l_string|&quot;r&quot;
(paren
id|p2
)paren
comma
l_string|&quot;r&quot;
(paren
id|p3
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|FPU_RESTORE
suffix:semicolon
)brace
r_static
r_void
DECL|function|xor_pII_mmx_4
id|xor_pII_mmx_4
c_func
(paren
r_int
r_int
id|bytes
comma
r_int
r_int
op_star
id|p1
comma
r_int
r_int
op_star
id|p2
comma
r_int
r_int
op_star
id|p3
comma
r_int
r_int
op_star
id|p4
)paren
(brace
r_int
r_int
id|lines
op_assign
id|bytes
op_rshift
l_int|7
suffix:semicolon
r_char
id|fpu_save
(braket
l_int|108
)braket
suffix:semicolon
id|FPU_SAVE
suffix:semicolon
id|__asm__
id|__volatile__
(paren
DECL|macro|BLOCK
macro_line|#undef BLOCK
DECL|macro|BLOCK
mdefine_line|#define BLOCK(i) &bslash;&n;&t;LD(i,0)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;LD(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;LD(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;LD(i+3,3)&t;&bslash;&n;&t;XO1(i,0)&t;&t;&t;&t;&bslash;&n;&t;&t;XO1(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;XO1(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;XO1(i+3,3)&t;&bslash;&n;&t;XO2(i,0)&t;&t;&t;&t;&bslash;&n;&t;&t;XO2(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;XO2(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;XO2(i+3,3)&t;&bslash;&n;&t;XO3(i,0)&t;&t;&t;&t;&bslash;&n;&t;ST(i,0)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;XO3(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;ST(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;XO3(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;ST(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;XO3(i+3,3)&t;&bslash;&n;&t;&t;&t;&t;ST(i+3,3)
l_string|&quot; .align 32&t;&t;&t;;&bslash;n&quot;
l_string|&quot; 1:                            ;&bslash;n&quot;
id|BLOCK
c_func
(paren
l_int|0
)paren
id|BLOCK
c_func
(paren
l_int|4
)paren
id|BLOCK
c_func
(paren
l_int|8
)paren
id|BLOCK
c_func
(paren
l_int|12
)paren
l_string|&quot;       addl $128, %1         ;&bslash;n&quot;
l_string|&quot;       addl $128, %2         ;&bslash;n&quot;
l_string|&quot;       addl $128, %3         ;&bslash;n&quot;
l_string|&quot;       addl $128, %4         ;&bslash;n&quot;
l_string|&quot;       decl %0               ;&bslash;n&quot;
l_string|&quot;       jnz 1b                ;&bslash;n&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|lines
)paren
comma
l_string|&quot;r&quot;
(paren
id|p1
)paren
comma
l_string|&quot;r&quot;
(paren
id|p2
)paren
comma
l_string|&quot;r&quot;
(paren
id|p3
)paren
comma
l_string|&quot;r&quot;
(paren
id|p4
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|FPU_RESTORE
suffix:semicolon
)brace
r_static
r_void
DECL|function|xor_pII_mmx_5
id|xor_pII_mmx_5
c_func
(paren
r_int
r_int
id|bytes
comma
r_int
r_int
op_star
id|p1
comma
r_int
r_int
op_star
id|p2
comma
r_int
r_int
op_star
id|p3
comma
r_int
r_int
op_star
id|p4
comma
r_int
r_int
op_star
id|p5
)paren
(brace
r_int
r_int
id|lines
op_assign
id|bytes
op_rshift
l_int|7
suffix:semicolon
r_char
id|fpu_save
(braket
l_int|108
)braket
suffix:semicolon
id|FPU_SAVE
suffix:semicolon
id|__asm__
id|__volatile__
(paren
DECL|macro|BLOCK
macro_line|#undef BLOCK
DECL|macro|BLOCK
mdefine_line|#define BLOCK(i) &bslash;&n;&t;LD(i,0)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;LD(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;LD(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;LD(i+3,3)&t;&bslash;&n;&t;XO1(i,0)&t;&t;&t;&t;&bslash;&n;&t;&t;XO1(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;XO1(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;XO1(i+3,3)&t;&bslash;&n;&t;XO2(i,0)&t;&t;&t;&t;&bslash;&n;&t;&t;XO2(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;XO2(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;XO2(i+3,3)&t;&bslash;&n;&t;XO3(i,0)&t;&t;&t;&t;&bslash;&n;&t;&t;XO3(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;XO3(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;XO3(i+3,3)&t;&bslash;&n;&t;XO4(i,0)&t;&t;&t;&t;&bslash;&n;&t;ST(i,0)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;XO4(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;ST(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;XO4(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;ST(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;XO4(i+3,3)&t;&bslash;&n;&t;&t;&t;&t;ST(i+3,3)
l_string|&quot; .align 32&t;&t;&t;;&bslash;n&quot;
l_string|&quot; 1:                            ;&bslash;n&quot;
id|BLOCK
c_func
(paren
l_int|0
)paren
id|BLOCK
c_func
(paren
l_int|4
)paren
id|BLOCK
c_func
(paren
l_int|8
)paren
id|BLOCK
c_func
(paren
l_int|12
)paren
l_string|&quot;       addl $128, %1         ;&bslash;n&quot;
l_string|&quot;       addl $128, %2         ;&bslash;n&quot;
l_string|&quot;       addl $128, %3         ;&bslash;n&quot;
l_string|&quot;       addl $128, %4         ;&bslash;n&quot;
l_string|&quot;       addl $128, %5         ;&bslash;n&quot;
l_string|&quot;       decl %0               ;&bslash;n&quot;
l_string|&quot;       jnz 1b                ;&bslash;n&quot;
suffix:colon
suffix:colon
l_string|&quot;g&quot;
(paren
id|lines
)paren
comma
l_string|&quot;r&quot;
(paren
id|p1
)paren
comma
l_string|&quot;r&quot;
(paren
id|p2
)paren
comma
l_string|&quot;r&quot;
(paren
id|p3
)paren
comma
l_string|&quot;r&quot;
(paren
id|p4
)paren
comma
l_string|&quot;r&quot;
(paren
id|p5
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|FPU_RESTORE
suffix:semicolon
)brace
DECL|macro|LD
macro_line|#undef LD
DECL|macro|XO1
macro_line|#undef XO1
DECL|macro|XO2
macro_line|#undef XO2
DECL|macro|XO3
macro_line|#undef XO3
DECL|macro|XO4
macro_line|#undef XO4
DECL|macro|ST
macro_line|#undef ST
DECL|macro|BLOCK
macro_line|#undef BLOCK
r_static
r_void
DECL|function|xor_p5_mmx_2
id|xor_p5_mmx_2
c_func
(paren
r_int
r_int
id|bytes
comma
r_int
r_int
op_star
id|p1
comma
r_int
r_int
op_star
id|p2
)paren
(brace
r_int
r_int
id|lines
op_assign
id|bytes
op_rshift
l_int|6
suffix:semicolon
r_char
id|fpu_save
(braket
l_int|108
)braket
suffix:semicolon
id|FPU_SAVE
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot; .align 32&t;             ;&bslash;n&quot;
l_string|&quot; 1:                         ;&bslash;n&quot;
l_string|&quot;       movq   (%1), %%mm0   ;&bslash;n&quot;
l_string|&quot;       movq  8(%1), %%mm1   ;&bslash;n&quot;
l_string|&quot;       pxor   (%2), %%mm0   ;&bslash;n&quot;
l_string|&quot;       movq 16(%1), %%mm2   ;&bslash;n&quot;
l_string|&quot;       movq %%mm0,   (%1)   ;&bslash;n&quot;
l_string|&quot;       pxor  8(%2), %%mm1   ;&bslash;n&quot;
l_string|&quot;       movq 24(%1), %%mm3   ;&bslash;n&quot;
l_string|&quot;       movq %%mm1,  8(%1)   ;&bslash;n&quot;
l_string|&quot;       pxor 16(%2), %%mm2   ;&bslash;n&quot;
l_string|&quot;       movq 32(%1), %%mm4   ;&bslash;n&quot;
l_string|&quot;       movq %%mm2, 16(%1)   ;&bslash;n&quot;
l_string|&quot;       pxor 24(%2), %%mm3   ;&bslash;n&quot;
l_string|&quot;       movq 40(%1), %%mm5   ;&bslash;n&quot;
l_string|&quot;       movq %%mm3, 24(%1)   ;&bslash;n&quot;
l_string|&quot;       pxor 32(%2), %%mm4   ;&bslash;n&quot;
l_string|&quot;       movq 48(%1), %%mm6   ;&bslash;n&quot;
l_string|&quot;       movq %%mm4, 32(%1)   ;&bslash;n&quot;
l_string|&quot;       pxor 40(%2), %%mm5   ;&bslash;n&quot;
l_string|&quot;       movq 56(%1), %%mm7   ;&bslash;n&quot;
l_string|&quot;       movq %%mm5, 40(%1)   ;&bslash;n&quot;
l_string|&quot;       pxor 48(%2), %%mm6   ;&bslash;n&quot;
l_string|&quot;       pxor 56(%2), %%mm7   ;&bslash;n&quot;
l_string|&quot;       movq %%mm6, 48(%1)   ;&bslash;n&quot;
l_string|&quot;       movq %%mm7, 56(%1)   ;&bslash;n&quot;
l_string|&quot;       addl $64, %1         ;&bslash;n&quot;
l_string|&quot;       addl $64, %2         ;&bslash;n&quot;
l_string|&quot;       decl %0              ;&bslash;n&quot;
l_string|&quot;       jnz 1b               ;&bslash;n&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|lines
)paren
comma
l_string|&quot;r&quot;
(paren
id|p1
)paren
comma
l_string|&quot;r&quot;
(paren
id|p2
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|FPU_RESTORE
suffix:semicolon
)brace
r_static
r_void
DECL|function|xor_p5_mmx_3
id|xor_p5_mmx_3
c_func
(paren
r_int
r_int
id|bytes
comma
r_int
r_int
op_star
id|p1
comma
r_int
r_int
op_star
id|p2
comma
r_int
r_int
op_star
id|p3
)paren
(brace
r_int
r_int
id|lines
op_assign
id|bytes
op_rshift
l_int|6
suffix:semicolon
r_char
id|fpu_save
(braket
l_int|108
)braket
suffix:semicolon
id|FPU_SAVE
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot; .align 32,0x90             ;&bslash;n&quot;
l_string|&quot; 1:                         ;&bslash;n&quot;
l_string|&quot;       movq   (%1), %%mm0   ;&bslash;n&quot;
l_string|&quot;       movq  8(%1), %%mm1   ;&bslash;n&quot;
l_string|&quot;       pxor   (%2), %%mm0   ;&bslash;n&quot;
l_string|&quot;       movq 16(%1), %%mm2   ;&bslash;n&quot;
l_string|&quot;       pxor  8(%2), %%mm1   ;&bslash;n&quot;
l_string|&quot;       pxor   (%3), %%mm0   ;&bslash;n&quot;
l_string|&quot;       pxor 16(%2), %%mm2   ;&bslash;n&quot;
l_string|&quot;       movq %%mm0,   (%1)   ;&bslash;n&quot;
l_string|&quot;       pxor  8(%3), %%mm1   ;&bslash;n&quot;
l_string|&quot;       pxor 16(%3), %%mm2   ;&bslash;n&quot;
l_string|&quot;       movq 24(%1), %%mm3   ;&bslash;n&quot;
l_string|&quot;       movq %%mm1,  8(%1)   ;&bslash;n&quot;
l_string|&quot;       movq 32(%1), %%mm4   ;&bslash;n&quot;
l_string|&quot;       movq 40(%1), %%mm5   ;&bslash;n&quot;
l_string|&quot;       pxor 24(%2), %%mm3   ;&bslash;n&quot;
l_string|&quot;       movq %%mm2, 16(%1)   ;&bslash;n&quot;
l_string|&quot;       pxor 32(%2), %%mm4   ;&bslash;n&quot;
l_string|&quot;       pxor 24(%3), %%mm3   ;&bslash;n&quot;
l_string|&quot;       pxor 40(%2), %%mm5   ;&bslash;n&quot;
l_string|&quot;       movq %%mm3, 24(%1)   ;&bslash;n&quot;
l_string|&quot;       pxor 32(%3), %%mm4   ;&bslash;n&quot;
l_string|&quot;       pxor 40(%3), %%mm5   ;&bslash;n&quot;
l_string|&quot;       movq 48(%1), %%mm6   ;&bslash;n&quot;
l_string|&quot;       movq %%mm4, 32(%1)   ;&bslash;n&quot;
l_string|&quot;       movq 56(%1), %%mm7   ;&bslash;n&quot;
l_string|&quot;       pxor 48(%2), %%mm6   ;&bslash;n&quot;
l_string|&quot;       movq %%mm5, 40(%1)   ;&bslash;n&quot;
l_string|&quot;       pxor 56(%2), %%mm7   ;&bslash;n&quot;
l_string|&quot;       pxor 48(%3), %%mm6   ;&bslash;n&quot;
l_string|&quot;       pxor 56(%3), %%mm7   ;&bslash;n&quot;
l_string|&quot;       movq %%mm6, 48(%1)   ;&bslash;n&quot;
l_string|&quot;       movq %%mm7, 56(%1)   ;&bslash;n&quot;
l_string|&quot;       addl $64, %1         ;&bslash;n&quot;
l_string|&quot;       addl $64, %2         ;&bslash;n&quot;
l_string|&quot;       addl $64, %3         ;&bslash;n&quot;
l_string|&quot;       decl %0              ;&bslash;n&quot;
l_string|&quot;       jnz 1b               ;&bslash;n&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|lines
)paren
comma
l_string|&quot;r&quot;
(paren
id|p1
)paren
comma
l_string|&quot;r&quot;
(paren
id|p2
)paren
comma
l_string|&quot;r&quot;
(paren
id|p3
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|FPU_RESTORE
suffix:semicolon
)brace
r_static
r_void
DECL|function|xor_p5_mmx_4
id|xor_p5_mmx_4
c_func
(paren
r_int
r_int
id|bytes
comma
r_int
r_int
op_star
id|p1
comma
r_int
r_int
op_star
id|p2
comma
r_int
r_int
op_star
id|p3
comma
r_int
r_int
op_star
id|p4
)paren
(brace
r_int
r_int
id|lines
op_assign
id|bytes
op_rshift
l_int|6
suffix:semicolon
r_char
id|fpu_save
(braket
l_int|108
)braket
suffix:semicolon
id|FPU_SAVE
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot; .align 32,0x90             ;&bslash;n&quot;
l_string|&quot; 1:                         ;&bslash;n&quot;
l_string|&quot;       movq   (%1), %%mm0   ;&bslash;n&quot;
l_string|&quot;       movq  8(%1), %%mm1   ;&bslash;n&quot;
l_string|&quot;       pxor   (%2), %%mm0   ;&bslash;n&quot;
l_string|&quot;       movq 16(%1), %%mm2   ;&bslash;n&quot;
l_string|&quot;       pxor  8(%2), %%mm1   ;&bslash;n&quot;
l_string|&quot;       pxor   (%3), %%mm0   ;&bslash;n&quot;
l_string|&quot;       pxor 16(%2), %%mm2   ;&bslash;n&quot;
l_string|&quot;       pxor  8(%3), %%mm1   ;&bslash;n&quot;
l_string|&quot;       pxor   (%4), %%mm0   ;&bslash;n&quot;
l_string|&quot;       movq 24(%1), %%mm3   ;&bslash;n&quot;
l_string|&quot;       pxor 16(%3), %%mm2   ;&bslash;n&quot;
l_string|&quot;       pxor  8(%4), %%mm1   ;&bslash;n&quot;
l_string|&quot;       movq %%mm0,   (%1)   ;&bslash;n&quot;
l_string|&quot;       movq 32(%1), %%mm4   ;&bslash;n&quot;
l_string|&quot;       pxor 24(%2), %%mm3   ;&bslash;n&quot;
l_string|&quot;       pxor 16(%4), %%mm2   ;&bslash;n&quot;
l_string|&quot;       movq %%mm1,  8(%1)   ;&bslash;n&quot;
l_string|&quot;       movq 40(%1), %%mm5   ;&bslash;n&quot;
l_string|&quot;       pxor 32(%2), %%mm4   ;&bslash;n&quot;
l_string|&quot;       pxor 24(%3), %%mm3   ;&bslash;n&quot;
l_string|&quot;       movq %%mm2, 16(%1)   ;&bslash;n&quot;
l_string|&quot;       pxor 40(%2), %%mm5   ;&bslash;n&quot;
l_string|&quot;       pxor 32(%3), %%mm4   ;&bslash;n&quot;
l_string|&quot;       pxor 24(%4), %%mm3   ;&bslash;n&quot;
l_string|&quot;       movq %%mm3, 24(%1)   ;&bslash;n&quot;
l_string|&quot;       movq 56(%1), %%mm7   ;&bslash;n&quot;
l_string|&quot;       movq 48(%1), %%mm6   ;&bslash;n&quot;
l_string|&quot;       pxor 40(%3), %%mm5   ;&bslash;n&quot;
l_string|&quot;       pxor 32(%4), %%mm4   ;&bslash;n&quot;
l_string|&quot;       pxor 48(%2), %%mm6   ;&bslash;n&quot;
l_string|&quot;       movq %%mm4, 32(%1)   ;&bslash;n&quot;
l_string|&quot;       pxor 56(%2), %%mm7   ;&bslash;n&quot;
l_string|&quot;       pxor 40(%4), %%mm5   ;&bslash;n&quot;
l_string|&quot;       pxor 48(%3), %%mm6   ;&bslash;n&quot;
l_string|&quot;       pxor 56(%3), %%mm7   ;&bslash;n&quot;
l_string|&quot;       movq %%mm5, 40(%1)   ;&bslash;n&quot;
l_string|&quot;       pxor 48(%4), %%mm6   ;&bslash;n&quot;
l_string|&quot;       pxor 56(%4), %%mm7   ;&bslash;n&quot;
l_string|&quot;       movq %%mm6, 48(%1)   ;&bslash;n&quot;
l_string|&quot;       movq %%mm7, 56(%1)   ;&bslash;n&quot;
l_string|&quot;       addl $64, %1         ;&bslash;n&quot;
l_string|&quot;       addl $64, %2         ;&bslash;n&quot;
l_string|&quot;       addl $64, %3         ;&bslash;n&quot;
l_string|&quot;       addl $64, %4         ;&bslash;n&quot;
l_string|&quot;       decl %0              ;&bslash;n&quot;
l_string|&quot;       jnz 1b               ;&bslash;n&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|lines
)paren
comma
l_string|&quot;r&quot;
(paren
id|p1
)paren
comma
l_string|&quot;r&quot;
(paren
id|p2
)paren
comma
l_string|&quot;r&quot;
(paren
id|p3
)paren
comma
l_string|&quot;r&quot;
(paren
id|p4
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|FPU_RESTORE
suffix:semicolon
)brace
r_static
r_void
DECL|function|xor_p5_mmx_5
id|xor_p5_mmx_5
c_func
(paren
r_int
r_int
id|bytes
comma
r_int
r_int
op_star
id|p1
comma
r_int
r_int
op_star
id|p2
comma
r_int
r_int
op_star
id|p3
comma
r_int
r_int
op_star
id|p4
comma
r_int
r_int
op_star
id|p5
)paren
(brace
r_int
r_int
id|lines
op_assign
id|bytes
op_rshift
l_int|6
suffix:semicolon
r_char
id|fpu_save
(braket
l_int|108
)braket
suffix:semicolon
id|FPU_SAVE
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot; .align 32,0x90             ;&bslash;n&quot;
l_string|&quot; 1:                         ;&bslash;n&quot;
l_string|&quot;       movq   (%1), %%mm0   ;&bslash;n&quot;
l_string|&quot;       movq  8(%1), %%mm1   ;&bslash;n&quot;
l_string|&quot;       pxor   (%2), %%mm0   ;&bslash;n&quot;
l_string|&quot;       pxor  8(%2), %%mm1   ;&bslash;n&quot;
l_string|&quot;       movq 16(%1), %%mm2   ;&bslash;n&quot;
l_string|&quot;       pxor   (%3), %%mm0   ;&bslash;n&quot;
l_string|&quot;       pxor  8(%3), %%mm1   ;&bslash;n&quot;
l_string|&quot;       pxor 16(%2), %%mm2   ;&bslash;n&quot;
l_string|&quot;       pxor   (%4), %%mm0   ;&bslash;n&quot;
l_string|&quot;       pxor  8(%4), %%mm1   ;&bslash;n&quot;
l_string|&quot;       pxor 16(%3), %%mm2   ;&bslash;n&quot;
l_string|&quot;       movq 24(%1), %%mm3   ;&bslash;n&quot;
l_string|&quot;       pxor   (%5), %%mm0   ;&bslash;n&quot;
l_string|&quot;       pxor  8(%5), %%mm1   ;&bslash;n&quot;
l_string|&quot;       movq %%mm0,   (%1)   ;&bslash;n&quot;
l_string|&quot;       pxor 16(%4), %%mm2   ;&bslash;n&quot;
l_string|&quot;       pxor 24(%2), %%mm3   ;&bslash;n&quot;
l_string|&quot;       movq %%mm1,  8(%1)   ;&bslash;n&quot;
l_string|&quot;       pxor 16(%5), %%mm2   ;&bslash;n&quot;
l_string|&quot;       pxor 24(%3), %%mm3   ;&bslash;n&quot;
l_string|&quot;       movq 32(%1), %%mm4   ;&bslash;n&quot;
l_string|&quot;       movq %%mm2, 16(%1)   ;&bslash;n&quot;
l_string|&quot;       pxor 24(%4), %%mm3   ;&bslash;n&quot;
l_string|&quot;       pxor 32(%2), %%mm4   ;&bslash;n&quot;
l_string|&quot;       movq 40(%1), %%mm5   ;&bslash;n&quot;
l_string|&quot;       pxor 24(%5), %%mm3   ;&bslash;n&quot;
l_string|&quot;       pxor 32(%3), %%mm4   ;&bslash;n&quot;
l_string|&quot;       pxor 40(%2), %%mm5   ;&bslash;n&quot;
l_string|&quot;       movq %%mm3, 24(%1)   ;&bslash;n&quot;
l_string|&quot;       pxor 32(%4), %%mm4   ;&bslash;n&quot;
l_string|&quot;       pxor 40(%3), %%mm5   ;&bslash;n&quot;
l_string|&quot;       movq 48(%1), %%mm6   ;&bslash;n&quot;
l_string|&quot;       movq 56(%1), %%mm7   ;&bslash;n&quot;
l_string|&quot;       pxor 32(%5), %%mm4   ;&bslash;n&quot;
l_string|&quot;       pxor 40(%4), %%mm5   ;&bslash;n&quot;
l_string|&quot;       pxor 48(%2), %%mm6   ;&bslash;n&quot;
l_string|&quot;       pxor 56(%2), %%mm7   ;&bslash;n&quot;
l_string|&quot;       movq %%mm4, 32(%1)   ;&bslash;n&quot;
l_string|&quot;       pxor 48(%3), %%mm6   ;&bslash;n&quot;
l_string|&quot;       pxor 56(%3), %%mm7   ;&bslash;n&quot;
l_string|&quot;       pxor 40(%5), %%mm5   ;&bslash;n&quot;
l_string|&quot;       pxor 48(%4), %%mm6   ;&bslash;n&quot;
l_string|&quot;       pxor 56(%4), %%mm7   ;&bslash;n&quot;
l_string|&quot;       movq %%mm5, 40(%1)   ;&bslash;n&quot;
l_string|&quot;       pxor 48(%5), %%mm6   ;&bslash;n&quot;
l_string|&quot;       pxor 56(%5), %%mm7   ;&bslash;n&quot;
l_string|&quot;       movq %%mm6, 48(%1)   ;&bslash;n&quot;
l_string|&quot;       movq %%mm7, 56(%1)   ;&bslash;n&quot;
l_string|&quot;       addl $64, %1         ;&bslash;n&quot;
l_string|&quot;       addl $64, %2         ;&bslash;n&quot;
l_string|&quot;       addl $64, %3         ;&bslash;n&quot;
l_string|&quot;       addl $64, %4         ;&bslash;n&quot;
l_string|&quot;       addl $64, %5         ;&bslash;n&quot;
l_string|&quot;       decl %0              ;&bslash;n&quot;
l_string|&quot;       jnz 1b               ;&bslash;n&quot;
suffix:colon
suffix:colon
l_string|&quot;g&quot;
(paren
id|lines
)paren
comma
l_string|&quot;r&quot;
(paren
id|p1
)paren
comma
l_string|&quot;r&quot;
(paren
id|p2
)paren
comma
l_string|&quot;r&quot;
(paren
id|p3
)paren
comma
l_string|&quot;r&quot;
(paren
id|p4
)paren
comma
l_string|&quot;r&quot;
(paren
id|p5
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|FPU_RESTORE
suffix:semicolon
)brace
DECL|variable|xor_block_pII_mmx
r_static
r_struct
id|xor_block_template
id|xor_block_pII_mmx
op_assign
(brace
id|name
suffix:colon
l_string|&quot;pII_mmx&quot;
comma
id|do_2
suffix:colon
id|xor_pII_mmx_2
comma
id|do_3
suffix:colon
id|xor_pII_mmx_3
comma
id|do_4
suffix:colon
id|xor_pII_mmx_4
comma
id|do_5
suffix:colon
id|xor_pII_mmx_5
comma
)brace
suffix:semicolon
DECL|variable|xor_block_p5_mmx
r_static
r_struct
id|xor_block_template
id|xor_block_p5_mmx
op_assign
(brace
id|name
suffix:colon
l_string|&quot;p5_mmx&quot;
comma
id|do_2
suffix:colon
id|xor_p5_mmx_2
comma
id|do_3
suffix:colon
id|xor_p5_mmx_3
comma
id|do_4
suffix:colon
id|xor_p5_mmx_4
comma
id|do_5
suffix:colon
id|xor_p5_mmx_5
comma
)brace
suffix:semicolon
DECL|macro|FPU_SAVE
macro_line|#undef FPU_SAVE
DECL|macro|FPU_RESTORE
macro_line|#undef FPU_RESTORE
multiline_comment|/*&n; * Cache avoiding checksumming functions utilizing KNI instructions&n; * Copyright (C) 1999 Zach Brown (with obvious credit due Ingo)&n; */
DECL|macro|XMMS_SAVE
mdefine_line|#define XMMS_SAVE&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__ ( &t;&t;&t;&bslash;&n;&t;&t;&quot;movl %%cr0,%0&t;&t;;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&quot;clts&t;&t;&t;;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&quot;movups %%xmm0,(%1)&t;;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&quot;movups %%xmm1,0x10(%1)&t;;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&quot;movups %%xmm2,0x20(%1)&t;;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&quot;movups %%xmm3,0x30(%1)&t;;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;: &quot;=r&quot; (cr0)&t;&t;&t;&bslash;&n;&t;&t;: &quot;r&quot; (xmm_save) &t;&t;&bslash;&n;&t;&t;: &quot;memory&quot;)
DECL|macro|XMMS_RESTORE
mdefine_line|#define XMMS_RESTORE&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__ ( &t;&t;&t;&bslash;&n;&t;&t;&quot;sfence&t;&t;&t;;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&quot;movups (%1),%%xmm0&t;;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&quot;movups 0x10(%1),%%xmm1&t;;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&quot;movups 0x20(%1),%%xmm2&t;;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&quot;movups 0x30(%1),%%xmm3&t;;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&quot;movl &t;%0,%%cr0&t;;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;:&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;r&quot; (cr0), &quot;r&quot; (xmm_save)&t;&bslash;&n;&t;&t;: &quot;memory&quot;)
DECL|macro|OFFS
mdefine_line|#define OFFS(x)&t;&t;&quot;16*(&quot;#x&quot;)&quot;
DECL|macro|PF0
mdefine_line|#define&t;PF0(x)&t;&t;&quot;&t;prefetcht0  &quot;OFFS(x)&quot;(%1)   ;&bslash;n&quot;
DECL|macro|LD
mdefine_line|#define LD(x,y)&t;&t;&quot;       movaps   &quot;OFFS(x)&quot;(%1), %%xmm&quot;#y&quot;   ;&bslash;n&quot;
DECL|macro|ST
mdefine_line|#define ST(x,y)&t;&t;&quot;       movaps %%xmm&quot;#y&quot;,   &quot;OFFS(x)&quot;(%1)   ;&bslash;n&quot;
DECL|macro|PF1
mdefine_line|#define PF1(x)&t;&t;&quot;&t;prefetchnta &quot;OFFS(x)&quot;(%2)   ;&bslash;n&quot;
DECL|macro|PF2
mdefine_line|#define PF2(x)&t;&t;&quot;&t;prefetchnta &quot;OFFS(x)&quot;(%3)   ;&bslash;n&quot;
DECL|macro|PF3
mdefine_line|#define PF3(x)&t;&t;&quot;&t;prefetchnta &quot;OFFS(x)&quot;(%4)   ;&bslash;n&quot;
DECL|macro|PF4
mdefine_line|#define PF4(x)&t;&t;&quot;&t;prefetchnta &quot;OFFS(x)&quot;(%5)   ;&bslash;n&quot;
DECL|macro|PF5
mdefine_line|#define PF5(x)&t;&t;&quot;&t;prefetchnta &quot;OFFS(x)&quot;(%6)   ;&bslash;n&quot;
DECL|macro|XO1
mdefine_line|#define XO1(x,y)&t;&quot;       xorps   &quot;OFFS(x)&quot;(%2), %%xmm&quot;#y&quot;   ;&bslash;n&quot;
DECL|macro|XO2
mdefine_line|#define XO2(x,y)&t;&quot;       xorps   &quot;OFFS(x)&quot;(%3), %%xmm&quot;#y&quot;   ;&bslash;n&quot;
DECL|macro|XO3
mdefine_line|#define XO3(x,y)&t;&quot;       xorps   &quot;OFFS(x)&quot;(%4), %%xmm&quot;#y&quot;   ;&bslash;n&quot;
DECL|macro|XO4
mdefine_line|#define XO4(x,y)&t;&quot;       xorps   &quot;OFFS(x)&quot;(%5), %%xmm&quot;#y&quot;   ;&bslash;n&quot;
DECL|macro|XO5
mdefine_line|#define XO5(x,y)&t;&quot;       xorps   &quot;OFFS(x)&quot;(%6), %%xmm&quot;#y&quot;   ;&bslash;n&quot;
r_static
r_void
DECL|function|xor_sse_2
id|xor_sse_2
c_func
(paren
r_int
r_int
id|bytes
comma
r_int
r_int
op_star
id|p1
comma
r_int
r_int
op_star
id|p2
)paren
(brace
r_int
r_int
id|lines
op_assign
id|bytes
op_rshift
l_int|8
suffix:semicolon
r_char
id|xmm_save
(braket
l_int|16
op_star
l_int|4
)braket
suffix:semicolon
r_int
id|cr0
suffix:semicolon
id|XMMS_SAVE
suffix:semicolon
id|__asm__
id|__volatile__
(paren
DECL|macro|BLOCK
macro_line|#undef BLOCK
DECL|macro|BLOCK
mdefine_line|#define BLOCK(i) &bslash;&n;&t;&t;LD(i,0)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;LD(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;PF1(i)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;PF1(i+2)&t;&t;&bslash;&n;&t;&t;&t;&t;LD(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;&t;LD(i+3,3)&t;&bslash;&n;&t;&t;PF0(i+4)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;PF0(i+6)&t;&t;&bslash;&n;&t;&t;XO1(i,0)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;XO1(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;&t;XO1(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;&t;XO1(i+3,3)&t;&bslash;&n;&t;&t;ST(i,0)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;ST(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;&t;ST(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;&t;ST(i+3,3)&t;&bslash;&n;
id|PF0
c_func
(paren
l_int|0
)paren
id|PF0
c_func
(paren
l_int|2
)paren
l_string|&quot; .align 32&t;&t;&t;;&bslash;n&quot;
l_string|&quot; 1:                            ;&bslash;n&quot;
id|BLOCK
c_func
(paren
l_int|0
)paren
id|BLOCK
c_func
(paren
l_int|4
)paren
id|BLOCK
c_func
(paren
l_int|8
)paren
id|BLOCK
c_func
(paren
l_int|12
)paren
l_string|&quot;       addl $256, %1           ;&bslash;n&quot;
l_string|&quot;       addl $256, %2           ;&bslash;n&quot;
l_string|&quot;       decl %0                 ;&bslash;n&quot;
l_string|&quot;       jnz 1b                  ;&bslash;n&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|lines
)paren
comma
l_string|&quot;r&quot;
(paren
id|p1
)paren
comma
l_string|&quot;r&quot;
(paren
id|p2
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|XMMS_RESTORE
suffix:semicolon
)brace
r_static
r_void
DECL|function|xor_sse_3
id|xor_sse_3
c_func
(paren
r_int
r_int
id|bytes
comma
r_int
r_int
op_star
id|p1
comma
r_int
r_int
op_star
id|p2
comma
r_int
r_int
op_star
id|p3
)paren
(brace
r_int
r_int
id|lines
op_assign
id|bytes
op_rshift
l_int|8
suffix:semicolon
r_char
id|xmm_save
(braket
l_int|16
op_star
l_int|4
)braket
suffix:semicolon
r_int
id|cr0
suffix:semicolon
id|XMMS_SAVE
suffix:semicolon
id|__asm__
id|__volatile__
(paren
DECL|macro|BLOCK
macro_line|#undef BLOCK
DECL|macro|BLOCK
mdefine_line|#define BLOCK(i) &bslash;&n;&t;&t;PF1(i)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;PF1(i+2)&t;&t;&bslash;&n;&t;&t;LD(i,0)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;LD(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;&t;LD(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;&t;LD(i+3,3)&t;&bslash;&n;&t;&t;PF2(i)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;PF2(i+2)&t;&t;&bslash;&n;&t;&t;PF0(i+4)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;PF0(i+6)&t;&t;&bslash;&n;&t;&t;XO1(i,0)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;XO1(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;&t;XO1(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;&t;XO1(i+3,3)&t;&bslash;&n;&t;&t;XO2(i,0)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;XO2(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;&t;XO2(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;&t;XO2(i+3,3)&t;&bslash;&n;&t;&t;ST(i,0)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;ST(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;&t;ST(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;&t;ST(i+3,3)&t;&bslash;&n;
id|PF0
c_func
(paren
l_int|0
)paren
id|PF0
c_func
(paren
l_int|2
)paren
l_string|&quot; .align 32&t;&t;&t;;&bslash;n&quot;
l_string|&quot; 1:                            ;&bslash;n&quot;
id|BLOCK
c_func
(paren
l_int|0
)paren
id|BLOCK
c_func
(paren
l_int|4
)paren
id|BLOCK
c_func
(paren
l_int|8
)paren
id|BLOCK
c_func
(paren
l_int|12
)paren
l_string|&quot;       addl $256, %1           ;&bslash;n&quot;
l_string|&quot;       addl $256, %2           ;&bslash;n&quot;
l_string|&quot;       addl $256, %3           ;&bslash;n&quot;
l_string|&quot;       decl %0                 ;&bslash;n&quot;
l_string|&quot;       jnz 1b                  ;&bslash;n&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|lines
)paren
comma
l_string|&quot;r&quot;
(paren
id|p1
)paren
comma
l_string|&quot;r&quot;
(paren
id|p2
)paren
comma
l_string|&quot;r&quot;
(paren
id|p3
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|XMMS_RESTORE
suffix:semicolon
)brace
r_static
r_void
DECL|function|xor_sse_4
id|xor_sse_4
c_func
(paren
r_int
r_int
id|bytes
comma
r_int
r_int
op_star
id|p1
comma
r_int
r_int
op_star
id|p2
comma
r_int
r_int
op_star
id|p3
comma
r_int
r_int
op_star
id|p4
)paren
(brace
r_int
r_int
id|lines
op_assign
id|bytes
op_rshift
l_int|8
suffix:semicolon
r_char
id|xmm_save
(braket
l_int|16
op_star
l_int|4
)braket
suffix:semicolon
r_int
id|cr0
suffix:semicolon
id|XMMS_SAVE
suffix:semicolon
id|__asm__
id|__volatile__
(paren
DECL|macro|BLOCK
macro_line|#undef BLOCK
DECL|macro|BLOCK
mdefine_line|#define BLOCK(i) &bslash;&n;&t;&t;PF1(i)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;PF1(i+2)&t;&t;&bslash;&n;&t;&t;LD(i,0)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;LD(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;&t;LD(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;&t;LD(i+3,3)&t;&bslash;&n;&t;&t;PF2(i)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;PF2(i+2)&t;&t;&bslash;&n;&t;&t;XO1(i,0)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;XO1(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;&t;XO1(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;&t;XO1(i+3,3)&t;&bslash;&n;&t;&t;PF3(i)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;PF3(i+2)&t;&t;&bslash;&n;&t;&t;PF0(i+4)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;PF0(i+6)&t;&t;&bslash;&n;&t;&t;XO2(i,0)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;XO2(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;&t;XO2(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;&t;XO2(i+3,3)&t;&bslash;&n;&t;&t;XO3(i,0)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;XO3(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;&t;XO3(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;&t;XO3(i+3,3)&t;&bslash;&n;&t;&t;ST(i,0)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;ST(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;&t;ST(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;&t;ST(i+3,3)&t;&bslash;&n;
id|PF0
c_func
(paren
l_int|0
)paren
id|PF0
c_func
(paren
l_int|2
)paren
l_string|&quot; .align 32&t;&t;&t;;&bslash;n&quot;
l_string|&quot; 1:                            ;&bslash;n&quot;
id|BLOCK
c_func
(paren
l_int|0
)paren
id|BLOCK
c_func
(paren
l_int|4
)paren
id|BLOCK
c_func
(paren
l_int|8
)paren
id|BLOCK
c_func
(paren
l_int|12
)paren
l_string|&quot;       addl $256, %1           ;&bslash;n&quot;
l_string|&quot;       addl $256, %2           ;&bslash;n&quot;
l_string|&quot;       addl $256, %3           ;&bslash;n&quot;
l_string|&quot;       addl $256, %4           ;&bslash;n&quot;
l_string|&quot;       decl %0                 ;&bslash;n&quot;
l_string|&quot;       jnz 1b                  ;&bslash;n&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|lines
)paren
comma
l_string|&quot;r&quot;
(paren
id|p1
)paren
comma
l_string|&quot;r&quot;
(paren
id|p2
)paren
comma
l_string|&quot;r&quot;
(paren
id|p3
)paren
comma
l_string|&quot;r&quot;
(paren
id|p4
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|XMMS_RESTORE
suffix:semicolon
)brace
r_static
r_void
DECL|function|xor_sse_5
id|xor_sse_5
c_func
(paren
r_int
r_int
id|bytes
comma
r_int
r_int
op_star
id|p1
comma
r_int
r_int
op_star
id|p2
comma
r_int
r_int
op_star
id|p3
comma
r_int
r_int
op_star
id|p4
comma
r_int
r_int
op_star
id|p5
)paren
(brace
r_int
r_int
id|lines
op_assign
id|bytes
op_rshift
l_int|8
suffix:semicolon
r_char
id|xmm_save
(braket
l_int|16
op_star
l_int|4
)braket
suffix:semicolon
r_int
id|cr0
suffix:semicolon
id|XMMS_SAVE
suffix:semicolon
id|__asm__
id|__volatile__
(paren
DECL|macro|BLOCK
macro_line|#undef BLOCK
DECL|macro|BLOCK
mdefine_line|#define BLOCK(i) &bslash;&n;&t;&t;PF1(i)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;PF1(i+2)&t;&t;&bslash;&n;&t;&t;LD(i,0)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;LD(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;&t;LD(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;&t;LD(i+3,3)&t;&bslash;&n;&t;&t;PF2(i)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;PF2(i+2)&t;&t;&bslash;&n;&t;&t;XO1(i,0)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;XO1(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;&t;XO1(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;&t;XO1(i+3,3)&t;&bslash;&n;&t;&t;PF3(i)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;PF3(i+2)&t;&t;&bslash;&n;&t;&t;XO2(i,0)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;XO2(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;&t;XO2(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;&t;XO2(i+3,3)&t;&bslash;&n;&t;&t;PF4(i)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;PF4(i+2)&t;&t;&bslash;&n;&t;&t;PF0(i+4)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;PF0(i+6)&t;&t;&bslash;&n;&t;&t;XO3(i,0)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;XO3(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;&t;XO3(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;&t;XO3(i+3,3)&t;&bslash;&n;&t;&t;XO4(i,0)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;XO4(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;&t;XO4(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;&t;XO4(i+3,3)&t;&bslash;&n;&t;&t;ST(i,0)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;ST(i+1,1)&t;&t;&t;&bslash;&n;&t;&t;&t;&t;ST(i+2,2)&t;&t;&bslash;&n;&t;&t;&t;&t;&t;ST(i+3,3)&t;&bslash;&n;
id|PF0
c_func
(paren
l_int|0
)paren
id|PF0
c_func
(paren
l_int|2
)paren
l_string|&quot; .align 32&t;&t;&t;;&bslash;n&quot;
l_string|&quot; 1:                            ;&bslash;n&quot;
id|BLOCK
c_func
(paren
l_int|0
)paren
id|BLOCK
c_func
(paren
l_int|4
)paren
id|BLOCK
c_func
(paren
l_int|8
)paren
id|BLOCK
c_func
(paren
l_int|12
)paren
l_string|&quot;       addl $256, %1           ;&bslash;n&quot;
l_string|&quot;       addl $256, %2           ;&bslash;n&quot;
l_string|&quot;       addl $256, %3           ;&bslash;n&quot;
l_string|&quot;       addl $256, %4           ;&bslash;n&quot;
l_string|&quot;       addl $256, %5           ;&bslash;n&quot;
l_string|&quot;       decl %0                 ;&bslash;n&quot;
l_string|&quot;       jnz 1b                  ;&bslash;n&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|lines
)paren
comma
l_string|&quot;r&quot;
(paren
id|p1
)paren
comma
l_string|&quot;r&quot;
(paren
id|p2
)paren
comma
l_string|&quot;r&quot;
(paren
id|p3
)paren
comma
l_string|&quot;r&quot;
(paren
id|p4
)paren
comma
l_string|&quot;r&quot;
(paren
id|p5
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|XMMS_RESTORE
suffix:semicolon
)brace
DECL|variable|xor_block_pIII_sse
r_static
r_struct
id|xor_block_template
id|xor_block_pIII_sse
op_assign
(brace
id|name
suffix:colon
l_string|&quot;pIII_sse&quot;
comma
id|do_2
suffix:colon
id|xor_sse_2
comma
id|do_3
suffix:colon
id|xor_sse_3
comma
id|do_4
suffix:colon
id|xor_sse_4
comma
id|do_5
suffix:colon
id|xor_sse_5
comma
)brace
suffix:semicolon
multiline_comment|/* Also try the generic routines.  */
macro_line|#include &lt;asm-generic/xor.h&gt;
DECL|macro|XOR_TRY_TEMPLATES
macro_line|#undef XOR_TRY_TEMPLATES
DECL|macro|XOR_TRY_TEMPLATES
mdefine_line|#define XOR_TRY_TEMPLATES&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;xor_speed(&amp;xor_block_8regs);&t;&t;&bslash;&n;&t;&t;xor_speed(&amp;xor_block_32regs);&t;&t;&bslash;&n;&t;        if (cpu_has_xmm)&t;&t;&t;&bslash;&n;&t;&t;&t;xor_speed(&amp;xor_block_pIII_sse);&t;&bslash;&n;&t;        if (md_cpu_has_mmx()) {&t;&t;&t;&bslash;&n;&t;                xor_speed(&amp;xor_block_pII_mmx);&t;&bslash;&n;&t;                xor_speed(&amp;xor_block_p5_mmx);&t;&bslash;&n;&t;        }&t;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
multiline_comment|/* We force the use of the SSE xor block because it can write around L2.&n;   We may also be able to load into the L1 only depending on how the cpu&n;   deals with a load to a line that is being prefetched.  */
DECL|macro|XOR_SELECT_TEMPLATE
mdefine_line|#define XOR_SELECT_TEMPLATE(FASTEST) &bslash;&n;&t;(cpu_has_xmm ? &amp;xor_block_pIII_sse : FASTEST)
eof
