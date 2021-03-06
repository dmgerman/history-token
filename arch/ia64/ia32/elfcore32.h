multiline_comment|/*&n; * IA-32 ELF core dump support.&n; *&n; * Copyright (C) 2003 Arun Sharma &lt;arun.sharma@intel.com&gt;&n; *&n; * Derived from the x86_64 version&n; */
macro_line|#ifndef _ELFCORE32_H_
DECL|macro|_ELFCORE32_H_
mdefine_line|#define _ELFCORE32_H_
macro_line|#include &lt;asm/intrinsics.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|USE_ELF_CORE_DUMP
mdefine_line|#define USE_ELF_CORE_DUMP 1
multiline_comment|/* Override elfcore.h */
DECL|macro|_LINUX_ELFCORE_H
mdefine_line|#define _LINUX_ELFCORE_H 1
DECL|typedef|elf_greg_t
r_typedef
r_int
r_int
id|elf_greg_t
suffix:semicolon
DECL|macro|ELF_NGREG
mdefine_line|#define ELF_NGREG (sizeof (struct user_regs_struct32) / sizeof(elf_greg_t))
DECL|typedef|elf_gregset_t
r_typedef
id|elf_greg_t
id|elf_gregset_t
(braket
id|ELF_NGREG
)braket
suffix:semicolon
DECL|typedef|elf_fpregset_t
r_typedef
r_struct
id|ia32_user_i387_struct
id|elf_fpregset_t
suffix:semicolon
DECL|typedef|elf_fpxregset_t
r_typedef
r_struct
id|ia32_user_fxsr_struct
id|elf_fpxregset_t
suffix:semicolon
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
DECL|macro|jiffies_to_timeval
mdefine_line|#define jiffies_to_timeval(a,b) do { (b)-&gt;tv_usec = 0; (b)-&gt;tv_sec = (a)/HZ; }while(0)
DECL|struct|elf_prstatus
r_struct
id|elf_prstatus
(brace
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
id|compat_timeval
id|pr_utime
suffix:semicolon
multiline_comment|/* User time */
DECL|member|pr_stime
r_struct
id|compat_timeval
id|pr_stime
suffix:semicolon
multiline_comment|/* System time */
DECL|member|pr_cutime
r_struct
id|compat_timeval
id|pr_cutime
suffix:semicolon
multiline_comment|/* Cumulative user time */
DECL|member|pr_cstime
r_struct
id|compat_timeval
id|pr_cstime
suffix:semicolon
multiline_comment|/* Cumulative system time */
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
id|__u16
id|pr_uid
suffix:semicolon
DECL|member|pr_gid
id|__u16
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
DECL|macro|ELF_CORE_COPY_REGS
mdefine_line|#define ELF_CORE_COPY_REGS(pr_reg, regs)       &t;&t;&bslash;&n;&t;pr_reg[0] = regs-&gt;r11;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[1] = regs-&gt;r9;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[2] = regs-&gt;r10;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[3] = regs-&gt;r14;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[4] = regs-&gt;r15;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[5] = regs-&gt;r13;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[6] = regs-&gt;r8;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[7] = regs-&gt;r16 &amp; 0xffff;&t;&t;&t;&bslash;&n;&t;pr_reg[8] = (regs-&gt;r16 &gt;&gt; 16) &amp; 0xffff;&t;&t;&bslash;&n;&t;pr_reg[9] = (regs-&gt;r16 &gt;&gt; 32) &amp; 0xffff;&t;&t;&bslash;&n;&t;pr_reg[10] = (regs-&gt;r16 &gt;&gt; 48) &amp; 0xffff;&t;&bslash;&n;&t;pr_reg[11] = regs-&gt;r1; &t;&t;&t;&t;&bslash;&n;&t;pr_reg[12] = regs-&gt;cr_iip;&t;&t;&t;&bslash;&n;&t;pr_reg[13] = regs-&gt;r17 &amp; 0xffff;&t;&t;&bslash;&n;&t;pr_reg[14] = ia64_getreg(_IA64_REG_AR_EFLAG);&t;&bslash;&n;&t;pr_reg[15] = regs-&gt;r12;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[16] = (regs-&gt;r17 &gt;&gt; 16) &amp; 0xffff;
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
r_struct
id|pt_regs
op_star
id|pp
op_assign
id|ia64_task_regs
c_func
(paren
id|t
)paren
suffix:semicolon
id|ELF_CORE_COPY_REGS
c_func
(paren
(paren
op_star
id|elfregs
)paren
comma
id|pp
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|elf_core_copy_task_fpregs
id|elf_core_copy_task_fpregs
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
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
r_struct
id|ia32_user_i387_struct
op_star
id|fpstate
op_assign
(paren
r_void
op_star
)paren
id|fpu
suffix:semicolon
id|mm_segment_t
id|old_fs
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tsk_used_math
c_func
(paren
id|tsk
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|old_fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|save_ia32_fpstate
c_func
(paren
id|tsk
comma
(paren
r_struct
id|ia32_user_i387_struct
id|__user
op_star
)paren
id|fpstate
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|old_fs
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|macro|ELF_CORE_COPY_XFPREGS
mdefine_line|#define ELF_CORE_COPY_XFPREGS 1
r_static
r_inline
r_int
DECL|function|elf_core_copy_task_xfpregs
id|elf_core_copy_task_xfpregs
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
id|elf_fpxregset_t
op_star
id|xfpu
)paren
(brace
r_struct
id|ia32_user_fxsr_struct
op_star
id|fpxstate
op_assign
(paren
r_void
op_star
)paren
id|xfpu
suffix:semicolon
id|mm_segment_t
id|old_fs
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tsk_used_math
c_func
(paren
id|tsk
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|old_fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|save_ia32_fpxstate
c_func
(paren
id|tsk
comma
(paren
r_struct
id|ia32_user_fxsr_struct
id|__user
op_star
)paren
id|fpxstate
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|old_fs
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif /* _ELFCORE32_H_ */
eof
