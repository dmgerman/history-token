multiline_comment|/*&n; * arch/ppc/platform/85xx/mpc8555.c&n; *&n; * MPC8555 I/O descriptions&n; *&n; * Maintainer: Kumar Gala &lt;kumar.gala@freescale.com&gt;&n; *&n; * Copyright 2004 Freescale Semiconductor Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/mpc85xx.h&gt;
macro_line|#include &lt;asm/ocp.h&gt;
multiline_comment|/* These should be defined in platform code */
r_extern
r_struct
id|ocp_gfar_data
id|mpc85xx_tsec1_def
suffix:semicolon
r_extern
r_struct
id|ocp_gfar_data
id|mpc85xx_tsec2_def
suffix:semicolon
r_extern
r_struct
id|ocp_mpc_i2c_data
id|mpc85xx_i2c1_def
suffix:semicolon
multiline_comment|/* We use offsets for paddr since we do not know at compile time&n; * what CCSRBAR is, platform code should fix this up in&n; * setup_arch&n; *&n; * Only the first IRQ is given even if a device has&n; * multiple lines associated with ita&n; */
DECL|variable|core_ocp
r_struct
id|ocp_def
id|core_ocp
(braket
)braket
op_assign
(brace
(brace
dot
id|vendor
op_assign
id|OCP_VENDOR_FREESCALE
comma
dot
id|function
op_assign
id|OCP_FUNC_IIC
comma
dot
id|index
op_assign
l_int|0
comma
dot
id|paddr
op_assign
id|MPC85xx_IIC1_OFFSET
comma
dot
id|irq
op_assign
id|MPC85xx_IRQ_IIC1
comma
dot
id|pm
op_assign
id|OCP_CPM_NA
comma
dot
id|additions
op_assign
op_amp
id|mpc85xx_i2c1_def
comma
)brace
comma
(brace
dot
id|vendor
op_assign
id|OCP_VENDOR_FREESCALE
comma
dot
id|function
op_assign
id|OCP_FUNC_16550
comma
dot
id|index
op_assign
l_int|0
comma
dot
id|paddr
op_assign
id|MPC85xx_UART0_OFFSET
comma
dot
id|irq
op_assign
id|MPC85xx_IRQ_DUART
comma
dot
id|pm
op_assign
id|OCP_CPM_NA
comma
)brace
comma
(brace
dot
id|vendor
op_assign
id|OCP_VENDOR_FREESCALE
comma
dot
id|function
op_assign
id|OCP_FUNC_16550
comma
dot
id|index
op_assign
l_int|1
comma
dot
id|paddr
op_assign
id|MPC85xx_UART1_OFFSET
comma
dot
id|irq
op_assign
id|MPC85xx_IRQ_DUART
comma
dot
id|pm
op_assign
id|OCP_CPM_NA
comma
)brace
comma
(brace
dot
id|vendor
op_assign
id|OCP_VENDOR_FREESCALE
comma
dot
id|function
op_assign
id|OCP_FUNC_GFAR
comma
dot
id|index
op_assign
l_int|0
comma
dot
id|paddr
op_assign
id|MPC85xx_ENET1_OFFSET
comma
dot
id|irq
op_assign
id|MPC85xx_IRQ_TSEC1_TX
comma
dot
id|pm
op_assign
id|OCP_CPM_NA
comma
dot
id|additions
op_assign
op_amp
id|mpc85xx_tsec1_def
comma
)brace
comma
(brace
dot
id|vendor
op_assign
id|OCP_VENDOR_FREESCALE
comma
dot
id|function
op_assign
id|OCP_FUNC_GFAR
comma
dot
id|index
op_assign
l_int|1
comma
dot
id|paddr
op_assign
id|MPC85xx_ENET2_OFFSET
comma
dot
id|irq
op_assign
id|MPC85xx_IRQ_TSEC2_TX
comma
dot
id|pm
op_assign
id|OCP_CPM_NA
comma
dot
id|additions
op_assign
op_amp
id|mpc85xx_tsec2_def
comma
)brace
comma
(brace
dot
id|vendor
op_assign
id|OCP_VENDOR_FREESCALE
comma
dot
id|function
op_assign
id|OCP_FUNC_DMA
comma
dot
id|index
op_assign
l_int|0
comma
dot
id|paddr
op_assign
id|MPC85xx_DMA_OFFSET
comma
dot
id|irq
op_assign
id|MPC85xx_IRQ_DMA0
comma
dot
id|pm
op_assign
id|OCP_CPM_NA
comma
)brace
comma
(brace
dot
id|vendor
op_assign
id|OCP_VENDOR_FREESCALE
comma
dot
id|function
op_assign
id|OCP_FUNC_PERFMON
comma
dot
id|index
op_assign
l_int|0
comma
dot
id|paddr
op_assign
id|MPC85xx_PERFMON_OFFSET
comma
dot
id|irq
op_assign
id|MPC85xx_IRQ_PERFMON
comma
dot
id|pm
op_assign
id|OCP_CPM_NA
comma
)brace
comma
(brace
dot
id|vendor
op_assign
id|OCP_VENDOR_INVALID
)brace
)brace
suffix:semicolon
eof
