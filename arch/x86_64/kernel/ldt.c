multiline_comment|/*&n; * linux/arch/x86_64/kernel/ldt.c&n; *&n; * Copyright (C) 1992 Krishna Balasubramanian and Linus Torvalds&n; * Copyright (C) 1999 Ingo Molnar &lt;mingo@redhat.com&gt;&n; * Copyright (C) 2002 Andi Kleen&n; * &n; * This handles calls from both 32bit and 64bit mode.&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/ldt.h&gt;
macro_line|#include &lt;asm/desc.h&gt;
macro_line|#include &lt;asm/proto.h&gt;
macro_line|#ifdef CONFIG_SMP /* avoids &quot;defined but not used&quot; warnig */
DECL|function|flush_ldt
r_static
r_void
id|flush_ldt
c_func
(paren
r_void
op_star
id|null
)paren
(brace
r_if
c_cond
(paren
id|current-&gt;active_mm
)paren
id|load_LDT
c_func
(paren
op_amp
id|current-&gt;active_mm-&gt;context
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|alloc_ldt
r_static
r_int
id|alloc_ldt
c_func
(paren
id|mm_context_t
op_star
id|pc
comma
r_int
id|mincount
comma
r_int
id|reload
)paren
(brace
r_void
op_star
id|oldldt
suffix:semicolon
r_void
op_star
id|newldt
suffix:semicolon
r_int
id|oldsize
suffix:semicolon
r_if
c_cond
(paren
id|mincount
op_le
(paren
r_int
)paren
id|pc-&gt;size
)paren
r_return
l_int|0
suffix:semicolon
id|oldsize
op_assign
id|pc-&gt;size
suffix:semicolon
id|mincount
op_assign
(paren
id|mincount
op_plus
l_int|511
)paren
op_amp
(paren
op_complement
l_int|511
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mincount
op_star
id|LDT_ENTRY_SIZE
OG
id|PAGE_SIZE
)paren
id|newldt
op_assign
id|vmalloc
c_func
(paren
id|mincount
op_star
id|LDT_ENTRY_SIZE
)paren
suffix:semicolon
r_else
id|newldt
op_assign
id|kmalloc
c_func
(paren
id|mincount
op_star
id|LDT_ENTRY_SIZE
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|newldt
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|oldsize
)paren
id|memcpy
c_func
(paren
id|newldt
comma
id|pc-&gt;ldt
comma
id|oldsize
op_star
id|LDT_ENTRY_SIZE
)paren
suffix:semicolon
id|oldldt
op_assign
id|pc-&gt;ldt
suffix:semicolon
id|memset
c_func
(paren
id|newldt
op_plus
id|oldsize
op_star
id|LDT_ENTRY_SIZE
comma
l_int|0
comma
(paren
id|mincount
op_minus
id|oldsize
)paren
op_star
id|LDT_ENTRY_SIZE
)paren
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|pc-&gt;ldt
op_assign
id|newldt
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|pc-&gt;size
op_assign
id|mincount
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reload
)paren
(brace
macro_line|#ifdef CONFIG_SMP
id|cpumask_t
id|mask
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
id|mask
op_assign
id|cpumask_of_cpu
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
id|load_LDT
c_func
(paren
id|pc
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpus_equal
c_func
(paren
id|current-&gt;mm-&gt;cpu_vm_mask
comma
id|mask
)paren
)paren
id|smp_call_function
c_func
(paren
id|flush_ldt
comma
l_int|NULL
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
macro_line|#else
id|load_LDT
c_func
(paren
id|pc
)paren
suffix:semicolon
macro_line|#endif
)brace
r_if
c_cond
(paren
id|oldsize
)paren
(brace
r_if
c_cond
(paren
id|oldsize
op_star
id|LDT_ENTRY_SIZE
OG
id|PAGE_SIZE
)paren
id|vfree
c_func
(paren
id|oldldt
)paren
suffix:semicolon
r_else
id|kfree
c_func
(paren
id|oldldt
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|copy_ldt
r_static
r_inline
r_int
id|copy_ldt
c_func
(paren
id|mm_context_t
op_star
r_new
comma
id|mm_context_t
op_star
id|old
)paren
(brace
r_int
id|err
op_assign
id|alloc_ldt
c_func
(paren
r_new
comma
id|old-&gt;size
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|memcpy
c_func
(paren
r_new
op_member_access_from_pointer
id|ldt
comma
id|old-&gt;ldt
comma
id|old-&gt;size
op_star
id|LDT_ENTRY_SIZE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * we do not have to muck with descriptors here, that is&n; * done in switch_mm() as needed.&n; */
DECL|function|init_new_context
r_int
id|init_new_context
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_struct
id|mm_struct
op_star
id|old_mm
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|mm-&gt;context.sem
)paren
suffix:semicolon
id|mm-&gt;context.size
op_assign
l_int|0
suffix:semicolon
id|old_mm
op_assign
id|current-&gt;mm
suffix:semicolon
r_if
c_cond
(paren
id|old_mm
op_logical_and
id|old_mm-&gt;context.size
OG
l_int|0
)paren
(brace
id|down
c_func
(paren
op_amp
id|old_mm-&gt;context.sem
)paren
suffix:semicolon
id|retval
op_assign
id|copy_ldt
c_func
(paren
op_amp
id|mm-&gt;context
comma
op_amp
id|old_mm-&gt;context
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|old_mm-&gt;context.sem
)paren
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; * &n; * Don&squot;t touch the LDT register - we&squot;re already in the next thread.&n; */
DECL|function|destroy_context
r_void
id|destroy_context
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_if
c_cond
(paren
id|mm-&gt;context.size
)paren
(brace
r_if
c_cond
(paren
(paren
r_int
)paren
id|mm-&gt;context.size
op_star
id|LDT_ENTRY_SIZE
OG
id|PAGE_SIZE
)paren
id|vfree
c_func
(paren
id|mm-&gt;context.ldt
)paren
suffix:semicolon
r_else
id|kfree
c_func
(paren
id|mm-&gt;context.ldt
)paren
suffix:semicolon
id|mm-&gt;context.size
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|read_ldt
r_static
r_int
id|read_ldt
c_func
(paren
r_void
id|__user
op_star
id|ptr
comma
r_int
r_int
id|bytecount
)paren
(brace
r_int
id|err
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|current-&gt;mm
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mm-&gt;context.size
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|bytecount
OG
id|LDT_ENTRY_SIZE
op_star
id|LDT_ENTRIES
)paren
id|bytecount
op_assign
id|LDT_ENTRY_SIZE
op_star
id|LDT_ENTRIES
suffix:semicolon
id|down
c_func
(paren
op_amp
id|mm-&gt;context.sem
)paren
suffix:semicolon
id|size
op_assign
id|mm-&gt;context.size
op_star
id|LDT_ENTRY_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
id|bytecount
)paren
id|size
op_assign
id|bytecount
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|ptr
comma
id|mm-&gt;context.ldt
comma
id|size
)paren
)paren
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
id|up
c_func
(paren
op_amp
id|mm-&gt;context.sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_goto
id|error_return
suffix:semicolon
r_if
c_cond
(paren
id|size
op_ne
id|bytecount
)paren
(brace
multiline_comment|/* zero-fill the rest */
r_if
c_cond
(paren
id|clear_user
c_func
(paren
id|ptr
op_plus
id|size
comma
id|bytecount
op_minus
id|size
)paren
op_ne
l_int|0
)paren
(brace
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|error_return
suffix:semicolon
)brace
)brace
r_return
id|bytecount
suffix:semicolon
id|error_return
suffix:colon
r_return
id|err
suffix:semicolon
)brace
DECL|function|read_default_ldt
r_static
r_int
id|read_default_ldt
c_func
(paren
r_void
id|__user
op_star
id|ptr
comma
r_int
r_int
id|bytecount
)paren
(brace
multiline_comment|/* Arbitrary number */
multiline_comment|/* x86-64 default LDT is all zeros */
r_if
c_cond
(paren
id|bytecount
OG
l_int|128
)paren
id|bytecount
op_assign
l_int|128
suffix:semicolon
r_if
c_cond
(paren
id|clear_user
c_func
(paren
id|ptr
comma
id|bytecount
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|bytecount
suffix:semicolon
)brace
DECL|function|write_ldt
r_static
r_int
id|write_ldt
c_func
(paren
r_void
id|__user
op_star
id|ptr
comma
r_int
r_int
id|bytecount
comma
r_int
id|oldmode
)paren
(brace
r_struct
id|task_struct
op_star
id|me
op_assign
id|current
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|me-&gt;mm
suffix:semicolon
id|__u32
id|entry_1
comma
id|entry_2
comma
op_star
id|lp
suffix:semicolon
r_int
id|error
suffix:semicolon
r_struct
id|user_desc
id|ldt_info
suffix:semicolon
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|bytecount
op_ne
r_sizeof
(paren
id|ldt_info
)paren
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|ldt_info
comma
id|ptr
comma
id|bytecount
)paren
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|ldt_info.entry_number
op_ge
id|LDT_ENTRIES
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|ldt_info.contents
op_eq
l_int|3
)paren
(brace
r_if
c_cond
(paren
id|oldmode
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|ldt_info.seg_not_present
op_eq
l_int|0
)paren
r_goto
id|out
suffix:semicolon
)brace
id|down
c_func
(paren
op_amp
id|mm-&gt;context.sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ldt_info.entry_number
op_ge
(paren
r_int
)paren
id|mm-&gt;context.size
)paren
(brace
id|error
op_assign
id|alloc_ldt
c_func
(paren
op_amp
id|current-&gt;mm-&gt;context
comma
id|ldt_info.entry_number
op_plus
l_int|1
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
r_goto
id|out_unlock
suffix:semicolon
)brace
id|lp
op_assign
(paren
id|__u32
op_star
)paren
(paren
(paren
id|ldt_info.entry_number
op_lshift
l_int|3
)paren
op_plus
(paren
r_char
op_star
)paren
id|mm-&gt;context.ldt
)paren
suffix:semicolon
multiline_comment|/* Allow LDTs to be cleared by the user. */
r_if
c_cond
(paren
id|ldt_info.base_addr
op_eq
l_int|0
op_logical_and
id|ldt_info.limit
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|oldmode
op_logical_or
id|LDT_empty
c_func
(paren
op_amp
id|ldt_info
)paren
)paren
(brace
id|entry_1
op_assign
l_int|0
suffix:semicolon
id|entry_2
op_assign
l_int|0
suffix:semicolon
r_goto
id|install
suffix:semicolon
)brace
)brace
id|entry_1
op_assign
id|LDT_entry_a
c_func
(paren
op_amp
id|ldt_info
)paren
suffix:semicolon
id|entry_2
op_assign
id|LDT_entry_b
c_func
(paren
op_amp
id|ldt_info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|oldmode
)paren
id|entry_2
op_and_assign
op_complement
(paren
l_int|1
op_lshift
l_int|20
)paren
suffix:semicolon
multiline_comment|/* Install the new entry ...  */
id|install
suffix:colon
op_star
id|lp
op_assign
id|entry_1
suffix:semicolon
op_star
(paren
id|lp
op_plus
l_int|1
)paren
op_assign
id|entry_2
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
id|out_unlock
suffix:colon
id|up
c_func
(paren
op_amp
id|mm-&gt;context.sem
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
)brace
DECL|function|sys_modify_ldt
id|asmlinkage
r_int
id|sys_modify_ldt
c_func
(paren
r_int
id|func
comma
r_void
id|__user
op_star
id|ptr
comma
r_int
r_int
id|bytecount
)paren
(brace
r_int
id|ret
op_assign
op_minus
id|ENOSYS
suffix:semicolon
r_switch
c_cond
(paren
id|func
)paren
(brace
r_case
l_int|0
suffix:colon
id|ret
op_assign
id|read_ldt
c_func
(paren
id|ptr
comma
id|bytecount
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|ret
op_assign
id|write_ldt
c_func
(paren
id|ptr
comma
id|bytecount
comma
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|ret
op_assign
id|read_default_ldt
c_func
(paren
id|ptr
comma
id|bytecount
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x11
suffix:colon
id|ret
op_assign
id|write_ldt
c_func
(paren
id|ptr
comma
id|bytecount
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
eof
