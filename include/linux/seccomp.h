macro_line|#ifndef _LINUX_SECCOMP_H
DECL|macro|_LINUX_SECCOMP_H
mdefine_line|#define _LINUX_SECCOMP_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_SECCOMP
DECL|macro|NR_SECCOMP_MODES
mdefine_line|#define NR_SECCOMP_MODES 1
macro_line|#include &lt;linux/thread_info.h&gt;
macro_line|#include &lt;asm/seccomp.h&gt;
DECL|member|mode
DECL|typedef|seccomp_t
r_typedef
r_struct
(brace
r_int
id|mode
suffix:semicolon
)brace
id|seccomp_t
suffix:semicolon
r_extern
r_void
id|__secure_computing
c_func
(paren
r_int
)paren
suffix:semicolon
DECL|function|secure_computing
r_static
r_inline
r_void
id|secure_computing
c_func
(paren
r_int
id|this_syscall
)paren
(brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|test_thread_flag
c_func
(paren
id|TIF_SECCOMP
)paren
)paren
)paren
id|__secure_computing
c_func
(paren
id|this_syscall
)paren
suffix:semicolon
)brace
macro_line|#else /* CONFIG_SECCOMP */
macro_line|#if (__GNUC__ &gt; 2)
DECL|typedef|seccomp_t
r_typedef
r_struct
(brace
)brace
id|seccomp_t
suffix:semicolon
macro_line|#else
DECL|member|gcc_is_buggy
DECL|typedef|seccomp_t
r_typedef
r_struct
(brace
r_int
id|gcc_is_buggy
suffix:semicolon
)brace
id|seccomp_t
suffix:semicolon
macro_line|#endif
DECL|macro|secure_computing
mdefine_line|#define secure_computing(x) do { } while (0)
macro_line|#endif /* CONFIG_SECCOMP */
macro_line|#endif /* _LINUX_SECCOMP_H */
eof
