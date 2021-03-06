multiline_comment|/*&n; * Copyright 2003 PathScale, Inc.&n; *&n; * Licensed under the GPL&n; */
DECL|macro|__FRAME_OFFSETS
mdefine_line|#define __FRAME_OFFSETS
macro_line|#include &quot;asm/ptrace.h&quot;
macro_line|#include &quot;linux/sched.h&quot;
macro_line|#include &quot;linux/errno.h&quot;
macro_line|#include &quot;asm/elf.h&quot;
multiline_comment|/* XXX x86_64 */
DECL|variable|not_ss
r_int
r_int
id|not_ss
suffix:semicolon
DECL|variable|not_ds
r_int
r_int
id|not_ds
suffix:semicolon
DECL|variable|not_es
r_int
r_int
id|not_es
suffix:semicolon
DECL|macro|SC_SS
mdefine_line|#define SC_SS(r) (not_ss)
DECL|macro|SC_DS
mdefine_line|#define SC_DS(r) (not_ds)
DECL|macro|SC_ES
mdefine_line|#define SC_ES(r) (not_es)
multiline_comment|/* determines which flags the user has access to. */
multiline_comment|/* 1 = access 0 = no access */
DECL|macro|FLAG_MASK
mdefine_line|#define FLAG_MASK 0x44dd5UL
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
r_int
r_int
id|tmp
suffix:semicolon
macro_line|#ifdef TIF_IA32
multiline_comment|/* Some code in the 64bit emulation may not be 64bit clean.&n;&t;   Don&squot;t take any chances. */
r_if
c_cond
(paren
id|test_tsk_thread_flag
c_func
(paren
id|child
comma
id|TIF_IA32
)paren
)paren
id|value
op_and_assign
l_int|0xffffffff
suffix:semicolon
macro_line|#endif
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
id|FS_BASE
suffix:colon
r_case
id|GS_BASE
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|value
op_rshift
l_int|48
)paren
op_eq
l_int|0
op_logical_or
(paren
id|value
op_rshift
l_int|48
)paren
op_eq
l_int|0xffff
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_break
suffix:semicolon
r_case
id|EFLAGS
suffix:colon
id|value
op_and_assign
id|FLAG_MASK
suffix:semicolon
id|tmp
op_assign
id|PT_REGS_EFLAGS
c_func
(paren
op_amp
id|child-&gt;thread.regs
)paren
op_amp
op_complement
id|FLAG_MASK
suffix:semicolon
id|value
op_or_assign
id|tmp
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
macro_line|#ifdef TIF_IA32
r_if
c_cond
(paren
id|test_tsk_thread_flag
c_func
(paren
id|child
comma
id|TIF_IA32
)paren
)paren
id|retval
op_and_assign
l_int|0xffffffff
suffix:semicolon
macro_line|#endif
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|function|arch_switch
r_void
id|arch_switch
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* XXX&n;&t;printk(&quot;arch_switch&bslash;n&quot;);&n;*/
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
id|panic
c_func
(paren
l_string|&quot;is_syscall&quot;
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
id|panic
c_func
(paren
l_string|&quot;dump_fpu&quot;
)paren
suffix:semicolon
r_return
l_int|1
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
id|panic
c_func
(paren
l_string|&quot;get_fpregs&quot;
)paren
suffix:semicolon
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
id|panic
c_func
(paren
l_string|&quot;set_fpregs&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
id|panic
c_func
(paren
l_string|&quot;get_fpxregs&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
id|panic
c_func
(paren
l_string|&quot;set_fxpregs&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
