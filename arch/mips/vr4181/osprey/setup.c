multiline_comment|/*&n; * linux/arch/mips/vr4181/setup.c&n; *&n; * VR41xx setup routines&n; *&n; * Copyright (C) 1999 Bradley D. LaRonde&n; * Copyright (C) 1999, 2000 Michael Klar&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; * Author: jsun@mvista.com or jsun@junsun.net&n; * Copyright (C) 2005 Ralf Baechle (ralf@linux-mips.org)&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; */
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/reboot.h&gt;
macro_line|#include &lt;asm/vr4181/vr4181.h&gt;
macro_line|#include &lt;asm/io.h&gt;
r_extern
r_void
id|nec_osprey_restart
c_func
(paren
r_char
op_star
id|c
)paren
suffix:semicolon
r_extern
r_void
id|nec_osprey_halt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|nec_osprey_power_off
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|vr4181_init_serial
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|vr4181_init_time
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|nec_osprey_setup
r_static
r_void
id|__init
id|nec_osprey_setup
c_func
(paren
r_void
)paren
(brace
id|set_io_port_base
c_func
(paren
id|VR4181_PORT_BASE
)paren
suffix:semicolon
id|isa_slot_offset
op_assign
id|VR4181_ISAMEM_BASE
suffix:semicolon
id|vr4181_init_serial
c_func
(paren
)paren
suffix:semicolon
id|vr4181_init_time
c_func
(paren
)paren
suffix:semicolon
id|_machine_restart
op_assign
id|nec_osprey_restart
suffix:semicolon
id|_machine_halt
op_assign
id|nec_osprey_halt
suffix:semicolon
id|_machine_power_off
op_assign
id|nec_osprey_power_off
suffix:semicolon
multiline_comment|/* setup resource limit */
id|ioport_resource.end
op_assign
l_int|0xffffffff
suffix:semicolon
id|iomem_resource.end
op_assign
l_int|0xffffffff
suffix:semicolon
multiline_comment|/* [jsun] hack */
multiline_comment|/*&n;&t;printk(&quot;[jsun] hack to change external ISA control register, %x -&gt; %x&bslash;n&quot;,&n;&t;&t;(*VR4181_XISACTL),&n;&t;&t;(*VR4181_XISACTL) | 0x2);&n;&t;*VR4181_XISACTL |= 0x2;&n;&t;*/
singleline_comment|// *VR4181_GPHIBSTH = 0x2000;
singleline_comment|// *VR4181_GPMD0REG = 0x00c0;
singleline_comment|// *VR4181_GPINTEN&t; = 1&lt;&lt;6;
multiline_comment|/* [jsun] I believe this will get the interrupt type right&n;&t; * for the ether port.&n;&t; */
op_star
id|VR4181_GPINTTYPL
op_assign
l_int|0x3000
suffix:semicolon
)brace
DECL|variable|nec_osprey_setup
id|early_initcall
c_func
(paren
id|nec_osprey_setup
)paren
suffix:semicolon
eof
