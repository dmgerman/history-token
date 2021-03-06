multiline_comment|/* &n; * Copyright (C) 2000, 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/config.h&quot;
macro_line|#include &quot;linux/fs.h&quot;
macro_line|#include &quot;linux/tty.h&quot;
macro_line|#include &quot;linux/tty_driver.h&quot;
macro_line|#include &quot;linux/major.h&quot;
macro_line|#include &quot;linux/mm.h&quot;
macro_line|#include &quot;linux/init.h&quot;
macro_line|#include &quot;linux/console.h&quot;
macro_line|#include &quot;asm/termbits.h&quot;
macro_line|#include &quot;asm/irq.h&quot;
macro_line|#include &quot;line.h&quot;
macro_line|#include &quot;ssl.h&quot;
macro_line|#include &quot;chan_kern.h&quot;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;kern.h&quot;
macro_line|#include &quot;init.h&quot;
macro_line|#include &quot;irq_user.h&quot;
macro_line|#include &quot;mconsole_kern.h&quot;
macro_line|#include &quot;2_5compat.h&quot;
DECL|variable|ssl_version
r_static
r_int
id|ssl_version
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Referenced only by tty_driver below - presumably it&squot;s locked correctly&n; * by the tty driver.&n; */
DECL|variable|ssl_driver
r_static
r_struct
id|tty_driver
op_star
id|ssl_driver
suffix:semicolon
DECL|macro|NR_PORTS
mdefine_line|#define NR_PORTS 64
DECL|function|ssl_announce
r_void
id|ssl_announce
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
l_string|&quot;Serial line %d assigned device &squot;%s&squot;&bslash;n&quot;
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
id|ssl_announce
comma
dot
id|xterm_title
op_assign
l_string|&quot;Serial Line #%d&quot;
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
id|ssl_config
c_func
(paren
r_char
op_star
id|str
)paren
suffix:semicolon
r_static
r_int
id|ssl_get_config
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
id|ssl_remove
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
l_string|&quot;UML serial line&quot;
comma
dot
id|device_name
op_assign
l_string|&quot;ttyS&quot;
comma
dot
id|devfs_name
op_assign
l_string|&quot;tts/&quot;
comma
dot
id|major
op_assign
id|TTY_MAJOR
comma
dot
id|minor_start
op_assign
l_int|64
comma
dot
id|type
op_assign
id|TTY_DRIVER_TYPE_SERIAL
comma
dot
id|subtype
op_assign
l_int|0
comma
dot
id|read_irq
op_assign
id|SSL_IRQ
comma
dot
id|read_irq_name
op_assign
l_string|&quot;ssl&quot;
comma
dot
id|write_irq
op_assign
id|SSL_WRITE_IRQ
comma
dot
id|write_irq_name
op_assign
l_string|&quot;ssl-write&quot;
comma
dot
id|symlink_from
op_assign
l_string|&quot;serial&quot;
comma
dot
id|symlink_to
op_assign
l_string|&quot;tts&quot;
comma
dot
id|mc
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;ssl&quot;
comma
dot
id|config
op_assign
id|ssl_config
comma
dot
id|get_config
op_assign
id|ssl_get_config
comma
dot
id|remove
op_assign
id|ssl_remove
comma
)brace
comma
)brace
suffix:semicolon
multiline_comment|/* The array is initialized by line_init, which is an initcall.  The &n; * individual elements are protected by individual semaphores.&n; */
DECL|variable|serial_lines
r_static
r_struct
id|line
id|serial_lines
(braket
id|NR_PORTS
)braket
op_assign
(brace
(braket
l_int|0
dot
dot
dot
id|NR_PORTS
op_minus
l_int|1
)braket
op_assign
id|LINE_INIT
c_func
(paren
id|CONFIG_SSL_CHAN
comma
op_amp
id|driver
)paren
)brace
suffix:semicolon
DECL|variable|lines
r_static
r_struct
id|lines
id|lines
op_assign
id|LINES_INIT
c_func
(paren
id|NR_PORTS
)paren
suffix:semicolon
DECL|function|ssl_config
r_static
r_int
id|ssl_config
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
id|serial_lines
comma
r_sizeof
(paren
id|serial_lines
)paren
op_div
r_sizeof
(paren
id|serial_lines
(braket
l_int|0
)braket
)paren
comma
id|str
)paren
suffix:semicolon
)brace
DECL|function|ssl_get_config
r_static
r_int
id|ssl_get_config
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
id|serial_lines
comma
r_sizeof
(paren
id|serial_lines
)paren
op_div
r_sizeof
(paren
id|serial_lines
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
DECL|function|ssl_remove
r_static
r_int
id|ssl_remove
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
id|serial_lines
comma
r_sizeof
(paren
id|serial_lines
)paren
op_div
r_sizeof
(paren
id|serial_lines
(braket
l_int|0
)braket
)paren
comma
id|str
)paren
suffix:semicolon
)brace
DECL|function|ssl_open
r_int
id|ssl_open
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
id|line_open
c_func
(paren
id|serial_lines
comma
id|tty
comma
op_amp
id|opts
)paren
suffix:semicolon
)brace
macro_line|#if 0
r_static
r_int
id|ssl_chars_in_buffer
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
r_void
id|ssl_flush_buffer
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_return
suffix:semicolon
)brace
r_static
r_void
id|ssl_throttle
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Someone should implement ssl_throttle&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_static
r_void
id|ssl_unthrottle
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Someone should implement ssl_unthrottle&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_static
r_void
id|ssl_stop
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Someone should implement ssl_stop&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_static
r_void
id|ssl_start
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Someone should implement ssl_start&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_void
id|ssl_hangup
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
)brace
macro_line|#endif
DECL|variable|ssl_ops
r_static
r_struct
id|tty_operations
id|ssl_ops
op_assign
(brace
dot
id|open
op_assign
id|ssl_open
comma
dot
id|close
op_assign
id|line_close
comma
dot
id|write
op_assign
id|line_write
comma
dot
id|put_char
op_assign
id|line_put_char
comma
dot
id|write_room
op_assign
id|line_write_room
comma
dot
id|chars_in_buffer
op_assign
id|line_chars_in_buffer
comma
dot
id|set_termios
op_assign
id|line_set_termios
comma
dot
id|ioctl
op_assign
id|line_ioctl
comma
macro_line|#if 0
dot
id|flush_chars
op_assign
id|ssl_flush_chars
comma
dot
id|flush_buffer
op_assign
id|ssl_flush_buffer
comma
dot
id|throttle
op_assign
id|ssl_throttle
comma
dot
id|unthrottle
op_assign
id|ssl_unthrottle
comma
dot
id|stop
op_assign
id|ssl_stop
comma
dot
id|start
op_assign
id|ssl_start
comma
dot
id|hangup
op_assign
id|ssl_hangup
comma
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/* Changed by ssl_init and referenced by ssl_exit, which are both serialized&n; * by being an initcall and exitcall, respectively.&n; */
DECL|variable|ssl_init_done
r_static
r_int
id|ssl_init_done
op_assign
l_int|0
suffix:semicolon
DECL|function|ssl_console_write
r_static
r_void
id|ssl_console_write
c_func
(paren
r_struct
id|console
op_star
id|c
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
id|serial_lines
(braket
id|c-&gt;index
)braket
suffix:semicolon
id|down
c_func
(paren
op_amp
id|line-&gt;sem
)paren
suffix:semicolon
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
id|up
c_func
(paren
op_amp
id|line-&gt;sem
)paren
suffix:semicolon
)brace
DECL|function|ssl_console_device
r_static
r_struct
id|tty_driver
op_star
id|ssl_console_device
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
id|ssl_driver
suffix:semicolon
)brace
DECL|function|ssl_console_setup
r_static
r_int
id|ssl_console_setup
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
r_struct
id|line
op_star
id|line
op_assign
op_amp
id|serial_lines
(braket
id|co-&gt;index
)braket
suffix:semicolon
r_return
id|console_open_chan
c_func
(paren
id|line
comma
id|co
comma
op_amp
id|opts
)paren
suffix:semicolon
)brace
DECL|variable|ssl_cons
r_static
r_struct
id|console
id|ssl_cons
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;ttyS&quot;
comma
dot
id|write
op_assign
id|ssl_console_write
comma
dot
id|device
op_assign
id|ssl_console_device
comma
dot
id|setup
op_assign
id|ssl_console_setup
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
DECL|function|ssl_init
r_int
id|ssl_init
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
l_string|&quot;Initializing software serial port version %d&bslash;n&quot;
comma
id|ssl_version
)paren
suffix:semicolon
id|ssl_driver
op_assign
id|line_register_devfs
c_func
(paren
op_amp
id|lines
comma
op_amp
id|driver
comma
op_amp
id|ssl_ops
comma
id|serial_lines
comma
id|ARRAY_SIZE
c_func
(paren
id|serial_lines
)paren
)paren
suffix:semicolon
id|lines_init
c_func
(paren
id|serial_lines
comma
r_sizeof
(paren
id|serial_lines
)paren
op_div
r_sizeof
(paren
id|serial_lines
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
id|opts.xterm_title
op_assign
id|new_title
suffix:semicolon
id|ssl_init_done
op_assign
l_int|1
suffix:semicolon
id|register_console
c_func
(paren
op_amp
id|ssl_cons
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ssl_init
id|late_initcall
c_func
(paren
id|ssl_init
)paren
suffix:semicolon
DECL|function|ssl_exit
r_static
r_void
id|ssl_exit
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ssl_init_done
)paren
r_return
suffix:semicolon
id|close_lines
c_func
(paren
id|serial_lines
comma
r_sizeof
(paren
id|serial_lines
)paren
op_div
r_sizeof
(paren
id|serial_lines
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
)brace
DECL|variable|ssl_exit
id|__uml_exitcall
c_func
(paren
id|ssl_exit
)paren
suffix:semicolon
DECL|function|ssl_chan_setup
r_static
r_int
id|ssl_chan_setup
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
id|serial_lines
comma
r_sizeof
(paren
id|serial_lines
)paren
op_div
r_sizeof
(paren
id|serial_lines
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
l_string|&quot;ssl&quot;
comma
id|ssl_chan_setup
)paren
suffix:semicolon
id|__channel_help
c_func
(paren
id|ssl_chan_setup
comma
l_string|&quot;ssl&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
