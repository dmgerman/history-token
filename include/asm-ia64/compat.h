macro_line|#ifndef _ASM_IA64_COMPAT_H
DECL|macro|_ASM_IA64_COMPAT_H
mdefine_line|#define _ASM_IA64_COMPAT_H
multiline_comment|/*&n; * Architecture specific compatibility types&n; */
macro_line|#include &lt;linux/types.h&gt;
DECL|typedef|compat_size_t
r_typedef
id|u32
id|compat_size_t
suffix:semicolon
DECL|typedef|compat_ssize_t
r_typedef
id|s32
id|compat_ssize_t
suffix:semicolon
DECL|typedef|compat_time_t
r_typedef
id|s32
id|compat_time_t
suffix:semicolon
DECL|struct|compat_timespec
r_struct
id|compat_timespec
(brace
DECL|member|tv_sec
id|compat_time_t
id|tv_sec
suffix:semicolon
DECL|member|tv_nsec
id|s32
id|tv_nsec
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|compat_timeval
r_struct
id|compat_timeval
(brace
DECL|member|tv_sec
id|compat_time_t
id|tv_sec
suffix:semicolon
DECL|member|tv_usec
id|s32
id|tv_usec
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _ASM_IA64_COMPAT_H */
eof
