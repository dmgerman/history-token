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
mdefine_line|#define ELF_CORE_COPY_REGS(__elf_regs, __pt_regs)&t;&bslash;&n;do {&t;unsigned long *dest = &amp;(__elf_regs[0]);&t;&t;&bslash;&n;&t;struct pt_regs *src = (__pt_regs);&t;&t;&bslash;&n;&t;unsigned long *sp;&t;&t;&t;&t;&bslash;&n;&t;int i;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;for(i = 0; i &lt; 16; i++)&t;&t;&t;&t;&bslash;&n;&t;&t;dest[i] = src-&gt;u_regs[i];&t;&t;&bslash;&n;&t;/* Don&squot;t try this at home kids... */&t;&t;&bslash;&n;&t;sp = (unsigned long *)&t;&t;&t;&t;&bslash;&n;&t; ((src-&gt;u_regs[14] + STACK_BIAS)&t;&t;&bslash;&n;&t;  &amp; 0xfffffffffffffff8UL);&t;&t;&t;&bslash;&n;&t;for(i = 0; i &lt; 16; i++)&t;&t;&t;&t;&bslash;&n;&t;&t;__get_user(dest[i+16], &amp;sp[i]);&t;&t;&bslash;&n;&t;dest[32] = src-&gt;tstate;&t;&t;&t;&t;&bslash;&n;&t;dest[33] = src-&gt;tpc;&t;&t;&t;&t;&bslash;&n;&t;dest[34] = src-&gt;tnpc;&t;&t;&t;&t;&bslash;&n;&t;dest[35] = src-&gt;y;&t;&t;&t;&t;&bslash;&n;} while (0);
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
