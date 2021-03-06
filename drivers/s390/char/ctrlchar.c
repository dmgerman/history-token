multiline_comment|/*&n; *  drivers/s390/char/ctrlchar.c&n; *  Unified handling of special chars.&n; *&n; *    Copyright (C) 2001 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Fritz Elfert &lt;felfert@millenux.com&gt; &lt;elfert@de.ibm.com&gt;&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;asm/errno.h&gt;
macro_line|#include &lt;linux/sysrq.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &quot;ctrlchar.h&quot;
macro_line|#ifdef CONFIG_MAGIC_SYSRQ
DECL|variable|ctrlchar_sysrq_key
r_static
r_int
id|ctrlchar_sysrq_key
suffix:semicolon
r_static
r_void
DECL|function|ctrlchar_handle_sysrq
id|ctrlchar_handle_sysrq
c_func
(paren
r_void
op_star
id|tty
)paren
(brace
id|handle_sysrq
c_func
(paren
id|ctrlchar_sysrq_key
comma
l_int|NULL
comma
(paren
r_struct
id|tty_struct
op_star
)paren
id|tty
)paren
suffix:semicolon
)brace
r_static
id|DECLARE_WORK
c_func
(paren
id|ctrlchar_work
comma
id|ctrlchar_handle_sysrq
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/**&n; * Check for special chars at start of input.&n; *&n; * @param buf Console input buffer.&n; * @param len Length of valid data in buffer.&n; * @param tty The tty struct for this console.&n; * @return CTRLCHAR_NONE, if nothing matched,&n; *         CTRLCHAR_SYSRQ, if sysrq was encountered&n; *         otherwise char to be inserted logically or&squot;ed&n; *         with CTRLCHAR_CTRL&n; */
r_int
r_int
DECL|function|ctrlchar_handle
id|ctrlchar_handle
c_func
(paren
r_const
r_int
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
(brace
r_if
c_cond
(paren
(paren
id|len
OL
l_int|2
)paren
op_logical_or
(paren
id|len
OG
l_int|3
)paren
)paren
r_return
id|CTRLCHAR_NONE
suffix:semicolon
multiline_comment|/* hat is 0xb1 in codepage 037 (US etc.) and thus */
multiline_comment|/* converted to 0x5e in ascii (&squot;^&squot;) */
r_if
c_cond
(paren
(paren
id|buf
(braket
l_int|0
)braket
op_ne
l_char|&squot;^&squot;
)paren
op_logical_and
(paren
id|buf
(braket
l_int|0
)braket
op_ne
l_char|&squot;&bslash;252&squot;
)paren
)paren
r_return
id|CTRLCHAR_NONE
suffix:semicolon
macro_line|#ifdef CONFIG_MAGIC_SYSRQ
multiline_comment|/* racy */
r_if
c_cond
(paren
id|len
op_eq
l_int|3
op_logical_and
id|buf
(braket
l_int|1
)braket
op_eq
l_char|&squot;-&squot;
)paren
(brace
id|ctrlchar_sysrq_key
op_assign
id|buf
(braket
l_int|2
)braket
suffix:semicolon
id|ctrlchar_work.data
op_assign
id|tty
suffix:semicolon
id|schedule_work
c_func
(paren
op_amp
id|ctrlchar_work
)paren
suffix:semicolon
r_return
id|CTRLCHAR_SYSRQ
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|len
op_ne
l_int|2
)paren
r_return
id|CTRLCHAR_NONE
suffix:semicolon
r_switch
c_cond
(paren
id|tolower
c_func
(paren
id|buf
(braket
l_int|1
)braket
)paren
)paren
(brace
r_case
l_char|&squot;c&squot;
suffix:colon
r_return
id|INTR_CHAR
c_func
(paren
id|tty
)paren
op_or
id|CTRLCHAR_CTRL
suffix:semicolon
r_case
l_char|&squot;d&squot;
suffix:colon
r_return
id|EOF_CHAR
c_func
(paren
id|tty
)paren
op_or
id|CTRLCHAR_CTRL
suffix:semicolon
r_case
l_char|&squot;z&squot;
suffix:colon
r_return
id|SUSP_CHAR
c_func
(paren
id|tty
)paren
op_or
id|CTRLCHAR_CTRL
suffix:semicolon
)brace
r_return
id|CTRLCHAR_NONE
suffix:semicolon
)brace
eof
