macro_line|#ifndef __ASMCRIS_ELF_H
DECL|macro|__ASMCRIS_ELF_H
mdefine_line|#define __ASMCRIS_ELF_H
multiline_comment|/*&n; * ELF register definitions..&n; */
macro_line|#include &lt;asm/ptrace.h&gt;
DECL|typedef|elf_greg_t
r_typedef
r_int
r_int
id|elf_greg_t
suffix:semicolon
multiline_comment|/* These probably need fixing.  */
DECL|macro|ELF_NGREG
mdefine_line|#define ELF_NGREG (sizeof (struct pt_regs) / sizeof(elf_greg_t))
DECL|typedef|elf_gregset_t
r_typedef
id|elf_greg_t
id|elf_gregset_t
(braket
id|ELF_NGREG
)braket
suffix:semicolon
multiline_comment|/* A placeholder; CRIS does not have any fp regs.  */
DECL|typedef|elf_fpregset_t
r_typedef
r_int
r_int
id|elf_fpregset_t
suffix:semicolon
multiline_comment|/*&n; * This is used to ensure we don&squot;t load something for the wrong architecture.&n; */
DECL|macro|elf_check_arch
mdefine_line|#define elf_check_arch(x) ( (x)-&gt;e_machine == EM_CRIS )
multiline_comment|/*&n; * These are used to set parameters in the core dumps.&n; */
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS&t;ELFCLASS32
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;ELFDATA2LSB;
DECL|macro|ELF_ARCH
mdefine_line|#define ELF_ARCH&t;EM_CRIS
multiline_comment|/* SVR4/i386 ABI (pages 3-31, 3-32) says that when the program&n;&t;   starts (a register; assume first param register for CRIS)&n;&t;   contains a pointer to a function which might be&n;&t;   registered using `atexit&squot;.  This provides a mean for the&n;&t;   dynamic linker to call DT_FINI functions for shared libraries&n;&t;   that have been loaded before the code runs.&n;&n;&t;   A value of 0 tells we have no such handler.  */
DECL|macro|ELF_PLAT_INIT
mdefine_line|#define ELF_PLAT_INIT(_r)&t;((_r)-&gt;r10 = 0)
DECL|macro|USE_ELF_CORE_DUMP
macro_line|#undef USE_ELF_CORE_DUMP
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE&t;8192
multiline_comment|/* This is the location that an ET_DYN program is loaded if exec&squot;ed.  Typical&n;   use of this is to invoke &quot;./ld.so someprog&quot; to test out a new version of&n;   the loader.  We need to make sure that it is out of the way of the program&n;   that it will &quot;exec&quot;, and that there is sufficient room for the brk.  */
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE         (2 * TASK_SIZE / 3)
multiline_comment|/* This yields a mask that user programs can use to figure out what&n;   instruction set this CPU supports.  This could be done in user space,&n;   but it&squot;s not easy, and we&squot;ve already done it here.  */
DECL|macro|ELF_HWCAP
mdefine_line|#define ELF_HWCAP       (0)
multiline_comment|/* This yields a string that ld.so will use to load implementation&n;   specific libraries for optimization.  This is more specific in&n;   intent than poking at uname or /proc/cpuinfo.&n;*/
DECL|macro|ELF_PLATFORM
mdefine_line|#define ELF_PLATFORM  (NULL)
macro_line|#ifdef __KERNEL__
DECL|macro|SET_PERSONALITY
mdefine_line|#define SET_PERSONALITY(ex, ibcs2) set_personality((ibcs2)?PER_SVR4:PER_LINUX)
macro_line|#endif
macro_line|#endif
eof
