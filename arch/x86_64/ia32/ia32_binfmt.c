multiline_comment|/* &n; * Written 2000 by Andi Kleen. &n; * &n; * Losely based on the sparc64 and IA64 32bit emulation loaders.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/config.h&gt; 
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/rwsem.h&gt;
macro_line|#include &lt;asm/segment.h&gt; 
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
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
singleline_comment|//#define USE_ELF_CORE_DUMP
DECL|macro|__ASM_X86_64_ELF_H
mdefine_line|#define __ASM_X86_64_ELF_H 1
macro_line|#include &lt;asm/ia32.h&gt;
macro_line|#include &lt;linux/elf.h&gt;
DECL|typedef|elf_greg_t
r_typedef
id|__u32
id|elf_greg_t
suffix:semicolon
DECL|typedef|elf_gregset_t
r_typedef
id|elf_greg_t
id|elf_gregset_t
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* FIXME -- wrong */
DECL|typedef|elf_fpregset_t
r_typedef
r_struct
id|user_i387_ia32_struct
id|elf_fpregset_t
suffix:semicolon
DECL|typedef|elf_fpxregset_t
r_typedef
r_struct
id|user_i387_struct
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
mdefine_line|#define start_thread(regs,new_rip,new_rsp) do { &bslash;&n;&t;__asm__(&quot;movl %0,%%fs&quot;: :&quot;r&quot; (0)); &bslash;&n;&t;__asm__(&quot;movl %0,%%es; movl %0,%%ds&quot;: :&quot;r&quot; (__USER32_DS)); &bslash;&n;&t;wrmsrl(MSR_KERNEL_GS_BASE, 0); &bslash;&n;&t;set_thread_flag(TIF_IA32); &bslash;&n;&t;(regs)-&gt;rip = (new_rip); &bslash;&n;&t;(regs)-&gt;rsp = (new_rsp); &bslash;&n;&t;(regs)-&gt;eflags = 0x200; &bslash;&n;&t;(regs)-&gt;cs = __USER32_CS; &bslash;&n;&t;(regs)-&gt;ss = __USER32_DS; &bslash;&n;&t;set_fs(USER_DS); &bslash;&n;} while(0) 
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
id|current-&gt;thread.fs
op_assign
l_int|0
suffix:semicolon
id|current-&gt;thread.gs
op_assign
l_int|0
suffix:semicolon
id|current-&gt;thread.fsindex
op_assign
l_int|0
suffix:semicolon
id|current-&gt;thread.gsindex
op_assign
l_int|0
suffix:semicolon
id|current-&gt;thread.ds
op_assign
id|__USER_DS
suffix:semicolon
id|current-&gt;thread.es
op_eq
id|__USER_DS
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
eof