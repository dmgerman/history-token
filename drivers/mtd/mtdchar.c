multiline_comment|/*&n; * $Id: mtdchar.c,v 1.44 2001/10/02 15:05:11 dwmw2 Exp $&n; *&n; * Character-device access to raw MTD devices.&n; * Pure 2.4 version - compatibility cruft removed to mtdchar-compat.c&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#ifdef CONFIG_DEVFS_FS
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
r_static
r_void
id|mtd_notify_add
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
suffix:semicolon
r_static
r_void
id|mtd_notify_remove
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
suffix:semicolon
DECL|variable|notifier
r_static
r_struct
id|mtd_notifier
id|notifier
op_assign
(brace
id|add
suffix:colon
id|mtd_notify_add
comma
id|remove
suffix:colon
id|mtd_notify_remove
comma
)brace
suffix:semicolon
macro_line|#endif
DECL|function|mtd_lseek
r_static
id|loff_t
id|mtd_lseek
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
r_struct
id|mtd_info
op_star
id|mtd
op_assign
(paren
r_struct
id|mtd_info
op_star
)paren
id|file-&gt;private_data
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
multiline_comment|/* SEEK_SET */
id|file-&gt;f_pos
op_assign
id|offset
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* SEEK_CUR */
id|file-&gt;f_pos
op_add_assign
id|offset
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/* SEEK_END */
id|file-&gt;f_pos
op_assign
id|mtd-&gt;size
op_plus
id|offset
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|file-&gt;f_pos
OL
l_int|0
)paren
id|file-&gt;f_pos
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|file-&gt;f_pos
op_ge
id|mtd-&gt;size
)paren
id|file-&gt;f_pos
op_assign
id|mtd-&gt;size
op_minus
l_int|1
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|file-&gt;f_pos
suffix:semicolon
)brace
DECL|function|mtd_open
r_static
r_int
id|mtd_open
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
id|minor
op_assign
id|minor
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_int
id|devnum
op_assign
id|minor
op_rshift
l_int|1
suffix:semicolon
r_struct
id|mtd_info
op_star
id|mtd
suffix:semicolon
id|DEBUG
c_func
(paren
id|MTD_DEBUG_LEVEL0
comma
l_string|&quot;MTD_open&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|devnum
op_ge
id|MAX_MTD_DEVICES
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* You can&squot;t open the RO devices RW */
r_if
c_cond
(paren
(paren
id|file-&gt;f_mode
op_amp
l_int|2
)paren
op_logical_and
(paren
id|minor
op_amp
l_int|1
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
id|mtd
op_assign
id|get_mtd_device
c_func
(paren
l_int|NULL
comma
id|devnum
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mtd
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|MTD_ABSENT
op_eq
id|mtd-&gt;type
)paren
(brace
id|put_mtd_device
c_func
(paren
id|mtd
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|file-&gt;private_data
op_assign
id|mtd
suffix:semicolon
multiline_comment|/* You can&squot;t open it RW if it&squot;s not a writeable device */
r_if
c_cond
(paren
(paren
id|file-&gt;f_mode
op_amp
l_int|2
)paren
op_logical_and
op_logical_neg
(paren
id|mtd-&gt;flags
op_amp
id|MTD_WRITEABLE
)paren
)paren
(brace
id|put_mtd_device
c_func
(paren
id|mtd
)paren
suffix:semicolon
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* mtd_open */
multiline_comment|/*====================================================================*/
DECL|function|mtd_close
r_static
r_int
id|mtd_close
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
r_struct
id|mtd_info
op_star
id|mtd
suffix:semicolon
id|DEBUG
c_func
(paren
id|MTD_DEBUG_LEVEL0
comma
l_string|&quot;MTD_close&bslash;n&quot;
)paren
suffix:semicolon
id|mtd
op_assign
(paren
r_struct
id|mtd_info
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|mtd-&gt;sync
)paren
id|mtd
op_member_access_from_pointer
id|sync
c_func
(paren
id|mtd
)paren
suffix:semicolon
id|put_mtd_device
c_func
(paren
id|mtd
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* mtd_close */
multiline_comment|/* FIXME: This _really_ needs to die. In 2.5, we should lock the&n;   userspace buffer down and use it directly with readv/writev.&n;*/
DECL|macro|MAX_KMALLOC_SIZE
mdefine_line|#define MAX_KMALLOC_SIZE 0x20000
DECL|function|mtd_read
r_static
id|ssize_t
id|mtd_read
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
r_struct
id|mtd_info
op_star
id|mtd
op_assign
(paren
r_struct
id|mtd_info
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_int
id|retlen
op_assign
l_int|0
suffix:semicolon
r_int
id|total_retlen
op_assign
l_int|0
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
id|len
suffix:semicolon
r_char
op_star
id|kbuf
suffix:semicolon
id|DEBUG
c_func
(paren
id|MTD_DEBUG_LEVEL0
comma
l_string|&quot;MTD_read&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|ppos
op_plus
id|count
OG
id|mtd-&gt;size
)paren
id|count
op_assign
id|mtd-&gt;size
op_minus
op_star
id|ppos
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* FIXME: Use kiovec in 2.5 to lock down the user&squot;s buffers&n;&t;   and pass them directly to the MTD functions */
r_while
c_loop
(paren
id|count
)paren
(brace
r_if
c_cond
(paren
id|count
OG
id|MAX_KMALLOC_SIZE
)paren
id|len
op_assign
id|MAX_KMALLOC_SIZE
suffix:semicolon
r_else
id|len
op_assign
id|count
suffix:semicolon
id|kbuf
op_assign
id|kmalloc
c_func
(paren
id|len
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kbuf
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|ret
op_assign
id|MTD_READ
c_func
(paren
id|mtd
comma
op_star
id|ppos
comma
id|len
comma
op_amp
id|retlen
comma
id|kbuf
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
op_star
id|ppos
op_add_assign
id|retlen
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
id|kbuf
comma
id|retlen
)paren
)paren
(brace
id|kfree
c_func
(paren
id|kbuf
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_else
id|total_retlen
op_add_assign
id|retlen
suffix:semicolon
id|count
op_sub_assign
id|retlen
suffix:semicolon
id|buf
op_add_assign
id|retlen
suffix:semicolon
)brace
r_else
(brace
id|kfree
c_func
(paren
id|kbuf
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|kbuf
)paren
suffix:semicolon
)brace
r_return
id|total_retlen
suffix:semicolon
)brace
multiline_comment|/* mtd_read */
DECL|function|mtd_write
r_static
id|ssize_t
id|mtd_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
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
r_struct
id|mtd_info
op_star
id|mtd
op_assign
(paren
r_struct
id|mtd_info
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_char
op_star
id|kbuf
suffix:semicolon
r_int
id|retlen
suffix:semicolon
r_int
id|total_retlen
op_assign
l_int|0
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
id|len
suffix:semicolon
id|DEBUG
c_func
(paren
id|MTD_DEBUG_LEVEL0
comma
l_string|&quot;MTD_write&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|ppos
op_eq
id|mtd-&gt;size
)paren
r_return
op_minus
id|ENOSPC
suffix:semicolon
r_if
c_cond
(paren
op_star
id|ppos
op_plus
id|count
OG
id|mtd-&gt;size
)paren
id|count
op_assign
id|mtd-&gt;size
op_minus
op_star
id|ppos
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
r_return
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|count
)paren
(brace
r_if
c_cond
(paren
id|count
OG
id|MAX_KMALLOC_SIZE
)paren
id|len
op_assign
id|MAX_KMALLOC_SIZE
suffix:semicolon
r_else
id|len
op_assign
id|count
suffix:semicolon
id|kbuf
op_assign
id|kmalloc
c_func
(paren
id|len
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kbuf
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;kmalloc is null&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|kbuf
comma
id|buf
comma
id|len
)paren
)paren
(brace
id|kfree
c_func
(paren
id|kbuf
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|ret
op_assign
(paren
op_star
(paren
id|mtd-&gt;write
)paren
)paren
(paren
id|mtd
comma
op_star
id|ppos
comma
id|len
comma
op_amp
id|retlen
comma
id|kbuf
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
op_star
id|ppos
op_add_assign
id|retlen
suffix:semicolon
id|total_retlen
op_add_assign
id|retlen
suffix:semicolon
id|count
op_sub_assign
id|retlen
suffix:semicolon
id|buf
op_add_assign
id|retlen
suffix:semicolon
)brace
r_else
(brace
id|kfree
c_func
(paren
id|kbuf
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|kbuf
)paren
suffix:semicolon
)brace
r_return
id|total_retlen
suffix:semicolon
)brace
multiline_comment|/* mtd_write */
multiline_comment|/*======================================================================&n;&n;    IOCTL calls for getting device parameters.&n;&n;======================================================================*/
DECL|function|mtd_erase_callback
r_static
r_void
id|mtd_erase_callback
(paren
r_struct
id|erase_info
op_star
id|instr
)paren
(brace
id|wake_up
c_func
(paren
(paren
id|wait_queue_head_t
op_star
)paren
id|instr-&gt;priv
)paren
suffix:semicolon
)brace
DECL|function|mtd_ioctl
r_static
r_int
id|mtd_ioctl
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
comma
id|u_int
id|cmd
comma
id|u_long
id|arg
)paren
(brace
r_struct
id|mtd_info
op_star
id|mtd
op_assign
(paren
r_struct
id|mtd_info
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|u_long
id|size
suffix:semicolon
id|DEBUG
c_func
(paren
id|MTD_DEBUG_LEVEL0
comma
l_string|&quot;MTD_ioctl&bslash;n&quot;
)paren
suffix:semicolon
id|size
op_assign
(paren
id|cmd
op_amp
id|IOCSIZE_MASK
)paren
op_rshift
id|IOCSIZE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_amp
id|IOC_IN
)paren
(brace
id|ret
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
(paren
r_char
op_star
)paren
id|arg
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cmd
op_amp
id|IOC_OUT
)paren
(brace
id|ret
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
r_char
op_star
)paren
id|arg
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|MEMGETREGIONCOUNT
suffix:colon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_int
op_star
)paren
id|arg
comma
op_amp
(paren
id|mtd-&gt;numeraseregions
)paren
comma
r_sizeof
(paren
r_int
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MEMGETREGIONINFO
suffix:colon
(brace
r_struct
id|region_info_user
id|ur
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|ur
comma
(paren
r_struct
id|region_info_user
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_struct
id|region_info_user
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ur.regionindex
op_ge
id|mtd-&gt;numeraseregions
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_struct
id|mtd_erase_region_info
op_star
)paren
id|arg
comma
op_amp
(paren
id|mtd-&gt;eraseregions
(braket
id|ur.regionindex
)braket
)paren
comma
r_sizeof
(paren
r_struct
id|mtd_erase_region_info
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|MEMGETINFO
suffix:colon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_struct
id|mtd_info
op_star
)paren
id|arg
comma
id|mtd
comma
r_sizeof
(paren
r_struct
id|mtd_info_user
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MEMERASE
suffix:colon
(brace
r_struct
id|erase_info
op_star
id|erase
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|erase_info
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|erase
)paren
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_else
(brace
id|wait_queue_head_t
id|waitq
suffix:semicolon
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|waitq
)paren
suffix:semicolon
id|memset
(paren
id|erase
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|erase_info
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|erase-&gt;addr
comma
(paren
id|u_long
op_star
)paren
id|arg
comma
l_int|2
op_star
r_sizeof
(paren
id|u_long
)paren
)paren
)paren
(brace
id|kfree
c_func
(paren
id|erase
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|erase-&gt;mtd
op_assign
id|mtd
suffix:semicolon
id|erase-&gt;callback
op_assign
id|mtd_erase_callback
suffix:semicolon
id|erase-&gt;priv
op_assign
(paren
r_int
r_int
)paren
op_amp
id|waitq
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;  FIXME: Allow INTERRUPTIBLE. Which means&n;&t;&t;&t;  not having the wait_queue head on the stack.&n;&t;&t;&t;  &n;&t;&t;&t;  If the wq_head is on the stack, and we&n;&t;&t;&t;  leave because we got interrupted, then the&n;&t;&t;&t;  wq_head is no longer there when the&n;&t;&t;&t;  callback routine tries to wake us up.&n;&t;&t;&t;*/
id|ret
op_assign
id|mtd
op_member_access_from_pointer
id|erase
c_func
(paren
id|mtd
comma
id|erase
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|waitq
comma
op_amp
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|erase-&gt;state
op_ne
id|MTD_ERASE_DONE
op_logical_and
id|erase-&gt;state
op_ne
id|MTD_ERASE_FAILED
)paren
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|waitq
comma
op_amp
id|wait
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|ret
op_assign
(paren
id|erase-&gt;state
op_eq
id|MTD_ERASE_FAILED
)paren
ques
op_minus
id|EIO
suffix:colon
l_int|0
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|erase
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_case
id|MEMWRITEOOB
suffix:colon
(brace
r_struct
id|mtd_oob_buf
id|buf
suffix:semicolon
r_void
op_star
id|databuf
suffix:semicolon
id|ssize_t
id|retlen
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|buf
comma
(paren
r_struct
id|mtd_oob_buf
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_struct
id|mtd_oob_buf
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
id|buf.length
OG
l_int|0x4096
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mtd-&gt;write_oob
)paren
id|ret
op_assign
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_else
id|ret
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
(paren
r_char
op_star
)paren
id|buf.ptr
comma
id|buf.length
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
id|databuf
op_assign
id|kmalloc
c_func
(paren
id|buf.length
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|databuf
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|databuf
comma
id|buf.ptr
comma
id|buf.length
)paren
)paren
(brace
id|kfree
c_func
(paren
id|databuf
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|ret
op_assign
(paren
id|mtd-&gt;write_oob
)paren
(paren
id|mtd
comma
id|buf.start
comma
id|buf.length
comma
op_amp
id|retlen
comma
id|databuf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
op_plus
r_sizeof
(paren
id|u_int32_t
)paren
comma
op_amp
id|retlen
comma
r_sizeof
(paren
id|u_int32_t
)paren
)paren
)paren
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
id|kfree
c_func
(paren
id|databuf
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|MEMREADOOB
suffix:colon
(brace
r_struct
id|mtd_oob_buf
id|buf
suffix:semicolon
r_void
op_star
id|databuf
suffix:semicolon
id|ssize_t
id|retlen
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|buf
comma
(paren
r_struct
id|mtd_oob_buf
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_struct
id|mtd_oob_buf
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
id|buf.length
OG
l_int|0x4096
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mtd-&gt;read_oob
)paren
id|ret
op_assign
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_else
id|ret
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
r_char
op_star
)paren
id|buf.ptr
comma
id|buf.length
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
id|databuf
op_assign
id|kmalloc
c_func
(paren
id|buf.length
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|databuf
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|ret
op_assign
(paren
id|mtd-&gt;read_oob
)paren
(paren
id|mtd
comma
id|buf.start
comma
id|buf.length
comma
op_amp
id|retlen
comma
id|databuf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
op_plus
r_sizeof
(paren
id|u_int32_t
)paren
comma
op_amp
id|retlen
comma
r_sizeof
(paren
id|u_int32_t
)paren
)paren
)paren
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_else
r_if
c_cond
(paren
id|retlen
op_logical_and
id|copy_to_user
c_func
(paren
id|buf.ptr
comma
id|databuf
comma
id|retlen
)paren
)paren
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
id|kfree
c_func
(paren
id|databuf
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|MEMLOCK
suffix:colon
(brace
r_int
r_int
id|adrs
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|adrs
comma
(paren
r_void
op_star
)paren
id|arg
comma
l_int|2
op_star
r_sizeof
(paren
r_int
r_int
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
op_logical_neg
id|mtd-&gt;lock
)paren
id|ret
op_assign
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_else
id|ret
op_assign
id|mtd
op_member_access_from_pointer
id|lock
c_func
(paren
id|mtd
comma
id|adrs
(braket
l_int|0
)braket
comma
id|adrs
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|MEMUNLOCK
suffix:colon
(brace
r_int
r_int
id|adrs
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|adrs
comma
(paren
r_void
op_star
)paren
id|arg
comma
l_int|2
op_star
r_sizeof
(paren
r_int
r_int
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
op_logical_neg
id|mtd-&gt;unlock
)paren
id|ret
op_assign
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_else
id|ret
op_assign
id|mtd
op_member_access_from_pointer
id|unlock
c_func
(paren
id|mtd
comma
id|adrs
(braket
l_int|0
)braket
comma
id|adrs
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_default
suffix:colon
id|DEBUG
c_func
(paren
id|MTD_DEBUG_LEVEL0
comma
l_string|&quot;Invalid ioctl %x (MEMGETINFO = %x)&bslash;n&quot;
comma
id|cmd
comma
id|MEMGETINFO
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ENOTTY
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* memory_ioctl */
DECL|variable|mtd_fops
r_static
r_struct
id|file_operations
id|mtd_fops
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|llseek
suffix:colon
id|mtd_lseek
comma
multiline_comment|/* lseek */
id|read
suffix:colon
id|mtd_read
comma
multiline_comment|/* read */
id|write
suffix:colon
id|mtd_write
comma
multiline_comment|/* write */
id|ioctl
suffix:colon
id|mtd_ioctl
comma
multiline_comment|/* ioctl */
id|open
suffix:colon
id|mtd_open
comma
multiline_comment|/* open */
id|release
suffix:colon
id|mtd_close
comma
multiline_comment|/* release */
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_DEVFS_FS
multiline_comment|/* Notification that a new device has been added. Create the devfs entry for&n; * it. */
DECL|function|mtd_notify_add
r_static
r_void
id|mtd_notify_add
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
(brace
r_char
id|name
(braket
l_int|16
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mtd
)paren
r_return
suffix:semicolon
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;mtd/%d&quot;
comma
id|mtd-&gt;index
)paren
suffix:semicolon
id|devfs_register
c_func
(paren
l_int|NULL
comma
id|name
comma
id|DEVFS_FL_DEFAULT
comma
id|MTD_CHAR_MAJOR
comma
id|mtd-&gt;index
op_star
l_int|2
comma
id|S_IFCHR
op_or
id|S_IRUGO
op_or
id|S_IWUGO
comma
op_amp
id|mtd_fops
comma
l_int|NULL
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;mtd/%dro&quot;
comma
id|mtd-&gt;index
)paren
suffix:semicolon
id|devfs_register
c_func
(paren
l_int|NULL
comma
id|name
comma
id|DEVFS_FL_DEFAULT
comma
id|MTD_CHAR_MAJOR
comma
id|mtd-&gt;index
op_star
l_int|2
op_plus
l_int|1
comma
id|S_IFCHR
op_or
id|S_IRUGO
op_or
id|S_IWUGO
comma
op_amp
id|mtd_fops
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|mtd_notify_remove
r_static
r_void
id|mtd_notify_remove
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|mtd
)paren
r_return
suffix:semicolon
id|devfs_remove
c_func
(paren
l_string|&quot;mtd/%d&quot;
comma
id|mtd-&gt;index
)paren
suffix:semicolon
id|devfs_remove
c_func
(paren
l_string|&quot;mtd/%dro&quot;
comma
id|mtd-&gt;index
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|init_mtdchar
r_static
r_int
id|__init
id|init_mtdchar
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
id|MTD_CHAR_MAJOR
comma
l_string|&quot;mtd&quot;
comma
op_amp
id|mtd_fops
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Can&squot;t allocate major number %d for Memory Technology Devices.&bslash;n&quot;
comma
id|MTD_CHAR_MAJOR
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_DEVFS_FS
id|devfs_mk_dir
c_func
(paren
l_int|NULL
comma
l_string|&quot;mtd&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|register_mtd_user
c_func
(paren
op_amp
id|notifier
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_mtdchar
r_static
r_void
id|__exit
id|cleanup_mtdchar
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_DEVFS_FS
id|unregister_mtd_user
c_func
(paren
op_amp
id|notifier
)paren
suffix:semicolon
id|devfs_remove
c_func
(paren
l_string|&quot;mtd&quot;
)paren
suffix:semicolon
macro_line|#endif
id|unregister_chrdev
c_func
(paren
id|MTD_CHAR_MAJOR
comma
l_string|&quot;mtd&quot;
)paren
suffix:semicolon
)brace
DECL|variable|init_mtdchar
id|module_init
c_func
(paren
id|init_mtdchar
)paren
suffix:semicolon
DECL|variable|cleanup_mtdchar
id|module_exit
c_func
(paren
id|cleanup_mtdchar
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;David Woodhouse &lt;dwmw2@infradead.org&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Direct character-device access to MTD devices&quot;
)paren
suffix:semicolon
eof
