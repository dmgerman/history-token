macro_line|#ifndef _LINUX_TIMES_H
DECL|macro|_LINUX_TIMES_H
mdefine_line|#define _LINUX_TIMES_H
macro_line|#ifdef __KERNEL__
DECL|macro|jiffies_to_clock_t
macro_line|# define jiffies_to_clock_t(x) ((x) / (HZ / USER_HZ))
macro_line|#endif
DECL|struct|tms
r_struct
id|tms
(brace
DECL|member|tms_utime
id|clock_t
id|tms_utime
suffix:semicolon
DECL|member|tms_stime
id|clock_t
id|tms_stime
suffix:semicolon
DECL|member|tms_cutime
id|clock_t
id|tms_cutime
suffix:semicolon
DECL|member|tms_cstime
id|clock_t
id|tms_cstime
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
