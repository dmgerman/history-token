macro_line|#ifndef __ASMm68k_ELF_H
DECL|macro|__ASMm68k_ELF_H
mdefine_line|#define __ASMm68k_ELF_H
multiline_comment|/*&n; * ELF register definitions..&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/user.h&gt;
multiline_comment|/*&n; * 68k ELF relocation types&n; */
DECL|macro|R_68K_NONE
mdefine_line|#define R_68K_NONE  0
DECL|macro|R_68K_32
mdefine_line|#define R_68K_32    1
DECL|macro|R_68K_16
mdefine_line|#define R_68K_16    2
DECL|macro|R_68K_8
mdefine_line|#define R_68K_8     3
DECL|macro|R_68K_PC32
mdefine_line|#define R_68K_PC32  4
DECL|macro|R_68K_PC16
mdefine_line|#define R_68K_PC16  5
DECL|macro|R_68K_PC8
mdefine_line|#define R_68K_PC8   6
DECL|macro|R_68K_GOT32
mdefine_line|#define R_68K_GOT32 7
DECL|macro|R_68K_GOT16
mdefine_line|#define R_68K_GOT16 8
DECL|macro|R_68K_GOT8
mdefine_line|#define R_68K_GOT8  9
DECL|macro|R_68K_GOT32O
mdefine_line|#define R_68K_GOT32O    10
DECL|macro|R_68K_GOT16O
mdefine_line|#define R_68K_GOT16O    11
DECL|macro|R_68K_GOT8O
mdefine_line|#define R_68K_GOT8O 12
DECL|macro|R_68K_PLT32
mdefine_line|#define R_68K_PLT32 13
DECL|macro|R_68K_PLT16
mdefine_line|#define R_68K_PLT16 14
DECL|macro|R_68K_PLT8
mdefine_line|#define R_68K_PLT8  15
DECL|macro|R_68K_PLT32O
mdefine_line|#define R_68K_PLT32O    16
DECL|macro|R_68K_PLT16O
mdefine_line|#define R_68K_PLT16O    17
DECL|macro|R_68K_PLT8O
mdefine_line|#define R_68K_PLT8O 18
DECL|macro|R_68K_COPY
mdefine_line|#define R_68K_COPY  19
DECL|macro|R_68K_GLOB_DAT
mdefine_line|#define R_68K_GLOB_DAT  20
DECL|macro|R_68K_JMP_SLOT
mdefine_line|#define R_68K_JMP_SLOT  21
DECL|macro|R_68K_RELATIVE
mdefine_line|#define R_68K_RELATIVE  22
DECL|typedef|elf_greg_t
r_typedef
r_int
r_int
id|elf_greg_t
suffix:semicolon
DECL|macro|ELF_NGREG
mdefine_line|#define ELF_NGREG (sizeof(struct user_regs_struct) / sizeof(elf_greg_t))
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
id|user_m68kfp_struct
id|elf_fpregset_t
suffix:semicolon
multiline_comment|/*&n; * This is used to ensure we don&squot;t load something for the wrong architecture.&n; */
DECL|macro|elf_check_arch
mdefine_line|#define elf_check_arch(x) ((x)-&gt;e_machine == EM_68K)
multiline_comment|/*&n; * These are used to set parameters in the core dumps.&n; */
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS&t;ELFCLASS32
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;ELFDATA2MSB
DECL|macro|ELF_ARCH
mdefine_line|#define ELF_ARCH&t;EM_68K
multiline_comment|/* For SVR4/m68k the function pointer to be registered with `atexit&squot; is&n;   passed in %a1.  Although my copy of the ABI has no such statement, it&n;   is actually used on ASV.  */
DECL|macro|ELF_PLAT_INIT
mdefine_line|#define ELF_PLAT_INIT(_r, load_addr)&t;_r-&gt;a1 = 0
DECL|macro|USE_ELF_CORE_DUMP
mdefine_line|#define USE_ELF_CORE_DUMP
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE&t;4096
multiline_comment|/* This is the location that an ET_DYN program is loaded if exec&squot;ed.  Typical&n;   use of this is to invoke &quot;./ld.so someprog&quot; to test out a new version of&n;   the loader.  We need to make sure that it is out of the way of the program&n;   that it will &quot;exec&quot;, and that there is sufficient room for the brk.  */
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE         0xD0000000UL
DECL|macro|ELF_CORE_COPY_REGS
mdefine_line|#define ELF_CORE_COPY_REGS(pr_reg, regs)&t;&t;&t;&t;&bslash;&n;&t;/* Bleech. */&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[0] = regs-&gt;d1;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[1] = regs-&gt;d2;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[2] = regs-&gt;d3;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[3] = regs-&gt;d4;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[4] = regs-&gt;d5;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[7] = regs-&gt;a0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[8] = regs-&gt;a1;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[14] = regs-&gt;d0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[15] = rdusp();&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[16] = 0 /* regs-&gt;orig_d0 */;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[17] = regs-&gt;sr;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[18] = regs-&gt;pc;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;/* pr_reg[19] = (regs-&gt;format &lt;&lt; 12) | regs-&gt;vector; */&t;&t;&bslash;&n;&t;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  struct switch_stack *sw = ((struct switch_stack *)regs) - 1;&t;&bslash;&n;&t;  pr_reg[5] = sw-&gt;d6;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  pr_reg[6] = sw-&gt;d7;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  pr_reg[10] = sw-&gt;a3;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  pr_reg[11] = sw-&gt;a4;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  pr_reg[12] = sw-&gt;a5;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  pr_reg[13] = sw-&gt;a6;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}
multiline_comment|/* This yields a mask that user programs can use to figure out what&n;   instruction set this cpu supports.  */
DECL|macro|ELF_HWCAP
mdefine_line|#define ELF_HWCAP&t;(0)
multiline_comment|/* This yields a string that ld.so will use to load implementation&n;   specific libraries for optimization.  This is more specific in&n;   intent than poking at uname or /proc/cpuinfo.  */
DECL|macro|ELF_PLATFORM
mdefine_line|#define ELF_PLATFORM  (NULL)
macro_line|#ifdef __KERNEL__
DECL|macro|SET_PERSONALITY
mdefine_line|#define SET_PERSONALITY(ex, ibcs2) set_personality((ibcs2)?PER_SVR4:PER_LINUX)
macro_line|#endif
macro_line|#endif
eof
