multiline_comment|/*&n; *  linux/arch/i386/kernel/i387.c&n; *&n; *  Copyright (C) 1994 Linus Torvalds&n; *&n; *  Pentium III FXSR, SSE support&n; *  General FPU state handling cleanups&n; *&t;Gareth Hughes &lt;gareth@valinux.com&gt;, May 2000&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/i387.h&gt;
macro_line|#include &lt;asm/math_emu.h&gt;
macro_line|#include &lt;asm/sigcontext.h&gt;
macro_line|#include &lt;asm/user.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#ifdef CONFIG_MATH_EMULATION
DECL|macro|HAVE_HWFP
mdefine_line|#define HAVE_HWFP (boot_cpu_data.hard_math)
macro_line|#else
DECL|macro|HAVE_HWFP
mdefine_line|#define HAVE_HWFP 1
macro_line|#endif
DECL|variable|mxcsr_feature_mask
r_int
r_int
id|mxcsr_feature_mask
op_assign
l_int|0xffffffff
suffix:semicolon
DECL|function|mxcsr_feature_mask_init
r_void
id|mxcsr_feature_mask_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|mask
op_assign
l_int|0
suffix:semicolon
id|clts
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu_has_fxsr
)paren
(brace
id|memset
c_func
(paren
op_amp
id|current-&gt;thread.i387.fxsave
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|i387_fxsave_struct
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;fxsave %0&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
id|current-&gt;thread.i387.fxsave
)paren
)paren
suffix:semicolon
id|mask
op_assign
id|current-&gt;thread.i387.fxsave.mxcsr_mask
suffix:semicolon
r_if
c_cond
(paren
id|mask
op_eq
l_int|0
)paren
id|mask
op_assign
l_int|0x0000ffbf
suffix:semicolon
)brace
id|mxcsr_feature_mask
op_and_assign
id|mask
suffix:semicolon
id|stts
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The _current_ task is using the FPU for the first time&n; * so initialize it and set the mxcsr to its default&n; * value at reset if we support XMM instructions and then&n; * remeber the current task has used the FPU.&n; */
DECL|function|init_fpu
r_void
id|init_fpu
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_if
c_cond
(paren
id|cpu_has_fxsr
)paren
(brace
id|memset
c_func
(paren
op_amp
id|tsk-&gt;thread.i387.fxsave
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|i387_fxsave_struct
)paren
)paren
suffix:semicolon
id|tsk-&gt;thread.i387.fxsave.cwd
op_assign
l_int|0x37f
suffix:semicolon
r_if
c_cond
(paren
id|cpu_has_xmm
)paren
id|tsk-&gt;thread.i387.fxsave.mxcsr
op_assign
l_int|0x1f80
suffix:semicolon
)brace
r_else
(brace
id|memset
c_func
(paren
op_amp
id|tsk-&gt;thread.i387.fsave
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|i387_fsave_struct
)paren
)paren
suffix:semicolon
id|tsk-&gt;thread.i387.fsave.cwd
op_assign
l_int|0xffff037fu
suffix:semicolon
id|tsk-&gt;thread.i387.fsave.swd
op_assign
l_int|0xffff0000u
suffix:semicolon
id|tsk-&gt;thread.i387.fsave.twd
op_assign
l_int|0xffffffffu
suffix:semicolon
id|tsk-&gt;thread.i387.fsave.fos
op_assign
l_int|0xffff0000u
suffix:semicolon
)brace
id|tsk-&gt;used_math
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * FPU lazy state save handling.&n; */
DECL|function|kernel_fpu_begin
r_void
id|kernel_fpu_begin
c_func
(paren
r_void
)paren
(brace
r_struct
id|thread_info
op_star
id|thread
op_assign
id|current_thread_info
c_func
(paren
)paren
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|thread-&gt;status
op_amp
id|TS_USEDFPU
)paren
(brace
id|__save_init_fpu
c_func
(paren
id|thread-&gt;task
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|clts
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|restore_fpu
r_void
id|restore_fpu
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_if
c_cond
(paren
id|cpu_has_fxsr
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;fxrstor %0&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
id|tsk-&gt;thread.i387.fxsave
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|asm
r_volatile
(paren
l_string|&quot;frstor %0&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
id|tsk-&gt;thread.i387.fsave
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * FPU tag word conversions.&n; */
DECL|function|twd_i387_to_fxsr
r_static
r_inline
r_int
r_int
id|twd_i387_to_fxsr
c_func
(paren
r_int
r_int
id|twd
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
multiline_comment|/* to avoid 16 bit prefixes in the code */
multiline_comment|/* Transform each pair of bits into 01 (valid) or 00 (empty) */
id|tmp
op_assign
op_complement
id|twd
suffix:semicolon
id|tmp
op_assign
(paren
id|tmp
op_or
(paren
id|tmp
op_rshift
l_int|1
)paren
)paren
op_amp
l_int|0x5555
suffix:semicolon
multiline_comment|/* 0V0V0V0V0V0V0V0V */
multiline_comment|/* and move the valid bits to the lower byte. */
id|tmp
op_assign
(paren
id|tmp
op_or
(paren
id|tmp
op_rshift
l_int|1
)paren
)paren
op_amp
l_int|0x3333
suffix:semicolon
multiline_comment|/* 00VV00VV00VV00VV */
id|tmp
op_assign
(paren
id|tmp
op_or
(paren
id|tmp
op_rshift
l_int|2
)paren
)paren
op_amp
l_int|0x0f0f
suffix:semicolon
multiline_comment|/* 0000VVVV0000VVVV */
id|tmp
op_assign
(paren
id|tmp
op_or
(paren
id|tmp
op_rshift
l_int|4
)paren
)paren
op_amp
l_int|0x00ff
suffix:semicolon
multiline_comment|/* 00000000VVVVVVVV */
r_return
id|tmp
suffix:semicolon
)brace
DECL|function|twd_fxsr_to_i387
r_static
r_inline
r_int
r_int
id|twd_fxsr_to_i387
c_func
(paren
r_struct
id|i387_fxsave_struct
op_star
id|fxsave
)paren
(brace
r_struct
id|_fpxreg
op_star
id|st
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|twd
op_assign
(paren
r_int
r_int
)paren
id|fxsave-&gt;twd
suffix:semicolon
r_int
r_int
id|tag
suffix:semicolon
r_int
r_int
id|ret
op_assign
l_int|0xffff0000u
suffix:semicolon
r_int
id|i
suffix:semicolon
DECL|macro|FPREG_ADDR
mdefine_line|#define FPREG_ADDR(f, n)&t;((char *)&amp;(f)-&gt;st_space + (n) * 16);
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|twd
op_amp
l_int|0x1
)paren
(brace
id|st
op_assign
(paren
r_struct
id|_fpxreg
op_star
)paren
id|FPREG_ADDR
c_func
(paren
id|fxsave
comma
id|i
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|st-&gt;exponent
op_amp
l_int|0x7fff
)paren
(brace
r_case
l_int|0x7fff
suffix:colon
id|tag
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* Special */
r_break
suffix:semicolon
r_case
l_int|0x0000
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|st-&gt;significand
(braket
l_int|0
)braket
op_logical_and
op_logical_neg
id|st-&gt;significand
(braket
l_int|1
)braket
op_logical_and
op_logical_neg
id|st-&gt;significand
(braket
l_int|2
)braket
op_logical_and
op_logical_neg
id|st-&gt;significand
(braket
l_int|3
)braket
)paren
(brace
id|tag
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Zero */
)brace
r_else
(brace
id|tag
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* Special */
)brace
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|st-&gt;significand
(braket
l_int|3
)braket
op_amp
l_int|0x8000
)paren
(brace
id|tag
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Valid */
)brace
r_else
(brace
id|tag
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* Special */
)brace
r_break
suffix:semicolon
)brace
)brace
r_else
(brace
id|tag
op_assign
l_int|3
suffix:semicolon
multiline_comment|/* Empty */
)brace
id|ret
op_or_assign
(paren
id|tag
op_lshift
(paren
l_int|2
op_star
id|i
)paren
)paren
suffix:semicolon
id|twd
op_assign
id|twd
op_rshift
l_int|1
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * FPU state interaction.&n; */
DECL|function|get_fpu_cwd
r_int
r_int
id|get_fpu_cwd
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_if
c_cond
(paren
id|cpu_has_fxsr
)paren
(brace
r_return
id|tsk-&gt;thread.i387.fxsave.cwd
suffix:semicolon
)brace
r_else
(brace
r_return
(paren
r_int
r_int
)paren
id|tsk-&gt;thread.i387.fsave.cwd
suffix:semicolon
)brace
)brace
DECL|function|get_fpu_swd
r_int
r_int
id|get_fpu_swd
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_if
c_cond
(paren
id|cpu_has_fxsr
)paren
(brace
r_return
id|tsk-&gt;thread.i387.fxsave.swd
suffix:semicolon
)brace
r_else
(brace
r_return
(paren
r_int
r_int
)paren
id|tsk-&gt;thread.i387.fsave.swd
suffix:semicolon
)brace
)brace
DECL|function|get_fpu_twd
r_int
r_int
id|get_fpu_twd
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_if
c_cond
(paren
id|cpu_has_fxsr
)paren
(brace
r_return
id|tsk-&gt;thread.i387.fxsave.twd
suffix:semicolon
)brace
r_else
(brace
r_return
(paren
r_int
r_int
)paren
id|tsk-&gt;thread.i387.fsave.twd
suffix:semicolon
)brace
)brace
DECL|function|get_fpu_mxcsr
r_int
r_int
id|get_fpu_mxcsr
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_if
c_cond
(paren
id|cpu_has_xmm
)paren
(brace
r_return
id|tsk-&gt;thread.i387.fxsave.mxcsr
suffix:semicolon
)brace
r_else
(brace
r_return
l_int|0x1f80
suffix:semicolon
)brace
)brace
DECL|function|set_fpu_cwd
r_void
id|set_fpu_cwd
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
r_int
id|cwd
)paren
(brace
r_if
c_cond
(paren
id|cpu_has_fxsr
)paren
(brace
id|tsk-&gt;thread.i387.fxsave.cwd
op_assign
id|cwd
suffix:semicolon
)brace
r_else
(brace
id|tsk-&gt;thread.i387.fsave.cwd
op_assign
(paren
(paren
r_int
)paren
id|cwd
op_or
l_int|0xffff0000u
)paren
suffix:semicolon
)brace
)brace
DECL|function|set_fpu_swd
r_void
id|set_fpu_swd
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
r_int
id|swd
)paren
(brace
r_if
c_cond
(paren
id|cpu_has_fxsr
)paren
(brace
id|tsk-&gt;thread.i387.fxsave.swd
op_assign
id|swd
suffix:semicolon
)brace
r_else
(brace
id|tsk-&gt;thread.i387.fsave.swd
op_assign
(paren
(paren
r_int
)paren
id|swd
op_or
l_int|0xffff0000u
)paren
suffix:semicolon
)brace
)brace
DECL|function|set_fpu_twd
r_void
id|set_fpu_twd
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
r_int
id|twd
)paren
(brace
r_if
c_cond
(paren
id|cpu_has_fxsr
)paren
(brace
id|tsk-&gt;thread.i387.fxsave.twd
op_assign
id|twd_i387_to_fxsr
c_func
(paren
id|twd
)paren
suffix:semicolon
)brace
r_else
(brace
id|tsk-&gt;thread.i387.fsave.twd
op_assign
(paren
(paren
r_int
)paren
id|twd
op_or
l_int|0xffff0000u
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * FXSR floating point environment conversions.&n; */
DECL|function|convert_fxsr_to_user
r_static
r_int
id|convert_fxsr_to_user
c_func
(paren
r_struct
id|_fpstate
id|__user
op_star
id|buf
comma
r_struct
id|i387_fxsave_struct
op_star
id|fxsave
)paren
(brace
r_int
r_int
id|env
(braket
l_int|7
)braket
suffix:semicolon
r_struct
id|_fpreg
id|__user
op_star
id|to
suffix:semicolon
r_struct
id|_fpxreg
op_star
id|from
suffix:semicolon
r_int
id|i
suffix:semicolon
id|env
(braket
l_int|0
)braket
op_assign
(paren
r_int
r_int
)paren
id|fxsave-&gt;cwd
op_or
l_int|0xffff0000ul
suffix:semicolon
id|env
(braket
l_int|1
)braket
op_assign
(paren
r_int
r_int
)paren
id|fxsave-&gt;swd
op_or
l_int|0xffff0000ul
suffix:semicolon
id|env
(braket
l_int|2
)braket
op_assign
id|twd_fxsr_to_i387
c_func
(paren
id|fxsave
)paren
suffix:semicolon
id|env
(braket
l_int|3
)braket
op_assign
id|fxsave-&gt;fip
suffix:semicolon
id|env
(braket
l_int|4
)braket
op_assign
id|fxsave-&gt;fcs
op_or
(paren
(paren
r_int
r_int
)paren
id|fxsave-&gt;fop
op_lshift
l_int|16
)paren
suffix:semicolon
id|env
(braket
l_int|5
)braket
op_assign
id|fxsave-&gt;foo
suffix:semicolon
id|env
(braket
l_int|6
)braket
op_assign
id|fxsave-&gt;fos
suffix:semicolon
r_if
c_cond
(paren
id|__copy_to_user
c_func
(paren
id|buf
comma
id|env
comma
l_int|7
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|to
op_assign
op_amp
id|buf-&gt;_st
(braket
l_int|0
)braket
suffix:semicolon
id|from
op_assign
(paren
r_struct
id|_fpxreg
op_star
)paren
op_amp
id|fxsave-&gt;st_space
(braket
l_int|0
)braket
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
comma
id|to
op_increment
comma
id|from
op_increment
)paren
(brace
r_int
r_int
op_star
id|t
op_assign
(paren
r_int
r_int
op_star
)paren
id|to
suffix:semicolon
r_int
r_int
op_star
id|f
op_assign
(paren
r_int
r_int
op_star
)paren
id|from
suffix:semicolon
r_if
c_cond
(paren
id|__put_user
c_func
(paren
op_star
id|f
comma
id|t
)paren
op_logical_or
id|__put_user
c_func
(paren
op_star
(paren
id|f
op_plus
l_int|1
)paren
comma
id|t
op_plus
l_int|1
)paren
op_logical_or
id|__put_user
c_func
(paren
id|from-&gt;exponent
comma
op_amp
id|to-&gt;exponent
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|convert_fxsr_from_user
r_static
r_int
id|convert_fxsr_from_user
c_func
(paren
r_struct
id|i387_fxsave_struct
op_star
id|fxsave
comma
r_struct
id|_fpstate
id|__user
op_star
id|buf
)paren
(brace
r_int
r_int
id|env
(braket
l_int|7
)braket
suffix:semicolon
r_struct
id|_fpxreg
op_star
id|to
suffix:semicolon
r_struct
id|_fpreg
id|__user
op_star
id|from
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|__copy_from_user
c_func
(paren
id|env
comma
id|buf
comma
l_int|7
op_star
r_sizeof
(paren
r_int
)paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|fxsave-&gt;cwd
op_assign
(paren
r_int
r_int
)paren
(paren
id|env
(braket
l_int|0
)braket
op_amp
l_int|0xffff
)paren
suffix:semicolon
id|fxsave-&gt;swd
op_assign
(paren
r_int
r_int
)paren
(paren
id|env
(braket
l_int|1
)braket
op_amp
l_int|0xffff
)paren
suffix:semicolon
id|fxsave-&gt;twd
op_assign
id|twd_i387_to_fxsr
c_func
(paren
(paren
r_int
r_int
)paren
(paren
id|env
(braket
l_int|2
)braket
op_amp
l_int|0xffff
)paren
)paren
suffix:semicolon
id|fxsave-&gt;fip
op_assign
id|env
(braket
l_int|3
)braket
suffix:semicolon
id|fxsave-&gt;fop
op_assign
(paren
r_int
r_int
)paren
(paren
(paren
id|env
(braket
l_int|4
)braket
op_amp
l_int|0xffff0000ul
)paren
op_rshift
l_int|16
)paren
suffix:semicolon
id|fxsave-&gt;fcs
op_assign
(paren
id|env
(braket
l_int|4
)braket
op_amp
l_int|0xffff
)paren
suffix:semicolon
id|fxsave-&gt;foo
op_assign
id|env
(braket
l_int|5
)braket
suffix:semicolon
id|fxsave-&gt;fos
op_assign
id|env
(braket
l_int|6
)braket
suffix:semicolon
id|to
op_assign
(paren
r_struct
id|_fpxreg
op_star
)paren
op_amp
id|fxsave-&gt;st_space
(braket
l_int|0
)braket
suffix:semicolon
id|from
op_assign
op_amp
id|buf-&gt;_st
(braket
l_int|0
)braket
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
comma
id|to
op_increment
comma
id|from
op_increment
)paren
(brace
r_int
r_int
op_star
id|t
op_assign
(paren
r_int
r_int
op_star
)paren
id|to
suffix:semicolon
r_int
r_int
op_star
id|f
op_assign
(paren
r_int
r_int
op_star
)paren
id|from
suffix:semicolon
r_if
c_cond
(paren
id|__get_user
c_func
(paren
op_star
id|t
comma
id|f
)paren
op_logical_or
id|__get_user
c_func
(paren
op_star
(paren
id|t
op_plus
l_int|1
)paren
comma
id|f
op_plus
l_int|1
)paren
op_logical_or
id|__get_user
c_func
(paren
id|to-&gt;exponent
comma
op_amp
id|from-&gt;exponent
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Signal frame handlers.&n; */
DECL|function|save_i387_fsave
r_static
r_inline
r_int
id|save_i387_fsave
c_func
(paren
r_struct
id|_fpstate
id|__user
op_star
id|buf
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
id|unlazy_fpu
c_func
(paren
id|tsk
)paren
suffix:semicolon
id|tsk-&gt;thread.i387.fsave.status
op_assign
id|tsk-&gt;thread.i387.fsave.swd
suffix:semicolon
r_if
c_cond
(paren
id|__copy_to_user
c_func
(paren
id|buf
comma
op_amp
id|tsk-&gt;thread.i387.fsave
comma
r_sizeof
(paren
r_struct
id|i387_fsave_struct
)paren
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|save_i387_fxsave
r_static
r_int
id|save_i387_fxsave
c_func
(paren
r_struct
id|_fpstate
id|__user
op_star
id|buf
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|unlazy_fpu
c_func
(paren
id|tsk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|convert_fxsr_to_user
c_func
(paren
id|buf
comma
op_amp
id|tsk-&gt;thread.i387.fxsave
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|tsk-&gt;thread.i387.fxsave.swd
comma
op_amp
id|buf-&gt;status
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|X86_FXSR_MAGIC
comma
op_amp
id|buf-&gt;magic
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|__copy_to_user
c_func
(paren
op_amp
id|buf-&gt;_fxsr_env
(braket
l_int|0
)braket
comma
op_amp
id|tsk-&gt;thread.i387.fxsave
comma
r_sizeof
(paren
r_struct
id|i387_fxsave_struct
)paren
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|save_i387
r_int
id|save_i387
c_func
(paren
r_struct
id|_fpstate
id|__user
op_star
id|buf
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|current-&gt;used_math
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* This will cause a &quot;finit&quot; to be triggered by the next&n;&t; * attempted FPU operation by the &squot;current&squot; process.&n;&t; */
id|current-&gt;used_math
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|HAVE_HWFP
)paren
(brace
r_if
c_cond
(paren
id|cpu_has_fxsr
)paren
(brace
r_return
id|save_i387_fxsave
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
id|save_i387_fsave
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_return
id|save_i387_soft
c_func
(paren
op_amp
id|current-&gt;thread.i387.soft
comma
id|buf
)paren
suffix:semicolon
)brace
)brace
DECL|function|restore_i387_fsave
r_static
r_inline
r_int
id|restore_i387_fsave
c_func
(paren
r_struct
id|_fpstate
id|__user
op_star
id|buf
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
id|clear_fpu
c_func
(paren
id|tsk
)paren
suffix:semicolon
r_return
id|__copy_from_user
c_func
(paren
op_amp
id|tsk-&gt;thread.i387.fsave
comma
id|buf
comma
r_sizeof
(paren
r_struct
id|i387_fsave_struct
)paren
)paren
suffix:semicolon
)brace
DECL|function|restore_i387_fxsave
r_static
r_int
id|restore_i387_fxsave
c_func
(paren
r_struct
id|_fpstate
id|__user
op_star
id|buf
)paren
(brace
r_int
id|err
suffix:semicolon
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
id|clear_fpu
c_func
(paren
id|tsk
)paren
suffix:semicolon
id|err
op_assign
id|__copy_from_user
c_func
(paren
op_amp
id|tsk-&gt;thread.i387.fxsave
comma
op_amp
id|buf-&gt;_fxsr_env
(braket
l_int|0
)braket
comma
r_sizeof
(paren
r_struct
id|i387_fxsave_struct
)paren
)paren
suffix:semicolon
multiline_comment|/* mxcsr reserved bits must be masked to zero for security reasons */
id|tsk-&gt;thread.i387.fxsave.mxcsr
op_and_assign
id|mxcsr_feature_mask
suffix:semicolon
r_return
id|err
ques
c_cond
l_int|1
suffix:colon
id|convert_fxsr_from_user
c_func
(paren
op_amp
id|tsk-&gt;thread.i387.fxsave
comma
id|buf
)paren
suffix:semicolon
)brace
DECL|function|restore_i387
r_int
id|restore_i387
c_func
(paren
r_struct
id|_fpstate
id|__user
op_star
id|buf
)paren
(brace
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|HAVE_HWFP
)paren
(brace
r_if
c_cond
(paren
id|cpu_has_fxsr
)paren
(brace
id|err
op_assign
id|restore_i387_fxsave
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
r_else
(brace
id|err
op_assign
id|restore_i387_fsave
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|err
op_assign
id|restore_i387_soft
c_func
(paren
op_amp
id|current-&gt;thread.i387.soft
comma
id|buf
)paren
suffix:semicolon
)brace
id|current-&gt;used_math
op_assign
l_int|1
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * ptrace request handlers.&n; */
DECL|function|get_fpregs_fsave
r_static
r_inline
r_int
id|get_fpregs_fsave
c_func
(paren
r_struct
id|user_i387_struct
id|__user
op_star
id|buf
comma
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_return
id|__copy_to_user
c_func
(paren
id|buf
comma
op_amp
id|tsk-&gt;thread.i387.fsave
comma
r_sizeof
(paren
r_struct
id|user_i387_struct
)paren
)paren
suffix:semicolon
)brace
DECL|function|get_fpregs_fxsave
r_static
r_inline
r_int
id|get_fpregs_fxsave
c_func
(paren
r_struct
id|user_i387_struct
id|__user
op_star
id|buf
comma
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_return
id|convert_fxsr_to_user
c_func
(paren
(paren
r_struct
id|_fpstate
id|__user
op_star
)paren
id|buf
comma
op_amp
id|tsk-&gt;thread.i387.fxsave
)paren
suffix:semicolon
)brace
DECL|function|get_fpregs
r_int
id|get_fpregs
c_func
(paren
r_struct
id|user_i387_struct
id|__user
op_star
id|buf
comma
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_if
c_cond
(paren
id|HAVE_HWFP
)paren
(brace
r_if
c_cond
(paren
id|cpu_has_fxsr
)paren
(brace
r_return
id|get_fpregs_fxsave
c_func
(paren
id|buf
comma
id|tsk
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
id|get_fpregs_fsave
c_func
(paren
id|buf
comma
id|tsk
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_return
id|save_i387_soft
c_func
(paren
op_amp
id|tsk-&gt;thread.i387.soft
comma
(paren
r_struct
id|_fpstate
id|__user
op_star
)paren
id|buf
)paren
suffix:semicolon
)brace
)brace
DECL|function|set_fpregs_fsave
r_static
r_inline
r_int
id|set_fpregs_fsave
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_struct
id|user_i387_struct
id|__user
op_star
id|buf
)paren
(brace
r_return
id|__copy_from_user
c_func
(paren
op_amp
id|tsk-&gt;thread.i387.fsave
comma
id|buf
comma
r_sizeof
(paren
r_struct
id|user_i387_struct
)paren
)paren
suffix:semicolon
)brace
DECL|function|set_fpregs_fxsave
r_static
r_inline
r_int
id|set_fpregs_fxsave
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_struct
id|user_i387_struct
id|__user
op_star
id|buf
)paren
(brace
r_return
id|convert_fxsr_from_user
c_func
(paren
op_amp
id|tsk-&gt;thread.i387.fxsave
comma
(paren
r_struct
id|_fpstate
id|__user
op_star
)paren
id|buf
)paren
suffix:semicolon
)brace
DECL|function|set_fpregs
r_int
id|set_fpregs
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_struct
id|user_i387_struct
id|__user
op_star
id|buf
)paren
(brace
r_if
c_cond
(paren
id|HAVE_HWFP
)paren
(brace
r_if
c_cond
(paren
id|cpu_has_fxsr
)paren
(brace
r_return
id|set_fpregs_fxsave
c_func
(paren
id|tsk
comma
id|buf
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
id|set_fpregs_fsave
c_func
(paren
id|tsk
comma
id|buf
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_return
id|restore_i387_soft
c_func
(paren
op_amp
id|tsk-&gt;thread.i387.soft
comma
(paren
r_struct
id|_fpstate
id|__user
op_star
)paren
id|buf
)paren
suffix:semicolon
)brace
)brace
DECL|function|get_fpxregs
r_int
id|get_fpxregs
c_func
(paren
r_struct
id|user_fxsr_struct
id|__user
op_star
id|buf
comma
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_if
c_cond
(paren
id|cpu_has_fxsr
)paren
(brace
r_if
c_cond
(paren
id|__copy_to_user
c_func
(paren
id|buf
comma
op_amp
id|tsk-&gt;thread.i387.fxsave
comma
r_sizeof
(paren
r_struct
id|user_fxsr_struct
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
)brace
DECL|function|set_fpxregs
r_int
id|set_fpxregs
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_struct
id|user_fxsr_struct
id|__user
op_star
id|buf
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|cpu_has_fxsr
)paren
(brace
r_if
c_cond
(paren
id|__copy_from_user
c_func
(paren
op_amp
id|tsk-&gt;thread.i387.fxsave
comma
id|buf
comma
r_sizeof
(paren
r_struct
id|user_fxsr_struct
)paren
)paren
)paren
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
multiline_comment|/* mxcsr reserved bits must be masked to zero for security reasons */
id|tsk-&gt;thread.i387.fxsave.mxcsr
op_and_assign
id|mxcsr_feature_mask
suffix:semicolon
)brace
r_else
(brace
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * FPU state for core dumps.&n; */
DECL|function|copy_fpu_fsave
r_static
r_inline
r_void
id|copy_fpu_fsave
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_struct
id|user_i387_struct
op_star
id|fpu
)paren
(brace
id|memcpy
c_func
(paren
id|fpu
comma
op_amp
id|tsk-&gt;thread.i387.fsave
comma
r_sizeof
(paren
r_struct
id|user_i387_struct
)paren
)paren
suffix:semicolon
)brace
DECL|function|copy_fpu_fxsave
r_static
r_inline
r_void
id|copy_fpu_fxsave
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_struct
id|user_i387_struct
op_star
id|fpu
)paren
(brace
r_int
r_int
op_star
id|to
suffix:semicolon
r_int
r_int
op_star
id|from
suffix:semicolon
r_int
id|i
suffix:semicolon
id|memcpy
c_func
(paren
id|fpu
comma
op_amp
id|tsk-&gt;thread.i387.fxsave
comma
l_int|7
op_star
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
id|to
op_assign
(paren
r_int
r_int
op_star
)paren
op_amp
id|fpu-&gt;st_space
(braket
l_int|0
)braket
suffix:semicolon
id|from
op_assign
(paren
r_int
r_int
op_star
)paren
op_amp
id|tsk-&gt;thread.i387.fxsave.st_space
(braket
l_int|0
)braket
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
comma
id|to
op_add_assign
l_int|5
comma
id|from
op_add_assign
l_int|8
)paren
(brace
id|memcpy
c_func
(paren
id|to
comma
id|from
comma
l_int|5
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|dump_fpu
r_int
id|dump_fpu
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_struct
id|user_i387_struct
op_star
id|fpu
)paren
(brace
r_int
id|fpvalid
suffix:semicolon
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
id|fpvalid
op_assign
id|tsk-&gt;used_math
suffix:semicolon
r_if
c_cond
(paren
id|fpvalid
)paren
(brace
id|unlazy_fpu
c_func
(paren
id|tsk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu_has_fxsr
)paren
(brace
id|copy_fpu_fxsave
c_func
(paren
id|tsk
comma
id|fpu
)paren
suffix:semicolon
)brace
r_else
(brace
id|copy_fpu_fsave
c_func
(paren
id|tsk
comma
id|fpu
)paren
suffix:semicolon
)brace
)brace
r_return
id|fpvalid
suffix:semicolon
)brace
DECL|function|dump_extended_fpu
r_int
id|dump_extended_fpu
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_struct
id|user_fxsr_struct
op_star
id|fpu
)paren
(brace
r_int
id|fpvalid
suffix:semicolon
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
id|fpvalid
op_assign
id|tsk-&gt;used_math
op_logical_and
id|cpu_has_fxsr
suffix:semicolon
r_if
c_cond
(paren
id|fpvalid
)paren
(brace
id|unlazy_fpu
c_func
(paren
id|tsk
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|fpu
comma
op_amp
id|tsk-&gt;thread.i387.fxsave
comma
r_sizeof
(paren
r_struct
id|user_fxsr_struct
)paren
)paren
suffix:semicolon
)brace
r_return
id|fpvalid
suffix:semicolon
)brace
DECL|function|dump_task_fpu
r_int
id|dump_task_fpu
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_struct
id|user_i387_struct
op_star
id|fpu
)paren
(brace
r_int
id|fpvalid
op_assign
id|tsk-&gt;used_math
suffix:semicolon
r_if
c_cond
(paren
id|fpvalid
)paren
(brace
r_if
c_cond
(paren
id|tsk
op_eq
id|current
)paren
id|unlazy_fpu
c_func
(paren
id|tsk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu_has_fxsr
)paren
id|copy_fpu_fxsave
c_func
(paren
id|tsk
comma
id|fpu
)paren
suffix:semicolon
r_else
id|copy_fpu_fsave
c_func
(paren
id|tsk
comma
id|fpu
)paren
suffix:semicolon
)brace
r_return
id|fpvalid
suffix:semicolon
)brace
DECL|function|dump_task_extended_fpu
r_int
id|dump_task_extended_fpu
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_struct
id|user_fxsr_struct
op_star
id|fpu
)paren
(brace
r_int
id|fpvalid
op_assign
id|tsk-&gt;used_math
op_logical_and
id|cpu_has_fxsr
suffix:semicolon
r_if
c_cond
(paren
id|fpvalid
)paren
(brace
r_if
c_cond
(paren
id|tsk
op_eq
id|current
)paren
id|unlazy_fpu
c_func
(paren
id|tsk
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|fpu
comma
op_amp
id|tsk-&gt;thread.i387.fxsave
comma
r_sizeof
(paren
op_star
id|fpu
)paren
)paren
suffix:semicolon
)brace
r_return
id|fpvalid
suffix:semicolon
)brace
eof
