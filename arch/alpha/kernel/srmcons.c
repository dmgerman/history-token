multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/srmcons.c&n; *&n; * Callback based driver for SRM Console console device.&n; * (TTY driver and console driver)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/tty_driver.h&gt;
macro_line|#include &lt;linux/tty_flip.h&gt;
macro_line|#include &lt;asm/console.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|variable|srmcons_callback_lock
r_static
id|spinlock_t
id|srmcons_callback_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|srm_is_registered_console
r_static
r_int
id|srm_is_registered_console
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* &n; * The TTY driver&n; */
DECL|macro|MAX_SRM_CONSOLE_DEVICES
mdefine_line|#define MAX_SRM_CONSOLE_DEVICES 1&t;/* only support 1 console device */
DECL|struct|srmcons_private
r_struct
id|srmcons_private
(brace
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
)brace
suffix:semicolon
DECL|union|_srmcons_result
r_typedef
r_union
id|_srmcons_result
(brace
r_struct
(brace
DECL|member|c
r_int
r_int
id|c
suffix:colon
l_int|61
suffix:semicolon
DECL|member|status
r_int
r_int
id|status
suffix:colon
l_int|3
suffix:semicolon
DECL|member|bits
)brace
id|bits
suffix:semicolon
DECL|member|as_long
r_int
id|as_long
suffix:semicolon
DECL|typedef|srmcons_result
)brace
id|srmcons_result
suffix:semicolon
multiline_comment|/* called with callback_lock held */
r_static
r_int
DECL|function|srmcons_do_receive_chars
id|srmcons_do_receive_chars
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
id|srmcons_result
id|result
suffix:semicolon
r_int
id|count
op_assign
l_int|0
comma
id|loops
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|result.as_long
op_assign
id|callback_getc
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result.bits.status
OL
l_int|2
)paren
(brace
id|tty_insert_flip_char
c_func
(paren
id|tty
comma
(paren
r_char
)paren
id|result.bits.c
comma
l_int|0
)paren
suffix:semicolon
id|count
op_increment
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
(paren
id|result.bits.status
op_amp
l_int|1
)paren
op_logical_and
(paren
op_increment
id|loops
OL
l_int|10
)paren
)paren
(brace
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
)paren
id|tty_schedule_flip
c_func
(paren
id|tty
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
r_static
r_void
DECL|function|srmcons_receive_chars
id|srmcons_receive_chars
c_func
(paren
r_int
r_int
id|data
)paren
(brace
r_struct
id|srmcons_private
op_star
id|srmconsp
op_assign
(paren
r_struct
id|srmcons_private
op_star
)paren
id|data
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|incr
op_assign
l_int|10
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|spin_trylock
c_func
(paren
op_amp
id|srmcons_callback_lock
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|srmcons_do_receive_chars
c_func
(paren
id|srmconsp-&gt;tty
)paren
)paren
id|incr
op_assign
l_int|100
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|srmcons_callback_lock
)paren
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|srmconsp-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|srmconsp-&gt;tty
)paren
(brace
id|srmconsp-&gt;timer.expires
op_assign
id|jiffies
op_plus
id|incr
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|srmconsp-&gt;timer
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|srmconsp-&gt;lock
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* called with callback_lock held */
r_static
r_int
DECL|function|srmcons_do_write
id|srmcons_do_write
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
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
r_int
r_char
op_star
id|str_cr
op_assign
l_string|&quot;&bslash;r&quot;
suffix:semicolon
r_int
id|c
comma
id|remaining
op_assign
id|count
suffix:semicolon
id|srmcons_result
id|result
suffix:semicolon
r_int
r_char
op_star
id|cur
suffix:semicolon
r_int
id|need_cr
suffix:semicolon
r_for
c_loop
(paren
id|cur
op_assign
(paren
r_int
r_char
op_star
)paren
id|buf
suffix:semicolon
id|remaining
OG
l_int|0
suffix:semicolon
)paren
(brace
id|need_cr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* &n;&t;&t; * Break it up into reasonable size chunks to allow a chance&n;&t;&t; * for input to get in&n;&t;&t; */
r_for
c_loop
(paren
id|c
op_assign
l_int|0
suffix:semicolon
id|c
OL
id|min_t
c_func
(paren
r_int
comma
l_int|128L
comma
id|remaining
)paren
op_logical_and
op_logical_neg
id|need_cr
suffix:semicolon
id|c
op_increment
)paren
r_if
c_cond
(paren
id|cur
(braket
id|c
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|need_cr
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|c
OG
l_int|0
)paren
(brace
id|result.as_long
op_assign
id|callback_puts
c_func
(paren
l_int|0
comma
id|cur
comma
id|c
)paren
suffix:semicolon
id|c
op_sub_assign
id|result.bits.c
suffix:semicolon
id|remaining
op_sub_assign
id|result.bits.c
suffix:semicolon
id|cur
op_add_assign
id|result.bits.c
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Check for pending input iff a tty was provided&n;&t;&t;&t; */
r_if
c_cond
(paren
id|tty
)paren
id|srmcons_do_receive_chars
c_func
(paren
id|tty
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|need_cr
)paren
(brace
id|result.as_long
op_assign
id|callback_puts
c_func
(paren
l_int|0
comma
id|str_cr
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result.bits.c
OG
l_int|0
)paren
id|need_cr
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_return
id|count
suffix:semicolon
)brace
r_static
r_int
DECL|function|srmcons_write
id|srmcons_write
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
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|from_user
)paren
(brace
r_int
r_char
id|tmp
(braket
l_int|512
)braket
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
id|c
suffix:semicolon
r_while
c_loop
(paren
(paren
id|c
op_assign
id|count
)paren
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|c
OG
r_sizeof
(paren
id|tmp
)paren
)paren
id|c
op_assign
r_sizeof
(paren
id|tmp
)paren
suffix:semicolon
id|c
op_sub_assign
id|copy_from_user
c_func
(paren
id|tmp
comma
id|buf
comma
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: EFAULT (count %d)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|count
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|srmcons_callback_lock
comma
id|flags
)paren
suffix:semicolon
id|srmcons_do_write
c_func
(paren
id|tty
comma
id|tmp
comma
id|c
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|srmcons_callback_lock
comma
id|flags
)paren
suffix:semicolon
id|buf
op_add_assign
id|c
suffix:semicolon
id|count
op_sub_assign
id|c
suffix:semicolon
id|ret
op_add_assign
id|c
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|srmcons_callback_lock
comma
id|flags
)paren
suffix:semicolon
id|srmcons_do_write
c_func
(paren
id|tty
comma
id|buf
comma
id|count
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|srmcons_callback_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
r_static
r_int
DECL|function|srmcons_write_room
id|srmcons_write_room
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_return
l_int|512
suffix:semicolon
)brace
r_static
r_int
DECL|function|srmcons_chars_in_buffer
id|srmcons_chars_in_buffer
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|srmcons_get_private_struct
id|srmcons_get_private_struct
c_func
(paren
r_struct
id|srmcons_private
op_star
op_star
id|ps
)paren
(brace
r_static
r_struct
id|srmcons_private
op_star
id|srmconsp
op_assign
l_int|NULL
suffix:semicolon
r_static
id|spinlock_t
id|srmconsp_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|srmconsp_lock
comma
id|flags
)paren
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|srmconsp
op_ne
l_int|NULL
)paren
(brace
op_star
id|ps
op_assign
id|srmconsp
suffix:semicolon
r_break
suffix:semicolon
)brace
id|srmconsp
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|srmconsp
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|srmconsp
op_eq
l_int|NULL
)paren
(brace
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_break
suffix:semicolon
)brace
id|srmconsp-&gt;tty
op_assign
l_int|NULL
suffix:semicolon
id|srmconsp-&gt;lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|srmconsp-&gt;timer
)paren
suffix:semicolon
op_star
id|ps
op_assign
id|srmconsp
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|0
)paren
(brace
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|srmconsp_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
r_static
r_int
DECL|function|srmcons_open
id|srmcons_open
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
id|srmcons_private
op_star
id|srmconsp
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|retval
op_assign
id|srmcons_get_private_struct
c_func
(paren
op_amp
id|srmconsp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|srmconsp-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|srmconsp-&gt;tty
)paren
(brace
id|tty-&gt;driver_data
op_assign
id|srmconsp
suffix:semicolon
id|srmconsp-&gt;tty
op_assign
id|tty
suffix:semicolon
id|srmconsp-&gt;timer.function
op_assign
id|srmcons_receive_chars
suffix:semicolon
id|srmconsp-&gt;timer.data
op_assign
(paren
r_int
r_int
)paren
id|srmconsp
suffix:semicolon
id|srmconsp-&gt;timer.expires
op_assign
id|jiffies
op_plus
l_int|10
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|srmconsp-&gt;timer
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|srmconsp-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|srmcons_close
id|srmcons_close
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
id|srmcons_private
op_star
id|srmconsp
op_assign
id|tty-&gt;driver_data
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|srmconsp-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tty-&gt;count
op_eq
l_int|1
)paren
(brace
id|srmconsp-&gt;tty
op_assign
l_int|NULL
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|srmconsp-&gt;timer
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|srmconsp-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|variable|srmcons_driver
r_static
r_struct
id|tty_driver
op_star
id|srmcons_driver
suffix:semicolon
DECL|variable|srmcons_ops
r_static
r_struct
id|tty_operations
id|srmcons_ops
op_assign
(brace
dot
id|open
op_assign
id|srmcons_open
comma
dot
id|close
op_assign
id|srmcons_close
comma
dot
id|write
op_assign
id|srmcons_write
comma
dot
id|write_room
op_assign
id|srmcons_write_room
comma
dot
id|chars_in_buffer
op_assign
id|srmcons_chars_in_buffer
comma
)brace
suffix:semicolon
r_static
r_int
id|__init
DECL|function|srmcons_init
id|srmcons_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|srm_is_registered_console
)paren
(brace
r_struct
id|tty_driver
op_star
id|driver
suffix:semicolon
r_int
id|err
suffix:semicolon
id|driver
op_assign
id|alloc_tty_driver
c_func
(paren
id|MAX_SRM_CONSOLE_DEVICES
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|driver
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|driver-&gt;driver_name
op_assign
l_string|&quot;srm&quot;
suffix:semicolon
id|driver-&gt;name
op_assign
l_string|&quot;srm&quot;
suffix:semicolon
id|driver-&gt;major
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* dynamic */
id|driver-&gt;minor_start
op_assign
l_int|0
suffix:semicolon
id|driver-&gt;type
op_assign
id|TTY_DRIVER_TYPE_SYSTEM
suffix:semicolon
id|driver-&gt;subtype
op_assign
id|SYSTEM_TYPE_SYSCONS
suffix:semicolon
id|driver-&gt;init_termios
op_assign
id|tty_std_termios
suffix:semicolon
id|err
op_assign
id|tty_register_driver
c_func
(paren
id|driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|put_tty_driver
c_func
(paren
id|driver
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|srmcons_driver
op_assign
id|driver
suffix:semicolon
)brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|variable|srmcons_init
id|module_init
c_func
(paren
id|srmcons_init
)paren
suffix:semicolon
"&f;"
multiline_comment|/*&n; * The console driver&n; */
r_static
r_void
DECL|function|srm_console_write
id|srm_console_write
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
id|s
comma
r_int
id|count
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|srmcons_callback_lock
comma
id|flags
)paren
suffix:semicolon
id|srmcons_do_write
c_func
(paren
l_int|NULL
comma
id|s
comma
id|count
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|srmcons_callback_lock
comma
id|flags
)paren
suffix:semicolon
)brace
r_static
r_struct
id|tty_driver
op_star
DECL|function|srm_console_device
id|srm_console_device
c_func
(paren
r_struct
id|console
op_star
id|co
comma
r_int
op_star
id|index
)paren
(brace
op_star
id|index
op_assign
id|co-&gt;index
suffix:semicolon
r_return
id|srmcons_driver
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|srm_console_setup
id|srm_console_setup
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|srmcons
r_static
r_struct
id|console
id|srmcons
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;srm&quot;
comma
dot
id|write
op_assign
id|srm_console_write
comma
dot
id|device
op_assign
id|srm_console_device
comma
dot
id|setup
op_assign
id|srm_console_setup
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
r_void
id|__init
DECL|function|register_srm_console
id|register_srm_console
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|srm_is_registered_console
)paren
(brace
id|callback_open_console
c_func
(paren
)paren
suffix:semicolon
id|register_console
c_func
(paren
op_amp
id|srmcons
)paren
suffix:semicolon
id|srm_is_registered_console
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_void
id|__init
DECL|function|unregister_srm_console
id|unregister_srm_console
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|srm_is_registered_console
)paren
(brace
id|callback_close_console
c_func
(paren
)paren
suffix:semicolon
id|unregister_console
c_func
(paren
op_amp
id|srmcons
)paren
suffix:semicolon
id|srm_is_registered_console
op_assign
l_int|0
suffix:semicolon
)brace
)brace
eof
