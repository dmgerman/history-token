multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * arch/sh64/kernel/fpu.c&n; *&n; * Copyright (C) 2001  Manuela Cirronis, Paolo Alberelli&n; * Copyright (C) 2002  STMicroelectronics Limited&n; *   Author : Stuart Menefy&n; *&n; * Started from SH4 version:&n; *   Copyright (C) 1999, 2000  Kaz Kojima &amp; Niibe Yutaka&n; *&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/user.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/*&n; * Initially load the FPU with signalling NANS.  This bit pattern&n; * has the property that no matter whether considered as single or as&n; * double precision, it still represents a signalling NAN.&n; */
DECL|macro|sNAN64
mdefine_line|#define sNAN64&t;&t;0xFFFFFFFFFFFFFFFFULL
DECL|macro|sNAN32
mdefine_line|#define sNAN32&t;&t;0xFFFFFFFFUL
DECL|variable|init_fpuregs
r_static
r_union
id|sh_fpu_union
id|init_fpuregs
op_assign
(brace
dot
id|hard
op_assign
(brace
dot
id|fp_regs
op_assign
(brace
(braket
l_int|0
dot
dot
dot
l_int|63
)braket
op_assign
id|sNAN32
)brace
comma
dot
id|fpscr
op_assign
id|FPSCR_INIT
)brace
)brace
suffix:semicolon
DECL|function|fpsave
r_inline
r_void
id|fpsave
c_func
(paren
r_struct
id|sh_fpu_hard_struct
op_star
id|fpregs
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;fst.p     %0, (0*8), fp0&bslash;n&bslash;t&quot;
l_string|&quot;fst.p     %0, (1*8), fp2&bslash;n&bslash;t&quot;
l_string|&quot;fst.p     %0, (2*8), fp4&bslash;n&bslash;t&quot;
l_string|&quot;fst.p     %0, (3*8), fp6&bslash;n&bslash;t&quot;
l_string|&quot;fst.p     %0, (4*8), fp8&bslash;n&bslash;t&quot;
l_string|&quot;fst.p     %0, (5*8), fp10&bslash;n&bslash;t&quot;
l_string|&quot;fst.p     %0, (6*8), fp12&bslash;n&bslash;t&quot;
l_string|&quot;fst.p     %0, (7*8), fp14&bslash;n&bslash;t&quot;
l_string|&quot;fst.p     %0, (8*8), fp16&bslash;n&bslash;t&quot;
l_string|&quot;fst.p     %0, (9*8), fp18&bslash;n&bslash;t&quot;
l_string|&quot;fst.p     %0, (10*8), fp20&bslash;n&bslash;t&quot;
l_string|&quot;fst.p     %0, (11*8), fp22&bslash;n&bslash;t&quot;
l_string|&quot;fst.p     %0, (12*8), fp24&bslash;n&bslash;t&quot;
l_string|&quot;fst.p     %0, (13*8), fp26&bslash;n&bslash;t&quot;
l_string|&quot;fst.p     %0, (14*8), fp28&bslash;n&bslash;t&quot;
l_string|&quot;fst.p     %0, (15*8), fp30&bslash;n&bslash;t&quot;
l_string|&quot;fst.p     %0, (16*8), fp32&bslash;n&bslash;t&quot;
l_string|&quot;fst.p     %0, (17*8), fp34&bslash;n&bslash;t&quot;
l_string|&quot;fst.p     %0, (18*8), fp36&bslash;n&bslash;t&quot;
l_string|&quot;fst.p     %0, (19*8), fp38&bslash;n&bslash;t&quot;
l_string|&quot;fst.p     %0, (20*8), fp40&bslash;n&bslash;t&quot;
l_string|&quot;fst.p     %0, (21*8), fp42&bslash;n&bslash;t&quot;
l_string|&quot;fst.p     %0, (22*8), fp44&bslash;n&bslash;t&quot;
l_string|&quot;fst.p     %0, (23*8), fp46&bslash;n&bslash;t&quot;
l_string|&quot;fst.p     %0, (24*8), fp48&bslash;n&bslash;t&quot;
l_string|&quot;fst.p     %0, (25*8), fp50&bslash;n&bslash;t&quot;
l_string|&quot;fst.p     %0, (26*8), fp52&bslash;n&bslash;t&quot;
l_string|&quot;fst.p     %0, (27*8), fp54&bslash;n&bslash;t&quot;
l_string|&quot;fst.p     %0, (28*8), fp56&bslash;n&bslash;t&quot;
l_string|&quot;fst.p     %0, (29*8), fp58&bslash;n&bslash;t&quot;
l_string|&quot;fst.p     %0, (30*8), fp60&bslash;n&bslash;t&quot;
l_string|&quot;fst.p     %0, (31*8), fp62&bslash;n&bslash;t&quot;
l_string|&quot;fgetscr   fr63&bslash;n&bslash;t&quot;
l_string|&quot;fst.s     %0, (32*8), fr63&bslash;n&bslash;t&quot;
suffix:colon
multiline_comment|/* no output */
suffix:colon
l_string|&quot;r&quot;
(paren
id|fpregs
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|fpload
id|fpload
c_func
(paren
r_struct
id|sh_fpu_hard_struct
op_star
id|fpregs
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;fld.p     %0, (0*8), fp0&bslash;n&bslash;t&quot;
l_string|&quot;fld.p     %0, (1*8), fp2&bslash;n&bslash;t&quot;
l_string|&quot;fld.p     %0, (2*8), fp4&bslash;n&bslash;t&quot;
l_string|&quot;fld.p     %0, (3*8), fp6&bslash;n&bslash;t&quot;
l_string|&quot;fld.p     %0, (4*8), fp8&bslash;n&bslash;t&quot;
l_string|&quot;fld.p     %0, (5*8), fp10&bslash;n&bslash;t&quot;
l_string|&quot;fld.p     %0, (6*8), fp12&bslash;n&bslash;t&quot;
l_string|&quot;fld.p     %0, (7*8), fp14&bslash;n&bslash;t&quot;
l_string|&quot;fld.p     %0, (8*8), fp16&bslash;n&bslash;t&quot;
l_string|&quot;fld.p     %0, (9*8), fp18&bslash;n&bslash;t&quot;
l_string|&quot;fld.p     %0, (10*8), fp20&bslash;n&bslash;t&quot;
l_string|&quot;fld.p     %0, (11*8), fp22&bslash;n&bslash;t&quot;
l_string|&quot;fld.p     %0, (12*8), fp24&bslash;n&bslash;t&quot;
l_string|&quot;fld.p     %0, (13*8), fp26&bslash;n&bslash;t&quot;
l_string|&quot;fld.p     %0, (14*8), fp28&bslash;n&bslash;t&quot;
l_string|&quot;fld.p     %0, (15*8), fp30&bslash;n&bslash;t&quot;
l_string|&quot;fld.p     %0, (16*8), fp32&bslash;n&bslash;t&quot;
l_string|&quot;fld.p     %0, (17*8), fp34&bslash;n&bslash;t&quot;
l_string|&quot;fld.p     %0, (18*8), fp36&bslash;n&bslash;t&quot;
l_string|&quot;fld.p     %0, (19*8), fp38&bslash;n&bslash;t&quot;
l_string|&quot;fld.p     %0, (20*8), fp40&bslash;n&bslash;t&quot;
l_string|&quot;fld.p     %0, (21*8), fp42&bslash;n&bslash;t&quot;
l_string|&quot;fld.p     %0, (22*8), fp44&bslash;n&bslash;t&quot;
l_string|&quot;fld.p     %0, (23*8), fp46&bslash;n&bslash;t&quot;
l_string|&quot;fld.p     %0, (24*8), fp48&bslash;n&bslash;t&quot;
l_string|&quot;fld.p     %0, (25*8), fp50&bslash;n&bslash;t&quot;
l_string|&quot;fld.p     %0, (26*8), fp52&bslash;n&bslash;t&quot;
l_string|&quot;fld.p     %0, (27*8), fp54&bslash;n&bslash;t&quot;
l_string|&quot;fld.p     %0, (28*8), fp56&bslash;n&bslash;t&quot;
l_string|&quot;fld.p     %0, (29*8), fp58&bslash;n&bslash;t&quot;
l_string|&quot;fld.p     %0, (30*8), fp60&bslash;n&bslash;t&quot;
l_string|&quot;fld.s     %0, (32*8), fr63&bslash;n&bslash;t&quot;
l_string|&quot;fputscr   fr63&bslash;n&bslash;t&quot;
l_string|&quot;fld.p     %0, (31*8), fp62&bslash;n&bslash;t&quot;
suffix:colon
multiline_comment|/* no output */
suffix:colon
l_string|&quot;r&quot;
(paren
id|fpregs
)paren
)paren
suffix:semicolon
)brace
DECL|function|fpinit
r_void
id|fpinit
c_func
(paren
r_struct
id|sh_fpu_hard_struct
op_star
id|fpregs
)paren
(brace
op_star
id|fpregs
op_assign
id|init_fpuregs.hard
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
id|ex
comma
r_struct
id|pt_regs
op_star
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
id|regs-&gt;pc
op_add_assign
l_int|4
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
id|ex
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_void
id|die
c_func
(paren
r_const
r_char
op_star
id|str
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|err
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|user_mode
c_func
(paren
id|regs
)paren
)paren
id|die
c_func
(paren
l_string|&quot;FPU used in kernel&quot;
comma
id|regs
comma
id|ex
)paren
suffix:semicolon
id|regs-&gt;sr
op_and_assign
op_complement
id|SR_FD
suffix:semicolon
r_if
c_cond
(paren
id|last_task_used_math
op_eq
id|current
)paren
r_return
suffix:semicolon
id|grab_fpu
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|last_task_used_math
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/* Other processes fpu state, save away */
id|fpsave
c_func
(paren
op_amp
id|last_task_used_math-&gt;thread.fpu.hard
)paren
suffix:semicolon
)brace
id|last_task_used_math
op_assign
id|current
suffix:semicolon
r_if
c_cond
(paren
id|used_math
c_func
(paren
)paren
)paren
(brace
id|fpload
c_func
(paren
op_amp
id|current-&gt;thread.fpu.hard
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* First time FPU user.  */
id|fpload
c_func
(paren
op_amp
id|init_fpuregs.hard
)paren
suffix:semicolon
id|set_used_math
c_func
(paren
)paren
suffix:semicolon
)brace
id|release_fpu
c_func
(paren
)paren
suffix:semicolon
)brace
eof
