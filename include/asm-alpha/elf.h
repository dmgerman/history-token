macro_line|#ifndef __ASM_ALPHA_ELF_H
DECL|macro|__ASM_ALPHA_ELF_H
mdefine_line|#define __ASM_ALPHA_ELF_H
multiline_comment|/*&n; * ELF register definitions..&n; */
multiline_comment|/*&n; * The OSF/1 version of &lt;sys/procfs.h&gt; makes gregset_t 46 entries long.&n; * I have no idea why that is so.  For now, we just leave it at 33&n; * (32 general regs + processor status word). &n; */
DECL|macro|ELF_NGREG
mdefine_line|#define ELF_NGREG&t;33
DECL|macro|ELF_NFPREG
mdefine_line|#define ELF_NFPREG&t;32
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
mdefine_line|#define elf_check_arch(x) ((x)-&gt;e_machine == EM_ALPHA)
multiline_comment|/*&n; * These are used to set parameters in the core dumps.&n; */
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS&t;ELFCLASS64
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;ELFDATA2LSB
DECL|macro|ELF_ARCH
mdefine_line|#define ELF_ARCH&t;EM_ALPHA
DECL|macro|USE_ELF_CORE_DUMP
mdefine_line|#define USE_ELF_CORE_DUMP
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE&t;8192
multiline_comment|/* This is the location that an ET_DYN program is loaded if exec&squot;ed.  Typical&n;   use of this is to invoke &quot;./ld.so someprog&quot; to test out a new version of&n;   the loader.  We need to make sure that it is out of the way of the program&n;   that it will &quot;exec&quot;, and that there is sufficient room for the brk.  */
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE&t;&t;(TASK_UNMAPPED_BASE + 0x1000000)
multiline_comment|/* $0 is set by ld.so to a pointer to a function which might be &n;   registered using atexit.  This provides a mean for the dynamic&n;   linker to call DT_FINI functions for shared libraries that have&n;   been loaded before the code runs.&n;&n;   So that we can use the same startup file with static executables,&n;   we start programs with a value of 0 to indicate that there is no&n;   such function.  */
DECL|macro|ELF_PLAT_INIT
mdefine_line|#define ELF_PLAT_INIT(_r)       _r-&gt;r0 = 0
multiline_comment|/* Use the same format as the OSF/1 procfs interface.  The register&n;   layout is sane.  However, since dump_thread() creates the funky&n;   layout that ECOFF coredumps want, we need to undo that layout here.&n;   Eventually, it would be nice if the ECOFF core-dump had to do the&n;   translation, then ELF_CORE_COPY_REGS() would become trivial and&n;   faster.  */
DECL|macro|ELF_CORE_COPY_REGS
mdefine_line|#define ELF_CORE_COPY_REGS(_dest,_regs)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct user _dump;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;dump_thread(_regs, &amp;_dump);&t;&t;&t;&t;&bslash;&n;&t;_dest[ 0] = _dump.regs[EF_V0];&t;&t;&t;&t;&bslash;&n;&t;_dest[ 1] = _dump.regs[EF_T0];&t;&t;&t;&t;&bslash;&n;&t;_dest[ 2] = _dump.regs[EF_T1];&t;&t;&t;&t;&bslash;&n;&t;_dest[ 3] = _dump.regs[EF_T2];&t;&t;&t;&t;&bslash;&n;&t;_dest[ 4] = _dump.regs[EF_T3];&t;&t;&t;&t;&bslash;&n;&t;_dest[ 5] = _dump.regs[EF_T4];&t;&t;&t;&t;&bslash;&n;&t;_dest[ 6] = _dump.regs[EF_T5];&t;&t;&t;&t;&bslash;&n;&t;_dest[ 7] = _dump.regs[EF_T6];&t;&t;&t;&t;&bslash;&n;&t;_dest[ 8] = _dump.regs[EF_T7];&t;&t;&t;&t;&bslash;&n;&t;_dest[ 9] = _dump.regs[EF_S0];&t;&t;&t;&t;&bslash;&n;&t;_dest[10] = _dump.regs[EF_S1];&t;&t;&t;&t;&bslash;&n;&t;_dest[11] = _dump.regs[EF_S2];&t;&t;&t;&t;&bslash;&n;&t;_dest[12] = _dump.regs[EF_S3];&t;&t;&t;&t;&bslash;&n;&t;_dest[13] = _dump.regs[EF_S4];&t;&t;&t;&t;&bslash;&n;&t;_dest[14] = _dump.regs[EF_S5];&t;&t;&t;&t;&bslash;&n;&t;_dest[15] = _dump.regs[EF_S6];&t;&t;&t;&t;&bslash;&n;&t;_dest[16] = _dump.regs[EF_A0];&t;&t;&t;&t;&bslash;&n;&t;_dest[17] = _dump.regs[EF_A1];&t;&t;&t;&t;&bslash;&n;&t;_dest[18] = _dump.regs[EF_A2];&t;&t;&t;&t;&bslash;&n;&t;_dest[19] = _dump.regs[EF_A3];&t;&t;&t;&t;&bslash;&n;&t;_dest[20] = _dump.regs[EF_A4];&t;&t;&t;&t;&bslash;&n;&t;_dest[21] = _dump.regs[EF_A5];&t;&t;&t;&t;&bslash;&n;&t;_dest[22] = _dump.regs[EF_T8];&t;&t;&t;&t;&bslash;&n;&t;_dest[23] = _dump.regs[EF_T9];&t;&t;&t;&t;&bslash;&n;&t;_dest[24] = _dump.regs[EF_T10];&t;&t;&t;&t;&bslash;&n;&t;_dest[25] = _dump.regs[EF_T11];&t;&t;&t;&t;&bslash;&n;&t;_dest[26] = _dump.regs[EF_RA];&t;&t;&t;&t;&bslash;&n;&t;_dest[27] = _dump.regs[EF_T12];&t;&t;&t;&t;&bslash;&n;&t;_dest[28] = _dump.regs[EF_AT];&t;&t;&t;&t;&bslash;&n;&t;_dest[29] = _dump.regs[EF_GP];&t;&t;&t;&t;&bslash;&n;&t;_dest[30] = _dump.regs[EF_SP];&t;&t;&t;&t;&bslash;&n;&t;_dest[31] = _dump.regs[EF_PC];&t;/* store PC here */&t;&bslash;&n;&t;_dest[32] = _dump.regs[EF_PS];&t;&t;&t;&t;&bslash;&n;}
multiline_comment|/* This yields a mask that user programs can use to figure out what&n;   instruction set this CPU supports.  This is trivial on Alpha, &n;   but not so on other machines. */
DECL|macro|ELF_HWCAP
mdefine_line|#define ELF_HWCAP&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;/* Sadly, most folks don&squot;t yet have assemblers that know about&t;&bslash;&n;&t;   amask.  This is &quot;amask v0, v0&quot; */&t;&t;&t;&t;&bslash;&n;&t;register long _v0 __asm(&quot;$0&quot;) = -1;&t;&t;&t;&t;&bslash;&n;&t;__asm(&quot;.long 0x47e00c20&quot; : &quot;=r&quot;(_v0) : &quot;0&quot;(_v0));&t;&t;&bslash;&n;&t;~_v0;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
multiline_comment|/* This yields a string that ld.so will use to load implementation&n;   specific libraries for optimization.  This is more specific in&n;   intent than poking at uname or /proc/cpuinfo.  &n;&n;   This might do with checking bwx simultaneously...  */
DECL|macro|ELF_PLATFORM
mdefine_line|#define ELF_PLATFORM&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&bslash;&n;&t;/* Or &quot;implver v0&quot; ... */&t;&t;&bslash;&n;&t;register long _v0 __asm(&quot;$0&quot;);&t;&t;&bslash;&n;&t;__asm(&quot;.long 0x47e03d80&quot; : &quot;=r&quot;(_v0));&t;&bslash;&n;&t;_v0 == 0 ? &quot;ev4&quot; : &quot;ev5&quot;;&t;&t;&bslash;&n;})
macro_line|#ifdef __KERNEL__
DECL|macro|SET_PERSONALITY
mdefine_line|#define SET_PERSONALITY(EX, IBCS2)&t;&t;&t;&t;&bslash;&n;&t;set_personality(((EX).e_flags &amp; EF_ALPHA_32BIT)&t;&t;&bslash;&n;&t;   ? PER_LINUX_32BIT : (IBCS2) ? PER_SVR4 : PER_LINUX)
macro_line|#endif
macro_line|#endif
eof
