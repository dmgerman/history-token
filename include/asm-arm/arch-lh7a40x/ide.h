multiline_comment|/* include/asm-arm/arch-lh7a40x/ide.h&n; *&n; *  Copyright (C) 2004 Logic Product Development&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  version 2 as published by the Free Software Foundation.&n; *&n; */
macro_line|#ifndef __ASM_ARCH_IDE_H
DECL|macro|__ASM_ARCH_IDE_H
mdefine_line|#define __ASM_ARCH_IDE_H
macro_line|#if defined (CONFIG_MACH_LPD7A400) || defined (CONFIG_MACH_LPD7A404)
multiline_comment|/*  This implementation of ide.h only applies to the LPD CardEngines.&n; *  Thankfully, there is less to do for the KEV.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/arch/registers.h&gt;
DECL|macro|IDE_REG_LINE
mdefine_line|#define IDE_REG_LINE&t;(1&lt;&lt;12)&t;/* A12 drives !REG  */
DECL|macro|IDE_ALT_LINE
mdefine_line|#define IDE_ALT_LINE&t;(1&lt;&lt;11)&t;/* Unused A11 allows non-overlapping regions */
DECL|macro|IDE_CONTROLREG_OFFSET
mdefine_line|#define IDE_CONTROLREG_OFFSET&t;(0xe)
r_void
id|lpd7a40x_hwif_ioops
(paren
r_struct
id|hwif_s
op_star
id|hwif
)paren
suffix:semicolon
DECL|function|ide_init_hwif_ports
r_static
id|__inline__
r_void
id|ide_init_hwif_ports
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
l_int|1
suffix:semicolon
id|memset
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
id|IDE_NO_IRQ
suffix:semicolon
)brace
DECL|function|ide_init_default_hwifs
r_static
id|__inline__
r_void
id|ide_init_default_hwifs
(paren
r_void
)paren
(brace
id|hw_regs_t
id|hw
suffix:semicolon
r_struct
id|hwif_s
op_star
id|hwif
suffix:semicolon
id|ide_init_hwif_ports
(paren
op_amp
id|hw
comma
id|CF_VIRT
op_plus
id|IDE_REG_LINE
comma
id|CF_VIRT
op_plus
id|IDE_REG_LINE
op_plus
id|IDE_ALT_LINE
op_plus
id|IDE_CONTROLREG_OFFSET
comma
l_int|NULL
)paren
suffix:semicolon
id|ide_register_hw
(paren
op_amp
id|hw
comma
op_amp
id|hwif
)paren
suffix:semicolon
id|lpd7a40x_hwif_ioops
(paren
id|hwif
)paren
suffix:semicolon
multiline_comment|/* Override IO routines */
)brace
macro_line|#endif
macro_line|#endif
eof
