macro_line|#ifndef _ASM_X86_64_IA32_H
DECL|macro|_ASM_X86_64_IA32_H
mdefine_line|#define _ASM_X86_64_IA32_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_IA32_EMULATION
macro_line|#include &lt;linux/compat.h&gt;
multiline_comment|/*&n; * 32 bit structures for IA32 support.&n; */
macro_line|#include &lt;asm/sigcontext32.h&gt;
multiline_comment|/* signal.h */
DECL|struct|sigaction32
r_struct
id|sigaction32
(brace
DECL|member|sa_handler
r_int
r_int
id|sa_handler
suffix:semicolon
multiline_comment|/* Really a pointer, but need to deal &n;&t;&t;&t;&t;&t;     with 32 bits */
DECL|member|sa_flags
r_int
r_int
id|sa_flags
suffix:semicolon
DECL|member|sa_restorer
r_int
r_int
id|sa_restorer
suffix:semicolon
multiline_comment|/* Another 32 bit pointer */
DECL|member|sa_mask
id|compat_sigset_t
id|sa_mask
suffix:semicolon
multiline_comment|/* A 32 bit mask */
)brace
suffix:semicolon
DECL|struct|old_sigaction32
r_struct
id|old_sigaction32
(brace
DECL|member|sa_handler
r_int
r_int
id|sa_handler
suffix:semicolon
multiline_comment|/* Really a pointer, but need to deal &n;&t;&t;&t;&t;&t;     with 32 bits */
DECL|member|sa_mask
id|compat_old_sigset_t
id|sa_mask
suffix:semicolon
multiline_comment|/* A 32 bit mask */
DECL|member|sa_flags
r_int
r_int
id|sa_flags
suffix:semicolon
DECL|member|sa_restorer
r_int
r_int
id|sa_restorer
suffix:semicolon
multiline_comment|/* Another 32 bit pointer */
)brace
suffix:semicolon
DECL|struct|sigaltstack_ia32
r_typedef
r_struct
id|sigaltstack_ia32
(brace
DECL|member|ss_sp
r_int
r_int
id|ss_sp
suffix:semicolon
DECL|member|ss_flags
r_int
id|ss_flags
suffix:semicolon
DECL|member|ss_size
r_int
r_int
id|ss_size
suffix:semicolon
DECL|typedef|stack_ia32_t
)brace
id|stack_ia32_t
suffix:semicolon
DECL|struct|ucontext_ia32
r_struct
id|ucontext_ia32
(brace
DECL|member|uc_flags
r_int
r_int
id|uc_flags
suffix:semicolon
DECL|member|uc_link
r_int
r_int
id|uc_link
suffix:semicolon
DECL|member|uc_stack
id|stack_ia32_t
id|uc_stack
suffix:semicolon
DECL|member|uc_mcontext
r_struct
id|sigcontext_ia32
id|uc_mcontext
suffix:semicolon
DECL|member|uc_sigmask
id|compat_sigset_t
id|uc_sigmask
suffix:semicolon
multiline_comment|/* mask last for extensibility */
)brace
suffix:semicolon
multiline_comment|/* This matches struct stat64 in glibc2.2, hence the absolutely&n; * insane amounts of padding around dev_t&squot;s.&n; */
DECL|struct|stat64
r_struct
id|stat64
(brace
DECL|member|st_dev
r_int
r_int
r_int
id|st_dev
suffix:semicolon
DECL|member|__pad0
r_int
r_char
id|__pad0
(braket
l_int|4
)braket
suffix:semicolon
DECL|macro|STAT64_HAS_BROKEN_ST_INO
mdefine_line|#define STAT64_HAS_BROKEN_ST_INO&t;1
DECL|member|__st_ino
r_int
r_int
id|__st_ino
suffix:semicolon
DECL|member|st_mode
r_int
r_int
id|st_mode
suffix:semicolon
DECL|member|st_nlink
r_int
r_int
id|st_nlink
suffix:semicolon
DECL|member|st_uid
r_int
r_int
id|st_uid
suffix:semicolon
DECL|member|st_gid
r_int
r_int
id|st_gid
suffix:semicolon
DECL|member|st_rdev
r_int
r_int
r_int
id|st_rdev
suffix:semicolon
DECL|member|__pad3
r_int
r_char
id|__pad3
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|st_size
r_int
r_int
id|st_size
suffix:semicolon
DECL|member|st_blksize
r_int
r_int
id|st_blksize
suffix:semicolon
DECL|member|st_blocks
r_int
r_int
id|st_blocks
suffix:semicolon
multiline_comment|/* Number 512-byte blocks allocated. */
DECL|member|st_atime
r_int
id|st_atime
suffix:semicolon
DECL|member|st_atime_nsec
r_int
id|st_atime_nsec
suffix:semicolon
DECL|member|st_mtime
r_int
id|st_mtime
suffix:semicolon
DECL|member|st_mtime_nsec
r_int
id|st_mtime_nsec
suffix:semicolon
DECL|member|st_ctime
r_int
id|st_ctime
suffix:semicolon
DECL|member|st_ctime_nsec
r_int
id|st_ctime_nsec
suffix:semicolon
DECL|member|st_ino
r_int
r_int
r_int
id|st_ino
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
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
r_int
r_int
id|sival_ptr
suffix:semicolon
DECL|typedef|sigval_t32
)brace
id|sigval_t32
suffix:semicolon
DECL|struct|siginfo32
r_typedef
r_struct
id|siginfo32
(brace
DECL|member|si_signo
r_int
id|si_signo
suffix:semicolon
DECL|member|si_errno
r_int
id|si_errno
suffix:semicolon
DECL|member|si_code
r_int
id|si_code
suffix:semicolon
r_union
(brace
DECL|member|_pad
r_int
id|_pad
(braket
(paren
(paren
l_int|128
op_div
r_sizeof
(paren
r_int
)paren
)paren
op_minus
l_int|3
)paren
)braket
suffix:semicolon
multiline_comment|/* kill() */
r_struct
(brace
DECL|member|_pid
r_int
r_int
id|_pid
suffix:semicolon
multiline_comment|/* sender&squot;s pid */
DECL|member|_uid
r_int
r_int
id|_uid
suffix:semicolon
multiline_comment|/* sender&squot;s uid */
DECL|member|_kill
)brace
id|_kill
suffix:semicolon
multiline_comment|/* POSIX.1b timers */
r_struct
(brace
DECL|member|_tid
r_int
id|_tid
suffix:semicolon
multiline_comment|/* timer id */
DECL|member|_overrun
r_int
id|_overrun
suffix:semicolon
multiline_comment|/* overrun count */
DECL|member|_sigval
id|sigval_t32
id|_sigval
suffix:semicolon
multiline_comment|/* same as below */
DECL|member|_sys_private
r_int
id|_sys_private
suffix:semicolon
multiline_comment|/* not to be passed to user */
DECL|member|_overrun_incr
r_int
id|_overrun_incr
suffix:semicolon
multiline_comment|/* amount to add to overrun */
DECL|member|_timer
)brace
id|_timer
suffix:semicolon
multiline_comment|/* POSIX.1b signals */
r_struct
(brace
DECL|member|_pid
r_int
r_int
id|_pid
suffix:semicolon
multiline_comment|/* sender&squot;s pid */
DECL|member|_uid
r_int
r_int
id|_uid
suffix:semicolon
multiline_comment|/* sender&squot;s uid */
DECL|member|_sigval
id|sigval_t32
id|_sigval
suffix:semicolon
DECL|member|_rt
)brace
id|_rt
suffix:semicolon
multiline_comment|/* SIGCHLD */
r_struct
(brace
DECL|member|_pid
r_int
r_int
id|_pid
suffix:semicolon
multiline_comment|/* which child */
DECL|member|_uid
r_int
r_int
id|_uid
suffix:semicolon
multiline_comment|/* sender&squot;s uid */
DECL|member|_status
r_int
id|_status
suffix:semicolon
multiline_comment|/* exit code */
DECL|member|_utime
id|compat_clock_t
id|_utime
suffix:semicolon
DECL|member|_stime
id|compat_clock_t
id|_stime
suffix:semicolon
DECL|member|_sigchld
)brace
id|_sigchld
suffix:semicolon
multiline_comment|/* SIGILL, SIGFPE, SIGSEGV, SIGBUS */
r_struct
(brace
DECL|member|_addr
r_int
r_int
id|_addr
suffix:semicolon
multiline_comment|/* faulting insn/memory ref. */
DECL|member|_sigfault
)brace
id|_sigfault
suffix:semicolon
multiline_comment|/* SIGPOLL */
r_struct
(brace
DECL|member|_band
r_int
id|_band
suffix:semicolon
multiline_comment|/* POLL_IN, POLL_OUT, POLL_MSG */
DECL|member|_fd
r_int
id|_fd
suffix:semicolon
DECL|member|_sigpoll
)brace
id|_sigpoll
suffix:semicolon
DECL|member|_sifields
)brace
id|_sifields
suffix:semicolon
DECL|typedef|siginfo_t32
)brace
id|siginfo_t32
suffix:semicolon
DECL|struct|sigframe32
r_struct
id|sigframe32
(brace
DECL|member|pretcode
id|u32
id|pretcode
suffix:semicolon
DECL|member|sig
r_int
id|sig
suffix:semicolon
DECL|member|sc
r_struct
id|sigcontext_ia32
id|sc
suffix:semicolon
DECL|member|fpstate
r_struct
id|_fpstate_ia32
id|fpstate
suffix:semicolon
DECL|member|extramask
r_int
r_int
id|extramask
(braket
id|_COMPAT_NSIG_WORDS
op_minus
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|rt_sigframe32
r_struct
id|rt_sigframe32
(brace
DECL|member|pretcode
id|u32
id|pretcode
suffix:semicolon
DECL|member|sig
r_int
id|sig
suffix:semicolon
DECL|member|pinfo
id|u32
id|pinfo
suffix:semicolon
DECL|member|puc
id|u32
id|puc
suffix:semicolon
DECL|member|info
r_struct
id|siginfo32
id|info
suffix:semicolon
DECL|member|uc
r_struct
id|ucontext_ia32
id|uc
suffix:semicolon
DECL|member|fpstate
r_struct
id|_fpstate_ia32
id|fpstate
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ustat32
r_struct
id|ustat32
(brace
DECL|member|f_tfree
id|__u32
id|f_tfree
suffix:semicolon
DECL|member|f_tinode
id|compat_ino_t
id|f_tinode
suffix:semicolon
DECL|member|f_fname
r_char
id|f_fname
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|f_fpack
r_char
id|f_fpack
(braket
l_int|6
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IA32_STACK_TOP
mdefine_line|#define IA32_STACK_TOP IA32_PAGE_OFFSET
macro_line|#ifdef __KERNEL__
r_struct
id|user_desc
suffix:semicolon
r_struct
id|siginfo_t
suffix:semicolon
r_int
id|do_get_thread_area
c_func
(paren
r_struct
id|thread_struct
op_star
id|t
comma
r_struct
id|user_desc
op_star
id|u_info
)paren
suffix:semicolon
r_int
id|do_set_thread_area
c_func
(paren
r_struct
id|thread_struct
op_star
id|t
comma
r_struct
id|user_desc
op_star
id|u_info
)paren
suffix:semicolon
r_int
id|ia32_child_tls
c_func
(paren
r_struct
id|task_struct
op_star
id|p
comma
r_struct
id|pt_regs
op_star
id|childregs
)paren
suffix:semicolon
r_int
id|ia32_copy_siginfo_from_user
c_func
(paren
id|siginfo_t
op_star
id|to
comma
id|siginfo_t32
id|__user
op_star
id|from
)paren
suffix:semicolon
r_int
id|ia32_copy_siginfo_to_user
c_func
(paren
id|siginfo_t32
id|__user
op_star
id|to
comma
id|siginfo_t
op_star
id|from
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* !CONFIG_IA32_SUPPORT */
macro_line|#endif 
eof
