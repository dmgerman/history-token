multiline_comment|/*&n; * Support for 32-bit Linux/Parisc ELF binaries on 64 bit kernels&n; *&n; * Copyright (C) 2000 John Marvin&n; * Copyright (C) 2000 Hewlett Packard Co.&n; *&n; * Heavily inspired from various other efforts to do the same thing&n; * (ia64,sparc64/mips64)&n; */
multiline_comment|/* Make sure include/asm-parisc/elf.h does the right thing */
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS&t;ELFCLASS32
DECL|macro|ELF_CORE_COPY_REGS
mdefine_line|#define ELF_CORE_COPY_REGS(dst, pt)&t;&bslash;&n;&t;memset(dst, 0, sizeof(dst));&t;/* don&squot;t leak any &quot;random&quot; bits */ &bslash;&n;&t;{&t;int i; &bslash;&n;&t;&t;for (i = 0; i &lt; 32; i++) dst[i] = (elf_greg_t) pt-&gt;gr[i]; &bslash;&n;&t;&t;for (i = 0; i &lt; 8; i++) dst[32 + i] = (elf_greg_t) pt-&gt;sr[i]; &bslash;&n;&t;} &bslash;&n;&t;dst[40] = (elf_greg_t) pt-&gt;iaoq[0]; dst[41] = (elf_greg_t) pt-&gt;iaoq[1]; &bslash;&n;&t;dst[42] = (elf_greg_t) pt-&gt;iasq[0]; dst[43] = (elf_greg_t) pt-&gt;iasq[1]; &bslash;&n;&t;dst[44] = (elf_greg_t) pt-&gt;sar;   dst[45] = (elf_greg_t) pt-&gt;iir; &bslash;&n;&t;dst[46] = (elf_greg_t) pt-&gt;isr;   dst[47] = (elf_greg_t) pt-&gt;ior; &bslash;&n;&t;dst[48] = (elf_greg_t) mfctl(22); dst[49] = (elf_greg_t) mfctl(0); &bslash;&n;&t;dst[50] = (elf_greg_t) mfctl(24); dst[51] = (elf_greg_t) mfctl(25); &bslash;&n;&t;dst[52] = (elf_greg_t) mfctl(26); dst[53] = (elf_greg_t) mfctl(27); &bslash;&n;&t;dst[54] = (elf_greg_t) mfctl(28); dst[55] = (elf_greg_t) mfctl(29); &bslash;&n;&t;dst[56] = (elf_greg_t) mfctl(30); dst[57] = (elf_greg_t) mfctl(31); &bslash;&n;&t;dst[58] = (elf_greg_t) mfctl( 8); dst[59] = (elf_greg_t) mfctl( 9); &bslash;&n;&t;dst[60] = (elf_greg_t) mfctl(12); dst[61] = (elf_greg_t) mfctl(13); &bslash;&n;&t;dst[62] = (elf_greg_t) mfctl(10); dst[63] = (elf_greg_t) mfctl(15);
DECL|typedef|elf_greg_t
r_typedef
r_int
r_int
id|elf_greg_t
suffix:semicolon
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/elfcore.h&gt;
macro_line|#include &lt;linux/compat.h&gt;&t;&t;/* struct compat_timeval */
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
DECL|macro|elf_addr_t
mdefine_line|#define elf_addr_t&t;unsigned int
DECL|macro|init_elf_binfmt
mdefine_line|#define init_elf_binfmt init_elf32_binfmt
DECL|macro|ELF_PLATFORM
mdefine_line|#define ELF_PLATFORM  (&quot;PARISC32&bslash;0&quot;)
multiline_comment|/*&n; * We should probably use this macro to set a flag somewhere to indicate&n; * this is a 32 on 64 process. We could use PER_LINUX_32BIT, or we&n; * could set a processor dependent flag in the thread_struct.&n; */
DECL|macro|SET_PERSONALITY
mdefine_line|#define SET_PERSONALITY(ex, ibcs2) &bslash;&n;&t;current-&gt;personality = PER_LINUX32; &bslash;&n;&t;current-&gt;thread.map_base = DEFAULT_MAP_BASE32; &bslash;&n;&t;current-&gt;thread.task_size = DEFAULT_TASK_SIZE32 &bslash;&n;
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
multiline_comment|/* Set up a separate execution domain for ELF32 binaries running&n; * on an ELF64 kernel */
DECL|variable|parisc32_exec_domain
r_static
r_struct
id|exec_domain
id|parisc32_exec_domain
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Linux/ELF32&quot;
comma
dot
id|pers_low
op_assign
id|PER_LINUX32
comma
dot
id|pers_high
op_assign
id|PER_LINUX32
comma
)brace
suffix:semicolon
DECL|function|parisc32_exec_init
r_static
r_int
id|__init
id|parisc32_exec_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* steal the identity signal mappings from the default domain */
id|parisc32_exec_domain.signal_map
op_assign
id|default_exec_domain.signal_map
suffix:semicolon
id|parisc32_exec_domain.signal_invmap
op_assign
id|default_exec_domain.signal_invmap
suffix:semicolon
id|register_exec_domain
c_func
(paren
op_amp
id|parisc32_exec_domain
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|parisc32_exec_init
id|__initcall
c_func
(paren
id|parisc32_exec_init
)paren
suffix:semicolon
eof
