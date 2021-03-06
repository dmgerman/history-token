multiline_comment|/*&n; * Video capture interface for Linux&n; *&n; *&t;&t;A generic video device interface for the LINUX operating system&n; *&t;&t;using a set of device structures/vectors for low level operations.&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; * Author:&t;Alan Cox, &lt;alan@redhat.com&gt;&n; *&n; * Fixes:&t;20000516  Claudio Matsuoka &lt;claudio@conectiva.com&gt;&n; *&t;&t;- Added procfs support&n; */
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
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;linux/videodev.h&gt;
DECL|macro|VIDEO_NUM_DEVICES
mdefine_line|#define VIDEO_NUM_DEVICES&t;256
DECL|macro|VIDEO_NAME
mdefine_line|#define VIDEO_NAME              &quot;video4linux&quot;
multiline_comment|/*&n; *&t;sysfs stuff&n; */
DECL|function|show_name
r_static
id|ssize_t
id|show_name
c_func
(paren
r_struct
id|class_device
op_star
id|cd
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|video_device
op_star
id|vfd
op_assign
id|container_of
c_func
(paren
id|cd
comma
r_struct
id|video_device
comma
id|class_dev
)paren
suffix:semicolon
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%.*s&bslash;n&quot;
comma
(paren
r_int
)paren
r_sizeof
(paren
id|vfd-&gt;name
)paren
comma
id|vfd-&gt;name
)paren
suffix:semicolon
)brace
r_static
id|CLASS_DEVICE_ATTR
c_func
(paren
id|name
comma
id|S_IRUGO
comma
id|show_name
comma
l_int|NULL
)paren
suffix:semicolon
DECL|function|video_device_alloc
r_struct
id|video_device
op_star
id|video_device_alloc
c_func
(paren
r_void
)paren
(brace
r_struct
id|video_device
op_star
id|vfd
suffix:semicolon
id|vfd
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|vfd
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
id|vfd
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|vfd
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|vfd
)paren
)paren
suffix:semicolon
r_return
id|vfd
suffix:semicolon
)brace
DECL|function|video_device_release
r_void
id|video_device_release
c_func
(paren
r_struct
id|video_device
op_star
id|vfd
)paren
(brace
id|kfree
c_func
(paren
id|vfd
)paren
suffix:semicolon
)brace
DECL|function|video_release
r_static
r_void
id|video_release
c_func
(paren
r_struct
id|class_device
op_star
id|cd
)paren
(brace
r_struct
id|video_device
op_star
id|vfd
op_assign
id|container_of
c_func
(paren
id|cd
comma
r_struct
id|video_device
comma
id|class_dev
)paren
suffix:semicolon
macro_line|#if 1 /* needed until all drivers are fixed */
r_if
c_cond
(paren
op_logical_neg
id|vfd-&gt;release
)paren
r_return
suffix:semicolon
macro_line|#endif
id|vfd
op_member_access_from_pointer
id|release
c_func
(paren
id|vfd
)paren
suffix:semicolon
)brace
DECL|variable|video_class
r_static
r_struct
r_class
id|video_class
op_assign
(brace
dot
id|name
op_assign
id|VIDEO_NAME
comma
dot
id|release
op_assign
id|video_release
comma
)brace
suffix:semicolon
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
id|iminor
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
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
id|iminor
c_func
(paren
id|inode
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
id|up
c_func
(paren
op_amp
id|videodev_lock
)paren
suffix:semicolon
id|request_module
c_func
(paren
l_string|&quot;char-major-%d-%d&quot;
comma
id|VIDEO_MAJOR
comma
id|minor
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
r_static
r_int
r_int
DECL|function|video_fix_command
id|video_fix_command
c_func
(paren
r_int
r_int
id|cmd
)paren
(brace
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|VIDIOC_OVERLAY_OLD
suffix:colon
id|cmd
op_assign
id|VIDIOC_OVERLAY
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIDIOC_S_PARM_OLD
suffix:colon
id|cmd
op_assign
id|VIDIOC_S_PARM
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIDIOC_S_CTRL_OLD
suffix:colon
id|cmd
op_assign
id|VIDIOC_S_CTRL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIDIOC_G_AUDIO_OLD
suffix:colon
id|cmd
op_assign
id|VIDIOC_G_AUDIO
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIDIOC_G_AUDOUT_OLD
suffix:colon
id|cmd
op_assign
id|VIDIOC_G_AUDOUT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIDIOC_CROPCAP_OLD
suffix:colon
id|cmd
op_assign
id|VIDIOC_CROPCAP
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|cmd
suffix:semicolon
)brace
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
id|cmd
op_assign
id|video_fix_command
c_func
(paren
id|cmd
)paren
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
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|_IOC_READ
suffix:colon
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
id|_IOC_DIR
c_func
(paren
id|cmd
)paren
op_amp
id|_IOC_WRITE
)paren
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
id|__user
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
id|__user
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
DECL|variable|video_fops
r_static
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
id|nr
op_ge
l_int|0
op_logical_and
id|nr
OL
id|end
op_minus
id|base
)paren
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
r_else
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
c_func
(paren
id|vfd-&gt;devfs_name
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
id|devfs_mk_cdev
c_func
(paren
id|MKDEV
c_func
(paren
id|VIDEO_MAJOR
comma
id|vfd-&gt;minor
)paren
comma
id|S_IFCHR
op_or
id|S_IRUSR
op_or
id|S_IWUSR
comma
id|vfd-&gt;devfs_name
)paren
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|vfd-&gt;lock
)paren
suffix:semicolon
multiline_comment|/* sysfs class */
id|memset
c_func
(paren
op_amp
id|vfd-&gt;class_dev
comma
l_int|0x00
comma
r_sizeof
(paren
id|vfd-&gt;class_dev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vfd-&gt;dev
)paren
id|vfd-&gt;class_dev.dev
op_assign
id|vfd-&gt;dev
suffix:semicolon
id|vfd-&gt;class_dev
dot
r_class
op_assign
op_amp
id|video_class
suffix:semicolon
id|vfd-&gt;class_dev.devt
op_assign
id|MKDEV
c_func
(paren
id|VIDEO_MAJOR
comma
id|vfd-&gt;minor
)paren
suffix:semicolon
id|strlcpy
c_func
(paren
id|vfd-&gt;class_dev.class_id
comma
id|vfd-&gt;devfs_name
op_plus
l_int|4
comma
id|BUS_ID_SIZE
)paren
suffix:semicolon
id|class_device_register
c_func
(paren
op_amp
id|vfd-&gt;class_dev
)paren
suffix:semicolon
id|class_device_create_file
c_func
(paren
op_amp
id|vfd-&gt;class_dev
comma
op_amp
id|class_device_attr_name
)paren
suffix:semicolon
macro_line|#if 1 /* needed until all drivers are fixed */
r_if
c_cond
(paren
op_logical_neg
id|vfd-&gt;release
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;videodev: &bslash;&quot;%s&bslash;&quot; has no release callback. &quot;
l_string|&quot;Please fix your driver for proper sysfs support, see &quot;
l_string|&quot;http://lwn.net/Articles/36850/&bslash;n&quot;
comma
id|vfd-&gt;name
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
id|devfs_remove
c_func
(paren
id|vfd-&gt;devfs_name
)paren
suffix:semicolon
id|video_device
(braket
id|vfd-&gt;minor
)braket
op_assign
l_int|NULL
suffix:semicolon
id|class_device_unregister
c_func
(paren
op_amp
id|vfd-&gt;class_dev
)paren
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
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|llseek
op_assign
id|no_llseek
comma
dot
id|open
op_assign
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
r_int
id|ret
suffix:semicolon
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
id|VIDEO_NAME
comma
op_amp
id|video_fops
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
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
id|ret
op_assign
id|class_register
c_func
(paren
op_amp
id|video_class
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|unregister_chrdev
c_func
(paren
id|VIDEO_MAJOR
comma
id|VIDEO_NAME
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;video_dev: class_register failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
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
id|class_unregister
c_func
(paren
op_amp
id|video_class
)paren
suffix:semicolon
id|unregister_chrdev
c_func
(paren
id|VIDEO_MAJOR
comma
id|VIDEO_NAME
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
DECL|variable|video_device_alloc
id|EXPORT_SYMBOL
c_func
(paren
id|video_device_alloc
)paren
suffix:semicolon
DECL|variable|video_device_release
id|EXPORT_SYMBOL
c_func
(paren
id|video_device_release
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
