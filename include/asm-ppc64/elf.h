macro_line|#ifndef __PPC64_ELF_H
DECL|macro|__PPC64_ELF_H
mdefine_line|#define __PPC64_ELF_H
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
multiline_comment|/* PowerPC relocations defined for the TLS access ABI.  */
DECL|macro|R_PPC_TLS
mdefine_line|#define R_PPC_TLS&t;&t;67 /* none&t;(sym+add)@tls */
DECL|macro|R_PPC_DTPMOD32
mdefine_line|#define R_PPC_DTPMOD32&t;&t;68 /* word32&t;(sym+add)@dtpmod */
DECL|macro|R_PPC_TPREL16
mdefine_line|#define R_PPC_TPREL16&t;&t;69 /* half16*&t;(sym+add)@tprel */
DECL|macro|R_PPC_TPREL16_LO
mdefine_line|#define R_PPC_TPREL16_LO&t;70 /* half16&t;(sym+add)@tprel@l */
DECL|macro|R_PPC_TPREL16_HI
mdefine_line|#define R_PPC_TPREL16_HI&t;71 /* half16&t;(sym+add)@tprel@h */
DECL|macro|R_PPC_TPREL16_HA
mdefine_line|#define R_PPC_TPREL16_HA&t;72 /* half16&t;(sym+add)@tprel@ha */
DECL|macro|R_PPC_TPREL32
mdefine_line|#define R_PPC_TPREL32&t;&t;73 /* word32&t;(sym+add)@tprel */
DECL|macro|R_PPC_DTPREL16
mdefine_line|#define R_PPC_DTPREL16&t;&t;74 /* half16*&t;(sym+add)@dtprel */
DECL|macro|R_PPC_DTPREL16_LO
mdefine_line|#define R_PPC_DTPREL16_LO&t;75 /* half16&t;(sym+add)@dtprel@l */
DECL|macro|R_PPC_DTPREL16_HI
mdefine_line|#define R_PPC_DTPREL16_HI&t;76 /* half16&t;(sym+add)@dtprel@h */
DECL|macro|R_PPC_DTPREL16_HA
mdefine_line|#define R_PPC_DTPREL16_HA&t;77 /* half16&t;(sym+add)@dtprel@ha */
DECL|macro|R_PPC_DTPREL32
mdefine_line|#define R_PPC_DTPREL32&t;&t;78 /* word32&t;(sym+add)@dtprel */
DECL|macro|R_PPC_GOT_TLSGD16
mdefine_line|#define R_PPC_GOT_TLSGD16&t;79 /* half16*&t;(sym+add)@got@tlsgd */
DECL|macro|R_PPC_GOT_TLSGD16_LO
mdefine_line|#define R_PPC_GOT_TLSGD16_LO&t;80 /* half16&t;(sym+add)@got@tlsgd@l */
DECL|macro|R_PPC_GOT_TLSGD16_HI
mdefine_line|#define R_PPC_GOT_TLSGD16_HI&t;81 /* half16&t;(sym+add)@got@tlsgd@h */
DECL|macro|R_PPC_GOT_TLSGD16_HA
mdefine_line|#define R_PPC_GOT_TLSGD16_HA&t;82 /* half16&t;(sym+add)@got@tlsgd@ha */
DECL|macro|R_PPC_GOT_TLSLD16
mdefine_line|#define R_PPC_GOT_TLSLD16&t;83 /* half16*&t;(sym+add)@got@tlsld */
DECL|macro|R_PPC_GOT_TLSLD16_LO
mdefine_line|#define R_PPC_GOT_TLSLD16_LO&t;84 /* half16&t;(sym+add)@got@tlsld@l */
DECL|macro|R_PPC_GOT_TLSLD16_HI
mdefine_line|#define R_PPC_GOT_TLSLD16_HI&t;85 /* half16&t;(sym+add)@got@tlsld@h */
DECL|macro|R_PPC_GOT_TLSLD16_HA
mdefine_line|#define R_PPC_GOT_TLSLD16_HA&t;86 /* half16&t;(sym+add)@got@tlsld@ha */
DECL|macro|R_PPC_GOT_TPREL16
mdefine_line|#define R_PPC_GOT_TPREL16&t;87 /* half16*&t;(sym+add)@got@tprel */
DECL|macro|R_PPC_GOT_TPREL16_LO
mdefine_line|#define R_PPC_GOT_TPREL16_LO&t;88 /* half16&t;(sym+add)@got@tprel@l */
DECL|macro|R_PPC_GOT_TPREL16_HI
mdefine_line|#define R_PPC_GOT_TPREL16_HI&t;89 /* half16&t;(sym+add)@got@tprel@h */
DECL|macro|R_PPC_GOT_TPREL16_HA
mdefine_line|#define R_PPC_GOT_TPREL16_HA&t;90 /* half16&t;(sym+add)@got@tprel@ha */
DECL|macro|R_PPC_GOT_DTPREL16
mdefine_line|#define R_PPC_GOT_DTPREL16&t;91 /* half16*&t;(sym+add)@got@dtprel */
DECL|macro|R_PPC_GOT_DTPREL16_LO
mdefine_line|#define R_PPC_GOT_DTPREL16_LO&t;92 /* half16*&t;(sym+add)@got@dtprel@l */
DECL|macro|R_PPC_GOT_DTPREL16_HI
mdefine_line|#define R_PPC_GOT_DTPREL16_HI&t;93 /* half16*&t;(sym+add)@got@dtprel@h */
DECL|macro|R_PPC_GOT_DTPREL16_HA
mdefine_line|#define R_PPC_GOT_DTPREL16_HA&t;94 /* half16*&t;(sym+add)@got@dtprel@ha */
multiline_comment|/* Keep this the last entry.  */
DECL|macro|R_PPC_NUM
mdefine_line|#define R_PPC_NUM&t;&t;95
multiline_comment|/*&n; * ELF register definitions..&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;asm/ptrace.h&gt;
DECL|macro|ELF_NGREG
mdefine_line|#define ELF_NGREG&t;48&t;/* includes nip, msr, lr, etc. */
DECL|macro|ELF_NFPREG
mdefine_line|#define ELF_NFPREG&t;33&t;/* includes fpscr */
DECL|macro|ELF_NVRREG32
mdefine_line|#define ELF_NVRREG32&t;33&t;/* includes vscr &amp; vrsave stuffed together */
DECL|macro|ELF_NVRREG
mdefine_line|#define ELF_NVRREG&t;34&t;/* includes vscr &amp; vrsave in split vectors */
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
multiline_comment|/* Altivec registers */
multiline_comment|/*&n; * The entries with indexes 0-31 contain the corresponding vector registers. &n; * The entry with index 32 contains the vscr as the last word (offset 12) &n; * within the quadword.  This allows the vscr to be stored as either a &n; * quadword (since it must be copied via a vector register to/from storage) &n; * or as a word.  The entry with index 33 contains the vrsave as the first &n; * word (offset 0) within the quadword.&n; *&n; * This definition of the VMX state is compatible with the current PPC32 &n; * ptrace interface.  This allows signal handling and ptrace to use the same &n; * structures.  This also simplifies the implementation of a bi-arch &n; * (combined (32- and 64-bit) gdb.&n; *&n; * Note that it&squot;s _not_ compatible with 32 bits ucontext which stuffs the&n; * vrsave along with vscr and so only uses 33 vectors for the register set&n; */
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
DECL|typedef|elf_vrregset_t32
r_typedef
id|elf_vrreg_t
id|elf_vrregset_t32
(braket
id|ELF_NVRREG32
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
macro_line|#ifdef __KERNEL__
multiline_comment|/* Common routine for both 32-bit and 64-bit processes */
DECL|function|ppc64_elf_core_copy_regs
r_static
r_inline
r_void
id|ppc64_elf_core_copy_regs
c_func
(paren
id|elf_gregset_t
id|elf_regs
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|gprs
op_assign
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
suffix:semicolon
r_if
c_cond
(paren
id|gprs
OG
id|ELF_NGREG
)paren
id|gprs
op_assign
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
id|gprs
suffix:semicolon
id|i
op_increment
)paren
id|elf_regs
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
id|regs
)paren
(braket
id|i
)braket
suffix:semicolon
)brace
DECL|macro|ELF_CORE_COPY_REGS
mdefine_line|#define ELF_CORE_COPY_REGS(gregs, regs) ppc64_elf_core_copy_regs(gregs, regs);
DECL|function|dump_task_regs
r_static
r_inline
r_int
id|dump_task_regs
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
id|elf_gregset_t
op_star
id|elf_regs
)paren
(brace
r_struct
id|pt_regs
op_star
id|regs
op_assign
id|tsk-&gt;thread.regs
suffix:semicolon
r_if
c_cond
(paren
id|regs
)paren
id|ppc64_elf_core_copy_regs
c_func
(paren
op_star
id|elf_regs
comma
id|regs
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|macro|ELF_CORE_COPY_TASK_REGS
mdefine_line|#define ELF_CORE_COPY_TASK_REGS(tsk, elf_regs) dump_task_regs(tsk, elf_regs)
r_extern
r_int
id|dump_task_fpu
c_func
(paren
r_struct
id|task_struct
op_star
comma
id|elf_fpregset_t
op_star
)paren
suffix:semicolon
DECL|macro|ELF_CORE_COPY_FPREGS
mdefine_line|#define ELF_CORE_COPY_FPREGS(tsk, elf_fpregs) dump_task_fpu(tsk, elf_fpregs)
multiline_comment|/* XXX Should we define the XFPREGS using altivec ??? */
macro_line|#endif
multiline_comment|/* This yields a mask that user programs can use to figure out what&n;   instruction set this cpu supports.  This could be done in userspace,&n;   but it&squot;s not easy, and we&squot;ve already done it here.  */
DECL|macro|ELF_HWCAP
mdefine_line|#define ELF_HWCAP&t;(cur_cpu_spec-&gt;cpu_user_features)
multiline_comment|/* This yields a string that ld.so will use to load implementation&n;   specific libraries for optimization.  This is more specific in&n;   intent than poking at uname or /proc/cpuinfo.&n;&n;   For the moment, we have only optimizations for the Intel generations,&n;   but that could change... */
DECL|macro|ELF_PLATFORM
mdefine_line|#define ELF_PLATFORM&t;(NULL)
DECL|macro|ELF_PLAT_INIT
mdefine_line|#define ELF_PLAT_INIT(_r, load_addr)&t;do { &bslash;&n;&t;memset(_r-&gt;gpr, 0, sizeof(_r-&gt;gpr)); &bslash;&n;&t;_r-&gt;ctr = _r-&gt;link = _r-&gt;xer = _r-&gt;ccr = 0; &bslash;&n;&t;_r-&gt;gpr[2] = load_addr; &bslash;&n;} while (0)
macro_line|#ifdef __KERNEL__
DECL|macro|SET_PERSONALITY
mdefine_line|#define SET_PERSONALITY(ex, ibcs2)&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long new_flags = 0;&t;&t;&t;&t;&bslash;&n;&t;if ((ex).e_ident[EI_CLASS] == ELFCLASS32)&t;&t;&bslash;&n;&t;&t;new_flags = _TIF_32BIT;&t;&t;&t;&t;&bslash;&n;&t;if ((current_thread_info()-&gt;flags &amp; _TIF_32BIT)&t;&t;&bslash;&n;&t;    != new_flags)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;set_thread_flag(TIF_ABI_PENDING);&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;clear_thread_flag(TIF_ABI_PENDING);&t;&t;&bslash;&n;&t;if (ibcs2)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;set_personality(PER_SVR4);&t;&t;&t;&bslash;&n;&t;else if (current-&gt;personality != PER_LINUX32)&t;&t;&bslash;&n;&t;&t;set_personality(PER_LINUX);&t;&t;&t;&bslash;&n;} while (0)
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
multiline_comment|/* The vDSO location. We have to use the same value as x86 for glibc&squot;s&n; * sake :-)&n; */
DECL|macro|AT_SYSINFO_EHDR
mdefine_line|#define AT_SYSINFO_EHDR&t;&t;33
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
multiline_comment|/* We do have an arch_setup_additional_pages for vDSO matters */
DECL|macro|ARCH_HAS_SETUP_ADDITIONAL_PAGES
mdefine_line|#define ARCH_HAS_SETUP_ADDITIONAL_PAGES
r_struct
id|linux_binprm
suffix:semicolon
r_extern
r_int
id|arch_setup_additional_pages
c_func
(paren
r_struct
id|linux_binprm
op_star
id|bprm
comma
r_int
id|executable_stack
)paren
suffix:semicolon
multiline_comment|/*&n; * The requirements here are:&n; * - keep the final alignment of sp (sp &amp; 0xf)&n; * - make sure the 32-bit value at the first 16 byte aligned position of&n; *   AUXV is greater than 16 for glibc compatibility.&n; *   AT_IGNOREPPC is used for that.&n; * - for compatibility with glibc ARCH_DLINFO must always be defined on PPC,&n; *   even if DLINFO_ARCH_ITEMS goes to zero or is undefined.&n; */
DECL|macro|ARCH_DLINFO
mdefine_line|#define ARCH_DLINFO&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;/* Handle glibc compatibility. */&t;&t;&t;&t;&bslash;&n;&t;NEW_AUX_ENT(AT_IGNOREPPC, AT_IGNOREPPC);&t;&t;&t;&bslash;&n;&t;NEW_AUX_ENT(AT_IGNOREPPC, AT_IGNOREPPC);&t;&t;&t;&bslash;&n;&t;/* Cache size items */&t;&t;&t;&t;&t;&t;&bslash;&n;&t;NEW_AUX_ENT(AT_DCACHEBSIZE, dcache_bsize);&t;&t;&t;&bslash;&n;&t;NEW_AUX_ENT(AT_ICACHEBSIZE, icache_bsize);&t;&t;&t;&bslash;&n;&t;NEW_AUX_ENT(AT_UCACHEBSIZE, ucache_bsize);&t;&t;&t;&bslash;&n;&t;/* vDSO base */&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;NEW_AUX_ENT(AT_SYSINFO_EHDR, current-&gt;thread.vdso_base);       &t;&bslash;&n; } while (0)
multiline_comment|/* PowerPC64 relocations defined by the ABIs */
DECL|macro|R_PPC64_NONE
mdefine_line|#define R_PPC64_NONE    R_PPC_NONE
DECL|macro|R_PPC64_ADDR32
mdefine_line|#define R_PPC64_ADDR32  R_PPC_ADDR32  /* 32bit absolute address.  */
DECL|macro|R_PPC64_ADDR24
mdefine_line|#define R_PPC64_ADDR24  R_PPC_ADDR24  /* 26bit address, word aligned.  */
DECL|macro|R_PPC64_ADDR16
mdefine_line|#define R_PPC64_ADDR16  R_PPC_ADDR16  /* 16bit absolute address. */
DECL|macro|R_PPC64_ADDR16_LO
mdefine_line|#define R_PPC64_ADDR16_LO R_PPC_ADDR16_LO /* lower 16bits of abs. address.  */
DECL|macro|R_PPC64_ADDR16_HI
mdefine_line|#define R_PPC64_ADDR16_HI R_PPC_ADDR16_HI /* high 16bits of abs. address. */
DECL|macro|R_PPC64_ADDR16_HA
mdefine_line|#define R_PPC64_ADDR16_HA R_PPC_ADDR16_HA /* adjusted high 16bits.  */
DECL|macro|R_PPC64_ADDR14
mdefine_line|#define R_PPC64_ADDR14 R_PPC_ADDR14   /* 16bit address, word aligned.  */
DECL|macro|R_PPC64_ADDR14_BRTAKEN
mdefine_line|#define R_PPC64_ADDR14_BRTAKEN  R_PPC_ADDR14_BRTAKEN
DECL|macro|R_PPC64_ADDR14_BRNTAKEN
mdefine_line|#define R_PPC64_ADDR14_BRNTAKEN R_PPC_ADDR14_BRNTAKEN
DECL|macro|R_PPC64_REL24
mdefine_line|#define R_PPC64_REL24   R_PPC_REL24 /* PC relative 26 bit, word aligned.  */
DECL|macro|R_PPC64_REL14
mdefine_line|#define R_PPC64_REL14   R_PPC_REL14 /* PC relative 16 bit. */
DECL|macro|R_PPC64_REL14_BRTAKEN
mdefine_line|#define R_PPC64_REL14_BRTAKEN   R_PPC_REL14_BRTAKEN
DECL|macro|R_PPC64_REL14_BRNTAKEN
mdefine_line|#define R_PPC64_REL14_BRNTAKEN  R_PPC_REL14_BRNTAKEN
DECL|macro|R_PPC64_GOT16
mdefine_line|#define R_PPC64_GOT16     R_PPC_GOT16
DECL|macro|R_PPC64_GOT16_LO
mdefine_line|#define R_PPC64_GOT16_LO  R_PPC_GOT16_LO
DECL|macro|R_PPC64_GOT16_HI
mdefine_line|#define R_PPC64_GOT16_HI  R_PPC_GOT16_HI
DECL|macro|R_PPC64_GOT16_HA
mdefine_line|#define R_PPC64_GOT16_HA  R_PPC_GOT16_HA
DECL|macro|R_PPC64_COPY
mdefine_line|#define R_PPC64_COPY      R_PPC_COPY
DECL|macro|R_PPC64_GLOB_DAT
mdefine_line|#define R_PPC64_GLOB_DAT  R_PPC_GLOB_DAT
DECL|macro|R_PPC64_JMP_SLOT
mdefine_line|#define R_PPC64_JMP_SLOT  R_PPC_JMP_SLOT
DECL|macro|R_PPC64_RELATIVE
mdefine_line|#define R_PPC64_RELATIVE  R_PPC_RELATIVE
DECL|macro|R_PPC64_UADDR32
mdefine_line|#define R_PPC64_UADDR32   R_PPC_UADDR32
DECL|macro|R_PPC64_UADDR16
mdefine_line|#define R_PPC64_UADDR16   R_PPC_UADDR16
DECL|macro|R_PPC64_REL32
mdefine_line|#define R_PPC64_REL32     R_PPC_REL32
DECL|macro|R_PPC64_PLT32
mdefine_line|#define R_PPC64_PLT32     R_PPC_PLT32
DECL|macro|R_PPC64_PLTREL32
mdefine_line|#define R_PPC64_PLTREL32  R_PPC_PLTREL32
DECL|macro|R_PPC64_PLT16_LO
mdefine_line|#define R_PPC64_PLT16_LO  R_PPC_PLT16_LO
DECL|macro|R_PPC64_PLT16_HI
mdefine_line|#define R_PPC64_PLT16_HI  R_PPC_PLT16_HI
DECL|macro|R_PPC64_PLT16_HA
mdefine_line|#define R_PPC64_PLT16_HA  R_PPC_PLT16_HA
DECL|macro|R_PPC64_SECTOFF
mdefine_line|#define R_PPC64_SECTOFF     R_PPC_SECTOFF
DECL|macro|R_PPC64_SECTOFF_LO
mdefine_line|#define R_PPC64_SECTOFF_LO  R_PPC_SECTOFF_LO
DECL|macro|R_PPC64_SECTOFF_HI
mdefine_line|#define R_PPC64_SECTOFF_HI  R_PPC_SECTOFF_HI
DECL|macro|R_PPC64_SECTOFF_HA
mdefine_line|#define R_PPC64_SECTOFF_HA  R_PPC_SECTOFF_HA
DECL|macro|R_PPC64_ADDR30
mdefine_line|#define R_PPC64_ADDR30          37  /* word30 (S + A - P) &gt;&gt; 2.  */
DECL|macro|R_PPC64_ADDR64
mdefine_line|#define R_PPC64_ADDR64          38  /* doubleword64 S + A.  */
DECL|macro|R_PPC64_ADDR16_HIGHER
mdefine_line|#define R_PPC64_ADDR16_HIGHER   39  /* half16 #higher(S + A).  */
DECL|macro|R_PPC64_ADDR16_HIGHERA
mdefine_line|#define R_PPC64_ADDR16_HIGHERA  40  /* half16 #highera(S + A).  */
DECL|macro|R_PPC64_ADDR16_HIGHEST
mdefine_line|#define R_PPC64_ADDR16_HIGHEST  41  /* half16 #highest(S + A).  */
DECL|macro|R_PPC64_ADDR16_HIGHESTA
mdefine_line|#define R_PPC64_ADDR16_HIGHESTA 42  /* half16 #highesta(S + A). */
DECL|macro|R_PPC64_UADDR64
mdefine_line|#define R_PPC64_UADDR64     43  /* doubleword64 S + A.  */
DECL|macro|R_PPC64_REL64
mdefine_line|#define R_PPC64_REL64       44  /* doubleword64 S + A - P.  */
DECL|macro|R_PPC64_PLT64
mdefine_line|#define R_PPC64_PLT64       45  /* doubleword64 L + A.  */
DECL|macro|R_PPC64_PLTREL64
mdefine_line|#define R_PPC64_PLTREL64    46  /* doubleword64 L + A - P.  */
DECL|macro|R_PPC64_TOC16
mdefine_line|#define R_PPC64_TOC16       47  /* half16* S + A - .TOC.  */
DECL|macro|R_PPC64_TOC16_LO
mdefine_line|#define R_PPC64_TOC16_LO    48  /* half16 #lo(S + A - .TOC.).  */
DECL|macro|R_PPC64_TOC16_HI
mdefine_line|#define R_PPC64_TOC16_HI    49  /* half16 #hi(S + A - .TOC.).  */
DECL|macro|R_PPC64_TOC16_HA
mdefine_line|#define R_PPC64_TOC16_HA    50  /* half16 #ha(S + A - .TOC.).  */
DECL|macro|R_PPC64_TOC
mdefine_line|#define R_PPC64_TOC         51  /* doubleword64 .TOC. */
DECL|macro|R_PPC64_PLTGOT16
mdefine_line|#define R_PPC64_PLTGOT16    52  /* half16* M + A.  */
DECL|macro|R_PPC64_PLTGOT16_LO
mdefine_line|#define R_PPC64_PLTGOT16_LO 53  /* half16 #lo(M + A).  */
DECL|macro|R_PPC64_PLTGOT16_HI
mdefine_line|#define R_PPC64_PLTGOT16_HI 54  /* half16 #hi(M + A).  */
DECL|macro|R_PPC64_PLTGOT16_HA
mdefine_line|#define R_PPC64_PLTGOT16_HA 55  /* half16 #ha(M + A).  */
DECL|macro|R_PPC64_ADDR16_DS
mdefine_line|#define R_PPC64_ADDR16_DS      56 /* half16ds* (S + A) &gt;&gt; 2.  */
DECL|macro|R_PPC64_ADDR16_LO_DS
mdefine_line|#define R_PPC64_ADDR16_LO_DS   57 /* half16ds  #lo(S + A) &gt;&gt; 2.  */
DECL|macro|R_PPC64_GOT16_DS
mdefine_line|#define R_PPC64_GOT16_DS       58 /* half16ds* (G + A) &gt;&gt; 2.  */
DECL|macro|R_PPC64_GOT16_LO_DS
mdefine_line|#define R_PPC64_GOT16_LO_DS    59 /* half16ds  #lo(G + A) &gt;&gt; 2.  */
DECL|macro|R_PPC64_PLT16_LO_DS
mdefine_line|#define R_PPC64_PLT16_LO_DS    60 /* half16ds  #lo(L + A) &gt;&gt; 2.  */
DECL|macro|R_PPC64_SECTOFF_DS
mdefine_line|#define R_PPC64_SECTOFF_DS     61 /* half16ds* (R + A) &gt;&gt; 2.  */
DECL|macro|R_PPC64_SECTOFF_LO_DS
mdefine_line|#define R_PPC64_SECTOFF_LO_DS  62 /* half16ds  #lo(R + A) &gt;&gt; 2.  */
DECL|macro|R_PPC64_TOC16_DS
mdefine_line|#define R_PPC64_TOC16_DS       63 /* half16ds* (S + A - .TOC.) &gt;&gt; 2.  */
DECL|macro|R_PPC64_TOC16_LO_DS
mdefine_line|#define R_PPC64_TOC16_LO_DS    64 /* half16ds  #lo(S + A - .TOC.) &gt;&gt; 2.  */
DECL|macro|R_PPC64_PLTGOT16_DS
mdefine_line|#define R_PPC64_PLTGOT16_DS    65 /* half16ds* (M + A) &gt;&gt; 2.  */
DECL|macro|R_PPC64_PLTGOT16_LO_DS
mdefine_line|#define R_PPC64_PLTGOT16_LO_DS 66 /* half16ds  #lo(M + A) &gt;&gt; 2.  */
multiline_comment|/* PowerPC64 relocations defined for the TLS access ABI.  */
DECL|macro|R_PPC64_TLS
mdefine_line|#define R_PPC64_TLS&t;&t;67 /* none&t;(sym+add)@tls */
DECL|macro|R_PPC64_DTPMOD64
mdefine_line|#define R_PPC64_DTPMOD64&t;68 /* doubleword64 (sym+add)@dtpmod */
DECL|macro|R_PPC64_TPREL16
mdefine_line|#define R_PPC64_TPREL16&t;&t;69 /* half16*&t;(sym+add)@tprel */
DECL|macro|R_PPC64_TPREL16_LO
mdefine_line|#define R_PPC64_TPREL16_LO&t;70 /* half16&t;(sym+add)@tprel@l */
DECL|macro|R_PPC64_TPREL16_HI
mdefine_line|#define R_PPC64_TPREL16_HI&t;71 /* half16&t;(sym+add)@tprel@h */
DECL|macro|R_PPC64_TPREL16_HA
mdefine_line|#define R_PPC64_TPREL16_HA&t;72 /* half16&t;(sym+add)@tprel@ha */
DECL|macro|R_PPC64_TPREL64
mdefine_line|#define R_PPC64_TPREL64&t;&t;73 /* doubleword64 (sym+add)@tprel */
DECL|macro|R_PPC64_DTPREL16
mdefine_line|#define R_PPC64_DTPREL16&t;74 /* half16*&t;(sym+add)@dtprel */
DECL|macro|R_PPC64_DTPREL16_LO
mdefine_line|#define R_PPC64_DTPREL16_LO&t;75 /* half16&t;(sym+add)@dtprel@l */
DECL|macro|R_PPC64_DTPREL16_HI
mdefine_line|#define R_PPC64_DTPREL16_HI&t;76 /* half16&t;(sym+add)@dtprel@h */
DECL|macro|R_PPC64_DTPREL16_HA
mdefine_line|#define R_PPC64_DTPREL16_HA&t;77 /* half16&t;(sym+add)@dtprel@ha */
DECL|macro|R_PPC64_DTPREL64
mdefine_line|#define R_PPC64_DTPREL64&t;78 /* doubleword64 (sym+add)@dtprel */
DECL|macro|R_PPC64_GOT_TLSGD16
mdefine_line|#define R_PPC64_GOT_TLSGD16&t;79 /* half16*&t;(sym+add)@got@tlsgd */
DECL|macro|R_PPC64_GOT_TLSGD16_LO
mdefine_line|#define R_PPC64_GOT_TLSGD16_LO&t;80 /* half16&t;(sym+add)@got@tlsgd@l */
DECL|macro|R_PPC64_GOT_TLSGD16_HI
mdefine_line|#define R_PPC64_GOT_TLSGD16_HI&t;81 /* half16&t;(sym+add)@got@tlsgd@h */
DECL|macro|R_PPC64_GOT_TLSGD16_HA
mdefine_line|#define R_PPC64_GOT_TLSGD16_HA&t;82 /* half16&t;(sym+add)@got@tlsgd@ha */
DECL|macro|R_PPC64_GOT_TLSLD16
mdefine_line|#define R_PPC64_GOT_TLSLD16&t;83 /* half16*&t;(sym+add)@got@tlsld */
DECL|macro|R_PPC64_GOT_TLSLD16_LO
mdefine_line|#define R_PPC64_GOT_TLSLD16_LO&t;84 /* half16&t;(sym+add)@got@tlsld@l */
DECL|macro|R_PPC64_GOT_TLSLD16_HI
mdefine_line|#define R_PPC64_GOT_TLSLD16_HI&t;85 /* half16&t;(sym+add)@got@tlsld@h */
DECL|macro|R_PPC64_GOT_TLSLD16_HA
mdefine_line|#define R_PPC64_GOT_TLSLD16_HA&t;86 /* half16&t;(sym+add)@got@tlsld@ha */
DECL|macro|R_PPC64_GOT_TPREL16_DS
mdefine_line|#define R_PPC64_GOT_TPREL16_DS&t;87 /* half16ds*&t;(sym+add)@got@tprel */
DECL|macro|R_PPC64_GOT_TPREL16_LO_DS
mdefine_line|#define R_PPC64_GOT_TPREL16_LO_DS 88 /* half16ds (sym+add)@got@tprel@l */
DECL|macro|R_PPC64_GOT_TPREL16_HI
mdefine_line|#define R_PPC64_GOT_TPREL16_HI&t;89 /* half16&t;(sym+add)@got@tprel@h */
DECL|macro|R_PPC64_GOT_TPREL16_HA
mdefine_line|#define R_PPC64_GOT_TPREL16_HA&t;90 /* half16&t;(sym+add)@got@tprel@ha */
DECL|macro|R_PPC64_GOT_DTPREL16_DS
mdefine_line|#define R_PPC64_GOT_DTPREL16_DS&t;91 /* half16ds*&t;(sym+add)@got@dtprel */
DECL|macro|R_PPC64_GOT_DTPREL16_LO_DS
mdefine_line|#define R_PPC64_GOT_DTPREL16_LO_DS 92 /* half16ds (sym+add)@got@dtprel@l */
DECL|macro|R_PPC64_GOT_DTPREL16_HI
mdefine_line|#define R_PPC64_GOT_DTPREL16_HI&t;93 /* half16&t;(sym+add)@got@dtprel@h */
DECL|macro|R_PPC64_GOT_DTPREL16_HA
mdefine_line|#define R_PPC64_GOT_DTPREL16_HA&t;94 /* half16&t;(sym+add)@got@dtprel@ha */
DECL|macro|R_PPC64_TPREL16_DS
mdefine_line|#define R_PPC64_TPREL16_DS&t;95 /* half16ds*&t;(sym+add)@tprel */
DECL|macro|R_PPC64_TPREL16_LO_DS
mdefine_line|#define R_PPC64_TPREL16_LO_DS&t;96 /* half16ds&t;(sym+add)@tprel@l */
DECL|macro|R_PPC64_TPREL16_HIGHER
mdefine_line|#define R_PPC64_TPREL16_HIGHER&t;97 /* half16&t;(sym+add)@tprel@higher */
DECL|macro|R_PPC64_TPREL16_HIGHERA
mdefine_line|#define R_PPC64_TPREL16_HIGHERA&t;98 /* half16&t;(sym+add)@tprel@highera */
DECL|macro|R_PPC64_TPREL16_HIGHEST
mdefine_line|#define R_PPC64_TPREL16_HIGHEST&t;99 /* half16&t;(sym+add)@tprel@highest */
DECL|macro|R_PPC64_TPREL16_HIGHESTA
mdefine_line|#define R_PPC64_TPREL16_HIGHESTA 100 /* half16&t;(sym+add)@tprel@highesta */
DECL|macro|R_PPC64_DTPREL16_DS
mdefine_line|#define R_PPC64_DTPREL16_DS&t;101 /* half16ds* (sym+add)@dtprel */
DECL|macro|R_PPC64_DTPREL16_LO_DS
mdefine_line|#define R_PPC64_DTPREL16_LO_DS&t;102 /* half16ds&t;(sym+add)@dtprel@l */
DECL|macro|R_PPC64_DTPREL16_HIGHER
mdefine_line|#define R_PPC64_DTPREL16_HIGHER&t;103 /* half16&t;(sym+add)@dtprel@higher */
DECL|macro|R_PPC64_DTPREL16_HIGHERA
mdefine_line|#define R_PPC64_DTPREL16_HIGHERA 104 /* half16&t;(sym+add)@dtprel@highera */
DECL|macro|R_PPC64_DTPREL16_HIGHEST
mdefine_line|#define R_PPC64_DTPREL16_HIGHEST 105 /* half16&t;(sym+add)@dtprel@highest */
DECL|macro|R_PPC64_DTPREL16_HIGHESTA
mdefine_line|#define R_PPC64_DTPREL16_HIGHESTA 106 /* half16&t;(sym+add)@dtprel@highesta */
multiline_comment|/* Keep this the last entry.  */
DECL|macro|R_PPC64_NUM
mdefine_line|#define R_PPC64_NUM&t;&t;107
macro_line|#endif /* __PPC64_ELF_H */
eof
