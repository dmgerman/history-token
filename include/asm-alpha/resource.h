macro_line|#ifndef _ALPHA_RESOURCE_H
DECL|macro|_ALPHA_RESOURCE_H
mdefine_line|#define _ALPHA_RESOURCE_H
multiline_comment|/*&n; * Alpha/Linux-specific ordering of these four resource limit IDs,&n; * the rest comes from the generic header:&n; */
DECL|macro|RLIMIT_NOFILE
mdefine_line|#define RLIMIT_NOFILE&t;&t;6&t;/* max number of open files */
DECL|macro|RLIMIT_AS
mdefine_line|#define RLIMIT_AS&t;&t;7&t;/* address space limit */
DECL|macro|RLIMIT_NPROC
mdefine_line|#define RLIMIT_NPROC&t;&t;8&t;/* max number of processes */
DECL|macro|RLIMIT_MEMLOCK
mdefine_line|#define RLIMIT_MEMLOCK&t;&t;9&t;/* max locked-in-memory address space */
multiline_comment|/*&n; * SuS says limits have to be unsigned.  Fine, it&squot;s unsigned, but&n; * we retain the old value for compatibility, especially with DU. &n; * When you run into the 2^63 barrier, you call me.&n; */
DECL|macro|RLIM_INFINITY
mdefine_line|#define RLIM_INFINITY&t;&t;0x7ffffffffffffffful
macro_line|#include &lt;asm-generic/resource.h&gt;
macro_line|#endif /* _ALPHA_RESOURCE_H */
eof
