macro_line|#ifndef __ASMPARISC_ELF_H
DECL|macro|__ASMPARISC_ELF_H
mdefine_line|#define __ASMPARISC_ELF_H
multiline_comment|/*&n; * ELF register definitions..&n; */
macro_line|#include &lt;asm/ptrace.h&gt;
DECL|macro|EM_PARISC
mdefine_line|#define EM_PARISC 15
DECL|macro|ELF_NGREG
mdefine_line|#define ELF_NGREG 32
DECL|macro|ELF_NFPREG
mdefine_line|#define ELF_NFPREG 32
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
DECL|macro|ELF_CORE_COPY_REGS
mdefine_line|#define ELF_CORE_COPY_REGS(gregs, regs) &bslash;&n;&t;memcpy(gregs, regs, &bslash;&n;&t;       sizeof(struct pt_regs) &lt; sizeof(elf_gregset_t)? &bslash;&n;&t;       sizeof(struct pt_regs): sizeof(elf_gregset_t));
multiline_comment|/*&n; * This is used to ensure we don&squot;t load something for the wrong architecture.&n; *&n; * Note that this header file is used by default in fs/binfmt_elf.c. So&n; * the following macros are for the default case. However, for the 64&n; * bit kernel we also support 32 bit parisc binaries. To do that&n; * arch/parisc64/kernel/binfmt_elf32.c defines its own set of these&n; * macros, and then if includes fs/binfmt_elf.c to provide an alternate&n; * elf binary handler for 32 bit binaries (on the 64 bit kernel).&n; */
macro_line|#ifdef __LP64__
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS       ELFCLASS64
macro_line|#else
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS&t;ELFCLASS32
macro_line|#endif
DECL|macro|elf_check_arch
mdefine_line|#define elf_check_arch(x) ((x)-&gt;e_machine == EM_PARISC &amp;&amp; (x)-&gt;e_ident[EI_CLASS] == ELF_CLASS)
multiline_comment|/*&n; * These are used to set parameters in the core dumps.&n; */
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;ELFDATA2MSB
DECL|macro|ELF_ARCH
mdefine_line|#define ELF_ARCH&t;EM_PARISC
multiline_comment|/* %r23 is set by ld.so to a pointer to a function which might be &n;   registered using atexit.  This provides a mean for the dynamic&n;   linker to call DT_FINI functions for shared libraries that have&n;   been loaded before the code runs.&n;&n;   So that we can use the same startup file with static executables,&n;   we start programs with a value of 0 to indicate that there is no&n;   such function.  */
DECL|macro|ELF_PLAT_INIT
mdefine_line|#define ELF_PLAT_INIT(_r)       _r-&gt;gr[23] = 0
DECL|macro|USE_ELF_CORE_DUMP
mdefine_line|#define USE_ELF_CORE_DUMP
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE&t;4096
multiline_comment|/* This is the location that an ET_DYN program is loaded if exec&squot;ed.  Typical&n;   use of this is to invoke &quot;./ld.so someprog&quot; to test out a new version of&n;   the loader.  We need to make sure that it is out of the way of the program&n;   that it will &quot;exec&quot;, and that there is sufficient room for the brk.&n;&n;   (2 * TASK_SIZE / 3) turns into something undefined when run through a&n;   32 bit preprocessor and in some cases results in the kernel trying to map&n;   ld.so to the kernel virtual base. Use a sane value instead. /Jes &n;  */
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE         (TASK_UNMAPPED_BASE + 0x01000000)
multiline_comment|/* This yields a mask that user programs can use to figure out what&n;   instruction set this CPU supports.  This could be done in user space,&n;   but it&squot;s not easy, and we&squot;ve already done it here.  */
DECL|macro|ELF_HWCAP
mdefine_line|#define ELF_HWCAP&t;0
multiline_comment|/* (boot_cpu_data.x86_capability) */
multiline_comment|/* This yields a string that ld.so will use to load implementation&n;   specific libraries for optimization.  This is more specific in&n;   intent than poking at uname or /proc/cpuinfo.&n;&n;   For the moment, we have only optimizations for the Intel generations,&n;   but that could change... */
DECL|macro|ELF_PLATFORM
mdefine_line|#define ELF_PLATFORM  (&quot;PARISC&bslash;0&quot; /*+((boot_cpu_data.x86-3)*5) */)
macro_line|#ifdef __KERNEL__
DECL|macro|SET_PERSONALITY
mdefine_line|#define SET_PERSONALITY(ex, ibcs2) &bslash;&n;&t;current-&gt;personality = PER_LINUX
macro_line|#endif
macro_line|#endif
eof
