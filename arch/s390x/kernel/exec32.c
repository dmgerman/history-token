multiline_comment|/*&n; * Support for 32-bit Linux for S390 ELF binaries.&n; *&n; * Copyright (C) 2000 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; * Author(s): Gerhard Tonn (ton@de.ibm.com)&n; *&n; * Seperated from binfmt_elf32.c to reduce exports for module enablement.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/binfmts.h&gt;
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#ifdef CONFIG_KMOD
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#endif
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
DECL|macro|STACK_TOP
macro_line|#undef STACK_TOP
DECL|macro|STACK_TOP
mdefine_line|#define STACK_TOP TASK31_SIZE
DECL|function|setup_arg_pages32
r_int
id|setup_arg_pages32
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
id|STACK_TOP
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
op_logical_neg
id|vm_enough_memory
c_func
(paren
(paren
id|STACK_TOP
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
id|STACK_TOP
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
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|mpnt-&gt;shared
)paren
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
id|mm
comma
id|mpnt
)paren
suffix:semicolon
id|mm-&gt;total_vm
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
DECL|variable|setup_arg_pages32
id|EXPORT_SYMBOL
c_func
(paren
id|setup_arg_pages32
)paren
suffix:semicolon
eof
