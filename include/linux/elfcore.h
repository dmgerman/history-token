macro_line|#ifndef _LINUX_ELFCORE_H
DECL|macro|_LINUX_ELFCORE_H
mdefine_line|#define _LINUX_ELFCORE_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/user.h&gt;
DECL|struct|elf_siginfo
r_struct
id|elf_siginfo
(brace
DECL|member|si_signo
r_int
id|si_signo
suffix:semicolon
multiline_comment|/* signal number */
DECL|member|si_code
r_int
id|si_code
suffix:semicolon
multiline_comment|/* extra code */
DECL|member|si_errno
r_int
id|si_errno
suffix:semicolon
multiline_comment|/* errno */
)brace
suffix:semicolon
macro_line|#include &lt;asm/elf.h&gt;
macro_line|#ifndef __KERNEL__
DECL|typedef|greg_t
r_typedef
id|elf_greg_t
id|greg_t
suffix:semicolon
DECL|typedef|gregset_t
r_typedef
id|elf_gregset_t
id|gregset_t
suffix:semicolon
DECL|typedef|fpregset_t
r_typedef
id|elf_fpregset_t
id|fpregset_t
suffix:semicolon
DECL|typedef|fpxregset_t
r_typedef
id|elf_fpxregset_t
id|fpxregset_t
suffix:semicolon
DECL|macro|NGREG
mdefine_line|#define NGREG ELF_NGREG
macro_line|#endif
multiline_comment|/*&n; * Definitions to generate Intel SVR4-like core files.&n; * These mostly have the same names as the SVR4 types with &quot;elf_&quot;&n; * tacked on the front to prevent clashes with linux definitions,&n; * and the typedef forms have been avoided.  This is mostly like&n; * the SVR4 structure, but more Linuxy, with things that Linux does&n; * not support and which gdb doesn&squot;t really use excluded.&n; * Fields present but not used are marked with &quot;XXX&quot;.&n; */
DECL|struct|elf_prstatus
r_struct
id|elf_prstatus
(brace
macro_line|#if 0
r_int
id|pr_flags
suffix:semicolon
multiline_comment|/* XXX Process flags */
r_int
id|pr_why
suffix:semicolon
multiline_comment|/* XXX Reason for process halt */
r_int
id|pr_what
suffix:semicolon
multiline_comment|/* XXX More detailed reason */
macro_line|#endif
DECL|member|pr_info
r_struct
id|elf_siginfo
id|pr_info
suffix:semicolon
multiline_comment|/* Info associated with signal */
DECL|member|pr_cursig
r_int
id|pr_cursig
suffix:semicolon
multiline_comment|/* Current signal */
DECL|member|pr_sigpend
r_int
r_int
id|pr_sigpend
suffix:semicolon
multiline_comment|/* Set of pending signals */
DECL|member|pr_sighold
r_int
r_int
id|pr_sighold
suffix:semicolon
multiline_comment|/* Set of held signals */
macro_line|#if 0
r_struct
id|sigaltstack
id|pr_altstack
suffix:semicolon
multiline_comment|/* Alternate stack info */
r_struct
id|sigaction
id|pr_action
suffix:semicolon
multiline_comment|/* Signal action for current sig */
macro_line|#endif
DECL|member|pr_pid
id|pid_t
id|pr_pid
suffix:semicolon
DECL|member|pr_ppid
id|pid_t
id|pr_ppid
suffix:semicolon
DECL|member|pr_pgrp
id|pid_t
id|pr_pgrp
suffix:semicolon
DECL|member|pr_sid
id|pid_t
id|pr_sid
suffix:semicolon
DECL|member|pr_utime
r_struct
id|timeval
id|pr_utime
suffix:semicolon
multiline_comment|/* User time */
DECL|member|pr_stime
r_struct
id|timeval
id|pr_stime
suffix:semicolon
multiline_comment|/* System time */
DECL|member|pr_cutime
r_struct
id|timeval
id|pr_cutime
suffix:semicolon
multiline_comment|/* Cumulative user time */
DECL|member|pr_cstime
r_struct
id|timeval
id|pr_cstime
suffix:semicolon
multiline_comment|/* Cumulative system time */
macro_line|#if 0
r_int
id|pr_instr
suffix:semicolon
multiline_comment|/* Current instruction */
macro_line|#endif
DECL|member|pr_reg
id|elf_gregset_t
id|pr_reg
suffix:semicolon
multiline_comment|/* GP registers */
DECL|member|pr_fpvalid
r_int
id|pr_fpvalid
suffix:semicolon
multiline_comment|/* True if math co-processor being used.  */
)brace
suffix:semicolon
DECL|macro|ELF_PRARGSZ
mdefine_line|#define ELF_PRARGSZ&t;(80)&t;/* Number of chars for args */
DECL|struct|elf_prpsinfo
r_struct
id|elf_prpsinfo
(brace
DECL|member|pr_state
r_char
id|pr_state
suffix:semicolon
multiline_comment|/* numeric process state */
DECL|member|pr_sname
r_char
id|pr_sname
suffix:semicolon
multiline_comment|/* char for pr_state */
DECL|member|pr_zomb
r_char
id|pr_zomb
suffix:semicolon
multiline_comment|/* zombie */
DECL|member|pr_nice
r_char
id|pr_nice
suffix:semicolon
multiline_comment|/* nice val */
DECL|member|pr_flag
r_int
r_int
id|pr_flag
suffix:semicolon
multiline_comment|/* flags */
DECL|member|pr_uid
id|__kernel_uid_t
id|pr_uid
suffix:semicolon
DECL|member|pr_gid
id|__kernel_gid_t
id|pr_gid
suffix:semicolon
DECL|member|pr_pid
DECL|member|pr_ppid
DECL|member|pr_pgrp
DECL|member|pr_sid
id|pid_t
id|pr_pid
comma
id|pr_ppid
comma
id|pr_pgrp
comma
id|pr_sid
suffix:semicolon
multiline_comment|/* Lots missing */
DECL|member|pr_fname
r_char
id|pr_fname
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* filename of executable */
DECL|member|pr_psargs
r_char
id|pr_psargs
(braket
id|ELF_PRARGSZ
)braket
suffix:semicolon
multiline_comment|/* initial part of arg list */
)brace
suffix:semicolon
macro_line|#ifndef __KERNEL__
DECL|typedef|prstatus_t
r_typedef
r_struct
id|elf_prstatus
id|prstatus_t
suffix:semicolon
DECL|typedef|prpsinfo_t
r_typedef
r_struct
id|elf_prpsinfo
id|prpsinfo_t
suffix:semicolon
DECL|macro|PRARGSZ
mdefine_line|#define PRARGSZ ELF_PRARGSZ 
macro_line|#endif
macro_line|#ifdef __KERNEL__
DECL|function|elf_core_copy_regs
r_static
r_inline
r_void
id|elf_core_copy_regs
c_func
(paren
id|elf_gregset_t
op_star
id|elfregs
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
macro_line|#ifdef ELF_CORE_COPY_REGS
id|ELF_CORE_COPY_REGS
c_func
(paren
(paren
op_star
id|elfregs
)paren
comma
id|regs
)paren
macro_line|#else
id|BUG_ON
c_func
(paren
r_sizeof
(paren
op_star
id|elfregs
)paren
op_ne
r_sizeof
(paren
op_star
id|regs
)paren
)paren
suffix:semicolon
op_star
(paren
r_struct
id|pt_regs
op_star
)paren
id|elfregs
op_assign
op_star
id|regs
suffix:semicolon
macro_line|#endif
)brace
DECL|function|elf_core_copy_task_regs
r_static
r_inline
r_int
id|elf_core_copy_task_regs
c_func
(paren
r_struct
id|task_struct
op_star
id|t
comma
id|elf_gregset_t
op_star
id|elfregs
)paren
(brace
macro_line|#ifdef ELF_CORE_COPY_TASK_REGS
r_return
id|ELF_CORE_COPY_TASK_REGS
c_func
(paren
id|t
comma
id|elfregs
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
r_extern
r_int
id|dump_fpu
(paren
r_struct
id|pt_regs
op_star
comma
id|elf_fpregset_t
op_star
)paren
suffix:semicolon
DECL|function|elf_core_copy_task_fpregs
r_static
r_inline
r_int
id|elf_core_copy_task_fpregs
c_func
(paren
r_struct
id|task_struct
op_star
id|t
comma
r_struct
id|pt_regs
op_star
id|regs
comma
id|elf_fpregset_t
op_star
id|fpu
)paren
(brace
macro_line|#ifdef ELF_CORE_COPY_FPREGS
r_return
id|ELF_CORE_COPY_FPREGS
c_func
(paren
id|t
comma
id|fpu
)paren
suffix:semicolon
macro_line|#else
r_return
id|dump_fpu
c_func
(paren
id|regs
comma
id|fpu
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#ifdef ELF_CORE_COPY_XFPREGS
DECL|function|elf_core_copy_task_xfpregs
r_static
r_inline
r_int
id|elf_core_copy_task_xfpregs
c_func
(paren
r_struct
id|task_struct
op_star
id|t
comma
id|elf_fpxregset_t
op_star
id|xfpu
)paren
(brace
r_return
id|ELF_CORE_COPY_XFPREGS
c_func
(paren
id|t
comma
id|xfpu
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_ELFCORE_H */
eof
