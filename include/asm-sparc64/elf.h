multiline_comment|/* $Id: elf.h,v 1.31 2002/01/08 16:00:20 davem Exp $ */
macro_line|#ifndef __ASM_SPARC64_ELF_H
DECL|macro|__ASM_SPARC64_ELF_H
mdefine_line|#define __ASM_SPARC64_ELF_H
multiline_comment|/*&n; * ELF register definitions..&n; */
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#endif
multiline_comment|/*&n; * These are used to set parameters in the core dumps.&n; */
macro_line|#ifndef ELF_ARCH
DECL|macro|ELF_ARCH
mdefine_line|#define ELF_ARCH&t;&t;EM_SPARCV9
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS&t;&t;ELFCLASS64
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;&t;ELFDATA2MSB
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
r_typedef
r_struct
(brace
DECL|member|pr_regs
r_int
r_int
id|pr_regs
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|pr_fsr
r_int
r_int
id|pr_fsr
suffix:semicolon
DECL|member|pr_gsr
r_int
r_int
id|pr_gsr
suffix:semicolon
DECL|member|pr_fprs
r_int
r_int
id|pr_fprs
suffix:semicolon
DECL|typedef|elf_fpregset_t
)brace
id|elf_fpregset_t
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * This is used to ensure we don&squot;t load something for the wrong architecture.&n; */
macro_line|#ifndef elf_check_arch
DECL|macro|elf_check_arch
mdefine_line|#define elf_check_arch(x) ((x)-&gt;e_machine == ELF_ARCH)&t;/* Might be EM_SPARCV9 or EM_SPARC */
macro_line|#endif
DECL|macro|USE_ELF_CORE_DUMP
mdefine_line|#define USE_ELF_CORE_DUMP
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE&t;PAGE_SIZE
multiline_comment|/* This is the location that an ET_DYN program is loaded if exec&squot;ed.  Typical&n;   use of this is to invoke &quot;./ld.so someprog&quot; to test out a new version of&n;   the loader.  We need to make sure that it is out of the way of the program&n;   that it will &quot;exec&quot;, and that there is sufficient room for the brk.  */
macro_line|#ifndef ELF_ET_DYN_BASE
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE         0x0000010000000000UL
macro_line|#endif
multiline_comment|/* This yields a mask that user programs can use to figure out what&n;   instruction set this cpu supports.  */
multiline_comment|/* On Ultra, we support all of the v8 capabilities. */
DECL|macro|ELF_HWCAP
mdefine_line|#define ELF_HWCAP&t;((HWCAP_SPARC_FLUSH | HWCAP_SPARC_STBAR | &bslash;&n;&t;&t;&t;  HWCAP_SPARC_SWAP | HWCAP_SPARC_MULDIV | &bslash;&n;&t;&t;&t;  HWCAP_SPARC_V9) | &bslash;&n;&t;&t;&t; ((tlb_type == cheetah) ? HWCAP_SPARC_ULTRA3 : 0))
multiline_comment|/* This yields a string that ld.so will use to load implementation&n;   specific libraries for optimization.  This is more specific in&n;   intent than poking at uname or /proc/cpuinfo.  */
DECL|macro|ELF_PLATFORM
mdefine_line|#define ELF_PLATFORM&t;(NULL)
macro_line|#ifdef __KERNEL__
DECL|macro|SET_PERSONALITY
mdefine_line|#define SET_PERSONALITY(ex, ibcs2)&t;&t;&t;&bslash;&n;do {&t;unsigned char flags = current-&gt;thread.flags;&t;&bslash;&n;&t;if ((ex).e_ident[EI_CLASS] == ELFCLASS32)&t;&bslash;&n;&t;&t;flags |= SPARC_FLAG_32BIT;&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;flags &amp;= ~SPARC_FLAG_32BIT;&t;&t;&bslash;&n;&t;if (flags != current-&gt;thread.flags) {&t;&t;&bslash;&n;&t;&t;/* flush_thread will update pgd cache */&bslash;&n;&t;&t;current-&gt;thread.flags = flags;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (ibcs2)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;set_personality(PER_SVR4);&t;&t;&bslash;&n;&t;else if (current-&gt;personality != PER_LINUX32)&t;&bslash;&n;&t;&t;set_personality(PER_LINUX);&t;&t;&bslash;&n;} while (0)
macro_line|#endif
macro_line|#endif /* !(__ASM_SPARC64_ELF_H) */
eof
