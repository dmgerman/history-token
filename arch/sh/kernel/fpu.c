multiline_comment|/* $Id: fpu.c,v 1.29 2000/03/22 13:42:10 gniibe Exp $&n; *&n; * linux/arch/sh/kernel/fpu.c&n; *&n; * Save/restore floating point context for signal handlers.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1999, 2000  Kaz Kojima &amp; Niibe Yutaka&n; *&n; * FIXME! These routines can be optimized in big endian case.&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/io.h&gt;
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
DECL|function|fpu_init
r_void
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
id|regs.pc
op_add_assign
l_int|2
suffix:semicolon
id|grab_fpu
c_func
(paren
)paren
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
r_if
c_cond
(paren
id|tsk
op_ne
op_amp
id|init_task
)paren
(brace
id|unlazy_fpu
c_func
(paren
id|tsk
)paren
suffix:semicolon
)brace
id|tsk
op_assign
op_amp
id|init_task
suffix:semicolon
r_if
c_cond
(paren
id|tsk-&gt;flags
op_amp
id|PF_USEDFPU
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * This weird situation can be occurred.&n;&t;&t;&t; *&n;&t;&t;&t; * There&squot;s race condition in __cli:&n;&t;&t;&t; *&n;&t;&t;&t; *   (1) SR --&gt; register&n;&t;&t;&t; *   (2) Set IMASK of register&n;&t;&t;&t; *   (3) SR &lt;-- register&n;&t;&t;&t; *&n;&t;&t;&t; * Between (1) and (2), or (2) and (3) getting&n;&t;&t;&t; * interrupt, and interrupt handler (or&n;&t;&t;&t; * softirq) may use FPU.&n;&t;&t;&t; *&n;&t;&t;&t; * Then, SR.FD is overwritten by (3).&n;&t;&t;&t; *&n;&t;&t;&t; * This results init_task.PF_USEDFPU is on,&n;&t;&t;&t; * with SR.FD == 1.&n;&t;&t;&t; *&n;&t;&t;&t; */
id|release_fpu
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|grab_fpu
c_func
(paren
)paren
suffix:semicolon
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
id|release_fpu
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Change current FD flag to set FD flag back to exception&n; */
id|asmlinkage
r_void
DECL|function|fpu_prepare_fd
id|fpu_prepare_fd
c_func
(paren
r_int
r_int
id|sr
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
id|__cli
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
r_if
c_cond
(paren
id|init_task.flags
op_amp
id|PF_USEDFPU
)paren
id|grab_fpu
c_func
(paren
)paren
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|sr
op_amp
id|SR_FD
)paren
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|release_fpu
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sr
op_amp
id|SR_FD
)paren
(brace
multiline_comment|/* Kernel doesn&squot;t grab FPU */
r_if
c_cond
(paren
id|current-&gt;flags
op_amp
id|PF_USEDFPU
)paren
id|grab_fpu
c_func
(paren
)paren
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
id|init_task.flags
op_amp
id|PF_USEDFPU
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * This weird situation can be occurred.&n;&t;&t;&t;&t; * See the comment in do_fpu_state_restore.&n;&t;&t;&t;&t; */
id|grab_fpu
c_func
(paren
)paren
suffix:semicolon
id|save_fpu
c_func
(paren
op_amp
id|init_task
)paren
suffix:semicolon
)brace
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|init_task.flags
op_amp
id|PF_USEDFPU
)paren
id|save_fpu
c_func
(paren
op_amp
id|init_task
)paren
suffix:semicolon
r_else
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|release_fpu
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* Short cut for the FPU exception */
id|asmlinkage
r_void
DECL|function|enable_fpu_in_danger
id|enable_fpu_in_danger
c_func
(paren
r_void
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
id|tsk
op_ne
op_amp
id|init_task
)paren
id|unlazy_fpu
c_func
(paren
id|tsk
)paren
suffix:semicolon
id|tsk
op_assign
op_amp
id|init_task
suffix:semicolon
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
