multiline_comment|/*&n; * FILE NAME&n; *&t;arch/mips/vr41xx/tanbac-tb0226/init.c&n; *&n; * BRIEF MODULE DESCRIPTION&n; *&t;Initialisation code for the TANBAC TB0226.&n; *&n; * Copyright 2002,2003 Yoichi Yuasa&n; *                yuasa@hh.iij4u.or.jp&n; *&n; *  This program is free software; you can redistribute it and/or modify it&n; *  under the terms of the GNU General Public License as published by the&n; *  Free Software Foundation; either version 2 of the License, or (at your&n; *  option) any later version.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/vr41xx/vr41xx.h&gt;
DECL|function|get_system_type
r_const
r_char
op_star
id|get_system_type
c_func
(paren
r_void
)paren
(brace
r_return
l_string|&quot;TANBAC TB0226&quot;
suffix:semicolon
)brace
DECL|function|prom_init
r_void
id|__init
id|prom_init
c_func
(paren
r_void
)paren
(brace
r_int
id|argc
op_assign
id|fw_arg0
suffix:semicolon
r_char
op_star
op_star
id|argv
op_assign
(paren
r_char
op_star
op_star
)paren
id|fw_arg1
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * collect args and prepare cmd_line&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|argc
suffix:semicolon
id|i
op_increment
)paren
(brace
id|strcat
c_func
(paren
id|arcs_cmdline
comma
id|argv
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
(paren
id|argc
op_minus
l_int|1
)paren
)paren
id|strcat
c_func
(paren
id|arcs_cmdline
comma
l_string|&quot; &quot;
)paren
suffix:semicolon
)brace
id|mips_machgroup
op_assign
id|MACH_GROUP_NEC_VR41XX
suffix:semicolon
id|mips_machtype
op_assign
id|MACH_TANBAC_TB0226
suffix:semicolon
)brace
DECL|function|prom_free_prom_memory
r_int
r_int
id|__init
id|prom_free_prom_memory
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
eof
