macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;asm/user.h&gt;
r_extern
r_int
id|debugreg
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;#define TASK_DEBUGREGS(task) ((unsigned long *) &quot;
l_string|&quot;&amp;(((char *) (task))[%d]))&bslash;n&quot;
comma
id|debugreg
c_func
(paren
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
