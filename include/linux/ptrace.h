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
DECL|macro|PTRACE_GETEVENTMSG
mdefine_line|#define PTRACE_GETEVENTMSG&t;0x4201
DECL|macro|PTRACE_GETSIGINFO
mdefine_line|#define PTRACE_GETSIGINFO&t;0x4202
DECL|macro|PTRACE_SETSIGINFO
mdefine_line|#define PTRACE_SETSIGINFO&t;0x4203
multiline_comment|/* options set using PTRACE_SETOPTIONS */
DECL|macro|PTRACE_O_TRACESYSGOOD
mdefine_line|#define PTRACE_O_TRACESYSGOOD&t;0x00000001
DECL|macro|PTRACE_O_TRACEFORK
mdefine_line|#define PTRACE_O_TRACEFORK&t;0x00000002
DECL|macro|PTRACE_O_TRACEVFORK
mdefine_line|#define PTRACE_O_TRACEVFORK&t;0x00000004
DECL|macro|PTRACE_O_TRACECLONE
mdefine_line|#define PTRACE_O_TRACECLONE&t;0x00000008
DECL|macro|PTRACE_O_TRACEEXEC
mdefine_line|#define PTRACE_O_TRACEEXEC&t;0x00000010
DECL|macro|PTRACE_O_TRACEVFORKDONE
mdefine_line|#define PTRACE_O_TRACEVFORKDONE&t;0x00000020
DECL|macro|PTRACE_O_TRACEEXIT
mdefine_line|#define PTRACE_O_TRACEEXIT&t;0x00000040
multiline_comment|/* Wait extended result codes for the above trace options.  */
DECL|macro|PTRACE_EVENT_FORK
mdefine_line|#define PTRACE_EVENT_FORK&t;1
DECL|macro|PTRACE_EVENT_VFORK
mdefine_line|#define PTRACE_EVENT_VFORK&t;2
DECL|macro|PTRACE_EVENT_CLONE
mdefine_line|#define PTRACE_EVENT_CLONE&t;3
DECL|macro|PTRACE_EVENT_EXEC
mdefine_line|#define PTRACE_EVENT_EXEC&t;4
DECL|macro|PTRACE_EVENT_VFORK_DONE
mdefine_line|#define PTRACE_EVENT_VFORK_DONE&t;5
DECL|macro|PTRACE_EVENT_EXIT
mdefine_line|#define PTRACE_EVENT_EXIT&t;6
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
id|ptrace_notify
c_func
(paren
r_int
id|exit_code
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
