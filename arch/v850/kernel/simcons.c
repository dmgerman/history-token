multiline_comment|/*&n; * arch/v850/kernel/simcons.c -- Console I/O for GDB v850e simulator&n; *&n; *  Copyright (C) 2001,02,03  NEC Electronics Corporation&n; *  Copyright (C) 2001,02,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/tty_flip.h&gt;
macro_line|#include &lt;linux/tty_driver.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/poll.h&gt;
macro_line|#include &lt;asm/string.h&gt;
macro_line|#include &lt;asm/simsyscall.h&gt;
"&f;"
multiline_comment|/*  Low-level console. */
DECL|function|simcons_write
r_static
r_void
id|simcons_write
(paren
r_struct
id|console
op_star
id|co
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|len
)paren
(brace
id|V850_SIM_SYSCALL
(paren
id|write
comma
l_int|1
comma
id|buf
comma
id|len
)paren
suffix:semicolon
)brace
DECL|function|simcons_read
r_static
r_int
id|simcons_read
(paren
r_struct
id|console
op_star
id|co
comma
r_char
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_return
id|V850_SIM_SYSCALL
(paren
id|read
comma
l_int|0
comma
id|buf
comma
id|len
)paren
suffix:semicolon
)brace
DECL|variable|tty_driver
r_static
r_struct
id|tty_driver
op_star
id|tty_driver
suffix:semicolon
DECL|function|simcons_device
r_static
r_struct
id|tty_driver
op_star
id|simcons_device
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
id|tty_driver
suffix:semicolon
)brace
DECL|variable|simcons
r_static
r_struct
id|console
id|simcons
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;simcons&quot;
comma
dot
id|write
op_assign
id|simcons_write
comma
dot
id|read
op_assign
id|simcons_read
comma
dot
id|device
op_assign
id|simcons_device
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
"&f;"
multiline_comment|/* Higher level TTY interface.  */
DECL|function|simcons_tty_open
r_int
id|simcons_tty_open
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|simcons_tty_write
r_int
id|simcons_tty_write
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
r_return
id|V850_SIM_SYSCALL
(paren
id|write
comma
l_int|1
comma
id|buf
comma
id|count
)paren
suffix:semicolon
)brace
DECL|function|simcons_tty_write_room
r_int
id|simcons_tty_write_room
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
multiline_comment|/* Completely arbitrary.  */
r_return
l_int|0x100000
suffix:semicolon
)brace
DECL|function|simcons_tty_chars_in_buffer
r_int
id|simcons_tty_chars_in_buffer
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
multiline_comment|/* We have no buffer.  */
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ops
r_static
r_struct
id|tty_operations
id|ops
op_assign
(brace
dot
id|open
op_assign
id|simcons_tty_open
comma
dot
id|write
op_assign
id|simcons_tty_write
comma
dot
id|write_room
op_assign
id|simcons_tty_write_room
comma
dot
id|chars_in_buffer
op_assign
id|simcons_tty_chars_in_buffer
comma
)brace
suffix:semicolon
DECL|function|simcons_tty_init
r_int
id|__init
id|simcons_tty_init
(paren
r_void
)paren
(brace
r_struct
id|tty_driver
op_star
id|driver
op_assign
id|alloc_tty_driver
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_int
id|err
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
id|driver-&gt;name
op_assign
l_string|&quot;simcons&quot;
suffix:semicolon
id|driver-&gt;major
op_assign
id|TTY_MAJOR
suffix:semicolon
id|driver-&gt;minor_start
op_assign
l_int|64
suffix:semicolon
id|driver-&gt;type
op_assign
id|TTY_DRIVER_TYPE_SYSCONS
suffix:semicolon
id|driver-&gt;init_termios
op_assign
id|tty_std_termios
suffix:semicolon
id|tty_set_operations
c_func
(paren
id|driver
comma
op_amp
id|ops
)paren
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
id|tty_driver
op_assign
id|driver
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* We use `late_initcall&squot; instead of just `__initcall&squot; as a workaround for&n;   the fact that (1) simcons_tty_init can&squot;t be called before tty_init,&n;   (2) tty_init is called via `module_init&squot;, (3) if statically linked,&n;   module_init == device_init, and (4) there&squot;s no ordering of init lists.&n;   We can do this easily because simcons is always statically linked, but&n;   other tty drivers that depend on tty_init and which must use&n;   `module_init&squot; to declare their init routines are likely to be broken.  */
DECL|variable|simcons_tty_init
id|late_initcall
c_func
(paren
id|simcons_tty_init
)paren
suffix:semicolon
"&f;"
multiline_comment|/* Poll for input on the console, and if there&squot;s any, deliver it to the&n;   tty driver.  */
DECL|function|simcons_poll_tty
r_void
id|simcons_poll_tty
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_int
id|flip
op_assign
l_int|0
comma
id|send_break
op_assign
l_int|0
suffix:semicolon
r_struct
id|pollfd
id|pfd
suffix:semicolon
id|pfd.fd
op_assign
l_int|0
suffix:semicolon
id|pfd.events
op_assign
id|POLLIN
suffix:semicolon
r_if
c_cond
(paren
id|V850_SIM_SYSCALL
(paren
id|poll
comma
op_amp
id|pfd
comma
l_int|1
comma
l_int|0
)paren
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|pfd.revents
op_amp
id|POLLIN
)paren
(brace
r_int
id|left
op_assign
id|TTY_FLIPBUF_SIZE
op_minus
id|tty-&gt;flip.count
suffix:semicolon
r_if
c_cond
(paren
id|left
OG
l_int|0
)paren
(brace
r_int
r_char
op_star
id|buf
op_assign
id|tty-&gt;flip.char_buf_ptr
suffix:semicolon
r_int
id|rd
op_assign
id|V850_SIM_SYSCALL
(paren
id|read
comma
l_int|0
comma
id|buf
comma
id|left
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rd
OG
l_int|0
)paren
(brace
id|tty-&gt;flip.count
op_add_assign
id|rd
suffix:semicolon
id|tty-&gt;flip.char_buf_ptr
op_add_assign
id|rd
suffix:semicolon
id|memset
(paren
id|tty-&gt;flip.flag_buf_ptr
comma
l_int|0
comma
id|rd
)paren
suffix:semicolon
id|tty-&gt;flip.flag_buf_ptr
op_add_assign
id|rd
suffix:semicolon
id|flip
op_assign
l_int|1
suffix:semicolon
)brace
r_else
id|send_break
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|pfd.revents
op_amp
id|POLLERR
)paren
id|send_break
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|send_break
)paren
(brace
id|tty_insert_flip_char
(paren
id|tty
comma
l_int|0
comma
id|TTY_BREAK
)paren
suffix:semicolon
id|flip
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flip
)paren
id|tty_schedule_flip
(paren
id|tty
)paren
suffix:semicolon
)brace
DECL|function|simcons_poll_ttys
r_void
id|simcons_poll_ttys
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|tty_driver
op_logical_and
id|tty_driver-&gt;ttys
(braket
l_int|0
)braket
)paren
id|simcons_poll_tty
(paren
id|tty_driver-&gt;ttys
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
"&f;"
DECL|function|simcons_setup
r_void
id|simcons_setup
(paren
r_void
)paren
(brace
id|V850_SIM_SYSCALL
(paren
id|make_raw
comma
l_int|0
)paren
suffix:semicolon
id|register_console
(paren
op_amp
id|simcons
)paren
suffix:semicolon
id|printk
(paren
id|KERN_INFO
l_string|&quot;Console: GDB V850E simulator stdio&bslash;n&quot;
)paren
suffix:semicolon
)brace
eof
