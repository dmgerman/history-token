multiline_comment|/* &n; * Written 2000,2002 by Andi Kleen. &n; * &n; * Losely based on the sparc64 and IA64 32bit emulation loaders.&n; * This tricks binfmt_elf.c into loading 32bit binaries using lots &n; * of ugly preprocessor tricks. Talk about very very poor man&squot;s inheritance.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/config.h&gt; 
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/rwsem.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/segment.h&gt; 
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/user32.h&gt;
macro_line|#include &lt;asm/sigcontext32.h&gt;
macro_line|#include &lt;asm/fpu32.h&gt;
macro_line|#include &lt;asm/i387.h&gt;
r_struct
id|file
suffix:semicolon
r_struct
id|elf_phdr
suffix:semicolon
DECL|macro|IA32_EMULATOR
mdefine_line|#define IA32_EMULATOR 1
DECL|macro|IA32_PAGE_OFFSET
mdefine_line|#define IA32_PAGE_OFFSET 0xE0000000
DECL|macro|IA32_STACK_TOP
mdefine_line|#define IA32_STACK_TOP IA32_PAGE_OFFSET
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE&t;&t;(IA32_PAGE_OFFSET/3 + 0x1000000)
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
DECL|struct|timeval32
r_struct
id|timeval32
(brace
DECL|member|tv_sec
DECL|member|tv_usec
r_int
id|tv_sec
comma
id|tv_usec
suffix:semicolon
)brace
suffix:semicolon
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
id|timeval32
id|pr_utime
suffix:semicolon
multiline_comment|/* User time */
DECL|member|pr_stime
r_struct
id|timeval32
id|pr_stime
suffix:semicolon
multiline_comment|/* System time */
DECL|member|pr_cutime
r_struct
id|timeval32
id|pr_cutime
suffix:semicolon
multiline_comment|/* Cumulative user time */
DECL|member|pr_cstime
r_struct
id|timeval32
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
DECL|macro|dump_fpu
mdefine_line|#define dump_fpu dump_fpu_ia32
DECL|macro|__ASM_X86_64_ELF_H
mdefine_line|#define __ASM_X86_64_ELF_H 1
macro_line|#include &lt;asm/ia32.h&gt;
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
mdefine_line|#define SET_PERSONALITY(ex, ibcs2)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;set_personality((ibcs2)?PER_SVR4:current-&gt;personality);&t;&bslash;&n;} while (0)
multiline_comment|/* Override some function names */
DECL|macro|elf_format
mdefine_line|#define elf_format&t;&t;&t;elf32_format
DECL|macro|init_elf_binfmt
mdefine_line|#define init_elf_binfmt&t;&t;&t;init_elf32_binfmt
DECL|macro|exit_elf_binfmt
mdefine_line|#define exit_elf_binfmt&t;&t;&t;exit_elf32_binfmt
DECL|macro|load_elf_binary
mdefine_line|#define load_elf_binary load_elf32_binary
DECL|macro|CONFIG_BINFMT_ELF
macro_line|#undef CONFIG_BINFMT_ELF
macro_line|#ifdef CONFIG_BINFMT_ELF32
DECL|macro|CONFIG_BINFMT_ELF
macro_line|# define CONFIG_BINFMT_ELF&t;&t;CONFIG_BINFMT_ELF32
macro_line|#endif
DECL|macro|CONFIG_BINFMT_ELF_MODULE
macro_line|#undef CONFIG_BINFMT_ELF_MODULE
macro_line|#ifdef CONFIG_BINFMT_ELF32_MODULE
DECL|macro|CONFIG_BINFMT_ELF_MODULE
macro_line|# define CONFIG_BINFMT_ELF_MODULE&t;CONFIG_BINFMT_ELF32_MODULE
macro_line|#endif
DECL|macro|ELF_PLAT_INIT
mdefine_line|#define ELF_PLAT_INIT(r)&t;&t;elf32_init(r)
DECL|macro|setup_arg_pages
mdefine_line|#define setup_arg_pages(bprm)&t;&t;ia32_setup_arg_pages(bprm)
DECL|macro|start_thread
macro_line|#undef start_thread
DECL|macro|start_thread
mdefine_line|#define start_thread(regs,new_rip,new_rsp) do { &bslash;&n;&t;__asm__(&quot;movl %0,%%fs&quot;: :&quot;r&quot; (0)); &bslash;&n;&t;__asm__(&quot;movl %0,%%es; movl %0,%%ds&quot;: :&quot;r&quot; (__USER32_DS)); &bslash;&n;&t;wrmsrl(MSR_KERNEL_GS_BASE, 0); &bslash;&n;&t;(regs)-&gt;rip = (new_rip); &bslash;&n;&t;(regs)-&gt;rsp = (new_rsp); &bslash;&n;&t;(regs)-&gt;eflags = 0x200; &bslash;&n;&t;(regs)-&gt;cs = __USER32_CS; &bslash;&n;&t;(regs)-&gt;ss = __USER32_DS; &bslash;&n;&t;set_fs(USER_DS); &bslash;&n;} while(0) 
DECL|macro|elf_map
mdefine_line|#define elf_map elf32_map
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
DECL|macro|elf_caddr_t
mdefine_line|#define elf_caddr_t __u32
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
id|set_thread_flag
c_func
(paren
id|TIF_IA32
)paren
suffix:semicolon
)brace
r_extern
r_void
id|put_dirty_page
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|address
)paren
suffix:semicolon
DECL|function|ia32_setup_arg_pages
r_int
id|ia32_setup_arg_pages
c_func
(paren
r_struct
id|linux_binprm
op_star
id|bprm
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
id|down_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
(brace
id|mpnt-&gt;vm_mm
op_assign
id|current-&gt;mm
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
id|mpnt-&gt;vm_page_prot
op_assign
id|PAGE_COPY
suffix:semicolon
id|mpnt-&gt;vm_flags
op_assign
id|VM_STACK_FLAGS
suffix:semicolon
id|mpnt-&gt;vm_ops
op_assign
l_int|NULL
suffix:semicolon
id|mpnt-&gt;vm_pgoff
op_assign
l_int|0
suffix:semicolon
id|mpnt-&gt;vm_file
op_assign
l_int|NULL
suffix:semicolon
id|mpnt-&gt;vm_private_data
op_assign
(paren
r_void
op_star
)paren
l_int|0
suffix:semicolon
id|insert_vm_struct
c_func
(paren
id|current-&gt;mm
comma
id|mpnt
)paren
suffix:semicolon
id|current-&gt;mm-&gt;total_vm
op_assign
(paren
id|mpnt-&gt;vm_end
op_minus
id|mpnt-&gt;vm_start
)paren
op_rshift
id|PAGE_SHIFT
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
id|current-&gt;mm-&gt;rss
op_increment
suffix:semicolon
id|put_dirty_page
c_func
(paren
id|current
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
id|current-&gt;mm-&gt;mmap_sem
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
r_if
c_cond
(paren
id|prot
op_amp
id|PROT_READ
)paren
id|prot
op_or_assign
id|PROT_EXEC
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
op_or
id|MAP_32BIT
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
DECL|function|dump_fpu_ia32
r_int
id|dump_fpu_ia32
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
id|elf_fpregset_t
op_star
id|fp
)paren
(brace
r_struct
id|_fpstate_ia32
op_star
id|fpu
op_assign
(paren
r_void
op_star
)paren
id|fp
suffix:semicolon
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
id|mm_segment_t
id|oldfs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
r_int
id|ret
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
(paren
id|test_thread_flag
c_func
(paren
id|TIF_IA32
)paren
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
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
id|ret
op_assign
id|save_i387_ia32
c_func
(paren
id|current
comma
id|fpu
comma
id|regs
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Correct for i386 bug. It puts the fop into the upper 16bits of &n;&t;   the tag word (like FXSAVE), not into the fcs*/
id|fpu-&gt;cssel
op_or_assign
id|fpu-&gt;tag
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
id|ret
suffix:semicolon
)brace
eof
