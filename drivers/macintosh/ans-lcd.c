multiline_comment|/*&n; * /dev/lcd driver for Apple Network Servers.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/sections.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/ans-lcd.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|ANSLCD_ADDR
mdefine_line|#define ANSLCD_ADDR&t;&t;0xf301c000
DECL|macro|ANSLCD_CTRL_IX
mdefine_line|#define ANSLCD_CTRL_IX 0x00
DECL|macro|ANSLCD_DATA_IX
mdefine_line|#define ANSLCD_DATA_IX 0x10
DECL|variable|anslcd_short_delay
r_static
r_int
r_int
id|anslcd_short_delay
op_assign
l_int|80
suffix:semicolon
DECL|variable|anslcd_long_delay
r_static
r_int
r_int
id|anslcd_long_delay
op_assign
l_int|3280
suffix:semicolon
DECL|variable|anslcd_ptr
r_static
r_volatile
r_int
r_char
id|__iomem
op_star
id|anslcd_ptr
suffix:semicolon
DECL|macro|DEBUG
macro_line|#undef DEBUG
r_static
r_void
id|__pmac
DECL|function|anslcd_write_byte_ctrl
id|anslcd_write_byte_ctrl
(paren
r_int
r_char
id|c
)paren
(brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;LCD: CTRL byte: %02x&bslash;n&quot;
comma
id|c
)paren
suffix:semicolon
macro_line|#endif
id|out_8
c_func
(paren
id|anslcd_ptr
op_plus
id|ANSLCD_CTRL_IX
comma
id|c
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|c
)paren
(brace
r_case
l_int|1
suffix:colon
r_case
l_int|2
suffix:colon
r_case
l_int|3
suffix:colon
id|udelay
c_func
(paren
id|anslcd_long_delay
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|udelay
c_func
(paren
id|anslcd_short_delay
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
id|__pmac
DECL|function|anslcd_write_byte_data
id|anslcd_write_byte_data
(paren
r_int
r_char
id|c
)paren
(brace
id|out_8
c_func
(paren
id|anslcd_ptr
op_plus
id|ANSLCD_DATA_IX
comma
id|c
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|anslcd_short_delay
)paren
suffix:semicolon
)brace
r_static
id|ssize_t
id|__pmac
DECL|function|anslcd_write
id|anslcd_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
id|__user
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
r_const
r_char
id|__user
op_star
id|p
op_assign
id|buf
suffix:semicolon
r_int
id|i
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;LCD: write&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|buf
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
op_star
id|ppos
suffix:semicolon
id|count
OG
l_int|0
suffix:semicolon
op_increment
id|i
comma
op_increment
id|p
comma
op_decrement
id|count
)paren
(brace
r_char
id|c
suffix:semicolon
id|__get_user
c_func
(paren
id|c
comma
id|p
)paren
suffix:semicolon
id|anslcd_write_byte_data
c_func
(paren
id|c
)paren
suffix:semicolon
)brace
op_star
id|ppos
op_assign
id|i
suffix:semicolon
r_return
id|p
op_minus
id|buf
suffix:semicolon
)brace
r_static
r_int
id|__pmac
DECL|function|anslcd_ioctl
id|anslcd_ioctl
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
r_char
id|ch
comma
id|__user
op_star
id|temp
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;LCD: ioctl(%d,%d)&bslash;n&quot;
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
macro_line|#endif
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|ANSLCD_CLEAR
suffix:colon
id|anslcd_write_byte_ctrl
(paren
l_int|0x38
)paren
suffix:semicolon
id|anslcd_write_byte_ctrl
(paren
l_int|0x0f
)paren
suffix:semicolon
id|anslcd_write_byte_ctrl
(paren
l_int|0x06
)paren
suffix:semicolon
id|anslcd_write_byte_ctrl
(paren
l_int|0x01
)paren
suffix:semicolon
id|anslcd_write_byte_ctrl
(paren
l_int|0x02
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|ANSLCD_SENDCTRL
suffix:colon
id|temp
op_assign
(paren
r_char
id|__user
op_star
)paren
id|arg
suffix:semicolon
id|__get_user
c_func
(paren
id|ch
comma
id|temp
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|ch
suffix:semicolon
id|temp
op_increment
)paren
(brace
multiline_comment|/* FIXME: This is ugly, but should work, as a &bslash;0 byte is not a valid command code */
id|anslcd_write_byte_ctrl
(paren
id|ch
)paren
suffix:semicolon
id|__get_user
c_func
(paren
id|ch
comma
id|temp
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
r_case
id|ANSLCD_SETSHORTDELAY
suffix:colon
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
id|EACCES
suffix:semicolon
id|anslcd_short_delay
op_assign
id|arg
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|ANSLCD_SETLONGDELAY
suffix:colon
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
id|EACCES
suffix:semicolon
id|anslcd_long_delay
op_assign
id|arg
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
r_static
r_int
id|__pmac
DECL|function|anslcd_open
id|anslcd_open
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|anslcd_fops
r_struct
id|file_operations
id|anslcd_fops
op_assign
(brace
dot
id|write
op_assign
id|anslcd_write
comma
dot
id|ioctl
op_assign
id|anslcd_ioctl
comma
dot
id|open
op_assign
id|anslcd_open
comma
)brace
suffix:semicolon
DECL|variable|anslcd_dev
r_static
r_struct
id|miscdevice
id|anslcd_dev
op_assign
(brace
id|ANSLCD_MINOR
comma
l_string|&quot;anslcd&quot;
comma
op_amp
id|anslcd_fops
)brace
suffix:semicolon
DECL|variable|anslcd_logo
r_const
r_char
id|anslcd_logo
(braket
)braket
op_assign
l_string|&quot;********************&quot;
multiline_comment|/* Line #1 */
l_string|&quot;*      LINUX!      *&quot;
multiline_comment|/* Line #3 */
l_string|&quot;*    Welcome to    *&quot;
multiline_comment|/* Line #2 */
l_string|&quot;********************&quot;
suffix:semicolon
multiline_comment|/* Line #4 */
r_static
r_int
id|__init
DECL|function|anslcd_init
id|anslcd_init
c_func
(paren
r_void
)paren
(brace
r_int
id|a
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_struct
id|device_node
op_star
id|node
suffix:semicolon
id|node
op_assign
id|find_devices
c_func
(paren
l_string|&quot;lcd&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node
op_logical_or
op_logical_neg
id|node-&gt;parent
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|node-&gt;parent-&gt;name
comma
l_string|&quot;gc&quot;
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|anslcd_ptr
op_assign
id|ioremap
c_func
(paren
id|ANSLCD_ADDR
comma
l_int|0x20
)paren
suffix:semicolon
id|retval
op_assign
id|misc_register
c_func
(paren
op_amp
id|anslcd_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;LCD: misc_register failed&bslash;n&quot;
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|anslcd_ptr
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;LCD: init&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|anslcd_write_byte_ctrl
(paren
l_int|0x38
)paren
suffix:semicolon
id|anslcd_write_byte_ctrl
(paren
l_int|0x0c
)paren
suffix:semicolon
id|anslcd_write_byte_ctrl
(paren
l_int|0x06
)paren
suffix:semicolon
id|anslcd_write_byte_ctrl
(paren
l_int|0x01
)paren
suffix:semicolon
id|anslcd_write_byte_ctrl
(paren
l_int|0x02
)paren
suffix:semicolon
r_for
c_loop
(paren
id|a
op_assign
l_int|0
suffix:semicolon
id|a
OL
l_int|80
suffix:semicolon
id|a
op_increment
)paren
(brace
id|anslcd_write_byte_data
c_func
(paren
id|anslcd_logo
(braket
id|a
)braket
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
id|__exit
DECL|function|anslcd_exit
id|anslcd_exit
c_func
(paren
r_void
)paren
(brace
id|misc_deregister
c_func
(paren
op_amp
id|anslcd_dev
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|anslcd_ptr
)paren
suffix:semicolon
)brace
DECL|variable|anslcd_init
id|module_init
c_func
(paren
id|anslcd_init
)paren
suffix:semicolon
DECL|variable|anslcd_exit
id|module_exit
c_func
(paren
id|anslcd_exit
)paren
suffix:semicolon
eof
