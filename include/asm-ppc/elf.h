macro_line|#ifndef __PPC_ELF_H
DECL|macro|__PPC_ELF_H
mdefine_line|#define __PPC_ELF_H
multiline_comment|/*&n; * ELF register definitions..&n; */
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/cputable.h&gt;
multiline_comment|/* PowerPC relocations defined by the ABIs */
DECL|macro|R_PPC_NONE
mdefine_line|#define R_PPC_NONE&t;&t;0
DECL|macro|R_PPC_ADDR32
mdefine_line|#define R_PPC_ADDR32&t;&t;1&t;/* 32bit absolute address */
DECL|macro|R_PPC_ADDR24
mdefine_line|#define R_PPC_ADDR24&t;&t;2&t;/* 26bit address, 2 bits ignored.  */
DECL|macro|R_PPC_ADDR16
mdefine_line|#define R_PPC_ADDR16&t;&t;3&t;/* 16bit absolute address */
DECL|macro|R_PPC_ADDR16_LO
mdefine_line|#define R_PPC_ADDR16_LO&t;&t;4&t;/* lower 16bit of absolute address */
DECL|macro|R_PPC_ADDR16_HI
mdefine_line|#define R_PPC_ADDR16_HI&t;&t;5&t;/* high 16bit of absolute address */
DECL|macro|R_PPC_ADDR16_HA
mdefine_line|#define R_PPC_ADDR16_HA&t;&t;6&t;/* adjusted high 16bit */
DECL|macro|R_PPC_ADDR14
mdefine_line|#define R_PPC_ADDR14&t;&t;7&t;/* 16bit address, 2 bits ignored */
DECL|macro|R_PPC_ADDR14_BRTAKEN
mdefine_line|#define R_PPC_ADDR14_BRTAKEN&t;8
DECL|macro|R_PPC_ADDR14_BRNTAKEN
mdefine_line|#define R_PPC_ADDR14_BRNTAKEN&t;9
DECL|macro|R_PPC_REL24
mdefine_line|#define R_PPC_REL24&t;&t;10&t;/* PC relative 26 bit */
DECL|macro|R_PPC_REL14
mdefine_line|#define R_PPC_REL14&t;&t;11&t;/* PC relative 16 bit */
DECL|macro|R_PPC_REL14_BRTAKEN
mdefine_line|#define R_PPC_REL14_BRTAKEN&t;12
DECL|macro|R_PPC_REL14_BRNTAKEN
mdefine_line|#define R_PPC_REL14_BRNTAKEN&t;13
DECL|macro|R_PPC_GOT16
mdefine_line|#define R_PPC_GOT16&t;&t;14
DECL|macro|R_PPC_GOT16_LO
mdefine_line|#define R_PPC_GOT16_LO&t;&t;15
DECL|macro|R_PPC_GOT16_HI
mdefine_line|#define R_PPC_GOT16_HI&t;&t;16
DECL|macro|R_PPC_GOT16_HA
mdefine_line|#define R_PPC_GOT16_HA&t;&t;17
DECL|macro|R_PPC_PLTREL24
mdefine_line|#define R_PPC_PLTREL24&t;&t;18
DECL|macro|R_PPC_COPY
mdefine_line|#define R_PPC_COPY&t;&t;19
DECL|macro|R_PPC_GLOB_DAT
mdefine_line|#define R_PPC_GLOB_DAT&t;&t;20
DECL|macro|R_PPC_JMP_SLOT
mdefine_line|#define R_PPC_JMP_SLOT&t;&t;21
DECL|macro|R_PPC_RELATIVE
mdefine_line|#define R_PPC_RELATIVE&t;&t;22
DECL|macro|R_PPC_LOCAL24PC
mdefine_line|#define R_PPC_LOCAL24PC&t;&t;23
DECL|macro|R_PPC_UADDR32
mdefine_line|#define R_PPC_UADDR32&t;&t;24
DECL|macro|R_PPC_UADDR16
mdefine_line|#define R_PPC_UADDR16&t;&t;25
DECL|macro|R_PPC_REL32
mdefine_line|#define R_PPC_REL32&t;&t;26
DECL|macro|R_PPC_PLT32
mdefine_line|#define R_PPC_PLT32&t;&t;27
DECL|macro|R_PPC_PLTREL32
mdefine_line|#define R_PPC_PLTREL32&t;&t;28
DECL|macro|R_PPC_PLT16_LO
mdefine_line|#define R_PPC_PLT16_LO&t;&t;29
DECL|macro|R_PPC_PLT16_HI
mdefine_line|#define R_PPC_PLT16_HI&t;&t;30
DECL|macro|R_PPC_PLT16_HA
mdefine_line|#define R_PPC_PLT16_HA&t;&t;31
DECL|macro|R_PPC_SDAREL16
mdefine_line|#define R_PPC_SDAREL16&t;&t;32
DECL|macro|R_PPC_SECTOFF
mdefine_line|#define R_PPC_SECTOFF&t;&t;33
DECL|macro|R_PPC_SECTOFF_LO
mdefine_line|#define R_PPC_SECTOFF_LO&t;34
DECL|macro|R_PPC_SECTOFF_HI
mdefine_line|#define R_PPC_SECTOFF_HI&t;35
DECL|macro|R_PPC_SECTOFF_HA
mdefine_line|#define R_PPC_SECTOFF_HA&t;36
multiline_comment|/* Keep this the last entry.  */
DECL|macro|R_PPC_NUM
mdefine_line|#define R_PPC_NUM&t;&t;37
DECL|macro|ELF_NGREG
mdefine_line|#define ELF_NGREG&t;48&t;/* includes nip, msr, lr, etc. */
DECL|macro|ELF_NFPREG
mdefine_line|#define ELF_NFPREG&t;33&t;/* includes fpscr */
DECL|macro|ELF_NVRREG
mdefine_line|#define ELF_NVRREG&t;33&t;/* includes vscr */
DECL|macro|ELF_NEVRREG
mdefine_line|#define ELF_NEVRREG&t;34&t;/* includes acc (as 2) */
multiline_comment|/*&n; * These are used to set parameters in the core dumps.&n; */
DECL|macro|ELF_ARCH
mdefine_line|#define ELF_ARCH&t;EM_PPC
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS&t;ELFCLASS32
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;ELFDATA2MSB
multiline_comment|/* General registers */
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
multiline_comment|/* Floating point registers */
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
multiline_comment|/* Altivec registers */
DECL|typedef|elf_vrreg_t
r_typedef
id|__vector128
id|elf_vrreg_t
suffix:semicolon
DECL|typedef|elf_vrregset_t
r_typedef
id|elf_vrreg_t
id|elf_vrregset_t
(braket
id|ELF_NVRREG
)braket
suffix:semicolon
macro_line|#ifdef __KERNEL__
r_struct
id|task_struct
suffix:semicolon
multiline_comment|/*&n; * This is used to ensure we don&squot;t load something for the wrong architecture.&n; */
DECL|macro|elf_check_arch
mdefine_line|#define elf_check_arch(x) ((x)-&gt;e_machine == EM_PPC)
multiline_comment|/* This is the location that an ET_DYN program is loaded if exec&squot;ed.  Typical&n;   use of this is to invoke &quot;./ld.so someprog&quot; to test out a new version of&n;   the loader.  We need to make sure that it is out of the way of the program&n;   that it will &quot;exec&quot;, and that there is sufficient room for the brk.  */
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE         (0x08000000)
DECL|macro|USE_ELF_CORE_DUMP
mdefine_line|#define USE_ELF_CORE_DUMP
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE&t;4096
DECL|macro|ELF_CORE_COPY_REGS
mdefine_line|#define ELF_CORE_COPY_REGS(gregs, regs)&t;&t;&t;&t;&bslash;&n;&t;memcpy((gregs), (regs), sizeof(struct pt_regs));&t;&bslash;&n;&t;memset((char *)(gregs) + sizeof(struct pt_regs), 0,&t;&bslash;&n;&t;       sizeof(elf_gregset_t) - sizeof(struct pt_regs));
DECL|macro|ELF_CORE_COPY_TASK_REGS
mdefine_line|#define ELF_CORE_COPY_TASK_REGS(t, elfregs)&t;&t;&t;&bslash;&n;&t;((t)-&gt;thread.regs?&t;&t;&t;&t;&t;&bslash;&n;&t; ({ ELF_CORE_COPY_REGS((elfregs), (t)-&gt;thread.regs); 1; }): 0)
r_extern
r_int
id|dump_task_fpu
c_func
(paren
r_struct
id|task_struct
op_star
id|t
comma
id|elf_fpregset_t
op_star
id|fpu
)paren
suffix:semicolon
DECL|macro|ELF_CORE_COPY_FPREGS
mdefine_line|#define ELF_CORE_COPY_FPREGS(t, fpu)&t;dump_task_fpu((t), (fpu))
multiline_comment|/* This yields a mask that user programs can use to figure out what&n;   instruction set this cpu supports.  This could be done in userspace,&n;   but it&squot;s not easy, and we&squot;ve already done it here.  */
DECL|macro|ELF_HWCAP
mdefine_line|#define ELF_HWCAP&t;(cur_cpu_spec[0]-&gt;cpu_user_features)
multiline_comment|/* This yields a string that ld.so will use to load implementation&n;   specific libraries for optimization.  This is more specific in&n;   intent than poking at uname or /proc/cpuinfo.&n;&n;   For the moment, we have only optimizations for the Intel generations,&n;   but that could change... */
DECL|macro|ELF_PLATFORM
mdefine_line|#define ELF_PLATFORM&t;(NULL)
DECL|macro|SET_PERSONALITY
mdefine_line|#define SET_PERSONALITY(ex, ibcs2) set_personality((ibcs2)?PER_SVR4:PER_LINUX)
multiline_comment|/*&n; * We need to put in some extra aux table entries to tell glibc what&n; * the cache block size is, so it can use the dcbz instruction safely.&n; */
DECL|macro|AT_DCACHEBSIZE
mdefine_line|#define AT_DCACHEBSIZE&t;&t;19
DECL|macro|AT_ICACHEBSIZE
mdefine_line|#define AT_ICACHEBSIZE&t;&t;20
DECL|macro|AT_UCACHEBSIZE
mdefine_line|#define AT_UCACHEBSIZE&t;&t;21
multiline_comment|/* A special ignored type value for PPC, for glibc compatibility.  */
DECL|macro|AT_IGNOREPPC
mdefine_line|#define AT_IGNOREPPC&t;&t;22
r_extern
r_int
id|dcache_bsize
suffix:semicolon
r_extern
r_int
id|icache_bsize
suffix:semicolon
r_extern
r_int
id|ucache_bsize
suffix:semicolon
multiline_comment|/*&n; * The requirements here are:&n; * - keep the final alignment of sp (sp &amp; 0xf)&n; * - make sure the 32-bit value at the first 16 byte aligned position of&n; *   AUXV is greater than 16 for glibc compatibility.&n; *   AT_IGNOREPPC is used for that.&n; * - for compatibility with glibc ARCH_DLINFO must always be defined on PPC,&n; *   even if DLINFO_ARCH_ITEMS goes to zero or is undefined.&n; */
DECL|macro|ARCH_DLINFO
mdefine_line|#define ARCH_DLINFO&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;/* Handle glibc compatibility. */&t;&t;&t;&t;&bslash;&n;&t;NEW_AUX_ENT(AT_IGNOREPPC, AT_IGNOREPPC);&t;&t;&t;&bslash;&n;&t;NEW_AUX_ENT(AT_IGNOREPPC, AT_IGNOREPPC);&t;&t;&t;&bslash;&n;&t;/* Cache size items */&t;&t;&t;&t;&t;&t;&bslash;&n;&t;NEW_AUX_ENT(AT_DCACHEBSIZE, dcache_bsize);&t;&t;&t;&bslash;&n;&t;NEW_AUX_ENT(AT_ICACHEBSIZE, icache_bsize);&t;&t;&t;&bslash;&n;&t;NEW_AUX_ENT(AT_UCACHEBSIZE, ucache_bsize);&t;&t;&t;&bslash;&n; } while (0)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
