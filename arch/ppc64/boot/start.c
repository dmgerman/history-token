multiline_comment|/*&n; * Copyright (C) Paul Mackerras 1997.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;asm/div64.h&gt;
DECL|variable|prom
r_int
(paren
op_star
id|prom
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|variable|chosen_handle
r_void
op_star
id|chosen_handle
suffix:semicolon
DECL|variable|stdin
r_void
op_star
id|stdin
suffix:semicolon
DECL|variable|stdout
r_void
op_star
id|stdout
suffix:semicolon
DECL|variable|stderr
r_void
op_star
id|stderr
suffix:semicolon
r_void
m_exit
(paren
r_void
)paren
suffix:semicolon
r_void
op_star
id|finddevice
c_func
(paren
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
r_int
id|getprop
c_func
(paren
r_void
op_star
id|phandle
comma
r_const
r_char
op_star
id|name
comma
r_void
op_star
id|buf
comma
r_int
id|buflen
)paren
suffix:semicolon
r_void
id|chrpboot
c_func
(paren
r_int
id|a1
comma
r_int
id|a2
comma
r_void
op_star
id|prom
)paren
suffix:semicolon
multiline_comment|/* in main.c */
r_void
id|printk
c_func
(paren
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
r_void
DECL|function|start
id|start
c_func
(paren
r_int
id|a1
comma
r_int
id|a2
comma
r_void
op_star
id|promptr
)paren
(brace
id|prom
op_assign
(paren
r_int
(paren
op_star
)paren
(paren
r_void
op_star
)paren
)paren
id|promptr
suffix:semicolon
id|chosen_handle
op_assign
id|finddevice
c_func
(paren
l_string|&quot;/chosen&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chosen_handle
op_eq
(paren
r_void
op_star
)paren
op_minus
l_int|1
)paren
m_exit
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|getprop
c_func
(paren
id|chosen_handle
comma
l_string|&quot;stdout&quot;
comma
op_amp
id|stdout
comma
r_sizeof
(paren
id|stdout
)paren
)paren
op_ne
l_int|4
)paren
m_exit
(paren
)paren
suffix:semicolon
id|stderr
op_assign
id|stdout
suffix:semicolon
r_if
c_cond
(paren
id|getprop
c_func
(paren
id|chosen_handle
comma
l_string|&quot;stdin&quot;
comma
op_amp
id|stdin
comma
r_sizeof
(paren
id|stdin
)paren
)paren
op_ne
l_int|4
)paren
m_exit
(paren
)paren
suffix:semicolon
id|chrpboot
c_func
(paren
id|a1
comma
id|a2
comma
id|promptr
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
m_exit
(paren
)paren
suffix:semicolon
)brace
r_int
DECL|function|write
id|write
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
r_struct
id|prom_args
(brace
r_char
op_star
id|service
suffix:semicolon
r_int
id|nargs
suffix:semicolon
r_int
id|nret
suffix:semicolon
r_void
op_star
id|ihandle
suffix:semicolon
r_void
op_star
id|addr
suffix:semicolon
r_int
id|len
suffix:semicolon
r_int
id|actual
suffix:semicolon
)brace
id|args
suffix:semicolon
id|args.service
op_assign
l_string|&quot;write&quot;
suffix:semicolon
id|args.nargs
op_assign
l_int|3
suffix:semicolon
id|args.nret
op_assign
l_int|1
suffix:semicolon
id|args.ihandle
op_assign
id|handle
suffix:semicolon
id|args.addr
op_assign
id|ptr
suffix:semicolon
id|args.len
op_assign
id|nb
suffix:semicolon
id|args.actual
op_assign
op_minus
l_int|1
suffix:semicolon
(paren
op_star
id|prom
)paren
(paren
op_amp
id|args
)paren
suffix:semicolon
r_return
id|args.actual
suffix:semicolon
)brace
r_int
DECL|function|read
id|read
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
r_struct
id|prom_args
(brace
r_char
op_star
id|service
suffix:semicolon
r_int
id|nargs
suffix:semicolon
r_int
id|nret
suffix:semicolon
r_void
op_star
id|ihandle
suffix:semicolon
r_void
op_star
id|addr
suffix:semicolon
r_int
id|len
suffix:semicolon
r_int
id|actual
suffix:semicolon
)brace
id|args
suffix:semicolon
id|args.service
op_assign
l_string|&quot;read&quot;
suffix:semicolon
id|args.nargs
op_assign
l_int|3
suffix:semicolon
id|args.nret
op_assign
l_int|1
suffix:semicolon
id|args.ihandle
op_assign
id|handle
suffix:semicolon
id|args.addr
op_assign
id|ptr
suffix:semicolon
id|args.len
op_assign
id|nb
suffix:semicolon
id|args.actual
op_assign
op_minus
l_int|1
suffix:semicolon
(paren
op_star
id|prom
)paren
(paren
op_amp
id|args
)paren
suffix:semicolon
r_return
id|args.actual
suffix:semicolon
)brace
r_void
DECL|function|exit
m_exit
(paren
)paren
(brace
r_struct
id|prom_args
(brace
r_char
op_star
id|service
suffix:semicolon
)brace
id|args
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|args.service
op_assign
l_string|&quot;exit&quot;
suffix:semicolon
(paren
op_star
id|prom
)paren
(paren
op_amp
id|args
)paren
suffix:semicolon
)brace
)brace
r_void
DECL|function|pause
id|pause
c_func
(paren
r_void
)paren
(brace
r_struct
id|prom_args
(brace
r_char
op_star
id|service
suffix:semicolon
)brace
id|args
suffix:semicolon
id|args.service
op_assign
l_string|&quot;enter&quot;
suffix:semicolon
(paren
op_star
id|prom
)paren
(paren
op_amp
id|args
)paren
suffix:semicolon
)brace
r_void
op_star
DECL|function|finddevice
id|finddevice
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|prom_args
(brace
r_char
op_star
id|service
suffix:semicolon
r_int
id|nargs
suffix:semicolon
r_int
id|nret
suffix:semicolon
r_const
r_char
op_star
id|devspec
suffix:semicolon
r_void
op_star
id|phandle
suffix:semicolon
)brace
id|args
suffix:semicolon
id|args.service
op_assign
l_string|&quot;finddevice&quot;
suffix:semicolon
id|args.nargs
op_assign
l_int|1
suffix:semicolon
id|args.nret
op_assign
l_int|1
suffix:semicolon
id|args.devspec
op_assign
id|name
suffix:semicolon
id|args.phandle
op_assign
(paren
r_void
op_star
)paren
op_minus
l_int|1
suffix:semicolon
(paren
op_star
id|prom
)paren
(paren
op_amp
id|args
)paren
suffix:semicolon
r_return
id|args.phandle
suffix:semicolon
)brace
r_void
op_star
DECL|function|claim
id|claim
c_func
(paren
r_int
r_int
id|virt
comma
r_int
r_int
id|size
comma
r_int
r_int
id|align
)paren
(brace
r_struct
id|prom_args
(brace
r_char
op_star
id|service
suffix:semicolon
r_int
id|nargs
suffix:semicolon
r_int
id|nret
suffix:semicolon
r_int
r_int
id|virt
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_int
r_int
id|align
suffix:semicolon
r_void
op_star
id|ret
suffix:semicolon
)brace
id|args
suffix:semicolon
id|args.service
op_assign
l_string|&quot;claim&quot;
suffix:semicolon
id|args.nargs
op_assign
l_int|3
suffix:semicolon
id|args.nret
op_assign
l_int|1
suffix:semicolon
id|args.virt
op_assign
id|virt
suffix:semicolon
id|args.size
op_assign
id|size
suffix:semicolon
id|args.align
op_assign
id|align
suffix:semicolon
(paren
op_star
id|prom
)paren
(paren
op_amp
id|args
)paren
suffix:semicolon
r_return
id|args.ret
suffix:semicolon
)brace
r_int
DECL|function|getprop
id|getprop
c_func
(paren
r_void
op_star
id|phandle
comma
r_const
r_char
op_star
id|name
comma
r_void
op_star
id|buf
comma
r_int
id|buflen
)paren
(brace
r_struct
id|prom_args
(brace
r_char
op_star
id|service
suffix:semicolon
r_int
id|nargs
suffix:semicolon
r_int
id|nret
suffix:semicolon
r_void
op_star
id|phandle
suffix:semicolon
r_const
r_char
op_star
id|name
suffix:semicolon
r_void
op_star
id|buf
suffix:semicolon
r_int
id|buflen
suffix:semicolon
r_int
id|size
suffix:semicolon
)brace
id|args
suffix:semicolon
id|args.service
op_assign
l_string|&quot;getprop&quot;
suffix:semicolon
id|args.nargs
op_assign
l_int|4
suffix:semicolon
id|args.nret
op_assign
l_int|1
suffix:semicolon
id|args.phandle
op_assign
id|phandle
suffix:semicolon
id|args.name
op_assign
id|name
suffix:semicolon
id|args.buf
op_assign
id|buf
suffix:semicolon
id|args.buflen
op_assign
id|buflen
suffix:semicolon
id|args.size
op_assign
op_minus
l_int|1
suffix:semicolon
(paren
op_star
id|prom
)paren
(paren
op_amp
id|args
)paren
suffix:semicolon
r_return
id|args.size
suffix:semicolon
)brace
r_int
DECL|function|putc
id|putc
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
id|putc
c_func
(paren
l_char|&squot;&bslash;r&squot;
comma
id|f
)paren
suffix:semicolon
r_return
id|write
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
DECL|function|putchar
id|putchar
c_func
(paren
r_int
id|c
)paren
(brace
r_return
id|putc
c_func
(paren
id|c
comma
id|stdout
)paren
suffix:semicolon
)brace
r_int
DECL|function|fputs
id|fputs
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
id|write
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
DECL|function|readchar
id|readchar
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
id|read
c_func
(paren
id|stdin
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
id|printk
c_func
(paren
l_string|&quot;read(stdin) returned -1&bslash;r&bslash;n&quot;
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
DECL|function|getchar
id|getchar
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
id|readchar
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
id|putchar
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
id|putchar
c_func
(paren
l_char|&squot;&bslash;b&squot;
)paren
suffix:semicolon
id|putchar
c_func
(paren
l_char|&squot; &squot;
)paren
suffix:semicolon
id|putchar
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
id|putchar
c_func
(paren
l_char|&squot;&bslash;b&squot;
)paren
suffix:semicolon
id|putchar
c_func
(paren
l_char|&squot; &squot;
)paren
suffix:semicolon
id|putchar
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
id|putchar
c_func
(paren
l_char|&squot;&bslash;a&squot;
)paren
suffix:semicolon
r_else
(brace
id|putchar
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
multiline_comment|/* String functions lifted from lib/vsprintf.c and lib/ctype.c */
DECL|variable|_ctype
r_int
r_char
id|_ctype
(braket
)braket
op_assign
(brace
id|_C
comma
id|_C
comma
id|_C
comma
id|_C
comma
id|_C
comma
id|_C
comma
id|_C
comma
id|_C
comma
multiline_comment|/* 0-7 */
id|_C
comma
id|_C
op_or
id|_S
comma
id|_C
op_or
id|_S
comma
id|_C
op_or
id|_S
comma
id|_C
op_or
id|_S
comma
id|_C
op_or
id|_S
comma
id|_C
comma
id|_C
comma
multiline_comment|/* 8-15 */
id|_C
comma
id|_C
comma
id|_C
comma
id|_C
comma
id|_C
comma
id|_C
comma
id|_C
comma
id|_C
comma
multiline_comment|/* 16-23 */
id|_C
comma
id|_C
comma
id|_C
comma
id|_C
comma
id|_C
comma
id|_C
comma
id|_C
comma
id|_C
comma
multiline_comment|/* 24-31 */
id|_S
op_or
id|_SP
comma
id|_P
comma
id|_P
comma
id|_P
comma
id|_P
comma
id|_P
comma
id|_P
comma
id|_P
comma
multiline_comment|/* 32-39 */
id|_P
comma
id|_P
comma
id|_P
comma
id|_P
comma
id|_P
comma
id|_P
comma
id|_P
comma
id|_P
comma
multiline_comment|/* 40-47 */
id|_D
comma
id|_D
comma
id|_D
comma
id|_D
comma
id|_D
comma
id|_D
comma
id|_D
comma
id|_D
comma
multiline_comment|/* 48-55 */
id|_D
comma
id|_D
comma
id|_P
comma
id|_P
comma
id|_P
comma
id|_P
comma
id|_P
comma
id|_P
comma
multiline_comment|/* 56-63 */
id|_P
comma
id|_U
op_or
id|_X
comma
id|_U
op_or
id|_X
comma
id|_U
op_or
id|_X
comma
id|_U
op_or
id|_X
comma
id|_U
op_or
id|_X
comma
id|_U
op_or
id|_X
comma
id|_U
comma
multiline_comment|/* 64-71 */
id|_U
comma
id|_U
comma
id|_U
comma
id|_U
comma
id|_U
comma
id|_U
comma
id|_U
comma
id|_U
comma
multiline_comment|/* 72-79 */
id|_U
comma
id|_U
comma
id|_U
comma
id|_U
comma
id|_U
comma
id|_U
comma
id|_U
comma
id|_U
comma
multiline_comment|/* 80-87 */
id|_U
comma
id|_U
comma
id|_U
comma
id|_P
comma
id|_P
comma
id|_P
comma
id|_P
comma
id|_P
comma
multiline_comment|/* 88-95 */
id|_P
comma
id|_L
op_or
id|_X
comma
id|_L
op_or
id|_X
comma
id|_L
op_or
id|_X
comma
id|_L
op_or
id|_X
comma
id|_L
op_or
id|_X
comma
id|_L
op_or
id|_X
comma
id|_L
comma
multiline_comment|/* 96-103 */
id|_L
comma
id|_L
comma
id|_L
comma
id|_L
comma
id|_L
comma
id|_L
comma
id|_L
comma
id|_L
comma
multiline_comment|/* 104-111 */
id|_L
comma
id|_L
comma
id|_L
comma
id|_L
comma
id|_L
comma
id|_L
comma
id|_L
comma
id|_L
comma
multiline_comment|/* 112-119 */
id|_L
comma
id|_L
comma
id|_L
comma
id|_P
comma
id|_P
comma
id|_P
comma
id|_P
comma
id|_C
comma
multiline_comment|/* 120-127 */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* 128-143 */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* 144-159 */
id|_S
op_or
id|_SP
comma
id|_P
comma
id|_P
comma
id|_P
comma
id|_P
comma
id|_P
comma
id|_P
comma
id|_P
comma
id|_P
comma
id|_P
comma
id|_P
comma
id|_P
comma
id|_P
comma
id|_P
comma
id|_P
comma
id|_P
comma
multiline_comment|/* 160-175 */
id|_P
comma
id|_P
comma
id|_P
comma
id|_P
comma
id|_P
comma
id|_P
comma
id|_P
comma
id|_P
comma
id|_P
comma
id|_P
comma
id|_P
comma
id|_P
comma
id|_P
comma
id|_P
comma
id|_P
comma
id|_P
comma
multiline_comment|/* 176-191 */
id|_U
comma
id|_U
comma
id|_U
comma
id|_U
comma
id|_U
comma
id|_U
comma
id|_U
comma
id|_U
comma
id|_U
comma
id|_U
comma
id|_U
comma
id|_U
comma
id|_U
comma
id|_U
comma
id|_U
comma
id|_U
comma
multiline_comment|/* 192-207 */
id|_U
comma
id|_U
comma
id|_U
comma
id|_U
comma
id|_U
comma
id|_U
comma
id|_U
comma
id|_P
comma
id|_U
comma
id|_U
comma
id|_U
comma
id|_U
comma
id|_U
comma
id|_U
comma
id|_U
comma
id|_L
comma
multiline_comment|/* 208-223 */
id|_L
comma
id|_L
comma
id|_L
comma
id|_L
comma
id|_L
comma
id|_L
comma
id|_L
comma
id|_L
comma
id|_L
comma
id|_L
comma
id|_L
comma
id|_L
comma
id|_L
comma
id|_L
comma
id|_L
comma
id|_L
comma
multiline_comment|/* 224-239 */
id|_L
comma
id|_L
comma
id|_L
comma
id|_L
comma
id|_L
comma
id|_L
comma
id|_L
comma
id|_P
comma
id|_L
comma
id|_L
comma
id|_L
comma
id|_L
comma
id|_L
comma
id|_L
comma
id|_L
comma
id|_L
)brace
suffix:semicolon
multiline_comment|/* 240-255 */
DECL|function|strnlen
r_int
id|strnlen
c_func
(paren
r_const
r_char
op_star
id|s
comma
r_int
id|count
)paren
(brace
r_const
r_char
op_star
id|sc
suffix:semicolon
r_for
c_loop
(paren
id|sc
op_assign
id|s
suffix:semicolon
id|count
op_decrement
op_logical_and
op_star
id|sc
op_ne
l_char|&squot;&bslash;0&squot;
suffix:semicolon
op_increment
id|sc
)paren
multiline_comment|/* nothing */
suffix:semicolon
r_return
id|sc
op_minus
id|s
suffix:semicolon
)brace
DECL|function|simple_strtoul
r_int
r_int
id|simple_strtoul
c_func
(paren
r_const
r_char
op_star
id|cp
comma
r_char
op_star
op_star
id|endp
comma
r_int
r_int
id|base
)paren
(brace
r_int
r_int
id|result
op_assign
l_int|0
comma
id|value
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|base
)paren
(brace
id|base
op_assign
l_int|10
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;0&squot;
)paren
(brace
id|base
op_assign
l_int|8
suffix:semicolon
id|cp
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|cp
op_eq
l_char|&squot;x&squot;
)paren
op_logical_and
id|isxdigit
c_func
(paren
id|cp
(braket
l_int|1
)braket
)paren
)paren
(brace
id|cp
op_increment
suffix:semicolon
id|base
op_assign
l_int|16
suffix:semicolon
)brace
)brace
)brace
r_while
c_loop
(paren
id|isxdigit
c_func
(paren
op_star
id|cp
)paren
op_logical_and
(paren
id|value
op_assign
id|isdigit
c_func
(paren
op_star
id|cp
)paren
ques
c_cond
op_star
id|cp
op_minus
l_char|&squot;0&squot;
suffix:colon
id|toupper
c_func
(paren
op_star
id|cp
)paren
op_minus
l_char|&squot;A&squot;
op_plus
l_int|10
)paren
OL
id|base
)paren
(brace
id|result
op_assign
id|result
op_star
id|base
op_plus
id|value
suffix:semicolon
id|cp
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|endp
)paren
op_star
id|endp
op_assign
(paren
r_char
op_star
)paren
id|cp
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|simple_strtol
r_int
id|simple_strtol
c_func
(paren
r_const
r_char
op_star
id|cp
comma
r_char
op_star
op_star
id|endp
comma
r_int
r_int
id|base
)paren
(brace
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;-&squot;
)paren
(brace
r_return
op_minus
id|simple_strtoul
c_func
(paren
id|cp
op_plus
l_int|1
comma
id|endp
comma
id|base
)paren
suffix:semicolon
)brace
r_return
id|simple_strtoul
c_func
(paren
id|cp
comma
id|endp
comma
id|base
)paren
suffix:semicolon
)brace
DECL|function|skip_atoi
r_static
r_int
id|skip_atoi
c_func
(paren
r_const
r_char
op_star
op_star
id|s
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|isdigit
c_func
(paren
op_star
op_star
id|s
)paren
)paren
id|i
op_assign
id|i
op_star
l_int|10
op_plus
op_star
(paren
(paren
op_star
id|s
)paren
op_increment
)paren
op_minus
l_char|&squot;0&squot;
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
DECL|macro|ZEROPAD
mdefine_line|#define ZEROPAD&t;1&t;&t;/* pad with zero */
DECL|macro|SIGN
mdefine_line|#define SIGN&t;2&t;&t;/* unsigned/signed long */
DECL|macro|PLUS
mdefine_line|#define PLUS&t;4&t;&t;/* show plus */
DECL|macro|SPACE
mdefine_line|#define SPACE&t;8&t;&t;/* space if plus */
DECL|macro|LEFT
mdefine_line|#define LEFT&t;16&t;&t;/* left justified */
DECL|macro|SPECIAL
mdefine_line|#define SPECIAL&t;32&t;&t;/* 0x */
DECL|macro|LARGE
mdefine_line|#define LARGE&t;64&t;&t;/* use &squot;ABCDEF&squot; instead of &squot;abcdef&squot; */
DECL|function|number
r_static
r_char
op_star
id|number
c_func
(paren
r_char
op_star
id|str
comma
r_int
r_int
id|num
comma
r_int
id|base
comma
r_int
id|size
comma
r_int
id|precision
comma
r_int
id|type
)paren
(brace
r_char
id|c
comma
id|sign
comma
id|tmp
(braket
l_int|66
)braket
suffix:semicolon
r_const
r_char
op_star
id|digits
op_assign
l_string|&quot;0123456789abcdefghijklmnopqrstuvwxyz&quot;
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|type
op_amp
id|LARGE
)paren
id|digits
op_assign
l_string|&quot;0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ&quot;
suffix:semicolon
r_if
c_cond
(paren
id|type
op_amp
id|LEFT
)paren
id|type
op_and_assign
op_complement
id|ZEROPAD
suffix:semicolon
r_if
c_cond
(paren
id|base
template_param
l_int|36
)paren
r_return
l_int|0
suffix:semicolon
id|c
op_assign
(paren
id|type
op_amp
id|ZEROPAD
)paren
ques
c_cond
l_char|&squot;0&squot;
suffix:colon
l_char|&squot; &squot;
suffix:semicolon
id|sign
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|type
op_amp
id|SIGN
)paren
(brace
r_if
c_cond
(paren
id|num
OL
l_int|0
)paren
(brace
id|sign
op_assign
l_char|&squot;-&squot;
suffix:semicolon
id|num
op_assign
op_minus
id|num
suffix:semicolon
id|size
op_decrement
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|type
op_amp
id|PLUS
)paren
(brace
id|sign
op_assign
l_char|&squot;+&squot;
suffix:semicolon
id|size
op_decrement
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|type
op_amp
id|SPACE
)paren
(brace
id|sign
op_assign
l_char|&squot; &squot;
suffix:semicolon
id|size
op_decrement
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|type
op_amp
id|SPECIAL
)paren
(brace
r_if
c_cond
(paren
id|base
op_eq
l_int|16
)paren
id|size
op_sub_assign
l_int|2
suffix:semicolon
r_else
r_if
c_cond
(paren
id|base
op_eq
l_int|8
)paren
id|size
op_decrement
suffix:semicolon
)brace
id|i
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|num
op_eq
l_int|0
)paren
id|tmp
(braket
id|i
op_increment
)braket
op_assign
l_char|&squot;0&squot;
suffix:semicolon
r_else
r_while
c_loop
(paren
id|num
op_ne
l_int|0
)paren
id|tmp
(braket
id|i
op_increment
)braket
op_assign
id|digits
(braket
id|do_div
c_func
(paren
id|num
comma
id|base
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
id|precision
)paren
id|precision
op_assign
id|i
suffix:semicolon
id|size
op_sub_assign
id|precision
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|type
op_amp
(paren
id|ZEROPAD
op_plus
id|LEFT
)paren
)paren
)paren
r_while
c_loop
(paren
id|size
op_decrement
OG
l_int|0
)paren
(brace
op_star
id|str
op_increment
op_assign
l_char|&squot; &squot;
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sign
)paren
op_star
id|str
op_increment
op_assign
id|sign
suffix:semicolon
r_if
c_cond
(paren
id|type
op_amp
id|SPECIAL
)paren
(brace
r_if
c_cond
(paren
id|base
op_eq
l_int|8
)paren
op_star
id|str
op_increment
op_assign
l_char|&squot;0&squot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|base
op_eq
l_int|16
)paren
(brace
op_star
id|str
op_increment
op_assign
l_char|&squot;0&squot;
suffix:semicolon
op_star
id|str
op_increment
op_assign
id|digits
(braket
l_int|33
)braket
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|type
op_amp
id|LEFT
)paren
)paren
r_while
c_loop
(paren
id|size
op_decrement
OG
l_int|0
)paren
op_star
id|str
op_increment
op_assign
id|c
suffix:semicolon
r_while
c_loop
(paren
id|i
OL
id|precision
op_decrement
)paren
op_star
id|str
op_increment
op_assign
l_char|&squot;0&squot;
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
OG
l_int|0
)paren
op_star
id|str
op_increment
op_assign
id|tmp
(braket
id|i
)braket
suffix:semicolon
r_while
c_loop
(paren
id|size
op_decrement
OG
l_int|0
)paren
op_star
id|str
op_increment
op_assign
l_char|&squot; &squot;
suffix:semicolon
r_return
id|str
suffix:semicolon
)brace
multiline_comment|/* Forward decl. needed for IP address printing stuff... */
r_int
id|sprintf
c_func
(paren
r_char
op_star
id|buf
comma
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
DECL|function|vsprintf
r_int
id|vsprintf
c_func
(paren
r_char
op_star
id|buf
comma
r_const
r_char
op_star
id|fmt
comma
id|va_list
id|args
)paren
(brace
r_int
id|len
suffix:semicolon
r_int
r_int
r_int
id|num
suffix:semicolon
r_int
id|i
comma
id|base
suffix:semicolon
r_char
op_star
id|str
suffix:semicolon
r_const
r_char
op_star
id|s
suffix:semicolon
r_int
id|flags
suffix:semicolon
multiline_comment|/* flags to number() */
r_int
id|field_width
suffix:semicolon
multiline_comment|/* width of output field */
r_int
id|precision
suffix:semicolon
multiline_comment|/* min. # of digits for integers; max&n;&t;&t;&t;&t;   number of chars for from string */
r_int
id|qualifier
suffix:semicolon
multiline_comment|/* &squot;h&squot;, &squot;l&squot;, or &squot;L&squot; for integer fields */
multiline_comment|/* &squot;z&squot; support added 23/7/1999 S.H.    */
multiline_comment|/* &squot;z&squot; changed to &squot;Z&squot; --davidm 1/25/99 */
r_for
c_loop
(paren
id|str
op_assign
id|buf
suffix:semicolon
op_star
id|fmt
suffix:semicolon
op_increment
id|fmt
)paren
(brace
r_if
c_cond
(paren
op_star
id|fmt
op_ne
l_char|&squot;%&squot;
)paren
(brace
op_star
id|str
op_increment
op_assign
op_star
id|fmt
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* process flags */
id|flags
op_assign
l_int|0
suffix:semicolon
id|repeat
suffix:colon
op_increment
id|fmt
suffix:semicolon
multiline_comment|/* this also skips first &squot;%&squot; */
r_switch
c_cond
(paren
op_star
id|fmt
)paren
(brace
r_case
l_char|&squot;-&squot;
suffix:colon
id|flags
op_or_assign
id|LEFT
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
r_case
l_char|&squot;+&squot;
suffix:colon
id|flags
op_or_assign
id|PLUS
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
r_case
l_char|&squot; &squot;
suffix:colon
id|flags
op_or_assign
id|SPACE
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
r_case
l_char|&squot;#&squot;
suffix:colon
id|flags
op_or_assign
id|SPECIAL
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
r_case
l_char|&squot;0&squot;
suffix:colon
id|flags
op_or_assign
id|ZEROPAD
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
multiline_comment|/* get field width */
id|field_width
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|isdigit
c_func
(paren
op_star
id|fmt
)paren
)paren
id|field_width
op_assign
id|skip_atoi
c_func
(paren
op_amp
id|fmt
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_star
id|fmt
op_eq
l_char|&squot;*&squot;
)paren
(brace
op_increment
id|fmt
suffix:semicolon
multiline_comment|/* it&squot;s the next argument */
id|field_width
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_int
)paren
suffix:semicolon
r_if
c_cond
(paren
id|field_width
OL
l_int|0
)paren
(brace
id|field_width
op_assign
op_minus
id|field_width
suffix:semicolon
id|flags
op_or_assign
id|LEFT
suffix:semicolon
)brace
)brace
multiline_comment|/* get the precision */
id|precision
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_star
id|fmt
op_eq
l_char|&squot;.&squot;
)paren
(brace
op_increment
id|fmt
suffix:semicolon
r_if
c_cond
(paren
id|isdigit
c_func
(paren
op_star
id|fmt
)paren
)paren
id|precision
op_assign
id|skip_atoi
c_func
(paren
op_amp
id|fmt
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_star
id|fmt
op_eq
l_char|&squot;*&squot;
)paren
(brace
op_increment
id|fmt
suffix:semicolon
multiline_comment|/* it&squot;s the next argument */
id|precision
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_int
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|precision
OL
l_int|0
)paren
id|precision
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* get the conversion qualifier */
id|qualifier
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_star
id|fmt
op_eq
l_char|&squot;h&squot;
op_logical_or
op_star
id|fmt
op_eq
l_char|&squot;l&squot;
op_logical_or
op_star
id|fmt
op_eq
l_char|&squot;L&squot;
op_logical_or
op_star
id|fmt
op_eq
l_char|&squot;Z&squot;
)paren
(brace
id|qualifier
op_assign
op_star
id|fmt
suffix:semicolon
op_increment
id|fmt
suffix:semicolon
)brace
multiline_comment|/* default base */
id|base
op_assign
l_int|10
suffix:semicolon
r_switch
c_cond
(paren
op_star
id|fmt
)paren
(brace
r_case
l_char|&squot;c&squot;
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|LEFT
)paren
)paren
r_while
c_loop
(paren
op_decrement
id|field_width
OG
l_int|0
)paren
op_star
id|str
op_increment
op_assign
l_char|&squot; &squot;
suffix:semicolon
op_star
id|str
op_increment
op_assign
(paren
r_int
r_char
)paren
id|va_arg
c_func
(paren
id|args
comma
r_int
)paren
suffix:semicolon
r_while
c_loop
(paren
op_decrement
id|field_width
OG
l_int|0
)paren
op_star
id|str
op_increment
op_assign
l_char|&squot; &squot;
suffix:semicolon
r_continue
suffix:semicolon
r_case
l_char|&squot;s&squot;
suffix:colon
id|s
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_char
op_star
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s
)paren
id|s
op_assign
l_string|&quot;&lt;NULL&gt;&quot;
suffix:semicolon
id|len
op_assign
id|strnlen
c_func
(paren
id|s
comma
id|precision
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|LEFT
)paren
)paren
r_while
c_loop
(paren
id|len
OL
id|field_width
op_decrement
)paren
op_star
id|str
op_increment
op_assign
l_char|&squot; &squot;
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|len
suffix:semicolon
op_increment
id|i
)paren
op_star
id|str
op_increment
op_assign
op_star
id|s
op_increment
suffix:semicolon
r_while
c_loop
(paren
id|len
OL
id|field_width
op_decrement
)paren
op_star
id|str
op_increment
op_assign
l_char|&squot; &squot;
suffix:semicolon
r_continue
suffix:semicolon
r_case
l_char|&squot;p&squot;
suffix:colon
r_if
c_cond
(paren
id|field_width
op_eq
op_minus
l_int|1
)paren
(brace
id|field_width
op_assign
l_int|2
op_star
r_sizeof
(paren
r_void
op_star
)paren
suffix:semicolon
id|flags
op_or_assign
id|ZEROPAD
suffix:semicolon
)brace
id|str
op_assign
id|number
c_func
(paren
id|str
comma
(paren
r_int
r_int
)paren
id|va_arg
c_func
(paren
id|args
comma
r_void
op_star
)paren
comma
l_int|16
comma
id|field_width
comma
id|precision
comma
id|flags
)paren
suffix:semicolon
r_continue
suffix:semicolon
r_case
l_char|&squot;n&squot;
suffix:colon
r_if
c_cond
(paren
id|qualifier
op_eq
l_char|&squot;l&squot;
)paren
(brace
r_int
op_star
id|ip
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_int
op_star
)paren
suffix:semicolon
op_star
id|ip
op_assign
(paren
id|str
op_minus
id|buf
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|qualifier
op_eq
l_char|&squot;Z&squot;
)paren
(brace
r_int
op_star
id|ip
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_int
op_star
)paren
suffix:semicolon
op_star
id|ip
op_assign
(paren
id|str
op_minus
id|buf
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
op_star
id|ip
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_int
op_star
)paren
suffix:semicolon
op_star
id|ip
op_assign
(paren
id|str
op_minus
id|buf
)paren
suffix:semicolon
)brace
r_continue
suffix:semicolon
r_case
l_char|&squot;%&squot;
suffix:colon
op_star
id|str
op_increment
op_assign
l_char|&squot;%&squot;
suffix:semicolon
r_continue
suffix:semicolon
multiline_comment|/* integer number formats - set up the flags and &quot;break&quot; */
r_case
l_char|&squot;o&squot;
suffix:colon
id|base
op_assign
l_int|8
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;X&squot;
suffix:colon
id|flags
op_or_assign
id|LARGE
suffix:semicolon
r_case
l_char|&squot;x&squot;
suffix:colon
id|base
op_assign
l_int|16
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;d&squot;
suffix:colon
r_case
l_char|&squot;i&squot;
suffix:colon
id|flags
op_or_assign
id|SIGN
suffix:semicolon
r_case
l_char|&squot;u&squot;
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
op_star
id|str
op_increment
op_assign
l_char|&squot;%&squot;
suffix:semicolon
r_if
c_cond
(paren
op_star
id|fmt
)paren
op_star
id|str
op_increment
op_assign
op_star
id|fmt
suffix:semicolon
r_else
op_decrement
id|fmt
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|qualifier
op_eq
l_char|&squot;L&squot;
)paren
id|num
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_int
r_int
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|qualifier
op_eq
l_char|&squot;l&squot;
)paren
(brace
id|num
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_int
r_int
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|SIGN
)paren
id|num
op_assign
(paren
r_int
r_int
)paren
id|num
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|qualifier
op_eq
l_char|&squot;Z&squot;
)paren
(brace
id|num
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_int
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|qualifier
op_eq
l_char|&squot;h&squot;
)paren
(brace
id|num
op_assign
(paren
r_int
r_int
)paren
id|va_arg
c_func
(paren
id|args
comma
r_int
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|SIGN
)paren
id|num
op_assign
(paren
r_int
r_int
)paren
id|num
suffix:semicolon
)brace
r_else
(brace
id|num
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_int
r_int
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|SIGN
)paren
id|num
op_assign
(paren
r_int
r_int
)paren
id|num
suffix:semicolon
)brace
id|str
op_assign
id|number
c_func
(paren
id|str
comma
id|num
comma
id|base
comma
id|field_width
comma
id|precision
comma
id|flags
)paren
suffix:semicolon
)brace
op_star
id|str
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
id|str
op_minus
id|buf
suffix:semicolon
)brace
DECL|function|sprintf
r_int
id|sprintf
c_func
(paren
r_char
op_star
id|buf
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
r_int
id|i
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|i
op_assign
id|vsprintf
c_func
(paren
id|buf
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
DECL|variable|sprint_buf
r_static
r_char
id|sprint_buf
(braket
l_int|1024
)braket
suffix:semicolon
r_void
DECL|function|printk
id|printk
c_func
(paren
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
r_int
id|n
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|n
op_assign
id|vsprintf
c_func
(paren
id|sprint_buf
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
id|write
c_func
(paren
id|stdout
comma
id|sprint_buf
comma
id|n
)paren
suffix:semicolon
)brace
r_int
DECL|function|printf
id|printf
c_func
(paren
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
r_int
id|n
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|n
op_assign
id|vsprintf
c_func
(paren
id|sprint_buf
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
id|write
c_func
(paren
id|stdout
comma
id|sprint_buf
comma
id|n
)paren
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
eof