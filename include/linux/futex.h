macro_line|#ifndef _LINUX_FUTEX_H
DECL|macro|_LINUX_FUTEX_H
mdefine_line|#define _LINUX_FUTEX_H
multiline_comment|/* Second argument to futex syscall */
DECL|macro|FUTEX_WAIT
mdefine_line|#define FUTEX_WAIT (0)
DECL|macro|FUTEX_WAKE
mdefine_line|#define FUTEX_WAKE (1)
DECL|macro|FUTEX_FD
mdefine_line|#define FUTEX_FD (2)
DECL|macro|FUTEX_REQUEUE
mdefine_line|#define FUTEX_REQUEUE (3)
id|asmlinkage
r_int
id|sys_futex
c_func
(paren
id|u32
id|__user
op_star
id|uaddr
comma
r_int
id|op
comma
r_int
id|val
comma
r_struct
id|timespec
id|__user
op_star
id|utime
comma
id|u32
id|__user
op_star
id|uaddr2
)paren
suffix:semicolon
r_int
id|do_futex
c_func
(paren
r_int
r_int
id|uaddr
comma
r_int
id|op
comma
r_int
id|val
comma
r_int
r_int
id|timeout
comma
r_int
r_int
id|uaddr2
comma
r_int
id|val2
)paren
suffix:semicolon
macro_line|#endif
eof
