multiline_comment|/*&n; * MIPS specific syscalls&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995, 1996, 1997, 2000 by Ralf Baechle&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;asm/cachectl.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/sysmips.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
r_extern
id|asmlinkage
r_void
id|syscall_trace
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * How long a hostname can we get from user space?&n; *  -EFAULT if invalid area or too long&n; *  0 if ok&n; *  &gt;0 EFAULT after xx bytes&n; */
r_static
r_inline
r_int
DECL|function|get_max_hostname
id|get_max_hostname
c_func
(paren
r_int
r_int
id|address
)paren
(brace
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
id|vma
op_assign
id|find_vma
c_func
(paren
id|current-&gt;mm
comma
id|address
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
id|address
op_logical_or
op_logical_neg
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_READ
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|address
op_assign
id|vma-&gt;vm_end
op_minus
id|address
suffix:semicolon
r_if
c_cond
(paren
id|address
OG
id|PAGE_SIZE
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_next
op_logical_and
id|vma-&gt;vm_next-&gt;vm_start
op_eq
id|vma-&gt;vm_end
op_logical_and
(paren
id|vma-&gt;vm_next-&gt;vm_flags
op_amp
id|VM_READ
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|address
suffix:semicolon
)brace
id|asmlinkage
r_int
DECL|function|sys_sysmips
id|sys_sysmips
c_func
(paren
r_int
id|cmd
comma
r_int
id|arg1
comma
r_int
id|arg2
comma
r_int
id|arg3
)paren
(brace
r_int
op_star
id|p
suffix:semicolon
r_char
op_star
id|name
suffix:semicolon
r_int
id|tmp
comma
id|len
comma
id|retval
comma
id|errno
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SETNAME
suffix:colon
(brace
r_char
id|nodename
(braket
id|__NEW_UTS_LEN
op_plus
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|name
op_assign
(paren
r_char
op_star
)paren
id|arg1
suffix:semicolon
id|len
op_assign
id|strncpy_from_user
c_func
(paren
id|nodename
comma
id|name
comma
id|__NEW_UTS_LEN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|nodename
(braket
id|__NEW_UTS_LEN
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|uts_sem
)paren
suffix:semicolon
id|strlcpy
c_func
(paren
id|system_utsname.nodename
comma
id|nodename
comma
r_sizeof
(paren
id|system_utsname.nodename
)paren
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|uts_sem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|MIPS_ATOMIC_SET
suffix:colon
(brace
macro_line|#ifdef CONFIG_CPU_HAS_LLSC
r_int
r_int
id|tmp
suffix:semicolon
id|p
op_assign
(paren
r_int
op_star
)paren
id|arg1
suffix:semicolon
id|errno
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|p
comma
r_sizeof
(paren
op_star
id|p
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|errno
)paren
r_return
id|errno
suffix:semicolon
id|errno
op_assign
l_int|0
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;.set&bslash;tpush&bslash;t&bslash;t&bslash;t# sysmips(MIPS_ATOMIC, ...)&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tmips2&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoat&bslash;n&bslash;t&quot;
l_string|&quot;1:&bslash;tll&bslash;t%0, %4&bslash;n&bslash;t&quot;
l_string|&quot;move&bslash;t$1, %3&bslash;n&bslash;t&quot;
l_string|&quot;2:&bslash;tsc&bslash;t$1, %1&bslash;n&bslash;t&quot;
l_string|&quot;beqz&bslash;t$1, 1b&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tpop&bslash;n&bslash;t&quot;
l_string|&quot;.section&bslash;t.fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;3:&bslash;tli&bslash;t%2, 1&bslash;t&bslash;t&bslash;t# error&bslash;n&bslash;t&quot;
l_string|&quot;.previous&bslash;n&bslash;t&quot;
l_string|&quot;.section&bslash;t__ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot;
l_string|&quot;.word&bslash;t1b, 3b&bslash;n&bslash;t&quot;
l_string|&quot;.word&bslash;t2b, 3b&bslash;n&bslash;t&quot;
l_string|&quot;.previous&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=o&quot;
(paren
op_star
(paren
id|u32
op_star
)paren
id|p
)paren
comma
l_string|&quot;=r&quot;
(paren
id|errno
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|arg2
)paren
comma
l_string|&quot;o&quot;
(paren
op_star
(paren
id|u32
op_star
)paren
id|p
)paren
comma
l_string|&quot;2&quot;
(paren
id|errno
)paren
suffix:colon
l_string|&quot;$1&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|errno
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
multiline_comment|/* We&squot;re skipping error handling etc.  */
r_if
c_cond
(paren
id|current-&gt;ptrace
op_amp
id|PT_TRACESYS
)paren
id|syscall_trace
c_func
(paren
)paren
suffix:semicolon
(paren
(paren
r_struct
id|pt_regs
op_star
)paren
op_amp
id|cmd
)paren
op_member_access_from_pointer
id|regs
(braket
l_int|2
)braket
op_assign
id|tmp
suffix:semicolon
(paren
(paren
r_struct
id|pt_regs
op_star
)paren
op_amp
id|cmd
)paren
op_member_access_from_pointer
id|regs
(braket
l_int|7
)braket
op_assign
l_int|0
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;move&bslash;t$29, %0&bslash;n&bslash;t&quot;
l_string|&quot;j&bslash;to32_ret_from_sys_call&quot;
suffix:colon
multiline_comment|/* No outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|cmd
)paren
)paren
suffix:semicolon
multiline_comment|/* Unreached */
macro_line|#else
id|printk
c_func
(paren
l_string|&quot;sys_sysmips(MIPS_ATOMIC_SET, ...) not ready for !CONFIG_CPU_HAS_LLSC&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
r_case
id|MIPS_FIXADE
suffix:colon
id|tmp
op_assign
id|current-&gt;thread.mflags
op_amp
op_complement
l_int|3
suffix:semicolon
id|current-&gt;thread.mflags
op_assign
id|tmp
op_or
(paren
id|arg1
op_amp
l_int|3
)paren
suffix:semicolon
id|retval
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|FLUSH_CACHE
suffix:colon
id|flush_cache_all
c_func
(paren
)paren
suffix:semicolon
id|retval
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|MIPS_RDNVRAM
suffix:colon
id|retval
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_default
suffix:colon
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; * No implemented yet ...&n; */
id|asmlinkage
r_int
DECL|function|sys_cachectl
id|sys_cachectl
c_func
(paren
r_char
op_star
id|addr
comma
r_int
id|nbytes
comma
r_int
id|op
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
eof
