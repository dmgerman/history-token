multiline_comment|/* $Id: signal.h,v 1.3 1998/04/12 06:20:33 davem Exp $&n; * signal.h: Signal emulation for Solaris&n; *&n; * Copyright (C) 1997 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; */
DECL|macro|SOLARIS_SIGHUP
mdefine_line|#define SOLARIS_SIGHUP&t;&t;1
DECL|macro|SOLARIS_SIGINT
mdefine_line|#define SOLARIS_SIGINT&t;&t;2
DECL|macro|SOLARIS_SIGQUIT
mdefine_line|#define SOLARIS_SIGQUIT&t;&t;3
DECL|macro|SOLARIS_SIGILL
mdefine_line|#define SOLARIS_SIGILL&t;&t;4
DECL|macro|SOLARIS_SIGTRAP
mdefine_line|#define SOLARIS_SIGTRAP&t;&t;5
DECL|macro|SOLARIS_SIGIOT
mdefine_line|#define SOLARIS_SIGIOT&t;&t;6
DECL|macro|SOLARIS_SIGEMT
mdefine_line|#define SOLARIS_SIGEMT&t;&t;7
DECL|macro|SOLARIS_SIGFPE
mdefine_line|#define SOLARIS_SIGFPE&t;&t;8
DECL|macro|SOLARIS_SIGKILL
mdefine_line|#define SOLARIS_SIGKILL&t;&t;9
DECL|macro|SOLARIS_SIGBUS
mdefine_line|#define SOLARIS_SIGBUS&t;&t;10
DECL|macro|SOLARIS_SIGSEGV
mdefine_line|#define SOLARIS_SIGSEGV&t;&t;11
DECL|macro|SOLARIS_SIGSYS
mdefine_line|#define SOLARIS_SIGSYS&t;&t;12
DECL|macro|SOLARIS_SIGPIPE
mdefine_line|#define SOLARIS_SIGPIPE&t;&t;13
DECL|macro|SOLARIS_SIGALRM
mdefine_line|#define SOLARIS_SIGALRM&t;&t;14
DECL|macro|SOLARIS_SIGTERM
mdefine_line|#define SOLARIS_SIGTERM&t;&t;15
DECL|macro|SOLARIS_SIGUSR1
mdefine_line|#define SOLARIS_SIGUSR1&t;&t;16
DECL|macro|SOLARIS_SIGUSR2
mdefine_line|#define SOLARIS_SIGUSR2&t;&t;17
DECL|macro|SOLARIS_SIGCLD
mdefine_line|#define SOLARIS_SIGCLD&t;&t;18
DECL|macro|SOLARIS_SIGPWR
mdefine_line|#define SOLARIS_SIGPWR&t;&t;19
DECL|macro|SOLARIS_SIGWINCH
mdefine_line|#define SOLARIS_SIGWINCH&t;20
DECL|macro|SOLARIS_SIGURG
mdefine_line|#define SOLARIS_SIGURG&t;&t;21
DECL|macro|SOLARIS_SIGPOLL
mdefine_line|#define SOLARIS_SIGPOLL&t;&t;22
DECL|macro|SOLARIS_SIGSTOP
mdefine_line|#define SOLARIS_SIGSTOP&t;&t;23
DECL|macro|SOLARIS_SIGTSTP
mdefine_line|#define SOLARIS_SIGTSTP&t;&t;24
DECL|macro|SOLARIS_SIGCONT
mdefine_line|#define SOLARIS_SIGCONT&t;&t;25
DECL|macro|SOLARIS_SIGTTIN
mdefine_line|#define SOLARIS_SIGTTIN&t;&t;26
DECL|macro|SOLARIS_SIGTTOU
mdefine_line|#define SOLARIS_SIGTTOU&t;&t;27
DECL|macro|SOLARIS_SIGVTALRM
mdefine_line|#define SOLARIS_SIGVTALRM&t;28
DECL|macro|SOLARIS_SIGPROF
mdefine_line|#define SOLARIS_SIGPROF&t;&t;29
DECL|macro|SOLARIS_SIGXCPU
mdefine_line|#define SOLARIS_SIGXCPU&t;&t;30
DECL|macro|SOLARIS_SIGXFSZ
mdefine_line|#define SOLARIS_SIGXFSZ&t;&t;31
DECL|macro|SOLARIS_SIGWAITING
mdefine_line|#define SOLARIS_SIGWAITING&t;32
DECL|macro|SOLARIS_SIGLWP
mdefine_line|#define SOLARIS_SIGLWP&t;&t;33
DECL|macro|SOLARIS_SIGFREEZE
mdefine_line|#define SOLARIS_SIGFREEZE&t;34
DECL|macro|SOLARIS_SIGTHAW
mdefine_line|#define SOLARIS_SIGTHAW&t;&t;35
DECL|macro|SOLARIS_SIGCANCEL
mdefine_line|#define SOLARIS_SIGCANCEL&t;36
DECL|macro|SOLARIS_SIGRTMIN
mdefine_line|#define SOLARIS_SIGRTMIN&t;37
DECL|macro|SOLARIS_SIGRTMAX
mdefine_line|#define SOLARIS_SIGRTMAX&t;44
DECL|macro|SOLARIS_NSIGNALS
mdefine_line|#define SOLARIS_NSIGNALS&t;44
DECL|macro|SOLARIS_SA_ONSTACK
mdefine_line|#define SOLARIS_SA_ONSTACK&t;1
DECL|macro|SOLARIS_SA_RESETHAND
mdefine_line|#define SOLARIS_SA_RESETHAND&t;2
DECL|macro|SOLARIS_SA_RESTART
mdefine_line|#define SOLARIS_SA_RESTART&t;4
DECL|macro|SOLARIS_SA_SIGINFO
mdefine_line|#define SOLARIS_SA_SIGINFO&t;8
DECL|macro|SOLARIS_SA_NODEFER
mdefine_line|#define SOLARIS_SA_NODEFER&t;16
DECL|macro|SOLARIS_SA_NOCLDWAIT
mdefine_line|#define SOLARIS_SA_NOCLDWAIT&t;0x10000
DECL|macro|SOLARIS_SA_NOCLDSTOP
mdefine_line|#define SOLARIS_SA_NOCLDSTOP&t;0x20000
DECL|struct|sol_siginfo
r_struct
id|sol_siginfo
(brace
DECL|member|si_signo
r_int
id|si_signo
suffix:semicolon
DECL|member|si_code
r_int
id|si_code
suffix:semicolon
DECL|member|si_errno
r_int
id|si_errno
suffix:semicolon
r_union
(brace
DECL|member|pad
r_char
id|pad
(braket
l_int|128
op_minus
l_int|3
op_star
r_sizeof
(paren
r_int
)paren
)braket
suffix:semicolon
r_struct
(brace
DECL|member|_pid
id|s32
id|_pid
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|_uid
id|s32
id|_uid
suffix:semicolon
DECL|member|_value
id|s32
id|_value
suffix:semicolon
DECL|member|_kill
)brace
id|_kill
suffix:semicolon
r_struct
(brace
DECL|member|_utime
id|s32
id|_utime
suffix:semicolon
DECL|member|_status
r_int
id|_status
suffix:semicolon
DECL|member|_stime
id|s32
id|_stime
suffix:semicolon
DECL|member|_cld
)brace
id|_cld
suffix:semicolon
DECL|member|_pdata
)brace
id|_pdata
suffix:semicolon
DECL|member|_proc
)brace
id|_proc
suffix:semicolon
r_struct
(brace
multiline_comment|/* SIGSEGV, SIGBUS, SIGILL and SIGFPE */
DECL|member|_addr
id|u32
id|_addr
suffix:semicolon
DECL|member|_trapno
r_int
id|_trapno
suffix:semicolon
DECL|member|_fault
)brace
id|_fault
suffix:semicolon
r_struct
(brace
multiline_comment|/* SIGPOLL, SIGXFSZ */
DECL|member|_fd
r_int
id|_fd
suffix:semicolon
DECL|member|_band
id|s32
id|_band
suffix:semicolon
DECL|member|_file
)brace
id|_file
suffix:semicolon
DECL|member|_data
)brace
id|_data
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SOLARIS_WUNTRACED
mdefine_line|#define SOLARIS_WUNTRACED&t;0x04
DECL|macro|SOLARIS_WNOHANG
mdefine_line|#define SOLARIS_WNOHANG&t;&t;0x40
DECL|macro|SOLARIS_WEXITED
mdefine_line|#define SOLARIS_WEXITED         0x01
DECL|macro|SOLARIS_WTRAPPED
mdefine_line|#define SOLARIS_WTRAPPED        0x02
DECL|macro|SOLARIS_WSTOPPED
mdefine_line|#define SOLARIS_WSTOPPED        WUNTRACED
DECL|macro|SOLARIS_WCONTINUED
mdefine_line|#define SOLARIS_WCONTINUED      0x08
DECL|macro|SOLARIS_WNOWAIT
mdefine_line|#define SOLARIS_WNOWAIT         0x80
DECL|macro|SOLARIS_TRAP_BRKPT
mdefine_line|#define SOLARIS_TRAP_BRKPT      1
DECL|macro|SOLARIS_TRAP_TRACE
mdefine_line|#define SOLARIS_TRAP_TRACE      2
DECL|macro|SOLARIS_CLD_EXITED
mdefine_line|#define SOLARIS_CLD_EXITED      1
DECL|macro|SOLARIS_CLD_KILLED
mdefine_line|#define SOLARIS_CLD_KILLED      2
DECL|macro|SOLARIS_CLD_DUMPED
mdefine_line|#define SOLARIS_CLD_DUMPED      3
DECL|macro|SOLARIS_CLD_TRAPPED
mdefine_line|#define SOLARIS_CLD_TRAPPED     4
DECL|macro|SOLARIS_CLD_STOPPED
mdefine_line|#define SOLARIS_CLD_STOPPED     5
DECL|macro|SOLARIS_CLD_CONTINUED
mdefine_line|#define SOLARIS_CLD_CONTINUED   6
DECL|macro|SOLARIS_POLL_IN
mdefine_line|#define SOLARIS_POLL_IN         1
DECL|macro|SOLARIS_POLL_OUT
mdefine_line|#define SOLARIS_POLL_OUT        2
DECL|macro|SOLARIS_POLL_MSG
mdefine_line|#define SOLARIS_POLL_MSG        3
DECL|macro|SOLARIS_POLL_ERR
mdefine_line|#define SOLARIS_POLL_ERR        4
DECL|macro|SOLARIS_POLL_PRI
mdefine_line|#define SOLARIS_POLL_PRI        5
DECL|macro|SOLARIS_POLL_HUP
mdefine_line|#define SOLARIS_POLL_HUP        6
eof
