macro_line|#include &quot;linux/config.h&quot;
macro_line|#include &quot;linux/stddef.h&quot;
macro_line|#include &quot;linux/sched.h&quot;
r_extern
r_void
id|print_head
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|print_constant_ptr
c_func
(paren
r_char
op_star
id|name
comma
r_int
id|value
)paren
suffix:semicolon
r_extern
r_void
id|print_constant
c_func
(paren
r_char
op_star
id|name
comma
r_char
op_star
id|type
comma
r_int
id|value
)paren
suffix:semicolon
r_extern
r_void
id|print_tail
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|THREAD_OFFSET
mdefine_line|#define THREAD_OFFSET(field) offsetof(struct task_struct, thread.field)
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
id|print_head
c_func
(paren
)paren
suffix:semicolon
id|print_constant_ptr
c_func
(paren
l_string|&quot;TASK_DEBUGREGS&quot;
comma
id|THREAD_OFFSET
c_func
(paren
id|arch.debugregs
)paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MODE_TT
id|print_constant
c_func
(paren
l_string|&quot;TASK_EXTERN_PID&quot;
comma
l_string|&quot;int&quot;
comma
id|THREAD_OFFSET
c_func
(paren
id|mode.tt.extern_pid
)paren
)paren
suffix:semicolon
macro_line|#endif
id|print_tail
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
