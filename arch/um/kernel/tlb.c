multiline_comment|/* &n; * Copyright (C) 2000 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/sched.h&quot;
macro_line|#include &quot;linux/slab.h&quot;
macro_line|#include &quot;linux/bootmem.h&quot;
macro_line|#include &quot;asm-generic/tlb.h&quot;
macro_line|#include &quot;asm/pgtable.h&quot;
macro_line|#include &quot;asm/pgalloc.h&quot;
macro_line|#include &quot;asm/a.out.h&quot;
macro_line|#include &quot;asm/processor.h&quot;
macro_line|#include &quot;asm/mmu_context.h&quot;
macro_line|#include &quot;asm/uaccess.h&quot;
macro_line|#include &quot;asm/atomic.h&quot;
macro_line|#include &quot;mem_user.h&quot;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;kern.h&quot;
macro_line|#include &quot;tlb.h&quot;
macro_line|#include &quot;os.h&quot;
DECL|function|fix_range
r_static
r_void
id|fix_range
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|start_addr
comma
r_int
r_int
id|end_addr
comma
r_int
id|force
)paren
(brace
id|pgd_t
op_star
id|npgd
suffix:semicolon
id|pmd_t
op_star
id|npmd
suffix:semicolon
id|pte_t
op_star
id|npte
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
r_int
id|r
comma
id|w
comma
id|x
comma
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|current-&gt;thread.extern_pid
op_ne
op_minus
l_int|1
)paren
op_logical_and
(paren
id|current-&gt;thread.extern_pid
op_ne
id|os_getpid
c_func
(paren
)paren
)paren
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;fix_range fixing wrong address space, current = 0x%p&quot;
comma
id|current
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mm
op_eq
l_int|NULL
)paren
(brace
r_return
suffix:semicolon
)brace
r_for
c_loop
(paren
id|addr
op_assign
id|start_addr
suffix:semicolon
id|addr
OL
id|end_addr
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|addr
op_eq
id|TASK_SIZE
)paren
(brace
multiline_comment|/* Skip over kernel text, kernel data, and physical&n;&t;&t;&t; * memory, which don&squot;t have ptes, plus kernel virtual&n;&t;&t;&t; * memory, which is flushed separately, and remap&n;&t;&t;&t; * the process stack.  The only way to get here is&n;&t;&t;&t; * if (end_addr == STACK_TOP) &gt; TASK_SIZE, which is&n;&t;&t;&t; * only true in the honeypot case.&n;&t;&t;&t; */
id|addr
op_assign
id|STACK_TOP
op_minus
id|ABOVE_KMEM
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|npgd
op_assign
id|pgd_offset
c_func
(paren
id|mm
comma
id|addr
)paren
suffix:semicolon
id|npmd
op_assign
id|pmd_offset
c_func
(paren
id|npgd
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd_present
c_func
(paren
op_star
id|npmd
)paren
)paren
(brace
id|npte
op_assign
id|pte_offset_kernel
c_func
(paren
id|npmd
comma
id|addr
)paren
suffix:semicolon
id|r
op_assign
id|pte_read
c_func
(paren
op_star
id|npte
)paren
suffix:semicolon
id|w
op_assign
id|pte_write
c_func
(paren
op_star
id|npte
)paren
suffix:semicolon
id|x
op_assign
id|pte_exec
c_func
(paren
op_star
id|npte
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte_dirty
c_func
(paren
op_star
id|npte
)paren
)paren
(brace
id|w
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|pte_young
c_func
(paren
op_star
id|npte
)paren
)paren
(brace
id|r
op_assign
l_int|0
suffix:semicolon
id|w
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|force
op_logical_or
id|pte_newpage
c_func
(paren
op_star
id|npte
)paren
)paren
(brace
id|err
op_assign
id|unmap
c_func
(paren
(paren
r_void
op_star
)paren
id|addr
comma
id|PAGE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;munmap failed, errno = %d&bslash;n&quot;
comma
op_minus
id|err
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pte_present
c_func
(paren
op_star
id|npte
)paren
)paren
(brace
id|map
c_func
(paren
id|addr
comma
id|pte_val
c_func
(paren
op_star
id|npte
)paren
op_amp
id|PAGE_MASK
comma
id|PAGE_SIZE
comma
id|r
comma
id|w
comma
id|x
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|pte_newprot
c_func
(paren
op_star
id|npte
)paren
)paren
(brace
id|protect
c_func
(paren
id|addr
comma
id|PAGE_SIZE
comma
id|r
comma
id|w
comma
id|x
comma
l_int|1
)paren
suffix:semicolon
)brace
op_star
id|npte
op_assign
id|pte_mkuptodate
c_func
(paren
op_star
id|npte
)paren
suffix:semicolon
id|addr
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|force
op_logical_or
id|pmd_newpage
c_func
(paren
op_star
id|npmd
)paren
)paren
(brace
id|err
op_assign
id|unmap
c_func
(paren
(paren
r_void
op_star
)paren
id|addr
comma
id|PMD_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;munmap failed, errno = %d&bslash;n&quot;
comma
op_minus
id|err
)paren
suffix:semicolon
)brace
id|pmd_mkuptodate
c_func
(paren
op_star
id|npmd
)paren
suffix:semicolon
)brace
id|addr
op_add_assign
id|PMD_SIZE
suffix:semicolon
)brace
)brace
)brace
DECL|variable|vmchange_seq
id|atomic_t
id|vmchange_seq
op_assign
id|ATOMIC_INIT
c_func
(paren
l_int|1
)paren
suffix:semicolon
DECL|function|flush_kernel_range
r_void
id|flush_kernel_range
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
comma
r_int
id|update_seq
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
suffix:semicolon
id|pgd_t
op_star
id|pgd
suffix:semicolon
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pte_t
op_star
id|pte
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
r_int
id|updated
op_assign
l_int|0
comma
id|err
suffix:semicolon
id|mm
op_assign
op_amp
id|init_mm
suffix:semicolon
r_for
c_loop
(paren
id|addr
op_assign
id|start_vm
suffix:semicolon
id|addr
OL
id|end_vm
suffix:semicolon
)paren
(brace
id|pgd
op_assign
id|pgd_offset
c_func
(paren
id|mm
comma
id|addr
)paren
suffix:semicolon
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pgd
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd_present
c_func
(paren
op_star
id|pmd
)paren
)paren
(brace
id|pte
op_assign
id|pte_offset_kernel
c_func
(paren
id|pmd
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte_present
c_func
(paren
op_star
id|pte
)paren
op_logical_or
id|pte_newpage
c_func
(paren
op_star
id|pte
)paren
)paren
(brace
id|updated
op_assign
l_int|1
suffix:semicolon
id|err
op_assign
id|unmap
c_func
(paren
(paren
r_void
op_star
)paren
id|addr
comma
id|PAGE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;munmap failed, errno = %d&bslash;n&quot;
comma
op_minus
id|err
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pte_present
c_func
(paren
op_star
id|pte
)paren
)paren
(brace
id|map
c_func
(paren
id|addr
comma
id|pte_val
c_func
(paren
op_star
id|pte
)paren
op_amp
id|PAGE_MASK
comma
id|PAGE_SIZE
comma
l_int|1
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|pte_newprot
c_func
(paren
op_star
id|pte
)paren
)paren
(brace
id|updated
op_assign
l_int|1
suffix:semicolon
id|protect
c_func
(paren
id|addr
comma
id|PAGE_SIZE
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
)brace
id|addr
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|pmd_newpage
c_func
(paren
op_star
id|pmd
)paren
)paren
(brace
id|updated
op_assign
l_int|1
suffix:semicolon
id|err
op_assign
id|unmap
c_func
(paren
(paren
r_void
op_star
)paren
id|addr
comma
id|PMD_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;munmap failed, errno = %d&bslash;n&quot;
comma
op_minus
id|err
)paren
suffix:semicolon
)brace
)brace
id|addr
op_add_assign
id|PMD_SIZE
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|updated
op_logical_and
id|update_seq
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|vmchange_seq
)paren
suffix:semicolon
)brace
)brace
DECL|function|flush_tlb_kernel_range
r_void
id|flush_tlb_kernel_range
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
(brace
id|flush_kernel_range
c_func
(paren
id|start
comma
id|end
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|protect_vm_page
r_static
r_void
id|protect_vm_page
c_func
(paren
r_int
r_int
id|addr
comma
r_int
id|w
comma
r_int
id|must_succeed
)paren
(brace
r_int
id|err
suffix:semicolon
id|err
op_assign
id|protect
c_func
(paren
id|addr
comma
id|PAGE_SIZE
comma
l_int|1
comma
id|w
comma
l_int|1
comma
id|must_succeed
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_eq
l_int|0
)paren
(brace
r_return
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|err
op_eq
op_minus
id|EFAULT
)paren
op_logical_or
(paren
id|err
op_eq
op_minus
id|ENOMEM
)paren
)paren
(brace
id|flush_tlb_kernel_range
c_func
(paren
id|addr
comma
id|addr
op_plus
id|PAGE_SIZE
)paren
suffix:semicolon
id|protect_vm_page
c_func
(paren
id|addr
comma
id|w
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
id|panic
c_func
(paren
l_string|&quot;protect_vm_page : protect failed, errno = %d&bslash;n&quot;
comma
id|err
)paren
suffix:semicolon
)brace
DECL|function|mprotect_kernel_vm
r_void
id|mprotect_kernel_vm
c_func
(paren
r_int
id|w
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
suffix:semicolon
id|pgd_t
op_star
id|pgd
suffix:semicolon
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pte_t
op_star
id|pte
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
id|mm
op_assign
op_amp
id|init_mm
suffix:semicolon
r_for
c_loop
(paren
id|addr
op_assign
id|start_vm
suffix:semicolon
id|addr
OL
id|end_vm
suffix:semicolon
)paren
(brace
id|pgd
op_assign
id|pgd_offset
c_func
(paren
id|mm
comma
id|addr
)paren
suffix:semicolon
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pgd
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd_present
c_func
(paren
op_star
id|pmd
)paren
)paren
(brace
id|pte
op_assign
id|pte_offset_kernel
c_func
(paren
id|pmd
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pte_present
c_func
(paren
op_star
id|pte
)paren
)paren
(brace
id|protect_vm_page
c_func
(paren
id|addr
comma
id|w
comma
l_int|0
)paren
suffix:semicolon
)brace
id|addr
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
r_else
id|addr
op_add_assign
id|PMD_SIZE
suffix:semicolon
)brace
)brace
DECL|function|flush_tlb_kernel_vm
r_void
id|flush_tlb_kernel_vm
c_func
(paren
r_void
)paren
(brace
id|flush_tlb_kernel_range
c_func
(paren
id|start_vm
comma
id|end_vm
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_range
r_void
id|flush_tlb_range
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
(brace
r_if
c_cond
(paren
id|vma-&gt;vm_mm
op_ne
id|current-&gt;mm
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/* Assumes that the range start ... end is entirely within&n;&t; * either process memory or kernel vm&n;&t; */
r_if
c_cond
(paren
(paren
id|start
op_ge
id|start_vm
)paren
op_logical_and
(paren
id|start
OL
id|end_vm
)paren
)paren
(brace
id|flush_kernel_range
c_func
(paren
id|start
comma
id|end
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
id|fix_range
c_func
(paren
id|vma-&gt;vm_mm
comma
id|start
comma
id|end
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_mm
r_void
id|flush_tlb_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_int
r_int
id|seq
suffix:semicolon
r_if
c_cond
(paren
id|mm
op_ne
id|current-&gt;mm
)paren
(brace
r_return
suffix:semicolon
)brace
id|fix_range
c_func
(paren
id|mm
comma
l_int|0
comma
id|STACK_TOP
comma
l_int|0
)paren
suffix:semicolon
id|seq
op_assign
id|atomic_read
c_func
(paren
op_amp
id|vmchange_seq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;thread.vm_seq
op_eq
id|seq
)paren
(brace
r_return
suffix:semicolon
)brace
id|current-&gt;thread.vm_seq
op_assign
id|seq
suffix:semicolon
id|flush_kernel_range
c_func
(paren
id|start_vm
comma
id|end_vm
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_page
r_void
id|flush_tlb_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
)paren
(brace
id|address
op_and_assign
id|PAGE_MASK
suffix:semicolon
id|flush_tlb_range
c_func
(paren
id|vma
comma
id|address
comma
id|address
op_plus
id|PAGE_SIZE
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_all
r_void
id|flush_tlb_all
c_func
(paren
r_void
)paren
(brace
id|flush_tlb_mm
c_func
(paren
id|current-&gt;mm
)paren
suffix:semicolon
)brace
DECL|function|force_flush_all
r_void
id|force_flush_all
c_func
(paren
r_void
)paren
(brace
id|fix_range
c_func
(paren
id|current-&gt;mm
comma
l_int|0
comma
id|STACK_TOP
comma
l_int|1
)paren
suffix:semicolon
id|flush_kernel_range
c_func
(paren
id|start_vm
comma
id|end_vm
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|pgd_offset_proc
id|pgd_t
op_star
id|pgd_offset_proc
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|address
)paren
(brace
r_return
id|pgd_offset
c_func
(paren
id|mm
comma
id|address
)paren
suffix:semicolon
)brace
DECL|function|pmd_offset_proc
id|pmd_t
op_star
id|pmd_offset_proc
c_func
(paren
id|pgd_t
op_star
id|pgd
comma
r_int
r_int
id|address
)paren
(brace
r_return
id|pmd_offset
c_func
(paren
id|pgd
comma
id|address
)paren
suffix:semicolon
)brace
DECL|function|pte_offset_proc
id|pte_t
op_star
id|pte_offset_proc
c_func
(paren
id|pmd_t
op_star
id|pmd
comma
r_int
r_int
id|address
)paren
(brace
r_return
id|pte_offset_kernel
c_func
(paren
id|pmd
comma
id|address
)paren
suffix:semicolon
)brace
DECL|function|addr_pte
id|pte_t
op_star
id|addr_pte
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
r_int
id|addr
)paren
(brace
r_return
id|pte_offset_kernel
c_func
(paren
id|pmd_offset
c_func
(paren
id|pgd_offset
c_func
(paren
id|task-&gt;mm
comma
id|addr
)paren
comma
id|addr
)paren
comma
id|addr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
