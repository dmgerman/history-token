multiline_comment|/* &n; * Copyright (C) 2000, 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &quot;linux/sched.h&quot;
macro_line|#include &quot;asm/elf.h&quot;
macro_line|#include &quot;asm/ptrace.h&quot;
macro_line|#include &quot;asm/uaccess.h&quot;
macro_line|#include &quot;asm/unistd.h&quot;
macro_line|#include &quot;sysdep/ptrace.h&quot;
macro_line|#include &quot;sysdep/sigcontext.h&quot;
macro_line|#include &quot;sysdep/sc.h&quot;
DECL|function|arch_switch
r_void
id|arch_switch
c_func
(paren
r_void
)paren
(brace
id|update_debugregs
c_func
(paren
id|current-&gt;thread.arch.debugregs_seq
)paren
suffix:semicolon
)brace
DECL|function|is_syscall
r_int
id|is_syscall
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|instr
suffix:semicolon
r_int
id|n
suffix:semicolon
id|n
op_assign
id|copy_from_user
c_func
(paren
op_amp
id|instr
comma
(paren
r_void
id|__user
op_star
)paren
id|addr
comma
r_sizeof
(paren
id|instr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;is_syscall : failed to read instruction from 0x%lx&bslash;n&quot;
comma
id|addr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* int 0x80 or sysenter */
r_return
(paren
id|instr
op_eq
l_int|0x80cd
)paren
op_logical_or
(paren
id|instr
op_eq
l_int|0x340f
)paren
suffix:semicolon
)brace
multiline_comment|/* determines which flags the user has access to. */
multiline_comment|/* 1 = access 0 = no access */
DECL|macro|FLAG_MASK
mdefine_line|#define FLAG_MASK 0x00044dd5
DECL|function|putreg
r_int
id|putreg
c_func
(paren
r_struct
id|task_struct
op_star
id|child
comma
r_int
id|regno
comma
r_int
r_int
id|value
)paren
(brace
id|regno
op_rshift_assign
l_int|2
suffix:semicolon
r_switch
c_cond
(paren
id|regno
)paren
(brace
r_case
id|FS
suffix:colon
r_if
c_cond
(paren
id|value
op_logical_and
(paren
id|value
op_amp
l_int|3
)paren
op_ne
l_int|3
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|PT_REGS_FS
c_func
(paren
op_amp
id|child-&gt;thread.regs
)paren
op_assign
id|value
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|GS
suffix:colon
r_if
c_cond
(paren
id|value
op_logical_and
(paren
id|value
op_amp
l_int|3
)paren
op_ne
l_int|3
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|PT_REGS_GS
c_func
(paren
op_amp
id|child-&gt;thread.regs
)paren
op_assign
id|value
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|DS
suffix:colon
r_case
id|ES
suffix:colon
r_if
c_cond
(paren
id|value
op_logical_and
(paren
id|value
op_amp
l_int|3
)paren
op_ne
l_int|3
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|value
op_and_assign
l_int|0xffff
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SS
suffix:colon
r_case
id|CS
suffix:colon
r_if
c_cond
(paren
(paren
id|value
op_amp
l_int|3
)paren
op_ne
l_int|3
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|value
op_and_assign
l_int|0xffff
suffix:semicolon
r_break
suffix:semicolon
r_case
id|EFL
suffix:colon
id|value
op_and_assign
id|FLAG_MASK
suffix:semicolon
id|value
op_or_assign
id|PT_REGS_EFLAGS
c_func
(paren
op_amp
id|child-&gt;thread.regs
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|PT_REGS_SET
c_func
(paren
op_amp
id|child-&gt;thread.regs
comma
id|regno
comma
id|value
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|getreg
r_int
r_int
id|getreg
c_func
(paren
r_struct
id|task_struct
op_star
id|child
comma
r_int
id|regno
)paren
(brace
r_int
r_int
id|retval
op_assign
op_complement
l_int|0UL
suffix:semicolon
id|regno
op_rshift_assign
l_int|2
suffix:semicolon
r_switch
c_cond
(paren
id|regno
)paren
(brace
r_case
id|FS
suffix:colon
r_case
id|GS
suffix:colon
r_case
id|DS
suffix:colon
r_case
id|ES
suffix:colon
r_case
id|SS
suffix:colon
r_case
id|CS
suffix:colon
id|retval
op_assign
l_int|0xffff
suffix:semicolon
multiline_comment|/* fall through */
r_default
suffix:colon
id|retval
op_and_assign
id|PT_REG
c_func
(paren
op_amp
id|child-&gt;thread.regs
comma
id|regno
)paren
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|struct|i387_fxsave_struct
r_struct
id|i387_fxsave_struct
(brace
DECL|member|cwd
r_int
r_int
id|cwd
suffix:semicolon
DECL|member|swd
r_int
r_int
id|swd
suffix:semicolon
DECL|member|twd
r_int
r_int
id|twd
suffix:semicolon
DECL|member|fop
r_int
r_int
id|fop
suffix:semicolon
DECL|member|fip
r_int
id|fip
suffix:semicolon
DECL|member|fcs
r_int
id|fcs
suffix:semicolon
DECL|member|foo
r_int
id|foo
suffix:semicolon
DECL|member|fos
r_int
id|fos
suffix:semicolon
DECL|member|mxcsr
r_int
id|mxcsr
suffix:semicolon
DECL|member|reserved
r_int
id|reserved
suffix:semicolon
DECL|member|st_space
r_int
id|st_space
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* 8*16 bytes for each FP-reg = 128 bytes */
DECL|member|xmm_space
r_int
id|xmm_space
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* 8*16 bytes for each XMM-reg = 128 bytes */
DECL|member|padding
r_int
id|padding
(braket
l_int|56
)braket
suffix:semicolon
)brace
suffix:semicolon
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
l_int|0xffff0000
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
multiline_comment|/*&n; * FXSR floating point environment conversions.&n; */
macro_line|#ifdef CONFIG_MODE_TT
DECL|function|convert_fxsr_to_user_tt
r_static
r_inline
r_int
id|convert_fxsr_to_user_tt
c_func
(paren
r_struct
id|_fpstate
id|__user
op_star
id|buf
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|i387_fxsave_struct
op_star
id|fxsave
op_assign
id|SC_FXSR_ENV
c_func
(paren
id|PT_REGS_SC
c_func
(paren
id|regs
)paren
)paren
suffix:semicolon
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
l_int|0xffff0000
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
l_int|0xffff0000
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
r_if
c_cond
(paren
id|__copy_to_user
c_func
(paren
id|to
comma
id|from
comma
r_sizeof
(paren
op_star
id|to
)paren
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
macro_line|#endif
DECL|function|convert_fxsr_to_user
r_static
r_inline
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
id|pt_regs
op_star
id|regs
)paren
(brace
r_return
id|CHOOSE_MODE
c_func
(paren
id|convert_fxsr_to_user_tt
c_func
(paren
id|buf
comma
id|regs
)paren
comma
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_MODE_TT
DECL|function|convert_fxsr_from_user_tt
r_static
r_inline
r_int
id|convert_fxsr_from_user_tt
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_struct
id|_fpstate
id|__user
op_star
id|buf
)paren
(brace
r_struct
id|i387_fxsave_struct
op_star
id|fxsave
op_assign
id|SC_FXSR_ENV
c_func
(paren
id|PT_REGS_SC
c_func
(paren
id|regs
)paren
)paren
suffix:semicolon
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
l_int|0xffff0000
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
r_if
c_cond
(paren
id|__copy_from_user
c_func
(paren
id|to
comma
id|from
comma
r_sizeof
(paren
op_star
id|from
)paren
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
macro_line|#endif
DECL|function|convert_fxsr_from_user
r_static
r_inline
r_int
id|convert_fxsr_from_user
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_struct
id|_fpstate
id|__user
op_star
id|buf
)paren
(brace
r_return
id|CHOOSE_MODE
c_func
(paren
id|convert_fxsr_from_user_tt
c_func
(paren
id|regs
comma
id|buf
)paren
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|get_fpregs
r_int
id|get_fpregs
c_func
(paren
r_int
r_int
id|buf
comma
r_struct
id|task_struct
op_star
id|child
)paren
(brace
r_int
id|err
suffix:semicolon
id|err
op_assign
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
id|child-&gt;thread.regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_else
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|set_fpregs
r_int
id|set_fpregs
c_func
(paren
r_int
r_int
id|buf
comma
r_struct
id|task_struct
op_star
id|child
)paren
(brace
r_int
id|err
suffix:semicolon
id|err
op_assign
id|convert_fxsr_from_user
c_func
(paren
op_amp
id|child-&gt;thread.regs
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
r_if
c_cond
(paren
id|err
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_else
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_MODE_TT
DECL|function|get_fpxregs_tt
r_int
id|get_fpxregs_tt
c_func
(paren
r_int
r_int
id|buf
comma
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_struct
id|pt_regs
op_star
id|regs
op_assign
op_amp
id|tsk-&gt;thread.regs
suffix:semicolon
r_struct
id|i387_fxsave_struct
op_star
id|fxsave
op_assign
id|SC_FXSR_ENV
c_func
(paren
id|PT_REGS_SC
c_func
(paren
id|regs
)paren
)paren
suffix:semicolon
r_int
id|err
suffix:semicolon
id|err
op_assign
id|__copy_to_user
c_func
(paren
(paren
r_void
id|__user
op_star
)paren
id|buf
comma
id|fxsave
comma
r_sizeof
(paren
r_struct
id|user_fxsr_struct
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_else
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
DECL|function|get_fpxregs
r_int
id|get_fpxregs
c_func
(paren
r_int
r_int
id|buf
comma
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_return
id|CHOOSE_MODE
c_func
(paren
id|get_fpxregs_tt
c_func
(paren
id|buf
comma
id|tsk
)paren
comma
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_MODE_TT
DECL|function|set_fpxregs_tt
r_int
id|set_fpxregs_tt
c_func
(paren
r_int
r_int
id|buf
comma
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_struct
id|pt_regs
op_star
id|regs
op_assign
op_amp
id|tsk-&gt;thread.regs
suffix:semicolon
r_struct
id|i387_fxsave_struct
op_star
id|fxsave
op_assign
id|SC_FXSR_ENV
c_func
(paren
id|PT_REGS_SC
c_func
(paren
id|regs
)paren
)paren
suffix:semicolon
r_int
id|err
suffix:semicolon
id|err
op_assign
id|__copy_from_user
c_func
(paren
id|fxsave
comma
(paren
r_void
id|__user
op_star
)paren
id|buf
comma
r_sizeof
(paren
r_struct
id|user_fxsr_struct
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_else
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
DECL|function|set_fpxregs
r_int
id|set_fpxregs
c_func
(paren
r_int
r_int
id|buf
comma
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_return
id|CHOOSE_MODE
c_func
(paren
id|set_fpxregs_tt
c_func
(paren
id|buf
comma
id|tsk
)paren
comma
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#ifdef notdef
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
id|elf_fpregset_t
op_star
id|fpu
)paren
(brace
id|fpu-&gt;cwd
op_assign
(paren
(paren
(paren
id|SC_FP_CW
c_func
(paren
id|PT_REGS_SC
c_func
(paren
id|regs
)paren
)paren
op_amp
l_int|0xffff
)paren
op_lshift
l_int|16
)paren
op_or
(paren
id|SC_FP_SW
c_func
(paren
id|PT_REGS_SC
c_func
(paren
id|regs
)paren
)paren
op_amp
l_int|0xffff
)paren
)paren
suffix:semicolon
id|fpu-&gt;swd
op_assign
id|SC_FP_CSSEL
c_func
(paren
id|PT_REGS_SC
c_func
(paren
id|regs
)paren
)paren
op_amp
l_int|0xffff
suffix:semicolon
id|fpu-&gt;twd
op_assign
id|SC_FP_IPOFF
c_func
(paren
id|PT_REGS_SC
c_func
(paren
id|regs
)paren
)paren
suffix:semicolon
id|fpu-&gt;fip
op_assign
id|SC_FP_CSSEL
c_func
(paren
id|PT_REGS_SC
c_func
(paren
id|regs
)paren
)paren
op_amp
l_int|0xffff
suffix:semicolon
id|fpu-&gt;fcs
op_assign
id|SC_FP_DATAOFF
c_func
(paren
id|PT_REGS_SC
c_func
(paren
id|regs
)paren
)paren
suffix:semicolon
id|fpu-&gt;foo
op_assign
id|SC_FP_DATASEL
c_func
(paren
id|PT_REGS_SC
c_func
(paren
id|regs
)paren
)paren
suffix:semicolon
id|fpu-&gt;fos
op_assign
l_int|0
suffix:semicolon
id|memcpy
c_func
(paren
id|fpu-&gt;st_space
comma
(paren
r_void
op_star
)paren
id|SC_FP_ST
c_func
(paren
id|PT_REGS_SC
c_func
(paren
id|regs
)paren
)paren
comma
r_sizeof
(paren
id|fpu-&gt;st_space
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_MODE_TT
DECL|function|copy_fpu_fxsave_tt
r_static
r_inline
r_void
id|copy_fpu_fxsave_tt
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
id|buf
)paren
(brace
r_struct
id|i387_fxsave_struct
op_star
id|fpu
op_assign
id|SC_FXSR_ENV
c_func
(paren
id|PT_REGS_SC
c_func
(paren
id|regs
)paren
)paren
suffix:semicolon
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
id|buf
comma
id|fpu
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
id|buf-&gt;st_space
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
id|fpu-&gt;st_space
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
macro_line|#endif
DECL|function|copy_fpu_fxsave
r_static
r_inline
r_void
id|copy_fpu_fxsave
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
id|buf
)paren
(brace
(paren
r_void
)paren
id|CHOOSE_MODE
c_func
(paren
id|copy_fpu_fxsave_tt
c_func
(paren
id|regs
comma
id|buf
)paren
comma
l_int|0
)paren
suffix:semicolon
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
id|elf_fpregset_t
op_star
id|fpu
)paren
(brace
id|copy_fpu_fxsave
c_func
(paren
id|regs
comma
(paren
r_struct
id|user_i387_struct
op_star
)paren
id|fpu
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
