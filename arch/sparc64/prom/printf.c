multiline_comment|/*&n; * printf.c:  Internal prom library printf facility.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 1997 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; * Copyright (c) 2002 Pete Zaitcev (zaitcev@yahoo.com)&n; *&n; * We used to warn all over the code: DO NOT USE prom_printf(),&n; * and yet people do. Anton&squot;s banking code was outputing banks&n; * with prom_printf for most of the 2.4 lifetime. Since an effective&n; * stick is not available, we deployed a carrot: an early printk&n; * through PROM by means of -p boot option. This ought to fix it.&n; * USE printk; if you need, deploy -p.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/openprom.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
DECL|variable|ppbuf
r_static
r_char
id|ppbuf
(braket
l_int|1024
)braket
suffix:semicolon
r_void
DECL|function|prom_write
id|prom_write
c_func
(paren
r_const
r_char
op_star
id|buf
comma
r_int
r_int
id|n
)paren
(brace
r_char
id|ch
suffix:semicolon
r_while
c_loop
(paren
id|n
op_ne
l_int|0
)paren
(brace
op_decrement
id|n
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ch
op_assign
op_star
id|buf
op_increment
)paren
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|prom_putchar
c_func
(paren
l_char|&squot;&bslash;r&squot;
)paren
suffix:semicolon
id|prom_putchar
c_func
(paren
id|ch
)paren
suffix:semicolon
)brace
)brace
r_void
DECL|function|prom_printf
id|prom_printf
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
id|vsnprintf
c_func
(paren
id|ppbuf
comma
r_sizeof
(paren
id|ppbuf
)paren
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
id|prom_write
c_func
(paren
id|ppbuf
comma
id|i
)paren
suffix:semicolon
)brace
eof
