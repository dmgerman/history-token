macro_line|#ifndef _LINUX_PTRACE_H
DECL|macro|_LINUX_PTRACE_H
mdefine_line|#define _LINUX_PTRACE_H
multiline_comment|/* ptrace.h */
multiline_comment|/* structs and defines to help the user use the ptrace system call. */
macro_line|#include &lt;linux/compiler.h&gt;
multiline_comment|/* has the defines to get at the registers. */
DECL|macro|PTRACE_TRACEME
mdefine_line|#define PTRACE_TRACEME&t;&t;   0
DECL|macro|PTRACE_PEEKTEXT
mdefine_line|#define PTRACE_PEEKTEXT&t;&t;   1
DECL|macro|PTRACE_PEEKDATA
mdefine_line|#define PTRACE_PEEKDATA&t;&t;   2
DECL|macro|PTRACE_PEEKUSR
mdefine_line|#define PTRACE_PEEKUSR&t;&t;   3
DECL|macro|PTRACE_POKETEXT
mdefine_line|#define PTRACE_POKETEXT&t;&t;   4
DECL|macro|PTRACE_POKEDATA
mdefine_line|#define PTRACE_POKEDATA&t;&t;   5
DECL|macro|PTRACE_POKEUSR
mdefine_line|#define PTRACE_POKEUSR&t;&t;   6
DECL|macro|PTRACE_CONT
mdefine_line|#define PTRACE_CONT&t;&t;   7
DECL|macro|PTRACE_KILL
mdefine_line|#define PTRACE_KILL&t;&t;   8
DECL|macro|PTRACE_SINGLESTEP
mdefine_line|#define PTRACE_SINGLESTEP&t;   9
DECL|macro|PTRACE_ATTACH
mdefine_line|#define PTRACE_ATTACH&t;&t;0x10
DECL|macro|PTRACE_DETACH
mdefine_line|#define PTRACE_DETACH&t;&t;0x11
DECL|macro|PTRACE_SYSCALL
mdefine_line|#define PTRACE_SYSCALL&t;&t;  24
multiline_comment|/* 0x4200-0x4300 are reserved for architecture-independent additions.  */
DECL|macro|PTRACE_SETOPTIONS
mdefine_line|#define PTRACE_SETOPTIONS&t;0x4200
multiline_comment|/* options set using PTRACE_SETOPTIONS */
DECL|macro|PTRACE_O_TRACESYSGOOD
mdefine_line|#define PTRACE_O_TRACESYSGOOD&t;0x00000001
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
r_extern
r_int
id|ptrace_readdata
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
r_int
id|src
comma
r_char
op_star
id|dst
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|ptrace_writedata
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_char
op_star
id|src
comma
r_int
r_int
id|dst
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|ptrace_attach
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
suffix:semicolon
r_extern
r_int
id|ptrace_detach
c_func
(paren
r_struct
id|task_struct
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|ptrace_disable
c_func
(paren
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ptrace_check_attach
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
id|kill
)paren
suffix:semicolon
r_extern
r_int
id|ptrace_request
c_func
(paren
r_struct
id|task_struct
op_star
id|child
comma
r_int
id|request
comma
r_int
id|addr
comma
r_int
id|data
)paren
suffix:semicolon
r_extern
r_void
id|__ptrace_link
c_func
(paren
r_struct
id|task_struct
op_star
id|child
comma
r_struct
id|task_struct
op_star
id|new_parent
)paren
suffix:semicolon
r_extern
r_void
id|__ptrace_unlink
c_func
(paren
r_struct
id|task_struct
op_star
id|child
)paren
suffix:semicolon
DECL|function|ptrace_link
r_static
r_inline
r_void
id|ptrace_link
c_func
(paren
r_struct
id|task_struct
op_star
id|child
comma
r_struct
id|task_struct
op_star
id|new_parent
)paren
(brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|child-&gt;ptrace
)paren
)paren
id|__ptrace_link
c_func
(paren
id|child
comma
id|new_parent
)paren
suffix:semicolon
)brace
DECL|function|ptrace_unlink
r_static
r_inline
r_void
id|ptrace_unlink
c_func
(paren
r_struct
id|task_struct
op_star
id|child
)paren
(brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|child-&gt;ptrace
)paren
)paren
id|__ptrace_unlink
c_func
(paren
id|child
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
