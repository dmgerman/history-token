multiline_comment|/*&n; *  linux/include/asm-arm/arch-rpc/ide.h&n; *&n; *  Copyright (C) 1997 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Modifications:&n; *   29-07-1998&t;RMK&t;Major re-work of IDE architecture specific code&n; */
macro_line|#include &lt;asm/irq.h&gt;
multiline_comment|/*&n; * Set up a hw structure for a specified data port, control port and IRQ.&n; * This should follow whatever the default interface uses.&n; */
r_static
id|__inline__
r_void
DECL|function|ide_init_hwif_ports
id|ide_init_hwif_ports
c_func
(paren
id|hw_regs_t
op_star
id|hw
comma
r_int
id|data_port
comma
r_int
id|ctrl_port
comma
r_int
op_star
id|irq
)paren
(brace
id|ide_ioreg_t
id|reg
op_assign
(paren
id|ide_ioreg_t
)paren
id|data_port
suffix:semicolon
r_int
id|i
suffix:semicolon
id|memset
c_func
(paren
id|hw
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|hw
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|IDE_DATA_OFFSET
suffix:semicolon
id|i
op_le
id|IDE_STATUS_OFFSET
suffix:semicolon
id|i
op_increment
)paren
(brace
id|hw-&gt;io_ports
(braket
id|i
)braket
op_assign
id|reg
suffix:semicolon
id|reg
op_add_assign
l_int|1
suffix:semicolon
)brace
id|hw-&gt;io_ports
(braket
id|IDE_CONTROL_OFFSET
)braket
op_assign
(paren
id|ide_ioreg_t
)paren
id|ctrl_port
suffix:semicolon
r_if
c_cond
(paren
id|irq
)paren
op_star
id|irq
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This registers the standard ports for this architecture with the IDE&n; * driver.&n; */
r_static
id|__inline__
r_void
DECL|function|ide_init_default_hwifs
id|ide_init_default_hwifs
c_func
(paren
r_void
)paren
(brace
id|hw_regs_t
id|hw
suffix:semicolon
id|ide_init_hwif_ports
c_func
(paren
op_amp
id|hw
comma
l_int|0x1f0
comma
l_int|0x3f6
comma
l_int|NULL
)paren
suffix:semicolon
id|hw.irq
op_assign
id|IRQ_HARDDISK
suffix:semicolon
id|ide_register_hw
c_func
(paren
op_amp
id|hw
comma
l_int|NULL
)paren
suffix:semicolon
)brace
eof
