multiline_comment|/*&n; * ARM/ARM26 default IDE host driver&n; *&n; * Copyright (C) 2004 Bartlomiej Zolnierkiewicz&n; * Based on code by: Russell King, Ian Molton and Alexander Schulz.&n; *&n; * May be copied or modified under the terms of the GNU General Public License.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#ifdef CONFIG_ARM26
DECL|macro|IDE_ARM_HOST
macro_line|# define IDE_ARM_HOST&t;(machine_is_a5k())
macro_line|#else
DECL|macro|IDE_ARM_HOST
macro_line|# define IDE_ARM_HOST&t;(1)
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_CLPS7500
macro_line|# include &lt;asm/arch/hardware.h&gt;
macro_line|#
DECL|macro|IDE_ARM_IO
macro_line|# define IDE_ARM_IO&t;(ISASLOT_IO + 0x1f0)
DECL|macro|IDE_ARM_IRQ
macro_line|# define IDE_ARM_IRQ&t;IRQ_ISA_14
macro_line|#else
DECL|macro|IDE_ARM_IO
macro_line|# define IDE_ARM_IO&t;0x1f0
DECL|macro|IDE_ARM_IRQ
macro_line|# define IDE_ARM_IRQ&t;IRQ_HARDDISK
macro_line|#endif
DECL|function|ide_arm_init
r_void
id|__init
id|ide_arm_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|IDE_ARM_HOST
)paren
(brace
id|hw_regs_t
id|hw
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|hw
comma
l_int|0
comma
r_sizeof
(paren
id|hw
)paren
)paren
suffix:semicolon
id|ide_std_init_ports
c_func
(paren
op_amp
id|hw
comma
id|IDE_ARM_IO
comma
id|IDE_ARM_IO
op_plus
l_int|0x206
)paren
suffix:semicolon
id|hw.irq
op_assign
id|IDE_ARM_IRQ
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
)brace
eof
