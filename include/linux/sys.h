macro_line|#ifndef _LINUX_SYS_H
DECL|macro|_LINUX_SYS_H
mdefine_line|#define _LINUX_SYS_H
multiline_comment|/*&n; * system call entry points ... but not all are defined&n; */
DECL|macro|NR_syscalls
mdefine_line|#define NR_syscalls 256
multiline_comment|/*&n; * These are system calls that will be removed at some time&n; * due to newer versions existing..&n; * (please be careful - ibcs2 may need some of these).&n; */
macro_line|#ifdef notdef
DECL|macro|_sys_waitpid
mdefine_line|#define _sys_waitpid&t;_sys_old_syscall&t;/* _sys_wait4 */
DECL|macro|_sys_olduname
mdefine_line|#define _sys_olduname&t;_sys_old_syscall&t;/* _sys_newuname */
DECL|macro|_sys_uname
mdefine_line|#define _sys_uname&t;_sys_old_syscall&t;/* _sys_newuname */
DECL|macro|_sys_stat
mdefine_line|#define _sys_stat&t;_sys_old_syscall&t;/* _sys_newstat */
DECL|macro|_sys_fstat
mdefine_line|#define _sys_fstat&t;_sys_old_syscall&t;/* _sys_newfstat */
DECL|macro|_sys_lstat
mdefine_line|#define _sys_lstat&t;_sys_old_syscall&t;/* _sys_newlstat */
DECL|macro|_sys_signal
mdefine_line|#define _sys_signal&t;_sys_old_syscall&t;/* _sys_sigaction */
DECL|macro|_sys_sgetmask
mdefine_line|#define _sys_sgetmask&t;_sys_old_syscall&t;/* _sys_sigprocmask */
DECL|macro|_sys_ssetmask
mdefine_line|#define _sys_ssetmask&t;_sys_old_syscall&t;/* _sys_sigprocmask */
macro_line|#endif
multiline_comment|/*&n; * These are system calls that haven&squot;t been implemented yet&n; * but have an entry in the table for future expansion..&n; */
macro_line|#endif
eof
