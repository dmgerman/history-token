macro_line|#ifndef _PARISC64_KERNEL_SYS32_H
DECL|macro|_PARISC64_KERNEL_SYS32_H
mdefine_line|#define _PARISC64_KERNEL_SYS32_H
multiline_comment|/* Call a kernel syscall which will use kernel space instead of user&n; * space for its copy_to/from_user.&n; */
DECL|macro|KERNEL_SYSCALL
mdefine_line|#define KERNEL_SYSCALL(ret, syscall, args...) &bslash;&n;{ &bslash;&n;    mm_segment_t old_fs = get_fs(); &bslash;&n;    set_fs(KERNEL_DS); &bslash;&n;    ret = syscall(args); &bslash;&n;    set_fs (old_fs); &bslash;&n;}
DECL|typedef|__sighandler_t32
r_typedef
id|__u32
id|__sighandler_t32
suffix:semicolon
macro_line|#include &lt;linux/signal.h&gt;
r_typedef
r_struct
(brace
DECL|member|sig
r_int
r_int
id|sig
(braket
id|_NSIG_WORDS
op_star
l_int|2
)braket
suffix:semicolon
DECL|typedef|sigset_t32
)brace
id|sigset_t32
suffix:semicolon
DECL|struct|sigaction32
r_struct
id|sigaction32
(brace
DECL|member|sa_handler
id|__sighandler_t32
id|sa_handler
suffix:semicolon
DECL|member|sa_flags
r_int
r_int
id|sa_flags
suffix:semicolon
DECL|member|sa_mask
id|sigset_t32
id|sa_mask
suffix:semicolon
multiline_comment|/* mask last for extensibility */
)brace
suffix:semicolon
macro_line|#endif
eof
