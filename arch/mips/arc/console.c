multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996 David S. Miller (dm@sgi.com)&n; * Compability with board caches, Ulf Carlsson&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/sgialib.h&gt;
macro_line|#include &lt;asm/bcache.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#ifdef CONFIG_ARC_CONSOLE
DECL|macro|__init
mdefine_line|#define __init
macro_line|#endif
multiline_comment|/*&n; * IP22 boardcache is not compatible with board caches.  Thus we disable it&n; * during romvec action.  Since r4xx0.c is always compiled and linked with your&n; * kernel, this shouldn&squot;t cause any harm regardless what MIPS processor you&n; * have.&n; *&n; * The ARC write and read functions seem to interfere with the serial lines&n; * in some way. You should be careful with them.&n; */
DECL|function|prom_putchar
r_void
id|__init
id|prom_putchar
c_func
(paren
r_char
id|c
)paren
(brace
r_int
id|cnt
suffix:semicolon
r_char
id|it
op_assign
id|c
suffix:semicolon
id|bc_disable
c_func
(paren
)paren
suffix:semicolon
id|romvec
op_member_access_from_pointer
id|write
c_func
(paren
l_int|1
comma
op_amp
id|it
comma
l_int|1
comma
op_amp
id|cnt
)paren
suffix:semicolon
id|bc_enable
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|prom_getchar
r_char
id|__init
id|prom_getchar
c_func
(paren
r_void
)paren
(brace
r_int
id|cnt
suffix:semicolon
r_char
id|c
suffix:semicolon
id|bc_disable
c_func
(paren
)paren
suffix:semicolon
id|romvec
op_member_access_from_pointer
id|read
c_func
(paren
l_int|0
comma
op_amp
id|c
comma
l_int|1
comma
op_amp
id|cnt
)paren
suffix:semicolon
id|bc_enable
c_func
(paren
)paren
suffix:semicolon
r_return
id|c
suffix:semicolon
)brace
DECL|variable|ppbuf
r_static
r_char
id|ppbuf
(braket
l_int|1024
)braket
suffix:semicolon
DECL|function|prom_printf
r_void
id|__init
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
id|ch
comma
op_star
id|bptr
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
(paren
id|ch
op_assign
op_star
(paren
id|bptr
op_increment
)paren
)paren
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|ch
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
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|arc_console_write
id|arc_console_write
c_func
(paren
r_struct
id|console
op_star
id|con
comma
r_const
r_char
op_star
id|s
comma
r_int
id|n
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;%s&quot;
comma
id|s
)paren
suffix:semicolon
)brace
r_static
id|kdev_t
DECL|function|arc_console_dev
id|arc_console_dev
c_func
(paren
r_struct
id|console
op_star
id|c
)paren
(brace
r_return
id|MKDEV
c_func
(paren
id|TTY_MAJOR
comma
l_int|64
op_plus
id|c-&gt;index
)paren
suffix:semicolon
)brace
DECL|variable|arc_prom_console
r_static
r_struct
id|console
id|arc_prom_console
op_assign
(brace
id|name
suffix:colon
l_string|&quot;prom&quot;
comma
id|write
suffix:colon
id|arc_console_write
comma
id|device
suffix:colon
id|arc_console_dev
comma
id|flags
suffix:colon
id|CON_PRINTBUFFER
comma
id|index
suffix:colon
op_minus
l_int|1
comma
)brace
suffix:semicolon
DECL|function|arc_setup_console
id|__init
r_void
id|arc_setup_console
c_func
(paren
r_void
)paren
(brace
id|register_console
c_func
(paren
op_amp
id|arc_prom_console
)paren
suffix:semicolon
)brace
eof
