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
r_extern
id|asmlinkage
r_int
id|sys_futex
c_func
(paren
id|u32
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
op_star
id|utime
)paren
suffix:semicolon
macro_line|#endif
eof
