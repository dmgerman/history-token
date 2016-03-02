macro_line|#ifndef _LINUX_COMPAT_H
DECL|macro|_LINUX_COMPAT_H
mdefine_line|#define _LINUX_COMPAT_H
multiline_comment|/*&n; * These are the type definitions for the architecture specific&n; * syscall compatibility layer.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_COMPAT
macro_line|#include &lt;asm/compat.h&gt;
DECL|macro|compat_jiffies_to_clock_t
mdefine_line|#define compat_jiffies_to_clock_t(x)&t;((x) / (HZ / COMPAT_USER_HZ))
DECL|struct|compat_utimbuf
r_struct
id|compat_utimbuf
(brace
DECL|member|actime
id|compat_time_t
id|actime
suffix:semicolon
DECL|member|modtime
id|compat_time_t
id|modtime
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|compat_itimerval
r_struct
id|compat_itimerval
(brace
DECL|member|it_interval
r_struct
id|compat_timeval
id|it_interval
suffix:semicolon
DECL|member|it_value
r_struct
id|compat_timeval
id|it_value
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|compat_tms
r_struct
id|compat_tms
(brace
DECL|member|tms_utime
id|compat_clock_t
id|tms_utime
suffix:semicolon
DECL|member|tms_stime
id|compat_clock_t
id|tms_stime
suffix:semicolon
DECL|member|tms_cutime
id|compat_clock_t
id|tms_cutime
suffix:semicolon
DECL|member|tms_cstime
id|compat_clock_t
id|tms_cstime
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_COMPAT */
macro_line|#endif /* _LINUX_COMPAT_H */
eof
