macro_line|#ifndef _SPARC64_SIGINFO_H
DECL|macro|_SPARC64_SIGINFO_H
mdefine_line|#define _SPARC64_SIGINFO_H
DECL|macro|SI_PAD_SIZE32
mdefine_line|#define SI_PAD_SIZE32&t;((SI_MAX_SIZE/sizeof(int)) - 3)
DECL|macro|SIGEV_PAD_SIZE
mdefine_line|#define SIGEV_PAD_SIZE&t;((SIGEV_MAX_SIZE/sizeof(int)) - 4)
DECL|macro|SIGEV_PAD_SIZE32
mdefine_line|#define SIGEV_PAD_SIZE32 ((SIGEV_MAX_SIZE/sizeof(int)) - 3)
DECL|macro|__ARCH_SI_PREAMBLE_SIZE
mdefine_line|#define __ARCH_SI_PREAMBLE_SIZE&t;(4 * sizeof(int))
DECL|macro|__ARCH_SI_TRAPNO
mdefine_line|#define __ARCH_SI_TRAPNO
DECL|macro|__ARCH_SI_BAND_T
mdefine_line|#define __ARCH_SI_BAND_T int
macro_line|#include &lt;asm-generic/siginfo.h&gt;
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/compat.h&gt;
macro_line|#ifdef CONFIG_COMPAT
DECL|union|sigval32
r_typedef
r_union
id|sigval32
(brace
DECL|member|sival_int
r_int
id|sival_int
suffix:semicolon
DECL|member|sival_ptr
id|u32
id|sival_ptr
suffix:semicolon
DECL|typedef|sigval_t32
)brace
id|sigval_t32
suffix:semicolon
r_struct
id|compat_siginfo
suffix:semicolon
macro_line|#endif /* CONFIG_COMPAT */
macro_line|#endif /* __KERNEL__ */
DECL|macro|SI_NOINFO
mdefine_line|#define SI_NOINFO&t;32767&t;&t;/* no information in siginfo_t */
multiline_comment|/*&n; * SIGEMT si_codes&n; */
DECL|macro|EMT_TAGOVF
mdefine_line|#define EMT_TAGOVF&t;(__SI_FAULT|1)&t;/* tag overflow */
DECL|macro|NSIGEMT
mdefine_line|#define NSIGEMT&t;&t;1
macro_line|#ifdef __KERNEL__
macro_line|#ifdef CONFIG_COMPAT
DECL|struct|sigevent32
r_typedef
r_struct
id|sigevent32
(brace
DECL|member|sigev_value
id|sigval_t32
id|sigev_value
suffix:semicolon
DECL|member|sigev_signo
r_int
id|sigev_signo
suffix:semicolon
DECL|member|sigev_notify
r_int
id|sigev_notify
suffix:semicolon
r_union
(brace
DECL|member|_pad
r_int
id|_pad
(braket
id|SIGEV_PAD_SIZE32
)braket
suffix:semicolon
r_struct
(brace
DECL|member|_function
id|u32
id|_function
suffix:semicolon
DECL|member|_attribute
id|u32
id|_attribute
suffix:semicolon
multiline_comment|/* really pthread_attr_t */
DECL|member|_sigev_thread
)brace
id|_sigev_thread
suffix:semicolon
DECL|member|_sigev_un
)brace
id|_sigev_un
suffix:semicolon
DECL|typedef|sigevent_t32
)brace
id|sigevent_t32
suffix:semicolon
macro_line|#endif /* CONFIG_COMPAT */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
