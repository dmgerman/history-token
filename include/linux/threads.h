macro_line|#ifndef _LINUX_THREADS_H
DECL|macro|_LINUX_THREADS_H
mdefine_line|#define _LINUX_THREADS_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * The default limit for the nr of threads is now in&n; * /proc/sys/kernel/threads-max.&n; */
multiline_comment|/*&n; * Maximum supported processors that can run under SMP.  This value is&n; * set via configure setting.  The maximum is equal to the size of the&n; * bitmasks used on that platform, i.e. 32 or 64.  Setting this smaller&n; * saves quite a bit of memory.&n; */
macro_line|#ifdef CONFIG_SMP
DECL|macro|NR_CPUS
mdefine_line|#define NR_CPUS&t;&t;CONFIG_NR_CPUS
macro_line|#else
DECL|macro|NR_CPUS
mdefine_line|#define NR_CPUS&t;&t;1
macro_line|#endif
DECL|macro|MIN_THREADS_LEFT_FOR_ROOT
mdefine_line|#define MIN_THREADS_LEFT_FOR_ROOT 4
multiline_comment|/*&n; * This controls the default maximum pid allocated to a process&n; */
DECL|macro|PID_MAX_DEFAULT
mdefine_line|#define PID_MAX_DEFAULT 0x8000
multiline_comment|/*&n; * A maximum of 4 million PIDs should be enough for a while:&n; */
DECL|macro|PID_MAX_LIMIT
mdefine_line|#define PID_MAX_LIMIT (sizeof(long) &gt; 4 ? 4*1024*1024 : PID_MAX_DEFAULT)
macro_line|#endif
eof
