macro_line|#ifndef __ASMi386_ELF_H
DECL|macro|__ASMi386_ELF_H
mdefine_line|#define __ASMi386_ELF_H
multiline_comment|/*&n; * ELF register definitions..&n; */
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/user.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
DECL|typedef|elf_greg_t
r_typedef
r_int
r_int
id|elf_greg_t
suffix:semicolon
DECL|macro|ELF_NGREG
mdefine_line|#define ELF_NGREG (sizeof (struct user_regs_struct) / sizeof(elf_greg_t))
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
id|user_i387_struct
id|elf_fpregset_t
suffix:semicolon
DECL|typedef|elf_fpxregset_t
r_typedef
r_struct
id|user_fxsr_struct
id|elf_fpxregset_t
suffix:semicolon
multiline_comment|/*&n; * This is used to ensure we don&squot;t load something for the wrong architecture.&n; */
DECL|macro|elf_check_arch
mdefine_line|#define elf_check_arch(x) &bslash;&n;&t;(((x)-&gt;e_machine == EM_386) || ((x)-&gt;e_machine == EM_486))
multiline_comment|/*&n; * These are used to set parameters in the core dumps.&n; */
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS&t;ELFCLASS32
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;ELFDATA2LSB
DECL|macro|ELF_ARCH
mdefine_line|#define ELF_ARCH&t;EM_386
multiline_comment|/* SVR4/i386 ABI (pages 3-31, 3-32) says that when the program starts %edx&n;   contains a pointer to a function which might be registered using `atexit&squot;.&n;   This provides a mean for the dynamic linker to call DT_FINI functions for&n;   shared libraries that have been loaded before the code runs.&n;&n;   A value of 0 tells we have no such handler. &n;&n;   We might as well make sure everything else is cleared too (except for %esp),&n;   just to make things more deterministic.&n; */
DECL|macro|ELF_PLAT_INIT
mdefine_line|#define ELF_PLAT_INIT(_r)&t;do { &bslash;&n;&t;_r-&gt;ebx = 0; _r-&gt;ecx = 0; _r-&gt;edx = 0; &bslash;&n;&t;_r-&gt;esi = 0; _r-&gt;edi = 0; _r-&gt;ebp = 0; &bslash;&n;&t;_r-&gt;eax = 0; &bslash;&n;} while (0)
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
mdefine_line|#define ELF_CORE_COPY_REGS(pr_reg, regs)&t;&t;&bslash;&n;&t;pr_reg[0] = regs-&gt;ebx;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[1] = regs-&gt;ecx;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[2] = regs-&gt;edx;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[3] = regs-&gt;esi;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[4] = regs-&gt;edi;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[5] = regs-&gt;ebp;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[6] = regs-&gt;eax;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[7] = regs-&gt;xds;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[8] = regs-&gt;xes;&t;&t;&t;&t;&bslash;&n;&t;/* fake once used fs and gs selectors? */&t;&bslash;&n;&t;pr_reg[9] = regs-&gt;xds;&t;/* was fs and __fs */&t;&bslash;&n;&t;pr_reg[10] = regs-&gt;xds;&t;/* was gs and __gs */&t;&bslash;&n;&t;pr_reg[11] = regs-&gt;orig_eax;&t;&t;&t;&bslash;&n;&t;pr_reg[12] = regs-&gt;eip;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[13] = regs-&gt;xcs;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[14] = regs-&gt;eflags;&t;&t;&t;&bslash;&n;&t;pr_reg[15] = regs-&gt;esp;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[16] = regs-&gt;xss;
multiline_comment|/* This yields a mask that user programs can use to figure out what&n;   instruction set this CPU supports.  This could be done in user space,&n;   but it&squot;s not easy, and we&squot;ve already done it here.  */
DECL|macro|ELF_HWCAP
mdefine_line|#define ELF_HWCAP&t;(boot_cpu_data.x86_capability[0])
multiline_comment|/* This yields a string that ld.so will use to load implementation&n;   specific libraries for optimization.  This is more specific in&n;   intent than poking at uname or /proc/cpuinfo.&n;&n;   For the moment, we have only optimizations for the Intel generations,&n;   but that could change... */
DECL|macro|ELF_PLATFORM
mdefine_line|#define ELF_PLATFORM  (system_utsname.machine)
macro_line|#ifdef __KERNEL__
DECL|macro|SET_PERSONALITY
mdefine_line|#define SET_PERSONALITY(ex, ibcs2) set_personality((ibcs2)?PER_SVR4:PER_LINUX)
macro_line|#endif
macro_line|#endif
eof
