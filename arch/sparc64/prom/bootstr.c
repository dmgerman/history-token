multiline_comment|/* $Id: bootstr.c,v 1.6 1999/08/31 06:55:01 davem Exp $&n; * bootstr.c:  Boot string/argument acquisition from the PROM.&n; *&n; * Copyright(C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright(C) 1996,1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; */
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
multiline_comment|/* WARNING: The boot loader knows that these next three variables come one right&n; *          after another in the .data section.  Do not move this stuff into&n; *          the .bss section or it will break things.&n; */
DECL|macro|BARG_LEN
mdefine_line|#define BARG_LEN  256
DECL|variable|bootstr_len
r_int
id|bootstr_len
op_assign
id|BARG_LEN
suffix:semicolon
DECL|variable|bootstr_valid
r_static
r_int
id|bootstr_valid
op_assign
l_int|0
suffix:semicolon
DECL|variable|bootstr_buf
r_static
r_char
id|bootstr_buf
(braket
id|BARG_LEN
)braket
op_assign
(brace
l_int|0
)brace
suffix:semicolon
r_char
op_star
id|__init
DECL|function|prom_getbootargs
id|prom_getbootargs
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* This check saves us from a panic when bootfd patches args. */
r_if
c_cond
(paren
id|bootstr_valid
)paren
r_return
id|bootstr_buf
suffix:semicolon
id|prom_getstring
c_func
(paren
id|prom_chosen_node
comma
l_string|&quot;bootargs&quot;
comma
id|bootstr_buf
comma
id|BARG_LEN
)paren
suffix:semicolon
id|bootstr_valid
op_assign
l_int|1
suffix:semicolon
r_return
id|bootstr_buf
suffix:semicolon
)brace
eof
