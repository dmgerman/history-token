macro_line|#ifndef _ASM_S390X_S390_H
DECL|macro|_ASM_S390X_S390_H
mdefine_line|#define _ASM_S390X_S390_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/compat.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/syscalls.h&gt;
macro_line|#include &lt;linux/nfs_fs.h&gt;
macro_line|#include &lt;linux/sunrpc/svc.h&gt;
macro_line|#include &lt;linux/nfsd/nfsd.h&gt;
macro_line|#include &lt;linux/nfsd/export.h&gt;
multiline_comment|/* Macro that masks the high order bit of an 32 bit pointer and converts it*/
multiline_comment|/*       to a 64 bit pointer */
DECL|macro|A
mdefine_line|#define A(__x) ((unsigned long)((__x) &amp; 0x7FFFFFFFUL))
DECL|macro|AA
mdefine_line|#define AA(__x)&t;&t;&t;&t;&bslash;&n;&t;((unsigned long)(__x))
multiline_comment|/* Now 32bit compatibility types */
DECL|struct|ipc_kludge_32
r_struct
id|ipc_kludge_32
(brace
DECL|member|msgp
id|__u32
id|msgp
suffix:semicolon
multiline_comment|/* pointer              */
DECL|member|msgtyp
id|__s32
id|msgtyp
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|old_sigaction32
r_struct
id|old_sigaction32
(brace
DECL|member|sa_handler
id|__u32
id|sa_handler
suffix:semicolon
multiline_comment|/* Really a pointer, but need to deal with 32 bits */
DECL|member|sa_mask
id|compat_old_sigset_t
id|sa_mask
suffix:semicolon
multiline_comment|/* A 32 bit mask */
DECL|member|sa_flags
id|__u32
id|sa_flags
suffix:semicolon
DECL|member|sa_restorer
id|__u32
id|sa_restorer
suffix:semicolon
multiline_comment|/* Another 32 bit pointer */
)brace
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
id|__u32
id|sival_ptr
suffix:semicolon
DECL|typedef|sigval_t32
)brace
id|sigval_t32
suffix:semicolon
DECL|struct|compat_siginfo
r_typedef
r_struct
id|compat_siginfo
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
id|pid_t
id|_pid
suffix:semicolon
multiline_comment|/* sender&squot;s pid */
DECL|member|_uid
id|uid_t
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
DECL|member|_timer1
r_int
r_int
id|_timer1
suffix:semicolon
DECL|member|_timer2
r_int
r_int
id|_timer2
suffix:semicolon
DECL|member|_timer
)brace
id|_timer
suffix:semicolon
multiline_comment|/* POSIX.1b signals */
r_struct
(brace
DECL|member|_pid
id|pid_t
id|_pid
suffix:semicolon
multiline_comment|/* sender&squot;s pid */
DECL|member|_uid
id|uid_t
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
id|pid_t
id|_pid
suffix:semicolon
multiline_comment|/* which child */
DECL|member|_uid
id|uid_t
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
id|__u32
id|_addr
suffix:semicolon
multiline_comment|/* faulting insn/memory ref. - pointer */
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
DECL|typedef|compat_siginfo_t
)brace
id|compat_siginfo_t
suffix:semicolon
multiline_comment|/*&n; * How these fields are to be accessed.&n; */
DECL|macro|si_pid
mdefine_line|#define si_pid&t;&t;_sifields._kill._pid
DECL|macro|si_uid
mdefine_line|#define si_uid&t;&t;_sifields._kill._uid
DECL|macro|si_status
mdefine_line|#define si_status&t;_sifields._sigchld._status
DECL|macro|si_utime
mdefine_line|#define si_utime&t;_sifields._sigchld._utime
DECL|macro|si_stime
mdefine_line|#define si_stime&t;_sifields._sigchld._stime
DECL|macro|si_value
mdefine_line|#define si_value&t;_sifields._rt._sigval
DECL|macro|si_int
mdefine_line|#define si_int&t;&t;_sifields._rt._sigval.sival_int
DECL|macro|si_ptr
mdefine_line|#define si_ptr&t;&t;_sifields._rt._sigval.sival_ptr
DECL|macro|si_addr
mdefine_line|#define si_addr&t;&t;_sifields._sigfault._addr
DECL|macro|si_band
mdefine_line|#define si_band&t;&t;_sifields._sigpoll._band
DECL|macro|si_fd
mdefine_line|#define si_fd&t;&t;_sifields._sigpoll._fd    
multiline_comment|/* asm/sigcontext.h */
r_typedef
r_union
(brace
DECL|member|d
id|__u64
id|d
suffix:semicolon
DECL|member|f
id|__u32
id|f
suffix:semicolon
DECL|typedef|freg_t32
)brace
id|freg_t32
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|fpc
r_int
r_int
id|fpc
suffix:semicolon
DECL|member|fprs
id|freg_t32
id|fprs
(braket
id|__NUM_FPRS
)braket
suffix:semicolon
DECL|typedef|_s390_fp_regs32
)brace
id|_s390_fp_regs32
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|mask
id|__u32
id|mask
suffix:semicolon
DECL|member|addr
id|__u32
id|addr
suffix:semicolon
DECL|typedef|_psw_t32
)brace
id|_psw_t32
id|__attribute__
(paren
(paren
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
DECL|macro|PSW32_MASK_PER
mdefine_line|#define PSW32_MASK_PER&t;&t;0x40000000UL
DECL|macro|PSW32_MASK_DAT
mdefine_line|#define PSW32_MASK_DAT&t;&t;0x04000000UL
DECL|macro|PSW32_MASK_IO
mdefine_line|#define PSW32_MASK_IO&t;&t;0x02000000UL
DECL|macro|PSW32_MASK_EXT
mdefine_line|#define PSW32_MASK_EXT&t;&t;0x01000000UL
DECL|macro|PSW32_MASK_KEY
mdefine_line|#define PSW32_MASK_KEY&t;&t;0x00F00000UL
DECL|macro|PSW32_MASK_MCHECK
mdefine_line|#define PSW32_MASK_MCHECK&t;0x00040000UL
DECL|macro|PSW32_MASK_WAIT
mdefine_line|#define PSW32_MASK_WAIT&t;&t;0x00020000UL
DECL|macro|PSW32_MASK_PSTATE
mdefine_line|#define PSW32_MASK_PSTATE&t;0x00010000UL
DECL|macro|PSW32_MASK_ASC
mdefine_line|#define PSW32_MASK_ASC&t;&t;0x0000C000UL
DECL|macro|PSW32_MASK_CC
mdefine_line|#define PSW32_MASK_CC&t;&t;0x00003000UL
DECL|macro|PSW32_MASK_PM
mdefine_line|#define PSW32_MASK_PM&t;&t;0x00000f00UL
DECL|macro|PSW32_ADDR_AMODE31
mdefine_line|#define PSW32_ADDR_AMODE31&t;0x80000000UL
DECL|macro|PSW32_ADDR_INSN
mdefine_line|#define PSW32_ADDR_INSN&t;&t;0x7FFFFFFFUL
DECL|macro|PSW32_BASE_BITS
mdefine_line|#define PSW32_BASE_BITS&t;&t;0x00080000UL
DECL|macro|PSW32_ASC_PRIMARY
mdefine_line|#define PSW32_ASC_PRIMARY&t;0x00000000UL
DECL|macro|PSW32_ASC_ACCREG
mdefine_line|#define PSW32_ASC_ACCREG&t;0x00004000UL
DECL|macro|PSW32_ASC_SECONDARY
mdefine_line|#define PSW32_ASC_SECONDARY&t;0x00008000UL
DECL|macro|PSW32_ASC_HOME
mdefine_line|#define PSW32_ASC_HOME&t;&t;0x0000C000UL
DECL|macro|PSW32_USER_BITS
mdefine_line|#define PSW32_USER_BITS&t;(PSW32_BASE_BITS | PSW32_MASK_DAT | PSW32_ASC_HOME | &bslash;&n;&t;&t;&t; PSW32_MASK_IO | PSW32_MASK_EXT | PSW32_MASK_MCHECK | &bslash;&n;&t;&t;&t; PSW32_MASK_PSTATE)
DECL|macro|PSW32_MASK_MERGE
mdefine_line|#define PSW32_MASK_MERGE(CURRENT,NEW) &bslash;&n;        (((CURRENT) &amp; ~(PSW32_MASK_CC|PSW32_MASK_PM)) | &bslash;&n;         ((NEW) &amp; (PSW32_MASK_CC|PSW32_MASK_PM)))
r_typedef
r_struct
(brace
DECL|member|psw
id|_psw_t32
id|psw
suffix:semicolon
DECL|member|gprs
id|__u32
id|gprs
(braket
id|__NUM_GPRS
)braket
suffix:semicolon
DECL|member|acrs
id|__u32
id|acrs
(braket
id|__NUM_ACRS
)braket
suffix:semicolon
DECL|typedef|_s390_regs_common32
)brace
id|_s390_regs_common32
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|regs
id|_s390_regs_common32
id|regs
suffix:semicolon
DECL|member|fpregs
id|_s390_fp_regs32
id|fpregs
suffix:semicolon
DECL|typedef|_sigregs32
)brace
id|_sigregs32
suffix:semicolon
DECL|macro|_SIGCONTEXT_NSIG32
mdefine_line|#define _SIGCONTEXT_NSIG32&t;64
DECL|macro|_SIGCONTEXT_NSIG_BPW32
mdefine_line|#define _SIGCONTEXT_NSIG_BPW32&t;32
DECL|macro|__SIGNAL_FRAMESIZE32
mdefine_line|#define __SIGNAL_FRAMESIZE32&t;96
DECL|macro|_SIGMASK_COPY_SIZE32
mdefine_line|#define _SIGMASK_COPY_SIZE32&t;(sizeof(u32)*2)
DECL|struct|sigcontext32
r_struct
id|sigcontext32
(brace
DECL|member|oldmask
id|__u32
id|oldmask
(braket
id|_COMPAT_NSIG_WORDS
)braket
suffix:semicolon
DECL|member|sregs
id|__u32
id|sregs
suffix:semicolon
multiline_comment|/* pointer */
)brace
suffix:semicolon
multiline_comment|/* asm/signal.h */
DECL|struct|sigaction32
r_struct
id|sigaction32
(brace
DECL|member|sa_handler
id|__u32
id|sa_handler
suffix:semicolon
multiline_comment|/* pointer */
DECL|member|sa_flags
id|__u32
id|sa_flags
suffix:semicolon
DECL|member|sa_restorer
id|__u32
id|sa_restorer
suffix:semicolon
multiline_comment|/* pointer */
DECL|member|sa_mask
id|compat_sigset_t
id|sa_mask
suffix:semicolon
multiline_comment|/* mask last for extensibility */
)brace
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|ss_sp
id|__u32
id|ss_sp
suffix:semicolon
multiline_comment|/* pointer */
DECL|member|ss_flags
r_int
id|ss_flags
suffix:semicolon
DECL|member|ss_size
id|compat_size_t
id|ss_size
suffix:semicolon
DECL|typedef|stack_t32
)brace
id|stack_t32
suffix:semicolon
multiline_comment|/* asm/ucontext.h */
DECL|struct|ucontext32
r_struct
id|ucontext32
(brace
DECL|member|uc_flags
id|__u32
id|uc_flags
suffix:semicolon
DECL|member|uc_link
id|__u32
id|uc_link
suffix:semicolon
multiline_comment|/* pointer */
DECL|member|uc_stack
id|stack_t32
id|uc_stack
suffix:semicolon
DECL|member|uc_mcontext
id|_sigregs32
id|uc_mcontext
suffix:semicolon
DECL|member|uc_sigmask
id|compat_sigset_t
id|uc_sigmask
suffix:semicolon
multiline_comment|/* mask last for extensibility */
)brace
suffix:semicolon
DECL|macro|SIGEV_PAD_SIZE32
mdefine_line|#define SIGEV_PAD_SIZE32 ((SIGEV_MAX_SIZE/sizeof(int)) - 3)
DECL|struct|sigevent32
r_struct
id|sigevent32
(brace
r_union
(brace
DECL|member|sival_int
r_int
id|sival_int
suffix:semicolon
DECL|member|sival_ptr
id|u32
id|sival_ptr
suffix:semicolon
DECL|member|sigev_value
)brace
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
DECL|member|_tid
r_int
id|_tid
suffix:semicolon
r_struct
(brace
DECL|member|_function
id|u32
op_star
id|_function
suffix:semicolon
DECL|member|_attribute
id|u32
op_star
id|_attribute
suffix:semicolon
DECL|member|_sigev_thread
)brace
id|_sigev_thread
suffix:semicolon
DECL|member|_sigev_un
)brace
id|_sigev_un
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _ASM_S390X_S390_H */
eof
