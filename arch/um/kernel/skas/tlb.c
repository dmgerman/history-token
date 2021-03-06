multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Copyright 2003 PathScale, Inc.&n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/stddef.h&quot;
macro_line|#include &quot;linux/sched.h&quot;
macro_line|#include &quot;linux/mm.h&quot;
macro_line|#include &quot;asm/page.h&quot;
macro_line|#include &quot;asm/pgtable.h&quot;
macro_line|#include &quot;asm/mmu.h&quot;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;mem_user.h&quot;
macro_line|#include &quot;mem.h&quot;
macro_line|#include &quot;skas.h&quot;
macro_line|#include &quot;os.h&quot;
macro_line|#include &quot;tlb.h&quot;
DECL|function|do_ops
r_static
r_void
id|do_ops
c_func
(paren
r_int
id|fd
comma
r_struct
id|host_vm_op
op_star
id|ops
comma
r_int
id|last
)paren
(brace
r_struct
id|host_vm_op
op_star
id|op
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|last
suffix:semicolon
id|i
op_increment
)paren
(brace
id|op
op_assign
op_amp
id|ops
(braket
id|i
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|op-&gt;type
)paren
(brace
r_case
id|MMAP
suffix:colon
id|map
c_func
(paren
id|fd
comma
id|op-&gt;u.mmap.addr
comma
id|op-&gt;u.mmap.len
comma
id|op-&gt;u.mmap.r
comma
id|op-&gt;u.mmap.w
comma
id|op-&gt;u.mmap.x
comma
id|op-&gt;u.mmap.fd
comma
id|op-&gt;u.mmap.offset
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MUNMAP
suffix:colon
id|unmap
c_func
(paren
id|fd
comma
(paren
r_void
op_star
)paren
id|op-&gt;u.munmap.addr
comma
id|op-&gt;u.munmap.len
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MPROTECT
suffix:colon
id|protect
c_func
(paren
id|fd
comma
id|op-&gt;u.mprotect.addr
comma
id|op-&gt;u.mprotect.len
comma
id|op-&gt;u.mprotect.r
comma
id|op-&gt;u.mprotect.w
comma
id|op-&gt;u.mprotect.x
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Unknown op type %d in do_ops&bslash;n&quot;
comma
id|op-&gt;type
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
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
r_int
id|fd
op_assign
id|mm-&gt;context.skas.mm_fd
suffix:semicolon
id|fix_range_common
c_func
(paren
id|mm
comma
id|start_addr
comma
id|end_addr
comma
id|force
comma
id|fd
comma
id|do_ops
)paren
suffix:semicolon
)brace
DECL|function|__flush_tlb_one_skas
r_void
id|__flush_tlb_one_skas
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|flush_tlb_kernel_range_common
c_func
(paren
id|addr
comma
id|addr
op_plus
id|PAGE_SIZE
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_range_skas
r_void
id|flush_tlb_range_skas
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
op_eq
l_int|NULL
)paren
(brace
id|flush_tlb_kernel_range_common
c_func
(paren
id|start
comma
id|end
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
DECL|function|flush_tlb_mm_skas
r_void
id|flush_tlb_mm_skas
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
multiline_comment|/* Don&squot;t bother flushing if this address space is about to be&n;         * destroyed.&n;         */
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|mm-&gt;mm_users
)paren
op_eq
l_int|0
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
id|host_task_size
comma
l_int|0
)paren
suffix:semicolon
id|flush_tlb_kernel_range_common
c_func
(paren
id|start_vm
comma
id|end_vm
)paren
suffix:semicolon
)brace
DECL|function|force_flush_all_skas
r_void
id|force_flush_all_skas
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
id|host_task_size
comma
l_int|1
)paren
suffix:semicolon
)brace
eof
