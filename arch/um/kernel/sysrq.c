multiline_comment|/* &n; * Copyright (C) 2001 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/sched.h&quot;
macro_line|#include &quot;linux/kernel.h&quot;
macro_line|#include &quot;linux/module.h&quot;
macro_line|#include &quot;asm/page.h&quot;
macro_line|#include &quot;asm/processor.h&quot;
macro_line|#include &quot;sysrq.h&quot;
macro_line|#include &quot;user_util.h&quot;
DECL|function|show_trace
r_void
id|show_trace
c_func
(paren
r_int
r_int
op_star
id|stack
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|stack
)paren
id|stack
op_assign
(paren
r_int
r_int
op_star
)paren
op_amp
id|stack
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Call Trace: &quot;
)paren
suffix:semicolon
id|i
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
(paren
(paren
r_int
)paren
id|stack
op_amp
(paren
id|THREAD_SIZE
op_minus
l_int|1
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|addr
op_assign
op_star
id|stack
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|kernel_text_address
c_func
(paren
id|addr
)paren
)paren
(brace
r_if
c_cond
(paren
id|i
op_logical_and
(paren
(paren
id|i
op_mod
l_int|6
)paren
op_eq
l_int|0
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;&bslash;n   &quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;[&lt;%08lx&gt;] &quot;
comma
id|addr
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The architecture-independent dump_stack generator&n; */
DECL|function|dump_stack
r_void
id|dump_stack
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|stack
suffix:semicolon
id|show_trace
c_func
(paren
op_amp
id|stack
)paren
suffix:semicolon
)brace
DECL|function|show_trace_task
r_void
id|show_trace_task
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_int
r_int
id|esp
op_assign
id|PT_REGS_SP
c_func
(paren
op_amp
id|tsk-&gt;thread.regs
)paren
suffix:semicolon
multiline_comment|/* User space on another CPU? */
r_if
c_cond
(paren
(paren
id|esp
op_xor
(paren
r_int
r_int
)paren
id|tsk
)paren
op_amp
(paren
id|PAGE_MASK
op_lshift
l_int|1
)paren
)paren
r_return
suffix:semicolon
id|show_trace
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|esp
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
