macro_line|#ifndef _LINUX_THREADS_H
DECL|macro|_LINUX_THREADS_H
mdefine_line|#define _LINUX_THREADS_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * The default limit for the nr of threads is now in&n; * /proc/sys/kernel/threads-max.&n; */
macro_line|#ifdef CONFIG_SMP
DECL|macro|NR_CPUS
mdefine_line|#define NR_CPUS&t;32&t;&t;/* Max processors that can be running in SMP */
macro_line|#else
DECL|macro|NR_CPUS
mdefine_line|#define NR_CPUS 1
macro_line|#endif
DECL|macro|MIN_THREADS_LEFT_FOR_ROOT
mdefine_line|#define MIN_THREADS_LEFT_FOR_ROOT 4
multiline_comment|/*&n; * This controls the default maximum pid allocated to a process&n; */
DECL|macro|PID_MAX_DEFAULT
mdefine_line|#define PID_MAX_DEFAULT 0x8000
multiline_comment|/*&n; * A maximum of 4 million PIDs should be enough for a while:&n; */
DECL|macro|PID_MAX_LIMIT
mdefine_line|#define PID_MAX_LIMIT (4*1024*1024)
macro_line|#endif
eof
