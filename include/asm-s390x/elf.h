multiline_comment|/*&n; *  include/asm-s390/elf.h&n; *&n; *  S390 version&n; *&n; *  Derived from &quot;include/asm-i386/elf.h&quot;&n; */
macro_line|#ifndef __ASMS390_ELF_H
DECL|macro|__ASMS390_ELF_H
mdefine_line|#define __ASMS390_ELF_H
multiline_comment|/*&n; * ELF register definitions..&n; */
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/user.h&gt;
DECL|typedef|elf_fpregset_t
r_typedef
id|s390_fp_regs
id|elf_fpregset_t
suffix:semicolon
DECL|typedef|elf_gregset_t
r_typedef
id|s390_regs
id|elf_gregset_t
suffix:semicolon
multiline_comment|/*&n; * These are used to set parameters in the core dumps.&n; */
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS&t;ELFCLASS64
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;ELFDATA2MSB
DECL|macro|ELF_ARCH
mdefine_line|#define ELF_ARCH&t;EM_S390
multiline_comment|/*&n; * This is used to ensure we don&squot;t load something for the wrong architecture.&n; */
DECL|macro|elf_check_arch
mdefine_line|#define elf_check_arch(x) &bslash;&n;        ((x)-&gt;e_machine == ELF_ARCH &amp;&amp; (x)-&gt;e_ident[EI_CLASS] == ELF_CLASS)
multiline_comment|/* For SVR4/S390 the function pointer to be registered with `atexit` is&n;   passed in R14. */
DECL|macro|ELF_PLAT_INIT
mdefine_line|#define ELF_PLAT_INIT(_r) &bslash;&n;&t;do { &bslash;&n;&t;_r-&gt;gprs[14] = 0; &bslash;&n;&t;current-&gt;thread.flags = 0; &bslash;&n;&t;} while(0)
DECL|macro|USE_ELF_CORE_DUMP
mdefine_line|#define USE_ELF_CORE_DUMP
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE&t;4096
multiline_comment|/* This is the location that an ET_DYN program is loaded if exec&squot;ed.  Typical&n;   use of this is to invoke &quot;./ld.so someprog&quot; to test out a new version of&n;   the loader.  We need to make sure that it is out of the way of the program&n;   that it will &quot;exec&quot;, and that there is sufficient room for the brk.  */
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE         (TASK_SIZE / 3 * 2)
multiline_comment|/* Wow, the &quot;main&quot; arch needs arch dependent functions too.. :) */
multiline_comment|/* regs is struct pt_regs, pr_reg is elf_gregset_t (which is&n;   now struct_user_regs, they are different) */
DECL|macro|ELF_CORE_COPY_REGS
mdefine_line|#define ELF_CORE_COPY_REGS(pr_reg, regs)&t;&bslash;&n;&t;memcpy(&amp;pr_reg,regs,sizeof(elf_gregset_t)); &bslash;&n;
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
macro_line|#endif
eof
