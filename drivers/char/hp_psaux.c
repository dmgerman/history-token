multiline_comment|/*&n; *      LASI PS/2 keyboard/psaux driver for HP-PARISC workstations&n; *      &n; *      (c) Copyright 1999 The Puffin Group Inc.&n; *      by Alex deVries &lt;adevries@thepuffingroup.com&gt;&n; *&t;Copyright 1999, 2000 Philipp Rumpf &lt;prumpf@tux.org&gt;&n; *&n; *&t;2000/10/26&t;Debacker Xavier (debackex@esiee.fr)&n; *&t;&t;&t;Marteau Thomas (marteaut@esiee.fr)&n; * &t;&t;&t;Djoudi Malek (djoudim@esiee.fr)&n; *&t;fixed leds control&n; *&t;implemented the psaux and controlled the mouse scancode based on pc_keyb.c&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/keyboard.h&gt;
macro_line|#include &lt;asm/gsc.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;&t;/* interrupt.h wants struct pt_regs defined */
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/sched.h&gt;&t;/* for request_irq/free_irq */
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pc_keyb.h&gt;
macro_line|#include &lt;linux/kbd_kern.h&gt;
multiline_comment|/* mouse includes */
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
multiline_comment|/* HP specific LASI PS/2 keyboard and psaux constants */
DECL|macro|AUX_REPLY_ACK
mdefine_line|#define&t;AUX_REPLY_ACK&t;0xFA&t;/* Command byte ACK. */
DECL|macro|AUX_RECONNECT
mdefine_line|#define&t;AUX_RECONNECT&t;0xAA&t;/* scancode when ps2 device is plugged (back) in */
DECL|macro|LASI_PSAUX_OFFSET
mdefine_line|#define&t;LASI_PSAUX_OFFSET 0x0100 /* offset from keyboard to psaux port */
DECL|macro|LASI_ID
mdefine_line|#define&t;LASI_ID&t;&t;0x00&t;/* ID and reset port offsets */
DECL|macro|LASI_RESET
mdefine_line|#define&t;LASI_RESET&t;0x00
DECL|macro|LASI_RCVDATA
mdefine_line|#define&t;LASI_RCVDATA&t;0x04&t;/* receive and transmit port offsets */
DECL|macro|LASI_XMTDATA
mdefine_line|#define&t;LASI_XMTDATA&t;0x04
DECL|macro|LASI_CONTROL
mdefine_line|#define&t;LASI_CONTROL&t;0x08&t;/* see: control register bits */
DECL|macro|LASI_STATUS
mdefine_line|#define&t;LASI_STATUS&t;0x0C&t;/* see: status register bits */
multiline_comment|/* control register bits */
DECL|macro|LASI_CTRL_ENBL
mdefine_line|#define LASI_CTRL_ENBL&t;0x01&t;/* enable interface */
DECL|macro|LASI_CTRL_LPBXR
mdefine_line|#define LASI_CTRL_LPBXR&t;0x02&t;/* loopback operation */
DECL|macro|LASI_CTRL_DIAG
mdefine_line|#define LASI_CTRL_DIAG&t;0x20&t;/* directly control clock/data line */
DECL|macro|LASI_CTRL_DATDIR
mdefine_line|#define LASI_CTRL_DATDIR 0x40&t;/* data line direct control */
DECL|macro|LASI_CTRL_CLKDIR
mdefine_line|#define LASI_CTRL_CLKDIR 0x80&t;/* clock line direct control */
multiline_comment|/* status register bits */
DECL|macro|LASI_STAT_RBNE
mdefine_line|#define LASI_STAT_RBNE&t;0x01
DECL|macro|LASI_STAT_TBNE
mdefine_line|#define LASI_STAT_TBNE&t;0x02
DECL|macro|LASI_STAT_TERR
mdefine_line|#define LASI_STAT_TERR&t;0x04
DECL|macro|LASI_STAT_PERR
mdefine_line|#define LASI_STAT_PERR&t;0x08
DECL|macro|LASI_STAT_CMPINTR
mdefine_line|#define LASI_STAT_CMPINTR 0x10
DECL|macro|LASI_STAT_DATSHD
mdefine_line|#define LASI_STAT_DATSHD 0x40
DECL|macro|LASI_STAT_CLKSHD
mdefine_line|#define LASI_STAT_CLKSHD 0x80
DECL|variable|lasikbd_hpa
r_static
r_void
op_star
id|lasikbd_hpa
suffix:semicolon
DECL|variable|lasips2_hpa
r_static
r_void
op_star
id|lasips2_hpa
suffix:semicolon
DECL|function|read_input
r_static
r_inline
id|u8
id|read_input
c_func
(paren
r_void
op_star
id|hpa
)paren
(brace
r_return
id|gsc_readb
c_func
(paren
id|hpa
op_plus
id|LASI_RCVDATA
)paren
suffix:semicolon
)brace
DECL|function|read_control
r_static
r_inline
id|u8
id|read_control
c_func
(paren
r_void
op_star
id|hpa
)paren
(brace
r_return
id|gsc_readb
c_func
(paren
id|hpa
op_plus
id|LASI_CONTROL
)paren
suffix:semicolon
)brace
DECL|function|write_control
r_static
r_inline
r_void
id|write_control
c_func
(paren
id|u8
id|val
comma
r_void
op_star
id|hpa
)paren
(brace
id|gsc_writeb
c_func
(paren
id|val
comma
id|hpa
op_plus
id|LASI_CONTROL
)paren
suffix:semicolon
)brace
DECL|function|read_status
r_static
r_inline
id|u8
id|read_status
c_func
(paren
r_void
op_star
id|hpa
)paren
(brace
r_return
id|gsc_readb
c_func
(paren
id|hpa
op_plus
id|LASI_STATUS
)paren
suffix:semicolon
)brace
DECL|function|write_output
r_static
r_int
id|write_output
c_func
(paren
id|u8
id|val
comma
r_void
op_star
id|hpa
)paren
(brace
r_int
id|wait
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|read_status
c_func
(paren
id|hpa
)paren
op_amp
id|LASI_STAT_TBNE
)paren
(brace
id|wait
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|wait
OG
l_int|10000
)paren
(brace
multiline_comment|/* printk(KERN_WARNING &quot;Lasi PS/2 transmit buffer timeout&bslash;n&quot;); */
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|wait
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Lasi PS/2 wait %d&bslash;n&quot;
comma
id|wait
)paren
suffix:semicolon
id|gsc_writeb
c_func
(paren
id|val
comma
id|hpa
op_plus
id|LASI_XMTDATA
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* This function is the PA-RISC adaptation of i386 source */
DECL|function|aux_write_ack
r_static
r_inline
r_int
id|aux_write_ack
c_func
(paren
id|u8
id|val
)paren
(brace
r_return
id|write_output
c_func
(paren
id|val
comma
id|lasikbd_hpa
op_plus
id|LASI_PSAUX_OFFSET
)paren
suffix:semicolon
)brace
DECL|function|lasikbd_leds
r_static
r_void
id|lasikbd_leds
c_func
(paren
r_int
r_char
id|leds
)paren
(brace
id|write_output
c_func
(paren
id|KBD_CMD_SET_LEDS
comma
id|lasikbd_hpa
)paren
suffix:semicolon
id|write_output
c_func
(paren
id|leds
comma
id|lasikbd_hpa
)paren
suffix:semicolon
id|write_output
c_func
(paren
id|KBD_CMD_ENABLE
comma
id|lasikbd_hpa
)paren
suffix:semicolon
)brace
macro_line|#if 0
multiline_comment|/* this might become useful again at some point.  not now  -prumpf */
r_int
id|lasi_ps2_test
c_func
(paren
r_void
op_star
id|hpa
)paren
(brace
id|u8
id|control
comma
id|c
suffix:semicolon
r_int
id|i
comma
id|ret
op_assign
l_int|0
suffix:semicolon
id|control
op_assign
id|read_control
c_func
(paren
id|hpa
)paren
suffix:semicolon
id|write_control
c_func
(paren
id|control
op_or
id|LASI_CTRL_LPBXR
op_or
id|LASI_CTRL_ENBL
comma
id|hpa
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
OL
l_int|256
suffix:semicolon
id|i
op_increment
)paren
(brace
id|write_output
c_func
(paren
id|i
comma
id|hpa
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|read_status
c_func
(paren
id|hpa
)paren
op_amp
id|LASI_STAT_RBNE
)paren
)paren
multiline_comment|/* just wait */
suffix:semicolon
id|c
op_assign
id|read_input
c_func
(paren
id|hpa
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_ne
id|i
)paren
id|ret
op_decrement
suffix:semicolon
)brace
id|write_control
c_func
(paren
id|control
comma
id|hpa
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
macro_line|#endif 
DECL|function|lasi_ps2_reset
r_static
r_int
id|__init
id|lasi_ps2_reset
c_func
(paren
r_void
op_star
id|hpa
comma
r_int
id|id
)paren
(brace
id|u8
id|control
suffix:semicolon
r_int
id|ret
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* reset the interface */
id|gsc_writeb
c_func
(paren
l_int|0xff
comma
id|hpa
op_plus
id|LASI_RESET
)paren
suffix:semicolon
id|gsc_writeb
c_func
(paren
l_int|0x0
comma
id|hpa
op_plus
id|LASI_RESET
)paren
suffix:semicolon
multiline_comment|/* enable it */
id|control
op_assign
id|read_control
c_func
(paren
id|hpa
)paren
suffix:semicolon
id|write_control
c_func
(paren
id|control
op_or
id|LASI_CTRL_ENBL
comma
id|hpa
)paren
suffix:semicolon
multiline_comment|/* initializes the leds at the default state */
r_if
c_cond
(paren
id|id
op_eq
l_int|0
)paren
(brace
id|write_output
c_func
(paren
id|KBD_CMD_SET_LEDS
comma
id|hpa
)paren
suffix:semicolon
id|write_output
c_func
(paren
l_int|0
comma
id|hpa
)paren
suffix:semicolon
id|ret
op_assign
id|write_output
c_func
(paren
id|KBD_CMD_ENABLE
comma
id|hpa
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|inited
r_static
r_int
id|inited
suffix:semicolon
DECL|function|lasi_ps2_init_hw
r_static
r_void
id|lasi_ps2_init_hw
c_func
(paren
r_void
)paren
(brace
op_increment
id|inited
suffix:semicolon
)brace
multiline_comment|/* Greatly inspired by pc_keyb.c */
multiline_comment|/*&n; * Wait for keyboard controller input buffer to drain.&n; *&n; * Don&squot;t use &squot;jiffies&squot; so that we don&squot;t depend on&n; * interrupts..&n; *&n; * Quote from PS/2 System Reference Manual:&n; *&n; * &quot;Address hex 0060 and address hex 0064 should be written only when&n; * the input-buffer-full bit and output-buffer-full bit in the&n; * Controller Status register are set 0.&quot;&n; */
macro_line|#ifdef CONFIG_PSMOUSE
DECL|variable|queue
r_static
r_struct
id|aux_queue
op_star
id|queue
suffix:semicolon
DECL|variable|kbd_controller_lock
r_static
id|spinlock_t
id|kbd_controller_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|mouse_reply_expected
r_static
r_int
r_char
id|mouse_reply_expected
suffix:semicolon
DECL|variable|aux_count
r_static
r_int
id|aux_count
suffix:semicolon
DECL|function|fasync_aux
r_static
r_int
id|fasync_aux
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
DECL|function|handle_mouse_scancode
r_static
r_inline
r_void
id|handle_mouse_scancode
c_func
(paren
r_int
r_char
id|scancode
)paren
(brace
r_if
c_cond
(paren
id|mouse_reply_expected
)paren
(brace
r_if
c_cond
(paren
id|scancode
op_eq
id|AUX_REPLY_ACK
)paren
(brace
id|mouse_reply_expected
op_decrement
suffix:semicolon
r_return
suffix:semicolon
)brace
id|mouse_reply_expected
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|scancode
op_eq
id|AUX_RECONNECT
)paren
(brace
id|queue-&gt;head
op_assign
id|queue-&gt;tail
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Flush input queue */
r_return
suffix:semicolon
)brace
id|add_mouse_randomness
c_func
(paren
id|scancode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|aux_count
)paren
(brace
r_int
id|head
op_assign
id|queue-&gt;head
suffix:semicolon
id|queue-&gt;buf
(braket
id|head
)braket
op_assign
id|scancode
suffix:semicolon
id|head
op_assign
(paren
id|head
op_plus
l_int|1
)paren
op_amp
(paren
id|AUX_BUF_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|head
op_ne
id|queue-&gt;tail
)paren
(brace
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
)brace
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
DECL|function|get_from_queue
r_static
r_int
r_char
id|get_from_queue
c_func
(paren
r_void
)paren
(brace
r_int
r_char
id|result
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|kbd_controller_lock
comma
id|flags
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
id|AUX_BUF_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|kbd_controller_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * Write to the aux device.&n; */
DECL|function|write_aux
r_static
id|ssize_t
id|write_aux
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
id|retval
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
)paren
(brace
id|ssize_t
id|written
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
l_int|32
)paren
id|count
op_assign
l_int|32
suffix:semicolon
multiline_comment|/* Limit to 32 bytes. */
r_do
(brace
r_char
id|c
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
id|written
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|count
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
id|written
)paren
(brace
id|retval
op_assign
id|written
suffix:semicolon
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_mtime
op_assign
id|CURRENT_TIME
suffix:semicolon
)brace
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|function|read_aux
r_static
id|ssize_t
id|read_aux
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
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
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
DECL|function|open_aux
r_static
r_int
id|open_aux
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
r_if
c_cond
(paren
id|aux_count
op_increment
)paren
r_return
l_int|0
suffix:semicolon
id|queue-&gt;head
op_assign
id|queue-&gt;tail
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Flush input queue */
id|aux_count
op_assign
l_int|1
suffix:semicolon
id|aux_write_ack
c_func
(paren
id|AUX_ENABLE_DEV
)paren
suffix:semicolon
multiline_comment|/* Enable aux device */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* No kernel lock held - fine */
DECL|function|aux_poll
r_static
r_int
r_int
id|aux_poll
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
DECL|function|release_aux
r_static
r_int
id|release_aux
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
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|fasync_aux
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
op_decrement
id|aux_count
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
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
DECL|variable|psaux_fops
r_static
r_struct
id|file_operations
id|psaux_fops
op_assign
(brace
id|read
suffix:colon
id|read_aux
comma
id|write
suffix:colon
id|write_aux
comma
id|poll
suffix:colon
id|aux_poll
comma
id|open
suffix:colon
id|open_aux
comma
id|release
suffix:colon
id|release_aux
comma
id|fasync
suffix:colon
id|fasync_aux
comma
)brace
suffix:semicolon
DECL|variable|psaux_mouse
r_static
r_struct
id|miscdevice
id|psaux_mouse
op_assign
(brace
id|minor
suffix:colon
id|PSMOUSE_MINOR
comma
id|name
suffix:colon
l_string|&quot;psaux&quot;
comma
id|fops
suffix:colon
op_amp
id|psaux_fops
comma
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_PSMOUSE */
multiline_comment|/* This function is looking at the PS2 controller and empty the two buffers */
DECL|function|handle_lasikbd_event
r_static
id|u8
id|handle_lasikbd_event
c_func
(paren
r_void
op_star
id|hpa
)paren
(brace
id|u8
id|status_keyb
comma
id|status_mouse
comma
id|scancode
comma
id|id
suffix:semicolon
r_extern
r_void
id|handle_at_scancode
c_func
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/* in drivers/char/keyb_at.c */
multiline_comment|/* Mask to get the base address of the PS/2 controller */
id|id
op_assign
id|gsc_readb
c_func
(paren
id|hpa
op_plus
id|LASI_ID
)paren
op_amp
l_int|0x0f
suffix:semicolon
r_if
c_cond
(paren
id|id
op_eq
l_int|1
)paren
id|hpa
op_sub_assign
id|LASI_PSAUX_OFFSET
suffix:semicolon
id|lasikbd_hpa
op_assign
id|hpa
suffix:semicolon
id|status_keyb
op_assign
id|read_status
c_func
(paren
id|hpa
)paren
suffix:semicolon
id|status_mouse
op_assign
id|read_status
c_func
(paren
id|hpa
op_plus
id|LASI_PSAUX_OFFSET
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|status_keyb
op_or
id|status_mouse
)paren
op_amp
id|LASI_STAT_RBNE
)paren
(brace
r_while
c_loop
(paren
id|status_keyb
op_amp
id|LASI_STAT_RBNE
)paren
(brace
id|scancode
op_assign
id|read_input
c_func
(paren
id|hpa
)paren
suffix:semicolon
multiline_comment|/* XXX don&squot;t know if this is a valid fix, but filtering&n;&t;       * 0xfa avoids &squot;unknown scancode&squot; errors on, eg, capslock&n;&t;       * on some keyboards.&n;&t;       */
r_if
c_cond
(paren
id|inited
op_logical_and
id|scancode
op_ne
l_int|0xfa
)paren
id|handle_at_scancode
c_func
(paren
id|scancode
)paren
suffix:semicolon
id|status_keyb
op_assign
id|read_status
c_func
(paren
id|hpa
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PSMOUSE
r_while
c_loop
(paren
id|status_mouse
op_amp
id|LASI_STAT_RBNE
)paren
(brace
id|scancode
op_assign
id|read_input
c_func
(paren
id|hpa
op_plus
id|LASI_PSAUX_OFFSET
)paren
suffix:semicolon
id|handle_mouse_scancode
c_func
(paren
id|scancode
)paren
suffix:semicolon
id|status_mouse
op_assign
id|read_status
c_func
(paren
id|hpa
op_plus
id|LASI_PSAUX_OFFSET
)paren
suffix:semicolon
)brace
id|status_mouse
op_assign
id|read_status
c_func
(paren
id|hpa
op_plus
id|LASI_PSAUX_OFFSET
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_PSMOUSE */
id|status_keyb
op_assign
id|read_status
c_func
(paren
id|hpa
)paren
suffix:semicolon
)brace
id|tasklet_schedule
c_func
(paren
op_amp
id|keyboard_tasklet
)paren
suffix:semicolon
r_return
(paren
id|status_keyb
op_or
id|status_mouse
)paren
suffix:semicolon
)brace
r_extern
r_struct
id|pt_regs
op_star
id|kbd_pt_regs
suffix:semicolon
DECL|function|lasikbd_interrupt
r_static
r_void
id|lasikbd_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|lasips2_hpa
op_assign
id|dev
suffix:semicolon
multiline_comment|/* save &quot;hpa&quot; for lasikbd_leds() */
id|kbd_pt_regs
op_assign
id|regs
suffix:semicolon
id|handle_lasikbd_event
c_func
(paren
id|lasips2_hpa
)paren
suffix:semicolon
)brace
r_extern
r_int
id|pckbd_translate
c_func
(paren
r_int
r_char
comma
r_int
r_char
op_star
comma
r_char
)paren
suffix:semicolon
DECL|variable|gsc_ps2_kbd_ops
r_static
r_struct
id|kbd_ops
id|gsc_ps2_kbd_ops
op_assign
(brace
id|translate
suffix:colon
id|pckbd_translate
comma
id|init_hw
suffix:colon
id|lasi_ps2_init_hw
comma
id|leds
suffix:colon
id|lasikbd_leds
comma
macro_line|#ifdef CONFIG_MAGIC_SYSRQ
id|sysrq_key
suffix:colon
l_int|0x54
comma
id|sysrq_xlate
suffix:colon
id|hp_ps2kbd_sysrq_xlate
comma
macro_line|#endif
)brace
suffix:semicolon
r_static
r_int
id|__init
DECL|function|lasi_ps2_register
id|lasi_ps2_register
c_func
(paren
r_struct
id|hp_device
op_star
id|d
comma
r_struct
id|pa_iodc_driver
op_star
id|dri
)paren
(brace
r_void
op_star
id|hpa
op_assign
(paren
r_void
op_star
)paren
id|d-&gt;hpa
suffix:semicolon
r_int
r_int
id|irq
suffix:semicolon
r_char
op_star
id|name
suffix:semicolon
r_int
id|device_found
suffix:semicolon
id|u8
id|id
suffix:semicolon
id|id
op_assign
id|gsc_readb
c_func
(paren
id|hpa
op_plus
id|LASI_ID
)paren
op_amp
l_int|0x0f
suffix:semicolon
r_switch
c_cond
(paren
id|id
)paren
(brace
r_case
l_int|0
suffix:colon
id|name
op_assign
l_string|&quot;keyboard&quot;
suffix:semicolon
id|lasikbd_hpa
op_assign
id|hpa
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|name
op_assign
l_string|&quot;psaux&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: Unknown PS/2 port (id=%d) - ignored.&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|id
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* reset the PS/2 port */
id|device_found
op_assign
id|lasi_ps2_reset
c_func
(paren
id|hpa
comma
id|id
)paren
suffix:semicolon
multiline_comment|/* allocate the irq and memory region for that device */
r_if
c_cond
(paren
op_logical_neg
(paren
id|irq
op_assign
id|busdevice_alloc_irq
c_func
(paren
id|d
)paren
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|irq
comma
id|lasikbd_interrupt
comma
l_int|0
comma
id|name
comma
id|hpa
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_mem_region
c_func
(paren
(paren
r_int
r_int
)paren
id|hpa
comma
id|LASI_STATUS
op_plus
l_int|4
comma
id|name
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_switch
c_cond
(paren
id|id
)paren
(brace
r_case
l_int|0
suffix:colon
id|register_kbd_ops
c_func
(paren
op_amp
id|gsc_ps2_kbd_ops
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
macro_line|#ifdef CONFIG_PSMOUSE
id|queue
op_assign
(paren
r_struct
id|aux_queue
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
op_logical_neg
id|queue
)paren
r_return
op_minus
id|ENOMEM
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
id|misc_register
c_func
(paren
op_amp
id|psaux_mouse
)paren
suffix:semicolon
id|aux_write_ack
c_func
(paren
id|AUX_ENABLE_DEV
)paren
suffix:semicolon
multiline_comment|/* try it a second time, this will give status if the device is&n;&t;&t; * available */
id|device_found
op_assign
id|aux_write_ack
c_func
(paren
id|AUX_ENABLE_DEV
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#else
multiline_comment|/* return without printing any unnecessary and misleading info */
r_return
l_int|0
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* of case */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PS/2 %s controller at 0x%08lx (irq %d) found, &quot;
l_string|&quot;%sdevice attached.&bslash;n&quot;
comma
id|name
comma
(paren
r_int
r_int
)paren
id|hpa
comma
id|irq
comma
id|device_found
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;no &quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_struct
id|pa_iodc_driver
id|lasi_psaux_drivers_for
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|HPHW_FIO
comma
l_int|0x0
comma
l_int|0
comma
l_int|0x00084
comma
l_int|0
comma
l_int|0
comma
id|DRIVER_CHECK_HWTYPE
op_plus
id|DRIVER_CHECK_SVERSION
comma
l_string|&quot;Lasi psaux&quot;
comma
l_string|&quot;generic&quot;
comma
(paren
r_void
op_star
)paren
id|lasi_ps2_register
)brace
comma
(brace
l_int|0
comma
)brace
)brace
suffix:semicolon
DECL|function|gsc_ps2_init
r_static
r_int
id|__init
id|gsc_ps2_init
c_func
(paren
r_void
)paren
(brace
r_return
id|pdc_register_driver
c_func
(paren
id|lasi_psaux_drivers_for
)paren
suffix:semicolon
)brace
DECL|variable|gsc_ps2_init
id|module_init
c_func
(paren
id|gsc_ps2_init
)paren
suffix:semicolon
eof
