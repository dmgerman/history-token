multiline_comment|/* $Id: elf.h,v 1.32 2002/02/09 19:49:31 davem Exp $ */
macro_line|#ifndef __ASM_SPARC64_ELF_H
DECL|macro|__ASM_SPARC64_ELF_H
mdefine_line|#define __ASM_SPARC64_ELF_H
multiline_comment|/*&n; * ELF register definitions..&n; */
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#endif
multiline_comment|/*&n; * Sparc section types&n; */
DECL|macro|STT_REGISTER
mdefine_line|#define STT_REGISTER&t;&t;13
multiline_comment|/*&n; * Sparc ELF relocation types&n; */
DECL|macro|R_SPARC_NONE
mdefine_line|#define&t;R_SPARC_NONE&t;&t;0
DECL|macro|R_SPARC_8
mdefine_line|#define&t;R_SPARC_8&t;&t;1
DECL|macro|R_SPARC_16
mdefine_line|#define&t;R_SPARC_16&t;&t;2
DECL|macro|R_SPARC_32
mdefine_line|#define&t;R_SPARC_32&t;&t;3
DECL|macro|R_SPARC_DISP8
mdefine_line|#define&t;R_SPARC_DISP8&t;&t;4
DECL|macro|R_SPARC_DISP16
mdefine_line|#define&t;R_SPARC_DISP16&t;&t;5
DECL|macro|R_SPARC_DISP32
mdefine_line|#define&t;R_SPARC_DISP32&t;&t;6
DECL|macro|R_SPARC_WDISP30
mdefine_line|#define&t;R_SPARC_WDISP30&t;&t;7
DECL|macro|R_SPARC_WDISP22
mdefine_line|#define&t;R_SPARC_WDISP22&t;&t;8
DECL|macro|R_SPARC_HI22
mdefine_line|#define&t;R_SPARC_HI22&t;&t;9
DECL|macro|R_SPARC_22
mdefine_line|#define&t;R_SPARC_22&t;&t;10
DECL|macro|R_SPARC_13
mdefine_line|#define&t;R_SPARC_13&t;&t;11
DECL|macro|R_SPARC_LO10
mdefine_line|#define&t;R_SPARC_LO10&t;&t;12
DECL|macro|R_SPARC_GOT10
mdefine_line|#define&t;R_SPARC_GOT10&t;&t;13
DECL|macro|R_SPARC_GOT13
mdefine_line|#define&t;R_SPARC_GOT13&t;&t;14
DECL|macro|R_SPARC_GOT22
mdefine_line|#define&t;R_SPARC_GOT22&t;&t;15
DECL|macro|R_SPARC_PC10
mdefine_line|#define&t;R_SPARC_PC10&t;&t;16
DECL|macro|R_SPARC_PC22
mdefine_line|#define&t;R_SPARC_PC22&t;&t;17
DECL|macro|R_SPARC_WPLT30
mdefine_line|#define&t;R_SPARC_WPLT30&t;&t;18
DECL|macro|R_SPARC_COPY
mdefine_line|#define&t;R_SPARC_COPY&t;&t;19
DECL|macro|R_SPARC_GLOB_DAT
mdefine_line|#define&t;R_SPARC_GLOB_DAT&t;20
DECL|macro|R_SPARC_JMP_SLOT
mdefine_line|#define&t;R_SPARC_JMP_SLOT&t;21
DECL|macro|R_SPARC_RELATIVE
mdefine_line|#define&t;R_SPARC_RELATIVE&t;22
DECL|macro|R_SPARC_UA32
mdefine_line|#define&t;R_SPARC_UA32&t;&t;23
DECL|macro|R_SPARC_PLT32
mdefine_line|#define R_SPARC_PLT32&t;&t;24
DECL|macro|R_SPARC_HIPLT22
mdefine_line|#define R_SPARC_HIPLT22&t;&t;25
DECL|macro|R_SPARC_LOPLT10
mdefine_line|#define R_SPARC_LOPLT10&t;&t;26
DECL|macro|R_SPARC_PCPLT32
mdefine_line|#define R_SPARC_PCPLT32&t;&t;27
DECL|macro|R_SPARC_PCPLT22
mdefine_line|#define R_SPARC_PCPLT22&t;&t;28
DECL|macro|R_SPARC_PCPLT10
mdefine_line|#define R_SPARC_PCPLT10&t;&t;29
DECL|macro|R_SPARC_10
mdefine_line|#define R_SPARC_10&t;&t;30
DECL|macro|R_SPARC_11
mdefine_line|#define R_SPARC_11&t;&t;31
DECL|macro|R_SPARC_64
mdefine_line|#define R_SPARC_64&t;&t;32
DECL|macro|R_SPARC_OLO10
mdefine_line|#define R_SPARC_OLO10&t;&t;33
DECL|macro|R_SPARC_WDISP16
mdefine_line|#define R_SPARC_WDISP16&t;&t;40
DECL|macro|R_SPARC_WDISP19
mdefine_line|#define R_SPARC_WDISP19&t;&t;41
DECL|macro|R_SPARC_7
mdefine_line|#define R_SPARC_7&t;&t;43
DECL|macro|R_SPARC_5
mdefine_line|#define R_SPARC_5&t;&t;44
DECL|macro|R_SPARC_6
mdefine_line|#define R_SPARC_6&t;&t;45
multiline_comment|/* Bits present in AT_HWCAP, primarily for Sparc32.  */
DECL|macro|HWCAP_SPARC_FLUSH
mdefine_line|#define HWCAP_SPARC_FLUSH       1    /* CPU supports flush instruction. */
DECL|macro|HWCAP_SPARC_STBAR
mdefine_line|#define HWCAP_SPARC_STBAR       2
DECL|macro|HWCAP_SPARC_SWAP
mdefine_line|#define HWCAP_SPARC_SWAP        4
DECL|macro|HWCAP_SPARC_MULDIV
mdefine_line|#define HWCAP_SPARC_MULDIV      8
DECL|macro|HWCAP_SPARC_V9
mdefine_line|#define HWCAP_SPARC_V9&t;&t;16
DECL|macro|HWCAP_SPARC_ULTRA3
mdefine_line|#define HWCAP_SPARC_ULTRA3&t;32
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
mdefine_line|#define ELF_NGREG 36
DECL|typedef|elf_gregset_t
r_typedef
id|elf_greg_t
id|elf_gregset_t
(braket
id|ELF_NGREG
)braket
suffix:semicolon
multiline_comment|/* Format of 64-bit elf_gregset_t is:&n; * &t;G0 --&gt; G7&n; * &t;O0 --&gt; O7&n; * &t;L0 --&gt; L7&n; * &t;I0 --&gt; I7&n; *&t;TSTATE&n; *&t;TPC&n; *&t;TNPC&n; *&t;Y&n; */
DECL|macro|ELF_CORE_COPY_REGS
mdefine_line|#define ELF_CORE_COPY_REGS(__elf_regs, __pt_regs)&t;&bslash;&n;do {&t;unsigned long *dest = &amp;(__elf_regs[0]);&t;&t;&bslash;&n;&t;struct pt_regs *src = (__pt_regs);&t;&t;&bslash;&n;&t;unsigned long __user *sp;&t;&t;&t;&bslash;&n;&t;int i;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;for(i = 0; i &lt; 16; i++)&t;&t;&t;&t;&bslash;&n;&t;&t;dest[i] = src-&gt;u_regs[i];&t;&t;&bslash;&n;&t;/* Don&squot;t try this at home kids... */&t;&t;&bslash;&n;&t;sp = (unsigned long __user *)&t;&t;&t;&bslash;&n;&t; ((src-&gt;u_regs[14] + STACK_BIAS)&t;&t;&bslash;&n;&t;  &amp; 0xfffffffffffffff8UL);&t;&t;&t;&bslash;&n;&t;for(i = 0; i &lt; 16; i++)&t;&t;&t;&t;&bslash;&n;&t;&t;__get_user(dest[i+16], &amp;sp[i]);&t;&t;&bslash;&n;&t;dest[32] = src-&gt;tstate;&t;&t;&t;&t;&bslash;&n;&t;dest[33] = src-&gt;tpc;&t;&t;&t;&t;&bslash;&n;&t;dest[34] = src-&gt;tnpc;&t;&t;&t;&t;&bslash;&n;&t;dest[35] = src-&gt;y;&t;&t;&t;&t;&bslash;&n;} while (0);
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
DECL|macro|ELF_CORE_COPY_TASK_REGS
mdefine_line|#define ELF_CORE_COPY_TASK_REGS(__tsk, __elf_regs)&t;&bslash;&n;&t;({ ELF_CORE_COPY_REGS((*(__elf_regs)), (__tsk)-&gt;thread_info-&gt;kregs); 1; })
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
mdefine_line|#define ELF_HWCAP&t;((HWCAP_SPARC_FLUSH | HWCAP_SPARC_STBAR | &bslash;&n;&t;&t;&t;  HWCAP_SPARC_SWAP | HWCAP_SPARC_MULDIV | &bslash;&n;&t;&t;&t;  HWCAP_SPARC_V9) | &bslash;&n;&t;&t;&t; ((tlb_type == cheetah || tlb_type == cheetah_plus) ? &bslash;&n;&t;&t;&t;  HWCAP_SPARC_ULTRA3 : 0))
multiline_comment|/* This yields a string that ld.so will use to load implementation&n;   specific libraries for optimization.  This is more specific in&n;   intent than poking at uname or /proc/cpuinfo.  */
DECL|macro|ELF_PLATFORM
mdefine_line|#define ELF_PLATFORM&t;(NULL)
macro_line|#ifdef __KERNEL__
DECL|macro|SET_PERSONALITY
mdefine_line|#define SET_PERSONALITY(ex, ibcs2)&t;&t;&t;&bslash;&n;do {&t;unsigned long new_flags = current_thread_info()-&gt;flags; &bslash;&n;&t;new_flags &amp;= _TIF_32BIT;&t;&t;&t;&bslash;&n;&t;if ((ex).e_ident[EI_CLASS] == ELFCLASS32)&t;&bslash;&n;&t;&t;new_flags |= _TIF_32BIT;&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;new_flags &amp;= ~_TIF_32BIT;&t;&t;&bslash;&n;&t;if ((current_thread_info()-&gt;flags &amp; _TIF_32BIT) &bslash;&n;&t;    != new_flags)&t;&t;&t;&t;&bslash;&n;&t;&t;set_thread_flag(TIF_ABI_PENDING);&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;clear_thread_flag(TIF_ABI_PENDING);&t;&bslash;&n;&t;/* flush_thread will update pgd cache */&t;&bslash;&n;&t;if (ibcs2)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;set_personality(PER_SVR4);&t;&t;&bslash;&n;&t;else if (current-&gt;personality != PER_LINUX32)&t;&bslash;&n;&t;&t;set_personality(PER_LINUX);&t;&t;&bslash;&n;} while (0)
macro_line|#endif
macro_line|#endif /* !(__ASM_SPARC64_ELF_H) */
eof
