multiline_comment|/*&n; * Copyright (C) 2001, 2004 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; *&n; * Adapted from arch/i386/kernel/ldt.c&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;ia32priv.h&quot;
multiline_comment|/*&n; * read_ldt() is not really atomic - this is not a problem since synchronization of reads&n; * and writes done to the LDT has to be assured by user-space anyway. Writes are atomic,&n; * to protect the security checks done on new descriptors.&n; */
r_static
r_int
DECL|function|read_ldt
id|read_ldt
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
r_int
id|bytes_left
comma
id|n
suffix:semicolon
r_char
id|__user
op_star
id|src
comma
op_star
id|dst
suffix:semicolon
r_char
id|buf
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* temporary buffer (don&squot;t overflow kernel stack!) */
r_if
c_cond
(paren
id|bytecount
OG
id|IA32_LDT_ENTRIES
op_star
id|IA32_LDT_ENTRY_SIZE
)paren
id|bytecount
op_assign
id|IA32_LDT_ENTRIES
op_star
id|IA32_LDT_ENTRY_SIZE
suffix:semicolon
id|bytes_left
op_assign
id|bytecount
suffix:semicolon
id|src
op_assign
(paren
r_void
id|__user
op_star
)paren
id|IA32_LDT_OFFSET
suffix:semicolon
id|dst
op_assign
id|ptr
suffix:semicolon
r_while
c_loop
(paren
id|bytes_left
)paren
(brace
id|n
op_assign
r_sizeof
(paren
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
OG
id|bytes_left
)paren
id|n
op_assign
id|bytes_left
suffix:semicolon
multiline_comment|/*&n;&t;&t; * We know we&squot;re reading valid memory, but we still must guard against&n;&t;&t; * running out of memory.&n;&t;&t; */
r_if
c_cond
(paren
id|__copy_from_user
c_func
(paren
id|buf
comma
id|src
comma
id|n
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|dst
comma
id|buf
comma
id|n
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|src
op_add_assign
id|n
suffix:semicolon
id|dst
op_add_assign
id|n
suffix:semicolon
id|bytes_left
op_sub_assign
id|n
suffix:semicolon
)brace
r_return
id|bytecount
suffix:semicolon
)brace
r_static
r_int
DECL|function|read_default_ldt
id|read_default_ldt
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
r_int
id|size
suffix:semicolon
r_int
id|err
suffix:semicolon
multiline_comment|/* XXX fix me: should return equivalent of default_ldt[0] */
id|err
op_assign
l_int|0
suffix:semicolon
id|size
op_assign
l_int|8
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
id|clear_user
c_func
(paren
id|ptr
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
r_static
r_int
DECL|function|write_ldt
id|write_ldt
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
id|ia32_user_desc
id|ldt_info
suffix:semicolon
id|__u64
id|entry
suffix:semicolon
r_int
id|ret
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
r_return
op_minus
id|EINVAL
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
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|ldt_info.entry_number
op_ge
id|IA32_LDT_ENTRIES
)paren
r_return
op_minus
id|EINVAL
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
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|ldt_info.seg_not_present
op_eq
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
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
op_logical_and
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
)paren
multiline_comment|/* allow LDTs to be cleared by the user */
id|entry
op_assign
l_int|0
suffix:semicolon
r_else
multiline_comment|/* we must set the &quot;Accessed&quot; bit as IVE doesn&squot;t emulate it */
id|entry
op_assign
id|IA32_SEG_DESCRIPTOR
c_func
(paren
id|ldt_info.base_addr
comma
id|ldt_info.limit
comma
(paren
(paren
(paren
id|ldt_info.read_exec_only
op_xor
l_int|1
)paren
op_lshift
l_int|1
)paren
op_or
(paren
id|ldt_info.contents
op_lshift
l_int|2
)paren
)paren
op_or
l_int|1
comma
l_int|1
comma
l_int|3
comma
id|ldt_info.seg_not_present
op_xor
l_int|1
comma
(paren
id|oldmode
ques
c_cond
l_int|0
suffix:colon
id|ldt_info.useable
)paren
comma
id|ldt_info.seg_32bit
comma
id|ldt_info.limit_in_pages
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Install the new entry.  We know we&squot;re accessing valid (mapped) user-level&n;&t; * memory, but we still need to guard against out-of-memory, hence we must use&n;&t; * put_user().&n;&t; */
id|ret
op_assign
id|__put_user
c_func
(paren
id|entry
comma
(paren
id|__u64
id|__user
op_star
)paren
id|IA32_LDT_OFFSET
op_plus
id|ldt_info.entry_number
)paren
suffix:semicolon
id|ia32_load_segment_descriptors
c_func
(paren
id|current
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|asmlinkage
r_int
DECL|function|sys32_modify_ldt
id|sys32_modify_ldt
(paren
r_int
id|func
comma
r_int
r_int
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
id|compat_ptr
c_func
(paren
id|ptr
)paren
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
id|compat_ptr
c_func
(paren
id|ptr
)paren
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
id|compat_ptr
c_func
(paren
id|ptr
)paren
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
id|compat_ptr
c_func
(paren
id|ptr
)paren
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
