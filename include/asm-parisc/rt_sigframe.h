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
DECL|macro|SIGFRAME32
mdefine_line|#define SIGFRAME32&t;&t;64
DECL|macro|FUNCTIONCALLFRAME32
mdefine_line|#define FUNCTIONCALLFRAME32&t;48
DECL|macro|PARISC_RT_SIGFRAME_SIZE32
mdefine_line|#define PARISC_RT_SIGFRAME_SIZE32&t;&t;&t;&t;&t;&bslash;&n;&t;(((sizeof(struct rt_sigframe) + FUNCTIONCALLFRAME32) + SIGFRAME32) &amp; -SIGFRAME32)
macro_line|#ifdef __LP64__
DECL|macro|SIGFRAME
mdefine_line|#define&t;SIGFRAME&t;&t;128
DECL|macro|FUNCTIONCALLFRAME
mdefine_line|#define FUNCTIONCALLFRAME&t;96
DECL|macro|PARISC_RT_SIGFRAME_SIZE
mdefine_line|#define PARISC_RT_SIGFRAME_SIZE&t;&t;&t;&t;&t;&bslash;&n;&t;(((sizeof(struct rt_sigframe) + FUNCTIONCALLFRAME) + SIGFRAME) &amp; -SIGFRAME)
macro_line|#else
DECL|macro|SIGFRAME
mdefine_line|#define&t;SIGFRAME&t;&t;SIGFRAME32
DECL|macro|FUNCTIONCALLFRAME
mdefine_line|#define FUNCTIONCALLFRAME&t;FUNCTIONCALLFRAME32
DECL|macro|PARISC_RT_SIGFRAME_SIZE
mdefine_line|#define PARISC_RT_SIGFRAME_SIZE&t;PARISC_RT_SIGFRAME_SIZE32
macro_line|#endif
macro_line|#endif
eof
