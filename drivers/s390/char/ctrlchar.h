multiline_comment|/*&n; *  drivers/s390/char/ctrlchar.c&n; *  Unified handling of special chars.&n; *&n; *    Copyright (C) 2001 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Fritz Elfert &lt;felfert@millenux.com&gt; &lt;elfert@de.ibm.com&gt;&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
r_extern
r_void
id|ctrlchar_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_char
op_star
id|ctrlchar_handle
c_func
(paren
r_const
r_char
op_star
id|buf
comma
r_int
id|len
comma
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
eof
