macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
r_extern
r_void
id|prom_putchar
c_func
(paren
r_char
)paren
suffix:semicolon
DECL|function|prom_printf
r_void
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
r_char
id|ppbuf
(braket
l_int|1024
)braket
suffix:semicolon
r_char
op_star
id|bptr
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|vsprintf
c_func
(paren
id|ppbuf
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
id|bptr
op_assign
id|ppbuf
suffix:semicolon
r_while
c_loop
(paren
op_star
id|bptr
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_star
id|bptr
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
op_star
id|bptr
op_increment
)paren
suffix:semicolon
)brace
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
)brace
eof
