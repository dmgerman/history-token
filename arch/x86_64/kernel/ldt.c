multiline_comment|/*&n; * linux/kernel/ldt.c&n; *&n; * Copyright (C) 1992 Krishna Balasubramanian and Linus Torvalds&n; * Copyright (C) 1999 Ingo Molnar &lt;mingo@redhat.com&gt;&n; */
multiline_comment|/* &n; * FIXME: forbid code segment setting for 64bit mode. doesn&squot;t work with SYSCALL &n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/ldt.h&gt;
macro_line|#include &lt;asm/desc.h&gt;
multiline_comment|/*&n; * read_ldt() is not really atomic - this is not a problem since&n; * synchronization of reads and writes done to the LDT has to be&n; * assured by user-space anyway. Writes are atomic, to protect&n; * the security checks done on new descriptors.&n; */
DECL|function|read_ldt
r_static
r_int
id|read_ldt
c_func
(paren
r_void
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
id|err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mm-&gt;context.segments
)paren
r_goto
id|out
suffix:semicolon
id|size
op_assign
id|LDT_ENTRIES
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
id|size
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|ptr
comma
id|mm-&gt;context.segments
comma
id|size
)paren
)paren
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
id|out
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
r_void
op_star
id|address
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
id|address
op_assign
op_amp
id|default_ldt
(braket
l_int|0
)braket
suffix:semicolon
id|size
op_assign
r_sizeof
(paren
r_struct
id|desc_struct
)paren
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
id|size
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|ptr
comma
id|address
comma
id|size
)paren
)paren
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|write_ldt
r_static
r_int
id|write_ldt
c_func
(paren
r_void
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
id|mm_struct
op_star
id|mm
op_assign
id|current-&gt;mm
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
id|modify_ldt_ldt_s
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
r_sizeof
(paren
id|ldt_info
)paren
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
id|current-&gt;thread.fsindex
op_assign
l_int|0
suffix:semicolon
id|current-&gt;thread.gsindex
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * the GDT index of the LDT is allocated dynamically, and is&n;&t; * limited by MAX_LDT_DESCRIPTORS.&n;&t; */
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
op_logical_neg
id|mm-&gt;context.segments
)paren
(brace
r_void
op_star
id|segments
op_assign
id|vmalloc
c_func
(paren
id|LDT_ENTRIES
op_star
id|LDT_ENTRY_SIZE
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|segments
)paren
r_goto
id|out_unlock
suffix:semicolon
id|memset
c_func
(paren
id|segments
comma
l_int|0
comma
id|LDT_ENTRIES
op_star
id|LDT_ENTRY_SIZE
)paren
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|mm-&gt;context.segments
op_assign
id|segments
suffix:semicolon
id|mm-&gt;context.cpuvalid
op_assign
l_int|1UL
op_lshift
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|load_LDT
c_func
(paren
id|mm
)paren
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
id|mm-&gt;context.segments
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
(paren
id|ldt_info.contents
op_eq
l_int|0
op_logical_and
id|ldt_info.read_exec_only
op_eq
l_int|1
op_logical_and
id|ldt_info.seg_32bit
op_eq
l_int|0
op_logical_and
id|ldt_info.limit_in_pages
op_eq
l_int|0
op_logical_and
id|ldt_info.seg_not_present
op_eq
l_int|1
op_logical_and
id|ldt_info.useable
op_eq
l_int|0
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
(paren
(paren
id|ldt_info.base_addr
op_amp
l_int|0x0000ffff
)paren
op_lshift
l_int|16
)paren
op_or
(paren
id|ldt_info.limit
op_amp
l_int|0x0ffff
)paren
suffix:semicolon
id|entry_2
op_assign
(paren
id|ldt_info.base_addr
op_amp
l_int|0xff000000
)paren
op_or
(paren
(paren
id|ldt_info.base_addr
op_amp
l_int|0x00ff0000
)paren
op_rshift
l_int|16
)paren
op_or
(paren
id|ldt_info.limit
op_amp
l_int|0xf0000
)paren
op_or
(paren
(paren
id|ldt_info.read_exec_only
op_xor
l_int|1
)paren
op_lshift
l_int|9
)paren
op_or
(paren
id|ldt_info.contents
op_lshift
l_int|10
)paren
op_or
(paren
(paren
id|ldt_info.seg_not_present
op_xor
l_int|1
)paren
op_lshift
l_int|15
)paren
op_or
(paren
id|ldt_info.seg_32bit
op_lshift
l_int|22
)paren
op_or
(paren
id|ldt_info.limit_in_pages
op_lshift
l_int|23
)paren
op_or
l_int|0x7000
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|oldmode
)paren
id|entry_2
op_or_assign
(paren
id|ldt_info.useable
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
id|up_write
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
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