multiline_comment|/*&n; * linux/drivers/char/qpmouse.c&n; *&n; * Driver for a 82C710 C&amp;T mouse interface chip.&n; *&n; * Based on the PS/2 driver by Johan Myreen.&n; *&n; * Corrections in device setup for some laptop mice &amp; trackballs.&n; * 02Feb93  (troyer@saifr00.cfsat.Honeywell.COM,mch@wimsey.bc.ca)&n; *&n; * Modified by Johan Myreen (jem@iki.fi) 04Aug93&n; *   to include support for QuickPort mouse.&n; *&n; * Changed references to &quot;QuickPort&quot; with &quot;82C710&quot; since &quot;QuickPort&quot;&n; * is not what this driver is all about -- QuickPort is just a&n; * connector type, and this driver is for the mouse port on the Chips&n; * &amp; Technologies 82C710 interface chip. 15Nov93 jem@iki.fi&n; *&n; * Added support for SIGIO. 28Jul95 jem@iki.fi&n; *&n; * Rearranged SIGIO support to use code from tty_io.  9Sept95 ctm@ardi.com&n; *&n; * Modularised 8-Sep-95 Philip Blundell &lt;pjb27@cam.ac.uk&gt;&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;linux/pc_keyb.h&gt;&t;&t;/* mouse enable command.. */
multiline_comment|/*&n; * We use the same minor number as the PS/2 mouse for (bad) historical&n; * reasons..&n; */
DECL|macro|PSMOUSE_MINOR
mdefine_line|#define PSMOUSE_MINOR      1&t;       &t;&t;/* Minor device # for this mouse */
DECL|macro|QP_BUF_SIZE
mdefine_line|#define QP_BUF_SIZE&t;2048
DECL|struct|qp_queue
r_struct
id|qp_queue
(brace
DECL|member|head
r_int
r_int
id|head
suffix:semicolon
DECL|member|tail
r_int
r_int
id|tail
suffix:semicolon
DECL|member|proc_list
id|wait_queue_head_t
id|proc_list
suffix:semicolon
DECL|member|fasync
r_struct
id|fasync_struct
op_star
id|fasync
suffix:semicolon
DECL|member|buf
r_int
r_char
id|buf
(braket
id|QP_BUF_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|queue
r_static
r_struct
id|qp_queue
op_star
id|queue
suffix:semicolon
DECL|function|get_from_queue
r_static
r_int
r_int
id|get_from_queue
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|result
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|result
op_assign
id|queue-&gt;buf
(braket
id|queue-&gt;tail
)braket
suffix:semicolon
id|queue-&gt;tail
op_assign
(paren
id|queue-&gt;tail
op_plus
l_int|1
)paren
op_amp
(paren
id|QP_BUF_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|queue_empty
r_static
r_inline
r_int
id|queue_empty
c_func
(paren
r_void
)paren
(brace
r_return
id|queue-&gt;head
op_eq
id|queue-&gt;tail
suffix:semicolon
)brace
DECL|function|fasync_qp
r_static
r_int
id|fasync_qp
c_func
(paren
r_int
id|fd
comma
r_struct
id|file
op_star
id|filp
comma
r_int
id|on
)paren
(brace
r_int
id|retval
suffix:semicolon
id|retval
op_assign
id|fasync_helper
c_func
(paren
id|fd
comma
id|filp
comma
id|on
comma
op_amp
id|queue-&gt;fasync
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
r_return
id|retval
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;82C710 Interface&n; */
DECL|macro|QP_DATA
mdefine_line|#define QP_DATA         0x310&t;&t;/* Data Port I/O Address */
DECL|macro|QP_STATUS
mdefine_line|#define QP_STATUS       0x311&t;&t;/* Status Port I/O Address */
DECL|macro|QP_DEV_IDLE
mdefine_line|#define QP_DEV_IDLE     0x01&t;&t;/* Device Idle */
DECL|macro|QP_RX_FULL
mdefine_line|#define QP_RX_FULL      0x02&t;&t;/* Device Char received */
DECL|macro|QP_TX_IDLE
mdefine_line|#define QP_TX_IDLE      0x04&t;&t;/* Device XMIT Idle */
DECL|macro|QP_RESET
mdefine_line|#define QP_RESET        0x08&t;&t;/* Device Reset */
DECL|macro|QP_INTS_ON
mdefine_line|#define QP_INTS_ON      0x10&t;&t;/* Device Interrupt On */
DECL|macro|QP_ERROR_FLAG
mdefine_line|#define QP_ERROR_FLAG   0x20&t;&t;/* Device Error */
DECL|macro|QP_CLEAR
mdefine_line|#define QP_CLEAR        0x40&t;&t;/* Device Clear */
DECL|macro|QP_ENABLE
mdefine_line|#define QP_ENABLE       0x80&t;&t;/* Device Enable */
DECL|macro|QP_IRQ
mdefine_line|#define QP_IRQ          12
DECL|variable|qp_present
r_static
r_int
id|qp_present
suffix:semicolon
DECL|variable|qp_count
r_static
r_int
id|qp_count
suffix:semicolon
DECL|variable|qp_data
r_static
r_int
id|qp_data
op_assign
id|QP_DATA
suffix:semicolon
DECL|variable|qp_status
r_static
r_int
id|qp_status
op_assign
id|QP_STATUS
suffix:semicolon
r_static
r_int
id|poll_qp_status
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|probe_qp
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Interrupt handler for the 82C710 mouse port. A character&n; * is waiting in the 82C710.&n; */
DECL|function|qp_interrupt
r_static
r_void
id|qp_interrupt
c_func
(paren
r_int
id|cpl
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|head
op_assign
id|queue-&gt;head
suffix:semicolon
r_int
id|maxhead
op_assign
(paren
id|queue-&gt;tail
op_minus
l_int|1
)paren
op_amp
(paren
id|QP_BUF_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|add_mouse_randomness
c_func
(paren
id|queue-&gt;buf
(braket
id|head
)braket
op_assign
id|inb
c_func
(paren
id|qp_data
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|head
op_ne
id|maxhead
)paren
(brace
id|head
op_increment
suffix:semicolon
id|head
op_and_assign
id|QP_BUF_SIZE
op_minus
l_int|1
suffix:semicolon
)brace
id|queue-&gt;head
op_assign
id|head
suffix:semicolon
id|kill_fasync
c_func
(paren
op_amp
id|queue-&gt;fasync
comma
id|SIGIO
comma
id|POLL_IN
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|queue-&gt;proc_list
)paren
suffix:semicolon
)brace
DECL|function|release_qp
r_static
r_int
id|release_qp
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
r_char
id|status
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|fasync_qp
c_func
(paren
op_minus
l_int|1
comma
id|file
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|qp_count
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|poll_qp_status
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Warning: Mouse device busy in release_qp()&bslash;n&quot;
)paren
suffix:semicolon
id|status
op_assign
id|inb_p
c_func
(paren
id|qp_status
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|status
op_amp
op_complement
(paren
id|QP_ENABLE
op_or
id|QP_INTS_ON
)paren
comma
id|qp_status
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|poll_qp_status
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Warning: Mouse device busy in release_qp()&bslash;n&quot;
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|QP_IRQ
comma
l_int|NULL
)paren
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Install interrupt handler.&n; * Enable the device, enable interrupts. &n; */
DECL|function|open_qp
r_static
r_int
id|open_qp
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
r_char
id|status
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|qp_present
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|qp_count
op_increment
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|QP_IRQ
comma
id|qp_interrupt
comma
l_int|0
comma
l_string|&quot;PS/2 Mouse&quot;
comma
l_int|NULL
)paren
)paren
(brace
id|qp_count
op_decrement
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|status
op_assign
id|inb_p
c_func
(paren
id|qp_status
)paren
suffix:semicolon
id|status
op_or_assign
(paren
id|QP_ENABLE
op_or
id|QP_RESET
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|status
comma
id|qp_status
)paren
suffix:semicolon
id|status
op_and_assign
op_complement
(paren
id|QP_RESET
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|status
comma
id|qp_status
)paren
suffix:semicolon
id|queue-&gt;head
op_assign
id|queue-&gt;tail
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Flush input queue */
id|status
op_or_assign
id|QP_INTS_ON
suffix:semicolon
id|outb_p
c_func
(paren
id|status
comma
id|qp_status
)paren
suffix:semicolon
multiline_comment|/* Enable interrupts */
r_while
c_loop
(paren
op_logical_neg
id|poll_qp_status
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Error: Mouse device busy in open_qp()&bslash;n&quot;
)paren
suffix:semicolon
id|qp_count
op_decrement
suffix:semicolon
id|status
op_and_assign
op_complement
(paren
id|QP_ENABLE
op_or
id|QP_INTS_ON
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|status
comma
id|qp_status
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|QP_IRQ
comma
l_int|NULL
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|outb_p
c_func
(paren
id|AUX_ENABLE_DEV
comma
id|qp_data
)paren
suffix:semicolon
multiline_comment|/* Wake up mouse */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Write to the 82C710 mouse device.&n; */
DECL|function|write_qp
r_static
id|ssize_t
id|write_qp
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
id|ssize_t
id|i
op_assign
id|count
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
)paren
(brace
r_char
id|c
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|poll_qp_status
c_func
(paren
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|get_user
c_func
(paren
id|c
comma
id|buffer
op_increment
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|c
comma
id|qp_data
)paren
suffix:semicolon
)brace
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_mtime
op_assign
id|CURRENT_TIME
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|poll_qp
r_static
r_int
r_int
id|poll_qp
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
id|poll_wait
c_func
(paren
id|file
comma
op_amp
id|queue-&gt;proc_list
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|queue_empty
c_func
(paren
)paren
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
multiline_comment|/*&n; * Wait for device to send output char and flush any input char.&n; */
DECL|macro|MAX_RETRIES
mdefine_line|#define MAX_RETRIES (60)
DECL|function|poll_qp_status
r_static
r_int
id|poll_qp_status
c_func
(paren
r_void
)paren
(brace
r_int
id|retries
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|inb
c_func
(paren
id|qp_status
)paren
op_amp
(paren
id|QP_RX_FULL
op_or
id|QP_TX_IDLE
op_or
id|QP_DEV_IDLE
)paren
)paren
op_ne
(paren
id|QP_DEV_IDLE
op_or
id|QP_TX_IDLE
)paren
op_logical_and
id|retries
OL
id|MAX_RETRIES
)paren
(brace
r_if
c_cond
(paren
id|inb_p
c_func
(paren
id|qp_status
)paren
op_amp
(paren
id|QP_RX_FULL
)paren
)paren
id|inb_p
c_func
(paren
id|qp_data
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|schedule_timeout
c_func
(paren
(paren
l_int|5
op_star
id|HZ
op_plus
l_int|99
)paren
op_div
l_int|100
)paren
suffix:semicolon
id|retries
op_increment
suffix:semicolon
)brace
r_return
op_logical_neg
(paren
id|retries
op_eq
id|MAX_RETRIES
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Put bytes from input queue to buffer.&n; */
DECL|function|read_qp
r_static
id|ssize_t
id|read_qp
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
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
id|ssize_t
id|i
op_assign
id|count
suffix:semicolon
r_int
r_char
id|c
suffix:semicolon
r_if
c_cond
(paren
id|queue_empty
c_func
(paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|file-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|queue-&gt;proc_list
comma
op_amp
id|wait
)paren
suffix:semicolon
id|repeat
suffix:colon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|queue_empty
c_func
(paren
)paren
op_logical_and
op_logical_neg
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
id|current-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|queue-&gt;proc_list
comma
op_amp
id|wait
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|i
OG
l_int|0
op_logical_and
op_logical_neg
id|queue_empty
c_func
(paren
)paren
)paren
(brace
id|c
op_assign
id|get_from_queue
c_func
(paren
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|c
comma
id|buffer
op_increment
)paren
suffix:semicolon
id|i
op_decrement
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
op_minus
id|i
)paren
(brace
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_atime
op_assign
id|CURRENT_TIME
suffix:semicolon
r_return
id|count
op_minus
id|i
suffix:semicolon
)brace
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|qp_fops
r_struct
id|file_operations
id|qp_fops
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|read
suffix:colon
id|read_qp
comma
id|write
suffix:colon
id|write_qp
comma
id|poll
suffix:colon
id|poll_qp
comma
id|open
suffix:colon
id|open_qp
comma
id|release
suffix:colon
id|release_qp
comma
id|fasync
suffix:colon
id|fasync_qp
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Initialize driver.&n; */
DECL|variable|qp_mouse
r_static
r_struct
id|miscdevice
id|qp_mouse
op_assign
(brace
id|minor
suffix:colon
id|PSMOUSE_MINOR
comma
id|name
suffix:colon
l_string|&quot;QPmouse&quot;
comma
id|fops
suffix:colon
op_amp
id|qp_fops
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Function to read register in 82C710.&n; */
DECL|function|read_710
r_static
r_inline
r_int
r_char
id|read_710
c_func
(paren
r_int
r_char
id|index
)paren
(brace
id|outb_p
c_func
(paren
id|index
comma
l_int|0x390
)paren
suffix:semicolon
multiline_comment|/* Write index */
r_return
id|inb_p
c_func
(paren
l_int|0x391
)paren
suffix:semicolon
multiline_comment|/* Read the data */
)brace
multiline_comment|/*&n; * See if we can find a 82C710 device. Read mouse address.&n; */
DECL|function|probe_qp
r_static
r_int
id|__init
id|probe_qp
c_func
(paren
r_void
)paren
(brace
id|outb_p
c_func
(paren
l_int|0x55
comma
l_int|0x2fa
)paren
suffix:semicolon
multiline_comment|/* Any value except 9, ff or 36 */
id|outb_p
c_func
(paren
l_int|0xaa
comma
l_int|0x3fa
)paren
suffix:semicolon
multiline_comment|/* Inverse of 55 */
id|outb_p
c_func
(paren
l_int|0x36
comma
l_int|0x3fa
)paren
suffix:semicolon
multiline_comment|/* Address the chip */
id|outb_p
c_func
(paren
l_int|0xe4
comma
l_int|0x3fa
)paren
suffix:semicolon
multiline_comment|/* 390/4; 390 = config address */
id|outb_p
c_func
(paren
l_int|0x1b
comma
l_int|0x2fa
)paren
suffix:semicolon
multiline_comment|/* Inverse of e4 */
r_if
c_cond
(paren
id|read_710
c_func
(paren
l_int|0x0f
)paren
op_ne
l_int|0xe4
)paren
multiline_comment|/* Config address found? */
r_return
l_int|0
suffix:semicolon
multiline_comment|/* No: no 82C710 here */
id|qp_data
op_assign
id|read_710
c_func
(paren
l_int|0x0d
)paren
op_star
l_int|4
suffix:semicolon
multiline_comment|/* Get mouse I/O address */
id|qp_status
op_assign
id|qp_data
op_plus
l_int|1
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x0f
comma
l_int|0x390
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x0f
comma
l_int|0x391
)paren
suffix:semicolon
multiline_comment|/* Close config mode */
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_const
r_char
id|msg_banner
(braket
)braket
id|__initdata
op_assign
id|KERN_INFO
l_string|&quot;82C710 type pointing device detected -- driver installed.&bslash;n&quot;
suffix:semicolon
DECL|variable|__initdata
r_static
r_const
r_char
id|msg_nomem
(braket
)braket
id|__initdata
op_assign
id|KERN_ERR
l_string|&quot;qpmouse: no queue memory.&bslash;n&quot;
suffix:semicolon
DECL|function|qpmouse_init_driver
r_static
r_int
id|__init
id|qpmouse_init_driver
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|probe_qp
c_func
(paren
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|printk
c_func
(paren
id|msg_banner
)paren
suffix:semicolon
multiline_comment|/*&t;printk(&quot;82C710 address = %x (should be 0x310)&bslash;n&quot;, qp_data); */
id|queue
op_assign
(paren
r_struct
id|qp_queue
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|queue
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|queue
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|msg_nomem
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|qp_present
op_assign
l_int|1
suffix:semicolon
id|misc_register
c_func
(paren
op_amp
id|qp_mouse
)paren
suffix:semicolon
id|memset
c_func
(paren
id|queue
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|queue
)paren
)paren
suffix:semicolon
id|queue-&gt;head
op_assign
id|queue-&gt;tail
op_assign
l_int|0
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|queue-&gt;proc_list
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|qpmouse_exit_driver
r_static
r_void
id|__exit
id|qpmouse_exit_driver
c_func
(paren
r_void
)paren
(brace
id|misc_deregister
c_func
(paren
op_amp
id|qp_mouse
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|queue
)paren
suffix:semicolon
)brace
DECL|variable|qpmouse_init_driver
id|module_init
c_func
(paren
id|qpmouse_init_driver
)paren
suffix:semicolon
DECL|variable|qpmouse_exit_driver
id|module_exit
c_func
(paren
id|qpmouse_exit_driver
)paren
suffix:semicolon
eof
