multiline_comment|/*&n; * This file contains various system calls that have different calling&n; * conventions on different platforms.&n; *&n; * Copyright (C) 1999-2000, 2002 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/shm.h&gt;
macro_line|#include &lt;linux/file.h&gt;&t;&t;/* doh, must come after sched.h... */
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/highuid.h&gt;
macro_line|#include &lt;linux/hugetlb.h&gt;
macro_line|#include &lt;asm/shmparam.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
r_int
r_int
DECL|function|arch_get_unmapped_area
id|arch_get_unmapped_area
(paren
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|len
comma
r_int
r_int
id|pgoff
comma
r_int
r_int
id|flags
)paren
(brace
r_int
id|map_shared
op_assign
(paren
id|flags
op_amp
id|MAP_SHARED
)paren
suffix:semicolon
r_int
r_int
id|align_mask
op_assign
id|PAGE_SIZE
op_minus
l_int|1
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|vmm
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|RGN_MAP_LIMIT
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
macro_line|#ifdef CONFIG_HUGETLB_PAGE
r_if
c_cond
(paren
id|REGION_NUMBER
c_func
(paren
id|addr
)paren
op_eq
id|REGION_HPAGE
)paren
id|addr
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|addr
)paren
id|addr
op_assign
id|TASK_UNMAPPED_BASE
suffix:semicolon
r_if
c_cond
(paren
id|map_shared
op_logical_and
(paren
id|TASK_SIZE
OG
l_int|0xfffffffful
)paren
)paren
multiline_comment|/*&n;&t;&t; * For 64-bit tasks, align shared segments to 1MB to avoid potential&n;&t;&t; * performance penalty due to virtual aliasing (see ASDM).  For 32-bit&n;&t;&t; * tasks, we prefer to avoid exhausting the address space too quickly by&n;&t;&t; * limiting alignment to a single page.&n;&t;&t; */
id|align_mask
op_assign
id|SHMLBA
op_minus
l_int|1
suffix:semicolon
id|addr
op_assign
(paren
id|addr
op_plus
id|align_mask
)paren
op_amp
op_complement
id|align_mask
suffix:semicolon
r_for
c_loop
(paren
id|vmm
op_assign
id|find_vma
c_func
(paren
id|current-&gt;mm
comma
id|addr
)paren
suffix:semicolon
suffix:semicolon
id|vmm
op_assign
id|vmm-&gt;vm_next
)paren
(brace
multiline_comment|/* At this point:  (!vmm || addr &lt; vmm-&gt;vm_end). */
r_if
c_cond
(paren
id|TASK_SIZE
op_minus
id|len
OL
id|addr
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|REGION_OFFSET
c_func
(paren
id|addr
)paren
op_plus
id|len
OG
id|RGN_MAP_LIMIT
)paren
multiline_comment|/* no risk of overflow here... */
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vmm
op_logical_or
id|addr
op_plus
id|len
op_le
id|vmm-&gt;vm_start
)paren
r_return
id|addr
suffix:semicolon
id|addr
op_assign
(paren
id|vmm-&gt;vm_end
op_plus
id|align_mask
)paren
op_amp
op_complement
id|align_mask
suffix:semicolon
)brace
)brace
id|asmlinkage
r_int
DECL|function|ia64_getpriority
id|ia64_getpriority
(paren
r_int
id|which
comma
r_int
id|who
)paren
(brace
r_extern
r_int
id|sys_getpriority
(paren
r_int
comma
r_int
)paren
suffix:semicolon
r_int
id|prio
suffix:semicolon
id|prio
op_assign
id|sys_getpriority
c_func
(paren
id|which
comma
id|who
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prio
op_ge
l_int|0
)paren
(brace
id|force_successful_syscall_return
c_func
(paren
)paren
suffix:semicolon
id|prio
op_assign
l_int|20
op_minus
id|prio
suffix:semicolon
)brace
r_return
id|prio
suffix:semicolon
)brace
multiline_comment|/* XXX obsolete, but leave it here until the old libc is gone... */
id|asmlinkage
r_int
r_int
DECL|function|sys_getpagesize
id|sys_getpagesize
(paren
r_void
)paren
(brace
r_return
id|PAGE_SIZE
suffix:semicolon
)brace
id|asmlinkage
r_int
r_int
DECL|function|ia64_shmat
id|ia64_shmat
(paren
r_int
id|shmid
comma
r_void
op_star
id|shmaddr
comma
r_int
id|shmflg
)paren
(brace
r_int
r_int
id|raddr
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|retval
op_assign
id|sys_shmat
c_func
(paren
id|shmid
comma
id|shmaddr
comma
id|shmflg
comma
op_amp
id|raddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
r_return
id|retval
suffix:semicolon
id|force_successful_syscall_return
c_func
(paren
)paren
suffix:semicolon
r_return
id|raddr
suffix:semicolon
)brace
id|asmlinkage
r_int
r_int
DECL|function|ia64_brk
id|ia64_brk
(paren
r_int
r_int
id|brk
)paren
(brace
r_extern
r_int
id|vm_enough_memory
(paren
r_int
id|pages
)paren
suffix:semicolon
r_int
r_int
id|rlim
comma
id|retval
comma
id|newbrk
comma
id|oldbrk
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|current-&gt;mm
suffix:semicolon
multiline_comment|/*&n;&t; * Most of this replicates the code in sys_brk() except for an additional safety&n;&t; * check and the clearing of r8.  However, we can&squot;t call sys_brk() because we need&n;&t; * to acquire the mmap_sem before we can do the test...&n;&t; */
id|down_write
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|brk
OL
id|mm-&gt;end_code
)paren
r_goto
id|out
suffix:semicolon
id|newbrk
op_assign
id|PAGE_ALIGN
c_func
(paren
id|brk
)paren
suffix:semicolon
id|oldbrk
op_assign
id|PAGE_ALIGN
c_func
(paren
id|mm-&gt;brk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|oldbrk
op_eq
id|newbrk
)paren
r_goto
id|set_brk
suffix:semicolon
multiline_comment|/* Always allow shrinking brk. */
r_if
c_cond
(paren
id|brk
op_le
id|mm-&gt;brk
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|do_munmap
c_func
(paren
id|mm
comma
id|newbrk
comma
id|oldbrk
op_minus
id|newbrk
)paren
)paren
r_goto
id|set_brk
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* Check against unimplemented/unmapped addresses: */
r_if
c_cond
(paren
(paren
id|newbrk
op_minus
id|oldbrk
)paren
OG
id|RGN_MAP_LIMIT
op_logical_or
id|REGION_OFFSET
c_func
(paren
id|newbrk
)paren
OG
id|RGN_MAP_LIMIT
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* Check against rlimit.. */
id|rlim
op_assign
id|current-&gt;rlim
(braket
id|RLIMIT_DATA
)braket
dot
id|rlim_cur
suffix:semicolon
r_if
c_cond
(paren
id|rlim
template_param
id|rlim
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* Check against existing mmap mappings. */
r_if
c_cond
(paren
id|find_vma_intersection
c_func
(paren
id|mm
comma
id|oldbrk
comma
id|newbrk
op_plus
id|PAGE_SIZE
)paren
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* Ok, looks good - let it rip. */
r_if
c_cond
(paren
id|do_brk
c_func
(paren
id|oldbrk
comma
id|newbrk
op_minus
id|oldbrk
)paren
op_ne
id|oldbrk
)paren
r_goto
id|out
suffix:semicolon
id|set_brk
suffix:colon
id|mm-&gt;brk
op_assign
id|brk
suffix:semicolon
id|out
suffix:colon
id|retval
op_assign
id|mm-&gt;brk
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
id|force_successful_syscall_return
c_func
(paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; * On IA-64, we return the two file descriptors in ret0 and ret1 (r8&n; * and r9) as this is faster than doing a copy_to_user().&n; */
id|asmlinkage
r_int
DECL|function|sys_pipe
id|sys_pipe
(paren
r_int
id|arg0
comma
r_int
id|arg1
comma
r_int
id|arg2
comma
r_int
id|arg3
comma
r_int
id|arg4
comma
r_int
id|arg5
comma
r_int
id|arg6
comma
r_int
id|arg7
comma
r_int
id|stack
)paren
(brace
r_struct
id|pt_regs
op_star
id|regs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
op_amp
id|stack
suffix:semicolon
r_int
id|fd
(braket
l_int|2
)braket
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|retval
op_assign
id|do_pipe
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
id|out
suffix:semicolon
id|retval
op_assign
id|fd
(braket
l_int|0
)braket
suffix:semicolon
id|regs-&gt;r9
op_assign
id|fd
(braket
l_int|1
)braket
suffix:semicolon
id|out
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|do_mmap2
id|do_mmap2
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|len
comma
r_int
id|prot
comma
r_int
id|flags
comma
r_int
id|fd
comma
r_int
r_int
id|pgoff
)paren
(brace
r_int
r_int
id|roff
suffix:semicolon
r_struct
id|file
op_star
id|file
op_assign
l_int|0
suffix:semicolon
id|flags
op_and_assign
op_complement
(paren
id|MAP_EXECUTABLE
op_or
id|MAP_DENYWRITE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|MAP_ANONYMOUS
)paren
)paren
(brace
id|file
op_assign
id|fget
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file-&gt;f_op
op_logical_or
op_logical_neg
id|file-&gt;f_op-&gt;mmap
)paren
(brace
id|addr
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * A zero mmap always succeeds in Linux, independent of whether or not the&n;&t; * remaining arguments are valid.&n;&t; */
id|len
op_assign
id|PAGE_ALIGN
c_func
(paren
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
l_int|0
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/*&n;&t; * Don&squot;t permit mappings into unmapped space, the virtual page table of a region,&n;&t; * or across a region boundary.  Note: RGN_MAP_LIMIT is equal to 2^n-PAGE_SIZE&n;&t; * (for some integer n &lt;= 61) and len &gt; 0.&n;&t; */
id|roff
op_assign
id|REGION_OFFSET
c_func
(paren
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
OG
id|RGN_MAP_LIMIT
)paren
op_logical_or
(paren
id|roff
OG
(paren
id|RGN_MAP_LIMIT
op_minus
id|len
)paren
)paren
)paren
(brace
id|addr
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|down_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|addr
op_assign
id|do_mmap_pgoff
c_func
(paren
id|file
comma
id|addr
comma
id|len
comma
id|prot
comma
id|flags
comma
id|pgoff
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|out
suffix:colon
r_if
c_cond
(paren
id|file
)paren
id|fput
c_func
(paren
id|file
)paren
suffix:semicolon
r_return
id|addr
suffix:semicolon
)brace
multiline_comment|/*&n; * mmap2() is like mmap() except that the offset is expressed in units&n; * of PAGE_SIZE (instead of bytes).  This allows to mmap2() (pieces&n; * of) files that are larger than the address space of the CPU.&n; */
id|asmlinkage
r_int
r_int
DECL|function|sys_mmap2
id|sys_mmap2
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|len
comma
r_int
id|prot
comma
r_int
id|flags
comma
r_int
id|fd
comma
r_int
id|pgoff
)paren
(brace
id|addr
op_assign
id|do_mmap2
c_func
(paren
id|addr
comma
id|len
comma
id|prot
comma
id|flags
comma
id|fd
comma
id|pgoff
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
(paren
r_void
op_star
)paren
id|addr
)paren
)paren
id|force_successful_syscall_return
c_func
(paren
)paren
suffix:semicolon
r_return
id|addr
suffix:semicolon
)brace
id|asmlinkage
r_int
r_int
DECL|function|sys_mmap
id|sys_mmap
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|len
comma
r_int
id|prot
comma
r_int
id|flags
comma
r_int
id|fd
comma
r_int
id|off
)paren
(brace
r_if
c_cond
(paren
(paren
id|off
op_amp
op_complement
id|PAGE_MASK
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|addr
op_assign
id|do_mmap2
c_func
(paren
id|addr
comma
id|len
comma
id|prot
comma
id|flags
comma
id|fd
comma
id|off
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
(paren
r_void
op_star
)paren
id|addr
)paren
)paren
id|force_successful_syscall_return
c_func
(paren
)paren
suffix:semicolon
r_return
id|addr
suffix:semicolon
)brace
id|asmlinkage
r_int
r_int
DECL|function|ia64_mremap
id|ia64_mremap
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|old_len
comma
r_int
r_int
id|new_len
comma
r_int
r_int
id|flags
comma
r_int
r_int
id|new_addr
)paren
(brace
r_extern
r_int
r_int
id|do_mremap
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|old_len
comma
r_int
r_int
id|new_len
comma
r_int
r_int
id|flags
comma
r_int
r_int
id|new_addr
)paren
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
(brace
id|addr
op_assign
id|do_mremap
c_func
(paren
id|addr
comma
id|old_len
comma
id|new_len
comma
id|flags
comma
id|new_addr
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
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
(paren
r_void
op_star
)paren
id|addr
)paren
)paren
r_return
id|addr
suffix:semicolon
id|force_successful_syscall_return
c_func
(paren
)paren
suffix:semicolon
r_return
id|addr
suffix:semicolon
)brace
macro_line|#ifndef CONFIG_PCI
id|asmlinkage
r_int
DECL|function|sys_pciconfig_read
id|sys_pciconfig_read
(paren
r_int
r_int
id|bus
comma
r_int
r_int
id|dfn
comma
r_int
r_int
id|off
comma
r_int
r_int
id|len
comma
r_void
op_star
id|buf
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
id|asmlinkage
r_int
DECL|function|sys_pciconfig_write
id|sys_pciconfig_write
(paren
r_int
r_int
id|bus
comma
r_int
r_int
id|dfn
comma
r_int
r_int
id|off
comma
r_int
r_int
id|len
comma
r_void
op_star
id|buf
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PCI */
eof
