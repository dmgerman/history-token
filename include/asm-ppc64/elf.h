macro_line|#ifndef __PPC64_ELF_H
DECL|macro|__PPC64_ELF_H
mdefine_line|#define __PPC64_ELF_H
multiline_comment|/*&n; * ELF register definitions..&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;asm/ptrace.h&gt;
DECL|macro|ELF_NGREG
mdefine_line|#define ELF_NGREG&t;48&t;/* includes nip, msr, lr, etc. */
DECL|macro|ELF_NFPREG
mdefine_line|#define ELF_NFPREG&t;33&t;/* includes fpscr */
DECL|macro|ELF_NVRREG
mdefine_line|#define ELF_NVRREG&t;33&t;/* includes vscr */
DECL|typedef|elf_greg_t64
r_typedef
r_int
r_int
id|elf_greg_t64
suffix:semicolon
DECL|typedef|elf_gregset_t64
r_typedef
id|elf_greg_t64
id|elf_gregset_t64
(braket
id|ELF_NGREG
)braket
suffix:semicolon
DECL|typedef|elf_greg_t32
r_typedef
r_int
r_int
id|elf_greg_t32
suffix:semicolon
DECL|typedef|elf_gregset_t32
r_typedef
id|elf_greg_t32
id|elf_gregset_t32
(braket
id|ELF_NGREG
)braket
suffix:semicolon
multiline_comment|/*&n; * These are used to set parameters in the core dumps.&n; */
macro_line|#ifndef ELF_ARCH
DECL|macro|ELF_ARCH
macro_line|# define ELF_ARCH&t;EM_PPC64
DECL|macro|ELF_CLASS
macro_line|# define ELF_CLASS&t;ELFCLASS64
DECL|macro|ELF_DATA
macro_line|# define ELF_DATA&t;ELFDATA2MSB
DECL|typedef|elf_greg_t
r_typedef
id|elf_greg_t64
id|elf_greg_t
suffix:semicolon
DECL|typedef|elf_gregset_t
r_typedef
id|elf_gregset_t64
id|elf_gregset_t
suffix:semicolon
DECL|macro|elf_addr_t
macro_line|# define elf_addr_t unsigned long
DECL|macro|elf_caddr_t
macro_line|# define elf_caddr_t char *
macro_line|#else
multiline_comment|/* Assumption: ELF_ARCH == EM_PPC and ELF_CLASS == ELFCLASS32 */
DECL|typedef|elf_greg_t
r_typedef
id|elf_greg_t32
id|elf_greg_t
suffix:semicolon
DECL|typedef|elf_gregset_t
r_typedef
id|elf_gregset_t32
id|elf_gregset_t
suffix:semicolon
DECL|macro|elf_addr_t
macro_line|# define elf_addr_t u32
DECL|macro|elf_caddr_t
macro_line|# define elf_caddr_t u32
macro_line|#endif
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
mdefine_line|#define elf_check_arch(x) ((x)-&gt;e_machine == ELF_ARCH)
DECL|macro|USE_ELF_CORE_DUMP
mdefine_line|#define USE_ELF_CORE_DUMP
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE&t;4096
multiline_comment|/* This is the location that an ET_DYN program is loaded if exec&squot;ed.  Typical&n;   use of this is to invoke &quot;./ld.so someprog&quot; to test out a new version of&n;   the loader.  We need to make sure that it is out of the way of the program&n;   that it will &quot;exec&quot;, and that there is sufficient room for the brk.  */
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE         (0x08000000)
multiline_comment|/* Common routine for both 32-bit and 64-bit processes */
DECL|macro|ELF_CORE_COPY_REGS
mdefine_line|#define ELF_CORE_COPY_REGS(gregs, regs) elf_core_copy_regs(gregs, regs);
r_static
r_inline
r_void
DECL|function|elf_core_copy_regs
id|elf_core_copy_regs
c_func
(paren
id|elf_gregset_t
id|dstRegs
comma
r_struct
id|pt_regs
op_star
id|srcRegs
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|numGPRS
op_assign
(paren
(paren
r_sizeof
(paren
r_struct
id|pt_regs
)paren
op_div
r_sizeof
(paren
id|elf_greg_t64
)paren
)paren
OL
id|ELF_NGREG
)paren
ques
c_cond
(paren
r_sizeof
(paren
r_struct
id|pt_regs
)paren
op_div
r_sizeof
(paren
id|elf_greg_t64
)paren
)paren
suffix:colon
id|ELF_NGREG
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|numGPRS
suffix:semicolon
id|i
op_increment
)paren
id|dstRegs
(braket
id|i
)braket
op_assign
(paren
id|elf_greg_t
)paren
(paren
(paren
id|elf_greg_t64
op_star
)paren
id|srcRegs
)paren
(braket
id|i
)braket
suffix:semicolon
)brace
multiline_comment|/* This yields a mask that user programs can use to figure out what&n;   instruction set this cpu supports.  This could be done in userspace,&n;   but it&squot;s not easy, and we&squot;ve already done it here.  */
DECL|macro|ELF_HWCAP
mdefine_line|#define ELF_HWCAP&t;(0)
multiline_comment|/* This yields a string that ld.so will use to load implementation&n;   specific libraries for optimization.  This is more specific in&n;   intent than poking at uname or /proc/cpuinfo.&n;&n;   For the moment, we have only optimizations for the Intel generations,&n;   but that could change... */
DECL|macro|ELF_PLATFORM
mdefine_line|#define ELF_PLATFORM&t;(NULL)
macro_line|#ifdef __KERNEL__
DECL|macro|SET_PERSONALITY
mdefine_line|#define SET_PERSONALITY(ex, ibcs2)&t;&t;&t;&t;&bslash;&n;do {&t;if ((ex).e_ident[EI_CLASS] == ELFCLASS32)&t;&t;&bslash;&n;&t;&t;set_thread_flag(TIF_32BIT);&t;&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;clear_thread_flag(TIF_32BIT);&t;&t;&t;&bslash;&n;&t;if (ibcs2)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;set_personality(PER_SVR4);&t;&t;&t;&bslash;&n;&t;else if (current-&gt;personality != PER_LINUX32)&t;&t;&bslash;&n;&t;&t;set_personality(PER_LINUX);&t;&t;&t;&bslash;&n;} while (0)
macro_line|#endif
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
DECL|macro|DLINFO_ARCH_ITEMS
mdefine_line|#define DLINFO_ARCH_ITEMS&t;3
DECL|macro|ARCH_DLINFO
mdefine_line|#define ARCH_DLINFO&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;sp -= DLINFO_ARCH_ITEMS * 2;&t;&t;&t;&t;&t;&bslash;&n;&t;NEW_AUX_ENT(0, AT_DCACHEBSIZE, dcache_bsize);&t;&t;&t;&bslash;&n;&t;NEW_AUX_ENT(1, AT_ICACHEBSIZE, icache_bsize);&t;&t;&t;&bslash;&n;&t;NEW_AUX_ENT(2, AT_UCACHEBSIZE, ucache_bsize);&t;&t;&t;&bslash;&n;&t;/*&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t; * Now handle glibc compatibility.&t;&t;&t;&t;&bslash;&n;&t; */&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;sp -= 2*2;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;NEW_AUX_ENT(0, AT_IGNOREPPC, AT_IGNOREPPC);&t;&t;&t;&bslash;&n;&t;NEW_AUX_ENT(1, AT_IGNOREPPC, AT_IGNOREPPC);&t;&t;&t;&bslash;&n; } while (0)
macro_line|#endif /* __PPC64_ELF_H */
eof
