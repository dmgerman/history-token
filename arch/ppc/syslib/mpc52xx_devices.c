multiline_comment|/*&n; * arch/ppc/syslib/mpc52xx_devices.c&n; *&n; * Freescale MPC52xx device descriptions&n; *&n; *&n; * Maintainer : Sylvain Munaut &lt;tnt@246tNt.com&gt;&n; *&n; * Copyright (C) 2005 Sylvain Munaut &lt;tnt@246tNt.com&gt;&n; *&n; * This file is licensed under the terms of the GNU General Public License&n; * version 2. This program is licensed &quot;as is&quot; without any warranty of any&n; * kind, whether express or implied.&n; */
macro_line|#include &lt;linux/fsl_devices.h&gt;
macro_line|#include &lt;linux/resource.h&gt;
macro_line|#include &lt;asm/mpc52xx.h&gt;
macro_line|#include &lt;asm/ppc_sys.h&gt;
DECL|variable|mpc52xx_dma_mask
r_static
id|u64
id|mpc52xx_dma_mask
op_assign
l_int|0xffffffffULL
suffix:semicolon
DECL|variable|mpc52xx_fsl_i2c_pdata
r_static
r_struct
id|fsl_i2c_platform_data
id|mpc52xx_fsl_i2c_pdata
op_assign
(brace
dot
id|device_flags
op_assign
id|FSL_I2C_DEV_CLOCK_5200
comma
)brace
suffix:semicolon
multiline_comment|/* We use relative offsets for IORESOURCE_MEM to be independent from the&n; * MBAR location at compile time&n; */
multiline_comment|/* TODO Add the BestComm initiator channel to the device definitions,&n;   possibly using IORESOURCE_DMA. But that&squot;s when BestComm is ready ... */
DECL|variable|ppc_sys_platform_devices
r_struct
id|platform_device
id|ppc_sys_platform_devices
(braket
)braket
op_assign
(brace
(braket
id|MPC52xx_MSCAN1
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;mpc52xx-mscan&quot;
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
l_int|0x0900
comma
dot
id|end
op_assign
l_int|0x097f
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
id|MPC52xx_MSCAN1_IRQ
comma
dot
id|end
op_assign
id|MPC52xx_MSCAN1_IRQ
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
id|MPC52xx_MSCAN2
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;mpc52xx-mscan&quot;
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
l_int|0x0980
comma
dot
id|end
op_assign
l_int|0x09ff
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
id|MPC52xx_MSCAN2_IRQ
comma
dot
id|end
op_assign
id|MPC52xx_MSCAN2_IRQ
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
id|MPC52xx_SPI
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;mpc52xx-spi&quot;
comma
dot
id|id
op_assign
op_minus
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
l_int|0x0f00
comma
dot
id|end
op_assign
l_int|0x0f1f
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
l_string|&quot;modf&quot;
comma
dot
id|start
op_assign
id|MPC52xx_SPI_MODF_IRQ
comma
dot
id|end
op_assign
id|MPC52xx_SPI_MODF_IRQ
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
l_string|&quot;spif&quot;
comma
dot
id|start
op_assign
id|MPC52xx_SPI_SPIF_IRQ
comma
dot
id|end
op_assign
id|MPC52xx_SPI_SPIF_IRQ
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
id|MPC52xx_USB
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;ppc-soc-ohci&quot;
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
dot
id|num_resources
op_assign
l_int|2
comma
dot
id|dev.dma_mask
op_assign
op_amp
id|mpc52xx_dma_mask
comma
dot
id|dev.coherent_dma_mask
op_assign
l_int|0xffffffffULL
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
l_int|0x1000
comma
dot
id|end
op_assign
l_int|0x10ff
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
id|MPC52xx_USB_IRQ
comma
dot
id|end
op_assign
id|MPC52xx_USB_IRQ
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
id|MPC52xx_BDLC
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;mpc52xx-bdlc&quot;
comma
dot
id|id
op_assign
op_minus
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
l_int|0x1300
comma
dot
id|end
op_assign
l_int|0x130f
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
id|MPC52xx_BDLC_IRQ
comma
dot
id|end
op_assign
id|MPC52xx_BDLC_IRQ
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
id|MPC52xx_PSC1
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;mpc52xx-psc&quot;
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
l_int|0x2000
comma
dot
id|end
op_assign
l_int|0x209f
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
id|MPC52xx_PSC1_IRQ
comma
dot
id|end
op_assign
id|MPC52xx_PSC1_IRQ
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
id|MPC52xx_PSC2
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;mpc52xx-psc&quot;
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
l_int|0x2200
comma
dot
id|end
op_assign
l_int|0x229f
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
id|MPC52xx_PSC2_IRQ
comma
dot
id|end
op_assign
id|MPC52xx_PSC2_IRQ
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
id|MPC52xx_PSC3
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;mpc52xx-psc&quot;
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
l_int|0x2400
comma
dot
id|end
op_assign
l_int|0x249f
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
id|MPC52xx_PSC3_IRQ
comma
dot
id|end
op_assign
id|MPC52xx_PSC3_IRQ
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
id|MPC52xx_PSC4
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;mpc52xx-psc&quot;
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
l_int|0x2600
comma
dot
id|end
op_assign
l_int|0x269f
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
id|MPC52xx_PSC4_IRQ
comma
dot
id|end
op_assign
id|MPC52xx_PSC4_IRQ
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
id|MPC52xx_PSC5
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;mpc52xx-psc&quot;
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
l_int|0x2800
comma
dot
id|end
op_assign
l_int|0x289f
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
id|MPC52xx_PSC5_IRQ
comma
dot
id|end
op_assign
id|MPC52xx_PSC5_IRQ
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
id|MPC52xx_PSC6
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;mpc52xx-psc&quot;
comma
dot
id|id
op_assign
l_int|5
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
l_int|0x2c00
comma
dot
id|end
op_assign
l_int|0x2c9f
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
id|MPC52xx_PSC6_IRQ
comma
dot
id|end
op_assign
id|MPC52xx_PSC6_IRQ
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
id|MPC52xx_FEC
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;mpc52xx-fec&quot;
comma
dot
id|id
op_assign
op_minus
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
l_int|0x3000
comma
dot
id|end
op_assign
l_int|0x33ff
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
id|MPC52xx_FEC_IRQ
comma
dot
id|end
op_assign
id|MPC52xx_FEC_IRQ
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
id|MPC52xx_ATA
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;mpc52xx-ata&quot;
comma
dot
id|id
op_assign
op_minus
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
l_int|0x3a00
comma
dot
id|end
op_assign
l_int|0x3aff
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
id|MPC52xx_ATA_IRQ
comma
dot
id|end
op_assign
id|MPC52xx_ATA_IRQ
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
id|MPC52xx_I2C1
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
l_int|0
comma
dot
id|dev.platform_data
op_assign
op_amp
id|mpc52xx_fsl_i2c_pdata
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
l_int|0x3d00
comma
dot
id|end
op_assign
l_int|0x3d1f
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
id|MPC52xx_I2C1_IRQ
comma
dot
id|end
op_assign
id|MPC52xx_I2C1_IRQ
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
id|MPC52xx_I2C2
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
id|mpc52xx_fsl_i2c_pdata
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
l_int|0x3d40
comma
dot
id|end
op_assign
l_int|0x3d5f
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
id|MPC52xx_I2C2_IRQ
comma
dot
id|end
op_assign
id|MPC52xx_I2C2_IRQ
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
)brace
suffix:semicolon
DECL|function|mach_mpc52xx_fixup
r_static
r_int
id|__init
id|mach_mpc52xx_fixup
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
id|MPC52xx_MBAR
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mach_mpc52xx_init
r_static
r_int
id|__init
id|mach_mpc52xx_init
c_func
(paren
r_void
)paren
(brace
id|ppc_sys_device_fixup
op_assign
id|mach_mpc52xx_fixup
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|mach_mpc52xx_init
id|postcore_initcall
c_func
(paren
id|mach_mpc52xx_init
)paren
suffix:semicolon
eof
