multiline_comment|/* $Id: fpu.c,v 1.29 2000/03/22 13:42:10 gniibe Exp $&n; *&n; * linux/arch/sh/kernel/fpu.c&n; *&n; * Save/restore floating point context for signal handlers.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1999, 2000  Kaz Kojima &amp; Niibe Yutaka&n; *&n; * FIXME! These routines can be optimized in big endian case.&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/*&n; * Save FPU registers onto task structure.&n; * Assume called with FPU enabled (SR.FD=0).&n; */
r_void
DECL|function|save_fpu
id|save_fpu
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;sts.l&t;fpul, @-%0&bslash;n&bslash;t&quot;
l_string|&quot;sts.l&t;fpscr, @-%0&bslash;n&bslash;t&quot;
l_string|&quot;lds&t;%1, fpscr&bslash;n&bslash;t&quot;
l_string|&quot;frchg&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;fr15, @-%0&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;fr14, @-%0&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;fr13, @-%0&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;fr12, @-%0&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;fr11, @-%0&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;fr10, @-%0&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;fr9, @-%0&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;fr8, @-%0&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;fr7, @-%0&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;fr6, @-%0&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;fr5, @-%0&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;fr4, @-%0&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;fr3, @-%0&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;fr2, @-%0&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;fr1, @-%0&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;fr0, @-%0&bslash;n&bslash;t&quot;
l_string|&quot;frchg&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;fr15, @-%0&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;fr14, @-%0&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;fr13, @-%0&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;fr12, @-%0&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;fr11, @-%0&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;fr10, @-%0&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;fr9, @-%0&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;fr8, @-%0&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;fr7, @-%0&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;fr6, @-%0&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;fr5, @-%0&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;fr4, @-%0&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;fr3, @-%0&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;fr2, @-%0&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;fr1, @-%0&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;fr0, @-%0&quot;
suffix:colon
multiline_comment|/* no output */
suffix:colon
l_string|&quot;r&quot;
(paren
(paren
r_char
op_star
)paren
(paren
op_amp
id|tsk-&gt;thread.fpu.hard.status
)paren
)paren
comma
l_string|&quot;r&quot;
(paren
id|FPSCR_INIT
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|tsk-&gt;flags
op_and_assign
op_complement
id|PF_USEDFPU
suffix:semicolon
id|release_fpu
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|restore_fpu
id|restore_fpu
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;lds&t;%1, fpscr&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;@%0+, fr0&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;@%0+, fr1&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;@%0+, fr2&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;@%0+, fr3&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;@%0+, fr4&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;@%0+, fr5&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;@%0+, fr6&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;@%0+, fr7&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;@%0+, fr8&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;@%0+, fr9&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;@%0+, fr10&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;@%0+, fr11&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;@%0+, fr12&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;@%0+, fr13&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;@%0+, fr14&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;@%0+, fr15&bslash;n&bslash;t&quot;
l_string|&quot;frchg&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;@%0+, fr0&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;@%0+, fr1&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;@%0+, fr2&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;@%0+, fr3&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;@%0+, fr4&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;@%0+, fr5&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;@%0+, fr6&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;@%0+, fr7&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;@%0+, fr8&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;@%0+, fr9&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;@%0+, fr10&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;@%0+, fr11&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;@%0+, fr12&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;@%0+, fr13&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;@%0+, fr14&bslash;n&bslash;t&quot;
l_string|&quot;fmov.s&t;@%0+, fr15&bslash;n&bslash;t&quot;
l_string|&quot;frchg&bslash;n&bslash;t&quot;
l_string|&quot;lds.l&t;@%0+, fpscr&bslash;n&bslash;t&quot;
l_string|&quot;lds.l&t;@%0+, fpul&bslash;n&bslash;t&quot;
suffix:colon
multiline_comment|/* no output */
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|tsk-&gt;thread.fpu
)paren
comma
l_string|&quot;r&quot;
(paren
id|FPSCR_INIT
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Load the FPU with signalling NANS.  This bit pattern we&squot;re using&n; * has the property that no matter wether considered as single or as&n; * double precission represents signaling NANS.  &n; */
r_static
r_void
DECL|function|fpu_init
id|fpu_init
c_func
(paren
r_void
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;lds&t;%0, fpul&bslash;n&bslash;t&quot;
l_string|&quot;lds&t;%1, fpscr&bslash;n&bslash;t&quot;
l_string|&quot;fsts&t;fpul, fr0&bslash;n&bslash;t&quot;
l_string|&quot;fsts&t;fpul, fr1&bslash;n&bslash;t&quot;
l_string|&quot;fsts&t;fpul, fr2&bslash;n&bslash;t&quot;
l_string|&quot;fsts&t;fpul, fr3&bslash;n&bslash;t&quot;
l_string|&quot;fsts&t;fpul, fr4&bslash;n&bslash;t&quot;
l_string|&quot;fsts&t;fpul, fr5&bslash;n&bslash;t&quot;
l_string|&quot;fsts&t;fpul, fr6&bslash;n&bslash;t&quot;
l_string|&quot;fsts&t;fpul, fr7&bslash;n&bslash;t&quot;
l_string|&quot;fsts&t;fpul, fr8&bslash;n&bslash;t&quot;
l_string|&quot;fsts&t;fpul, fr9&bslash;n&bslash;t&quot;
l_string|&quot;fsts&t;fpul, fr10&bslash;n&bslash;t&quot;
l_string|&quot;fsts&t;fpul, fr11&bslash;n&bslash;t&quot;
l_string|&quot;fsts&t;fpul, fr12&bslash;n&bslash;t&quot;
l_string|&quot;fsts&t;fpul, fr13&bslash;n&bslash;t&quot;
l_string|&quot;fsts&t;fpul, fr14&bslash;n&bslash;t&quot;
l_string|&quot;fsts&t;fpul, fr15&bslash;n&bslash;t&quot;
l_string|&quot;frchg&bslash;n&bslash;t&quot;
l_string|&quot;fsts&t;fpul, fr0&bslash;n&bslash;t&quot;
l_string|&quot;fsts&t;fpul, fr1&bslash;n&bslash;t&quot;
l_string|&quot;fsts&t;fpul, fr2&bslash;n&bslash;t&quot;
l_string|&quot;fsts&t;fpul, fr3&bslash;n&bslash;t&quot;
l_string|&quot;fsts&t;fpul, fr4&bslash;n&bslash;t&quot;
l_string|&quot;fsts&t;fpul, fr5&bslash;n&bslash;t&quot;
l_string|&quot;fsts&t;fpul, fr6&bslash;n&bslash;t&quot;
l_string|&quot;fsts&t;fpul, fr7&bslash;n&bslash;t&quot;
l_string|&quot;fsts&t;fpul, fr8&bslash;n&bslash;t&quot;
l_string|&quot;fsts&t;fpul, fr9&bslash;n&bslash;t&quot;
l_string|&quot;fsts&t;fpul, fr10&bslash;n&bslash;t&quot;
l_string|&quot;fsts&t;fpul, fr11&bslash;n&bslash;t&quot;
l_string|&quot;fsts&t;fpul, fr12&bslash;n&bslash;t&quot;
l_string|&quot;fsts&t;fpul, fr13&bslash;n&bslash;t&quot;
l_string|&quot;fsts&t;fpul, fr14&bslash;n&bslash;t&quot;
l_string|&quot;fsts&t;fpul, fr15&bslash;n&bslash;t&quot;
l_string|&quot;frchg&quot;
suffix:colon
multiline_comment|/* no output */
suffix:colon
l_string|&quot;r&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;r&quot;
(paren
id|FPSCR_INIT
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;denormal_to_double - Given denormalized float number,&n; *&t;                     store double float&n; *&n; *&t;@fpu: Pointer to sh_fpu_hard structure&n; *&t;@n: Index to FP register&n; */
r_static
r_void
DECL|function|denormal_to_double
id|denormal_to_double
(paren
r_struct
id|sh_fpu_hard_struct
op_star
id|fpu
comma
r_int
id|n
)paren
(brace
r_int
r_int
id|du
comma
id|dl
suffix:semicolon
r_int
r_int
id|x
op_assign
id|fpu-&gt;fpul
suffix:semicolon
r_int
id|exp
op_assign
l_int|1023
op_minus
l_int|126
suffix:semicolon
r_if
c_cond
(paren
id|x
op_ne
l_int|0
op_logical_and
(paren
id|x
op_amp
l_int|0x7f800000
)paren
op_eq
l_int|0
)paren
(brace
id|du
op_assign
(paren
id|x
op_amp
l_int|0x80000000
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|x
op_amp
l_int|0x00800000
)paren
op_eq
l_int|0
)paren
(brace
id|x
op_lshift_assign
l_int|1
suffix:semicolon
id|exp
op_decrement
suffix:semicolon
)brace
id|x
op_and_assign
l_int|0x007fffff
suffix:semicolon
id|du
op_or_assign
(paren
id|exp
op_lshift
l_int|20
)paren
op_or
(paren
id|x
op_rshift
l_int|3
)paren
suffix:semicolon
id|dl
op_assign
id|x
op_lshift
l_int|29
suffix:semicolon
id|fpu-&gt;fp_regs
(braket
id|n
)braket
op_assign
id|du
suffix:semicolon
id|fpu-&gt;fp_regs
(braket
id|n
op_plus
l_int|1
)braket
op_assign
id|dl
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; *&t;ieee_fpe_handler - Handle denormalized number exception&n; *&n; *&t;@regs: Pointer to register structure&n; *&n; *&t;Returns 1 when it&squot;s handled (should not cause exception).&n; */
r_static
r_int
DECL|function|ieee_fpe_handler
id|ieee_fpe_handler
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|insn
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|regs-&gt;pc
suffix:semicolon
r_int
r_int
id|finsn
suffix:semicolon
r_int
r_int
id|nextpc
suffix:semicolon
r_int
id|nib
(braket
l_int|4
)braket
op_assign
(brace
(paren
id|insn
op_rshift
l_int|12
)paren
op_amp
l_int|0xf
comma
(paren
id|insn
op_rshift
l_int|8
)paren
op_amp
l_int|0xf
comma
(paren
id|insn
op_rshift
l_int|4
)paren
op_amp
l_int|0xf
comma
id|insn
op_amp
l_int|0xf
)brace
suffix:semicolon
r_if
c_cond
(paren
id|nib
(braket
l_int|0
)braket
op_eq
l_int|0xb
op_logical_or
(paren
id|nib
(braket
l_int|0
)braket
op_eq
l_int|0x4
op_logical_and
id|nib
(braket
l_int|2
)braket
op_eq
l_int|0x0
op_logical_and
id|nib
(braket
l_int|3
)braket
op_eq
l_int|0xb
)paren
)paren
multiline_comment|/* bsr &amp; jsr */
id|regs-&gt;pr
op_assign
id|regs-&gt;pc
op_plus
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|nib
(braket
l_int|0
)braket
op_eq
l_int|0xa
op_logical_or
id|nib
(braket
l_int|0
)braket
op_eq
l_int|0xb
)paren
(brace
multiline_comment|/* bra &amp; bsr */
id|nextpc
op_assign
id|regs-&gt;pc
op_plus
l_int|4
op_plus
(paren
(paren
r_int
)paren
(paren
(paren
id|insn
op_amp
l_int|0xfff
)paren
op_lshift
l_int|4
)paren
op_rshift
l_int|3
)paren
suffix:semicolon
id|finsn
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|regs-&gt;pc
op_plus
l_int|2
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|nib
(braket
l_int|0
)braket
op_eq
l_int|0x8
op_logical_and
id|nib
(braket
l_int|1
)braket
op_eq
l_int|0xd
)paren
(brace
multiline_comment|/* bt/s */
r_if
c_cond
(paren
id|regs-&gt;sr
op_amp
l_int|1
)paren
id|nextpc
op_assign
id|regs-&gt;pc
op_plus
l_int|4
op_plus
(paren
(paren
r_char
)paren
(paren
id|insn
op_amp
l_int|0xff
)paren
op_lshift
l_int|1
)paren
suffix:semicolon
r_else
id|nextpc
op_assign
id|regs-&gt;pc
op_plus
l_int|4
suffix:semicolon
id|finsn
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|regs-&gt;pc
op_plus
l_int|2
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|nib
(braket
l_int|0
)braket
op_eq
l_int|0x8
op_logical_and
id|nib
(braket
l_int|1
)braket
op_eq
l_int|0xf
)paren
(brace
multiline_comment|/* bf/s */
r_if
c_cond
(paren
id|regs-&gt;sr
op_amp
l_int|1
)paren
id|nextpc
op_assign
id|regs-&gt;pc
op_plus
l_int|4
suffix:semicolon
r_else
id|nextpc
op_assign
id|regs-&gt;pc
op_plus
l_int|4
op_plus
(paren
(paren
r_char
)paren
(paren
id|insn
op_amp
l_int|0xff
)paren
op_lshift
l_int|1
)paren
suffix:semicolon
id|finsn
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|regs-&gt;pc
op_plus
l_int|2
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|nib
(braket
l_int|0
)braket
op_eq
l_int|0x4
op_logical_and
id|nib
(braket
l_int|3
)braket
op_eq
l_int|0xb
op_logical_and
(paren
id|nib
(braket
l_int|2
)braket
op_eq
l_int|0x0
op_logical_or
id|nib
(braket
l_int|2
)braket
op_eq
l_int|0x2
)paren
)paren
(brace
multiline_comment|/* jmp &amp; jsr */
id|nextpc
op_assign
id|regs-&gt;regs
(braket
id|nib
(braket
l_int|1
)braket
)braket
suffix:semicolon
id|finsn
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|regs-&gt;pc
op_plus
l_int|2
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|nib
(braket
l_int|0
)braket
op_eq
l_int|0x0
op_logical_and
id|nib
(braket
l_int|3
)braket
op_eq
l_int|0x3
op_logical_and
(paren
id|nib
(braket
l_int|2
)braket
op_eq
l_int|0x0
op_logical_or
id|nib
(braket
l_int|2
)braket
op_eq
l_int|0x2
)paren
)paren
(brace
multiline_comment|/* braf &amp; bsrf */
id|nextpc
op_assign
id|regs-&gt;pc
op_plus
l_int|4
op_plus
id|regs-&gt;regs
(braket
id|nib
(braket
l_int|1
)braket
)braket
suffix:semicolon
id|finsn
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|regs-&gt;pc
op_plus
l_int|2
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|insn
op_eq
l_int|0x000b
)paren
(brace
multiline_comment|/* rts */
id|nextpc
op_assign
id|regs-&gt;pr
suffix:semicolon
id|finsn
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|regs-&gt;pc
op_plus
l_int|2
)paren
suffix:semicolon
)brace
r_else
(brace
id|nextpc
op_assign
id|regs-&gt;pc
op_plus
l_int|2
suffix:semicolon
id|finsn
op_assign
id|insn
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|finsn
op_amp
l_int|0xf1ff
)paren
op_eq
l_int|0xf0ad
)paren
(brace
multiline_comment|/* fcnvsd */
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
id|save_fpu
c_func
(paren
id|tsk
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tsk-&gt;thread.fpu.hard.fpscr
op_amp
(paren
l_int|1
op_lshift
l_int|17
)paren
)paren
)paren
(brace
multiline_comment|/* FPU error */
id|denormal_to_double
(paren
op_amp
id|tsk-&gt;thread.fpu.hard
comma
(paren
id|finsn
op_rshift
l_int|8
)paren
op_amp
l_int|0xf
)paren
suffix:semicolon
id|tsk-&gt;thread.fpu.hard.fpscr
op_and_assign
op_complement
(paren
id|FPSCR_CAUSE_MASK
op_or
id|FPSCR_FLAG_MASK
)paren
suffix:semicolon
id|grab_fpu
c_func
(paren
)paren
suffix:semicolon
id|restore_fpu
c_func
(paren
id|tsk
)paren
suffix:semicolon
id|tsk-&gt;flags
op_or_assign
id|PF_USEDFPU
suffix:semicolon
)brace
r_else
(brace
id|tsk-&gt;thread.trap_no
op_assign
l_int|11
suffix:semicolon
id|tsk-&gt;thread.error_code
op_assign
l_int|0
suffix:semicolon
id|force_sig
c_func
(paren
id|SIGFPE
comma
id|tsk
)paren
suffix:semicolon
)brace
id|regs-&gt;pc
op_assign
id|nextpc
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
id|asmlinkage
r_void
DECL|function|do_fpu_error
id|do_fpu_error
c_func
(paren
r_int
r_int
id|r4
comma
r_int
r_int
id|r5
comma
r_int
r_int
id|r6
comma
r_int
r_int
id|r7
comma
r_struct
id|pt_regs
id|regs
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
r_if
c_cond
(paren
id|ieee_fpe_handler
(paren
op_amp
id|regs
)paren
)paren
r_return
suffix:semicolon
id|regs.pc
op_add_assign
l_int|2
suffix:semicolon
id|save_fpu
c_func
(paren
id|tsk
)paren
suffix:semicolon
id|tsk-&gt;thread.trap_no
op_assign
l_int|11
suffix:semicolon
id|tsk-&gt;thread.error_code
op_assign
l_int|0
suffix:semicolon
id|force_sig
c_func
(paren
id|SIGFPE
comma
id|tsk
)paren
suffix:semicolon
)brace
id|asmlinkage
r_void
DECL|function|do_fpu_state_restore
id|do_fpu_state_restore
c_func
(paren
r_int
r_int
id|r4
comma
r_int
r_int
id|r5
comma
r_int
r_int
id|r6
comma
r_int
r_int
id|r7
comma
r_struct
id|pt_regs
id|regs
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
id|grab_fpu
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|user_mode
c_func
(paren
op_amp
id|regs
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;BUG: FPU is used in kernel mode.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tsk-&gt;used_math
)paren
(brace
multiline_comment|/* Using the FPU again.  */
id|restore_fpu
c_func
(paren
id|tsk
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* First time FPU user.  */
id|fpu_init
c_func
(paren
)paren
suffix:semicolon
id|tsk-&gt;used_math
op_assign
l_int|1
suffix:semicolon
)brace
id|tsk-&gt;flags
op_or_assign
id|PF_USEDFPU
suffix:semicolon
)brace
eof
