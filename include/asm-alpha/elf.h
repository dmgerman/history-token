macro_line|#ifndef __ASM_ALPHA_ELF_H
DECL|macro|__ASM_ALPHA_ELF_H
mdefine_line|#define __ASM_ALPHA_ELF_H
multiline_comment|/*&n; * Alpha ELF relocation types&n; */
DECL|macro|R_ALPHA_NONE
mdefine_line|#define R_ALPHA_NONE            0       /* No reloc */
DECL|macro|R_ALPHA_REFLONG
mdefine_line|#define R_ALPHA_REFLONG         1       /* Direct 32 bit */
DECL|macro|R_ALPHA_REFQUAD
mdefine_line|#define R_ALPHA_REFQUAD         2       /* Direct 64 bit */
DECL|macro|R_ALPHA_GPREL32
mdefine_line|#define R_ALPHA_GPREL32         3       /* GP relative 32 bit */
DECL|macro|R_ALPHA_LITERAL
mdefine_line|#define R_ALPHA_LITERAL         4       /* GP relative 16 bit w/optimization */
DECL|macro|R_ALPHA_LITUSE
mdefine_line|#define R_ALPHA_LITUSE          5       /* Optimization hint for LITERAL */
DECL|macro|R_ALPHA_GPDISP
mdefine_line|#define R_ALPHA_GPDISP          6       /* Add displacement to GP */
DECL|macro|R_ALPHA_BRADDR
mdefine_line|#define R_ALPHA_BRADDR          7       /* PC+4 relative 23 bit shifted */
DECL|macro|R_ALPHA_HINT
mdefine_line|#define R_ALPHA_HINT            8       /* PC+4 relative 16 bit shifted */
DECL|macro|R_ALPHA_SREL16
mdefine_line|#define R_ALPHA_SREL16          9       /* PC relative 16 bit */
DECL|macro|R_ALPHA_SREL32
mdefine_line|#define R_ALPHA_SREL32          10      /* PC relative 32 bit */
DECL|macro|R_ALPHA_SREL64
mdefine_line|#define R_ALPHA_SREL64          11      /* PC relative 64 bit */
DECL|macro|R_ALPHA_GPRELHIGH
mdefine_line|#define R_ALPHA_GPRELHIGH       17      /* GP relative 32 bit, high 16 bits */
DECL|macro|R_ALPHA_GPRELLOW
mdefine_line|#define R_ALPHA_GPRELLOW        18      /* GP relative 32 bit, low 16 bits */
DECL|macro|R_ALPHA_GPREL16
mdefine_line|#define R_ALPHA_GPREL16         19      /* GP relative 16 bit */
DECL|macro|R_ALPHA_COPY
mdefine_line|#define R_ALPHA_COPY            24      /* Copy symbol at runtime */
DECL|macro|R_ALPHA_GLOB_DAT
mdefine_line|#define R_ALPHA_GLOB_DAT        25      /* Create GOT entry */
DECL|macro|R_ALPHA_JMP_SLOT
mdefine_line|#define R_ALPHA_JMP_SLOT        26      /* Create PLT entry */
DECL|macro|R_ALPHA_RELATIVE
mdefine_line|#define R_ALPHA_RELATIVE        27      /* Adjust by program base */
DECL|macro|R_ALPHA_BRSGP
mdefine_line|#define R_ALPHA_BRSGP&t;&t;28
DECL|macro|R_ALPHA_TLSGD
mdefine_line|#define R_ALPHA_TLSGD           29
DECL|macro|R_ALPHA_TLS_LDM
mdefine_line|#define R_ALPHA_TLS_LDM         30
DECL|macro|R_ALPHA_DTPMOD64
mdefine_line|#define R_ALPHA_DTPMOD64        31
DECL|macro|R_ALPHA_GOTDTPREL
mdefine_line|#define R_ALPHA_GOTDTPREL       32
DECL|macro|R_ALPHA_DTPREL64
mdefine_line|#define R_ALPHA_DTPREL64        33
DECL|macro|R_ALPHA_DTPRELHI
mdefine_line|#define R_ALPHA_DTPRELHI        34
DECL|macro|R_ALPHA_DTPRELLO
mdefine_line|#define R_ALPHA_DTPRELLO        35
DECL|macro|R_ALPHA_DTPREL16
mdefine_line|#define R_ALPHA_DTPREL16        36
DECL|macro|R_ALPHA_GOTTPREL
mdefine_line|#define R_ALPHA_GOTTPREL        37
DECL|macro|R_ALPHA_TPREL64
mdefine_line|#define R_ALPHA_TPREL64         38
DECL|macro|R_ALPHA_TPRELHI
mdefine_line|#define R_ALPHA_TPRELHI         39
DECL|macro|R_ALPHA_TPRELLO
mdefine_line|#define R_ALPHA_TPRELLO         40
DECL|macro|R_ALPHA_TPREL16
mdefine_line|#define R_ALPHA_TPREL16         41
DECL|macro|SHF_ALPHA_GPREL
mdefine_line|#define SHF_ALPHA_GPREL&t;&t;0x10000000
multiline_comment|/* Legal values for e_flags field of Elf64_Ehdr.  */
DECL|macro|EF_ALPHA_32BIT
mdefine_line|#define EF_ALPHA_32BIT&t;&t;1&t;/* All addresses are below 2GB */
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
mdefine_line|#define ELF_PLAT_INIT(_r, load_addr)&t;_r-&gt;r0 = 0
multiline_comment|/* The registers are layed out in pt_regs for PAL and syscall&n;   convenience.  Re-order them for the linear elf_gregset_t.  */
r_struct
id|pt_regs
suffix:semicolon
r_struct
id|thread_info
suffix:semicolon
r_struct
id|task_struct
suffix:semicolon
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
