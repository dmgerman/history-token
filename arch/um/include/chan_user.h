multiline_comment|/* &n; * Copyright (C) 2000, 2001 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __CHAN_USER_H__
DECL|macro|__CHAN_USER_H__
mdefine_line|#define __CHAN_USER_H__
macro_line|#include &quot;init.h&quot;
DECL|struct|chan_opts
r_struct
id|chan_opts
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
DECL|member|xterm_title
r_char
op_star
id|xterm_title
suffix:semicolon
DECL|member|raw
r_int
id|raw
suffix:semicolon
DECL|member|tramp_stack
r_int
r_int
id|tramp_stack
suffix:semicolon
DECL|member|in_kernel
r_int
id|in_kernel
suffix:semicolon
)brace
suffix:semicolon
DECL|enum|chan_init_pri
DECL|enumerator|INIT_STATIC
DECL|enumerator|INIT_ALL
DECL|enumerator|INIT_ONE
r_enum
id|chan_init_pri
(brace
id|INIT_STATIC
comma
id|INIT_ALL
comma
id|INIT_ONE
)brace
suffix:semicolon
DECL|struct|chan_ops
r_struct
id|chan_ops
(brace
DECL|member|type
r_char
op_star
id|type
suffix:semicolon
DECL|member|init
r_void
op_star
(paren
op_star
id|init
)paren
(paren
r_char
op_star
comma
r_int
comma
r_struct
id|chan_opts
op_star
)paren
suffix:semicolon
DECL|member|open
r_int
(paren
op_star
id|open
)paren
(paren
r_int
comma
r_int
comma
r_int
comma
r_void
op_star
comma
r_char
op_star
op_star
)paren
suffix:semicolon
DECL|member|close
r_void
(paren
op_star
id|close
)paren
(paren
r_int
comma
r_void
op_star
)paren
suffix:semicolon
DECL|member|read
r_int
(paren
op_star
id|read
)paren
(paren
r_int
comma
r_char
op_star
comma
r_void
op_star
)paren
suffix:semicolon
DECL|member|write
r_int
(paren
op_star
id|write
)paren
(paren
r_int
comma
r_const
r_char
op_star
comma
r_int
comma
r_void
op_star
)paren
suffix:semicolon
DECL|member|console_write
r_int
(paren
op_star
id|console_write
)paren
(paren
r_int
comma
r_const
r_char
op_star
comma
r_int
comma
r_void
op_star
)paren
suffix:semicolon
DECL|member|window_size
r_int
(paren
op_star
id|window_size
)paren
(paren
r_int
comma
r_void
op_star
comma
r_int
r_int
op_star
comma
r_int
r_int
op_star
)paren
suffix:semicolon
DECL|member|free
r_void
(paren
op_star
id|free
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|member|winch
r_int
id|winch
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|chan_ops
id|fd_ops
comma
id|null_ops
comma
id|port_ops
comma
id|pts_ops
comma
id|pty_ops
comma
id|tty_ops
comma
id|xterm_ops
suffix:semicolon
r_extern
r_void
id|generic_close
c_func
(paren
r_int
id|fd
comma
r_void
op_star
id|unused
)paren
suffix:semicolon
r_extern
r_int
id|generic_read
c_func
(paren
r_int
id|fd
comma
r_char
op_star
id|c_out
comma
r_void
op_star
id|unused
)paren
suffix:semicolon
r_extern
r_int
id|generic_write
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
id|unused
)paren
suffix:semicolon
r_extern
r_int
id|generic_console_write
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
id|state
)paren
suffix:semicolon
r_extern
r_int
id|generic_window_size
c_func
(paren
r_int
id|fd
comma
r_void
op_star
id|unused
comma
r_int
r_int
op_star
id|rows_out
comma
r_int
r_int
op_star
id|cols_out
)paren
suffix:semicolon
r_extern
r_void
id|generic_free
c_func
(paren
r_void
op_star
id|data
)paren
suffix:semicolon
r_struct
id|tty_struct
suffix:semicolon
r_extern
r_void
id|register_winch
c_func
(paren
r_int
id|fd
comma
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
r_extern
r_void
id|register_winch_irq
c_func
(paren
r_int
id|fd
comma
r_int
id|tty_fd
comma
r_int
id|pid
comma
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
DECL|macro|__channel_help
mdefine_line|#define __channel_help(fn, prefix) &bslash;&n;__uml_help(fn, prefix &quot;[0-9]*=&lt;channel description&gt;&bslash;n&quot; &bslash;&n;&quot;    Attach a console or serial line to a host channel.  See&bslash;n&quot; &bslash;&n;&quot;    http:
singleline_comment|//user-mode-linux.sourceforge.net/input.html for a complete&bslash;n&quot; &bslash;
l_string|&quot;    description of this switch.&bslash;n&bslash;n&quot;
"&bslash;"
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
