macro_line|#ident &quot;$Id: cpuid.c,v 1.4 2001/10/24 23:58:53 ak Exp $&quot;
multiline_comment|/* ----------------------------------------------------------------------- *&n; *   &n; *   Copyright 2000 H. Peter Anvin - All Rights Reserved&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation, Inc., 675 Mass Ave, Cambridge MA 02139,&n; *   USA; either version 2 of the License, or (at your option) any later&n; *   version; incorporated herein by reference.&n; *&n; * ----------------------------------------------------------------------- */
multiline_comment|/*&n; * cpuid.c&n; *&n; * x86 CPUID access device&n; *&n; * This device is accessed by lseek() to the appropriate CPUID level&n; * and then read in chunks of 16 bytes.  A larger size means multiple&n; * reads of consecutive levels.&n; *&n; * This driver uses /dev/cpu/%d/cpuid where %d is the minor number, and on&n; * an SMP box will direct the access to CPU %d.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/msr.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#ifdef CONFIG_SMP
DECL|struct|cpuid_command
r_struct
id|cpuid_command
(brace
DECL|member|cpu
r_int
id|cpu
suffix:semicolon
DECL|member|reg
id|u32
id|reg
suffix:semicolon
DECL|member|data
id|u32
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
DECL|function|cpuid_smp_cpuid
r_static
r_void
id|cpuid_smp_cpuid
c_func
(paren
r_void
op_star
id|cmd_block
)paren
(brace
r_struct
id|cpuid_command
op_star
id|cmd
op_assign
(paren
r_struct
id|cpuid_command
op_star
)paren
id|cmd_block
suffix:semicolon
r_if
c_cond
(paren
id|cmd-&gt;cpu
op_eq
id|smp_processor_id
c_func
(paren
)paren
)paren
id|cpuid
c_func
(paren
id|cmd-&gt;reg
comma
op_amp
id|cmd-&gt;data
(braket
l_int|0
)braket
comma
op_amp
id|cmd-&gt;data
(braket
l_int|1
)braket
comma
op_amp
id|cmd-&gt;data
(braket
l_int|2
)braket
comma
op_amp
id|cmd-&gt;data
(braket
l_int|3
)braket
)paren
suffix:semicolon
)brace
DECL|function|do_cpuid
r_static
r_inline
r_void
id|do_cpuid
c_func
(paren
r_int
id|cpu
comma
id|u32
id|reg
comma
id|u32
op_star
id|data
)paren
(brace
r_struct
id|cpuid_command
id|cmd
suffix:semicolon
r_if
c_cond
(paren
id|cpu
op_eq
id|smp_processor_id
c_func
(paren
)paren
)paren
(brace
id|cpuid
c_func
(paren
id|reg
comma
op_amp
id|data
(braket
l_int|0
)braket
comma
op_amp
id|data
(braket
l_int|1
)braket
comma
op_amp
id|data
(braket
l_int|2
)braket
comma
op_amp
id|data
(braket
l_int|3
)braket
)paren
suffix:semicolon
)brace
r_else
(brace
id|cmd.cpu
op_assign
id|cpu
suffix:semicolon
id|cmd.reg
op_assign
id|reg
suffix:semicolon
id|cmd.data
op_assign
id|data
suffix:semicolon
id|smp_call_function
c_func
(paren
id|cpuid_smp_cpuid
comma
op_amp
id|cmd
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
)brace
)brace
macro_line|#else /* ! CONFIG_SMP */
DECL|function|do_cpuid
r_static
r_inline
r_void
id|do_cpuid
c_func
(paren
r_int
id|cpu
comma
id|u32
id|reg
comma
id|u32
op_star
id|data
)paren
(brace
id|cpuid
c_func
(paren
id|reg
comma
op_amp
id|data
(braket
l_int|0
)braket
comma
op_amp
id|data
(braket
l_int|1
)braket
comma
op_amp
id|data
(braket
l_int|2
)braket
comma
op_amp
id|data
(braket
l_int|3
)braket
)paren
suffix:semicolon
)brace
macro_line|#endif /* ! CONFIG_SMP */
DECL|function|cpuid_seek
r_static
id|loff_t
id|cpuid_seek
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|loff_t
id|offset
comma
r_int
id|orig
)paren
(brace
id|loff_t
id|ret
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|orig
)paren
(brace
r_case
l_int|0
suffix:colon
id|file-&gt;f_pos
op_assign
id|offset
suffix:semicolon
id|ret
op_assign
id|file-&gt;f_pos
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|file-&gt;f_pos
op_add_assign
id|offset
suffix:semicolon
id|ret
op_assign
id|file-&gt;f_pos
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|cpuid_read
r_static
id|ssize_t
id|cpuid_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
id|u32
op_star
id|tmp
op_assign
(paren
id|u32
op_star
)paren
id|buf
suffix:semicolon
id|u32
id|data
(braket
l_int|4
)braket
suffix:semicolon
r_int
id|rv
suffix:semicolon
id|u32
id|reg
op_assign
op_star
id|ppos
suffix:semicolon
r_int
id|cpu
op_assign
id|minor
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_rdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_mod
l_int|16
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Invalid chunk size */
r_for
c_loop
(paren
id|rv
op_assign
l_int|0
suffix:semicolon
id|count
suffix:semicolon
id|count
op_sub_assign
l_int|16
)paren
(brace
id|do_cpuid
c_func
(paren
id|cpu
comma
id|reg
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|tmp
comma
op_amp
id|data
comma
l_int|16
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|tmp
op_add_assign
l_int|4
suffix:semicolon
op_star
id|ppos
op_assign
id|reg
op_increment
suffix:semicolon
)brace
r_return
(paren
(paren
r_char
op_star
)paren
id|tmp
)paren
op_minus
id|buf
suffix:semicolon
)brace
DECL|function|cpuid_open
r_static
r_int
id|cpuid_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_int
id|cpu
op_assign
id|minor
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_rdev
)paren
suffix:semicolon
r_struct
id|cpuinfo_x86
op_star
id|c
op_assign
op_amp
(paren
id|cpu_data
)paren
(braket
id|cpu
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|cpu_online_map
op_amp
(paren
l_int|1UL
op_lshift
id|cpu
)paren
)paren
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
multiline_comment|/* No such CPU */
r_if
c_cond
(paren
id|c-&gt;cpuid_level
OL
l_int|0
)paren
r_return
op_minus
id|EIO
suffix:semicolon
multiline_comment|/* CPUID not supported */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * File operations we support&n; */
DECL|variable|cpuid_fops
r_static
r_struct
id|file_operations
id|cpuid_fops
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|llseek
suffix:colon
id|cpuid_seek
comma
id|read
suffix:colon
id|cpuid_read
comma
id|open
suffix:colon
id|cpuid_open
comma
)brace
suffix:semicolon
DECL|function|cpuid_init
r_int
id|__init
id|cpuid_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|register_chrdev
c_func
(paren
id|CPUID_MAJOR
comma
l_string|&quot;cpu/cpuid&quot;
comma
op_amp
id|cpuid_fops
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cpuid: unable to get major %d for cpuid&bslash;n&quot;
comma
id|CPUID_MAJOR
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cpuid_exit
r_void
id|__exit
id|cpuid_exit
c_func
(paren
r_void
)paren
(brace
id|unregister_chrdev
c_func
(paren
id|CPUID_MAJOR
comma
l_string|&quot;cpu/cpuid&quot;
)paren
suffix:semicolon
)brace
DECL|variable|cpuid_init
id|module_init
c_func
(paren
id|cpuid_init
)paren
suffix:semicolon
id|module_exit
c_func
(paren
id|cpuid_exit
)paren
id|EXPORT_NO_SYMBOLS
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;H. Peter Anvin &lt;hpa@zytor.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;x86 generic CPUID driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
