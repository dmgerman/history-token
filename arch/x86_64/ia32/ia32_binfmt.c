multiline_comment|/* &n; * Written 2000,2002 by Andi Kleen. &n; * &n; * Loosely based on the sparc64 and IA64 32bit emulation loaders.&n; * This tricks binfmt_elf.c into loading 32bit binaries using lots &n; * of ugly preprocessor tricks. Talk about very very poor man&squot;s inheritance.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/config.h&gt; 
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/rwsem.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/compat.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/binfmts.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/security.h&gt;
macro_line|#include &lt;asm/segment.h&gt; 
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/user32.h&gt;
macro_line|#include &lt;asm/sigcontext32.h&gt;
macro_line|#include &lt;asm/fpu32.h&gt;
macro_line|#include &lt;asm/i387.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/ia32.h&gt;
macro_line|#include &lt;asm/vsyscall32.h&gt;
DECL|macro|ELF_NAME
mdefine_line|#define ELF_NAME &quot;elf/i386&quot;
DECL|macro|AT_SYSINFO
mdefine_line|#define AT_SYSINFO 32
DECL|macro|AT_SYSINFO_EHDR
mdefine_line|#define AT_SYSINFO_EHDR&t;&t;33
DECL|variable|sysctl_vsyscall32
r_int
id|sysctl_vsyscall32
op_assign
l_int|1
suffix:semicolon
DECL|macro|ARCH_DLINFO
mdefine_line|#define ARCH_DLINFO do {  &bslash;&n;&t;if (sysctl_vsyscall32) { &bslash;&n;&t;NEW_AUX_ENT(AT_SYSINFO, (u32)(u64)VSYSCALL32_VSYSCALL); &bslash;&n;&t;NEW_AUX_ENT(AT_SYSINFO_EHDR, VSYSCALL32_BASE);    &bslash;&n;&t;}&t;&bslash;&n;} while(0)
r_struct
id|file
suffix:semicolon
r_struct
id|elf_phdr
suffix:semicolon
DECL|macro|IA32_EMULATOR
mdefine_line|#define IA32_EMULATOR 1
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE&t;&t;(TASK_UNMAPPED_32 + 0x1000000)
DECL|macro|ELF_ARCH
macro_line|#undef ELF_ARCH
DECL|macro|ELF_ARCH
mdefine_line|#define ELF_ARCH EM_386
DECL|macro|ELF_CLASS
macro_line|#undef ELF_CLASS
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS ELFCLASS32
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;ELFDATA2LSB
DECL|macro|USE_ELF_CORE_DUMP
mdefine_line|#define USE_ELF_CORE_DUMP 1
multiline_comment|/* Overwrite elfcore.h */
DECL|macro|_LINUX_ELFCORE_H
mdefine_line|#define _LINUX_ELFCORE_H 1
DECL|typedef|elf_greg_t
r_typedef
r_int
r_int
id|elf_greg_t
suffix:semicolon
DECL|macro|ELF_NGREG
mdefine_line|#define ELF_NGREG (sizeof (struct user_regs_struct32) / sizeof(elf_greg_t))
DECL|typedef|elf_gregset_t
r_typedef
id|elf_greg_t
id|elf_gregset_t
(braket
id|ELF_NGREG
)braket
suffix:semicolon
multiline_comment|/*&n; * These macros parameterize elf_core_dump in fs/binfmt_elf.c to write out&n; * extra segments containing the vsyscall DSO contents.  Dumping its&n; * contents makes post-mortem fully interpretable later without matching up&n; * the same kernel and hardware config to see what PC values meant.&n; * Dumping its extra ELF program headers includes all the other information&n; * a debugger needs to easily find how the vsyscall DSO was being used.&n; */
DECL|macro|ELF_CORE_EXTRA_PHDRS
mdefine_line|#define ELF_CORE_EXTRA_PHDRS&t;&t;(VSYSCALL32_EHDR-&gt;e_phnum)
DECL|macro|ELF_CORE_WRITE_EXTRA_PHDRS
mdefine_line|#define ELF_CORE_WRITE_EXTRA_PHDRS&t;&t;&t;&t;&t;      &bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;const struct elf32_phdr *const vsyscall_phdrs =&t;&t;&t;      &bslash;&n;&t;&t;(const struct elf32_phdr *) (VSYSCALL32_BASE&t;&t;      &bslash;&n;&t;&t;&t;&t;&t;   + VSYSCALL32_EHDR-&gt;e_phoff);&t;      &bslash;&n;&t;int i;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;Elf32_Off ofs = 0;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;for (i = 0; i &lt; VSYSCALL32_EHDR-&gt;e_phnum; ++i) {&t;&t;      &bslash;&n;&t;&t;struct elf32_phdr phdr = vsyscall_phdrs[i];&t;&t;      &bslash;&n;&t;&t;if (phdr.p_type == PT_LOAD) {&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;BUG_ON(ofs != 0);&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;ofs = phdr.p_offset = offset;&t;&t;&t;      &bslash;&n;&t;&t;&t;phdr.p_memsz = PAGE_ALIGN(phdr.p_memsz);&t;      &bslash;&n;&t;&t;&t;phdr.p_filesz = phdr.p_memsz;&t;&t;&t;      &bslash;&n;&t;&t;&t;offset += phdr.p_filesz;&t;&t;&t;      &bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;else&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;phdr.p_offset += ofs;&t;&t;&t;&t;      &bslash;&n;&t;&t;phdr.p_paddr = 0; /* match other core phdrs */&t;&t;      &bslash;&n;&t;&t;DUMP_WRITE(&amp;phdr, sizeof(phdr));&t;&t;&t;      &bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;} while (0)
DECL|macro|ELF_CORE_WRITE_EXTRA_DATA
mdefine_line|#define ELF_CORE_WRITE_EXTRA_DATA&t;&t;&t;&t;&t;      &bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;const struct elf32_phdr *const vsyscall_phdrs =&t;&t;&t;      &bslash;&n;&t;&t;(const struct elf32_phdr *) (VSYSCALL32_BASE&t;&t;      &bslash;&n;&t;&t;&t;&t;&t;   + VSYSCALL32_EHDR-&gt;e_phoff);&t;      &bslash;&n;&t;int i;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;for (i = 0; i &lt; VSYSCALL32_EHDR-&gt;e_phnum; ++i) {&t;&t;      &bslash;&n;&t;&t;if (vsyscall_phdrs[i].p_type == PT_LOAD)&t;&t;      &bslash;&n;&t;&t;&t;DUMP_WRITE((void *) (u64) vsyscall_phdrs[i].p_vaddr,&t;      &bslash;&n;&t;&t;&t;&t;   PAGE_ALIGN(vsyscall_phdrs[i].p_memsz));    &bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;} while (0)
DECL|struct|elf_siginfo
r_struct
id|elf_siginfo
(brace
DECL|member|si_signo
r_int
id|si_signo
suffix:semicolon
multiline_comment|/* signal number */
DECL|member|si_code
r_int
id|si_code
suffix:semicolon
multiline_comment|/* extra code */
DECL|member|si_errno
r_int
id|si_errno
suffix:semicolon
multiline_comment|/* errno */
)brace
suffix:semicolon
DECL|macro|jiffies_to_timeval
mdefine_line|#define jiffies_to_timeval(a,b) do { (b)-&gt;tv_usec = 0; (b)-&gt;tv_sec = (a)/HZ; }while(0)
DECL|struct|elf_prstatus
r_struct
id|elf_prstatus
(brace
DECL|member|pr_info
r_struct
id|elf_siginfo
id|pr_info
suffix:semicolon
multiline_comment|/* Info associated with signal */
DECL|member|pr_cursig
r_int
id|pr_cursig
suffix:semicolon
multiline_comment|/* Current signal */
DECL|member|pr_sigpend
r_int
r_int
id|pr_sigpend
suffix:semicolon
multiline_comment|/* Set of pending signals */
DECL|member|pr_sighold
r_int
r_int
id|pr_sighold
suffix:semicolon
multiline_comment|/* Set of held signals */
DECL|member|pr_pid
id|pid_t
id|pr_pid
suffix:semicolon
DECL|member|pr_ppid
id|pid_t
id|pr_ppid
suffix:semicolon
DECL|member|pr_pgrp
id|pid_t
id|pr_pgrp
suffix:semicolon
DECL|member|pr_sid
id|pid_t
id|pr_sid
suffix:semicolon
DECL|member|pr_utime
r_struct
id|compat_timeval
id|pr_utime
suffix:semicolon
multiline_comment|/* User time */
DECL|member|pr_stime
r_struct
id|compat_timeval
id|pr_stime
suffix:semicolon
multiline_comment|/* System time */
DECL|member|pr_cutime
r_struct
id|compat_timeval
id|pr_cutime
suffix:semicolon
multiline_comment|/* Cumulative user time */
DECL|member|pr_cstime
r_struct
id|compat_timeval
id|pr_cstime
suffix:semicolon
multiline_comment|/* Cumulative system time */
DECL|member|pr_reg
id|elf_gregset_t
id|pr_reg
suffix:semicolon
multiline_comment|/* GP registers */
DECL|member|pr_fpvalid
r_int
id|pr_fpvalid
suffix:semicolon
multiline_comment|/* True if math co-processor being used.  */
)brace
suffix:semicolon
DECL|macro|ELF_PRARGSZ
mdefine_line|#define ELF_PRARGSZ&t;(80)&t;/* Number of chars for args */
DECL|struct|elf_prpsinfo
r_struct
id|elf_prpsinfo
(brace
DECL|member|pr_state
r_char
id|pr_state
suffix:semicolon
multiline_comment|/* numeric process state */
DECL|member|pr_sname
r_char
id|pr_sname
suffix:semicolon
multiline_comment|/* char for pr_state */
DECL|member|pr_zomb
r_char
id|pr_zomb
suffix:semicolon
multiline_comment|/* zombie */
DECL|member|pr_nice
r_char
id|pr_nice
suffix:semicolon
multiline_comment|/* nice val */
DECL|member|pr_flag
r_int
r_int
id|pr_flag
suffix:semicolon
multiline_comment|/* flags */
DECL|member|pr_uid
id|__u16
id|pr_uid
suffix:semicolon
DECL|member|pr_gid
id|__u16
id|pr_gid
suffix:semicolon
DECL|member|pr_pid
DECL|member|pr_ppid
DECL|member|pr_pgrp
DECL|member|pr_sid
id|pid_t
id|pr_pid
comma
id|pr_ppid
comma
id|pr_pgrp
comma
id|pr_sid
suffix:semicolon
multiline_comment|/* Lots missing */
DECL|member|pr_fname
r_char
id|pr_fname
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* filename of executable */
DECL|member|pr_psargs
r_char
id|pr_psargs
(braket
id|ELF_PRARGSZ
)braket
suffix:semicolon
multiline_comment|/* initial part of arg list */
)brace
suffix:semicolon
DECL|macro|__STR
mdefine_line|#define __STR(x) #x
DECL|macro|STR
mdefine_line|#define STR(x) __STR(x)
DECL|macro|_GET_SEG
mdefine_line|#define _GET_SEG(x) &bslash;&n;&t;({ __u32 seg; asm(&quot;movl %%&quot; STR(x) &quot;,%0&quot; : &quot;=r&quot;(seg)); seg; })
multiline_comment|/* Assumes current==process to be dumped */
DECL|macro|ELF_CORE_COPY_REGS
mdefine_line|#define ELF_CORE_COPY_REGS(pr_reg, regs)       &t;&t;&bslash;&n;&t;pr_reg[0] = regs-&gt;rbx;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[1] = regs-&gt;rcx;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[2] = regs-&gt;rdx;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[3] = regs-&gt;rsi;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[4] = regs-&gt;rdi;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[5] = regs-&gt;rbp;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[6] = regs-&gt;rax;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[7] = _GET_SEG(ds);   &t;&t;&t;&bslash;&n;&t;pr_reg[8] = _GET_SEG(es);&t;&t;&t;&bslash;&n;&t;pr_reg[9] = _GET_SEG(fs);&t;&t;&t;&bslash;&n;&t;pr_reg[10] = _GET_SEG(gs);&t;&t;&t;&bslash;&n;&t;pr_reg[11] = regs-&gt;orig_rax;&t;&t;&t;&bslash;&n;&t;pr_reg[12] = regs-&gt;rip;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[13] = regs-&gt;cs;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[14] = regs-&gt;eflags;&t;&t;&t;&bslash;&n;&t;pr_reg[15] = regs-&gt;rsp;&t;&t;&t;&t;&bslash;&n;&t;pr_reg[16] = regs-&gt;ss;
DECL|macro|user
mdefine_line|#define user user32
DECL|macro|__ASM_X86_64_ELF_H
mdefine_line|#define __ASM_X86_64_ELF_H 1
DECL|macro|elf_read_implies_exec
mdefine_line|#define elf_read_implies_exec(ex, have_pt_gnu_stack)&t;(!(have_pt_gnu_stack))
singleline_comment|//#include &lt;asm/ia32.h&gt;
macro_line|#include &lt;linux/elf.h&gt;
DECL|typedef|elf_fpregset_t
r_typedef
r_struct
id|user_i387_ia32_struct
id|elf_fpregset_t
suffix:semicolon
DECL|typedef|elf_fpxregset_t
r_typedef
r_struct
id|user32_fxsr_struct
id|elf_fpxregset_t
suffix:semicolon
DECL|function|elf_core_copy_regs
r_static
r_inline
r_void
id|elf_core_copy_regs
c_func
(paren
id|elf_gregset_t
op_star
id|elfregs
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|ELF_CORE_COPY_REGS
c_func
(paren
(paren
op_star
id|elfregs
)paren
comma
id|regs
)paren
)brace
DECL|function|elf_core_copy_task_regs
r_static
r_inline
r_int
id|elf_core_copy_task_regs
c_func
(paren
r_struct
id|task_struct
op_star
id|t
comma
id|elf_gregset_t
op_star
id|elfregs
)paren
(brace
r_struct
id|pt_regs
op_star
id|pp
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
(paren
id|t-&gt;thread.rsp0
)paren
suffix:semicolon
op_decrement
id|pp
suffix:semicolon
id|ELF_CORE_COPY_REGS
c_func
(paren
(paren
op_star
id|elfregs
)paren
comma
id|pp
)paren
suffix:semicolon
multiline_comment|/* fix wrong segments */
(paren
op_star
id|elfregs
)paren
(braket
l_int|7
)braket
op_assign
id|t-&gt;thread.ds
suffix:semicolon
(paren
op_star
id|elfregs
)paren
(braket
l_int|9
)braket
op_assign
id|t-&gt;thread.fsindex
suffix:semicolon
(paren
op_star
id|elfregs
)paren
(braket
l_int|10
)braket
op_assign
id|t-&gt;thread.gsindex
suffix:semicolon
(paren
op_star
id|elfregs
)paren
(braket
l_int|8
)braket
op_assign
id|t-&gt;thread.es
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|elf_core_copy_task_fpregs
id|elf_core_copy_task_fpregs
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_struct
id|pt_regs
op_star
id|regs
comma
id|elf_fpregset_t
op_star
id|fpu
)paren
(brace
r_struct
id|_fpstate_ia32
op_star
id|fpstate
op_assign
(paren
r_void
op_star
)paren
id|fpu
suffix:semicolon
id|mm_segment_t
id|oldfs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tsk-&gt;used_math
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|regs
)paren
id|regs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
id|tsk-&gt;thread.rsp0
suffix:semicolon
op_decrement
id|regs
suffix:semicolon
r_if
c_cond
(paren
id|tsk
op_eq
id|current
)paren
id|unlazy_fpu
c_func
(paren
id|tsk
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|save_i387_ia32
c_func
(paren
id|tsk
comma
id|fpstate
comma
id|regs
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Correct for i386 bug. It puts the fop into the upper 16bits of &n;&t;   the tag word (like FXSAVE), not into the fcs*/
id|fpstate-&gt;cssel
op_or_assign
id|fpstate-&gt;tag
op_amp
l_int|0xffff0000
suffix:semicolon
id|set_fs
c_func
(paren
id|oldfs
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|macro|ELF_CORE_COPY_XFPREGS
mdefine_line|#define ELF_CORE_COPY_XFPREGS 1
r_static
r_inline
r_int
DECL|function|elf_core_copy_task_xfpregs
id|elf_core_copy_task_xfpregs
c_func
(paren
r_struct
id|task_struct
op_star
id|t
comma
id|elf_fpxregset_t
op_star
id|xfpu
)paren
(brace
r_struct
id|pt_regs
op_star
id|regs
op_assign
(paren
(paren
r_struct
id|pt_regs
op_star
)paren
(paren
id|t-&gt;thread.rsp0
)paren
)paren
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|t-&gt;used_math
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|t
op_eq
id|current
)paren
id|unlazy_fpu
c_func
(paren
id|t
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|xfpu
comma
op_amp
id|t-&gt;thread.i387.fxsave
comma
r_sizeof
(paren
id|elf_fpxregset_t
)paren
)paren
suffix:semicolon
id|xfpu-&gt;fcs
op_assign
id|regs-&gt;cs
suffix:semicolon
id|xfpu-&gt;fos
op_assign
id|t-&gt;thread.ds
suffix:semicolon
multiline_comment|/* right? */
r_return
l_int|1
suffix:semicolon
)brace
DECL|macro|elf_check_arch
macro_line|#undef elf_check_arch
DECL|macro|elf_check_arch
mdefine_line|#define elf_check_arch(x) &bslash;&n;&t;((x)-&gt;e_machine == EM_386)
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE PAGE_SIZE
DECL|macro|ELF_HWCAP
mdefine_line|#define ELF_HWCAP (boot_cpu_data.x86_capability[0])
DECL|macro|ELF_PLATFORM
mdefine_line|#define ELF_PLATFORM  (&quot;i686&quot;)
DECL|macro|SET_PERSONALITY
mdefine_line|#define SET_PERSONALITY(ex, ibcs2)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long new_flags = 0;&t;&t;&t;&t;&bslash;&n;&t;if ((ex).e_ident[EI_CLASS] == ELFCLASS32)&t;&t;&bslash;&n;&t;&t;new_flags = _TIF_IA32;&t;&t;&t;&t;&bslash;&n;&t;if ((current_thread_info()-&gt;flags &amp; _TIF_IA32)&t;&t;&bslash;&n;&t;    != new_flags)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;set_thread_flag(TIF_ABI_PENDING);&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;clear_thread_flag(TIF_ABI_PENDING);&t;&t;&bslash;&n;} while (0)
multiline_comment|/* Override some function names */
DECL|macro|elf_format
mdefine_line|#define elf_format&t;&t;&t;elf32_format
DECL|macro|init_elf_binfmt
mdefine_line|#define init_elf_binfmt&t;&t;&t;init_elf32_binfmt
DECL|macro|exit_elf_binfmt
mdefine_line|#define exit_elf_binfmt&t;&t;&t;exit_elf32_binfmt
DECL|macro|load_elf_binary
mdefine_line|#define load_elf_binary load_elf32_binary
DECL|macro|ELF_PLAT_INIT
mdefine_line|#define ELF_PLAT_INIT(r, load_addr)&t;elf32_init(r)
DECL|macro|setup_arg_pages
mdefine_line|#define setup_arg_pages(bprm, exec_stack)&t;ia32_setup_arg_pages(bprm, exec_stack)
r_int
id|ia32_setup_arg_pages
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
DECL|macro|start_thread
macro_line|#undef start_thread
DECL|macro|start_thread
mdefine_line|#define start_thread(regs,new_rip,new_rsp) do { &bslash;&n;&t;asm volatile(&quot;movl %0,%%fs&quot; :: &quot;r&quot; (0)); &bslash;&n;&t;asm volatile(&quot;movl %0,%%es; movl %0,%%ds&quot;: :&quot;r&quot; (__USER32_DS)); &bslash;&n;&t;load_gs_index(0); &bslash;&n;&t;(regs)-&gt;rip = (new_rip); &bslash;&n;&t;(regs)-&gt;rsp = (new_rsp); &bslash;&n;&t;(regs)-&gt;eflags = 0x200; &bslash;&n;&t;(regs)-&gt;cs = __USER32_CS; &bslash;&n;&t;(regs)-&gt;ss = __USER32_DS; &bslash;&n;&t;set_fs(USER_DS); &bslash;&n;} while(0) 
DECL|macro|elf_map
mdefine_line|#define elf_map elf32_map
macro_line|#include &lt;linux/module.h&gt;
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Binary format loader for compatibility with IA32 ELF binaries.&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Eric Youngdale, Andi Kleen&quot;
)paren
suffix:semicolon
DECL|macro|MODULE_DESCRIPTION
macro_line|#undef MODULE_DESCRIPTION
DECL|macro|MODULE_AUTHOR
macro_line|#undef MODULE_AUTHOR
DECL|macro|elf_addr_t
mdefine_line|#define elf_addr_t __u32
DECL|macro|TASK_SIZE
macro_line|#undef TASK_SIZE
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE 0xffffffff
r_static
r_void
id|elf32_init
c_func
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
macro_line|#include &quot;../../../fs/binfmt_elf.c&quot; 
DECL|function|elf32_init
r_static
r_void
id|elf32_init
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|task_struct
op_star
id|me
op_assign
id|current
suffix:semicolon
id|regs-&gt;rdi
op_assign
l_int|0
suffix:semicolon
id|regs-&gt;rsi
op_assign
l_int|0
suffix:semicolon
id|regs-&gt;rdx
op_assign
l_int|0
suffix:semicolon
id|regs-&gt;rcx
op_assign
l_int|0
suffix:semicolon
id|regs-&gt;rax
op_assign
l_int|0
suffix:semicolon
id|regs-&gt;rbx
op_assign
l_int|0
suffix:semicolon
id|regs-&gt;rbp
op_assign
l_int|0
suffix:semicolon
id|regs-&gt;r8
op_assign
id|regs-&gt;r9
op_assign
id|regs-&gt;r10
op_assign
id|regs-&gt;r11
op_assign
id|regs-&gt;r12
op_assign
id|regs-&gt;r13
op_assign
id|regs-&gt;r14
op_assign
id|regs-&gt;r15
op_assign
l_int|0
suffix:semicolon
id|me-&gt;thread.fs
op_assign
l_int|0
suffix:semicolon
id|me-&gt;thread.gs
op_assign
l_int|0
suffix:semicolon
id|me-&gt;thread.fsindex
op_assign
l_int|0
suffix:semicolon
id|me-&gt;thread.gsindex
op_assign
l_int|0
suffix:semicolon
id|me-&gt;thread.ds
op_assign
id|__USER_DS
suffix:semicolon
id|me-&gt;thread.es
op_assign
id|__USER_DS
suffix:semicolon
)brace
DECL|function|setup_arg_pages
r_int
id|setup_arg_pages
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
(brace
r_int
r_int
id|stack_base
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|mpnt
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|current-&gt;mm
suffix:semicolon
r_int
id|i
suffix:semicolon
id|stack_base
op_assign
id|IA32_STACK_TOP
op_minus
id|MAX_ARG_PAGES
op_star
id|PAGE_SIZE
suffix:semicolon
id|mm-&gt;arg_start
op_assign
id|bprm-&gt;p
op_plus
id|stack_base
suffix:semicolon
id|bprm-&gt;p
op_add_assign
id|stack_base
suffix:semicolon
r_if
c_cond
(paren
id|bprm-&gt;loader
)paren
id|bprm-&gt;loader
op_add_assign
id|stack_base
suffix:semicolon
id|bprm-&gt;exec
op_add_assign
id|stack_base
suffix:semicolon
id|mpnt
op_assign
id|kmem_cache_alloc
c_func
(paren
id|vm_area_cachep
comma
id|SLAB_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mpnt
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|security_vm_enough_memory
c_func
(paren
(paren
id|IA32_STACK_TOP
op_minus
(paren
id|PAGE_MASK
op_amp
(paren
r_int
r_int
)paren
id|bprm-&gt;p
)paren
)paren
op_rshift
id|PAGE_SHIFT
)paren
)paren
(brace
id|kmem_cache_free
c_func
(paren
id|vm_area_cachep
comma
id|mpnt
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|mpnt
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|mpnt
)paren
)paren
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
(brace
id|mpnt-&gt;vm_mm
op_assign
id|mm
suffix:semicolon
id|mpnt-&gt;vm_start
op_assign
id|PAGE_MASK
op_amp
(paren
r_int
r_int
)paren
id|bprm-&gt;p
suffix:semicolon
id|mpnt-&gt;vm_end
op_assign
id|IA32_STACK_TOP
suffix:semicolon
r_if
c_cond
(paren
id|executable_stack
op_eq
id|EXSTACK_ENABLE_X
)paren
id|mpnt-&gt;vm_flags
op_assign
id|VM_STACK_FLAGS
op_or
id|VM_EXEC
suffix:semicolon
r_else
r_if
c_cond
(paren
id|executable_stack
op_eq
id|EXSTACK_DISABLE_X
)paren
id|mpnt-&gt;vm_flags
op_assign
id|VM_STACK_FLAGS
op_amp
op_complement
id|VM_EXEC
suffix:semicolon
r_else
id|mpnt-&gt;vm_flags
op_assign
id|VM_STACK_FLAGS
suffix:semicolon
id|mpnt-&gt;vm_page_prot
op_assign
(paren
id|mpnt-&gt;vm_flags
op_amp
id|VM_EXEC
)paren
ques
c_cond
id|PAGE_COPY_EXEC
suffix:colon
id|PAGE_COPY
suffix:semicolon
id|insert_vm_struct
c_func
(paren
id|mm
comma
id|mpnt
)paren
suffix:semicolon
id|mm-&gt;stack_vm
op_assign
id|mm-&gt;total_vm
op_assign
id|vma_pages
c_func
(paren
id|mpnt
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_ARG_PAGES
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|bprm-&gt;page
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|page
)paren
(brace
id|bprm-&gt;page
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
id|install_arg_page
c_func
(paren
id|mpnt
comma
id|page
comma
id|stack_base
)paren
suffix:semicolon
)brace
id|stack_base
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
id|up_write
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|elf32_map
id|elf32_map
(paren
r_struct
id|file
op_star
id|filep
comma
r_int
r_int
id|addr
comma
r_struct
id|elf_phdr
op_star
id|eppnt
comma
r_int
id|prot
comma
r_int
id|type
)paren
(brace
r_int
r_int
id|map_addr
suffix:semicolon
r_struct
id|task_struct
op_star
id|me
op_assign
id|current
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|me-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|map_addr
op_assign
id|do_mmap
c_func
(paren
id|filep
comma
id|ELF_PAGESTART
c_func
(paren
id|addr
)paren
comma
id|eppnt-&gt;p_filesz
op_plus
id|ELF_PAGEOFFSET
c_func
(paren
id|eppnt-&gt;p_vaddr
)paren
comma
id|prot
comma
id|type
comma
id|eppnt-&gt;p_offset
op_minus
id|ELF_PAGEOFFSET
c_func
(paren
id|eppnt-&gt;p_vaddr
)paren
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|me-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
r_return
id|map_addr
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SYSCTL
multiline_comment|/* Register vsyscall32 into the ABI table */
macro_line|#include &lt;linux/sysctl.h&gt;
DECL|variable|abi_table2
r_static
id|ctl_table
id|abi_table2
(braket
)braket
op_assign
(brace
(brace
l_int|99
comma
l_string|&quot;vsyscall32&quot;
comma
op_amp
id|sysctl_vsyscall32
comma
r_sizeof
(paren
r_int
)paren
comma
l_int|0644
comma
l_int|NULL
comma
id|proc_dointvec
)brace
comma
(brace
l_int|0
comma
)brace
)brace
suffix:semicolon
DECL|variable|abi_root_table2
r_static
id|ctl_table
id|abi_root_table2
(braket
)braket
op_assign
(brace
(brace
dot
id|ctl_name
op_assign
id|CTL_ABI
comma
dot
id|procname
op_assign
l_string|&quot;abi&quot;
comma
dot
id|mode
op_assign
l_int|0555
comma
dot
id|child
op_assign
id|abi_table2
)brace
comma
(brace
l_int|0
)brace
comma
)brace
suffix:semicolon
DECL|function|ia32_binfmt_init
r_static
id|__init
r_int
id|ia32_binfmt_init
c_func
(paren
r_void
)paren
(brace
id|register_sysctl_table
c_func
(paren
id|abi_root_table2
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ia32_binfmt_init
id|__initcall
c_func
(paren
id|ia32_binfmt_init
)paren
suffix:semicolon
macro_line|#endif
eof
