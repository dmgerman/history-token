macro_line|#ifndef _ASM_M32R__ELF_H
DECL|macro|_ASM_M32R__ELF_H
mdefine_line|#define _ASM_M32R__ELF_H
multiline_comment|/* $Id$ */
multiline_comment|/*&n; * ELF register definitions..&n; */
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/user.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
multiline_comment|/* M32R relocation types  */
DECL|macro|R_M32R_NONE
mdefine_line|#define&t;R_M32R_NONE&t;&t;0
DECL|macro|R_M32R_16
mdefine_line|#define&t;R_M32R_16&t;&t;1
DECL|macro|R_M32R_32
mdefine_line|#define&t;R_M32R_32&t;&t;2
DECL|macro|R_M32R_24
mdefine_line|#define&t;R_M32R_24&t;&t;3
DECL|macro|R_M32R_10_PCREL
mdefine_line|#define&t;R_M32R_10_PCREL&t;&t;4
DECL|macro|R_M32R_18_PCREL
mdefine_line|#define&t;R_M32R_18_PCREL&t;&t;5
DECL|macro|R_M32R_26_PCREL
mdefine_line|#define&t;R_M32R_26_PCREL&t;&t;6
DECL|macro|R_M32R_HI16_ULO
mdefine_line|#define&t;R_M32R_HI16_ULO&t;&t;7
DECL|macro|R_M32R_HI16_SLO
mdefine_line|#define&t;R_M32R_HI16_SLO&t;&t;8
DECL|macro|R_M32R_LO16
mdefine_line|#define&t;R_M32R_LO16&t;&t;9
DECL|macro|R_M32R_SDA16
mdefine_line|#define&t;R_M32R_SDA16&t;&t;10
macro_line|#ifdef OLD_TYPE
DECL|macro|R_M32R_GOT24
mdefine_line|#define&t;R_M32R_GOT24&t;&t;11
DECL|macro|R_M32R_26_PLTREL
mdefine_line|#define&t;R_M32R_26_PLTREL&t;12
DECL|macro|R_M32R_GOT16_HI_ULO
mdefine_line|#define&t;R_M32R_GOT16_HI_ULO&t;13
DECL|macro|R_M32R_GOT16_HI_SLO
mdefine_line|#define&t;R_M32R_GOT16_HI_SLO&t;14
DECL|macro|R_M32R_GOT16_LO
mdefine_line|#define&t;R_M32R_GOT16_LO&t;&t;15
DECL|macro|R_M32R_GOTPC24
mdefine_line|#define&t;R_M32R_GOTPC24&t;&t;16
DECL|macro|R_M32R_COPY
mdefine_line|#define&t;R_M32R_COPY&t;&t;17
DECL|macro|R_M32R_GLOB_DAT
mdefine_line|#define&t;R_M32R_GLOB_DAT&t;&t;18
DECL|macro|R_M32R_JMP_SLOT
mdefine_line|#define&t;R_M32R_JMP_SLOT&t;&t;19
DECL|macro|R_M32R_RELATIVE
mdefine_line|#define&t;R_M32R_RELATIVE&t;&t;20
DECL|macro|R_M32R_GNU_VTINHERIT
mdefine_line|#define&t;R_M32R_GNU_VTINHERIT&t;21
DECL|macro|R_M32R_GNU_VTENTRY
mdefine_line|#define&t;R_M32R_GNU_VTENTRY&t;22
DECL|macro|R_M32R_16_RELA
mdefine_line|#define R_M32R_16_RELA&t;&t;R_M32R_16
DECL|macro|R_M32R_32_RELA
mdefine_line|#define R_M32R_32_RELA&t;&t;R_M32R_32
DECL|macro|R_M32R_24_RELA
mdefine_line|#define R_M32R_24_RELA&t;&t;R_M32R_24
DECL|macro|R_M32R_10_PCREL_RELA
mdefine_line|#define R_M32R_10_PCREL_RELA&t;R_M32R_10_PCREL
DECL|macro|R_M32R_18_PCREL_RELA
mdefine_line|#define R_M32R_18_PCREL_RELA&t;R_M32R_18_PCREL
DECL|macro|R_M32R_26_PCREL_RELA
mdefine_line|#define R_M32R_26_PCREL_RELA&t;R_M32R_26_PCREL
DECL|macro|R_M32R_HI16_ULO_RELA
mdefine_line|#define R_M32R_HI16_ULO_RELA&t;R_M32R_HI16_ULO
DECL|macro|R_M32R_HI16_SLO_RELA
mdefine_line|#define R_M32R_HI16_SLO_RELA&t;R_M32R_HI16_SLO
DECL|macro|R_M32R_LO16_RELA
mdefine_line|#define R_M32R_LO16_RELA&t;R_M32R_LO16
DECL|macro|R_M32R_SDA16_RELA
mdefine_line|#define R_M32R_SDA16_RELA&t;R_M32R_SDA16
macro_line|#else /* OLD_TYPE */
DECL|macro|R_M32R_GNU_VTINHERIT
mdefine_line|#define&t;R_M32R_GNU_VTINHERIT&t;11
DECL|macro|R_M32R_GNU_VTENTRY
mdefine_line|#define&t;R_M32R_GNU_VTENTRY&t;12
DECL|macro|R_M32R_GOT24_SAMPLE
mdefine_line|#define&t;R_M32R_GOT24_SAMPLE&t;&t;11 /* comflict */
DECL|macro|R_M32R_26_PLTREL_SAMPLE
mdefine_line|#define&t;R_M32R_26_PLTREL_SAMPLE&t;12 /* comflict */
DECL|macro|R_M32R_GOT16_HI_ULO_SAMPLE
mdefine_line|#define&t;R_M32R_GOT16_HI_ULO_SAMPLE&t;13
DECL|macro|R_M32R_GOT16_HI_SLO_SAMPLE
mdefine_line|#define&t;R_M32R_GOT16_HI_SLO_SAMPLE&t;14
DECL|macro|R_M32R_GOT16_LO_SAMPLE
mdefine_line|#define&t;R_M32R_GOT16_LO_SAMPLE&t;&t;15
DECL|macro|R_M32R_GOTPC24_SAMPLE
mdefine_line|#define&t;R_M32R_GOTPC24_SAMPLE&t;&t;16
DECL|macro|R_M32R_COPY_SAMPLE
mdefine_line|#define&t;R_M32R_COPY_SAMPLE&t;&t;17
DECL|macro|R_M32R_GLOB_DAT_SAMPLE
mdefine_line|#define&t;R_M32R_GLOB_DAT_SAMPLE&t;&t;18
DECL|macro|R_M32R_JMP_SLOT_SAMPLE
mdefine_line|#define&t;R_M32R_JMP_SLOT_SAMPLE&t;&t;19
DECL|macro|R_M32R_RELATIVE_SAMPLE
mdefine_line|#define&t;R_M32R_RELATIVE_SAMPLE&t;&t;20
DECL|macro|R_M32R_GNU_VTINHERIT_SAMPLE
mdefine_line|#define&t;R_M32R_GNU_VTINHERIT_SAMPLE&t;21
DECL|macro|R_M32R_GNU_VTENTRY_SAMPLE
mdefine_line|#define&t;R_M32R_GNU_VTENTRY_SAMPLE&t;22
DECL|macro|R_M32R_16_RELA
mdefine_line|#define R_M32R_16_RELA&t;&t;33
DECL|macro|R_M32R_32_RELA
mdefine_line|#define R_M32R_32_RELA&t;&t;34
DECL|macro|R_M32R_24_RELA
mdefine_line|#define R_M32R_24_RELA&t;&t;35
DECL|macro|R_M32R_10_PCREL_RELA
mdefine_line|#define R_M32R_10_PCREL_RELA&t;36
DECL|macro|R_M32R_18_PCREL_RELA
mdefine_line|#define R_M32R_18_PCREL_RELA&t;37
DECL|macro|R_M32R_26_PCREL_RELA
mdefine_line|#define R_M32R_26_PCREL_RELA&t;38
DECL|macro|R_M32R_HI16_ULO_RELA
mdefine_line|#define R_M32R_HI16_ULO_RELA&t;39
DECL|macro|R_M32R_HI16_SLO_RELA
mdefine_line|#define R_M32R_HI16_SLO_RELA&t;40
DECL|macro|R_M32R_LO16_RELA
mdefine_line|#define R_M32R_LO16_RELA&t;41
DECL|macro|R_M32R_SDA16_RELA
mdefine_line|#define R_M32R_SDA16_RELA&t;42
DECL|macro|R_M32R_RELA_GNU_VTINHERIT
mdefine_line|#define&t;R_M32R_RELA_GNU_VTINHERIT&t;43
DECL|macro|R_M32R_RELA_GNU_VTENTRY
mdefine_line|#define&t;R_M32R_RELA_GNU_VTENTRY&t;44
DECL|macro|R_M32R_GOT24
mdefine_line|#define R_M32R_GOT24&t;&t;48
DECL|macro|R_M32R_26_PLTREL
mdefine_line|#define R_M32R_26_PLTREL&t;49
DECL|macro|R_M32R_COPY
mdefine_line|#define R_M32R_COPY&t;&t;50
DECL|macro|R_M32R_GLOB_DAT
mdefine_line|#define R_M32R_GLOB_DAT&t;&t;51
DECL|macro|R_M32R_JMP_SLOT
mdefine_line|#define R_M32R_JMP_SLOT&t;&t;52
DECL|macro|R_M32R_RELATIVE
mdefine_line|#define R_M32R_RELATIVE&t;&t;53
DECL|macro|R_M32R_GOTOFF
mdefine_line|#define R_M32R_GOTOFF&t;&t;54
DECL|macro|R_M32R_GOTPC24
mdefine_line|#define R_M32R_GOTPC24&t;&t;55
DECL|macro|R_M32R_GOT16_HI_ULO
mdefine_line|#define R_M32R_GOT16_HI_ULO&t;56
DECL|macro|R_M32R_GOT16_HI_SLO
mdefine_line|#define R_M32R_GOT16_HI_SLO&t;57
DECL|macro|R_M32R_GOT16_LO
mdefine_line|#define R_M32R_GOT16_LO&t;&t;58
DECL|macro|R_M32R_GOTPC_HI_ULO
mdefine_line|#define R_M32R_GOTPC_HI_ULO&t;59
DECL|macro|R_M32R_GOTPC_HI_SLO
mdefine_line|#define R_M32R_GOTPC_HI_SLO&t;60
DECL|macro|R_M32R_GOTPC_LO
mdefine_line|#define R_M32R_GOTPC_LO&t;&t;61
macro_line|#endif /* OLD_TYPE */
DECL|macro|R_M32R_NUM
mdefine_line|#define R_M32R_NUM&t;&t;256
DECL|typedef|elf_greg_t
r_typedef
r_int
r_int
id|elf_greg_t
suffix:semicolon
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
multiline_comment|/* We have no FP mumumu.  */
DECL|typedef|elf_fpreg_t
r_typedef
r_float
id|elf_fpreg_t
suffix:semicolon
DECL|typedef|elf_fpregset_t
r_typedef
id|elf_fpreg_t
id|elf_fpregset_t
suffix:semicolon
multiline_comment|/*&n; * This is used to ensure we don&squot;t load something for the wrong architecture.&n; */
DECL|macro|elf_check_arch
mdefine_line|#define elf_check_arch(x) &bslash;&n;&t;(((x)-&gt;e_machine == EM_M32R) || ((x)-&gt;e_machine == EM_CYGNUS_M32R))
multiline_comment|/*&n; * These are used to set parameters in the core dumps.&n; */
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS&t;ELFCLASS32
macro_line|#if defined(__LITTLE_ENDIAN)
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;ELFDATA2LSB
macro_line|#elif defined(__BIG_ENDIAN)
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;ELFDATA2MSB
macro_line|#else
macro_line|#error no endian defined
macro_line|#endif
DECL|macro|ELF_ARCH
mdefine_line|#define ELF_ARCH&t;EM_M32R
multiline_comment|/* SVR4/i386 ABI (pages 3-31, 3-32) says that when the program starts %edx&n;   contains a pointer to a function which might be registered using `atexit&squot;.&n;   This provides a mean for the dynamic linker to call DT_FINI functions for&n;   shared libraries that have been loaded before the code runs.&n;&n;   A value of 0 tells we have no such handler.&n;&n;   We might as well make sure everything else is cleared too (except for %esp),&n;   just to make things more deterministic.&n; */
DECL|macro|ELF_PLAT_INIT
mdefine_line|#define ELF_PLAT_INIT(_r, load_addr)&t;do { &bslash;&n;&t;_r-&gt;r0 = 0; &bslash;&n;} while (0)
DECL|macro|USE_ELF_CORE_DUMP
mdefine_line|#define USE_ELF_CORE_DUMP
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE&t;4096
multiline_comment|/* This is the location that an ET_DYN program is loaded if exec&squot;ed.  Typical&n;   use of this is to invoke &quot;./ld.so someprog&quot; to test out a new version of&n;   the loader.  We need to make sure that it is out of the way of the program&n;   that it will &quot;exec&quot;, and that there is sufficient room for the brk.  */
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE         (TASK_SIZE / 3 * 2)
multiline_comment|/* regs is struct pt_regs, pr_reg is elf_gregset_t (which is&n;   now struct_user_regs, they are different) */
DECL|macro|ELF_CORE_COPY_REGS
mdefine_line|#define ELF_CORE_COPY_REGS(pr_reg, regs)  &bslash;&n;&t;memcpy((char *)&amp;pr_reg, (char *)&amp;regs, sizeof (struct pt_regs));
multiline_comment|/* This yields a mask that user programs can use to figure out what&n;   instruction set this CPU supports.  This could be done in user space,&n;   but it&squot;s not easy, and we&squot;ve already done it here.  */
DECL|macro|ELF_HWCAP
mdefine_line|#define ELF_HWCAP&t;(0)
multiline_comment|/* This yields a string that ld.so will use to load implementation&n;   specific libraries for optimization.  This is more specific in&n;   intent than poking at uname or /proc/cpuinfo.&n;&n;   For the moment, we have only optimizations for the Intel generations,&n;   but that could change... */
DECL|macro|ELF_PLATFORM
mdefine_line|#define ELF_PLATFORM  (NULL)
macro_line|#ifdef __KERNEL__
DECL|macro|SET_PERSONALITY
mdefine_line|#define SET_PERSONALITY(ex, ibcs2) set_personality((ibcs2)?PER_SVR4:PER_LINUX)
macro_line|#endif
macro_line|#endif  /* _ASM_M32R__ELF_H */
eof
