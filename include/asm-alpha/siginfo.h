macro_line|#ifndef _ALPHA_SIGINFO_H
DECL|macro|_ALPHA_SIGINFO_H
mdefine_line|#define _ALPHA_SIGINFO_H
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/* This structure matches OSF/1 for binary compatibility. */
DECL|union|sigval
r_typedef
r_union
id|sigval
(brace
DECL|member|sival_int
r_int
id|sival_int
suffix:semicolon
DECL|member|sival_ptr
r_void
op_star
id|sival_ptr
suffix:semicolon
DECL|typedef|sigval_t
)brace
id|sigval_t
suffix:semicolon
DECL|macro|SI_MAX_SIZE
mdefine_line|#define SI_MAX_SIZE&t;128
DECL|macro|SI_PAD_SIZE
mdefine_line|#define SI_PAD_SIZE&t;((SI_MAX_SIZE/sizeof(int)) - 4)
DECL|struct|siginfo
r_typedef
r_struct
id|siginfo
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
id|SI_PAD_SIZE
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
id|sigval_t
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
id|clock_t
id|_utime
suffix:semicolon
DECL|member|_stime
id|clock_t
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
r_void
op_star
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
DECL|typedef|siginfo_t
)brace
id|siginfo_t
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
macro_line|#ifdef __KERNEL__
DECL|macro|__SI_MASK
mdefine_line|#define __SI_MASK&t;0xffff0000
DECL|macro|__SI_KILL
mdefine_line|#define __SI_KILL&t;(0 &lt;&lt; 16)
DECL|macro|__SI_TIMER
mdefine_line|#define __SI_TIMER&t;(1 &lt;&lt; 16)
DECL|macro|__SI_POLL
mdefine_line|#define __SI_POLL&t;(2 &lt;&lt; 16)
DECL|macro|__SI_FAULT
mdefine_line|#define __SI_FAULT&t;(3 &lt;&lt; 16)
DECL|macro|__SI_CHLD
mdefine_line|#define __SI_CHLD&t;(4 &lt;&lt; 16)
DECL|macro|__SI_RT
mdefine_line|#define __SI_RT&t;&t;(5 &lt;&lt; 16)
DECL|macro|__SI_CODE
mdefine_line|#define __SI_CODE(T,N)&t;((T) &lt;&lt; 16 | ((N) &amp; 0xffff))
macro_line|#else
DECL|macro|__SI_KILL
mdefine_line|#define __SI_KILL&t;0
DECL|macro|__SI_TIMER
mdefine_line|#define __SI_TIMER&t;0
DECL|macro|__SI_POLL
mdefine_line|#define __SI_POLL&t;0
DECL|macro|__SI_FAULT
mdefine_line|#define __SI_FAULT&t;0
DECL|macro|__SI_CHLD
mdefine_line|#define __SI_CHLD&t;0
DECL|macro|__SI_RT
mdefine_line|#define __SI_RT&t;&t;0
DECL|macro|__SI_CODE
mdefine_line|#define __SI_CODE(T,N)&t;(N)
macro_line|#endif
multiline_comment|/*&n; * si_code values&n; * Digital reserves positive values for kernel-generated signals.&n; */
DECL|macro|SI_USER
mdefine_line|#define SI_USER&t;&t;0&t;&t;/* sent by kill, sigsend, raise */
DECL|macro|SI_KERNEL
mdefine_line|#define SI_KERNEL&t;0x80&t;&t;/* sent by the kernel from somewhere */
DECL|macro|SI_QUEUE
mdefine_line|#define SI_QUEUE&t;-1&t;&t;/* sent by sigqueue */
DECL|macro|SI_TIMER
mdefine_line|#define SI_TIMER __SI_CODE(__SI_TIMER,-2) /* sent by timer expiration */
DECL|macro|SI_MESGQ
mdefine_line|#define SI_MESGQ&t;-3&t;&t;/* sent by real time mesq state change */
DECL|macro|SI_ASYNCIO
mdefine_line|#define SI_ASYNCIO&t;-4&t;&t;/* sent by AIO completion */
DECL|macro|SI_SIGIO
mdefine_line|#define SI_SIGIO&t;-5&t;&t;/* sent by queued SIGIO */
DECL|macro|SI_FROMUSER
mdefine_line|#define SI_FROMUSER(siptr)&t;((siptr)-&gt;si_code &lt;= 0)
DECL|macro|SI_FROMKERNEL
mdefine_line|#define SI_FROMKERNEL(siptr)&t;((siptr)-&gt;si_code &gt; 0)
multiline_comment|/*&n; * SIGILL si_codes&n; */
DECL|macro|ILL_ILLOPC
mdefine_line|#define ILL_ILLOPC&t;(__SI_FAULT|1)&t;/* illegal opcode */
DECL|macro|ILL_ILLOPN
mdefine_line|#define ILL_ILLOPN&t;(__SI_FAULT|2)&t;/* illegal operand */
DECL|macro|ILL_ILLADR
mdefine_line|#define ILL_ILLADR&t;(__SI_FAULT|3)&t;/* illegal addressing mode */
DECL|macro|ILL_ILLTRP
mdefine_line|#define ILL_ILLTRP&t;(__SI_FAULT|4)&t;/* illegal trap */
DECL|macro|ILL_PRVOPC
mdefine_line|#define ILL_PRVOPC&t;(__SI_FAULT|5)&t;/* privileged opcode */
DECL|macro|ILL_PRVREG
mdefine_line|#define ILL_PRVREG&t;(__SI_FAULT|6)&t;/* privileged register */
DECL|macro|ILL_COPROC
mdefine_line|#define ILL_COPROC&t;(__SI_FAULT|7)&t;/* coprocessor error */
DECL|macro|ILL_BADSTK
mdefine_line|#define ILL_BADSTK&t;(__SI_FAULT|8)&t;/* internal stack error */
DECL|macro|NSIGILL
mdefine_line|#define NSIGILL&t;&t;8
multiline_comment|/*&n; * SIGFPE si_codes&n; */
DECL|macro|FPE_INTDIV
mdefine_line|#define FPE_INTDIV&t;(__SI_FAULT|1)&t;/* integer divide by zero */
DECL|macro|FPE_INTOVF
mdefine_line|#define FPE_INTOVF&t;(__SI_FAULT|2)&t;/* integer overflow */
DECL|macro|FPE_FLTDIV
mdefine_line|#define FPE_FLTDIV&t;(__SI_FAULT|3)&t;/* floating point divide by zero */
DECL|macro|FPE_FLTOVF
mdefine_line|#define FPE_FLTOVF&t;(__SI_FAULT|4)&t;/* floating point overflow */
DECL|macro|FPE_FLTUND
mdefine_line|#define FPE_FLTUND&t;(__SI_FAULT|5)&t;/* floating point underflow */
DECL|macro|FPE_FLTRES
mdefine_line|#define FPE_FLTRES&t;(__SI_FAULT|6)&t;/* floating point inexact result */
DECL|macro|FPE_FLTINV
mdefine_line|#define FPE_FLTINV&t;(__SI_FAULT|7)&t;/* floating point invalid operation */
DECL|macro|FPE_FLTSUB
mdefine_line|#define FPE_FLTSUB&t;(__SI_FAULT|8)&t;/* subscript out of range */
DECL|macro|NSIGFPE
mdefine_line|#define NSIGFPE&t;&t;8
multiline_comment|/*&n; * SIGSEGV si_codes&n; */
DECL|macro|SEGV_MAPERR
mdefine_line|#define SEGV_MAPERR&t;(__SI_FAULT|1)&t;/* address not mapped to object */
DECL|macro|SEGV_ACCERR
mdefine_line|#define SEGV_ACCERR&t;(__SI_FAULT|2)&t;/* invalid permissions for mapped object */
DECL|macro|NSIGSEGV
mdefine_line|#define NSIGSEGV&t;2
multiline_comment|/*&n; * SIGBUS si_codes&n; */
DECL|macro|BUS_ADRALN
mdefine_line|#define BUS_ADRALN&t;(__SI_FAULT|1)&t;/* invalid address alignment */
DECL|macro|BUS_ADRERR
mdefine_line|#define BUS_ADRERR&t;(__SI_FAULT|2)&t;/* non-existant physical address */
DECL|macro|BUS_OBJERR
mdefine_line|#define BUS_OBJERR&t;(__SI_FAULT|3)&t;/* object specific hardware error */
DECL|macro|NSIGBUS
mdefine_line|#define NSIGBUS&t;&t;3
multiline_comment|/*&n; * SIGTRAP si_codes&n; */
DECL|macro|TRAP_BRKPT
mdefine_line|#define TRAP_BRKPT&t;(__SI_FAULT|1)&t;/* process breakpoint */
DECL|macro|TRAP_TRACE
mdefine_line|#define TRAP_TRACE&t;(__SI_FAULT|2)&t;/* process trace trap */
DECL|macro|NSIGTRAP
mdefine_line|#define NSIGTRAP&t;2
multiline_comment|/*&n; * SIGCHLD si_codes&n; */
DECL|macro|CLD_EXITED
mdefine_line|#define CLD_EXITED&t;(__SI_CHLD|1)&t;/* child has exited */
DECL|macro|CLD_KILLED
mdefine_line|#define CLD_KILLED&t;(__SI_CHLD|2)&t;/* child was killed */
DECL|macro|CLD_DUMPED
mdefine_line|#define CLD_DUMPED&t;(__SI_CHLD|3)&t;/* child terminated abnormally */
DECL|macro|CLD_TRAPPED
mdefine_line|#define CLD_TRAPPED&t;(__SI_CHLD|4)&t;/* traced child has trapped */
DECL|macro|CLD_STOPPED
mdefine_line|#define CLD_STOPPED&t;(__SI_CHLD|5)&t;/* child has stopped */
DECL|macro|CLD_CONTINUED
mdefine_line|#define CLD_CONTINUED&t;(__SI_CHLD|6)&t;/* stopped child has continued */
DECL|macro|NSIGCHLD
mdefine_line|#define NSIGCHLD&t;6
multiline_comment|/*&n; * SIGPOLL si_codes&n; */
DECL|macro|POLL_IN
mdefine_line|#define POLL_IN&t;&t;(__SI_POLL|1)&t;/* data input available */
DECL|macro|POLL_OUT
mdefine_line|#define POLL_OUT&t;(__SI_POLL|2)&t;/* output buffers available */
DECL|macro|POLL_MSG
mdefine_line|#define POLL_MSG&t;(__SI_POLL|3)&t;/* input message available */
DECL|macro|POLL_ERR
mdefine_line|#define POLL_ERR&t;(__SI_POLL|4)&t;/* i/o error */
DECL|macro|POLL_PRI
mdefine_line|#define POLL_PRI&t;(__SI_POLL|5)&t;/* high priority input available */
DECL|macro|POLL_HUP
mdefine_line|#define POLL_HUP&t;(__SI_POLL|6)&t;/* device disconnected */
DECL|macro|NSIGPOLL
mdefine_line|#define NSIGPOLL&t;6
multiline_comment|/*&n; * sigevent definitions&n; * &n; * It seems likely that SIGEV_THREAD will have to be handled from &n; * userspace, libpthread transmuting it to SIGEV_SIGNAL, which the&n; * thread manager then catches and does the appropriate nonsense.&n; * However, everything is written out here so as to not get lost.&n; */
DECL|macro|SIGEV_SIGNAL
mdefine_line|#define SIGEV_SIGNAL&t;0&t;/* notify via signal */
DECL|macro|SIGEV_NONE
mdefine_line|#define SIGEV_NONE&t;1&t;/* other notification: meaningless */
DECL|macro|SIGEV_THREAD
mdefine_line|#define SIGEV_THREAD&t;2&t;/* deliver via thread creation */
DECL|macro|SIGEV_MAX_SIZE
mdefine_line|#define SIGEV_MAX_SIZE&t;64
DECL|macro|SIGEV_PAD_SIZE
mdefine_line|#define SIGEV_PAD_SIZE&t;((SIGEV_MAX_SIZE/sizeof(int)) - 4)
DECL|struct|sigevent
r_typedef
r_struct
id|sigevent
(brace
DECL|member|sigev_value
id|sigval_t
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
id|SIGEV_PAD_SIZE
)braket
suffix:semicolon
r_struct
(brace
DECL|member|_function
r_void
(paren
op_star
id|_function
)paren
(paren
id|sigval_t
)paren
suffix:semicolon
DECL|member|_attribute
r_void
op_star
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
DECL|typedef|sigevent_t
)brace
id|sigevent_t
suffix:semicolon
DECL|macro|sigev_notify_function
mdefine_line|#define sigev_notify_function&t;_sigev_un._sigev_thread._function
DECL|macro|sigev_notify_attributes
mdefine_line|#define sigev_notify_attributes&t;_sigev_un._sigev_thread._attribute
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/string.h&gt;
DECL|function|copy_siginfo
r_extern
r_inline
r_void
id|copy_siginfo
c_func
(paren
id|siginfo_t
op_star
id|to
comma
id|siginfo_t
op_star
id|from
)paren
(brace
r_if
c_cond
(paren
id|from-&gt;si_code
OL
l_int|0
)paren
id|memcpy
c_func
(paren
id|to
comma
id|from
comma
r_sizeof
(paren
id|siginfo_t
)paren
)paren
suffix:semicolon
r_else
multiline_comment|/* _sigchld is currently the largest know union member */
id|memcpy
c_func
(paren
id|to
comma
id|from
comma
l_int|4
op_star
r_sizeof
(paren
r_int
)paren
op_plus
r_sizeof
(paren
id|from-&gt;_sifields._sigchld
)paren
)paren
suffix:semicolon
)brace
r_extern
r_int
id|copy_siginfo_to_user
c_func
(paren
id|siginfo_t
op_star
id|to
comma
id|siginfo_t
op_star
id|from
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
