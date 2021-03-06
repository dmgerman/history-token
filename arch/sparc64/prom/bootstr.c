multiline_comment|/* $Id: bootstr.c,v 1.6 1999/08/31 06:55:01 davem Exp $&n; * bootstr.c:  Boot string/argument acquisition from the PROM.&n; *&n; * Copyright(C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright(C) 1996,1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; */
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
multiline_comment|/* WARNING: The boot loader knows that these next three variables come one right&n; *          after another in the .data section.  Do not move this stuff into&n; *          the .bss section or it will break things.&n; */
DECL|macro|BARG_LEN
mdefine_line|#define BARG_LEN  256
r_struct
(brace
DECL|member|bootstr_len
r_int
id|bootstr_len
suffix:semicolon
DECL|member|bootstr_valid
r_int
id|bootstr_valid
suffix:semicolon
DECL|member|bootstr_buf
r_char
id|bootstr_buf
(braket
id|BARG_LEN
)braket
suffix:semicolon
DECL|variable|bootstr_info
)brace
id|bootstr_info
op_assign
(brace
dot
id|bootstr_len
op_assign
id|BARG_LEN
comma
macro_line|#ifdef CONFIG_CMDLINE
dot
id|bootstr_valid
op_assign
l_int|1
comma
dot
id|bootstr_buf
op_assign
id|CONFIG_CMDLINE
comma
macro_line|#endif
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
id|bootstr_info.bootstr_valid
)paren
r_return
id|bootstr_info.bootstr_buf
suffix:semicolon
id|prom_getstring
c_func
(paren
id|prom_chosen_node
comma
l_string|&quot;bootargs&quot;
comma
id|bootstr_info.bootstr_buf
comma
id|BARG_LEN
)paren
suffix:semicolon
id|bootstr_info.bootstr_valid
op_assign
l_int|1
suffix:semicolon
r_return
id|bootstr_info.bootstr_buf
suffix:semicolon
)brace
eof
