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
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|newflags
op_eq
id|vma-&gt;vm_flags
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|start
op_ne
id|vma-&gt;vm_start
)paren
(brace
r_if
c_cond
(paren
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
)paren
(brace
id|ret
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|end
op_ne
id|vma-&gt;vm_end
)paren
(brace
r_if
c_cond
(paren
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
)paren
(brace
id|ret
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * vm_flags is protected by the mmap_sem held in write mode.&n;&t; * It&squot;s okay if try_to_unmap_one unmaps a page just after we&n;&t; * set VM_LOCKED, make_pages_present below will bring it back.&n;&t; */
id|vma-&gt;vm_flags
op_assign
id|newflags
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
id|ret
op_assign
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
id|out
suffix:colon
r_return
id|ret
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
id|can_do_mlock
c_func
(paren
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
(paren
id|locked
op_le
id|lock_limit
)paren
op_logical_or
id|capable
c_func
(paren
id|CAP_IPC_LOCK
)paren
)paren
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
id|can_do_mlock
c_func
(paren
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
r_if
c_cond
(paren
id|flags
op_eq
id|MCL_FUTURE
)paren
r_goto
id|out
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
multiline_comment|/* Ignore errors */
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
)brace
id|out
suffix:colon
r_return
l_int|0
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
(paren
id|current-&gt;mm-&gt;total_vm
op_le
id|lock_limit
)paren
op_logical_or
id|capable
c_func
(paren
id|CAP_IPC_LOCK
)paren
)paren
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
multiline_comment|/*&n; * Objects with different lifetime than processes (SHM_LOCK and SHM_HUGETLB&n; * shm segments) get accounted against the user_struct instead.&n; */
DECL|variable|shmlock_user_lock
r_static
id|spinlock_t
id|shmlock_user_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|function|user_shm_lock
r_int
id|user_shm_lock
c_func
(paren
r_int
id|size
comma
r_struct
id|user_struct
op_star
id|user
)paren
(brace
r_int
r_int
id|lock_limit
comma
id|locked
suffix:semicolon
r_int
id|allowed
op_assign
l_int|0
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|shmlock_user_lock
)paren
suffix:semicolon
id|locked
op_assign
id|size
op_rshift
id|PAGE_SHIFT
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
r_if
c_cond
(paren
id|locked
op_plus
id|user-&gt;locked_shm
OG
id|lock_limit
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_IPC_LOCK
)paren
)paren
r_goto
id|out
suffix:semicolon
id|get_uid
c_func
(paren
id|user
)paren
suffix:semicolon
id|user-&gt;locked_shm
op_add_assign
id|locked
suffix:semicolon
id|allowed
op_assign
l_int|1
suffix:semicolon
id|out
suffix:colon
id|spin_unlock
c_func
(paren
op_amp
id|shmlock_user_lock
)paren
suffix:semicolon
r_return
id|allowed
suffix:semicolon
)brace
DECL|function|user_shm_unlock
r_void
id|user_shm_unlock
c_func
(paren
r_int
id|size
comma
r_struct
id|user_struct
op_star
id|user
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|shmlock_user_lock
)paren
suffix:semicolon
id|user-&gt;locked_shm
op_sub_assign
(paren
id|size
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|shmlock_user_lock
)paren
suffix:semicolon
id|free_uid
c_func
(paren
id|user
)paren
suffix:semicolon
)brace
eof
