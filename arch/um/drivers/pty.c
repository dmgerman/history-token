multiline_comment|/* &n; * Copyright (C) 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;termios.h&gt;
macro_line|#include &quot;chan_user.h&quot;
macro_line|#include &quot;user.h&quot;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;os.h&quot;
DECL|struct|pty_chan
r_struct
id|pty_chan
(brace
DECL|member|announce
r_void
(paren
op_star
id|announce
)paren
(paren
r_char
op_star
id|dev_name
comma
r_int
id|dev
)paren
suffix:semicolon
DECL|member|dev
r_int
id|dev
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
DECL|member|dev_name
r_char
id|dev_name
(braket
r_sizeof
(paren
l_string|&quot;/dev/pts/0123456&bslash;0&quot;
)paren
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|function|pty_chan_init
r_static
r_void
op_star
id|pty_chan_init
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
id|pty_chan
op_star
id|data
suffix:semicolon
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
id|pty_chan
)paren
(brace
dot
id|announce
op_assign
id|opts-&gt;announce
comma
dot
id|dev
op_assign
id|device
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
DECL|function|pts_open
r_static
r_int
id|pts_open
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
id|pty_chan
op_star
id|data
op_assign
id|d
suffix:semicolon
r_char
op_star
id|dev
suffix:semicolon
r_int
id|fd
comma
id|err
suffix:semicolon
id|fd
op_assign
id|get_pty
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;open_pts : Failed to open pts&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|errno
suffix:semicolon
)brace
r_if
c_cond
(paren
id|data-&gt;raw
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
id|fd
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
id|fd
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
id|dev
op_assign
id|ptsname
c_func
(paren
id|fd
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|data-&gt;dev_name
comma
l_string|&quot;%s&quot;
comma
id|dev
)paren
suffix:semicolon
op_star
id|dev_out
op_assign
id|data-&gt;dev_name
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;announce
)paren
(paren
op_star
id|data-&gt;announce
)paren
(paren
id|dev
comma
id|data-&gt;dev
)paren
suffix:semicolon
r_return
id|fd
suffix:semicolon
)brace
DECL|function|getmaster
r_static
r_int
id|getmaster
c_func
(paren
r_char
op_star
id|line
)paren
(brace
r_char
op_star
id|pty
comma
op_star
id|bank
comma
op_star
id|cp
suffix:semicolon
r_int
id|master
comma
id|err
suffix:semicolon
id|pty
op_assign
op_amp
id|line
(braket
id|strlen
c_func
(paren
l_string|&quot;/dev/ptyp&quot;
)paren
)braket
suffix:semicolon
r_for
c_loop
(paren
id|bank
op_assign
l_string|&quot;pqrs&quot;
suffix:semicolon
op_star
id|bank
suffix:semicolon
id|bank
op_increment
)paren
(brace
id|line
(braket
id|strlen
c_func
(paren
l_string|&quot;/dev/pty&quot;
)paren
)braket
op_assign
op_star
id|bank
suffix:semicolon
op_star
id|pty
op_assign
l_char|&squot;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|os_stat_file
c_func
(paren
id|line
comma
l_int|NULL
)paren
OL
l_int|0
)paren
r_break
suffix:semicolon
r_for
c_loop
(paren
id|cp
op_assign
l_string|&quot;0123456789abcdef&quot;
suffix:semicolon
op_star
id|cp
suffix:semicolon
id|cp
op_increment
)paren
(brace
op_star
id|pty
op_assign
op_star
id|cp
suffix:semicolon
id|master
op_assign
id|os_open_file
c_func
(paren
id|line
comma
id|of_rdwr
c_func
(paren
id|OPENFLAGS
c_func
(paren
)paren
)paren
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|master
op_ge
l_int|0
)paren
(brace
r_char
op_star
id|tp
op_assign
op_amp
id|line
(braket
id|strlen
c_func
(paren
l_string|&quot;/dev/&quot;
)paren
)braket
suffix:semicolon
multiline_comment|/* verify slave side is usable */
op_star
id|tp
op_assign
l_char|&squot;t&squot;
suffix:semicolon
id|err
op_assign
id|os_access
c_func
(paren
id|line
comma
id|OS_ACC_RW_OK
)paren
suffix:semicolon
op_star
id|tp
op_assign
l_char|&squot;p&squot;
suffix:semicolon
r_if
c_cond
(paren
id|err
op_eq
l_int|0
)paren
(brace
r_return
id|master
suffix:semicolon
)brace
(paren
r_void
)paren
id|os_close_file
c_func
(paren
id|master
)paren
suffix:semicolon
)brace
)brace
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|pty_open
r_static
r_int
id|pty_open
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
id|pty_chan
op_star
id|data
op_assign
id|d
suffix:semicolon
r_int
id|fd
comma
id|err
suffix:semicolon
r_char
id|dev
(braket
r_sizeof
(paren
l_string|&quot;/dev/ptyxx&bslash;0&quot;
)paren
)braket
op_assign
l_string|&quot;/dev/ptyxx&quot;
suffix:semicolon
id|fd
op_assign
id|getmaster
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
(brace
r_return
op_minus
id|errno
suffix:semicolon
)brace
r_if
c_cond
(paren
id|data-&gt;raw
)paren
(brace
id|err
op_assign
id|raw
c_func
(paren
id|fd
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
r_if
c_cond
(paren
id|data-&gt;announce
)paren
(brace
(paren
op_star
id|data-&gt;announce
)paren
(paren
id|dev
comma
id|data-&gt;dev
)paren
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|data-&gt;dev_name
comma
l_string|&quot;%s&quot;
comma
id|dev
)paren
suffix:semicolon
op_star
id|dev_out
op_assign
id|data-&gt;dev_name
suffix:semicolon
r_return
id|fd
suffix:semicolon
)brace
DECL|function|pty_console_write
r_static
r_int
id|pty_console_write
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
id|pty_chan
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
DECL|variable|pty_ops
r_struct
id|chan_ops
id|pty_ops
op_assign
(brace
dot
id|type
op_assign
l_string|&quot;pty&quot;
comma
dot
id|init
op_assign
id|pty_chan_init
comma
dot
id|open
op_assign
id|pty_open
comma
dot
id|close
op_assign
id|generic_close
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
id|pty_console_write
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
l_int|0
comma
)brace
suffix:semicolon
DECL|variable|pts_ops
r_struct
id|chan_ops
id|pts_ops
op_assign
(brace
dot
id|type
op_assign
l_string|&quot;pts&quot;
comma
dot
id|init
op_assign
id|pty_chan_init
comma
dot
id|open
op_assign
id|pts_open
comma
dot
id|close
op_assign
id|generic_close
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
id|pty_console_write
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
l_int|0
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
