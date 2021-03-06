multiline_comment|/* -*- linux-c -*- ------------------------------------------------------- *&n; *&n; *   Copyright 2002 H. Peter Anvin - All Rights Reserved&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation, Inc., 53 Temple Place Ste 330,&n; *   Bostom MA 02111-1307, USA; either version 2 of the License, or&n; *   (at your option) any later version; incorporated herein by reference.&n; *&n; * ----------------------------------------------------------------------- */
multiline_comment|/*&n; * raid6mmx.c&n; *&n; * MMX implementation of RAID-6 syndrome functions&n; */
macro_line|#if defined(__i386__)
macro_line|#include &quot;raid6.h&quot;
macro_line|#include &quot;raid6x86.h&quot;
multiline_comment|/* Shared with raid6sse1.c */
DECL|struct|raid6_mmx_constants
r_const
r_struct
id|raid6_mmx_constants
(brace
DECL|member|x1d
id|u64
id|x1d
suffix:semicolon
DECL|variable|raid6_mmx_constants
)brace
id|raid6_mmx_constants
op_assign
(brace
l_int|0x1d1d1d1d1d1d1d1dULL
comma
)brace
suffix:semicolon
DECL|function|raid6_have_mmx
r_static
r_int
id|raid6_have_mmx
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef __KERNEL__
multiline_comment|/* Not really &quot;boot_cpu&quot; but &quot;all_cpus&quot; */
r_return
id|boot_cpu_has
c_func
(paren
id|X86_FEATURE_MMX
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/* User space test code */
id|u32
id|features
op_assign
id|cpuid_features
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
(paren
id|features
op_amp
(paren
l_int|1
op_lshift
l_int|23
)paren
)paren
op_eq
(paren
l_int|1
op_lshift
l_int|23
)paren
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * Plain MMX implementation&n; */
DECL|function|raid6_mmx1_gen_syndrome
r_static
r_void
id|raid6_mmx1_gen_syndrome
c_func
(paren
r_int
id|disks
comma
r_int
id|bytes
comma
r_void
op_star
op_star
id|ptrs
)paren
(brace
id|u8
op_star
op_star
id|dptr
op_assign
(paren
id|u8
op_star
op_star
)paren
id|ptrs
suffix:semicolon
id|u8
op_star
id|p
comma
op_star
id|q
suffix:semicolon
r_int
id|d
comma
id|z
comma
id|z0
suffix:semicolon
id|raid6_mmx_save_t
id|sa
suffix:semicolon
id|z0
op_assign
id|disks
op_minus
l_int|3
suffix:semicolon
multiline_comment|/* Highest data disk */
id|p
op_assign
id|dptr
(braket
id|z0
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* XOR parity */
id|q
op_assign
id|dptr
(braket
id|z0
op_plus
l_int|2
)braket
suffix:semicolon
multiline_comment|/* RS syndrome */
id|raid6_before_mmx
c_func
(paren
op_amp
id|sa
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movq %0,%%mm0&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
id|raid6_mmx_constants.x1d
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;pxor %mm5,%mm5&quot;
)paren
suffix:semicolon
multiline_comment|/* Zero temp */
r_for
c_loop
(paren
id|d
op_assign
l_int|0
suffix:semicolon
id|d
OL
id|bytes
suffix:semicolon
id|d
op_add_assign
l_int|8
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;movq %0,%%mm2&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
id|dptr
(braket
id|z0
)braket
(braket
id|d
)braket
)paren
)paren
suffix:semicolon
multiline_comment|/* P[0] */
id|asm
r_volatile
(paren
l_string|&quot;movq %mm2,%mm4&quot;
)paren
suffix:semicolon
multiline_comment|/* Q[0] */
r_for
c_loop
(paren
id|z
op_assign
id|z0
op_minus
l_int|1
suffix:semicolon
id|z
op_ge
l_int|0
suffix:semicolon
id|z
op_decrement
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;movq %0,%%mm6&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
id|dptr
(braket
id|z
)braket
(braket
id|d
)braket
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;pcmpgtb %mm4,%mm5&quot;
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;paddb %mm4,%mm4&quot;
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;pand %mm0,%mm5&quot;
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;pxor %mm5,%mm4&quot;
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;pxor %mm5,%mm5&quot;
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;pxor %mm6,%mm2&quot;
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;pxor %mm6,%mm4&quot;
)paren
suffix:semicolon
)brace
id|asm
r_volatile
(paren
l_string|&quot;movq %%mm2,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|p
(braket
id|d
)braket
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;pxor %mm2,%mm2&quot;
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movq %%mm4,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|q
(braket
id|d
)braket
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;pxor %mm4,%mm4&quot;
)paren
suffix:semicolon
)brace
id|raid6_after_mmx
c_func
(paren
op_amp
id|sa
)paren
suffix:semicolon
)brace
DECL|variable|raid6_mmxx1
r_const
r_struct
id|raid6_calls
id|raid6_mmxx1
op_assign
(brace
id|raid6_mmx1_gen_syndrome
comma
id|raid6_have_mmx
comma
l_string|&quot;mmxx1&quot;
comma
l_int|0
)brace
suffix:semicolon
multiline_comment|/*&n; * Unrolled-by-2 MMX implementation&n; */
DECL|function|raid6_mmx2_gen_syndrome
r_static
r_void
id|raid6_mmx2_gen_syndrome
c_func
(paren
r_int
id|disks
comma
r_int
id|bytes
comma
r_void
op_star
op_star
id|ptrs
)paren
(brace
id|u8
op_star
op_star
id|dptr
op_assign
(paren
id|u8
op_star
op_star
)paren
id|ptrs
suffix:semicolon
id|u8
op_star
id|p
comma
op_star
id|q
suffix:semicolon
r_int
id|d
comma
id|z
comma
id|z0
suffix:semicolon
id|raid6_mmx_save_t
id|sa
suffix:semicolon
id|z0
op_assign
id|disks
op_minus
l_int|3
suffix:semicolon
multiline_comment|/* Highest data disk */
id|p
op_assign
id|dptr
(braket
id|z0
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* XOR parity */
id|q
op_assign
id|dptr
(braket
id|z0
op_plus
l_int|2
)braket
suffix:semicolon
multiline_comment|/* RS syndrome */
id|raid6_before_mmx
c_func
(paren
op_amp
id|sa
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movq %0,%%mm0&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
id|raid6_mmx_constants.x1d
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;pxor %mm5,%mm5&quot;
)paren
suffix:semicolon
multiline_comment|/* Zero temp */
id|asm
r_volatile
(paren
l_string|&quot;pxor %mm7,%mm7&quot;
)paren
suffix:semicolon
multiline_comment|/* Zero temp */
r_for
c_loop
(paren
id|d
op_assign
l_int|0
suffix:semicolon
id|d
OL
id|bytes
suffix:semicolon
id|d
op_add_assign
l_int|16
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;movq %0,%%mm2&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
id|dptr
(braket
id|z0
)braket
(braket
id|d
)braket
)paren
)paren
suffix:semicolon
multiline_comment|/* P[0] */
id|asm
r_volatile
(paren
l_string|&quot;movq %0,%%mm3&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
id|dptr
(braket
id|z0
)braket
(braket
id|d
op_plus
l_int|8
)braket
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movq %mm2,%mm4&quot;
)paren
suffix:semicolon
multiline_comment|/* Q[0] */
id|asm
r_volatile
(paren
l_string|&quot;movq %mm3,%mm6&quot;
)paren
suffix:semicolon
multiline_comment|/* Q[1] */
r_for
c_loop
(paren
id|z
op_assign
id|z0
op_minus
l_int|1
suffix:semicolon
id|z
op_ge
l_int|0
suffix:semicolon
id|z
op_decrement
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;pcmpgtb %mm4,%mm5&quot;
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;pcmpgtb %mm6,%mm7&quot;
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;paddb %mm4,%mm4&quot;
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;paddb %mm6,%mm6&quot;
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;pand %mm0,%mm5&quot;
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;pand %mm0,%mm7&quot;
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;pxor %mm5,%mm4&quot;
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;pxor %mm7,%mm6&quot;
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movq %0,%%mm5&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
id|dptr
(braket
id|z
)braket
(braket
id|d
)braket
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movq %0,%%mm7&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
id|dptr
(braket
id|z
)braket
(braket
id|d
op_plus
l_int|8
)braket
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;pxor %mm5,%mm2&quot;
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;pxor %mm7,%mm3&quot;
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;pxor %mm5,%mm4&quot;
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;pxor %mm7,%mm6&quot;
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;pxor %mm5,%mm5&quot;
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;pxor %mm7,%mm7&quot;
)paren
suffix:semicolon
)brace
id|asm
r_volatile
(paren
l_string|&quot;movq %%mm2,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|p
(braket
id|d
)braket
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movq %%mm3,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|p
(braket
id|d
op_plus
l_int|8
)braket
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movq %%mm4,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|q
(braket
id|d
)braket
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movq %%mm6,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|q
(braket
id|d
op_plus
l_int|8
)braket
)paren
)paren
suffix:semicolon
)brace
id|raid6_after_mmx
c_func
(paren
op_amp
id|sa
)paren
suffix:semicolon
)brace
DECL|variable|raid6_mmxx2
r_const
r_struct
id|raid6_calls
id|raid6_mmxx2
op_assign
(brace
id|raid6_mmx2_gen_syndrome
comma
id|raid6_have_mmx
comma
l_string|&quot;mmxx2&quot;
comma
l_int|0
)brace
suffix:semicolon
macro_line|#endif
eof
