multiline_comment|/*&n; * arch/ppc/platforms/85xx/mpc85xx_devices.c&n; *&n; * MPC85xx Device descriptions&n; *&n; * Maintainer: Kumar Gala &lt;kumar.gala@freescale.com&gt;&n; *&n; * Copyright 2005 Freescale Semiconductor Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/serial_8250.h&gt;
macro_line|#include &lt;linux/fsl_devices.h&gt;
macro_line|#include &lt;asm/mpc85xx.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/ppc_sys.h&gt;
multiline_comment|/* We use offsets for IORESOURCE_MEM since we do not know at compile time&n; * what CCSRBAR is, will get fixed up by mach_mpc85xx_fixup&n; */
DECL|variable|mpc85xx_tsec1_pdata
r_static
r_struct
id|gianfar_platform_data
id|mpc85xx_tsec1_pdata
op_assign
(brace
dot
id|device_flags
op_assign
id|FSL_GIANFAR_DEV_HAS_GIGABIT
op_or
id|FSL_GIANFAR_DEV_HAS_COALESCE
op_or
id|FSL_GIANFAR_DEV_HAS_RMON
op_or
id|FSL_GIANFAR_DEV_HAS_MULTI_INTR
comma
dot
id|phy_reg_addr
op_assign
id|MPC85xx_ENET1_OFFSET
comma
)brace
suffix:semicolon
DECL|variable|mpc85xx_tsec2_pdata
r_static
r_struct
id|gianfar_platform_data
id|mpc85xx_tsec2_pdata
op_assign
(brace
dot
id|device_flags
op_assign
id|FSL_GIANFAR_DEV_HAS_GIGABIT
op_or
id|FSL_GIANFAR_DEV_HAS_COALESCE
op_or
id|FSL_GIANFAR_DEV_HAS_RMON
op_or
id|FSL_GIANFAR_DEV_HAS_MULTI_INTR
comma
dot
id|phy_reg_addr
op_assign
id|MPC85xx_ENET1_OFFSET
comma
)brace
suffix:semicolon
DECL|variable|mpc85xx_fec_pdata
r_static
r_struct
id|gianfar_platform_data
id|mpc85xx_fec_pdata
op_assign
(brace
dot
id|phy_reg_addr
op_assign
id|MPC85xx_ENET1_OFFSET
comma
)brace
suffix:semicolon
DECL|variable|mpc85xx_fsl_i2c_pdata
r_static
r_struct
id|fsl_i2c_platform_data
id|mpc85xx_fsl_i2c_pdata
op_assign
(brace
dot
id|device_flags
op_assign
id|FSL_I2C_DEV_SEPARATE_DFSRR
comma
)brace
suffix:semicolon
DECL|variable|serial_platform_data
r_static
r_struct
id|plat_serial8250_port
id|serial_platform_data
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
(brace
dot
id|mapbase
op_assign
l_int|0x4500
comma
dot
id|irq
op_assign
id|MPC85xx_IRQ_DUART
comma
dot
id|iotype
op_assign
id|UPIO_MEM
comma
dot
id|flags
op_assign
id|UPF_BOOT_AUTOCONF
op_or
id|UPF_SKIP_TEST
op_or
id|UPF_SHARE_IRQ
comma
)brace
comma
(braket
l_int|1
)braket
op_assign
(brace
dot
id|mapbase
op_assign
l_int|0x4600
comma
dot
id|irq
op_assign
id|MPC85xx_IRQ_DUART
comma
dot
id|iotype
op_assign
id|UPIO_MEM
comma
dot
id|flags
op_assign
id|UPF_BOOT_AUTOCONF
op_or
id|UPF_SKIP_TEST
op_or
id|UPF_SHARE_IRQ
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|ppc_sys_platform_devices
r_struct
id|platform_device
id|ppc_sys_platform_devices
(braket
)braket
op_assign
(brace
(braket
id|MPC85xx_TSEC1
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;fsl-gianfar&quot;
comma
dot
id|id
op_assign
l_int|1
comma
dot
id|dev.platform_data
op_assign
op_amp
id|mpc85xx_tsec1_pdata
comma
dot
id|num_resources
op_assign
l_int|4
comma
dot
id|resource
op_assign
(paren
r_struct
id|resource
(braket
)braket
)paren
(brace
(brace
dot
id|start
op_assign
id|MPC85xx_ENET1_OFFSET
comma
dot
id|end
op_assign
id|MPC85xx_ENET1_OFFSET
op_plus
id|MPC85xx_ENET1_SIZE
op_minus
l_int|1
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;tx&quot;
comma
dot
id|start
op_assign
id|MPC85xx_IRQ_TSEC1_TX
comma
dot
id|end
op_assign
id|MPC85xx_IRQ_TSEC1_TX
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;rx&quot;
comma
dot
id|start
op_assign
id|MPC85xx_IRQ_TSEC1_RX
comma
dot
id|end
op_assign
id|MPC85xx_IRQ_TSEC1_RX
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;error&quot;
comma
dot
id|start
op_assign
id|MPC85xx_IRQ_TSEC1_ERROR
comma
dot
id|end
op_assign
id|MPC85xx_IRQ_TSEC1_ERROR
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
comma
)brace
comma
)brace
comma
(braket
id|MPC85xx_TSEC2
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;fsl-gianfar&quot;
comma
dot
id|id
op_assign
l_int|2
comma
dot
id|dev.platform_data
op_assign
op_amp
id|mpc85xx_tsec2_pdata
comma
dot
id|num_resources
op_assign
l_int|4
comma
dot
id|resource
op_assign
(paren
r_struct
id|resource
(braket
)braket
)paren
(brace
(brace
dot
id|start
op_assign
id|MPC85xx_ENET2_OFFSET
comma
dot
id|end
op_assign
id|MPC85xx_ENET2_OFFSET
op_plus
id|MPC85xx_ENET2_SIZE
op_minus
l_int|1
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;tx&quot;
comma
dot
id|start
op_assign
id|MPC85xx_IRQ_TSEC2_TX
comma
dot
id|end
op_assign
id|MPC85xx_IRQ_TSEC2_TX
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;rx&quot;
comma
dot
id|start
op_assign
id|MPC85xx_IRQ_TSEC2_RX
comma
dot
id|end
op_assign
id|MPC85xx_IRQ_TSEC2_RX
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;error&quot;
comma
dot
id|start
op_assign
id|MPC85xx_IRQ_TSEC2_ERROR
comma
dot
id|end
op_assign
id|MPC85xx_IRQ_TSEC2_ERROR
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
comma
)brace
comma
)brace
comma
(braket
id|MPC85xx_FEC
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;fsl-gianfar&quot;
comma
dot
id|id
op_assign
l_int|3
comma
dot
id|dev.platform_data
op_assign
op_amp
id|mpc85xx_fec_pdata
comma
dot
id|num_resources
op_assign
l_int|2
comma
dot
id|resource
op_assign
(paren
r_struct
id|resource
(braket
)braket
)paren
(brace
(brace
dot
id|start
op_assign
id|MPC85xx_ENET3_OFFSET
comma
dot
id|end
op_assign
id|MPC85xx_ENET3_OFFSET
op_plus
id|MPC85xx_ENET3_SIZE
op_minus
l_int|1
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
(brace
dot
id|start
op_assign
id|MPC85xx_IRQ_FEC
comma
dot
id|end
op_assign
id|MPC85xx_IRQ_FEC
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
comma
)brace
comma
)brace
comma
(braket
id|MPC85xx_IIC1
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;fsl-i2c&quot;
comma
dot
id|id
op_assign
l_int|1
comma
dot
id|dev.platform_data
op_assign
op_amp
id|mpc85xx_fsl_i2c_pdata
comma
dot
id|num_resources
op_assign
l_int|2
comma
dot
id|resource
op_assign
(paren
r_struct
id|resource
(braket
)braket
)paren
(brace
(brace
dot
id|start
op_assign
id|MPC85xx_IIC1_OFFSET
comma
dot
id|end
op_assign
id|MPC85xx_IIC1_OFFSET
op_plus
id|MPC85xx_IIC1_SIZE
op_minus
l_int|1
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
(brace
dot
id|start
op_assign
id|MPC85xx_IRQ_IIC1
comma
dot
id|end
op_assign
id|MPC85xx_IRQ_IIC1
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
comma
)brace
comma
)brace
comma
(braket
id|MPC85xx_DMA0
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;fsl-dma&quot;
comma
dot
id|id
op_assign
l_int|0
comma
dot
id|num_resources
op_assign
l_int|2
comma
dot
id|resource
op_assign
(paren
r_struct
id|resource
(braket
)braket
)paren
(brace
(brace
dot
id|start
op_assign
id|MPC85xx_DMA0_OFFSET
comma
dot
id|end
op_assign
id|MPC85xx_DMA0_OFFSET
op_plus
id|MPC85xx_DMA0_SIZE
op_minus
l_int|1
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
(brace
dot
id|start
op_assign
id|MPC85xx_IRQ_DMA0
comma
dot
id|end
op_assign
id|MPC85xx_IRQ_DMA0
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
comma
)brace
comma
)brace
comma
(braket
id|MPC85xx_DMA1
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;fsl-dma&quot;
comma
dot
id|id
op_assign
l_int|1
comma
dot
id|num_resources
op_assign
l_int|2
comma
dot
id|resource
op_assign
(paren
r_struct
id|resource
(braket
)braket
)paren
(brace
(brace
dot
id|start
op_assign
id|MPC85xx_DMA1_OFFSET
comma
dot
id|end
op_assign
id|MPC85xx_DMA1_OFFSET
op_plus
id|MPC85xx_DMA1_SIZE
op_minus
l_int|1
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
(brace
dot
id|start
op_assign
id|MPC85xx_IRQ_DMA1
comma
dot
id|end
op_assign
id|MPC85xx_IRQ_DMA1
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
comma
)brace
comma
)brace
comma
(braket
id|MPC85xx_DMA2
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;fsl-dma&quot;
comma
dot
id|id
op_assign
l_int|2
comma
dot
id|num_resources
op_assign
l_int|2
comma
dot
id|resource
op_assign
(paren
r_struct
id|resource
(braket
)braket
)paren
(brace
(brace
dot
id|start
op_assign
id|MPC85xx_DMA2_OFFSET
comma
dot
id|end
op_assign
id|MPC85xx_DMA2_OFFSET
op_plus
id|MPC85xx_DMA2_SIZE
op_minus
l_int|1
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
(brace
dot
id|start
op_assign
id|MPC85xx_IRQ_DMA2
comma
dot
id|end
op_assign
id|MPC85xx_IRQ_DMA2
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
comma
)brace
comma
)brace
comma
(braket
id|MPC85xx_DMA3
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;fsl-dma&quot;
comma
dot
id|id
op_assign
l_int|3
comma
dot
id|num_resources
op_assign
l_int|2
comma
dot
id|resource
op_assign
(paren
r_struct
id|resource
(braket
)braket
)paren
(brace
(brace
dot
id|start
op_assign
id|MPC85xx_DMA3_OFFSET
comma
dot
id|end
op_assign
id|MPC85xx_DMA3_OFFSET
op_plus
id|MPC85xx_DMA3_SIZE
op_minus
l_int|1
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
(brace
dot
id|start
op_assign
id|MPC85xx_IRQ_DMA3
comma
dot
id|end
op_assign
id|MPC85xx_IRQ_DMA3
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
comma
)brace
comma
)brace
comma
(braket
id|MPC85xx_DUART
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;serial8250&quot;
comma
dot
id|id
op_assign
l_int|0
comma
dot
id|dev.platform_data
op_assign
id|serial_platform_data
comma
)brace
comma
(braket
id|MPC85xx_PERFMON
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;fsl-perfmon&quot;
comma
dot
id|id
op_assign
l_int|1
comma
dot
id|num_resources
op_assign
l_int|2
comma
dot
id|resource
op_assign
(paren
r_struct
id|resource
(braket
)braket
)paren
(brace
(brace
dot
id|start
op_assign
id|MPC85xx_PERFMON_OFFSET
comma
dot
id|end
op_assign
id|MPC85xx_PERFMON_OFFSET
op_plus
id|MPC85xx_PERFMON_SIZE
op_minus
l_int|1
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
(brace
dot
id|start
op_assign
id|MPC85xx_IRQ_PERFMON
comma
dot
id|end
op_assign
id|MPC85xx_IRQ_PERFMON
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
comma
)brace
comma
)brace
comma
(braket
id|MPC85xx_SEC2
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;fsl-sec2&quot;
comma
dot
id|id
op_assign
l_int|1
comma
dot
id|num_resources
op_assign
l_int|2
comma
dot
id|resource
op_assign
(paren
r_struct
id|resource
(braket
)braket
)paren
(brace
(brace
dot
id|start
op_assign
id|MPC85xx_SEC2_OFFSET
comma
dot
id|end
op_assign
id|MPC85xx_SEC2_OFFSET
op_plus
id|MPC85xx_SEC2_SIZE
op_minus
l_int|1
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
(brace
dot
id|start
op_assign
id|MPC85xx_IRQ_SEC2
comma
dot
id|end
op_assign
id|MPC85xx_IRQ_SEC2
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
comma
)brace
comma
)brace
comma
macro_line|#ifdef CONFIG_CPM2
(braket
id|MPC85xx_CPM_FCC1
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;fsl-cpm-fcc&quot;
comma
dot
id|id
op_assign
l_int|1
comma
dot
id|num_resources
op_assign
l_int|3
comma
dot
id|resource
op_assign
(paren
r_struct
id|resource
(braket
)braket
)paren
(brace
(brace
dot
id|start
op_assign
l_int|0x91300
comma
dot
id|end
op_assign
l_int|0x9131F
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
(brace
dot
id|start
op_assign
l_int|0x91380
comma
dot
id|end
op_assign
l_int|0x9139F
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
(brace
dot
id|start
op_assign
id|SIU_INT_FCC1
comma
dot
id|end
op_assign
id|SIU_INT_FCC1
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
comma
)brace
comma
)brace
comma
(braket
id|MPC85xx_CPM_FCC2
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;fsl-cpm-fcc&quot;
comma
dot
id|id
op_assign
l_int|2
comma
dot
id|num_resources
op_assign
l_int|3
comma
dot
id|resource
op_assign
(paren
r_struct
id|resource
(braket
)braket
)paren
(brace
(brace
dot
id|start
op_assign
l_int|0x91320
comma
dot
id|end
op_assign
l_int|0x9133F
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
(brace
dot
id|start
op_assign
l_int|0x913A0
comma
dot
id|end
op_assign
l_int|0x913CF
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
(brace
dot
id|start
op_assign
id|SIU_INT_FCC2
comma
dot
id|end
op_assign
id|SIU_INT_FCC2
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
comma
)brace
comma
)brace
comma
(braket
id|MPC85xx_CPM_FCC3
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;fsl-cpm-fcc&quot;
comma
dot
id|id
op_assign
l_int|3
comma
dot
id|num_resources
op_assign
l_int|3
comma
dot
id|resource
op_assign
(paren
r_struct
id|resource
(braket
)braket
)paren
(brace
(brace
dot
id|start
op_assign
l_int|0x91340
comma
dot
id|end
op_assign
l_int|0x9135F
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
(brace
dot
id|start
op_assign
l_int|0x913D0
comma
dot
id|end
op_assign
l_int|0x913FF
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
(brace
dot
id|start
op_assign
id|SIU_INT_FCC3
comma
dot
id|end
op_assign
id|SIU_INT_FCC3
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
comma
)brace
comma
)brace
comma
(braket
id|MPC85xx_CPM_I2C
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;fsl-cpm-i2c&quot;
comma
dot
id|id
op_assign
l_int|1
comma
dot
id|num_resources
op_assign
l_int|2
comma
dot
id|resource
op_assign
(paren
r_struct
id|resource
(braket
)braket
)paren
(brace
(brace
dot
id|start
op_assign
l_int|0x91860
comma
dot
id|end
op_assign
l_int|0x918BF
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
(brace
dot
id|start
op_assign
id|SIU_INT_I2C
comma
dot
id|end
op_assign
id|SIU_INT_I2C
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
comma
)brace
comma
)brace
comma
(braket
id|MPC85xx_CPM_SCC1
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;fsl-cpm-scc&quot;
comma
dot
id|id
op_assign
l_int|1
comma
dot
id|num_resources
op_assign
l_int|2
comma
dot
id|resource
op_assign
(paren
r_struct
id|resource
(braket
)braket
)paren
(brace
(brace
dot
id|start
op_assign
l_int|0x91A00
comma
dot
id|end
op_assign
l_int|0x91A1F
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
(brace
dot
id|start
op_assign
id|SIU_INT_SCC1
comma
dot
id|end
op_assign
id|SIU_INT_SCC1
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
comma
)brace
comma
)brace
comma
(braket
id|MPC85xx_CPM_SCC2
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;fsl-cpm-scc&quot;
comma
dot
id|id
op_assign
l_int|2
comma
dot
id|num_resources
op_assign
l_int|2
comma
dot
id|resource
op_assign
(paren
r_struct
id|resource
(braket
)braket
)paren
(brace
(brace
dot
id|start
op_assign
l_int|0x91A20
comma
dot
id|end
op_assign
l_int|0x91A3F
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
(brace
dot
id|start
op_assign
id|SIU_INT_SCC2
comma
dot
id|end
op_assign
id|SIU_INT_SCC2
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
comma
)brace
comma
)brace
comma
(braket
id|MPC85xx_CPM_SCC3
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;fsl-cpm-scc&quot;
comma
dot
id|id
op_assign
l_int|3
comma
dot
id|num_resources
op_assign
l_int|2
comma
dot
id|resource
op_assign
(paren
r_struct
id|resource
(braket
)braket
)paren
(brace
(brace
dot
id|start
op_assign
l_int|0x91A40
comma
dot
id|end
op_assign
l_int|0x91A5F
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
(brace
dot
id|start
op_assign
id|SIU_INT_SCC3
comma
dot
id|end
op_assign
id|SIU_INT_SCC3
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
comma
)brace
comma
)brace
comma
(braket
id|MPC85xx_CPM_SCC4
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;fsl-cpm-scc&quot;
comma
dot
id|id
op_assign
l_int|4
comma
dot
id|num_resources
op_assign
l_int|2
comma
dot
id|resource
op_assign
(paren
r_struct
id|resource
(braket
)braket
)paren
(brace
(brace
dot
id|start
op_assign
l_int|0x91A60
comma
dot
id|end
op_assign
l_int|0x91A7F
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
(brace
dot
id|start
op_assign
id|SIU_INT_SCC4
comma
dot
id|end
op_assign
id|SIU_INT_SCC4
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
comma
)brace
comma
)brace
comma
(braket
id|MPC85xx_CPM_SPI
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;fsl-cpm-spi&quot;
comma
dot
id|id
op_assign
l_int|1
comma
dot
id|num_resources
op_assign
l_int|2
comma
dot
id|resource
op_assign
(paren
r_struct
id|resource
(braket
)braket
)paren
(brace
(brace
dot
id|start
op_assign
l_int|0x91AA0
comma
dot
id|end
op_assign
l_int|0x91AFF
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
(brace
dot
id|start
op_assign
id|SIU_INT_SPI
comma
dot
id|end
op_assign
id|SIU_INT_SPI
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
comma
)brace
comma
)brace
comma
(braket
id|MPC85xx_CPM_MCC1
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;fsl-cpm-mcc&quot;
comma
dot
id|id
op_assign
l_int|1
comma
dot
id|num_resources
op_assign
l_int|2
comma
dot
id|resource
op_assign
(paren
r_struct
id|resource
(braket
)braket
)paren
(brace
(brace
dot
id|start
op_assign
l_int|0x91B30
comma
dot
id|end
op_assign
l_int|0x91B3F
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
(brace
dot
id|start
op_assign
id|SIU_INT_MCC1
comma
dot
id|end
op_assign
id|SIU_INT_MCC1
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
comma
)brace
comma
)brace
comma
(braket
id|MPC85xx_CPM_MCC2
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;fsl-cpm-mcc&quot;
comma
dot
id|id
op_assign
l_int|2
comma
dot
id|num_resources
op_assign
l_int|2
comma
dot
id|resource
op_assign
(paren
r_struct
id|resource
(braket
)braket
)paren
(brace
(brace
dot
id|start
op_assign
l_int|0x91B50
comma
dot
id|end
op_assign
l_int|0x91B5F
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
(brace
dot
id|start
op_assign
id|SIU_INT_MCC2
comma
dot
id|end
op_assign
id|SIU_INT_MCC2
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
comma
)brace
comma
)brace
comma
(braket
id|MPC85xx_CPM_SMC1
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;fsl-cpm-smc&quot;
comma
dot
id|id
op_assign
l_int|1
comma
dot
id|num_resources
op_assign
l_int|2
comma
dot
id|resource
op_assign
(paren
r_struct
id|resource
(braket
)braket
)paren
(brace
(brace
dot
id|start
op_assign
l_int|0x91A80
comma
dot
id|end
op_assign
l_int|0x91A8F
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
(brace
dot
id|start
op_assign
id|SIU_INT_SMC1
comma
dot
id|end
op_assign
id|SIU_INT_SMC1
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
comma
)brace
comma
)brace
comma
(braket
id|MPC85xx_CPM_SMC2
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;fsl-cpm-smc&quot;
comma
dot
id|id
op_assign
l_int|2
comma
dot
id|num_resources
op_assign
l_int|2
comma
dot
id|resource
op_assign
(paren
r_struct
id|resource
(braket
)braket
)paren
(brace
(brace
dot
id|start
op_assign
l_int|0x91A90
comma
dot
id|end
op_assign
l_int|0x91A9F
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
(brace
dot
id|start
op_assign
id|SIU_INT_SMC2
comma
dot
id|end
op_assign
id|SIU_INT_SMC2
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
comma
)brace
comma
)brace
comma
(braket
id|MPC85xx_CPM_USB
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;fsl-cpm-usb&quot;
comma
dot
id|id
op_assign
l_int|2
comma
dot
id|num_resources
op_assign
l_int|2
comma
dot
id|resource
op_assign
(paren
r_struct
id|resource
(braket
)braket
)paren
(brace
(brace
dot
id|start
op_assign
l_int|0x91B60
comma
dot
id|end
op_assign
l_int|0x91B7F
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
(brace
dot
id|start
op_assign
id|SIU_INT_USB
comma
dot
id|end
op_assign
id|SIU_INT_USB
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
comma
)brace
comma
)brace
comma
macro_line|#endif /* CONFIG_CPM2 */
)brace
suffix:semicolon
DECL|function|mach_mpc85xx_fixup
r_static
r_int
id|__init
id|mach_mpc85xx_fixup
c_func
(paren
r_struct
id|platform_device
op_star
id|pdev
)paren
(brace
id|ppc_sys_fixup_mem_resource
c_func
(paren
id|pdev
comma
id|CCSRBAR
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mach_mpc85xx_init
r_static
r_int
id|__init
id|mach_mpc85xx_init
c_func
(paren
r_void
)paren
(brace
id|ppc_sys_device_fixup
op_assign
id|mach_mpc85xx_fixup
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|mach_mpc85xx_init
id|postcore_initcall
c_func
(paren
id|mach_mpc85xx_init
)paren
suffix:semicolon
eof
