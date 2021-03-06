multiline_comment|/*&n; *  linux/arch/arm/kernel/isa.c&n; *&n; *  Copyright (C) 1999 Phil Blundell&n; *&n; *  ISA shared memory and I/O port support&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
multiline_comment|/* &n; * Nothing about this is actually ARM specific.  One day we could move&n; * it into kernel/resource.c or some place like that.  &n; */
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;linux/init.h&gt;
DECL|variable|isa_membase
DECL|variable|isa_portbase
DECL|variable|isa_portshift
r_static
r_int
r_int
id|isa_membase
comma
id|isa_portbase
comma
id|isa_portshift
suffix:semicolon
DECL|variable|ctl_isa_vars
r_static
id|ctl_table
id|ctl_isa_vars
(braket
l_int|4
)braket
op_assign
(brace
(brace
id|BUS_ISA_MEM_BASE
comma
l_string|&quot;membase&quot;
comma
op_amp
id|isa_membase
comma
r_sizeof
(paren
id|isa_membase
)paren
comma
l_int|0444
comma
l_int|NULL
comma
op_amp
id|proc_dointvec
)brace
comma
(brace
id|BUS_ISA_PORT_BASE
comma
l_string|&quot;portbase&quot;
comma
op_amp
id|isa_portbase
comma
r_sizeof
(paren
id|isa_portbase
)paren
comma
l_int|0444
comma
l_int|NULL
comma
op_amp
id|proc_dointvec
)brace
comma
(brace
id|BUS_ISA_PORT_SHIFT
comma
l_string|&quot;portshift&quot;
comma
op_amp
id|isa_portshift
comma
r_sizeof
(paren
id|isa_portshift
)paren
comma
l_int|0444
comma
l_int|NULL
comma
op_amp
id|proc_dointvec
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|isa_sysctl_header
r_static
r_struct
id|ctl_table_header
op_star
id|isa_sysctl_header
suffix:semicolon
DECL|variable|ctl_isa
r_static
id|ctl_table
id|ctl_isa
(braket
l_int|2
)braket
op_assign
(brace
(brace
id|CTL_BUS_ISA
comma
l_string|&quot;isa&quot;
comma
l_int|NULL
comma
l_int|0
comma
l_int|0555
comma
id|ctl_isa_vars
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|ctl_bus
r_static
id|ctl_table
id|ctl_bus
(braket
l_int|2
)braket
op_assign
(brace
(brace
id|CTL_BUS
comma
l_string|&quot;bus&quot;
comma
l_int|NULL
comma
l_int|0
comma
l_int|0555
comma
id|ctl_isa
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
r_void
id|__init
DECL|function|register_isa_ports
id|register_isa_ports
c_func
(paren
r_int
r_int
id|membase
comma
r_int
r_int
id|portbase
comma
r_int
r_int
id|portshift
)paren
(brace
id|isa_membase
op_assign
id|membase
suffix:semicolon
id|isa_portbase
op_assign
id|portbase
suffix:semicolon
id|isa_portshift
op_assign
id|portshift
suffix:semicolon
id|isa_sysctl_header
op_assign
id|register_sysctl_table
c_func
(paren
id|ctl_bus
comma
l_int|0
)paren
suffix:semicolon
)brace
eof
