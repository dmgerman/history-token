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
multiline_comment|/* The registers are layed out in pt_regs for PAL and syscall&n;   convenience.  Re-order them for the linear elf_gregset_t.  */
r_extern
r_void
id|dump_elf_thread
c_func
(paren
id|elf_greg_t
op_star
id|dest
comma
r_struct
id|pt_regs
op_star
id|pt
comma
r_struct
id|thread_info
op_star
id|ti
)paren
suffix:semicolon
DECL|macro|ELF_CORE_COPY_REGS
mdefine_line|#define ELF_CORE_COPY_REGS(DEST, REGS) &bslash;&n;&t;dump_elf_thread(DEST, REGS, current_thread_info());
multiline_comment|/* Similar, but for a thread other than current.  */
r_extern
r_int
id|dump_elf_task
c_func
(paren
id|elf_greg_t
op_star
id|dest
comma
r_struct
id|task_struct
op_star
id|task
)paren
suffix:semicolon
DECL|macro|ELF_CORE_COPY_TASK_REGS
mdefine_line|#define ELF_CORE_COPY_TASK_REGS(TASK, DEST) &bslash;&n;&t;dump_elf_task(*(DEST), TASK)
multiline_comment|/* Similar, but for the FP registers.  */
r_extern
r_int
id|dump_elf_task_fp
c_func
(paren
id|elf_fpreg_t
op_star
id|dest
comma
r_struct
id|task_struct
op_star
id|task
)paren
suffix:semicolon
DECL|macro|ELF_CORE_COPY_FPREGS
mdefine_line|#define ELF_CORE_COPY_FPREGS(TASK, DEST) &bslash;&n;&t;dump_elf_task_fp(*(DEST), TASK)
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
