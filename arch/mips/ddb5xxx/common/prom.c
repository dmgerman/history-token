multiline_comment|/***********************************************************************&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; * Author: jsun@mvista.com or jsun@junsun.net&n; *&n; * arch/mips/ddb5xxx/common/prom.c&n; *     prom.c file.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; ***********************************************************************&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/ddb5xxx/ddb5xxx.h&gt;
DECL|variable|arcs_cmdline
r_char
id|arcs_cmdline
(braket
id|COMMAND_LINE_SIZE
)braket
suffix:semicolon
multiline_comment|/* [jsun@junsun.net] PMON passes arguments in C main() style */
DECL|function|prom_init
r_void
id|__init
id|prom_init
c_func
(paren
r_int
id|argc
comma
r_const
r_char
op_star
op_star
id|arg
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* arg[0] is &quot;g&quot;, the rest is boot parameters */
id|arcs_cmdline
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
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
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|arcs_cmdline
)paren
op_plus
id|strlen
c_func
(paren
id|arg
(braket
id|i
)braket
op_plus
l_int|1
)paren
op_ge
r_sizeof
(paren
id|arcs_cmdline
)paren
)paren
r_break
suffix:semicolon
id|strcat
c_func
(paren
id|arcs_cmdline
comma
id|arg
(braket
id|i
)braket
)paren
suffix:semicolon
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
id|MACH_GROUP_NEC_DDB
suffix:semicolon
macro_line|#if defined(CONFIG_DDB5074)
id|mips_machtype
op_assign
id|MACH_NEC_DDB5074
suffix:semicolon
macro_line|#elif defined(CONFIG_DDB5476)
id|mips_machtype
op_assign
id|MACH_NEC_DDB5476
suffix:semicolon
macro_line|#elif defined(CONFIG_DDB5477)
id|mips_machtype
op_assign
id|MACH_NEC_DDB5477
suffix:semicolon
macro_line|#endif
id|add_memory_region
c_func
(paren
l_int|0
comma
id|DDB_SDRAM_SIZE
comma
id|BOOT_MEM_RAM
)paren
suffix:semicolon
)brace
DECL|function|prom_free_prom_memory
r_void
id|__init
id|prom_free_prom_memory
c_func
(paren
r_void
)paren
(brace
)brace
eof
