multiline_comment|/*&n; * drivers/sbus/char/vfc_dev.c&n; *&n; * Driver for the Videopix Frame Grabber.&n; * &n; * In order to use the VFC you need to program the video controller&n; * chip. This chip is the Phillips SAA9051.  You need to call their&n; * documentation ordering line to get the docs.&n; *&n; * There is very little documentation on the VFC itself.  There is&n; * some useful info that can be found in the manuals that come with&n; * the card.  I will hopefully write some better docs at a later date.&n; *&n; * Copyright (C) 1996 Manish Vachharajani (mvachhar@noc.rutgers.edu)&n; * */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/openprom.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/sbus.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|VFC_MAJOR
mdefine_line|#define VFC_MAJOR (60)
macro_line|#if 0
mdefine_line|#define VFC_IOCTL_DEBUG
macro_line|#endif
macro_line|#include &quot;vfc.h&quot;
macro_line|#include &lt;asm/vfc_ioctls.h&gt;
DECL|variable|vfc_fops
r_static
r_struct
id|file_operations
id|vfc_fops
suffix:semicolon
DECL|variable|devfs_handle
r_static
id|devfs_handle_t
id|devfs_handle
suffix:semicolon
multiline_comment|/*  For the directory  */
DECL|variable|vfc_dev_lst
r_struct
id|vfc_dev
op_star
op_star
id|vfc_dev_lst
suffix:semicolon
DECL|variable|vfcstr
r_static
r_char
id|vfcstr
(braket
)braket
op_assign
l_string|&quot;vfc&quot;
suffix:semicolon
DECL|variable|saa9051_init_array
r_static
r_int
r_char
id|saa9051_init_array
(braket
id|VFC_SAA9051_NR
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x64
comma
l_int|0x72
comma
l_int|0x52
comma
l_int|0x36
comma
l_int|0x18
comma
l_int|0xff
comma
l_int|0x20
comma
l_int|0xfc
comma
l_int|0x77
comma
l_int|0xe3
comma
l_int|0x50
comma
l_int|0x3e
)brace
suffix:semicolon
DECL|function|vfc_lock_device
r_void
id|vfc_lock_device
c_func
(paren
r_struct
id|vfc_dev
op_star
id|dev
)paren
(brace
id|down
c_func
(paren
op_amp
id|dev-&gt;device_lock_sem
)paren
suffix:semicolon
)brace
DECL|function|vfc_unlock_device
r_void
id|vfc_unlock_device
c_func
(paren
r_struct
id|vfc_dev
op_star
id|dev
)paren
(brace
id|up
c_func
(paren
op_amp
id|dev-&gt;device_lock_sem
)paren
suffix:semicolon
)brace
DECL|function|vfc_captstat_reset
r_void
id|vfc_captstat_reset
c_func
(paren
r_struct
id|vfc_dev
op_star
id|dev
)paren
(brace
id|dev-&gt;control_reg
op_or_assign
id|VFC_CONTROL_CAPTRESET
suffix:semicolon
id|sbus_writel
c_func
(paren
id|dev-&gt;control_reg
comma
op_amp
id|dev-&gt;regs-&gt;control
)paren
suffix:semicolon
id|dev-&gt;control_reg
op_and_assign
op_complement
id|VFC_CONTROL_CAPTRESET
suffix:semicolon
id|sbus_writel
c_func
(paren
id|dev-&gt;control_reg
comma
op_amp
id|dev-&gt;regs-&gt;control
)paren
suffix:semicolon
id|dev-&gt;control_reg
op_or_assign
id|VFC_CONTROL_CAPTRESET
suffix:semicolon
id|sbus_writel
c_func
(paren
id|dev-&gt;control_reg
comma
op_amp
id|dev-&gt;regs-&gt;control
)paren
suffix:semicolon
)brace
DECL|function|vfc_memptr_reset
r_void
id|vfc_memptr_reset
c_func
(paren
r_struct
id|vfc_dev
op_star
id|dev
)paren
(brace
id|dev-&gt;control_reg
op_or_assign
id|VFC_CONTROL_MEMPTR
suffix:semicolon
id|sbus_writel
c_func
(paren
id|dev-&gt;control_reg
comma
op_amp
id|dev-&gt;regs-&gt;control
)paren
suffix:semicolon
id|dev-&gt;control_reg
op_and_assign
op_complement
id|VFC_CONTROL_MEMPTR
suffix:semicolon
id|sbus_writel
c_func
(paren
id|dev-&gt;control_reg
comma
op_amp
id|dev-&gt;regs-&gt;control
)paren
suffix:semicolon
id|dev-&gt;control_reg
op_or_assign
id|VFC_CONTROL_MEMPTR
suffix:semicolon
id|sbus_writel
c_func
(paren
id|dev-&gt;control_reg
comma
op_amp
id|dev-&gt;regs-&gt;control
)paren
suffix:semicolon
)brace
DECL|function|vfc_csr_init
r_int
id|vfc_csr_init
c_func
(paren
r_struct
id|vfc_dev
op_star
id|dev
)paren
(brace
id|dev-&gt;control_reg
op_assign
l_int|0x80000000
suffix:semicolon
id|sbus_writel
c_func
(paren
id|dev-&gt;control_reg
comma
op_amp
id|dev-&gt;regs-&gt;control
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|200
)paren
suffix:semicolon
id|dev-&gt;control_reg
op_and_assign
op_complement
l_int|0x80000000
suffix:semicolon
id|sbus_writel
c_func
(paren
id|dev-&gt;control_reg
comma
op_amp
id|dev-&gt;regs-&gt;control
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
id|sbus_writel
c_func
(paren
l_int|0x0f000000
comma
op_amp
id|dev-&gt;regs-&gt;i2c_magic2
)paren
suffix:semicolon
id|vfc_memptr_reset
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev-&gt;control_reg
op_and_assign
op_complement
id|VFC_CONTROL_DIAGMODE
suffix:semicolon
id|dev-&gt;control_reg
op_and_assign
op_complement
id|VFC_CONTROL_CAPTURE
suffix:semicolon
id|dev-&gt;control_reg
op_or_assign
l_int|0x40000000
suffix:semicolon
id|sbus_writel
c_func
(paren
id|dev-&gt;control_reg
comma
op_amp
id|dev-&gt;regs-&gt;control
)paren
suffix:semicolon
id|vfc_captstat_reset
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|vfc_saa9051_init
r_int
id|vfc_saa9051_init
c_func
(paren
r_struct
id|vfc_dev
op_star
id|dev
)paren
(brace
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
OL
id|VFC_SAA9051_NR
suffix:semicolon
id|i
op_increment
)paren
id|dev-&gt;saa9051_state_array
(braket
id|i
)braket
op_assign
id|saa9051_init_array
(braket
id|i
)braket
suffix:semicolon
id|vfc_i2c_sendbuf
c_func
(paren
id|dev
comma
id|VFC_SAA9051_ADDR
comma
id|dev-&gt;saa9051_state_array
comma
id|VFC_SAA9051_NR
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|init_vfc_hw
r_int
id|init_vfc_hw
c_func
(paren
r_struct
id|vfc_dev
op_star
id|dev
)paren
(brace
id|vfc_lock_device
c_func
(paren
id|dev
)paren
suffix:semicolon
id|vfc_csr_init
c_func
(paren
id|dev
)paren
suffix:semicolon
id|vfc_pcf8584_init
c_func
(paren
id|dev
)paren
suffix:semicolon
id|vfc_init_i2c_bus
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* hopefully this doesn&squot;t undo the magic&n;&t;&t;&t;&t;  sun code above*/
id|vfc_saa9051_init
c_func
(paren
id|dev
)paren
suffix:semicolon
id|vfc_unlock_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|init_vfc_devstruct
r_int
id|init_vfc_devstruct
c_func
(paren
r_struct
id|vfc_dev
op_star
id|dev
comma
r_int
id|instance
)paren
(brace
id|dev-&gt;instance
op_assign
id|instance
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|dev-&gt;device_lock_sem
)paren
suffix:semicolon
id|dev-&gt;control_reg
op_assign
l_int|0
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|dev-&gt;poll_wait
)paren
suffix:semicolon
id|dev-&gt;busy
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|init_vfc_device
r_int
id|init_vfc_device
c_func
(paren
r_struct
id|sbus_dev
op_star
id|sdev
comma
r_struct
id|vfc_dev
op_star
id|dev
comma
r_int
id|instance
)paren
(brace
r_char
id|devname
(braket
l_int|8
)braket
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;VFC: Bogus pointer passed&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Initializing vfc%d&bslash;n&quot;
comma
id|instance
)paren
suffix:semicolon
id|dev-&gt;regs
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;regs
op_assign
(paren
r_volatile
r_struct
id|vfc_regs
op_star
)paren
id|sbus_ioremap
c_func
(paren
op_amp
id|sdev-&gt;resource
(braket
l_int|0
)braket
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|vfc_regs
)paren
comma
id|vfcstr
)paren
suffix:semicolon
id|dev-&gt;which_io
op_assign
id|sdev-&gt;reg_addrs
(braket
l_int|0
)braket
dot
id|which_io
suffix:semicolon
id|dev-&gt;phys_regs
op_assign
(paren
r_struct
id|vfc_regs
op_star
)paren
id|sdev-&gt;reg_addrs
(braket
l_int|0
)braket
dot
id|phys_addr
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;regs
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;vfc%d: registers mapped at phys_addr: 0x%lx&bslash;n    virt_addr: 0x%lx&bslash;n&quot;
comma
id|instance
comma
(paren
r_int
r_int
)paren
id|sdev-&gt;reg_addrs
(braket
l_int|0
)braket
dot
id|phys_addr
comma
(paren
r_int
r_int
)paren
id|dev-&gt;regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|init_vfc_devstruct
c_func
(paren
id|dev
comma
id|instance
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|init_vfc_hw
c_func
(paren
id|dev
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|sprintf
(paren
id|devname
comma
l_string|&quot;%d&quot;
comma
id|instance
)paren
suffix:semicolon
id|dev-&gt;de
op_assign
id|devfs_register
(paren
id|devfs_handle
comma
id|devname
comma
id|DEVFS_FL_DEFAULT
comma
id|VFC_MAJOR
comma
id|instance
comma
id|S_IFCHR
op_or
id|S_IRUSR
op_or
id|S_IWUSR
comma
op_amp
id|vfc_fops
comma
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|vfc_get_dev_ptr
r_struct
id|vfc_dev
op_star
id|vfc_get_dev_ptr
c_func
(paren
r_int
id|instance
)paren
(brace
r_return
id|vfc_dev_lst
(braket
id|instance
)braket
suffix:semicolon
)brace
DECL|variable|vfc_dev_lock
r_static
id|spinlock_t
id|vfc_dev_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|function|vfc_open
r_static
r_int
id|vfc_open
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
id|vfc_dev
op_star
id|dev
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|vfc_dev_lock
)paren
suffix:semicolon
id|dev
op_assign
id|vfc_get_dev_ptr
c_func
(paren
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|vfc_dev_lock
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;busy
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|vfc_dev_lock
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|dev-&gt;busy
op_assign
l_int|1
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|vfc_dev_lock
)paren
suffix:semicolon
id|vfc_lock_device
c_func
(paren
id|dev
)paren
suffix:semicolon
id|vfc_csr_init
c_func
(paren
id|dev
)paren
suffix:semicolon
id|vfc_pcf8584_init
c_func
(paren
id|dev
)paren
suffix:semicolon
id|vfc_init_i2c_bus
c_func
(paren
id|dev
)paren
suffix:semicolon
id|vfc_saa9051_init
c_func
(paren
id|dev
)paren
suffix:semicolon
id|vfc_memptr_reset
c_func
(paren
id|dev
)paren
suffix:semicolon
id|vfc_captstat_reset
c_func
(paren
id|dev
)paren
suffix:semicolon
id|vfc_unlock_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|vfc_release
r_static
r_int
id|vfc_release
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
id|vfc_dev
op_star
id|dev
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|vfc_dev_lock
)paren
suffix:semicolon
id|dev
op_assign
id|vfc_get_dev_ptr
c_func
(paren
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
op_logical_or
op_logical_neg
id|dev-&gt;busy
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|vfc_dev_lock
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|dev-&gt;busy
op_assign
l_int|0
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|vfc_dev_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|vfc_debug
r_static
r_int
id|vfc_debug
c_func
(paren
r_struct
id|vfc_dev
op_star
id|dev
comma
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|vfc_debug_inout
id|inout
suffix:semicolon
r_int
r_char
op_star
id|buffer
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
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|VFC_I2C_SEND
suffix:colon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|inout
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|inout
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|buffer
op_assign
id|kmalloc
c_func
(paren
id|inout.len
op_star
r_sizeof
(paren
r_char
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer
op_eq
l_int|NULL
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
id|buffer
comma
id|inout.buffer
comma
id|inout.len
op_star
r_sizeof
(paren
r_char
)paren
)paren
)paren
(brace
id|kfree
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|vfc_lock_device
c_func
(paren
id|dev
)paren
suffix:semicolon
id|inout.ret
op_assign
id|vfc_i2c_sendbuf
c_func
(paren
id|dev
comma
id|inout.addr
op_amp
l_int|0xff
comma
id|inout.buffer
comma
id|inout.len
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
comma
op_amp
id|inout
comma
r_sizeof
(paren
id|inout
)paren
)paren
)paren
(brace
id|kfree
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|vfc_unlock_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VFC_I2C_RECV
suffix:colon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|inout
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|inout
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|buffer
op_assign
id|kmalloc
c_func
(paren
id|inout.len
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|buffer
comma
l_int|0
comma
id|inout.len
op_star
r_sizeof
(paren
r_char
)paren
)paren
suffix:semicolon
id|vfc_lock_device
c_func
(paren
id|dev
)paren
suffix:semicolon
id|inout.ret
op_assign
id|vfc_i2c_recvbuf
c_func
(paren
id|dev
comma
id|inout.addr
op_amp
l_int|0xff
comma
id|buffer
comma
id|inout.len
)paren
suffix:semicolon
id|vfc_unlock_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|inout.buffer
comma
id|buffer
comma
id|inout.len
)paren
)paren
(brace
id|kfree
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
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
op_amp
id|inout
comma
r_sizeof
(paren
id|inout
)paren
)paren
)paren
(brace
id|kfree
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|vfc_capture_start
r_int
id|vfc_capture_start
c_func
(paren
r_struct
id|vfc_dev
op_star
id|dev
)paren
(brace
id|vfc_captstat_reset
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev-&gt;control_reg
op_assign
id|sbus_readl
c_func
(paren
op_amp
id|dev-&gt;regs-&gt;control
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dev-&gt;control_reg
op_amp
id|VFC_STATUS_CAPTURE
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;vfc%d: vfc capture status not reset&bslash;n&quot;
comma
id|dev-&gt;instance
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|vfc_lock_device
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev-&gt;control_reg
op_and_assign
op_complement
id|VFC_CONTROL_CAPTURE
suffix:semicolon
id|sbus_writel
c_func
(paren
id|dev-&gt;control_reg
comma
op_amp
id|dev-&gt;regs-&gt;control
)paren
suffix:semicolon
id|dev-&gt;control_reg
op_or_assign
id|VFC_CONTROL_CAPTURE
suffix:semicolon
id|sbus_writel
c_func
(paren
id|dev-&gt;control_reg
comma
op_amp
id|dev-&gt;regs-&gt;control
)paren
suffix:semicolon
id|dev-&gt;control_reg
op_and_assign
op_complement
id|VFC_CONTROL_CAPTURE
suffix:semicolon
id|sbus_writel
c_func
(paren
id|dev-&gt;control_reg
comma
op_amp
id|dev-&gt;regs-&gt;control
)paren
suffix:semicolon
id|vfc_unlock_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|vfc_capture_poll
r_int
id|vfc_capture_poll
c_func
(paren
r_struct
id|vfc_dev
op_star
id|dev
)paren
(brace
r_int
id|timeout
op_assign
l_int|1000
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|timeout
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;regs-&gt;control
op_amp
id|VFC_STATUS_CAPTURE
)paren
r_break
suffix:semicolon
id|vfc_i2c_delay_no_busy
c_func
(paren
id|dev
comma
l_int|100
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|timeout
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;vfc%d: capture timed out&bslash;n&quot;
comma
id|dev-&gt;instance
)paren
suffix:semicolon
r_return
op_minus
id|ETIMEDOUT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|vfc_set_control_ioctl
r_static
r_int
id|vfc_set_control_ioctl
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
r_struct
id|vfc_dev
op_star
id|dev
comma
r_int
r_int
id|arg
)paren
(brace
r_int
id|setcmd
comma
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|setcmd
comma
(paren
r_void
op_star
)paren
id|arg
comma
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
id|VFC_IOCTL_DEBUG_PRINTK
c_func
(paren
(paren
l_string|&quot;vfc%d: IOCTL(VFCSCTRL) arg=0x%x&bslash;n&quot;
comma
id|dev-&gt;instance
comma
id|setcmd
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|setcmd
)paren
(brace
r_case
id|MEMPRST
suffix:colon
id|vfc_lock_device
c_func
(paren
id|dev
)paren
suffix:semicolon
id|vfc_memptr_reset
c_func
(paren
id|dev
)paren
suffix:semicolon
id|vfc_unlock_device
c_func
(paren
id|dev
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CAPTRCMD
suffix:colon
id|vfc_capture_start
c_func
(paren
id|dev
)paren
suffix:semicolon
id|vfc_capture_poll
c_func
(paren
id|dev
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIAGMODE
suffix:colon
r_if
c_cond
(paren
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
(brace
id|vfc_lock_device
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev-&gt;control_reg
op_or_assign
id|VFC_CONTROL_DIAGMODE
suffix:semicolon
id|sbus_writel
c_func
(paren
id|dev-&gt;control_reg
comma
op_amp
id|dev-&gt;regs-&gt;control
)paren
suffix:semicolon
id|vfc_unlock_device
c_func
(paren
id|dev
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|ret
op_assign
op_minus
id|EPERM
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|NORMMODE
suffix:colon
id|vfc_lock_device
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev-&gt;control_reg
op_and_assign
op_complement
id|VFC_CONTROL_DIAGMODE
suffix:semicolon
id|sbus_writel
c_func
(paren
id|dev-&gt;control_reg
comma
op_amp
id|dev-&gt;regs-&gt;control
)paren
suffix:semicolon
id|vfc_unlock_device
c_func
(paren
id|dev
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CAPTRSTR
suffix:colon
id|vfc_capture_start
c_func
(paren
id|dev
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CAPTRWAIT
suffix:colon
id|vfc_capture_poll
c_func
(paren
id|dev
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
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
r_break
suffix:semicolon
)brace
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|vfc_port_change_ioctl
r_int
id|vfc_port_change_ioctl
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
r_struct
id|vfc_dev
op_star
id|dev
comma
r_int
r_int
id|arg
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
id|cmd
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|cmd
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_int
r_int
)paren
)paren
)paren
(brace
id|VFC_IOCTL_DEBUG_PRINTK
c_func
(paren
(paren
l_string|&quot;vfc%d: User passed bogus pointer to &quot;
l_string|&quot;vfc_port_change_ioctl&bslash;n&quot;
comma
id|dev-&gt;instance
)paren
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|VFC_IOCTL_DEBUG_PRINTK
c_func
(paren
(paren
l_string|&quot;vfc%d: IOCTL(VFCPORTCHG) arg=0x%x&bslash;n&quot;
comma
id|dev-&gt;instance
comma
id|cmd
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
l_int|1
suffix:colon
r_case
l_int|2
suffix:colon
id|VFC_SAA9051_SA
c_func
(paren
id|dev
comma
id|VFC_SAA9051_HSY_START
)paren
op_assign
l_int|0x72
suffix:semicolon
id|VFC_SAA9051_SA
c_func
(paren
id|dev
comma
id|VFC_SAA9051_HSY_STOP
)paren
op_assign
l_int|0x52
suffix:semicolon
id|VFC_SAA9051_SA
c_func
(paren
id|dev
comma
id|VFC_SAA9051_HC_START
)paren
op_assign
l_int|0x36
suffix:semicolon
id|VFC_SAA9051_SA
c_func
(paren
id|dev
comma
id|VFC_SAA9051_HC_STOP
)paren
op_assign
l_int|0x18
suffix:semicolon
id|VFC_SAA9051_SA
c_func
(paren
id|dev
comma
id|VFC_SAA9051_HORIZ_PEAK
)paren
op_assign
id|VFC_SAA9051_BP2
suffix:semicolon
id|VFC_SAA9051_SA
c_func
(paren
id|dev
comma
id|VFC_SAA9051_C3
)paren
op_assign
id|VFC_SAA9051_CT
op_or
id|VFC_SAA9051_SS3
suffix:semicolon
id|VFC_SAA9051_SA
c_func
(paren
id|dev
comma
id|VFC_SAA9051_SECAM_DELAY
)paren
op_assign
l_int|0x3e
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|VFC_SAA9051_SA
c_func
(paren
id|dev
comma
id|VFC_SAA9051_HSY_START
)paren
op_assign
l_int|0x3a
suffix:semicolon
id|VFC_SAA9051_SA
c_func
(paren
id|dev
comma
id|VFC_SAA9051_HSY_STOP
)paren
op_assign
l_int|0x17
suffix:semicolon
id|VFC_SAA9051_SA
c_func
(paren
id|dev
comma
id|VFC_SAA9051_HC_START
)paren
op_assign
l_int|0xfa
suffix:semicolon
id|VFC_SAA9051_SA
c_func
(paren
id|dev
comma
id|VFC_SAA9051_HC_STOP
)paren
op_assign
l_int|0xde
suffix:semicolon
id|VFC_SAA9051_SA
c_func
(paren
id|dev
comma
id|VFC_SAA9051_HORIZ_PEAK
)paren
op_assign
id|VFC_SAA9051_BY
op_or
id|VFC_SAA9051_PF
op_or
id|VFC_SAA9051_BP2
suffix:semicolon
id|VFC_SAA9051_SA
c_func
(paren
id|dev
comma
id|VFC_SAA9051_C3
)paren
op_assign
id|VFC_SAA9051_YC
suffix:semicolon
id|VFC_SAA9051_SA
c_func
(paren
id|dev
comma
id|VFC_SAA9051_SECAM_DELAY
)paren
op_assign
l_int|0
suffix:semicolon
id|VFC_SAA9051_SA
c_func
(paren
id|dev
comma
id|VFC_SAA9051_C2
)paren
op_and_assign
op_complement
(paren
id|VFC_SAA9051_SS0
op_or
id|VFC_SAA9051_SS1
)paren
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
r_return
id|ret
suffix:semicolon
r_break
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
l_int|1
suffix:colon
id|VFC_SAA9051_SA
c_func
(paren
id|dev
comma
id|VFC_SAA9051_C2
)paren
op_or_assign
(paren
id|VFC_SAA9051_SS0
op_or
id|VFC_SAA9051_SS1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|VFC_SAA9051_SA
c_func
(paren
id|dev
comma
id|VFC_SAA9051_C2
)paren
op_and_assign
op_complement
(paren
id|VFC_SAA9051_SS0
op_or
id|VFC_SAA9051_SS1
)paren
suffix:semicolon
id|VFC_SAA9051_SA
c_func
(paren
id|dev
comma
id|VFC_SAA9051_C2
)paren
op_or_assign
id|VFC_SAA9051_SS0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_return
id|ret
suffix:semicolon
r_break
suffix:semicolon
)brace
id|VFC_SAA9051_SA
c_func
(paren
id|dev
comma
id|VFC_SAA9051_C3
)paren
op_and_assign
op_complement
(paren
id|VFC_SAA9051_SS2
)paren
suffix:semicolon
id|ret
op_assign
id|vfc_update_saa9051
c_func
(paren
id|dev
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|500
)paren
suffix:semicolon
id|VFC_SAA9051_SA
c_func
(paren
id|dev
comma
id|VFC_SAA9051_C3
)paren
op_or_assign
(paren
id|VFC_SAA9051_SS2
)paren
suffix:semicolon
id|ret
op_assign
id|vfc_update_saa9051
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|vfc_set_video_ioctl
r_int
id|vfc_set_video_ioctl
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
r_struct
id|vfc_dev
op_star
id|dev
comma
r_int
r_int
id|arg
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
id|cmd
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|cmd
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_int
r_int
)paren
)paren
)paren
(brace
id|VFC_IOCTL_DEBUG_PRINTK
c_func
(paren
(paren
l_string|&quot;vfc%d: User passed bogus pointer to &quot;
l_string|&quot;vfc_set_video_ioctl&bslash;n&quot;
comma
id|dev-&gt;instance
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|VFC_IOCTL_DEBUG_PRINTK
c_func
(paren
(paren
l_string|&quot;vfc%d: IOCTL(VFCSVID) arg=0x%x&bslash;n&quot;
comma
id|dev-&gt;instance
comma
id|cmd
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|STD_NTSC
suffix:colon
id|VFC_SAA9051_SA
c_func
(paren
id|dev
comma
id|VFC_SAA9051_C1
)paren
op_and_assign
op_complement
id|VFC_SAA9051_ALT
suffix:semicolon
id|VFC_SAA9051_SA
c_func
(paren
id|dev
comma
id|VFC_SAA9051_C1
)paren
op_or_assign
id|VFC_SAA9051_YPN
op_or
id|VFC_SAA9051_CCFR0
op_or
id|VFC_SAA9051_CCFR1
op_or
id|VFC_SAA9051_FS
suffix:semicolon
id|ret
op_assign
id|vfc_update_saa9051
c_func
(paren
id|dev
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|STD_PAL
suffix:colon
id|VFC_SAA9051_SA
c_func
(paren
id|dev
comma
id|VFC_SAA9051_C1
)paren
op_and_assign
op_complement
(paren
id|VFC_SAA9051_YPN
op_or
id|VFC_SAA9051_CCFR1
op_or
id|VFC_SAA9051_CCFR0
op_or
id|VFC_SAA9051_FS
)paren
suffix:semicolon
id|VFC_SAA9051_SA
c_func
(paren
id|dev
comma
id|VFC_SAA9051_C1
)paren
op_or_assign
id|VFC_SAA9051_ALT
suffix:semicolon
id|ret
op_assign
id|vfc_update_saa9051
c_func
(paren
id|dev
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|COLOR_ON
suffix:colon
id|VFC_SAA9051_SA
c_func
(paren
id|dev
comma
id|VFC_SAA9051_C1
)paren
op_or_assign
id|VFC_SAA9051_CO
suffix:semicolon
id|VFC_SAA9051_SA
c_func
(paren
id|dev
comma
id|VFC_SAA9051_HORIZ_PEAK
)paren
op_and_assign
op_complement
(paren
id|VFC_SAA9051_BY
op_or
id|VFC_SAA9051_PF
)paren
suffix:semicolon
id|ret
op_assign
id|vfc_update_saa9051
c_func
(paren
id|dev
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MONO
suffix:colon
id|VFC_SAA9051_SA
c_func
(paren
id|dev
comma
id|VFC_SAA9051_C1
)paren
op_and_assign
op_complement
(paren
id|VFC_SAA9051_CO
)paren
suffix:semicolon
id|VFC_SAA9051_SA
c_func
(paren
id|dev
comma
id|VFC_SAA9051_HORIZ_PEAK
)paren
op_or_assign
(paren
id|VFC_SAA9051_BY
op_or
id|VFC_SAA9051_PF
)paren
suffix:semicolon
id|ret
op_assign
id|vfc_update_saa9051
c_func
(paren
id|dev
)paren
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
r_break
suffix:semicolon
)brace
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|vfc_get_video_ioctl
r_int
id|vfc_get_video_ioctl
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
r_struct
id|vfc_dev
op_star
id|dev
comma
r_int
r_int
id|arg
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|status
op_assign
id|NO_LOCK
suffix:semicolon
r_int
r_char
id|buf
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|vfc_i2c_recvbuf
c_func
(paren
id|dev
comma
id|VFC_SAA9051_ADDR
comma
id|buf
comma
l_int|1
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;vfc%d: Unable to get status&bslash;n&quot;
comma
id|dev-&gt;instance
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|buf
(braket
l_int|0
)braket
op_amp
id|VFC_SAA9051_HLOCK
)paren
(brace
id|status
op_assign
id|NO_LOCK
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|buf
(braket
l_int|0
)braket
op_amp
id|VFC_SAA9051_FD
)paren
(brace
r_if
c_cond
(paren
id|buf
(braket
l_int|0
)braket
op_amp
id|VFC_SAA9051_CD
)paren
(brace
id|status
op_assign
id|NTSC_COLOR
suffix:semicolon
)brace
r_else
id|status
op_assign
id|NTSC_NOCOLOR
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|buf
(braket
l_int|0
)braket
op_amp
id|VFC_SAA9051_CD
)paren
(brace
id|status
op_assign
id|PAL_COLOR
suffix:semicolon
)brace
r_else
id|status
op_assign
id|PAL_NOCOLOR
suffix:semicolon
)brace
id|VFC_IOCTL_DEBUG_PRINTK
c_func
(paren
(paren
l_string|&quot;vfc%d: IOCTL(VFCGVID) returning status 0x%x; &quot;
l_string|&quot;buf[0]=%x&bslash;n&quot;
comma
id|dev-&gt;instance
comma
id|status
comma
id|buf
(braket
l_int|0
)braket
)paren
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
comma
op_amp
id|status
comma
r_sizeof
(paren
r_int
r_int
)paren
)paren
)paren
(brace
id|VFC_IOCTL_DEBUG_PRINTK
c_func
(paren
(paren
l_string|&quot;vfc%d: User passed bogus pointer to &quot;
l_string|&quot;vfc_get_video_ioctl&bslash;n&quot;
comma
id|dev-&gt;instance
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|vfc_ioctl
r_static
r_int
id|vfc_ioctl
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
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|tmp
suffix:semicolon
r_struct
id|vfc_dev
op_star
id|dev
suffix:semicolon
id|dev
op_assign
id|vfc_get_dev_ptr
c_func
(paren
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|cmd
op_amp
l_int|0x0000ffff
)paren
(brace
r_case
id|VFCGCTRL
suffix:colon
macro_line|#if 0
id|VFC_IOCTL_DEBUG_PRINTK
c_func
(paren
(paren
l_string|&quot;vfc%d: IOCTL(VFCGCTRL)&bslash;n&quot;
comma
id|dev-&gt;instance
)paren
)paren
suffix:semicolon
macro_line|#endif
id|tmp
op_assign
id|sbus_readl
c_func
(paren
op_amp
id|dev-&gt;regs-&gt;control
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
comma
op_amp
id|tmp
comma
r_sizeof
(paren
r_int
r_int
)paren
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VFCSCTRL
suffix:colon
id|ret
op_assign
id|vfc_set_control_ioctl
c_func
(paren
id|inode
comma
id|file
comma
id|dev
comma
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VFCGVID
suffix:colon
id|ret
op_assign
id|vfc_get_video_ioctl
c_func
(paren
id|inode
comma
id|file
comma
id|dev
comma
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VFCSVID
suffix:colon
id|ret
op_assign
id|vfc_set_video_ioctl
c_func
(paren
id|inode
comma
id|file
comma
id|dev
comma
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VFCHUE
suffix:colon
id|VFC_IOCTL_DEBUG_PRINTK
c_func
(paren
(paren
l_string|&quot;vfc%d: IOCTL(VFCHUE)&bslash;n&quot;
comma
id|dev-&gt;instance
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
id|tmp
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_int
r_int
)paren
)paren
)paren
(brace
id|VFC_IOCTL_DEBUG_PRINTK
c_func
(paren
(paren
l_string|&quot;vfc%d: User passed bogus pointer &quot;
l_string|&quot;to IOCTL(VFCHUE)&quot;
comma
id|dev-&gt;instance
)paren
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
r_else
(brace
id|VFC_SAA9051_SA
c_func
(paren
id|dev
comma
id|VFC_SAA9051_HUE
)paren
op_assign
id|tmp
suffix:semicolon
id|vfc_update_saa9051
c_func
(paren
id|dev
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|VFCPORTCHG
suffix:colon
id|ret
op_assign
id|vfc_port_change_ioctl
c_func
(paren
id|inode
comma
id|file
comma
id|dev
comma
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VFCRDINFO
suffix:colon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|VFC_IOCTL_DEBUG_PRINTK
c_func
(paren
(paren
l_string|&quot;vfc%d: IOCTL(VFCRDINFO)&bslash;n&quot;
comma
id|dev-&gt;instance
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ret
op_assign
id|vfc_debug
c_func
(paren
id|vfc_get_dev_ptr
c_func
(paren
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
)paren
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|vfc_mmap
r_static
r_int
id|vfc_mmap
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
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
r_int
r_int
id|map_size
comma
id|ret
comma
id|map_offset
suffix:semicolon
r_struct
id|vfc_dev
op_star
id|dev
suffix:semicolon
id|dev
op_assign
id|vfc_get_dev_ptr
c_func
(paren
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|map_size
op_assign
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
suffix:semicolon
r_if
c_cond
(paren
id|map_size
OG
r_sizeof
(paren
r_struct
id|vfc_regs
)paren
)paren
(brace
id|map_size
op_assign
r_sizeof
(paren
r_struct
id|vfc_regs
)paren
suffix:semicolon
)brace
id|vma-&gt;vm_flags
op_or_assign
(paren
id|VM_SHM
op_or
id|VM_LOCKED
op_or
id|VM_IO
op_or
id|VM_MAYREAD
op_or
id|VM_MAYWRITE
op_or
id|VM_MAYSHARE
)paren
suffix:semicolon
id|map_offset
op_assign
(paren
r_int
r_int
)paren
(paren
r_int
)paren
id|dev-&gt;phys_regs
suffix:semicolon
id|ret
op_assign
id|io_remap_page_range
c_func
(paren
id|vma-&gt;vm_start
comma
id|map_offset
comma
id|map_size
comma
id|vma-&gt;vm_page_prot
comma
id|dev-&gt;which_io
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|vfc_fops
r_static
r_struct
id|file_operations
id|vfc_fops
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
id|ioctl
suffix:colon
id|vfc_ioctl
comma
id|mmap
suffix:colon
id|vfc_mmap
comma
id|open
suffix:colon
id|vfc_open
comma
id|release
suffix:colon
id|vfc_release
comma
)brace
suffix:semicolon
DECL|function|vfc_probe
r_static
r_int
id|vfc_probe
c_func
(paren
r_void
)paren
(brace
r_struct
id|sbus_bus
op_star
id|sbus
suffix:semicolon
r_struct
id|sbus_dev
op_star
id|sdev
op_assign
l_int|NULL
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_int
id|instance
op_assign
l_int|0
comma
id|cards
op_assign
l_int|0
suffix:semicolon
id|for_all_sbusdev
c_func
(paren
id|sdev
comma
id|sbus
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|sdev-&gt;prom_name
comma
l_string|&quot;vfc&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|cards
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|cards
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|vfc_dev_lst
op_assign
(paren
r_struct
id|vfc_dev
op_star
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|vfc_dev
op_star
)paren
op_star
(paren
id|cards
op_plus
l_int|1
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vfc_dev_lst
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|vfc_dev_lst
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|vfc_dev
op_star
)paren
op_star
(paren
id|cards
op_plus
l_int|1
)paren
)paren
suffix:semicolon
id|vfc_dev_lst
(braket
id|cards
)braket
op_assign
l_int|NULL
suffix:semicolon
id|ret
op_assign
id|devfs_register_chrdev
c_func
(paren
id|VFC_MAJOR
comma
id|vfcstr
comma
op_amp
id|vfc_fops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Unable to get major number %d&bslash;n&quot;
comma
id|VFC_MAJOR
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|vfc_dev_lst
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|devfs_handle
op_assign
id|devfs_mk_dir
(paren
l_int|NULL
comma
l_string|&quot;vfc&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|instance
op_assign
l_int|0
suffix:semicolon
id|for_all_sbusdev
c_func
(paren
id|sdev
comma
id|sbus
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|sdev-&gt;prom_name
comma
l_string|&quot;vfc&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|vfc_dev_lst
(braket
id|instance
)braket
op_assign
(paren
r_struct
id|vfc_dev
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|vfc_dev
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vfc_dev_lst
(braket
id|instance
)braket
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|ret
op_assign
id|init_vfc_device
c_func
(paren
id|sdev
comma
id|vfc_dev_lst
(braket
id|instance
)braket
comma
id|instance
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Unable to initialize&quot;
l_string|&quot; vfc%d device&bslash;n&quot;
comma
id|instance
)paren
suffix:semicolon
)brace
r_else
(brace
)brace
id|instance
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
macro_line|#else 
r_int
id|vfc_init
c_func
(paren
r_void
)paren
macro_line|#endif
(brace
r_return
id|vfc_probe
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|function|deinit_vfc_device
r_static
r_void
id|deinit_vfc_device
c_func
(paren
r_struct
id|vfc_dev
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
(brace
r_return
suffix:semicolon
)brace
id|devfs_unregister
(paren
id|dev-&gt;de
)paren
suffix:semicolon
id|sbus_iounmap
c_func
(paren
(paren
r_int
r_int
)paren
id|dev-&gt;regs
comma
r_sizeof
(paren
r_struct
id|vfc_regs
)paren
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
r_struct
id|vfc_dev
op_star
op_star
id|devp
suffix:semicolon
id|devfs_unregister_chrdev
c_func
(paren
id|VFC_MAJOR
comma
id|vfcstr
)paren
suffix:semicolon
r_for
c_loop
(paren
id|devp
op_assign
id|vfc_dev_lst
suffix:semicolon
op_star
id|devp
suffix:semicolon
id|devp
op_increment
)paren
id|deinit_vfc_device
c_func
(paren
op_star
id|devp
)paren
suffix:semicolon
id|devfs_unregister
(paren
id|devfs_handle
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|vfc_dev_lst
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif
eof
