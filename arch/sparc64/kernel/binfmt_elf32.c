multiline_comment|/*&n; * binfmt_elf32.c: Support 32-bit Sparc ELF binaries on Ultra.&n; *&n; * Copyright (C) 1995, 1996, 1997, 1998 David S. Miller&t;(davem@redhat.com)&n; * Copyright (C) 1995, 1996, 1997, 1998 Jakub Jelinek&t;(jj@ultra.linux.cz)&n; */
DECL|macro|ELF_ARCH
mdefine_line|#define ELF_ARCH&t;&t;EM_SPARC
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS&t;&t;ELFCLASS32
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;&t;ELFDATA2MSB;
multiline_comment|/* For the most part we present code dumps in the format&n; * Solaris does.&n; */
DECL|typedef|elf_greg_t
r_typedef
r_int
r_int
id|elf_greg_t
suffix:semicolon
DECL|macro|ELF_NGREG
mdefine_line|#define ELF_NGREG 38
DECL|typedef|elf_gregset_t
r_typedef
id|elf_greg_t
id|elf_gregset_t
(braket
id|ELF_NGREG
)braket
suffix:semicolon
multiline_comment|/* Format is:&n; * &t;G0 --&gt; G7&n; *&t;O0 --&gt; O7&n; *&t;L0 --&gt; L7&n; *&t;I0 --&gt; I7&n; *&t;PSR, PC, nPC, Y, WIM, TBR&n; */
macro_line|#include &lt;asm/psrcompat.h&gt;
DECL|macro|ELF_CORE_COPY_REGS
mdefine_line|#define ELF_CORE_COPY_REGS(__elf_regs, __pt_regs)&t;&bslash;&n;do {&t;unsigned int *dest = &amp;(__elf_regs[0]);&t;&t;&bslash;&n;&t;struct pt_regs *src = (__pt_regs);&t;&t;&bslash;&n;&t;unsigned int *sp;&t;&t;&t;&t;&bslash;&n;&t;int i;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;for(i = 0; i &lt; 16; i++)&t;&t;&t;&t;&bslash;&n;&t;&t;dest[i] = (unsigned int) src-&gt;u_regs[i];&bslash;&n;&t;/* Don&squot;t try this at home kids... */&t;&t;&bslash;&n;&t;set_fs(USER_DS);&t;&t;&t;&t;&bslash;&n;&t;sp = (unsigned int *) (src-&gt;u_regs[14] &amp;&t;&bslash;&n;&t;&t;0x00000000fffffffc);&t;&t;&t;&bslash;&n;&t;for(i = 0; i &lt; 16; i++)&t;&t;&t;&t;&bslash;&n;&t;&t;__get_user(dest[i+16], &amp;sp[i]);&t;&t;&bslash;&n;&t;set_fs(KERNEL_DS);&t;&t;&t;&t;&bslash;&n;&t;dest[32] = tstate_to_psr(src-&gt;tstate);&t;&t;&bslash;&n;&t;dest[33] = (unsigned int) src-&gt;tpc;&t;&t;&bslash;&n;&t;dest[34] = (unsigned int) src-&gt;tnpc;&t;&t;&bslash;&n;&t;dest[35] = src-&gt;y;&t;&t;&t;&t;&bslash;&n;&t;dest[36] = dest[37] = 0; /* XXX */&t;&t;&bslash;&n;} while(0)
r_typedef
r_struct
(brace
r_union
(brace
DECL|member|pr_regs
r_int
r_int
id|pr_regs
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|pr_dregs
r_int
r_int
id|pr_dregs
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|pr_fr
)brace
id|pr_fr
suffix:semicolon
DECL|member|__unused
r_int
r_int
id|__unused
suffix:semicolon
DECL|member|pr_fsr
r_int
r_int
id|pr_fsr
suffix:semicolon
DECL|member|pr_qcnt
r_int
r_char
id|pr_qcnt
suffix:semicolon
DECL|member|pr_q_entrysize
r_int
r_char
id|pr_q_entrysize
suffix:semicolon
DECL|member|pr_en
r_int
r_char
id|pr_en
suffix:semicolon
DECL|member|pr_q
r_int
r_int
id|pr_q
(braket
l_int|64
)braket
suffix:semicolon
DECL|typedef|elf_fpregset_t
)brace
id|elf_fpregset_t
suffix:semicolon
multiline_comment|/* UltraSparc extensions.  Still unused, but will be eventually.  */
r_typedef
r_struct
(brace
DECL|member|pr_type
r_int
r_int
id|pr_type
suffix:semicolon
DECL|member|pr_align
r_int
r_int
id|pr_align
suffix:semicolon
r_union
(brace
r_struct
(brace
r_union
(brace
DECL|member|pr_regs
r_int
r_int
id|pr_regs
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|pr_dregs
r_int
r_int
id|pr_dregs
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|pr_qregs
r_int
r_float
id|pr_qregs
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|pr_xfr
)brace
id|pr_xfr
suffix:semicolon
DECL|member|pr_v8p
)brace
id|pr_v8p
suffix:semicolon
DECL|member|pr_xfsr
r_int
r_int
id|pr_xfsr
suffix:semicolon
DECL|member|pr_fprs
r_int
r_int
id|pr_fprs
suffix:semicolon
DECL|member|pr_xg
r_int
r_int
id|pr_xg
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|pr_xo
r_int
r_int
id|pr_xo
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|pr_tstate
r_int
r_int
id|pr_tstate
suffix:semicolon
DECL|member|pr_filler
r_int
r_int
id|pr_filler
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|pr_un
)brace
id|pr_un
suffix:semicolon
DECL|typedef|elf_xregset_t
)brace
id|elf_xregset_t
suffix:semicolon
DECL|macro|elf_check_arch
mdefine_line|#define elf_check_arch(x)&t;(((x)-&gt;e_machine == EM_SPARC) || ((x)-&gt;e_machine == EM_SPARC32PLUS))
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE         0x08000000
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/elfcore.h&gt;
DECL|struct|timeval32
r_struct
id|timeval32
(brace
DECL|member|tv_sec
DECL|member|tv_usec
r_int
id|tv_sec
comma
id|tv_usec
suffix:semicolon
)brace
suffix:semicolon
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
id|timeval32
id|pr_utime
suffix:semicolon
multiline_comment|/* User time */
DECL|member|pr_stime
r_struct
id|timeval32
id|pr_stime
suffix:semicolon
multiline_comment|/* System time */
DECL|member|pr_cutime
r_struct
id|timeval32
id|pr_cutime
suffix:semicolon
multiline_comment|/* Cumulative user time */
DECL|member|pr_cstime
r_struct
id|timeval32
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
DECL|macro|elf_caddr_t
mdefine_line|#define elf_caddr_t&t;u32
DECL|macro|start_thread
macro_line|#undef start_thread
DECL|macro|start_thread
mdefine_line|#define start_thread start_thread32
DECL|macro|init_elf_binfmt
mdefine_line|#define init_elf_binfmt init_elf32_binfmt
DECL|macro|CONFIG_BINFMT_ELF
macro_line|#undef CONFIG_BINFMT_ELF
macro_line|#ifdef CONFIG_BINFMT_ELF32
DECL|macro|CONFIG_BINFMT_ELF
mdefine_line|#define CONFIG_BINFMT_ELF CONFIG_BINFMT_ELF32
macro_line|#endif
DECL|macro|CONFIG_BINFMT_ELF_MODULE
macro_line|#undef CONFIG_BINFMT_ELF_MODULE
macro_line|#ifdef CONFIG_BINFMT_ELF32_MODULE
DECL|macro|CONFIG_BINFMT_ELF_MODULE
mdefine_line|#define CONFIG_BINFMT_ELF_MODULE CONFIG_BINFMT_ELF32_MODULE
macro_line|#endif
DECL|macro|ELF_FLAGS_INIT
mdefine_line|#define ELF_FLAGS_INIT&t;set_thread_flag(TIF_32BIT)
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Binary format loader for compatibility with 32bit SparcLinux binaries on the Ultra&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Eric Youngdale, David S. Miller, Jakub Jelinek&quot;
)paren
suffix:semicolon
DECL|macro|MODULE_DESCRIPTION
macro_line|#undef MODULE_DESCRIPTION
DECL|macro|MODULE_AUTHOR
macro_line|#undef MODULE_AUTHOR
macro_line|#include &quot;../../../fs/binfmt_elf.c&quot;
eof
