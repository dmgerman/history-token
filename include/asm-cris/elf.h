macro_line|#ifndef __ASMCRIS_ELF_H
DECL|macro|__ASMCRIS_ELF_H
mdefine_line|#define __ASMCRIS_ELF_H
multiline_comment|/*&n; * ELF register definitions..&n; */
macro_line|#include &lt;asm/ptrace.h&gt;
DECL|typedef|elf_greg_t
r_typedef
r_int
r_int
id|elf_greg_t
suffix:semicolon
multiline_comment|/* Note that NGREG is defined to ELF_NGREG in include/linux/elfcore.h, and is&n;   thus exposed to user-space. */
DECL|macro|ELF_NGREG
mdefine_line|#define ELF_NGREG (sizeof (struct user_regs_struct) / sizeof(elf_greg_t))
DECL|typedef|elf_gregset_t
r_typedef
id|elf_greg_t
id|elf_gregset_t
(braket
id|ELF_NGREG
)braket
suffix:semicolon
multiline_comment|/* A placeholder; CRIS does not have any fp regs.  */
DECL|typedef|elf_fpregset_t
r_typedef
r_int
r_int
id|elf_fpregset_t
suffix:semicolon
multiline_comment|/*&n; * This is used to ensure we don&squot;t load something for the wrong architecture.&n; */
DECL|macro|elf_check_arch
mdefine_line|#define elf_check_arch(x) ( (x)-&gt;e_machine == EM_CRIS )
multiline_comment|/*&n; * These are used to set parameters in the core dumps.&n; */
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS&t;ELFCLASS32
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;ELFDATA2LSB;
DECL|macro|ELF_ARCH
mdefine_line|#define ELF_ARCH&t;EM_CRIS
multiline_comment|/* SVR4/i386 ABI (pages 3-31, 3-32) says that when the program&n;&t;   starts (a register; assume first param register for CRIS)&n;&t;   contains a pointer to a function which might be&n;&t;   registered using `atexit&squot;.  This provides a mean for the&n;&t;   dynamic linker to call DT_FINI functions for shared libraries&n;&t;   that have been loaded before the code runs.&n;&n;&t;   A value of 0 tells we have no such handler.  */
multiline_comment|/* Explicitly set registers to 0 to increase determinism.  */
DECL|macro|ELF_PLAT_INIT
mdefine_line|#define ELF_PLAT_INIT(_r)&t;do { &bslash;&n;&t;(_r)-&gt;r13 = 0; (_r)-&gt;r12 = 0; (_r)-&gt;r11 = 0; (_r)-&gt;r10 = 0; &bslash;&n;&t;(_r)-&gt;r9 = 0;  (_r)-&gt;r8 = 0;  (_r)-&gt;r7 = 0;  (_r)-&gt;r6 = 0;  &bslash;&n;&t;(_r)-&gt;r5 = 0;  (_r)-&gt;r4 = 0;  (_r)-&gt;r3 = 0;  (_r)-&gt;r2 = 0;  &bslash;&n;&t;(_r)-&gt;r1 = 0;  (_r)-&gt;r0 = 0;  (_r)-&gt;mof = 0; (_r)-&gt;srp = 0; &bslash;&n;} while (0)
DECL|macro|USE_ELF_CORE_DUMP
mdefine_line|#define USE_ELF_CORE_DUMP
multiline_comment|/* The additional layer below is because the stack pointer is missing in &n;   the pt_regs struct, but needed in a core dump. pr_reg is a elf_gregset_t,&n;   and should be filled in according to the layout of the user_regs_struct&n;   struct; regs is a pt_regs struct. We dump all registers, though several are&n;   obviously unnecessary. That way there&squot;s less need for intelligence at &n;   the receiving end (i.e. gdb). */
DECL|macro|ELF_CORE_COPY_REGS
mdefine_line|#define ELF_CORE_COPY_REGS(pr_reg, regs)                   &bslash;&n;&t;pr_reg[0] = regs-&gt;r0;                              &bslash;&n;&t;pr_reg[1] = regs-&gt;r1;                              &bslash;&n;&t;pr_reg[2] = regs-&gt;r2;                              &bslash;&n;&t;pr_reg[3] = regs-&gt;r3;                              &bslash;&n;&t;pr_reg[4] = regs-&gt;r4;                              &bslash;&n;&t;pr_reg[5] = regs-&gt;r5;                              &bslash;&n;&t;pr_reg[6] = regs-&gt;r6;                              &bslash;&n;&t;pr_reg[7] = regs-&gt;r7;                              &bslash;&n;&t;pr_reg[8] = regs-&gt;r8;                              &bslash;&n;&t;pr_reg[9] = regs-&gt;r9;                              &bslash;&n;&t;pr_reg[10] = regs-&gt;r10;                            &bslash;&n;&t;pr_reg[11] = regs-&gt;r11;                            &bslash;&n;&t;pr_reg[12] = regs-&gt;r12;                            &bslash;&n;&t;pr_reg[13] = regs-&gt;r13;                            &bslash;&n;&t;pr_reg[14] = rdusp();               /* sp */       &bslash;&n;&t;pr_reg[15] = regs-&gt;irp;             /* pc */       &bslash;&n;&t;pr_reg[16] = 0;                     /* p0 */       &bslash;&n;&t;pr_reg[17] = rdvr();                /* vr */       &bslash;&n;&t;pr_reg[18] = 0;                     /* p2 */       &bslash;&n;&t;pr_reg[19] = 0;                     /* p3 */       &bslash;&n;&t;pr_reg[20] = 0;                     /* p4 */       &bslash;&n;&t;pr_reg[21] = (regs-&gt;dccr &amp; 0xffff); /* ccr */      &bslash;&n;&t;pr_reg[22] = 0;                     /* p6 */       &bslash;&n;&t;pr_reg[23] = regs-&gt;mof;             /* mof */      &bslash;&n;&t;pr_reg[24] = 0;                     /* p8 */       &bslash;&n;&t;pr_reg[25] = 0;                     /* ibr */      &bslash;&n;&t;pr_reg[26] = 0;                     /* irp */      &bslash;&n;&t;pr_reg[27] = regs-&gt;srp;             /* srp */      &bslash;&n;&t;pr_reg[28] = 0;                     /* bar */      &bslash;&n;&t;pr_reg[29] = regs-&gt;dccr;            /* dccr */     &bslash;&n;&t;pr_reg[30] = 0;                     /* brp */      &bslash;&n;&t;pr_reg[31] = rdusp();               /* usp */      &bslash;&n;&t;pr_reg[32] = 0;                     /* csrinstr */ &bslash;&n;&t;pr_reg[33] = 0;                     /* csraddr */  &bslash;&n;&t;pr_reg[34] = 0;                     /* csrdata */
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE&t;8192
multiline_comment|/* This is the location that an ET_DYN program is loaded if exec&squot;ed.  Typical&n;   use of this is to invoke &quot;./ld.so someprog&quot; to test out a new version of&n;   the loader.  We need to make sure that it is out of the way of the program&n;   that it will &quot;exec&quot;, and that there is sufficient room for the brk.  */
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE         (2 * TASK_SIZE / 3)
multiline_comment|/* This yields a mask that user programs can use to figure out what&n;   instruction set this CPU supports.  This could be done in user space,&n;   but it&squot;s not easy, and we&squot;ve already done it here.  */
DECL|macro|ELF_HWCAP
mdefine_line|#define ELF_HWCAP       (0)
multiline_comment|/* This yields a string that ld.so will use to load implementation&n;   specific libraries for optimization.  This is more specific in&n;   intent than poking at uname or /proc/cpuinfo.&n;*/
DECL|macro|ELF_PLATFORM
mdefine_line|#define ELF_PLATFORM  (NULL)
macro_line|#ifdef __KERNEL__
DECL|macro|SET_PERSONALITY
mdefine_line|#define SET_PERSONALITY(ex, ibcs2) set_personality((ibcs2)?PER_SVR4:PER_LINUX)
macro_line|#endif
macro_line|#endif
eof
