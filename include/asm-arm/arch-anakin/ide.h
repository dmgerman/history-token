multiline_comment|/*&n; * linux/include/asm-arm/arch-anakin/ide.h&n; *&n; * Copyright 2001 Blue Mug Inc. for Acunia N.V.&n; *&n; * 08-jun-2001: Initial clone of arch-sa1100/ide.h by Jon McClintock&n; *              (jonm@bluemug.com).&n; */
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
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
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|regincr
op_assign
l_int|4
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
id|reg
op_assign
(paren
id|ide_ioreg_t
)paren
id|data_port
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
id|regincr
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
id|IO_BASE
op_plus
id|COMPACTFLASH
comma
id|IO_BASE
op_plus
id|COMPACTFLASH
op_plus
id|IDE_CONTROL_OFFSET
comma
l_int|NULL
)paren
suffix:semicolon
id|hw.irq
op_assign
id|IRQ_COMPACTFLASH
suffix:semicolon
id|ide_register_hw
c_func
(paren
op_amp
id|hw
)paren
suffix:semicolon
)brace
eof
