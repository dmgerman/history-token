macro_line|#include &quot;linux/stddef.h&quot;
macro_line|#include &quot;linux/sched.h&quot;
DECL|function|debugreg
r_int
id|debugreg
c_func
(paren
r_void
)paren
(brace
r_return
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.arch.debugregs
)paren
suffix:semicolon
)brace
eof
