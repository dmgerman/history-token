multiline_comment|/*&n; * Support for 32-bit Linux for S390 ELF binaries.&n; *&n; * Copyright (C) 2000 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; * Author(s): Gerhard Tonn (ton@de.ibm.com)&n; *&n; * Heavily inspired by the 32-bit Sparc compat code which is&n; * Copyright (C) 1995, 1996, 1997, 1998 David S. Miller (davem@redhat.com)&n; * Copyright (C) 1995, 1996, 1997, 1998 Jakub Jelinek   (jj@ultra.linux.cz)&n; */
DECL|macro|__ASMS390_ELF_H
mdefine_line|#define __ASMS390_ELF_H
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
DECL|macro|TASK31_SIZE
mdefine_line|#define TASK31_SIZE&t;&t;(0x80000000UL)
multiline_comment|/* For SVR4/S390 the function pointer to be registered with `atexit` is&n;   passed in R14. */
DECL|macro|ELF_PLAT_INIT
mdefine_line|#define ELF_PLAT_INIT(_r) &bslash;&n;&t;do { &bslash;&n;&t;_r-&gt;gprs[14] = 0; &bslash;&n;&t;current-&gt;thread.flags |= S390_FLAG_31BIT; &bslash;&n;&t;} while(0)
DECL|macro|USE_ELF_CORE_DUMP
mdefine_line|#define USE_ELF_CORE_DUMP
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE       4096
multiline_comment|/* This is the location that an ET_DYN program is loaded if exec&squot;ed.  Typical&n;   use of this is to invoke &quot;./ld.so someprog&quot; to test out a new version of&n;   the loader.  We need to make sure that it is out of the way of the program&n;   that it will &quot;exec&quot;, and that there is sufficient room for the brk.  */
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE         ((TASK31_SIZE &amp; 0x80000000) &bslash;&n;                                ? TASK31_SIZE / 3 * 2 &bslash;&n;                                : 2 * TASK31_SIZE / 3)     
multiline_comment|/* Wow, the &quot;main&quot; arch needs arch dependent functions too.. :) */
multiline_comment|/* regs is struct pt_regs, pr_reg is elf_gregset_t (which is&n;   now struct_user_regs, they are different) */
DECL|macro|ELF_CORE_COPY_REGS
mdefine_line|#define ELF_CORE_COPY_REGS(pr_reg, regs)        &bslash;&n;&t;{ &bslash;&n;&t;int i; &bslash;&n;&t;memcpy(&amp;pr_reg.psw.mask, &amp;regs-&gt;psw.mask, 4); &bslash;&n;&t;memcpy(&amp;pr_reg.psw.addr, ((char*)&amp;regs-&gt;psw.addr)+4, 4); &bslash;&n;&t;for(i=0; i&lt;NUM_GPRS; i++) &bslash;&n;&t;&t;pr_reg.gprs[i] = regs-&gt;gprs[i]; &bslash;&n;&t;for(i=0; i&lt;NUM_ACRS; i++) &bslash;&n;&t;&t;pr_reg.acrs[i] = regs-&gt;acrs[i]; &bslash;&n;&t;pr_reg.orig_gpr2 = regs-&gt;orig_gpr2; &bslash;&n;&t;}
multiline_comment|/* This yields a mask that user programs can use to figure out what&n;   instruction set this CPU supports. */
DECL|macro|ELF_HWCAP
mdefine_line|#define ELF_HWCAP (0)
multiline_comment|/* This yields a string that ld.so will use to load implementation&n;   specific libraries for optimization.  This is more specific in&n;   intent than poking at uname or /proc/cpuinfo.&n;&n;   For the moment, we have only optimizations for the Intel generations,&n;   but that could change... */
DECL|macro|ELF_PLATFORM
mdefine_line|#define ELF_PLATFORM (NULL)
macro_line|#ifdef __KERNEL__
DECL|macro|SET_PERSONALITY
mdefine_line|#define SET_PERSONALITY(ex, ibcs2) set_personality((ibcs2)?PER_SVR4:PER_LINUX)
macro_line|#endif 
macro_line|#include &quot;linux32.h&quot;
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
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/elfcore.h&gt;
r_int
id|setup_arg_pages32
c_func
(paren
r_struct
id|linux_binprm
op_star
id|bprm
)paren
suffix:semicolon
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
DECL|macro|elf_caddr_t
mdefine_line|#define elf_caddr_t&t;u32
multiline_comment|/*&n;#define init_elf_binfmt init_elf32_binfmt&n;*/
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
DECL|macro|start_thread
macro_line|#undef start_thread
DECL|macro|start_thread
mdefine_line|#define start_thread                    start_thread31 
DECL|macro|setup_arg_pages
mdefine_line|#define setup_arg_pages(bprm)           setup_arg_pages32(bprm)
DECL|macro|elf_map
mdefine_line|#define elf_map&t;&t;&t;&t;elf_map32
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
macro_line|#include &quot;../../../fs/binfmt_elf.c&quot;
r_static
r_int
r_int
DECL|function|elf_map32
id|elf_map32
(paren
r_struct
id|file
op_star
id|filep
comma
r_int
r_int
id|addr
comma
r_struct
id|elf_phdr
op_star
id|eppnt
comma
r_int
id|prot
comma
r_int
id|type
)paren
(brace
r_int
r_int
id|map_addr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|addr
)paren
(brace
id|addr
op_assign
l_int|0x40000000
suffix:semicolon
)brace
id|down_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|map_addr
op_assign
id|do_mmap
c_func
(paren
id|filep
comma
id|ELF_PAGESTART
c_func
(paren
id|addr
)paren
comma
id|eppnt-&gt;p_filesz
op_plus
id|ELF_PAGEOFFSET
c_func
(paren
id|eppnt-&gt;p_vaddr
)paren
comma
id|prot
comma
id|type
comma
id|eppnt-&gt;p_offset
op_minus
id|ELF_PAGEOFFSET
c_func
(paren
id|eppnt-&gt;p_vaddr
)paren
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
r_return
id|map_addr
suffix:semicolon
)brace
eof
