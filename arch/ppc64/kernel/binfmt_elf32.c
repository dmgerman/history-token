multiline_comment|/*&n; * binfmt_elf32.c: Support 32-bit PPC ELF binaries on Power3 and followons.&n; * based on the SPARC64 version.&n; * Copyright (C) 1995, 1996, 1997, 1998 David S. Miller&t;(davem@redhat.com)&n; * Copyright (C) 1995, 1996, 1997, 1998 Jakub Jelinek&t;(jj@ultra.linux.cz)&n; *&n; * Copyright (C) 2000,2001 Ken Aaker (kdaaker@rchland.vnet.ibm.com), IBM Corp&n; * Copyright (C) 2001 Anton Blanchard (anton@au.ibm.com), IBM&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
DECL|macro|ELF_ARCH
mdefine_line|#define ELF_ARCH&t;&t;EM_PPC
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS&t;&t;ELFCLASS32
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;&t;ELFDATA2MSB;
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
multiline_comment|/* General purpose registers. */
DECL|member|pr_fpvalid
r_int
id|pr_fpvalid
suffix:semicolon
multiline_comment|/* True if math co-processor being used. */
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
id|u32
id|pr_uid
suffix:semicolon
DECL|member|pr_gid
id|u32
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
macro_line|#include &lt;linux/time.h&gt;
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
r_extern
r_void
id|start_thread32
c_func
(paren
r_struct
id|pt_regs
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|macro|start_thread
macro_line|#undef start_thread
DECL|macro|start_thread
mdefine_line|#define start_thread start_thread32
DECL|macro|init_elf_binfmt
mdefine_line|#define init_elf_binfmt init_elf32_binfmt
macro_line|#include &quot;../../../fs/binfmt_elf.c&quot;
eof
