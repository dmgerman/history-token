multiline_comment|/*&n; * Copyright (C) 1996 Paul Mackerras.&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sysrq.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/udbg.h&gt;
r_extern
r_void
id|xmon_printf
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
DECL|macro|TB_SPEED
mdefine_line|#define TB_SPEED&t;25000000
DECL|function|readtb
r_static
r_inline
r_int
r_int
id|readtb
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|ret
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;mftb %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|sysrq_handle_xmon
r_static
r_void
id|sysrq_handle_xmon
c_func
(paren
r_int
id|key
comma
r_struct
id|pt_regs
op_star
id|pt_regs
comma
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
id|xmon
c_func
(paren
id|pt_regs
)paren
suffix:semicolon
)brace
DECL|variable|sysrq_xmon_op
r_static
r_struct
id|sysrq_key_op
id|sysrq_xmon_op
op_assign
(brace
dot
id|handler
op_assign
id|sysrq_handle_xmon
comma
dot
id|help_msg
op_assign
l_string|&quot;xmon&quot;
comma
dot
id|action_msg
op_assign
l_string|&quot;Entering xmon&bslash;n&quot;
comma
)brace
suffix:semicolon
r_void
DECL|function|xmon_map_scc
id|xmon_map_scc
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* This maybe isn&squot;t the best place to register sysrq &squot;x&squot; */
id|__sysrq_put_key_op
c_func
(paren
l_char|&squot;x&squot;
comma
op_amp
id|sysrq_xmon_op
)paren
suffix:semicolon
)brace
r_int
DECL|function|xmon_write
id|xmon_write
c_func
(paren
r_void
op_star
id|handle
comma
r_void
op_star
id|ptr
comma
r_int
id|nb
)paren
(brace
r_return
id|udbg_write
c_func
(paren
id|ptr
comma
id|nb
)paren
suffix:semicolon
)brace
DECL|variable|xmon_wants_key
r_int
id|xmon_wants_key
suffix:semicolon
r_int
DECL|function|xmon_read
id|xmon_read
c_func
(paren
r_void
op_star
id|handle
comma
r_void
op_star
id|ptr
comma
r_int
id|nb
)paren
(brace
r_return
id|udbg_read
c_func
(paren
id|ptr
comma
id|nb
)paren
suffix:semicolon
)brace
r_int
DECL|function|xmon_read_poll
id|xmon_read_poll
c_func
(paren
r_void
)paren
(brace
r_return
id|udbg_getc_poll
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|xmon_stdin
r_void
op_star
id|xmon_stdin
suffix:semicolon
DECL|variable|xmon_stdout
r_void
op_star
id|xmon_stdout
suffix:semicolon
DECL|variable|xmon_stderr
r_void
op_star
id|xmon_stderr
suffix:semicolon
r_void
DECL|function|xmon_init
id|xmon_init
c_func
(paren
r_void
)paren
(brace
)brace
r_int
DECL|function|xmon_putc
id|xmon_putc
c_func
(paren
r_int
id|c
comma
r_void
op_star
id|f
)paren
(brace
r_char
id|ch
op_assign
id|c
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|xmon_putc
c_func
(paren
l_char|&squot;&bslash;r&squot;
comma
id|f
)paren
suffix:semicolon
r_return
id|xmon_write
c_func
(paren
id|f
comma
op_amp
id|ch
comma
l_int|1
)paren
op_eq
l_int|1
ques
c_cond
id|c
suffix:colon
op_minus
l_int|1
suffix:semicolon
)brace
r_int
DECL|function|xmon_putchar
id|xmon_putchar
c_func
(paren
r_int
id|c
)paren
(brace
r_return
id|xmon_putc
c_func
(paren
id|c
comma
id|xmon_stdout
)paren
suffix:semicolon
)brace
r_int
DECL|function|xmon_fputs
id|xmon_fputs
c_func
(paren
r_char
op_star
id|str
comma
r_void
op_star
id|f
)paren
(brace
r_int
id|n
op_assign
id|strlen
c_func
(paren
id|str
)paren
suffix:semicolon
r_return
id|xmon_write
c_func
(paren
id|f
comma
id|str
comma
id|n
)paren
op_eq
id|n
ques
c_cond
l_int|0
suffix:colon
op_minus
l_int|1
suffix:semicolon
)brace
r_int
DECL|function|xmon_readchar
id|xmon_readchar
c_func
(paren
r_void
)paren
(brace
r_char
id|ch
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_switch
c_cond
(paren
id|xmon_read
c_func
(paren
id|xmon_stdin
comma
op_amp
id|ch
comma
l_int|1
)paren
)paren
(brace
r_case
l_int|1
suffix:colon
r_return
id|ch
suffix:semicolon
r_case
op_minus
l_int|1
suffix:colon
id|xmon_printf
c_func
(paren
l_string|&quot;read(stdin) returned -1&bslash;r&bslash;n&quot;
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
)brace
DECL|variable|line
r_static
r_char
id|line
(braket
l_int|256
)braket
suffix:semicolon
DECL|variable|lineptr
r_static
r_char
op_star
id|lineptr
suffix:semicolon
DECL|variable|lineleft
r_static
r_int
id|lineleft
suffix:semicolon
r_int
DECL|function|xmon_getchar
id|xmon_getchar
c_func
(paren
r_void
)paren
(brace
r_int
id|c
suffix:semicolon
r_if
c_cond
(paren
id|lineleft
op_eq
l_int|0
)paren
(brace
id|lineptr
op_assign
id|line
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|c
op_assign
id|xmon_readchar
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
op_minus
l_int|1
op_logical_or
id|c
op_eq
l_int|4
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;r&squot;
op_logical_or
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
op_star
id|lineptr
op_increment
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|xmon_putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|c
)paren
(brace
r_case
l_int|0177
suffix:colon
r_case
l_char|&squot;&bslash;b&squot;
suffix:colon
r_if
c_cond
(paren
id|lineptr
OG
id|line
)paren
(brace
id|xmon_putchar
c_func
(paren
l_char|&squot;&bslash;b&squot;
)paren
suffix:semicolon
id|xmon_putchar
c_func
(paren
l_char|&squot; &squot;
)paren
suffix:semicolon
id|xmon_putchar
c_func
(paren
l_char|&squot;&bslash;b&squot;
)paren
suffix:semicolon
op_decrement
id|lineptr
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_char|&squot;U&squot;
op_amp
l_int|0x1F
suffix:colon
r_while
c_loop
(paren
id|lineptr
OG
id|line
)paren
(brace
id|xmon_putchar
c_func
(paren
l_char|&squot;&bslash;b&squot;
)paren
suffix:semicolon
id|xmon_putchar
c_func
(paren
l_char|&squot; &squot;
)paren
suffix:semicolon
id|xmon_putchar
c_func
(paren
l_char|&squot;&bslash;b&squot;
)paren
suffix:semicolon
op_decrement
id|lineptr
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|lineptr
op_ge
op_amp
id|line
(braket
r_sizeof
(paren
id|line
)paren
op_minus
l_int|1
)braket
)paren
id|xmon_putchar
c_func
(paren
l_char|&squot;&bslash;a&squot;
)paren
suffix:semicolon
r_else
(brace
id|xmon_putchar
c_func
(paren
id|c
)paren
suffix:semicolon
op_star
id|lineptr
op_increment
op_assign
id|c
suffix:semicolon
)brace
)brace
)brace
id|lineleft
op_assign
id|lineptr
op_minus
id|line
suffix:semicolon
id|lineptr
op_assign
id|line
suffix:semicolon
)brace
r_if
c_cond
(paren
id|lineleft
op_eq
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
op_decrement
id|lineleft
suffix:semicolon
r_return
op_star
id|lineptr
op_increment
suffix:semicolon
)brace
r_char
op_star
DECL|function|xmon_fgets
id|xmon_fgets
c_func
(paren
r_char
op_star
id|str
comma
r_int
id|nb
comma
r_void
op_star
id|f
)paren
(brace
r_char
op_star
id|p
suffix:semicolon
r_int
id|c
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|str
suffix:semicolon
id|p
OL
id|str
op_plus
id|nb
op_minus
l_int|1
suffix:semicolon
)paren
(brace
id|c
op_assign
id|xmon_getchar
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|p
op_eq
id|str
)paren
r_return
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
op_star
id|p
op_increment
op_assign
id|c
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
r_break
suffix:semicolon
)brace
op_star
id|p
op_assign
l_int|0
suffix:semicolon
r_return
id|str
suffix:semicolon
)brace
eof
