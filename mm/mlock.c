multiline_comment|/*&n; *&t;linux/mm/mlock.c&n; *&n; *  (C) Copyright 1995 Linus Torvalds&n; *  (C) Copyright 2002 Christoph Hellwig&n; */
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
DECL|function|mlock_fixup
r_static
r_int
id|mlock_fixup
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
comma
r_int
r_int
id|newflags
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|vma-&gt;vm_mm
suffix:semicolon
r_int
id|pages
comma
id|error
suffix:semicolon
r_if
c_cond
(paren
id|newflags
op_eq
id|vma-&gt;vm_flags
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|start
op_ne
id|vma-&gt;vm_start
)paren
(brace
id|error
op_assign
id|split_vma
c_func
(paren
id|mm
comma
id|vma
comma
id|start
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
r_if
c_cond
(paren
id|end
op_ne
id|vma-&gt;vm_end
)paren
(brace
id|error
op_assign
id|split_vma
c_func
(paren
id|mm
comma
id|vma
comma
id|end
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
)paren
suffix:semicolon
id|vma-&gt;vm_flags
op_assign
id|newflags
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Keep track of amount of locked VM.&n;&t; */
id|pages
op_assign
(paren
id|end
op_minus
id|start
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|newflags
op_amp
id|VM_LOCKED
)paren
(brace
id|pages
op_assign
op_minus
id|pages
suffix:semicolon
id|make_pages_present
c_func
(paren
id|start
comma
id|end
)paren
suffix:semicolon
)brace
id|vma-&gt;vm_mm-&gt;locked_vm
op_sub_assign
id|pages
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|do_mlock
r_static
r_int
id|do_mlock
c_func
(paren
r_int
r_int
id|start
comma
r_int
id|len
comma
r_int
id|on
)paren
(brace
r_int
r_int
id|nstart
comma
id|end
comma
id|tmp
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|vma
comma
op_star
id|next
suffix:semicolon
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
id|on
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_IPC_LOCK
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|len
op_assign
id|PAGE_ALIGN
c_func
(paren
id|len
)paren
suffix:semicolon
id|end
op_assign
id|start
op_plus
id|len
suffix:semicolon
r_if
c_cond
(paren
id|end
OL
id|start
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|end
op_eq
id|start
)paren
r_return
l_int|0
suffix:semicolon
id|vma
op_assign
id|find_vma
c_func
(paren
id|current-&gt;mm
comma
id|start
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vma
op_logical_or
id|vma-&gt;vm_start
OG
id|start
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_for
c_loop
(paren
id|nstart
op_assign
id|start
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
r_int
id|newflags
suffix:semicolon
multiline_comment|/* Here we know that  vma-&gt;vm_start &lt;= nstart &lt; vma-&gt;vm_end. */
id|newflags
op_assign
id|vma-&gt;vm_flags
op_or
id|VM_LOCKED
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|on
)paren
id|newflags
op_and_assign
op_complement
id|VM_LOCKED
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_end
op_ge
id|end
)paren
(brace
id|error
op_assign
id|mlock_fixup
c_func
(paren
id|vma
comma
id|nstart
comma
id|end
comma
id|newflags
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|tmp
op_assign
id|vma-&gt;vm_end
suffix:semicolon
id|next
op_assign
id|vma-&gt;vm_next
suffix:semicolon
id|error
op_assign
id|mlock_fixup
c_func
(paren
id|vma
comma
id|nstart
comma
id|tmp
comma
id|newflags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_break
suffix:semicolon
id|nstart
op_assign
id|tmp
suffix:semicolon
id|vma
op_assign
id|next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vma
op_logical_or
id|vma-&gt;vm_start
op_ne
id|nstart
)paren
(brace
id|error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|function|sys_mlock
id|asmlinkage
r_int
id|sys_mlock
c_func
(paren
r_int
r_int
id|start
comma
r_int
id|len
)paren
(brace
r_int
r_int
id|locked
suffix:semicolon
r_int
r_int
id|lock_limit
suffix:semicolon
r_int
id|error
op_assign
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
id|len
op_assign
id|PAGE_ALIGN
c_func
(paren
id|len
op_plus
(paren
id|start
op_amp
op_complement
id|PAGE_MASK
)paren
)paren
suffix:semicolon
id|start
op_and_assign
id|PAGE_MASK
suffix:semicolon
id|locked
op_assign
id|len
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|locked
op_add_assign
id|current-&gt;mm-&gt;locked_vm
suffix:semicolon
id|lock_limit
op_assign
id|current-&gt;rlim
(braket
id|RLIMIT_MEMLOCK
)braket
dot
id|rlim_cur
suffix:semicolon
id|lock_limit
op_rshift_assign
id|PAGE_SHIFT
suffix:semicolon
multiline_comment|/* check against resource limits */
r_if
c_cond
(paren
id|locked
OG
id|lock_limit
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* we may lock at most half of physical memory... */
multiline_comment|/* (this check is pretty bogus, but doesn&squot;t hurt) */
r_if
c_cond
(paren
id|locked
OG
id|num_physpages
op_div
l_int|2
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
id|do_mlock
c_func
(paren
id|start
comma
id|len
comma
l_int|1
)paren
suffix:semicolon
id|out
suffix:colon
id|up_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|sys_munlock
id|asmlinkage
r_int
id|sys_munlock
c_func
(paren
r_int
r_int
id|start
comma
r_int
id|len
)paren
(brace
r_int
id|ret
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|len
op_assign
id|PAGE_ALIGN
c_func
(paren
id|len
op_plus
(paren
id|start
op_amp
op_complement
id|PAGE_MASK
)paren
)paren
suffix:semicolon
id|start
op_and_assign
id|PAGE_MASK
suffix:semicolon
id|ret
op_assign
id|do_mlock
c_func
(paren
id|start
comma
id|len
comma
l_int|0
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|do_mlockall
r_static
r_int
id|do_mlockall
c_func
(paren
r_int
id|flags
)paren
(brace
r_int
id|error
suffix:semicolon
r_int
r_int
id|def_flags
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_IPC_LOCK
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|def_flags
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|MCL_FUTURE
)paren
id|def_flags
op_assign
id|VM_LOCKED
suffix:semicolon
id|current-&gt;mm-&gt;def_flags
op_assign
id|def_flags
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|vma
op_assign
id|current-&gt;mm-&gt;mmap
suffix:semicolon
id|vma
suffix:semicolon
id|vma
op_assign
id|vma-&gt;vm_next
)paren
(brace
r_int
r_int
id|newflags
suffix:semicolon
id|newflags
op_assign
id|vma-&gt;vm_flags
op_or
id|VM_LOCKED
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|MCL_CURRENT
)paren
)paren
id|newflags
op_and_assign
op_complement
id|VM_LOCKED
suffix:semicolon
id|error
op_assign
id|mlock_fixup
c_func
(paren
id|vma
comma
id|vma-&gt;vm_start
comma
id|vma-&gt;vm_end
comma
id|newflags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_break
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|function|sys_mlockall
id|asmlinkage
r_int
id|sys_mlockall
c_func
(paren
r_int
id|flags
)paren
(brace
r_int
r_int
id|lock_limit
suffix:semicolon
r_int
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|flags
op_logical_or
(paren
id|flags
op_amp
op_complement
(paren
id|MCL_CURRENT
op_or
id|MCL_FUTURE
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
id|lock_limit
op_assign
id|current-&gt;rlim
(braket
id|RLIMIT_MEMLOCK
)braket
dot
id|rlim_cur
suffix:semicolon
id|lock_limit
op_rshift_assign
id|PAGE_SHIFT
suffix:semicolon
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;mm-&gt;total_vm
OG
id|lock_limit
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* we may lock at most half of physical memory... */
multiline_comment|/* (this check is pretty bogus, but doesn&squot;t hurt) */
r_if
c_cond
(paren
id|current-&gt;mm-&gt;total_vm
OG
id|num_physpages
op_div
l_int|2
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
id|do_mlockall
c_func
(paren
id|flags
)paren
suffix:semicolon
id|out
suffix:colon
id|up_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|sys_munlockall
id|asmlinkage
r_int
id|sys_munlockall
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|ret
op_assign
id|do_mlockall
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
eof
