multiline_comment|/*&n; * Atari Joystick Driver for Linux&n; * by Robert de Vries (robert@and.nl) 19Jul93&n; *&n; * 16 Nov 1994 Andreas Schwab&n; * Support for three button mouse (shamelessly stolen from MiNT)&n; * third button wired to one of the joystick directions on joystick 1&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/atarikb.h&gt;
macro_line|#include &lt;asm/atari_joystick.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|MAJOR_NR
mdefine_line|#define MAJOR_NR    JOYSTICK_MAJOR
DECL|macro|ANALOG_JOY
mdefine_line|#define&t;ANALOG_JOY(n)&t;(!(n &amp; 0x80))
DECL|macro|DIGITAL_JOY
mdefine_line|#define&t;DIGITAL_JOY(n)&t;(minor(n) &amp; 0x80)
DECL|macro|DEVICE_NR
mdefine_line|#define&t;DEVICE_NR(n)&t;(minor(n) &amp; 0x7f)
DECL|variable|joystick
r_static
r_struct
id|joystick_status
id|joystick
(braket
l_int|2
)braket
suffix:semicolon
DECL|variable|atari_mouse_buttons
r_int
id|atari_mouse_buttons
suffix:semicolon
multiline_comment|/* for three-button mouse */
DECL|function|atari_joystick_interrupt
r_void
id|atari_joystick_interrupt
c_func
(paren
r_char
op_star
id|buf
)paren
(brace
r_int
id|j
suffix:semicolon
multiline_comment|/*    ikbd_joystick_disable(); */
id|j
op_assign
id|buf
(braket
l_int|0
)braket
op_amp
l_int|0x1
suffix:semicolon
id|joystick
(braket
id|j
)braket
dot
id|dir
op_assign
id|buf
(braket
l_int|1
)braket
op_amp
l_int|0xF
suffix:semicolon
id|joystick
(braket
id|j
)braket
dot
id|fire
op_assign
(paren
id|buf
(braket
l_int|1
)braket
op_amp
l_int|0x80
)paren
op_rshift
l_int|7
suffix:semicolon
id|joystick
(braket
id|j
)braket
dot
id|ready
op_assign
l_int|1
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|joystick
(braket
id|j
)braket
dot
id|wait
)paren
suffix:semicolon
multiline_comment|/* For three-button mouse emulation fake a mouse packet */
r_if
c_cond
(paren
id|atari_mouse_interrupt_hook
op_logical_and
id|j
op_eq
l_int|1
op_logical_and
(paren
id|buf
(braket
l_int|1
)braket
op_amp
l_int|1
)paren
op_ne
(paren
(paren
id|atari_mouse_buttons
op_amp
l_int|2
)paren
op_rshift
l_int|1
)paren
)paren
(brace
r_char
id|faked_packet
(braket
l_int|3
)braket
suffix:semicolon
id|atari_mouse_buttons
op_assign
(paren
id|atari_mouse_buttons
op_amp
l_int|5
)paren
op_or
(paren
(paren
id|buf
(braket
l_int|1
)braket
op_amp
l_int|1
)paren
op_lshift
l_int|1
)paren
suffix:semicolon
id|faked_packet
(braket
l_int|0
)braket
op_assign
(paren
id|atari_mouse_buttons
op_amp
l_int|1
)paren
op_or
(paren
id|atari_mouse_buttons
op_amp
l_int|4
ques
c_cond
l_int|2
suffix:colon
l_int|0
)paren
suffix:semicolon
id|faked_packet
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|faked_packet
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
id|atari_mouse_interrupt_hook
(paren
id|faked_packet
)paren
suffix:semicolon
)brace
multiline_comment|/*    ikbd_joystick_event_on(); */
)brace
DECL|function|release_joystick
r_static
r_int
id|release_joystick
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
id|DEVICE_NR
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
id|joystick
(braket
id|minor
)braket
dot
id|active
op_assign
l_int|0
suffix:semicolon
id|joystick
(braket
id|minor
)braket
dot
id|ready
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|joystick
(braket
l_int|0
)braket
dot
id|active
op_eq
l_int|0
)paren
op_logical_and
(paren
id|joystick
(braket
l_int|1
)braket
dot
id|active
op_eq
l_int|0
)paren
)paren
id|ikbd_joystick_disable
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|open_joystick
r_static
r_int
id|open_joystick
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
id|DEVICE_NR
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|DIGITAL_JOY
c_func
(paren
id|inode-&gt;i_rdev
)paren
op_logical_or
id|minor
OG
l_int|1
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|joystick
(braket
id|minor
)braket
dot
id|active
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|joystick
(braket
id|minor
)braket
dot
id|active
op_assign
l_int|1
suffix:semicolon
id|joystick
(braket
id|minor
)braket
dot
id|ready
op_assign
l_int|0
suffix:semicolon
id|ikbd_joystick_event_on
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|write_joystick
r_static
id|ssize_t
id|write_joystick
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
id|buffer
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|read_joystick
r_static
id|ssize_t
id|read_joystick
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buffer
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
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_int
id|minor
op_assign
id|DEVICE_NR
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
l_int|2
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|joystick
(braket
id|minor
)braket
dot
id|ready
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
id|joystick
(braket
id|minor
)braket
dot
id|ready
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|joystick
(braket
id|minor
)braket
dot
id|fire
comma
id|buffer
op_increment
)paren
op_logical_or
id|put_user
c_func
(paren
id|joystick
(braket
id|minor
)braket
dot
id|dir
comma
id|buffer
op_increment
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
l_int|2
)paren
r_if
c_cond
(paren
id|clear_user
c_func
(paren
id|buffer
comma
id|count
op_minus
l_int|2
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|joystick_poll
r_static
r_int
r_int
id|joystick_poll
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|poll_table
op_star
id|wait
)paren
(brace
r_int
id|minor
op_assign
id|DEVICE_NR
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_rdev
)paren
suffix:semicolon
id|poll_wait
c_func
(paren
id|file
comma
op_amp
id|joystick
(braket
id|minor
)braket
dot
id|wait
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|joystick
(braket
id|minor
)braket
dot
id|ready
)paren
r_return
id|POLLIN
op_or
id|POLLRDNORM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|atari_joystick_fops
r_struct
id|file_operations
id|atari_joystick_fops
op_assign
(brace
dot
id|read
op_assign
id|read_joystick
comma
dot
id|write
op_assign
id|write_joystick
comma
dot
id|poll
op_assign
id|joystick_poll
comma
dot
id|open
op_assign
id|open_joystick
comma
dot
id|release
op_assign
id|release_joystick
comma
)brace
suffix:semicolon
DECL|function|atari_joystick_init
r_int
id|__init
id|atari_joystick_init
c_func
(paren
r_void
)paren
(brace
id|joystick
(braket
l_int|0
)braket
dot
id|active
op_assign
id|joystick
(braket
l_int|1
)braket
dot
id|active
op_assign
l_int|0
suffix:semicolon
id|joystick
(braket
l_int|0
)braket
dot
id|ready
op_assign
id|joystick
(braket
l_int|1
)braket
dot
id|ready
op_assign
l_int|0
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|joystick
(braket
l_int|0
)braket
dot
id|wait
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|joystick
(braket
l_int|1
)braket
dot
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|devfs_register_chrdev
c_func
(paren
id|MAJOR_NR
comma
l_string|&quot;Joystick&quot;
comma
op_amp
id|atari_joystick_fops
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;unable to get major %d for joystick devices&bslash;n&quot;
comma
id|MAJOR_NR
)paren
suffix:semicolon
id|devfs_register_series
(paren
l_int|NULL
comma
l_string|&quot;joysticks/digital%u&quot;
comma
l_int|2
comma
id|DEVFS_FL_DEFAULT
comma
id|MAJOR_NR
comma
l_int|128
comma
id|S_IFCHR
op_or
id|S_IRUSR
op_or
id|S_IWUSR
comma
op_amp
id|atari_joystick_fops
comma
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
