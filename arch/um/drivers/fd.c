multiline_comment|/* &n; * Copyright (C) 2001 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;termios.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &quot;user.h&quot;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;chan_user.h&quot;
DECL|struct|fd_chan
r_struct
id|fd_chan
(brace
DECL|member|fd
r_int
id|fd
suffix:semicolon
DECL|member|raw
r_int
id|raw
suffix:semicolon
DECL|member|tt
r_struct
id|termios
id|tt
suffix:semicolon
DECL|member|str
r_char
id|str
(braket
r_sizeof
(paren
l_string|&quot;1234567890&bslash;0&quot;
)paren
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|function|fd_init
r_static
r_void
op_star
id|fd_init
c_func
(paren
r_char
op_star
id|str
comma
r_int
id|device
comma
r_struct
id|chan_opts
op_star
id|opts
)paren
(brace
r_struct
id|fd_chan
op_star
id|data
suffix:semicolon
r_char
op_star
id|end
suffix:semicolon
r_int
id|n
suffix:semicolon
r_if
c_cond
(paren
op_star
id|str
op_ne
l_char|&squot;:&squot;
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;fd_init : channel type &squot;fd&squot; must specify a file &quot;
l_string|&quot;descriptor&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|str
op_increment
suffix:semicolon
id|n
op_assign
id|strtoul
c_func
(paren
id|str
comma
op_amp
id|end
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|end
op_ne
l_char|&squot;&bslash;0&squot;
)paren
op_logical_or
(paren
id|end
op_eq
id|str
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;fd_init : couldn&squot;t parse file descriptor &squot;%s&squot;&bslash;n&quot;
comma
id|str
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|data
op_assign
id|um_kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|data
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data
op_eq
l_int|NULL
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
op_star
id|data
op_assign
(paren
(paren
r_struct
id|fd_chan
)paren
(brace
dot
id|fd
op_assign
id|n
comma
dot
id|raw
op_assign
id|opts-&gt;raw
)brace
)paren
suffix:semicolon
r_return
id|data
suffix:semicolon
)brace
DECL|function|fd_open
r_static
r_int
id|fd_open
c_func
(paren
r_int
id|input
comma
r_int
id|output
comma
r_int
id|primary
comma
r_void
op_star
id|d
comma
r_char
op_star
op_star
id|dev_out
)paren
(brace
r_struct
id|fd_chan
op_star
id|data
op_assign
id|d
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;raw
op_logical_and
id|isatty
c_func
(paren
id|data-&gt;fd
)paren
)paren
(brace
id|CATCH_EINTR
c_func
(paren
id|err
op_assign
id|tcgetattr
c_func
(paren
id|data-&gt;fd
comma
op_amp
id|data-&gt;tt
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_return
id|err
suffix:semicolon
)brace
id|err
op_assign
id|raw
c_func
(paren
id|data-&gt;fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_return
id|err
suffix:semicolon
)brace
)brace
id|sprintf
c_func
(paren
id|data-&gt;str
comma
l_string|&quot;%d&quot;
comma
id|data-&gt;fd
)paren
suffix:semicolon
op_star
id|dev_out
op_assign
id|data-&gt;str
suffix:semicolon
r_return
id|data-&gt;fd
suffix:semicolon
)brace
DECL|function|fd_close
r_static
r_void
id|fd_close
c_func
(paren
r_int
id|fd
comma
r_void
op_star
id|d
)paren
(brace
r_struct
id|fd_chan
op_star
id|data
op_assign
id|d
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;raw
op_logical_and
id|isatty
c_func
(paren
id|fd
)paren
)paren
(brace
id|CATCH_EINTR
c_func
(paren
id|err
op_assign
id|tcsetattr
c_func
(paren
id|fd
comma
id|TCSAFLUSH
comma
op_amp
id|data-&gt;tt
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Failed to restore terminal state - &quot;
l_string|&quot;errno = %d&bslash;n&quot;
comma
op_minus
id|err
)paren
suffix:semicolon
)brace
id|data-&gt;raw
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|fd_console_write
r_static
r_int
id|fd_console_write
c_func
(paren
r_int
id|fd
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|n
comma
r_void
op_star
id|d
)paren
(brace
r_struct
id|fd_chan
op_star
id|data
op_assign
id|d
suffix:semicolon
r_return
id|generic_console_write
c_func
(paren
id|fd
comma
id|buf
comma
id|n
comma
op_amp
id|data-&gt;tt
)paren
suffix:semicolon
)brace
DECL|variable|fd_ops
r_struct
id|chan_ops
id|fd_ops
op_assign
(brace
dot
id|type
op_assign
l_string|&quot;fd&quot;
comma
dot
id|init
op_assign
id|fd_init
comma
dot
id|open
op_assign
id|fd_open
comma
dot
id|close
op_assign
id|fd_close
comma
dot
id|read
op_assign
id|generic_read
comma
dot
id|write
op_assign
id|generic_write
comma
dot
id|console_write
op_assign
id|fd_console_write
comma
dot
id|window_size
op_assign
id|generic_window_size
comma
dot
id|free
op_assign
id|generic_free
comma
dot
id|winch
op_assign
l_int|1
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
