multiline_comment|/*&n; * IA-32 ELF support.&n; *&n; * Copyright (C) 1999 Arun Sharma &lt;arun.sharma@intel.com&gt;&n; * Copyright (C) 2001 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; *&n; * 06/16/00&t;A. Mallick&t;initialize csd/ssd/tssd/cflg for ia32_load_state&n; * 04/13/01&t;D. Mosberger&t;dropped saving tssd in ar.k1---it&squot;s not needed&n; * 09/14/01&t;D. Mosberger&t;fixed memory management for gdt/tss page&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/security.h&gt;
macro_line|#include &lt;asm/param.h&gt;
macro_line|#include &lt;asm/signal.h&gt;
macro_line|#include &quot;ia32priv.h&quot;
macro_line|#include &quot;elfcore32.h&quot;
DECL|macro|CONFIG_BINFMT_ELF32
mdefine_line|#define CONFIG_BINFMT_ELF32
multiline_comment|/* Override some function names */
DECL|macro|start_thread
macro_line|#undef start_thread
DECL|macro|start_thread
mdefine_line|#define start_thread&t;&t;&t;ia32_start_thread
DECL|macro|elf_format
mdefine_line|#define elf_format&t;&t;&t;elf32_format
DECL|macro|init_elf_binfmt
mdefine_line|#define init_elf_binfmt&t;&t;&t;init_elf32_binfmt
DECL|macro|exit_elf_binfmt
mdefine_line|#define exit_elf_binfmt&t;&t;&t;exit_elf32_binfmt
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
DECL|macro|CLOCKS_PER_SEC
macro_line|#undef CLOCKS_PER_SEC
DECL|macro|CLOCKS_PER_SEC
mdefine_line|#define CLOCKS_PER_SEC&t;IA32_CLOCKS_PER_SEC
r_extern
r_void
id|ia64_elf32_init
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_static
r_void
id|elf32_set_personality
(paren
r_void
)paren
suffix:semicolon
DECL|macro|setup_arg_pages
mdefine_line|#define setup_arg_pages(bprm)&t;&t;ia32_setup_arg_pages(bprm)
DECL|macro|elf_map
mdefine_line|#define elf_map&t;&t;&t;&t;elf32_map
DECL|macro|SET_PERSONALITY
macro_line|#undef SET_PERSONALITY
DECL|macro|SET_PERSONALITY
mdefine_line|#define SET_PERSONALITY(ex, ibcs2)&t;elf32_set_personality()
multiline_comment|/* Ugly but avoids duplication */
macro_line|#include &quot;../../../fs/binfmt_elf.c&quot;
r_extern
r_struct
id|page
op_star
id|ia32_shared_page
(braket
)braket
suffix:semicolon
r_extern
r_int
r_int
op_star
id|ia32_gdt
suffix:semicolon
r_struct
id|page
op_star
DECL|function|ia32_install_shared_page
id|ia32_install_shared_page
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
comma
r_int
id|no_share
)paren
(brace
r_struct
id|page
op_star
id|pg
op_assign
id|ia32_shared_page
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
suffix:semicolon
id|get_page
c_func
(paren
id|pg
)paren
suffix:semicolon
r_return
id|pg
suffix:semicolon
)brace
DECL|variable|ia32_shared_page_vm_ops
r_static
r_struct
id|vm_operations_struct
id|ia32_shared_page_vm_ops
op_assign
(brace
dot
id|nopage
op_assign
id|ia32_install_shared_page
)brace
suffix:semicolon
r_void
DECL|function|ia64_elf32_init
id|ia64_elf32_init
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
multiline_comment|/*&n;&t; * Map GDT below 4GB, where the processor can find it.  We need to map&n;&t; * it with privilege level 3 because the IVE uses non-privileged accesses to these&n;&t; * tables.  IA-32 segmentation is used to protect against IA-32 accesses to them.&n;&t; */
id|vma
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
id|vma
)paren
(brace
id|vma-&gt;vm_mm
op_assign
id|current-&gt;mm
suffix:semicolon
id|vma-&gt;vm_start
op_assign
id|IA32_GDT_OFFSET
suffix:semicolon
id|vma-&gt;vm_end
op_assign
id|vma-&gt;vm_start
op_plus
id|PAGE_SIZE
suffix:semicolon
id|vma-&gt;vm_page_prot
op_assign
id|PAGE_SHARED
suffix:semicolon
id|vma-&gt;vm_flags
op_assign
id|VM_READ
op_or
id|VM_MAYREAD
suffix:semicolon
id|vma-&gt;vm_ops
op_assign
op_amp
id|ia32_shared_page_vm_ops
suffix:semicolon
id|vma-&gt;vm_pgoff
op_assign
l_int|0
suffix:semicolon
id|vma-&gt;vm_file
op_assign
l_int|NULL
suffix:semicolon
id|vma-&gt;vm_private_data
op_assign
l_int|NULL
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
(brace
id|insert_vm_struct
c_func
(paren
id|current-&gt;mm
comma
id|vma
)paren
suffix:semicolon
)brace
id|up_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Install LDT as anonymous memory.  This gives us all-zero segment descriptors&n;&t; * until a task modifies them via modify_ldt().&n;&t; */
id|vma
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
id|vma
)paren
(brace
id|vma-&gt;vm_mm
op_assign
id|current-&gt;mm
suffix:semicolon
id|vma-&gt;vm_start
op_assign
id|IA32_LDT_OFFSET
suffix:semicolon
id|vma-&gt;vm_end
op_assign
id|vma-&gt;vm_start
op_plus
id|PAGE_ALIGN
c_func
(paren
id|IA32_LDT_ENTRIES
op_star
id|IA32_LDT_ENTRY_SIZE
)paren
suffix:semicolon
id|vma-&gt;vm_page_prot
op_assign
id|PAGE_SHARED
suffix:semicolon
id|vma-&gt;vm_flags
op_assign
id|VM_READ
op_or
id|VM_WRITE
op_or
id|VM_MAYREAD
op_or
id|VM_MAYWRITE
suffix:semicolon
id|vma-&gt;vm_ops
op_assign
l_int|NULL
suffix:semicolon
id|vma-&gt;vm_pgoff
op_assign
l_int|0
suffix:semicolon
id|vma-&gt;vm_file
op_assign
l_int|NULL
suffix:semicolon
id|vma-&gt;vm_private_data
op_assign
l_int|NULL
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
(brace
id|insert_vm_struct
c_func
(paren
id|current-&gt;mm
comma
id|vma
)paren
suffix:semicolon
)brace
id|up_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
)brace
id|ia64_psr
c_func
(paren
id|regs
)paren
op_member_access_from_pointer
id|ac
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* turn off alignment checking */
id|regs-&gt;loadrs
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; *  According to the ABI %edx points to an `atexit&squot; handler.  Since we don&squot;t have&n;&t; *  one we&squot;ll set it to 0 and initialize all the other registers just to make&n;&t; *  things more deterministic, ala the i386 implementation.&n;&t; */
id|regs-&gt;r8
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* %eax */
id|regs-&gt;r11
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* %ebx */
id|regs-&gt;r9
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* %ecx */
id|regs-&gt;r10
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* %edx */
id|regs-&gt;r13
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* %ebp */
id|regs-&gt;r14
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* %esi */
id|regs-&gt;r15
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* %edi */
id|current-&gt;thread.eflag
op_assign
id|IA32_EFLAG
suffix:semicolon
id|current-&gt;thread.fsr
op_assign
id|IA32_FSR_DEFAULT
suffix:semicolon
id|current-&gt;thread.fcr
op_assign
id|IA32_FCR_DEFAULT
suffix:semicolon
id|current-&gt;thread.fir
op_assign
l_int|0
suffix:semicolon
id|current-&gt;thread.fdr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Setup GDTD.  Note: GDTD is the descrambled version of the pseudo-descriptor&n;&t; * format defined by Figure 3-11 &quot;Pseudo-Descriptor Format&quot; in the IA-32&n;&t; * architecture manual. Also note that the only fields that are not ignored are&n;&t; * `base&squot;, `limit&squot;, &squot;G&squot;, `P&squot; (must be 1) and `S&squot; (must be 0).&n;&t; */
id|regs-&gt;r31
op_assign
id|IA32_SEG_UNSCRAMBLE
c_func
(paren
id|IA32_SEG_DESCRIPTOR
c_func
(paren
id|IA32_GDT_OFFSET
comma
id|IA32_PAGE_SIZE
op_minus
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
)paren
suffix:semicolon
multiline_comment|/* Setup the segment selectors */
id|regs-&gt;r16
op_assign
(paren
id|__USER_DS
op_lshift
l_int|16
)paren
op_or
id|__USER_DS
suffix:semicolon
multiline_comment|/* ES == DS, GS, FS are zero */
id|regs-&gt;r17
op_assign
(paren
id|__USER_DS
op_lshift
l_int|16
)paren
op_or
id|__USER_CS
suffix:semicolon
multiline_comment|/* SS, CS; ia32_load_state() sets TSS and LDT */
id|ia32_load_segment_descriptors
c_func
(paren
id|current
)paren
suffix:semicolon
id|ia32_load_state
c_func
(paren
id|current
)paren
suffix:semicolon
)brace
r_int
DECL|function|ia32_setup_arg_pages
id|ia32_setup_arg_pages
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
id|put_dirty_page
c_func
(paren
id|current
comma
id|page
comma
id|stack_base
comma
id|PAGE_COPY
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
r_void
DECL|function|elf32_set_personality
id|elf32_set_personality
(paren
r_void
)paren
(brace
id|set_personality
c_func
(paren
id|PER_LINUX32
)paren
suffix:semicolon
id|current-&gt;thread.map_base
op_assign
id|IA32_PAGE_OFFSET
op_div
l_int|3
suffix:semicolon
id|current-&gt;thread.task_size
op_assign
id|IA32_PAGE_OFFSET
suffix:semicolon
multiline_comment|/* use what Linux/x86 uses... */
id|current-&gt;thread.flags
op_or_assign
id|IA64_THREAD_XSTACK
suffix:semicolon
multiline_comment|/* data must be executable */
id|set_fs
c_func
(paren
id|USER_DS
)paren
suffix:semicolon
multiline_comment|/* set addr limit for new TASK_SIZE */
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
id|pgoff
op_assign
(paren
id|eppnt-&gt;p_vaddr
)paren
op_amp
op_complement
id|IA32_PAGE_MASK
suffix:semicolon
r_return
id|ia32_do_mmap
c_func
(paren
id|filep
comma
(paren
id|addr
op_amp
id|IA32_PAGE_MASK
)paren
comma
id|eppnt-&gt;p_filesz
op_plus
id|pgoff
comma
id|prot
comma
id|type
comma
id|eppnt-&gt;p_offset
op_minus
id|pgoff
)paren
suffix:semicolon
)brace
eof
