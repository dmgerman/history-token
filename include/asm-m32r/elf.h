macro_line|#ifndef _ASM_M32R__ELF_H
DECL|macro|_ASM_M32R__ELF_H
mdefine_line|#define _ASM_M32R__ELF_H
multiline_comment|/*&n; * ELF-specific definitions.&n; *&n; * Copyright (C) 1999-2004, Renesas Technology Corp.&n; *      Hirokazu Takata &lt;takata at linux-m32r.org&gt;&n; */
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/user.h&gt;
macro_line|#include &lt;asm/page.h&gt;
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
DECL|macro|R_M32R_GNU_VTINHERIT
mdefine_line|#define&t;R_M32R_GNU_VTINHERIT&t;11
DECL|macro|R_M32R_GNU_VTENTRY
mdefine_line|#define&t;R_M32R_GNU_VTENTRY&t;12
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
DECL|macro|R_M32R_NUM
mdefine_line|#define R_M32R_NUM&t;&t;256
multiline_comment|/*&n; * ELF register definitions..&n; */
DECL|macro|ELF_NGREG
mdefine_line|#define ELF_NGREG (sizeof (struct pt_regs) / sizeof(elf_greg_t))
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
multiline_comment|/* r0 is set by ld.so to a pointer to a function which might be&n; * registered using &squot;atexit&squot;.  This provides a mean for the dynamic&n; * linker to call DT_FINI functions for shared libraries that have&n; * been loaded before the code runs.&n; *&n; * So that we can use the same startup file with static executables,&n; * we start programs with a value of 0 to indicate that there is no&n; * such function.&n; */
DECL|macro|ELF_PLAT_INIT
mdefine_line|#define ELF_PLAT_INIT(_r, load_addr)&t;(_r)-&gt;r0 = 0
DECL|macro|USE_ELF_CORE_DUMP
mdefine_line|#define USE_ELF_CORE_DUMP
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE&t;PAGE_SIZE
multiline_comment|/*&n; * This is the location that an ET_DYN program is loaded if exec&squot;ed.&n; * Typical use of this is to invoke &quot;./ld.so someprog&quot; to test out a&n; * new version of the loader.  We need to make sure that it is out of&n; * the way of the program that it will &quot;exec&quot;, and that there is&n; * sufficient room for the brk.&n; */
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE         (TASK_SIZE / 3 * 2)
multiline_comment|/* regs is struct pt_regs, pr_reg is elf_gregset_t (which is&n;   now struct_user_regs, they are different) */
DECL|macro|ELF_CORE_COPY_REGS
mdefine_line|#define ELF_CORE_COPY_REGS(pr_reg, regs)  &bslash;&n;&t;memcpy((char *)pr_reg, (char *)regs, sizeof (struct pt_regs));
multiline_comment|/* This yields a mask that user programs can use to figure out what&n;   instruction set this CPU supports.  */
DECL|macro|ELF_HWCAP
mdefine_line|#define ELF_HWCAP&t;(0)
multiline_comment|/* This yields a string that ld.so will use to load implementation&n;   specific libraries for optimization.  This is more specific in&n;   intent than poking at uname or /proc/cpuinfo.  */
DECL|macro|ELF_PLATFORM
mdefine_line|#define ELF_PLATFORM&t;(NULL)
macro_line|#ifdef __KERNEL__
DECL|macro|SET_PERSONALITY
mdefine_line|#define SET_PERSONALITY(ex, ibcs2) set_personality(PER_LINUX)
macro_line|#endif
macro_line|#endif  /* _ASM_M32R__ELF_H */
eof
