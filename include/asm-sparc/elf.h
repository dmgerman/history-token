multiline_comment|/* $Id: elf.h,v 1.22 2000/07/12 01:27:08 davem Exp $ */
macro_line|#ifndef __ASMSPARC_ELF_H
DECL|macro|__ASMSPARC_ELF_H
mdefine_line|#define __ASMSPARC_ELF_H
multiline_comment|/*&n; * ELF register definitions..&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/mbus.h&gt;
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
mdefine_line|#define ELF_CORE_COPY_REGS(__elf_regs, __pt_regs)&t;&bslash;&n;do {&t;unsigned long *dest = &amp;(__elf_regs[0]);&t;&t;&bslash;&n;&t;struct pt_regs *src = (__pt_regs);&t;&t;&bslash;&n;&t;unsigned long *sp;&t;&t;&t;&t;&bslash;&n;&t;memcpy(&amp;dest[0], &amp;src-&gt;u_regs[0],&t;&t;&bslash;&n;&t;       sizeof(unsigned long) * 16);&t;&t;&bslash;&n;&t;/* Don&squot;t try this at home kids... */&t;&t;&bslash;&n;&t;set_fs(USER_DS);&t;&t;&t;&t;&bslash;&n;&t;sp = (unsigned long *) src-&gt;u_regs[14];&t;&t;&bslash;&n;&t;copy_from_user(&amp;dest[16], sp,&t;&t;&t;&bslash;&n;&t;&t;       sizeof(unsigned long) * 16);&t;&bslash;&n;&t;set_fs(KERNEL_DS);&t;&t;&t;&t;&bslash;&n;&t;dest[32] = src-&gt;psr;&t;&t;&t;&t;&bslash;&n;&t;dest[33] = src-&gt;pc;&t;&t;&t;&t;&bslash;&n;&t;dest[34] = src-&gt;npc;&t;&t;&t;&t;&bslash;&n;&t;dest[35] = src-&gt;y;&t;&t;&t;&t;&bslash;&n;&t;dest[36] = dest[37] = 0; /* XXX */&t;&t;&bslash;&n;} while(0);
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
mdefine_line|#define ELF_ET_DYN_BASE         (0x08000000)
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
