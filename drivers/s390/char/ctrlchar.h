multiline_comment|/*&n; *  drivers/s390/char/ctrlchar.c&n; *  Unified handling of special chars.&n; *&n; *    Copyright (C) 2001 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Fritz Elfert &lt;felfert@millenux.com&gt; &lt;elfert@de.ibm.com&gt;&n; *&n; */
macro_line|#include &lt;linux/tty.h&gt;
r_extern
r_int
r_int
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
DECL|macro|CTRLCHAR_NONE
mdefine_line|#define CTRLCHAR_NONE  (1 &lt;&lt; 8)
DECL|macro|CTRLCHAR_CTRL
mdefine_line|#define CTRLCHAR_CTRL  (2 &lt;&lt; 8)
DECL|macro|CTRLCHAR_SYSRQ
mdefine_line|#define CTRLCHAR_SYSRQ (3 &lt;&lt; 8)
DECL|macro|CTRLCHAR_MASK
mdefine_line|#define CTRLCHAR_MASK (~0xffu)
eof
