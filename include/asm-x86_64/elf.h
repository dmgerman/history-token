macro_line|#ifndef __ASM_X86_64_ELF_H
DECL|macro|__ASM_X86_64_ELF_H
mdefine_line|#define __ASM_X86_64_ELF_H
multiline_comment|/*&n; * ELF register definitions..&n; */
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/user.h&gt;
DECL|typedef|elf_greg_t
r_typedef
r_int
r_int
id|elf_greg_t
suffix:semicolon
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
DECL|typedef|elf_fpregset_t
r_typedef
r_struct
id|user_i387_struct
id|elf_fpregset_t
suffix:semicolon
DECL|typedef|elf_fpxregset_t
r_typedef
r_struct
id|user_fxsr_struct
id|elf_fpxregset_t
suffix:semicolon
multiline_comment|/*&n; * This is used to ensure we don&squot;t load something for the wrong architecture.&n; */
DECL|macro|elf_check_arch
mdefine_line|#define elf_check_arch(x) &bslash;&n;&t;((x)-&gt;e_machine == EM_X8664)
multiline_comment|/*&n; * These are used to set parameters in the core dumps.&n; */
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS&t;ELFCLASS64
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;ELFDATA2LSB
DECL|macro|ELF_ARCH
mdefine_line|#define ELF_ARCH&t;EM_X8664
multiline_comment|/* SVR4/i386 ABI (pages 3-31, 3-32) says that when the program starts %edx&n;   contains a pointer to a function which might be registered using `atexit&squot;.&n;   This provides a mean for the dynamic linker to call DT_FINI functions for&n;   shared libraries that have been loaded before the code runs.&n;&n;   A value of 0 tells we have no such handler. &n;&n;   We might as well make sure everything else is cleared too (except for %esp),&n;   just to make things more deterministic.&n; */
DECL|macro|ELF_PLAT_INIT
mdefine_line|#define ELF_PLAT_INIT(_r)&t;do { &bslash;&n;&t;struct task_struct *cur = current; &bslash;&n;&t;(_r)-&gt;rbx = 0; (_r)-&gt;rcx = 0; (_r)-&gt;rdx = 0; &bslash;&n;&t;(_r)-&gt;rsi = 0; (_r)-&gt;rdi = 0; (_r)-&gt;rbp = 0; &bslash;&n;&t;(_r)-&gt;rax = 0;&t;&t;&t;&t;&bslash;&n;&t;(_r)-&gt;r8 = 0;&t;&t;&t;&t;&bslash;&n;&t;(_r)-&gt;r9 = 0;&t;&t;&t;&t;&bslash;&n;&t;(_r)-&gt;r10 = 0;&t;&t;&t;&t;&bslash;&n;&t;(_r)-&gt;r11 = 0;&t;&t;&t;&t;&bslash;&n;&t;(_r)-&gt;r12 = 0;&t;&t;&t;&t;&bslash;&n;&t;(_r)-&gt;r13 = 0;&t;&t;&t;&t;&bslash;&n;&t;(_r)-&gt;r14 = 0;&t;&t;&t;&t;&bslash;&n;&t;(_r)-&gt;r15 = 0;&t;&t;&t;&t;&bslash;&n;        cur-&gt;thread.fs = 0; cur-&gt;thread.gs = 0; &bslash;&n;&t;cur-&gt;thread.fsindex = 0; cur-&gt;thread.gsindex = 0; &bslash;&n;        cur-&gt;thread.ds = 0; cur-&gt;thread.es = 0;  &bslash;&n;&t;clear_thread_flag(TIF_IA32); &bslash;&n;} while (0)
DECL|macro|USE_ELF_CORE_DUMP
mdefine_line|#define USE_ELF_CORE_DUMP
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE&t;4096
multiline_comment|/* This is the location that an ET_DYN program is loaded if exec&squot;ed.  Typical&n;   use of this is to invoke &quot;./ld.so someprog&quot; to test out a new version of&n;   the loader.  We need to make sure that it is out of the way of the program&n;   that it will &quot;exec&quot;, and that there is sufficient room for the brk.  */
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE         (2 * TASK_SIZE / 3)
multiline_comment|/* regs is struct pt_regs, pr_reg is elf_gregset_t (which is&n;   now struct_user_regs, they are different). Assumes current is the process&n;   getting dumped. */
DECL|macro|ELF_CORE_COPY_REGS
mdefine_line|#define ELF_CORE_COPY_REGS(pr_reg, regs)  do { &bslash;&n;&t;unsigned v;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(pr_reg)[0] = (regs)-&gt;r15;&t;&t;&t;&t;&bslash;&n;&t;(pr_reg)[1] = (regs)-&gt;r14;&t;&t;&t;&t;&bslash;&n;&t;(pr_reg)[2] = (regs)-&gt;r13;&t;&t;&t;&t;&bslash;&n;&t;(pr_reg)[3] = (regs)-&gt;r12;&t;&t;&t;&t;&bslash;&n;&t;(pr_reg)[4] = (regs)-&gt;rbp;&t;&t;&t;&t;&bslash;&n;&t;(pr_reg)[5] = (regs)-&gt;rbx;&t;&t;&t;&t;&bslash;&n;&t;(pr_reg)[6] = (regs)-&gt;r11;&t;&t;&t;&t;&bslash;&n;&t;(pr_reg)[7] = (regs)-&gt;r10;&t;&t;&t;&t;&bslash;&n;&t;(pr_reg)[8] = (regs)-&gt;r9;&t;&t;&t;&t;&bslash;&n;&t;(pr_reg)[9] = (regs)-&gt;r8;&t;&t;&t;&t;&bslash;&n;&t;(pr_reg)[10] = (regs)-&gt;rax;&t;&t;&t;&t;&bslash;&n;&t;(pr_reg)[11] = (regs)-&gt;rcx;&t;&t;&t;&t;&bslash;&n;&t;(pr_reg)[12] = (regs)-&gt;rdx;&t;&t;&t;&t;&bslash;&n;&t;(pr_reg)[13] = (regs)-&gt;rsi;&t;&t;&t;&t;&bslash;&n;&t;(pr_reg)[14] = (regs)-&gt;rdi;&t;&t;&t;&t;&bslash;&n;&t;(pr_reg)[15] = (regs)-&gt;orig_rax;&t;&t;&t;&bslash;&n;&t;(pr_reg)[16] = (regs)-&gt;rip;&t;&t;&t;&bslash;&n;&t;(pr_reg)[17] = (regs)-&gt;cs;&t;&t;&t;&bslash;&n;&t;(pr_reg)[18] = (regs)-&gt;eflags;&t;&t;&t;&bslash;&n;&t;(pr_reg)[19] = (regs)-&gt;rsp;&t;&t;&t;&bslash;&n;&t;(pr_reg)[20] = (regs)-&gt;ss;&t;&t;&t;&bslash;&n;&t;(pr_reg)[21] = current-&gt;thread.fs;&t;&t;&t;&bslash;&n;&t;(pr_reg)[22] = current-&gt;thread.gs;&t;&t;&t;&bslash;&n;&t;asm(&quot;movl %%ds,%0&quot; : &quot;=r&quot; (v)); (pr_reg)[23] = v;&t;&bslash;&n;&t;asm(&quot;movl %%es,%0&quot; : &quot;=r&quot; (v)); (pr_reg)[24] = v;&t;&bslash;&n;&t;asm(&quot;movl %%fs,%0&quot; : &quot;=r&quot; (v)); (pr_reg)[25] = v;&t;&bslash;&n;&t;asm(&quot;movl %%gs,%0&quot; : &quot;=r&quot; (v)); (pr_reg)[26] = v;&t;&bslash;&n;} while(0);
multiline_comment|/* This yields a mask that user programs can use to figure out what&n;   instruction set this CPU supports.  This could be done in user space,&n;   but it&squot;s not easy, and we&squot;ve already done it here.  */
DECL|macro|ELF_HWCAP
mdefine_line|#define ELF_HWCAP&t;(boot_cpu_data.x86_capability[0])
multiline_comment|/* This yields a string that ld.so will use to load implementation&n;   specific libraries for optimization.  This is more specific in&n;   intent than poking at uname or /proc/cpuinfo.&n;&n;   For the moment, we have only optimizations for the Intel generations,&n;   but that could change... */
multiline_comment|/* I&squot;m not sure if we can use &squot;-&squot; here */
DECL|macro|ELF_PLATFORM
mdefine_line|#define ELF_PLATFORM  (&quot;x86_64&quot;)
macro_line|#ifdef __KERNEL__
r_extern
r_void
id|set_personality_64bit
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|SET_PERSONALITY
mdefine_line|#define SET_PERSONALITY(ex, ibcs2) set_personality_64bit()
macro_line|#endif
macro_line|#endif
eof
