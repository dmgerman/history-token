multiline_comment|/* $Id: elf.h,v 1.22 2000/07/12 01:27:08 davem Exp $ */
macro_line|#ifndef __ASMSPARC_ELF_H
DECL|macro|__ASMSPARC_ELF_H
mdefine_line|#define __ASMSPARC_ELF_H
multiline_comment|/*&n; * ELF register definitions..&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/mbus.h&gt;
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
multiline_comment|/* For the most part we present code dumps in the format&n; * Solaris does.&n; */
DECL|typedef|elf_greg_t
r_typedef
r_int
r_int
id|elf_greg_t
suffix:semicolon
DECL|macro|ELF_NGREG
mdefine_line|#define ELF_NGREG 38
DECL|typedef|elf_gregset_t
r_typedef
id|elf_greg_t
id|elf_gregset_t
(braket
id|ELF_NGREG
)braket
suffix:semicolon
multiline_comment|/* Format is:&n; * &t;G0 --&gt; G7&n; *&t;O0 --&gt; O7&n; *&t;L0 --&gt; L7&n; *&t;I0 --&gt; I7&n; *&t;PSR, PC, nPC, Y, WIM, TBR&n; */
DECL|macro|ELF_CORE_COPY_REGS
mdefine_line|#define ELF_CORE_COPY_REGS(__elf_regs, __pt_regs)&t;&bslash;&n;do {&t;unsigned long *dest = &amp;(__elf_regs[0]);&t;&t;&bslash;&n;&t;struct pt_regs *src = (__pt_regs);&t;&t;&bslash;&n;&t;unsigned long *sp;&t;&t;&t;&t;&bslash;&n;&t;memcpy(&amp;dest[0], &amp;src-&gt;u_regs[0],&t;&t;&bslash;&n;&t;       sizeof(unsigned long) * 16);&t;&t;&bslash;&n;&t;/* Don&squot;t try this at home kids... */&t;&t;&bslash;&n;&t;sp = (unsigned long *) src-&gt;u_regs[14];&t;&t;&bslash;&n;&t;copy_from_user(&amp;dest[16], sp,&t;&t;&t;&bslash;&n;&t;&t;       sizeof(unsigned long) * 16);&t;&bslash;&n;&t;dest[32] = src-&gt;psr;&t;&t;&t;&t;&bslash;&n;&t;dest[33] = src-&gt;pc;&t;&t;&t;&t;&bslash;&n;&t;dest[34] = src-&gt;npc;&t;&t;&t;&t;&bslash;&n;&t;dest[35] = src-&gt;y;&t;&t;&t;&t;&bslash;&n;&t;dest[36] = dest[37] = 0; /* XXX */&t;&t;&bslash;&n;} while(0); /* Janitors: Don&squot;t touch this colon. */
r_typedef
r_struct
(brace
r_union
(brace
DECL|member|pr_regs
r_int
r_int
id|pr_regs
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|pr_dregs
r_float
id|pr_dregs
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|pr_fr
)brace
id|pr_fr
suffix:semicolon
DECL|member|__unused
r_int
r_int
id|__unused
suffix:semicolon
DECL|member|pr_fsr
r_int
r_int
id|pr_fsr
suffix:semicolon
DECL|member|pr_qcnt
r_int
r_char
id|pr_qcnt
suffix:semicolon
DECL|member|pr_q_entrysize
r_int
r_char
id|pr_q_entrysize
suffix:semicolon
DECL|member|pr_en
r_int
r_char
id|pr_en
suffix:semicolon
DECL|member|pr_q
r_int
r_int
id|pr_q
(braket
l_int|64
)braket
suffix:semicolon
DECL|typedef|elf_fpregset_t
)brace
id|elf_fpregset_t
suffix:semicolon
DECL|macro|ELF_CORE_COPY_TASK_REGS
mdefine_line|#define ELF_CORE_COPY_TASK_REGS(__tsk, __elf_regs)&t;&bslash;&n;&t;({ ELF_CORE_COPY_REGS((*(__elf_regs)), (__tsk)-&gt;thread.kregs); 1; })
multiline_comment|/*&n; * This is used to ensure we don&squot;t load something for the wrong architecture.&n; */
DECL|macro|elf_check_arch
mdefine_line|#define elf_check_arch(x) ((x)-&gt;e_machine == EM_SPARC)
multiline_comment|/*&n; * These are used to set parameters in the core dumps.&n; */
DECL|macro|ELF_ARCH
mdefine_line|#define ELF_ARCH&t;EM_SPARC
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS&t;ELFCLASS32
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;ELFDATA2MSB
DECL|macro|USE_ELF_CORE_DUMP
mdefine_line|#define USE_ELF_CORE_DUMP
macro_line|#ifndef CONFIG_SUN4
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE&t;4096
macro_line|#else
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE&t;8192
macro_line|#endif
multiline_comment|/* This is the location that an ET_DYN program is loaded if exec&squot;ed.  Typical&n;   use of this is to invoke &quot;./ld.so someprog&quot; to test out a new version of&n;   the loader.  We need to make sure that it is out of the way of the program&n;   that it will &quot;exec&quot;, and that there is sufficient room for the brk.  */
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE         (TASK_UNMAPPED_BASE)
multiline_comment|/* This yields a mask that user programs can use to figure out what&n;   instruction set this cpu supports.  This can NOT be done in userspace&n;   on Sparc.  */
multiline_comment|/* Sun4c has none of the capabilities, most sun4m&squot;s have them all.&n; * XXX This is gross, set some global variable at boot time. -DaveM&n; */
DECL|macro|ELF_HWCAP
mdefine_line|#define ELF_HWCAP&t;((ARCH_SUN4C_SUN4) ? 0 : &bslash;&n;&t;&t;&t; (HWCAP_SPARC_FLUSH | HWCAP_SPARC_STBAR | &bslash;&n;&t;&t;&t;  HWCAP_SPARC_SWAP | &bslash;&n;&t;&t;&t;  ((srmmu_modtype != Cypress &amp;&amp; &bslash;&n;&t;&t;&t;    srmmu_modtype != Cypress_vE &amp;&amp; &bslash;&n;&t;&t;&t;    srmmu_modtype != Cypress_vD) ? &bslash;&n;&t;&t;&t;   HWCAP_SPARC_MULDIV : 0)))
multiline_comment|/* This yields a string that ld.so will use to load implementation&n;   specific libraries for optimization.  This is more specific in&n;   intent than poking at uname or /proc/cpuinfo. */
DECL|macro|ELF_PLATFORM
mdefine_line|#define ELF_PLATFORM&t;(NULL)
macro_line|#ifdef __KERNEL__
DECL|macro|SET_PERSONALITY
mdefine_line|#define SET_PERSONALITY(ex, ibcs2) set_personality((ibcs2)?PER_SVR4:PER_LINUX)
macro_line|#endif
macro_line|#endif /* !(__ASMSPARC_ELF_H) */
eof
