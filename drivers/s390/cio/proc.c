multiline_comment|/*&n; *  drivers/s390/cio/proc.c&n; *   S/390 common I/O routines -- proc file system entries&n; *   $Revision: 1.4 $&n; *&n; *    Copyright (C) 1999-2002 IBM Deutschland Entwicklung GmbH,&n; *                            IBM Corporation&n; *    Author(s): Ingo Adlung (adlung@de.ibm.com)&n; *               Cornelia Huck (cohuck@de.ibm.com) &n; *&t;&t; Arnd Bergmann (arndb@de.ibm.com)&n; *    ChangeLog: 11/04/2002 Arnd Bergmann Split s390io.c into multiple files,&n; *&t;&t;&t;&t;&t;  see s390io.c for complete list of&n; * &t;&t;&t;&t;&t;  changes.&n; *               05/03/2002 Cornelia Huck  removed /proc/deviceinfo/&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/s390io.h&gt;
macro_line|#include &lt;asm/debug.h&gt;
macro_line|#include &quot;ioinfo.h&quot;
macro_line|#include &quot;s390io.h&quot;
macro_line|#include &quot;cio_debug.h&quot;
r_static
r_int
id|chan_proc_init
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* &n; * Display info on subchannels in /proc/subchannels. &n; * Adapted from procfs stuff in dasd.c by Cornelia Huck, 02/28/01.      &n; */
r_typedef
r_struct
(brace
DECL|member|data
r_char
op_star
id|data
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|typedef|tempinfo_t
)brace
id|tempinfo_t
suffix:semicolon
DECL|variable|chan_subch_entry
r_static
r_struct
id|proc_dir_entry
op_star
id|chan_subch_entry
suffix:semicolon
r_static
r_int
DECL|function|chan_subch_open
id|chan_subch_open
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
id|rc
op_assign
l_int|0
suffix:semicolon
r_int
id|size
op_assign
l_int|1
suffix:semicolon
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_int
id|j
op_assign
l_int|0
suffix:semicolon
id|tempinfo_t
op_star
id|info
suffix:semicolon
id|info
op_assign
(paren
id|tempinfo_t
op_star
)paren
id|vmalloc
(paren
r_sizeof
(paren
id|tempinfo_t
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info
op_eq
l_int|NULL
)paren
(brace
id|printk
(paren
id|KERN_WARNING
l_string|&quot;No memory available for data&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_else
(brace
id|file-&gt;private_data
op_assign
(paren
r_void
op_star
)paren
id|info
suffix:semicolon
)brace
id|size
op_add_assign
(paren
id|highest_subchannel
op_plus
l_int|1
)paren
op_star
l_int|128
suffix:semicolon
id|info-&gt;data
op_assign
(paren
r_char
op_star
)paren
id|vmalloc
(paren
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
op_logical_and
id|info-&gt;data
op_eq
l_int|NULL
)paren
(brace
id|printk
(paren
id|KERN_WARNING
l_string|&quot;No memory available for data&bslash;n&quot;
)paren
suffix:semicolon
id|vfree
(paren
id|info
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|len
op_add_assign
id|sprintf
(paren
id|info-&gt;data
op_plus
id|len
comma
l_string|&quot;Device sch.  Dev Type/Model CU  in use  PIM PAM POM CHPIDs&bslash;n&quot;
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
(paren
id|info-&gt;data
op_plus
id|len
comma
l_string|&quot;---------------------------------------------------------------------&bslash;n&quot;
)paren
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
id|highest_subchannel
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|ioinfo
(braket
id|i
)braket
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|ioinfo
(braket
id|i
)braket
op_eq
id|INVALID_STORAGE_AREA
)paren
op_logical_or
(paren
id|ioinfo
(braket
id|i
)braket
op_member_access_from_pointer
id|st
)paren
op_logical_or
op_logical_neg
(paren
id|ioinfo
(braket
id|i
)braket
op_member_access_from_pointer
id|ui.flags.oper
)paren
)paren
)paren
(brace
id|len
op_add_assign
id|sprintf
(paren
id|info-&gt;data
op_plus
id|len
comma
l_string|&quot;%04X   %04X  &quot;
comma
id|ioinfo
(braket
id|i
)braket
op_member_access_from_pointer
id|schib.pmcw.dev
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ioinfo
(braket
id|i
)braket
op_member_access_from_pointer
id|senseid.dev_type
op_ne
l_int|0
)paren
(brace
id|len
op_add_assign
id|sprintf
(paren
id|info-&gt;data
op_plus
id|len
comma
l_string|&quot;%04X/%02X   %04X/%02X&quot;
comma
id|ioinfo
(braket
id|i
)braket
op_member_access_from_pointer
id|senseid.dev_type
comma
id|ioinfo
(braket
id|i
)braket
op_member_access_from_pointer
id|senseid.dev_model
comma
id|ioinfo
(braket
id|i
)braket
op_member_access_from_pointer
id|senseid.cu_type
comma
id|ioinfo
(braket
id|i
)braket
op_member_access_from_pointer
id|senseid.cu_model
)paren
suffix:semicolon
)brace
r_else
(brace
id|len
op_add_assign
id|sprintf
(paren
id|info-&gt;data
op_plus
id|len
comma
l_string|&quot;          %04X/%02X&quot;
comma
id|ioinfo
(braket
id|i
)braket
op_member_access_from_pointer
id|senseid.cu_type
comma
id|ioinfo
(braket
id|i
)braket
op_member_access_from_pointer
id|senseid.cu_model
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ioinfo
(braket
id|i
)braket
op_member_access_from_pointer
id|ui.flags.ready
)paren
(brace
id|len
op_add_assign
id|sprintf
(paren
id|info-&gt;data
op_plus
id|len
comma
l_string|&quot;  yes &quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|len
op_add_assign
id|sprintf
(paren
id|info-&gt;data
op_plus
id|len
comma
l_string|&quot;      &quot;
)paren
suffix:semicolon
)brace
id|len
op_add_assign
id|sprintf
(paren
id|info-&gt;data
op_plus
id|len
comma
l_string|&quot;    %02X  %02X  %02X  &quot;
comma
id|ioinfo
(braket
id|i
)braket
op_member_access_from_pointer
id|schib.pmcw.pim
comma
id|ioinfo
(braket
id|i
)braket
op_member_access_from_pointer
id|schib.pmcw.pam
comma
id|ioinfo
(braket
id|i
)braket
op_member_access_from_pointer
id|schib.pmcw.pom
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|8
suffix:semicolon
id|j
op_increment
)paren
(brace
id|len
op_add_assign
id|sprintf
(paren
id|info-&gt;data
op_plus
id|len
comma
l_string|&quot;%02X&quot;
comma
id|ioinfo
(braket
id|i
)braket
op_member_access_from_pointer
id|schib.pmcw.chpid
(braket
id|j
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|j
op_eq
l_int|3
)paren
(brace
id|len
op_add_assign
id|sprintf
(paren
id|info-&gt;data
op_plus
id|len
comma
l_string|&quot; &quot;
)paren
suffix:semicolon
)brace
)brace
id|len
op_add_assign
id|sprintf
(paren
id|info-&gt;data
op_plus
id|len
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
id|info-&gt;len
op_assign
id|len
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
r_static
r_int
DECL|function|chan_subch_close
id|chan_subch_close
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
id|rc
op_assign
l_int|0
suffix:semicolon
id|tempinfo_t
op_star
id|p_info
op_assign
(paren
id|tempinfo_t
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|p_info
)paren
(brace
r_if
c_cond
(paren
id|p_info-&gt;data
)paren
id|vfree
(paren
id|p_info-&gt;data
)paren
suffix:semicolon
id|vfree
(paren
id|p_info
)paren
suffix:semicolon
)brace
r_return
id|rc
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|chan_subch_read
id|chan_subch_read
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|user_buf
comma
r_int
id|user_len
comma
id|loff_t
op_star
id|offset
)paren
(brace
id|loff_t
id|len
suffix:semicolon
id|tempinfo_t
op_star
id|p_info
op_assign
(paren
id|tempinfo_t
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
op_star
id|offset
op_ge
id|p_info-&gt;len
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|len
op_assign
id|min
(paren
(paren
r_int
)paren
id|user_len
comma
(paren
r_int
)paren
(paren
id|p_info-&gt;len
op_minus
op_star
id|offset
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
(paren
id|user_buf
comma
op_amp
(paren
id|p_info-&gt;data
(braket
op_star
id|offset
)braket
)paren
comma
id|len
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
(paren
op_star
id|offset
)paren
op_add_assign
id|len
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
)brace
DECL|variable|chan_subch_file_ops
r_static
r_struct
id|file_operations
id|chan_subch_file_ops
op_assign
(brace
id|read
suffix:colon
id|chan_subch_read
comma
id|open
suffix:colon
id|chan_subch_open
comma
id|release
suffix:colon
id|chan_subch_close
comma
)brace
suffix:semicolon
r_static
r_int
DECL|function|chan_proc_init
id|chan_proc_init
(paren
r_void
)paren
(brace
id|chan_subch_entry
op_assign
id|create_proc_entry
(paren
l_string|&quot;subchannels&quot;
comma
id|S_IFREG
op_or
id|S_IRUGO
comma
op_amp
id|proc_root
)paren
suffix:semicolon
id|chan_subch_entry-&gt;proc_fops
op_assign
op_amp
id|chan_subch_file_ops
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|chan_proc_init
id|__initcall
(paren
id|chan_proc_init
)paren
suffix:semicolon
multiline_comment|/*&n; * Entry /proc/irq_count&n; * display how many irqs have occured per cpu...&n; */
DECL|variable|cio_irq_proc_entry
r_static
r_struct
id|proc_dir_entry
op_star
id|cio_irq_proc_entry
suffix:semicolon
r_static
r_int
DECL|function|cio_irq_proc_open
id|cio_irq_proc_open
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
id|rc
op_assign
l_int|0
suffix:semicolon
r_int
id|size
op_assign
l_int|1
suffix:semicolon
r_int
id|len
op_assign
l_int|0
suffix:semicolon
id|tempinfo_t
op_star
id|info
suffix:semicolon
r_int
id|i
suffix:semicolon
id|info
op_assign
(paren
id|tempinfo_t
op_star
)paren
id|vmalloc
(paren
r_sizeof
(paren
id|tempinfo_t
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info
op_eq
l_int|NULL
)paren
(brace
id|printk
(paren
id|KERN_WARNING
l_string|&quot;No memory available for data&bslash;n&quot;
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_else
(brace
id|file-&gt;private_data
op_assign
(paren
r_void
op_star
)paren
id|info
suffix:semicolon
id|size
op_add_assign
id|NR_CPUS
op_star
l_int|16
suffix:semicolon
id|info-&gt;data
op_assign
(paren
r_char
op_star
)paren
id|vmalloc
(paren
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
op_logical_and
id|info-&gt;data
op_eq
l_int|NULL
)paren
(brace
id|printk
(paren
id|KERN_WARNING
l_string|&quot;No memory available for data&bslash;n&quot;
)paren
suffix:semicolon
id|vfree
(paren
id|info
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_else
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_CPUS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|s390_irq_count
(braket
id|i
)braket
op_ne
l_int|0
)paren
id|len
op_add_assign
id|sprintf
(paren
id|info-&gt;data
op_plus
id|len
comma
l_string|&quot;%lx&bslash;n&quot;
comma
id|s390_irq_count
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|info-&gt;len
op_assign
id|len
suffix:semicolon
)brace
)brace
r_return
id|rc
suffix:semicolon
)brace
r_static
r_int
DECL|function|cio_irq_proc_close
id|cio_irq_proc_close
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
id|rc
op_assign
l_int|0
suffix:semicolon
id|tempinfo_t
op_star
id|p_info
op_assign
(paren
id|tempinfo_t
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|p_info
)paren
(brace
r_if
c_cond
(paren
id|p_info-&gt;data
)paren
id|vfree
(paren
id|p_info-&gt;data
)paren
suffix:semicolon
id|vfree
(paren
id|p_info
)paren
suffix:semicolon
)brace
r_return
id|rc
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|cio_irq_proc_read
id|cio_irq_proc_read
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|user_buf
comma
r_int
id|user_len
comma
id|loff_t
op_star
id|offset
)paren
(brace
id|loff_t
id|len
suffix:semicolon
id|tempinfo_t
op_star
id|p_info
op_assign
(paren
id|tempinfo_t
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
op_star
id|offset
op_ge
id|p_info-&gt;len
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|len
op_assign
id|min
(paren
(paren
r_int
)paren
id|user_len
comma
(paren
r_int
)paren
(paren
id|p_info-&gt;len
op_minus
op_star
id|offset
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
(paren
id|user_buf
comma
op_amp
(paren
id|p_info-&gt;data
(braket
op_star
id|offset
)braket
)paren
comma
id|len
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
(paren
op_star
id|offset
)paren
op_add_assign
id|len
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
)brace
DECL|variable|cio_irq_proc_file_ops
r_static
r_struct
id|file_operations
id|cio_irq_proc_file_ops
op_assign
(brace
id|read
suffix:colon
id|cio_irq_proc_read
comma
id|open
suffix:colon
id|cio_irq_proc_open
comma
id|release
suffix:colon
id|cio_irq_proc_close
comma
)brace
suffix:semicolon
r_static
r_int
DECL|function|cio_irq_proc_init
id|cio_irq_proc_init
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|cio_count_irqs
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_CPUS
suffix:semicolon
id|i
op_increment
)paren
id|s390_irq_count
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|cio_irq_proc_entry
op_assign
id|create_proc_entry
(paren
l_string|&quot;irq_count&quot;
comma
id|S_IFREG
op_or
id|S_IRUGO
comma
op_amp
id|proc_root
)paren
suffix:semicolon
id|cio_irq_proc_entry-&gt;proc_fops
op_assign
op_amp
id|cio_irq_proc_file_ops
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|cio_irq_proc_init
id|__initcall
(paren
id|cio_irq_proc_init
)paren
suffix:semicolon
eof