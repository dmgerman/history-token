multiline_comment|/*&n; * Support for 32-bit Linux for S390 ELF binaries.&n; *&n; * Copyright (C) 2000 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; * Author(s): Gerhard Tonn (ton@de.ibm.com)&n; *&n; * Heavily inspired by the 32-bit Sparc compat code which is&n; * Copyright (C) 1995, 1996, 1997, 1998 David S. Miller (davem@redhat.com)&n; * Copyright (C) 1995, 1996, 1997, 1998 Jakub Jelinek   (jj@ultra.linux.cz)&n; */
DECL|macro|__ASMS390_ELF_H
mdefine_line|#define __ASMS390_ELF_H
macro_line|#include &lt;linux/time.h&gt;
multiline_comment|/*&n; * These are used to set parameters in the core dumps.&n; */
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS&t;ELFCLASS32
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;ELFDATA2MSB
DECL|macro|ELF_ARCH
mdefine_line|#define ELF_ARCH&t;EM_S390
multiline_comment|/*&n; * This is used to ensure we don&squot;t load something for the wrong architecture.&n; */
DECL|macro|elf_check_arch
mdefine_line|#define elf_check_arch(x) &bslash;&n;&t;(((x)-&gt;e_machine == EM_S390 || (x)-&gt;e_machine == EM_S390_OLD) &bslash;&n;         &amp;&amp; (x)-&gt;e_ident[EI_CLASS] == ELF_CLASS)
multiline_comment|/* ELF register definitions */
DECL|macro|NUM_GPRS
mdefine_line|#define NUM_GPRS      16
DECL|macro|NUM_FPRS
mdefine_line|#define NUM_FPRS      16
DECL|macro|NUM_ACRS
mdefine_line|#define NUM_ACRS      16    
multiline_comment|/* For SVR4/S390 the function pointer to be registered with `atexit` is&n;   passed in R14. */
DECL|macro|ELF_PLAT_INIT
mdefine_line|#define ELF_PLAT_INIT(_r, load_addr) &bslash;&n;&t;do { &bslash;&n;&t;&t;_r-&gt;gprs[14] = 0; &bslash;&n;&t;} while(0)
DECL|macro|USE_ELF_CORE_DUMP
mdefine_line|#define USE_ELF_CORE_DUMP
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE       4096
multiline_comment|/* This is the location that an ET_DYN program is loaded if exec&squot;ed.  Typical&n;   use of this is to invoke &quot;./ld.so someprog&quot; to test out a new version of&n;   the loader.  We need to make sure that it is out of the way of the program&n;   that it will &quot;exec&quot;, and that there is sufficient room for the brk.  */
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE         (TASK_SIZE / 3 * 2)
multiline_comment|/* Wow, the &quot;main&quot; arch needs arch dependent functions too.. :) */
multiline_comment|/* regs is struct pt_regs, pr_reg is elf_gregset_t (which is&n;   now struct_user_regs, they are different) */
DECL|macro|ELF_CORE_COPY_REGS
mdefine_line|#define ELF_CORE_COPY_REGS(pr_reg, regs) dump_regs32(regs, &amp;pr_reg);
DECL|macro|ELF_CORE_COPY_TASK_REGS
mdefine_line|#define ELF_CORE_COPY_TASK_REGS(tsk, regs) dump_task_regs32(tsk, regs)
DECL|macro|ELF_CORE_COPY_FPREGS
mdefine_line|#define ELF_CORE_COPY_FPREGS(tsk, fpregs) dump_task_fpu(tsk, fpregs)
multiline_comment|/* This yields a mask that user programs can use to figure out what&n;   instruction set this CPU supports. */
DECL|macro|ELF_HWCAP
mdefine_line|#define ELF_HWCAP (0)
multiline_comment|/* This yields a string that ld.so will use to load implementation&n;   specific libraries for optimization.  This is more specific in&n;   intent than poking at uname or /proc/cpuinfo.&n;&n;   For the moment, we have only optimizations for the Intel generations,&n;   but that could change... */
DECL|macro|ELF_PLATFORM
mdefine_line|#define ELF_PLATFORM (NULL)
DECL|macro|SET_PERSONALITY
mdefine_line|#define SET_PERSONALITY(ex, ibcs2)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (ibcs2)                                      &bslash;&n;&t;&t;set_personality(PER_SVR4);              &bslash;&n;&t;else if (current-&gt;personality != PER_LINUX32)   &bslash;&n;&t;&t;set_personality(PER_LINUX);             &bslash;&n;&t;set_thread_flag(TIF_31BIT);&t;&t;&t;&bslash;&n;} while (0)
macro_line|#include &quot;compat_linux.h&quot;
DECL|typedef|elf_fpregset_t
r_typedef
id|_s390_fp_regs32
id|elf_fpregset_t
suffix:semicolon
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
DECL|member|orig_gpr2
id|__u32
id|orig_gpr2
suffix:semicolon
DECL|typedef|s390_regs32
)brace
id|s390_regs32
suffix:semicolon
DECL|typedef|elf_gregset_t
r_typedef
id|s390_regs32
id|elf_gregset_t
suffix:semicolon
DECL|function|dump_regs32
r_static
r_inline
r_int
id|dump_regs32
c_func
(paren
r_struct
id|pt_regs
op_star
id|ptregs
comma
id|elf_gregset_t
op_star
id|regs
)paren
(brace
r_int
id|i
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|regs-&gt;psw.mask
comma
op_amp
id|ptregs-&gt;psw.mask
comma
l_int|4
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|regs-&gt;psw.addr
comma
(paren
r_char
op_star
)paren
op_amp
id|ptregs-&gt;psw.addr
op_plus
l_int|4
comma
l_int|4
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_GPRS
suffix:semicolon
id|i
op_increment
)paren
id|regs-&gt;gprs
(braket
id|i
)braket
op_assign
id|ptregs-&gt;gprs
(braket
id|i
)braket
suffix:semicolon
id|save_access_regs
c_func
(paren
id|regs-&gt;acrs
)paren
suffix:semicolon
id|regs-&gt;orig_gpr2
op_assign
id|ptregs-&gt;orig_gpr2
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|dump_task_regs32
r_static
r_inline
r_int
id|dump_task_regs32
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
id|elf_gregset_t
op_star
id|regs
)paren
(brace
r_struct
id|pt_regs
op_star
id|ptregs
op_assign
id|__KSTK_PTREGS
c_func
(paren
id|tsk
)paren
suffix:semicolon
r_int
id|i
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|regs-&gt;psw.mask
comma
op_amp
id|ptregs-&gt;psw.mask
comma
l_int|4
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|regs-&gt;psw.addr
comma
(paren
r_char
op_star
)paren
op_amp
id|ptregs-&gt;psw.addr
op_plus
l_int|4
comma
l_int|4
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_GPRS
suffix:semicolon
id|i
op_increment
)paren
id|regs-&gt;gprs
(braket
id|i
)braket
op_assign
id|ptregs-&gt;gprs
(braket
id|i
)braket
suffix:semicolon
id|memcpy
c_func
(paren
id|regs-&gt;acrs
comma
id|tsk-&gt;thread.acrs
comma
r_sizeof
(paren
id|regs-&gt;acrs
)paren
)paren
suffix:semicolon
id|regs-&gt;orig_gpr2
op_assign
id|ptregs-&gt;orig_gpr2
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|dump_task_fpu
r_static
r_inline
r_int
id|dump_task_fpu
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
id|elf_fpregset_t
op_star
id|fpregs
)paren
(brace
r_if
c_cond
(paren
id|tsk
op_eq
id|current
)paren
id|save_fp_regs
c_func
(paren
(paren
id|s390_fp_regs
op_star
)paren
id|fpregs
)paren
suffix:semicolon
r_else
id|memcpy
c_func
(paren
id|fpregs
comma
op_amp
id|tsk-&gt;thread.fp_regs
comma
r_sizeof
(paren
id|elf_fpregset_t
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/elfcore.h&gt;
macro_line|#include &lt;linux/binfmts.h&gt;
macro_line|#include &lt;linux/compat.h&gt;
DECL|macro|elf_prstatus
mdefine_line|#define elf_prstatus elf_prstatus32
DECL|struct|elf_prstatus32
r_struct
id|elf_prstatus32
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
id|u32
id|pr_sigpend
suffix:semicolon
multiline_comment|/* Set of pending signals */
DECL|member|pr_sighold
id|u32
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
DECL|macro|elf_prpsinfo
mdefine_line|#define elf_prpsinfo elf_prpsinfo32
DECL|struct|elf_prpsinfo32
r_struct
id|elf_prpsinfo32
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
id|u32
id|pr_flag
suffix:semicolon
multiline_comment|/* flags */
DECL|member|pr_uid
id|u16
id|pr_uid
suffix:semicolon
DECL|member|pr_gid
id|u16
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
macro_line|#include &lt;linux/highuid.h&gt;
DECL|macro|NEW_TO_OLD_UID
macro_line|#undef NEW_TO_OLD_UID
DECL|macro|NEW_TO_OLD_GID
macro_line|#undef NEW_TO_OLD_GID
DECL|macro|NEW_TO_OLD_UID
mdefine_line|#define NEW_TO_OLD_UID(uid) ((uid) &gt; 65535) ? (u16)overflowuid : (u16)(uid)
DECL|macro|NEW_TO_OLD_GID
mdefine_line|#define NEW_TO_OLD_GID(gid) ((gid) &gt; 65535) ? (u16)overflowgid : (u16)(gid) 
DECL|macro|elf_addr_t
mdefine_line|#define elf_addr_t&t;u32
multiline_comment|/*&n;#define init_elf_binfmt init_elf32_binfmt&n;*/
DECL|macro|start_thread
macro_line|#undef start_thread
DECL|macro|start_thread
mdefine_line|#define start_thread                    start_thread31 
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Binary format loader for compatibility with 32bit Linux for S390 binaries,&quot;
l_string|&quot; Copyright 2000 IBM Corporation&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Gerhard Tonn &lt;ton@de.ibm.com&gt;&quot;
)paren
suffix:semicolon
DECL|macro|MODULE_DESCRIPTION
macro_line|#undef MODULE_DESCRIPTION
DECL|macro|MODULE_AUTHOR
macro_line|#undef MODULE_AUTHOR
DECL|macro|cputime_to_timeval
macro_line|#undef cputime_to_timeval
DECL|macro|cputime_to_timeval
mdefine_line|#define cputime_to_timeval cputime_to_compat_timeval
r_static
id|__inline__
r_void
DECL|function|cputime_to_compat_timeval
id|cputime_to_compat_timeval
c_func
(paren
r_const
id|cputime_t
id|cputime
comma
r_struct
id|compat_timeval
op_star
id|value
)paren
(brace
r_int
r_int
id|jiffies
op_assign
id|cputime_to_jiffies
c_func
(paren
id|cputime
)paren
suffix:semicolon
id|value-&gt;tv_usec
op_assign
(paren
id|jiffies
op_mod
id|HZ
)paren
op_star
(paren
l_int|1000000L
op_div
id|HZ
)paren
suffix:semicolon
id|value-&gt;tv_sec
op_assign
id|jiffies
op_div
id|HZ
suffix:semicolon
)brace
macro_line|#include &quot;../../../fs/binfmt_elf.c&quot;
eof
