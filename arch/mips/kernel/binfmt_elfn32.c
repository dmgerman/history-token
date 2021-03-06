multiline_comment|/*&n; * Support for n32 Linux/MIPS ELF binaries.&n; *&n; * Copyright (C) 1999, 2001 Ralf Baechle&n; * Copyright (C) 1999, 2001 Silicon Graphics, Inc.&n; *&n; * Heavily inspired by the 32-bit Sparc compat code which is&n; * Copyright (C) 1995, 1996, 1997, 1998 David S. Miller (davem@redhat.com)&n; * Copyright (C) 1995, 1996, 1997, 1998 Jakub Jelinek   (jj@ultra.linux.cz)&n; */
DECL|macro|ELF_ARCH
mdefine_line|#define ELF_ARCH&t;&t;EM_MIPS
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS&t;&t;ELFCLASS32
macro_line|#ifdef __MIPSEB__
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;&t;ELFDATA2MSB;
macro_line|#else /* __MIPSEL__ */
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;&t;ELFDATA2LSB;
macro_line|#endif
multiline_comment|/* ELF register definitions */
DECL|macro|ELF_NGREG
mdefine_line|#define ELF_NGREG&t;45
DECL|macro|ELF_NFPREG
mdefine_line|#define ELF_NFPREG&t;33
DECL|typedef|elf_greg_t
r_typedef
r_int
r_int
id|elf_greg_t
suffix:semicolon
DECL|typedef|elf_gregset_t
r_typedef
id|elf_greg_t
id|elf_gregset_t
(braket
id|ELF_NGREG
)braket
suffix:semicolon
DECL|typedef|elf_fpreg_t
r_typedef
r_float
id|elf_fpreg_t
suffix:semicolon
DECL|typedef|elf_fpregset_t
r_typedef
id|elf_fpreg_t
id|elf_fpregset_t
(braket
id|ELF_NFPREG
)braket
suffix:semicolon
multiline_comment|/*&n; * This is used to ensure we don&squot;t load something for the wrong architecture.&n; */
DECL|macro|elf_check_arch
mdefine_line|#define elf_check_arch(hdr)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int __res = 1;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct elfhdr *__h = (hdr);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__h-&gt;e_machine != EM_MIPS)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__res = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__h-&gt;e_ident[EI_CLASS] != ELFCLASS32)&t;&t;&t;&bslash;&n;&t;&t;__res = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (((__h-&gt;e_flags &amp; EF_MIPS_ABI2) == 0) ||&t;&t;&t;&bslash;&n;&t;    ((__h-&gt;e_flags &amp; EF_MIPS_ABI) != 0))&t;&t;&t;&bslash;&n;&t;&t;__res = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|TASK32_SIZE
mdefine_line|#define TASK32_SIZE&t;&t;0x7fff8000UL
DECL|macro|ELF_ET_DYN_BASE
macro_line|#undef ELF_ET_DYN_BASE
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE         (TASK32_SIZE / 3 * 2)
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/elfcore.h&gt;
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
DECL|macro|elf_addr_t
mdefine_line|#define elf_addr_t&t;u32
DECL|macro|elf_caddr_t
mdefine_line|#define elf_caddr_t&t;u32
DECL|macro|init_elf_binfmt
mdefine_line|#define init_elf_binfmt init_elfn32_binfmt
DECL|macro|jiffies_to_timeval
mdefine_line|#define jiffies_to_timeval jiffies_to_compat_timeval
r_static
id|__inline__
r_void
DECL|function|jiffies_to_compat_timeval
id|jiffies_to_compat_timeval
c_func
(paren
r_int
r_int
id|jiffies
comma
r_struct
id|compat_timeval
op_star
id|value
)paren
(brace
multiline_comment|/*&n;&t; * Convert jiffies to nanoseconds and seperate with&n;&t; * one divide.&n;&t; */
id|u64
id|nsec
op_assign
(paren
id|u64
)paren
id|jiffies
op_star
id|TICK_NSEC
suffix:semicolon
id|value-&gt;tv_sec
op_assign
id|div_long_long_rem
c_func
(paren
id|nsec
comma
id|NSEC_PER_SEC
comma
op_amp
id|value-&gt;tv_usec
)paren
suffix:semicolon
id|value-&gt;tv_usec
op_div_assign
id|NSEC_PER_USEC
suffix:semicolon
)brace
DECL|macro|ELF_CORE_EFLAGS
mdefine_line|#define ELF_CORE_EFLAGS EF_MIPS_ABI2
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Binary format loader for compatibility with n32 Linux/MIPS binaries&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Ralf Baechle (ralf@linux-mips.org)&quot;
)paren
suffix:semicolon
DECL|macro|MODULE_DESCRIPTION
macro_line|#undef MODULE_DESCRIPTION
DECL|macro|MODULE_AUTHOR
macro_line|#undef MODULE_AUTHOR
macro_line|#include &quot;../../../fs/binfmt_elf.c&quot;
eof
