multiline_comment|/*&n; * Copyright (C) 2001 Anton Blanchard &lt;anton@au.ibm.com&gt;, IBM&n; * Copyright (C) 2001 Paul Mackerras &lt;paulus@au.ibm.com&gt;, IBM&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sysrq.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/tty_flip.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kbd_kern.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
r_extern
r_int
id|hvc_count
c_func
(paren
r_int
op_star
)paren
suffix:semicolon
r_extern
r_int
id|hvc_get_chars
c_func
(paren
r_int
id|index
comma
r_char
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
r_extern
r_int
id|hvc_put_chars
c_func
(paren
r_int
id|index
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
DECL|macro|HVC_MAJOR
mdefine_line|#define HVC_MAJOR&t;229
DECL|macro|HVC_MINOR
mdefine_line|#define HVC_MINOR&t;0
DECL|macro|MAX_NR_HVC_CONSOLES
mdefine_line|#define MAX_NR_HVC_CONSOLES&t;4
DECL|macro|TIMEOUT
mdefine_line|#define TIMEOUT&t;&t;((HZ + 99) / 100)
DECL|variable|hvc_driver
r_static
r_struct
id|tty_driver
op_star
id|hvc_driver
suffix:semicolon
DECL|variable|hvc_offset
r_static
r_int
id|hvc_offset
suffix:semicolon
macro_line|#ifdef CONFIG_MAGIC_SYSRQ
DECL|variable|sysrq_pressed
r_static
r_int
id|sysrq_pressed
suffix:semicolon
macro_line|#endif
DECL|macro|N_OUTBUF
mdefine_line|#define N_OUTBUF&t;16
DECL|macro|__ALIGNED__
mdefine_line|#define __ALIGNED__&t;__attribute__((__aligned__(8)))
DECL|struct|hvc_struct
r_struct
id|hvc_struct
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|index
r_int
id|index
suffix:semicolon
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
DECL|member|do_wakeup
r_int
id|do_wakeup
suffix:semicolon
DECL|member|__ALIGNED__
r_char
id|outbuf
(braket
id|N_OUTBUF
)braket
id|__ALIGNED__
suffix:semicolon
DECL|member|n_outbuf
r_int
id|n_outbuf
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|hvc_struct
r_struct
id|hvc_struct
id|hvc_struct
(braket
id|MAX_NR_HVC_CONSOLES
)braket
suffix:semicolon
DECL|function|hvc_open
r_static
r_int
id|hvc_open
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
r_int
id|line
op_assign
id|tty-&gt;index
suffix:semicolon
r_struct
id|hvc_struct
op_star
id|hp
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|line
OL
l_int|0
op_logical_or
id|line
op_ge
id|MAX_NR_HVC_CONSOLES
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|hp
op_assign
op_amp
id|hvc_struct
(braket
id|line
)braket
suffix:semicolon
id|tty-&gt;driver_data
op_assign
id|hp
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|hp-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|hp-&gt;tty
op_assign
id|tty
suffix:semicolon
id|hp-&gt;count
op_increment
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|hp-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hvc_close
r_static
r_void
id|hvc_close
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
r_struct
id|hvc_struct
op_star
id|hp
op_assign
id|tty-&gt;driver_data
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|tty_hung_up_p
c_func
(paren
id|filp
)paren
)paren
r_return
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|hp-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|hp-&gt;count
op_eq
l_int|0
)paren
id|hp-&gt;tty
op_assign
l_int|NULL
suffix:semicolon
r_else
r_if
c_cond
(paren
id|hp-&gt;count
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;hvc_close %lu: oops, count is %d&bslash;n&quot;
comma
id|hp
op_minus
id|hvc_struct
comma
id|hp-&gt;count
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|hp-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|hvc_hangup
r_static
r_void
id|hvc_hangup
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_struct
id|hvc_struct
op_star
id|hp
op_assign
id|tty-&gt;driver_data
suffix:semicolon
id|hp-&gt;count
op_assign
l_int|0
suffix:semicolon
id|hp-&gt;tty
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* called with hp-&gt;lock held */
DECL|function|hvc_push
r_static
r_void
id|hvc_push
c_func
(paren
r_struct
id|hvc_struct
op_star
id|hp
)paren
(brace
r_int
id|n
suffix:semicolon
id|n
op_assign
id|hvc_put_chars
c_func
(paren
id|hp-&gt;index
op_plus
id|hvc_offset
comma
id|hp-&gt;outbuf
comma
id|hp-&gt;n_outbuf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_le
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|n
op_eq
l_int|0
)paren
r_return
suffix:semicolon
multiline_comment|/* throw away output on error; this happens when&n;&t;&t;   there is no session connected to the vterm. */
id|hp-&gt;n_outbuf
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|hp-&gt;n_outbuf
op_sub_assign
id|n
suffix:semicolon
r_if
c_cond
(paren
id|hp-&gt;n_outbuf
OG
l_int|0
)paren
id|memmove
c_func
(paren
id|hp-&gt;outbuf
comma
id|hp-&gt;outbuf
op_plus
id|n
comma
id|hp-&gt;n_outbuf
)paren
suffix:semicolon
r_else
id|hp-&gt;do_wakeup
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|hvc_write
r_static
r_int
id|hvc_write
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_int
id|from_user
comma
r_const
r_int
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_struct
id|hvc_struct
op_star
id|hp
op_assign
id|tty-&gt;driver_data
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
r_int
id|todo
comma
id|written
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|hp-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
OG
l_int|0
op_logical_and
(paren
id|todo
op_assign
id|N_OUTBUF
op_minus
id|hp-&gt;n_outbuf
)paren
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|todo
OG
id|count
)paren
id|todo
op_assign
id|count
suffix:semicolon
id|p
op_assign
id|hp-&gt;outbuf
op_plus
id|hp-&gt;n_outbuf
suffix:semicolon
r_if
c_cond
(paren
id|from_user
)paren
(brace
id|todo
op_sub_assign
id|copy_from_user
c_func
(paren
id|p
comma
id|buf
comma
id|todo
)paren
suffix:semicolon
r_if
c_cond
(paren
id|todo
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|written
op_eq
l_int|0
)paren
id|written
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
id|memcpy
c_func
(paren
id|p
comma
id|buf
comma
id|todo
)paren
suffix:semicolon
id|count
op_sub_assign
id|todo
suffix:semicolon
id|buf
op_add_assign
id|todo
suffix:semicolon
id|hp-&gt;n_outbuf
op_add_assign
id|todo
suffix:semicolon
id|written
op_add_assign
id|todo
suffix:semicolon
id|hvc_push
c_func
(paren
id|hp
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|hp-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|written
suffix:semicolon
)brace
DECL|function|hvc_write_room
r_static
r_int
id|hvc_write_room
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_struct
id|hvc_struct
op_star
id|hp
op_assign
id|tty-&gt;driver_data
suffix:semicolon
r_return
id|N_OUTBUF
op_minus
id|hp-&gt;n_outbuf
suffix:semicolon
)brace
DECL|function|hvc_chars_in_buffer
r_static
r_int
id|hvc_chars_in_buffer
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_struct
id|hvc_struct
op_star
id|hp
op_assign
id|tty-&gt;driver_data
suffix:semicolon
r_return
id|hp-&gt;n_outbuf
suffix:semicolon
)brace
DECL|function|hvc_poll
r_static
r_void
id|hvc_poll
c_func
(paren
r_int
id|index
)paren
(brace
r_struct
id|hvc_struct
op_star
id|hp
op_assign
op_amp
id|hvc_struct
(braket
id|index
)braket
suffix:semicolon
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
r_int
id|i
comma
id|n
suffix:semicolon
r_char
id|buf
(braket
l_int|16
)braket
id|__ALIGNED__
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|hp-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hp-&gt;n_outbuf
OG
l_int|0
)paren
id|hvc_push
c_func
(paren
id|hp
)paren
suffix:semicolon
id|tty
op_assign
id|hp-&gt;tty
suffix:semicolon
r_if
c_cond
(paren
id|tty
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|TTY_FLIPBUF_SIZE
op_minus
id|tty-&gt;flip.count
OL
r_sizeof
(paren
id|buf
)paren
)paren
r_break
suffix:semicolon
id|n
op_assign
id|hvc_get_chars
c_func
(paren
id|index
op_plus
id|hvc_offset
comma
id|buf
comma
r_sizeof
(paren
id|buf
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_le
l_int|0
)paren
r_break
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
id|n
suffix:semicolon
op_increment
id|i
)paren
(brace
macro_line|#ifdef CONFIG_MAGIC_SYSRQ&t;&t;/* Handle the SysRq Hack */
r_if
c_cond
(paren
id|buf
(braket
id|i
)braket
op_eq
l_char|&squot;&bslash;x0f&squot;
)paren
(brace
multiline_comment|/* ^O -- should support a sequence */
id|sysrq_pressed
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|sysrq_pressed
)paren
(brace
id|handle_sysrq
c_func
(paren
id|buf
(braket
id|i
)braket
comma
l_int|NULL
comma
id|tty
)paren
suffix:semicolon
id|sysrq_pressed
op_assign
l_int|0
suffix:semicolon
r_continue
suffix:semicolon
)brace
macro_line|#endif
id|tty_insert_flip_char
c_func
(paren
id|tty
comma
id|buf
(braket
id|i
)braket
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|tty-&gt;flip.count
)paren
id|tty_schedule_flip
c_func
(paren
id|tty
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hp-&gt;do_wakeup
)paren
(brace
id|hp-&gt;do_wakeup
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tty-&gt;flags
op_amp
(paren
l_int|1
op_lshift
id|TTY_DO_WRITE_WAKEUP
)paren
)paren
op_logical_and
id|tty-&gt;ldisc.write_wakeup
)paren
(paren
id|tty-&gt;ldisc.write_wakeup
)paren
(paren
id|tty
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|tty-&gt;write_wait
)paren
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|hp-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
macro_line|#if defined (CONFIG_XMON)
r_extern
r_int
r_int
id|cpus_in_xmon
suffix:semicolon
macro_line|#else
DECL|variable|cpus_in_xmon
r_int
r_int
id|cpus_in_xmon
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
DECL|function|khvcd
r_int
id|khvcd
c_func
(paren
r_void
op_star
id|unused
)paren
(brace
r_int
id|i
suffix:semicolon
id|daemonize
c_func
(paren
l_string|&quot;khvcd&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|cpus_in_xmon
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
id|MAX_NR_HVC_CONSOLES
suffix:semicolon
op_increment
id|i
)paren
id|hvc_poll
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|TIMEOUT
)paren
suffix:semicolon
)brace
)brace
DECL|variable|hvc_ops
r_static
r_struct
id|tty_operations
id|hvc_ops
op_assign
(brace
dot
id|open
op_assign
id|hvc_open
comma
dot
id|close
op_assign
id|hvc_close
comma
dot
id|write
op_assign
id|hvc_write
comma
dot
id|hangup
op_assign
id|hvc_hangup
comma
dot
id|write_room
op_assign
id|hvc_write_room
comma
dot
id|chars_in_buffer
op_assign
id|hvc_chars_in_buffer
comma
)brace
suffix:semicolon
DECL|function|hvc_init
r_int
id|__init
id|hvc_init
c_func
(paren
r_void
)paren
(brace
r_int
id|num
op_assign
id|hvc_count
c_func
(paren
op_amp
id|hvc_offset
)paren
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|num
OG
id|MAX_NR_HVC_CONSOLES
)paren
id|num
op_assign
id|MAX_NR_HVC_CONSOLES
suffix:semicolon
id|hvc_driver
op_assign
id|alloc_tty_driver
c_func
(paren
id|num
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hvc_driver
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|hvc_driver-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|hvc_driver-&gt;driver_name
op_assign
l_string|&quot;hvc&quot;
suffix:semicolon
id|hvc_driver-&gt;name
op_assign
l_string|&quot;hvc/&quot;
suffix:semicolon
id|hvc_driver-&gt;major
op_assign
id|HVC_MAJOR
suffix:semicolon
id|hvc_driver-&gt;minor_start
op_assign
id|HVC_MINOR
suffix:semicolon
id|hvc_driver-&gt;type
op_assign
id|TTY_DRIVER_TYPE_SYSTEM
suffix:semicolon
id|hvc_driver-&gt;init_termios
op_assign
id|tty_std_termios
suffix:semicolon
id|hvc_driver-&gt;flags
op_assign
id|TTY_DRIVER_REAL_RAW
suffix:semicolon
id|tty_set_operations
c_func
(paren
id|hvc_driver
comma
op_amp
id|hvc_ops
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
id|num
suffix:semicolon
id|i
op_increment
)paren
(brace
id|hvc_struct
(braket
id|i
)braket
dot
id|lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
id|hvc_struct
(braket
id|i
)braket
dot
id|index
op_assign
id|i
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tty_register_driver
c_func
(paren
id|hvc_driver
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;Couldn&squot;t register hvc console driver&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|num
OG
l_int|0
)paren
id|kernel_thread
c_func
(paren
id|khvcd
comma
l_int|NULL
comma
id|CLONE_KERNEL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hvc_exit
r_static
r_void
id|__exit
id|hvc_exit
c_func
(paren
r_void
)paren
(brace
)brace
DECL|function|hvc_console_print
r_void
id|hvc_console_print
c_func
(paren
r_struct
id|console
op_star
id|co
comma
r_const
r_char
op_star
id|b
comma
r_int
id|count
)paren
(brace
r_char
id|c
(braket
l_int|16
)braket
id|__ALIGNED__
suffix:semicolon
r_int
id|i
comma
id|n
suffix:semicolon
r_int
id|r
comma
id|donecr
op_assign
l_int|0
suffix:semicolon
id|i
op_assign
id|n
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|count
OG
l_int|0
op_logical_or
id|i
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|count
OG
l_int|0
op_logical_and
id|i
OL
r_sizeof
(paren
id|c
)paren
)paren
(brace
r_if
c_cond
(paren
id|b
(braket
id|n
)braket
op_eq
l_char|&squot;&bslash;n&squot;
op_logical_and
op_logical_neg
id|donecr
)paren
(brace
id|c
(braket
id|i
op_increment
)braket
op_assign
l_char|&squot;&bslash;r&squot;
suffix:semicolon
id|donecr
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|c
(braket
id|i
op_increment
)braket
op_assign
id|b
(braket
id|n
op_increment
)braket
suffix:semicolon
id|donecr
op_assign
l_int|0
suffix:semicolon
op_decrement
id|count
suffix:semicolon
)brace
)brace
r_else
(brace
id|r
op_assign
id|hvc_put_chars
c_func
(paren
id|co-&gt;index
op_plus
id|hvc_offset
comma
id|c
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
OL
l_int|0
)paren
(brace
multiline_comment|/* throw away chars on error */
id|i
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|r
OG
l_int|0
)paren
(brace
id|i
op_sub_assign
id|r
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
l_int|0
)paren
id|memmove
c_func
(paren
id|c
comma
id|c
op_plus
id|r
comma
id|i
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
DECL|function|hvc_console_device
r_static
r_struct
id|tty_driver
op_star
id|hvc_console_device
c_func
(paren
r_struct
id|console
op_star
id|c
comma
r_int
op_star
id|index
)paren
(brace
op_star
id|index
op_assign
id|c-&gt;index
suffix:semicolon
r_return
id|hvc_driver
suffix:semicolon
)brace
DECL|function|hvc_console_setup
r_static
r_int
id|__init
id|hvc_console_setup
c_func
(paren
r_struct
id|console
op_star
id|co
comma
r_char
op_star
id|options
)paren
(brace
r_if
c_cond
(paren
id|co-&gt;index
OL
l_int|0
op_logical_or
id|co-&gt;index
op_ge
id|MAX_NR_HVC_CONSOLES
op_logical_or
id|co-&gt;index
op_ge
id|hvc_count
c_func
(paren
op_amp
id|hvc_offset
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|hvc_con_driver
r_struct
id|console
id|hvc_con_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;hvc&quot;
comma
dot
id|write
op_assign
id|hvc_console_print
comma
dot
id|device
op_assign
id|hvc_console_device
comma
dot
id|setup
op_assign
id|hvc_console_setup
comma
dot
id|flags
op_assign
id|CON_PRINTBUFFER
comma
dot
id|index
op_assign
op_minus
l_int|1
comma
)brace
suffix:semicolon
DECL|function|hvc_console_init
r_static
r_int
id|__init
id|hvc_console_init
c_func
(paren
r_void
)paren
(brace
id|register_console
c_func
(paren
op_amp
id|hvc_con_driver
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|hvc_console_init
id|console_initcall
c_func
(paren
id|hvc_console_init
)paren
suffix:semicolon
DECL|variable|hvc_init
id|module_init
c_func
(paren
id|hvc_init
)paren
suffix:semicolon
DECL|variable|hvc_exit
id|module_exit
c_func
(paren
id|hvc_exit
)paren
suffix:semicolon
eof
