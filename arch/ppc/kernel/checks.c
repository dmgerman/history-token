macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/*&n; * Do various before compile checks of data structures&n; * -- Cort&n; */
DECL|function|main
r_int
id|main
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
macro_line|#if 0
r_if
c_cond
(paren
r_sizeof
(paren
r_struct
id|thread_struct
)paren
op_mod
l_int|16
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;Thread struct is not modulo 16 bytes: &quot;
l_string|&quot;%d bytes total, %d bytes off&bslash;n&quot;
comma
r_sizeof
(paren
r_struct
id|thread_struct
)paren
comma
r_sizeof
(paren
r_struct
id|thread_struct
)paren
op_mod
l_int|16
)paren
suffix:semicolon
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|#endif&t;
r_if
c_cond
(paren
r_sizeof
(paren
r_struct
id|pt_regs
)paren
op_mod
l_int|16
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;pt_regs struct is not modulo 16 bytes: &quot;
l_string|&quot;%d bytes total, %d bytes off&bslash;n&quot;
comma
r_sizeof
(paren
r_struct
id|pt_regs
)paren
comma
r_sizeof
(paren
r_struct
id|pt_regs
)paren
op_mod
l_int|16
)paren
suffix:semicolon
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;Task size        : %d bytes&bslash;n&quot;
l_string|&quot;Tss size         : %d bytes&bslash;n&quot;
l_string|&quot;pt_regs size     : %d bytes&bslash;n&quot;
l_string|&quot;Kernel stack size: %d bytes&bslash;n&quot;
comma
r_sizeof
(paren
r_struct
id|task_struct
)paren
comma
r_sizeof
(paren
r_struct
id|thread_struct
)paren
comma
r_sizeof
(paren
r_struct
id|pt_regs
)paren
comma
r_sizeof
(paren
r_union
id|task_union
)paren
op_minus
r_sizeof
(paren
r_struct
id|task_struct
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
eof
