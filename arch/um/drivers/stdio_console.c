multiline_comment|/* &n; * Copyright (C) 2000, 2001 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/config.h&quot;
macro_line|#include &quot;linux/posix_types.h&quot;
macro_line|#include &quot;linux/tty.h&quot;
macro_line|#include &quot;linux/tty_flip.h&quot;
macro_line|#include &quot;linux/types.h&quot;
macro_line|#include &quot;linux/major.h&quot;
macro_line|#include &quot;linux/kdev_t.h&quot;
macro_line|#include &quot;linux/console.h&quot;
macro_line|#include &quot;linux/string.h&quot;
macro_line|#include &quot;linux/sched.h&quot;
macro_line|#include &quot;linux/list.h&quot;
macro_line|#include &quot;linux/init.h&quot;
macro_line|#include &quot;linux/interrupt.h&quot;
macro_line|#include &quot;linux/slab.h&quot;
macro_line|#include &quot;asm/current.h&quot;
macro_line|#include &quot;asm/hardirq.h&quot;
macro_line|#include &quot;asm/irq.h&quot;
macro_line|#include &quot;stdio_console.h&quot;
macro_line|#include &quot;line.h&quot;
macro_line|#include &quot;chan_kern.h&quot;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;irq_user.h&quot;
macro_line|#include &quot;mconsole_kern.h&quot;
macro_line|#include &quot;init.h&quot;
macro_line|#include &quot;2_5compat.h&quot;
DECL|macro|MAX_TTYS
mdefine_line|#define MAX_TTYS (8)
multiline_comment|/* Referenced only by tty_driver below - presumably it&squot;s locked correctly&n; * by the tty driver.&n; */
DECL|variable|console_driver
r_static
r_struct
id|tty_driver
op_star
id|console_driver
suffix:semicolon
DECL|variable|init_console_ops
r_static
r_struct
id|chan_ops
id|init_console_ops
op_assign
(brace
dot
id|type
op_assign
l_string|&quot;you shouldn&squot;t see this&quot;
comma
dot
id|init
op_assign
l_int|NULL
comma
dot
id|open
op_assign
l_int|NULL
comma
dot
id|close
op_assign
l_int|NULL
comma
dot
id|read
op_assign
l_int|NULL
comma
dot
id|write
op_assign
l_int|NULL
comma
dot
id|console_write
op_assign
id|generic_write
comma
dot
id|window_size
op_assign
l_int|NULL
comma
dot
id|free
op_assign
l_int|NULL
comma
dot
id|winch
op_assign
l_int|0
comma
)brace
suffix:semicolon
DECL|variable|init_console_chan
r_static
r_struct
id|chan
id|init_console_chan
op_assign
(brace
dot
id|list
op_assign
(brace
)brace
comma
dot
id|primary
op_assign
l_int|1
comma
dot
id|input
op_assign
l_int|0
comma
dot
id|output
op_assign
l_int|1
comma
dot
id|opened
op_assign
l_int|1
comma
dot
id|fd
op_assign
l_int|1
comma
dot
id|pri
op_assign
id|INIT_STATIC
comma
dot
id|ops
op_assign
op_amp
id|init_console_ops
comma
dot
id|data
op_assign
l_int|NULL
)brace
suffix:semicolon
DECL|function|stdio_announce
r_void
id|stdio_announce
c_func
(paren
r_char
op_star
id|dev_name
comma
r_int
id|dev
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Virtual console %d assigned device &squot;%s&squot;&bslash;n&quot;
comma
id|dev
comma
id|dev_name
)paren
suffix:semicolon
)brace
DECL|variable|opts
r_static
r_struct
id|chan_opts
id|opts
op_assign
(brace
dot
id|announce
op_assign
id|stdio_announce
comma
dot
id|xterm_title
op_assign
l_string|&quot;Virtual Console #%d&quot;
comma
dot
id|raw
op_assign
l_int|1
comma
dot
id|tramp_stack
op_assign
l_int|0
comma
dot
id|in_kernel
op_assign
l_int|1
comma
)brace
suffix:semicolon
r_static
r_int
id|con_config
c_func
(paren
r_char
op_star
id|str
)paren
suffix:semicolon
r_static
r_int
id|con_get_config
c_func
(paren
r_char
op_star
id|dev
comma
r_char
op_star
id|str
comma
r_int
id|size
comma
r_char
op_star
op_star
id|error_out
)paren
suffix:semicolon
r_static
r_int
id|con_remove
c_func
(paren
r_char
op_star
id|str
)paren
suffix:semicolon
DECL|variable|driver
r_static
r_struct
id|line_driver
id|driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;UML console&quot;
comma
dot
id|device_name
op_assign
l_string|&quot;tty&quot;
comma
dot
id|devfs_name
op_assign
l_string|&quot;vc/&quot;
comma
dot
id|major
op_assign
id|TTY_MAJOR
comma
dot
id|minor_start
op_assign
l_int|0
comma
dot
id|type
op_assign
id|TTY_DRIVER_TYPE_CONSOLE
comma
dot
id|subtype
op_assign
id|SYSTEM_TYPE_CONSOLE
comma
dot
id|read_irq
op_assign
id|CONSOLE_IRQ
comma
dot
id|read_irq_name
op_assign
l_string|&quot;console&quot;
comma
dot
id|write_irq
op_assign
id|CONSOLE_WRITE_IRQ
comma
dot
id|write_irq_name
op_assign
l_string|&quot;console-write&quot;
comma
dot
id|symlink_from
op_assign
l_string|&quot;ttys&quot;
comma
dot
id|symlink_to
op_assign
l_string|&quot;vc&quot;
comma
dot
id|mc
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;con&quot;
comma
dot
id|config
op_assign
id|con_config
comma
dot
id|get_config
op_assign
id|con_get_config
comma
dot
id|remove
op_assign
id|con_remove
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|console_lines
r_static
r_struct
id|lines
id|console_lines
op_assign
id|LINES_INIT
c_func
(paren
id|MAX_TTYS
)paren
suffix:semicolon
multiline_comment|/* The array is initialized by line_init, which is an initcall.  The &n; * individual elements are protected by individual semaphores.&n; */
DECL|variable|vts
r_struct
id|line
id|vts
(braket
id|MAX_TTYS
)braket
op_assign
(brace
id|LINE_INIT
c_func
(paren
id|CONFIG_CON_ZERO_CHAN
comma
op_amp
id|driver
)paren
comma
(braket
l_int|1
dot
dot
dot
id|MAX_TTYS
op_minus
l_int|1
)braket
op_assign
id|LINE_INIT
c_func
(paren
id|CONFIG_CON_CHAN
comma
op_amp
id|driver
)paren
)brace
suffix:semicolon
DECL|function|con_config
r_static
r_int
id|con_config
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_return
id|line_config
c_func
(paren
id|vts
comma
r_sizeof
(paren
id|vts
)paren
op_div
r_sizeof
(paren
id|vts
(braket
l_int|0
)braket
)paren
comma
id|str
)paren
suffix:semicolon
)brace
DECL|function|con_get_config
r_static
r_int
id|con_get_config
c_func
(paren
r_char
op_star
id|dev
comma
r_char
op_star
id|str
comma
r_int
id|size
comma
r_char
op_star
op_star
id|error_out
)paren
(brace
r_return
id|line_get_config
c_func
(paren
id|dev
comma
id|vts
comma
r_sizeof
(paren
id|vts
)paren
op_div
r_sizeof
(paren
id|vts
(braket
l_int|0
)braket
)paren
comma
id|str
comma
id|size
comma
id|error_out
)paren
suffix:semicolon
)brace
DECL|function|con_remove
r_static
r_int
id|con_remove
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_return
id|line_remove
c_func
(paren
id|vts
comma
r_sizeof
(paren
id|vts
)paren
op_div
r_sizeof
(paren
id|vts
(braket
l_int|0
)braket
)paren
comma
id|str
)paren
suffix:semicolon
)brace
DECL|function|open_console
r_static
r_int
id|open_console
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_return
id|line_open
c_func
(paren
id|vts
comma
id|tty
comma
op_amp
id|opts
)paren
suffix:semicolon
)brace
DECL|function|con_open
r_static
r_int
id|con_open
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
r_return
id|open_console
c_func
(paren
id|tty
)paren
suffix:semicolon
)brace
DECL|function|con_close
r_static
r_void
id|con_close
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
id|line_close
c_func
(paren
id|vts
comma
id|tty
)paren
suffix:semicolon
)brace
DECL|function|con_write
r_static
r_int
id|con_write
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
r_return
id|line_write
c_func
(paren
id|vts
comma
id|tty
comma
id|from_user
comma
id|buf
comma
id|count
)paren
suffix:semicolon
)brace
DECL|function|set_termios
r_static
r_void
id|set_termios
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|termios
op_star
id|old
)paren
(brace
)brace
DECL|function|chars_in_buffer
r_static
r_int
id|chars_in_buffer
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
DECL|variable|con_init_done
r_static
r_int
id|con_init_done
op_assign
l_int|0
suffix:semicolon
DECL|variable|console_ops
r_static
r_struct
id|tty_operations
id|console_ops
op_assign
(brace
dot
id|open
op_assign
id|con_open
comma
dot
id|close
op_assign
id|con_close
comma
dot
id|write
op_assign
id|con_write
comma
dot
id|chars_in_buffer
op_assign
id|chars_in_buffer
comma
dot
id|set_termios
op_assign
id|set_termios
comma
dot
id|write_room
op_assign
id|line_write_room
comma
)brace
suffix:semicolon
DECL|function|stdio_init
r_int
id|stdio_init
c_func
(paren
r_void
)paren
(brace
r_char
op_star
id|new_title
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Initializing stdio console driver&bslash;n&quot;
)paren
suffix:semicolon
id|console_driver
op_assign
id|line_register_devfs
c_func
(paren
op_amp
id|console_lines
comma
op_amp
id|driver
comma
op_amp
id|console_ops
comma
id|vts
comma
r_sizeof
(paren
id|vts
)paren
op_div
r_sizeof
(paren
id|vts
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
id|lines_init
c_func
(paren
id|vts
comma
r_sizeof
(paren
id|vts
)paren
op_div
r_sizeof
(paren
id|vts
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
id|new_title
op_assign
id|add_xterm_umid
c_func
(paren
id|opts.xterm_title
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_title
op_ne
l_int|NULL
)paren
(brace
id|opts.xterm_title
op_assign
id|new_title
suffix:semicolon
)brace
id|open_console
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
id|con_init_done
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|stdio_init
id|late_initcall
c_func
(paren
id|stdio_init
)paren
suffix:semicolon
DECL|function|console_write
r_static
r_void
id|console_write
c_func
(paren
r_struct
id|console
op_star
id|console
comma
r_const
r_char
op_star
id|string
comma
r_int
id|len
)paren
(brace
r_struct
id|line
op_star
id|line
op_assign
op_amp
id|vts
(braket
id|console-&gt;index
)braket
suffix:semicolon
r_if
c_cond
(paren
id|con_init_done
)paren
(brace
id|down
c_func
(paren
op_amp
id|line-&gt;sem
)paren
suffix:semicolon
)brace
id|console_write_chan
c_func
(paren
op_amp
id|line-&gt;chan_list
comma
id|string
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|con_init_done
)paren
(brace
id|up
c_func
(paren
op_amp
id|line-&gt;sem
)paren
suffix:semicolon
)brace
)brace
DECL|function|console_device
r_static
r_struct
id|tty_driver
op_star
id|console_device
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
id|console_driver
suffix:semicolon
)brace
DECL|function|console_setup
r_static
r_int
id|console_setup
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
DECL|variable|stdiocons
r_static
r_struct
id|console
id|stdiocons
op_assign
(brace
id|name
suffix:colon
l_string|&quot;tty&quot;
comma
id|write
suffix:colon
id|console_write
comma
id|device
suffix:colon
id|console_device
comma
id|setup
suffix:colon
id|console_setup
comma
id|flags
suffix:colon
id|CON_PRINTBUFFER
comma
id|index
suffix:colon
op_minus
l_int|1
comma
)brace
suffix:semicolon
DECL|function|stdio_console_init
r_static
r_int
id|__init
id|stdio_console_init
c_func
(paren
r_void
)paren
(brace
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|vts
(braket
l_int|0
)braket
dot
id|chan_list
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|init_console_chan.list
comma
op_amp
id|vts
(braket
l_int|0
)braket
dot
id|chan_list
)paren
suffix:semicolon
id|register_console
c_func
(paren
op_amp
id|stdiocons
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|stdio_console_init
id|console_initcall
c_func
(paren
id|stdio_console_init
)paren
suffix:semicolon
DECL|function|console_chan_setup
r_static
r_int
id|console_chan_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_return
id|line_setup
c_func
(paren
id|vts
comma
r_sizeof
(paren
id|vts
)paren
op_div
r_sizeof
(paren
id|vts
(braket
l_int|0
)braket
)paren
comma
id|str
comma
l_int|1
)paren
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;con&quot;
comma
id|console_chan_setup
)paren
suffix:semicolon
id|__channel_help
c_func
(paren
id|console_chan_setup
comma
l_string|&quot;con&quot;
)paren
suffix:semicolon
DECL|function|console_exit
r_static
r_void
id|console_exit
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|con_init_done
)paren
(brace
r_return
suffix:semicolon
)brace
id|close_lines
c_func
(paren
id|vts
comma
r_sizeof
(paren
id|vts
)paren
op_div
r_sizeof
(paren
id|vts
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
)brace
DECL|variable|console_exit
id|__uml_exitcall
c_func
(paren
id|console_exit
)paren
suffix:semicolon
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
