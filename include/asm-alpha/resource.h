macro_line|#ifndef _ALPHA_RESOURCE_H
DECL|macro|_ALPHA_RESOURCE_H
mdefine_line|#define _ALPHA_RESOURCE_H
multiline_comment|/*&n; * Resource limits&n; */
DECL|macro|RLIMIT_CPU
mdefine_line|#define RLIMIT_CPU&t;0&t;&t;/* CPU time in ms */
DECL|macro|RLIMIT_FSIZE
mdefine_line|#define RLIMIT_FSIZE&t;1&t;&t;/* Maximum filesize */
DECL|macro|RLIMIT_DATA
mdefine_line|#define RLIMIT_DATA&t;2&t;&t;/* max data size */
DECL|macro|RLIMIT_STACK
mdefine_line|#define RLIMIT_STACK&t;3&t;&t;/* max stack size */
DECL|macro|RLIMIT_CORE
mdefine_line|#define RLIMIT_CORE&t;4&t;&t;/* max core file size */
DECL|macro|RLIMIT_RSS
mdefine_line|#define RLIMIT_RSS&t;5&t;&t;/* max resident set size */
DECL|macro|RLIMIT_NOFILE
mdefine_line|#define RLIMIT_NOFILE&t;6&t;&t;/* max number of open files */
DECL|macro|RLIMIT_AS
mdefine_line|#define RLIMIT_AS&t;7&t;&t;/* address space limit(?) */
DECL|macro|RLIMIT_NPROC
mdefine_line|#define RLIMIT_NPROC&t;8&t;&t;/* max number of processes */
DECL|macro|RLIMIT_MEMLOCK
mdefine_line|#define RLIMIT_MEMLOCK&t;9&t;&t;/* max locked-in-memory address space */
DECL|macro|RLIMIT_LOCKS
mdefine_line|#define RLIMIT_LOCKS&t;10&t;&t;/* maximum file locks held */
DECL|macro|RLIMIT_SIGPENDING
mdefine_line|#define RLIMIT_SIGPENDING 11&t;&t;/* max number of pending signals */
DECL|macro|RLIMIT_MSGQUEUE
mdefine_line|#define RLIMIT_MSGQUEUE 12&t;&t;/* maximum bytes in POSIX mqueues */
DECL|macro|RLIM_NLIMITS
mdefine_line|#define RLIM_NLIMITS&t;13
DECL|macro|__ARCH_RLIMIT_ORDER
mdefine_line|#define __ARCH_RLIMIT_ORDER
multiline_comment|/*&n; * SuS says limits have to be unsigned.  Fine, it&squot;s unsigned, but&n; * we retain the old value for compatibility, especially with DU. &n; * When you run into the 2^63 barrier, you call me.&n; */
DECL|macro|RLIM_INFINITY
mdefine_line|#define RLIM_INFINITY&t;0x7ffffffffffffffful
macro_line|#include &lt;asm-generic/resource.h&gt;
macro_line|#endif /* _ALPHA_RESOURCE_H */
eof
