macro_line|#ifndef _ASM_PARISC_RT_SIGFRAME_H
DECL|macro|_ASM_PARISC_RT_SIGFRAME_H
mdefine_line|#define _ASM_PARISC_RT_SIGFRAME_H
DECL|struct|rt_sigframe
r_struct
id|rt_sigframe
(brace
DECL|member|tramp
r_int
r_int
id|tramp
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|info
r_struct
id|siginfo
id|info
suffix:semicolon
DECL|member|uc
r_struct
id|ucontext
id|uc
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * The 32-bit ABI wants at least 48 bytes for a function call frame:&n; * 16 bytes for arg0-arg3, and 32 bytes for magic (the only part of&n; * which Linux/parisc uses is sp-20 for the saved return pointer...)&n; * Then, the stack pointer must be rounded to a cache line (64 bytes).&n; */
DECL|macro|PARISC_RT_SIGFRAME_SIZE
mdefine_line|#define PARISC_RT_SIGFRAME_SIZE&t;&t;&t;&t;&t;&bslash;&n;&t;(((sizeof(struct rt_sigframe) + 48) + 63) &amp; -64)
macro_line|#endif
eof
