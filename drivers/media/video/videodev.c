multiline_comment|/*&n; * Video capture interface for Linux&n; *&n; *&t;&t;A generic video device interface for the LINUX operating system&n; *&t;&t;using a set of device structures/vectors for low level operations.&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; * Author:&t;Alan Cox, &lt;alan@redhat.com&gt;&n; *&n; * Fixes:&t;20000516  Claudio Matsuoka &lt;claudio@conectiva.com&gt;&n; *&t;&t;- Added procfs support&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;linux/videodev.h&gt;
DECL|macro|VIDEO_NUM_DEVICES
mdefine_line|#define VIDEO_NUM_DEVICES&t;256 
multiline_comment|/*&n; *&t;Active devices &n; */
DECL|variable|video_device
r_static
r_struct
id|video_device
op_star
id|video_device
(braket
id|VIDEO_NUM_DEVICES
)braket
suffix:semicolon
r_static
id|DECLARE_MUTEX
c_func
(paren
id|videodev_lock
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_VIDEO_PROC_FS
macro_line|#include &lt;linux/proc_fs.h&gt;
DECL|struct|videodev_proc_data
r_struct
id|videodev_proc_data
(brace
DECL|member|proc_list
r_struct
id|list_head
id|proc_list
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|vdev
r_struct
id|video_device
op_star
id|vdev
suffix:semicolon
DECL|member|proc_entry
r_struct
id|proc_dir_entry
op_star
id|proc_entry
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|video_dev_proc_entry
r_static
r_struct
id|proc_dir_entry
op_star
id|video_dev_proc_entry
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|video_proc_entry
r_struct
id|proc_dir_entry
op_star
id|video_proc_entry
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|video_proc_entry
id|EXPORT_SYMBOL
c_func
(paren
id|video_proc_entry
)paren
suffix:semicolon
DECL|variable|videodev_proc_list
id|LIST_HEAD
c_func
(paren
id|videodev_proc_list
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_VIDEO_PROC_FS */
DECL|function|video_devdata
r_struct
id|video_device
op_star
id|video_devdata
c_func
(paren
r_struct
id|file
op_star
id|file
)paren
(brace
r_return
id|video_device
(braket
id|minor
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_rdev
)paren
)braket
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Open a video device.&n; */
DECL|function|video_open
r_static
r_int
id|video_open
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
id|err
op_assign
l_int|0
suffix:semicolon
r_struct
id|video_device
op_star
id|vfl
suffix:semicolon
r_struct
id|file_operations
op_star
id|old_fops
suffix:semicolon
r_if
c_cond
(paren
id|minor
op_ge
id|VIDEO_NUM_DEVICES
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|down
c_func
(paren
op_amp
id|videodev_lock
)paren
suffix:semicolon
id|vfl
op_assign
id|video_device
(braket
id|minor
)braket
suffix:semicolon
r_if
c_cond
(paren
id|vfl
op_eq
l_int|NULL
)paren
(brace
r_char
id|modname
(braket
l_int|20
)braket
suffix:semicolon
id|up
c_func
(paren
op_amp
id|videodev_lock
)paren
suffix:semicolon
id|sprintf
(paren
id|modname
comma
l_string|&quot;char-major-%d-%d&quot;
comma
id|VIDEO_MAJOR
comma
id|minor
)paren
suffix:semicolon
id|request_module
c_func
(paren
id|modname
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|videodev_lock
)paren
suffix:semicolon
id|vfl
op_assign
id|video_device
(braket
id|minor
)braket
suffix:semicolon
r_if
c_cond
(paren
id|vfl
op_eq
l_int|NULL
)paren
(brace
id|up
c_func
(paren
op_amp
id|videodev_lock
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
)brace
id|old_fops
op_assign
id|file-&gt;f_op
suffix:semicolon
id|file-&gt;f_op
op_assign
id|fops_get
c_func
(paren
id|vfl-&gt;fops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_op-&gt;open
)paren
(brace
id|err
op_assign
id|file-&gt;f_op
op_member_access_from_pointer
id|open
c_func
(paren
id|inode
comma
id|file
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|err
)paren
(brace
id|fops_put
c_func
(paren
id|file-&gt;f_op
)paren
suffix:semicolon
id|file-&gt;f_op
op_assign
id|fops_get
c_func
(paren
id|old_fops
)paren
suffix:semicolon
)brace
id|fops_put
c_func
(paren
id|old_fops
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|videodev_lock
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * helper function -- handles userspace copying for ioctl arguments&n; */
r_int
DECL|function|video_usercopy
id|video_usercopy
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
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
comma
r_int
(paren
op_star
id|func
)paren
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
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
)paren
(brace
r_char
id|sbuf
(braket
l_int|128
)braket
suffix:semicolon
r_void
op_star
id|mbuf
op_assign
l_int|NULL
suffix:semicolon
r_void
op_star
id|parg
op_assign
l_int|NULL
suffix:semicolon
r_int
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/*  Copy arguments into temp kernel buffer  */
r_switch
c_cond
(paren
id|_IOC_DIR
c_func
(paren
id|cmd
)paren
)paren
(brace
r_case
id|_IOC_NONE
suffix:colon
id|parg
op_assign
(paren
r_void
op_star
)paren
id|arg
suffix:semicolon
r_break
suffix:semicolon
r_case
id|_IOC_READ
suffix:colon
multiline_comment|/* some v4l ioctls are marked wrong ... */
r_case
id|_IOC_WRITE
suffix:colon
r_case
(paren
id|_IOC_WRITE
op_or
id|_IOC_READ
)paren
suffix:colon
r_if
c_cond
(paren
id|_IOC_SIZE
c_func
(paren
id|cmd
)paren
op_le
r_sizeof
(paren
id|sbuf
)paren
)paren
(brace
id|parg
op_assign
id|sbuf
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* too big to allocate from stack */
id|mbuf
op_assign
id|kmalloc
c_func
(paren
id|_IOC_SIZE
c_func
(paren
id|cmd
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|mbuf
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|parg
op_assign
id|mbuf
suffix:semicolon
)brace
id|err
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
id|parg
comma
(paren
r_void
op_star
)paren
id|arg
comma
id|_IOC_SIZE
c_func
(paren
id|cmd
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* call driver */
id|err
op_assign
id|func
c_func
(paren
id|inode
comma
id|file
comma
id|cmd
comma
id|parg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_eq
op_minus
id|ENOIOCTLCMD
)paren
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/*  Copy results into user buffer  */
r_switch
c_cond
(paren
id|_IOC_DIR
c_func
(paren
id|cmd
)paren
)paren
(brace
r_case
id|_IOC_READ
suffix:colon
r_case
(paren
id|_IOC_WRITE
op_or
id|_IOC_READ
)paren
suffix:colon
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
comma
id|parg
comma
id|_IOC_SIZE
c_func
(paren
id|cmd
)paren
)paren
)paren
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
id|out
suffix:colon
r_if
c_cond
(paren
id|mbuf
)paren
id|kfree
c_func
(paren
id|mbuf
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * open/release helper functions -- handle exclusive opens&n; */
DECL|function|video_exclusive_open
r_extern
r_int
id|video_exclusive_open
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
id|video_device
op_star
id|vfl
op_assign
id|video_devdata
c_func
(paren
id|file
)paren
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|down
c_func
(paren
op_amp
id|vfl-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vfl-&gt;users
)paren
(brace
id|retval
op_assign
op_minus
id|EBUSY
suffix:semicolon
)brace
r_else
(brace
id|vfl-&gt;users
op_increment
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|vfl-&gt;lock
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|video_exclusive_release
r_extern
r_int
id|video_exclusive_release
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
id|video_device
op_star
id|vfl
op_assign
id|video_devdata
c_func
(paren
id|file
)paren
suffix:semicolon
id|vfl-&gt;users
op_decrement
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;/proc support&n; */
macro_line|#ifdef CONFIG_VIDEO_PROC_FS
multiline_comment|/* Hmm... i&squot;d like to see video_capability information here, but&n; * how can I access it (without changing the other drivers? -claudio&n; */
DECL|function|videodev_proc_read
r_static
r_int
id|videodev_proc_read
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_char
op_star
id|out
op_assign
id|page
suffix:semicolon
r_struct
id|video_device
op_star
id|vfd
op_assign
id|data
suffix:semicolon
r_struct
id|videodev_proc_data
op_star
id|d
suffix:semicolon
r_struct
id|list_head
op_star
id|tmp
suffix:semicolon
r_int
id|len
suffix:semicolon
r_char
id|c
op_assign
l_char|&squot; &squot;
suffix:semicolon
id|list_for_each
(paren
id|tmp
comma
op_amp
id|videodev_proc_list
)paren
(brace
id|d
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|videodev_proc_data
comma
id|proc_list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vfd
op_eq
id|d-&gt;vdev
)paren
r_break
suffix:semicolon
)brace
multiline_comment|/* Sanity check */
r_if
c_cond
(paren
id|tmp
op_eq
op_amp
id|videodev_proc_list
)paren
r_goto
id|skip
suffix:semicolon
DECL|macro|PRINT_VID_TYPE
mdefine_line|#define PRINT_VID_TYPE(x) do { if (vfd-&gt;type &amp; x) &bslash;&n;&t;out += sprintf (out, &quot;%c%s&quot;, c, #x); c=&squot;|&squot;;} while (0)
id|out
op_add_assign
id|sprintf
(paren
id|out
comma
l_string|&quot;name            : %s&bslash;n&quot;
comma
id|vfd-&gt;name
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
(paren
id|out
comma
l_string|&quot;type            :&quot;
)paren
suffix:semicolon
id|PRINT_VID_TYPE
c_func
(paren
id|VID_TYPE_CAPTURE
)paren
suffix:semicolon
id|PRINT_VID_TYPE
c_func
(paren
id|VID_TYPE_TUNER
)paren
suffix:semicolon
id|PRINT_VID_TYPE
c_func
(paren
id|VID_TYPE_TELETEXT
)paren
suffix:semicolon
id|PRINT_VID_TYPE
c_func
(paren
id|VID_TYPE_OVERLAY
)paren
suffix:semicolon
id|PRINT_VID_TYPE
c_func
(paren
id|VID_TYPE_CHROMAKEY
)paren
suffix:semicolon
id|PRINT_VID_TYPE
c_func
(paren
id|VID_TYPE_CLIPPING
)paren
suffix:semicolon
id|PRINT_VID_TYPE
c_func
(paren
id|VID_TYPE_FRAMERAM
)paren
suffix:semicolon
id|PRINT_VID_TYPE
c_func
(paren
id|VID_TYPE_SCALES
)paren
suffix:semicolon
id|PRINT_VID_TYPE
c_func
(paren
id|VID_TYPE_MONOCHROME
)paren
suffix:semicolon
id|PRINT_VID_TYPE
c_func
(paren
id|VID_TYPE_SUBCAPTURE
)paren
suffix:semicolon
id|PRINT_VID_TYPE
c_func
(paren
id|VID_TYPE_MPEG_DECODER
)paren
suffix:semicolon
id|PRINT_VID_TYPE
c_func
(paren
id|VID_TYPE_MPEG_ENCODER
)paren
suffix:semicolon
id|PRINT_VID_TYPE
c_func
(paren
id|VID_TYPE_MJPEG_DECODER
)paren
suffix:semicolon
id|PRINT_VID_TYPE
c_func
(paren
id|VID_TYPE_MJPEG_ENCODER
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
(paren
id|out
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
(paren
id|out
comma
l_string|&quot;hardware        : 0x%x&bslash;n&quot;
comma
id|vfd-&gt;hardware
)paren
suffix:semicolon
macro_line|#if 0
id|out
op_add_assign
id|sprintf
(paren
id|out
comma
l_string|&quot;channels        : %d&bslash;n&quot;
comma
id|d-&gt;vcap.channels
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
(paren
id|out
comma
l_string|&quot;audios          : %d&bslash;n&quot;
comma
id|d-&gt;vcap.audios
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
(paren
id|out
comma
l_string|&quot;maxwidth        : %d&bslash;n&quot;
comma
id|d-&gt;vcap.maxwidth
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
(paren
id|out
comma
l_string|&quot;maxheight       : %d&bslash;n&quot;
comma
id|d-&gt;vcap.maxheight
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
(paren
id|out
comma
l_string|&quot;minwidth        : %d&bslash;n&quot;
comma
id|d-&gt;vcap.minwidth
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
(paren
id|out
comma
l_string|&quot;minheight       : %d&bslash;n&quot;
comma
id|d-&gt;vcap.minheight
)paren
suffix:semicolon
macro_line|#endif
id|skip
suffix:colon
id|len
op_assign
id|out
op_minus
id|page
suffix:semicolon
id|len
op_sub_assign
id|off
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
id|count
)paren
(brace
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|len
op_le
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_else
id|len
op_assign
id|count
suffix:semicolon
op_star
id|start
op_assign
id|page
op_plus
id|off
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|videodev_proc_create
r_static
r_void
id|videodev_proc_create
c_func
(paren
r_void
)paren
(brace
id|video_proc_entry
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;video&quot;
comma
id|S_IFDIR
comma
op_amp
id|proc_root
)paren
suffix:semicolon
r_if
c_cond
(paren
id|video_proc_entry
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;video_dev: unable to initialise /proc/video&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|video_proc_entry-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|video_dev_proc_entry
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;dev&quot;
comma
id|S_IFDIR
comma
id|video_proc_entry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|video_dev_proc_entry
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;video_dev: unable to initialise /proc/video/dev&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|video_dev_proc_entry-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
)brace
macro_line|#ifdef MODULE
macro_line|#ifdef CONFIG_VIDEO_PROC_FS
DECL|function|videodev_proc_destroy
r_static
r_void
id|videodev_proc_destroy
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|video_dev_proc_entry
op_ne
l_int|NULL
)paren
id|remove_proc_entry
c_func
(paren
l_string|&quot;dev&quot;
comma
id|video_proc_entry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|video_proc_entry
op_ne
l_int|NULL
)paren
id|remove_proc_entry
c_func
(paren
l_string|&quot;video&quot;
comma
op_amp
id|proc_root
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif
DECL|function|videodev_proc_create_dev
r_static
r_void
id|videodev_proc_create_dev
(paren
r_struct
id|video_device
op_star
id|vfd
comma
r_char
op_star
id|name
)paren
(brace
r_struct
id|videodev_proc_data
op_star
id|d
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|video_dev_proc_entry
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|d
op_assign
id|kmalloc
(paren
r_sizeof
(paren
r_struct
id|videodev_proc_data
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|d
)paren
r_return
suffix:semicolon
id|p
op_assign
id|create_proc_entry
c_func
(paren
id|name
comma
id|S_IFREG
op_or
id|S_IRUGO
op_or
id|S_IWUSR
comma
id|video_dev_proc_entry
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_return
suffix:semicolon
id|p-&gt;data
op_assign
id|vfd
suffix:semicolon
id|p-&gt;read_proc
op_assign
id|videodev_proc_read
suffix:semicolon
id|d-&gt;proc_entry
op_assign
id|p
suffix:semicolon
id|d-&gt;vdev
op_assign
id|vfd
suffix:semicolon
id|strcpy
(paren
id|d-&gt;name
comma
id|name
)paren
suffix:semicolon
multiline_comment|/* How can I get capability information ? */
id|list_add
(paren
op_amp
id|d-&gt;proc_list
comma
op_amp
id|videodev_proc_list
)paren
suffix:semicolon
)brace
DECL|function|videodev_proc_destroy_dev
r_static
r_void
id|videodev_proc_destroy_dev
(paren
r_struct
id|video_device
op_star
id|vfd
)paren
(brace
r_struct
id|list_head
op_star
id|tmp
suffix:semicolon
r_struct
id|videodev_proc_data
op_star
id|d
suffix:semicolon
id|list_for_each
(paren
id|tmp
comma
op_amp
id|videodev_proc_list
)paren
(brace
id|d
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|videodev_proc_data
comma
id|proc_list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vfd
op_eq
id|d-&gt;vdev
)paren
(brace
id|remove_proc_entry
c_func
(paren
id|d-&gt;name
comma
id|video_dev_proc_entry
)paren
suffix:semicolon
id|list_del
(paren
op_amp
id|d-&gt;proc_list
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|d
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif /* CONFIG_VIDEO_PROC_FS */
r_extern
r_struct
id|file_operations
id|video_fops
suffix:semicolon
multiline_comment|/**&n; *&t;video_register_device - register video4linux devices&n; *&t;@vfd:  video device structure we want to register&n; *&t;@type: type of device to register&n; *&t;@nr:   which device number (0 == /dev/video0, 1 == /dev/video1, ...&n; *             -1 == first free)&n; *&t;&n; *&t;The registration code assigns minor numbers based on the type&n; *&t;requested. -ENFILE is returned in all the device slots for this&n; *&t;category are full. If not then the minor field is set and the&n; *&t;driver initialize function is called (if non %NULL).&n; *&n; *&t;Zero is returned on success.&n; *&n; *&t;Valid types are&n; *&n; *&t;%VFL_TYPE_GRABBER - A frame grabber&n; *&n; *&t;%VFL_TYPE_VTX - A teletext device&n; *&n; *&t;%VFL_TYPE_VBI - Vertical blank data (undecoded)&n; *&n; *&t;%VFL_TYPE_RADIO - A radio card&t;&n; */
DECL|function|video_register_device
r_int
id|video_register_device
c_func
(paren
r_struct
id|video_device
op_star
id|vfd
comma
r_int
id|type
comma
r_int
id|nr
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_int
id|base
suffix:semicolon
r_int
id|end
suffix:semicolon
r_char
op_star
id|name_base
suffix:semicolon
r_char
id|name
(braket
l_int|16
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|VFL_TYPE_GRABBER
suffix:colon
id|base
op_assign
l_int|0
suffix:semicolon
id|end
op_assign
l_int|64
suffix:semicolon
id|name_base
op_assign
l_string|&quot;video&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VFL_TYPE_VTX
suffix:colon
id|base
op_assign
l_int|192
suffix:semicolon
id|end
op_assign
l_int|224
suffix:semicolon
id|name_base
op_assign
l_string|&quot;vtx&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VFL_TYPE_VBI
suffix:colon
id|base
op_assign
l_int|224
suffix:semicolon
id|end
op_assign
l_int|240
suffix:semicolon
id|name_base
op_assign
l_string|&quot;vbi&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VFL_TYPE_RADIO
suffix:colon
id|base
op_assign
l_int|64
suffix:semicolon
id|end
op_assign
l_int|128
suffix:semicolon
id|name_base
op_assign
l_string|&quot;radio&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* pick a minor number */
id|down
c_func
(paren
op_amp
id|videodev_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_minus
l_int|1
op_eq
id|nr
)paren
(brace
multiline_comment|/* use first free */
r_for
c_loop
(paren
id|i
op_assign
id|base
suffix:semicolon
id|i
OL
id|end
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
l_int|NULL
op_eq
id|video_device
(braket
id|i
)braket
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|end
)paren
(brace
id|up
c_func
(paren
op_amp
id|videodev_lock
)paren
suffix:semicolon
r_return
op_minus
id|ENFILE
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* use the one the driver asked for */
id|i
op_assign
id|base
op_plus
id|nr
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_ne
id|video_device
(braket
id|i
)braket
)paren
(brace
id|up
c_func
(paren
op_amp
id|videodev_lock
)paren
suffix:semicolon
r_return
op_minus
id|ENFILE
suffix:semicolon
)brace
)brace
id|video_device
(braket
id|i
)braket
op_assign
id|vfd
suffix:semicolon
id|vfd-&gt;minor
op_assign
id|i
suffix:semicolon
id|up
c_func
(paren
op_amp
id|videodev_lock
)paren
suffix:semicolon
id|sprintf
(paren
id|name
comma
l_string|&quot;v4l/%s%d&quot;
comma
id|name_base
comma
id|i
op_minus
id|base
)paren
suffix:semicolon
id|vfd-&gt;devfs_handle
op_assign
id|devfs_register
(paren
l_int|NULL
comma
id|name
comma
id|DEVFS_FL_DEFAULT
comma
id|VIDEO_MAJOR
comma
id|vfd-&gt;minor
comma
id|S_IFCHR
op_or
id|S_IRUSR
op_or
id|S_IWUSR
comma
op_amp
id|video_fops
comma
l_int|NULL
)paren
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|vfd-&gt;lock
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_VIDEO_PROC_FS
id|sprintf
(paren
id|name
comma
l_string|&quot;%s%d&quot;
comma
id|name_base
comma
id|i
op_minus
id|base
)paren
suffix:semicolon
id|videodev_proc_create_dev
(paren
id|vfd
comma
id|name
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;video_unregister_device - unregister a video4linux device&n; *&t;@vfd: the device to unregister&n; *&n; *&t;This unregisters the passed device and deassigns the minor&n; *&t;number. Future open calls will be met with errors.&n; */
DECL|function|video_unregister_device
r_void
id|video_unregister_device
c_func
(paren
r_struct
id|video_device
op_star
id|vfd
)paren
(brace
id|down
c_func
(paren
op_amp
id|videodev_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|video_device
(braket
id|vfd-&gt;minor
)braket
op_ne
id|vfd
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;videodev: bad unregister&quot;
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_VIDEO_PROC_FS
id|videodev_proc_destroy_dev
(paren
id|vfd
)paren
suffix:semicolon
macro_line|#endif
id|devfs_unregister
(paren
id|vfd-&gt;devfs_handle
)paren
suffix:semicolon
id|video_device
(braket
id|vfd-&gt;minor
)braket
op_assign
l_int|NULL
suffix:semicolon
id|up
c_func
(paren
op_amp
id|videodev_lock
)paren
suffix:semicolon
)brace
DECL|variable|video_fops
r_static
r_struct
id|file_operations
id|video_fops
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|llseek
suffix:colon
id|no_llseek
comma
id|open
suffix:colon
id|video_open
comma
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Initialise video for linux&n; */
DECL|function|videodev_init
r_static
r_int
id|__init
id|videodev_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Linux video capture interface: v1.00&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|register_chrdev
c_func
(paren
id|VIDEO_MAJOR
comma
l_string|&quot;video_capture&quot;
comma
op_amp
id|video_fops
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;video_dev: unable to get major %d&bslash;n&quot;
comma
id|VIDEO_MAJOR
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_VIDEO_PROC_FS
id|videodev_proc_create
(paren
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|videodev_exit
r_static
r_void
id|__exit
id|videodev_exit
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_VIDEO_PROC_FS
id|videodev_proc_destroy
(paren
)paren
suffix:semicolon
macro_line|#endif
id|unregister_chrdev
c_func
(paren
id|VIDEO_MAJOR
comma
l_string|&quot;video_capture&quot;
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|videodev_init
)paren
id|module_exit
c_func
(paren
id|videodev_exit
)paren
id|EXPORT_SYMBOL
c_func
(paren
id|video_register_device
)paren
suffix:semicolon
DECL|variable|EXPORT_SYMBOL
id|EXPORT_SYMBOL
c_func
(paren
id|video_unregister_device
)paren
suffix:semicolon
DECL|variable|video_devdata
id|EXPORT_SYMBOL
c_func
(paren
id|video_devdata
)paren
suffix:semicolon
DECL|variable|video_usercopy
id|EXPORT_SYMBOL
c_func
(paren
id|video_usercopy
)paren
suffix:semicolon
DECL|variable|video_exclusive_open
id|EXPORT_SYMBOL
c_func
(paren
id|video_exclusive_open
)paren
suffix:semicolon
DECL|variable|video_exclusive_release
id|EXPORT_SYMBOL
c_func
(paren
id|video_exclusive_release
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Alan Cox&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Device registrar for Video4Linux drivers&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
