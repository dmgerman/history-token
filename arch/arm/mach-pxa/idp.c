multiline_comment|/*&n; *  linux/arch/arm/mach-pxa/idp.c&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License version 2 as&n; *  published by the Free Software Foundation.&n; *&n; *  Copyright (c) 2001 Cliff Brake, Accelent Systems Inc.&n; *&n; *  2001-09-13: Cliff Brake &lt;cbrake@accelent.com&gt;&n; *              Initial code&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/memory.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &quot;generic.h&quot;
DECL|macro|PXA_IDP_REV02
mdefine_line|#define PXA_IDP_REV02
macro_line|#ifndef PXA_IDP_REV02
multiline_comment|/* shadow registers for write only registers */
DECL|variable|idp_cpld_led_control_shadow
r_int
r_int
id|idp_cpld_led_control_shadow
op_assign
l_int|0x1
suffix:semicolon
DECL|variable|idp_cpld_periph_pwr_shadow
r_int
r_int
id|idp_cpld_periph_pwr_shadow
op_assign
l_int|0xd
suffix:semicolon
DECL|variable|ipd_cpld_cir_shadow
r_int
r_int
id|ipd_cpld_cir_shadow
op_assign
l_int|0
suffix:semicolon
DECL|variable|idp_cpld_kb_col_high_shadow
r_int
r_int
id|idp_cpld_kb_col_high_shadow
op_assign
l_int|0
suffix:semicolon
DECL|variable|idp_cpld_kb_col_low_shadow
r_int
r_int
id|idp_cpld_kb_col_low_shadow
op_assign
l_int|0
suffix:semicolon
DECL|variable|idp_cpld_pccard_en_shadow
r_int
r_int
id|idp_cpld_pccard_en_shadow
op_assign
l_int|0xC3
suffix:semicolon
DECL|variable|idp_cpld_gpioh_dir_shadow
r_int
r_int
id|idp_cpld_gpioh_dir_shadow
op_assign
l_int|0
suffix:semicolon
DECL|variable|idp_cpld_gpioh_value_shadow
r_int
r_int
id|idp_cpld_gpioh_value_shadow
op_assign
l_int|0
suffix:semicolon
DECL|variable|idp_cpld_gpiol_dir_shadow
r_int
r_int
id|idp_cpld_gpiol_dir_shadow
op_assign
l_int|0
suffix:semicolon
DECL|variable|idp_cpld_gpiol_value_shadow
r_int
r_int
id|idp_cpld_gpiol_value_shadow
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * enable all LCD signals -- they should still be on&n; * write protect flash&n; * enable all serial port transceivers&n; */
DECL|variable|idp_control_port_shadow
r_int
r_int
id|idp_control_port_shadow
op_assign
(paren
(paren
l_int|0x7
op_lshift
l_int|21
)paren
op_or
multiline_comment|/* LCD power */
(paren
l_int|0x1
op_lshift
l_int|19
)paren
op_or
multiline_comment|/* disable flash write enable */
(paren
l_int|0x7
op_lshift
l_int|9
)paren
)paren
suffix:semicolon
multiline_comment|/* enable serial port transeivers */
macro_line|#endif
DECL|function|idp_init
r_static
r_int
id|__init
id|idp_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;idp_init()&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|idp_init
id|__initcall
c_func
(paren
id|idp_init
)paren
suffix:semicolon
DECL|function|idp_init_irq
r_static
r_void
id|__init
id|idp_init_irq
c_func
(paren
r_void
)paren
(brace
id|pxa_init_irq
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|idp_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* virtual     physical    length      domain     r  w  c  b */
macro_line|#ifndef PXA_IDP_REV02
(brace
id|IDP_CTRL_PORT_BASE
comma
id|IDP_CTRL_PORT_PHYS
comma
id|IDP_CTRL_PORT_SIZE
comma
id|DOMAIN_IO
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
macro_line|#endif
(brace
id|IDP_IDE_BASE
comma
id|IDP_IDE_PHYS
comma
id|IDP_IDE_SIZE
comma
id|DOMAIN_IO
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
id|IDP_ETH_BASE
comma
id|IDP_ETH_PHYS
comma
id|IDP_ETH_SIZE
comma
id|DOMAIN_IO
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
id|IDP_COREVOLT_BASE
comma
id|IDP_COREVOLT_PHYS
comma
id|IDP_COREVOLT_SIZE
comma
id|DOMAIN_IO
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
id|IDP_CPLD_BASE
comma
id|IDP_CPLD_PHYS
comma
id|IDP_CPLD_SIZE
comma
id|DOMAIN_IO
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
id|LAST_DESC
)brace
suffix:semicolon
DECL|function|idp_map_io
r_static
r_void
id|__init
id|idp_map_io
c_func
(paren
r_void
)paren
(brace
id|pxa_map_io
c_func
(paren
)paren
suffix:semicolon
id|iotable_init
c_func
(paren
id|idp_io_desc
)paren
suffix:semicolon
id|set_GPIO_IRQ_edge
c_func
(paren
id|IRQ_TO_GPIO_2_80
c_func
(paren
id|TOUCH_PANEL_IRQ
)paren
comma
id|TOUCH_PANEL_IRQ_EDGE
)paren
suffix:semicolon
)brace
id|MACHINE_START
c_func
(paren
id|PXA_IDP
comma
l_string|&quot;Accelent Xscale IDP&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Accelent Systems Inc.&quot;
)paren
id|BOOT_MEM
c_func
(paren
l_int|0xa0000000
comma
l_int|0x40000000
comma
l_int|0xfc000000
)paren
id|MAPIO
c_func
(paren
id|idp_map_io
)paren
id|INITIRQ
c_func
(paren
id|idp_init_irq
)paren
id|MACHINE_END
eof