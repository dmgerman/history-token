multiline_comment|/*&n; * Copyright 2001 MontaVista Software Inc.&n; * Author: jsun@mvista.com or jsun@junsun.net&n; *&n; * arch/mips/vr4181/osprey/prom.c&n; *     prom code for osprey.&n; *&n; * This program is free software; you can redistribute&t;it and/or modify it&n; * under  the terms of&t;the GNU General&t; Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
DECL|variable|arcs_cmdline
r_char
id|arcs_cmdline
(braket
id|CL_SIZE
)braket
suffix:semicolon
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
l_string|&quot;NEC_Vr41xx Osprey&quot;
suffix:semicolon
)brace
multiline_comment|/*&n; * [jsun] right now we assume it is the nec debug monitor, which does&n; * not pass any arguments.&n; */
DECL|function|prom_init
r_void
id|__init
id|prom_init
c_func
(paren
)paren
(brace
id|strcpy
c_func
(paren
id|arcs_cmdline
comma
l_string|&quot;ip=bootp &quot;
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|arcs_cmdline
comma
l_string|&quot;ether=46,0x03fe0300,eth0 &quot;
)paren
suffix:semicolon
singleline_comment|// strcpy(arcs_cmdline, &quot;ether=0,0x0300,eth0 &quot;
singleline_comment|// strcat(arcs_cmdline, &quot;video=vr4181fb:xres:240,yres:320,bpp:8 &quot;);
id|mips_machgroup
op_assign
id|MACH_GROUP_NEC_VR41XX
suffix:semicolon
id|mips_machtype
op_assign
id|MACH_NEC_OSPREY
suffix:semicolon
multiline_comment|/* 16MB fixed */
id|add_memory_region
c_func
(paren
l_int|0
comma
l_int|16
op_lshift
l_int|20
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
DECL|function|prom_fixup_mem_map
r_void
id|__init
id|prom_fixup_mem_map
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
(brace
)brace
eof
