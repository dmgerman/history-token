multiline_comment|/*&n; *  linux/arch/arm/mach-versatile/versatile_pb.c&n; *&n; *  Copyright (C) 2004 ARM Limited&n; *  Copyright (C) 2000 Deep Blue Solutions Ltd&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/sysdev.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/hardware/amba.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/mmc.h&gt;
macro_line|#include &quot;core.h&quot;
macro_line|#if 1
DECL|macro|IRQ_MMCI1A
mdefine_line|#define IRQ_MMCI1A&t;IRQ_VICSOURCE23
macro_line|#else
DECL|macro|IRQ_MMCI1A
mdefine_line|#define IRQ_MMCI1A&t;IRQ_SIC_MMCI1A
macro_line|#endif
DECL|variable|mmc1_plat_data
r_static
r_struct
id|mmc_platform_data
id|mmc1_plat_data
op_assign
(brace
dot
id|ocr_mask
op_assign
id|MMC_VDD_32_33
op_or
id|MMC_VDD_33_34
comma
dot
id|status
op_assign
id|mmc_status
comma
)brace
suffix:semicolon
DECL|macro|UART3_IRQ
mdefine_line|#define UART3_IRQ&t;{ IRQ_SIC_UART3, NO_IRQ }
DECL|macro|UART3_DMA
mdefine_line|#define UART3_DMA&t;{ 0x86, 0x87 }
DECL|macro|SCI1_IRQ
mdefine_line|#define SCI1_IRQ&t;{ IRQ_SIC_SCI3, NO_IRQ }
DECL|macro|SCI1_DMA
mdefine_line|#define SCI1_DMA&t;{ 0x88, 0x89 }
DECL|macro|MMCI1_IRQ
mdefine_line|#define MMCI1_IRQ&t;{ IRQ_MMCI1A, IRQ_SIC_MMCI1B }
DECL|macro|MMCI1_DMA
mdefine_line|#define MMCI1_DMA&t;{ 0x85, 0 }
multiline_comment|/*&n; * These devices are connected via the core APB bridge&n; */
DECL|macro|GPIO2_IRQ
mdefine_line|#define GPIO2_IRQ&t;{ IRQ_GPIOINT2, NO_IRQ }
DECL|macro|GPIO2_DMA
mdefine_line|#define GPIO2_DMA&t;{ 0, 0 }
DECL|macro|GPIO3_IRQ
mdefine_line|#define GPIO3_IRQ&t;{ IRQ_GPIOINT3, NO_IRQ }
DECL|macro|GPIO3_DMA
mdefine_line|#define GPIO3_DMA&t;{ 0, 0 }
multiline_comment|/*&n; * These devices are connected via the DMA APB bridge&n; */
multiline_comment|/* FPGA Primecells */
id|AMBA_DEVICE
c_func
(paren
id|uart3
comma
l_string|&quot;fpga:09&quot;
comma
id|UART3
comma
l_int|NULL
)paren
suffix:semicolon
id|AMBA_DEVICE
c_func
(paren
id|sci1
comma
l_string|&quot;fpga:0a&quot;
comma
id|SCI1
comma
l_int|NULL
)paren
suffix:semicolon
id|AMBA_DEVICE
c_func
(paren
id|mmc1
comma
l_string|&quot;fpga:0b&quot;
comma
id|MMCI1
comma
op_amp
id|mmc1_plat_data
)paren
suffix:semicolon
multiline_comment|/* DevChip Primecells */
id|AMBA_DEVICE
c_func
(paren
id|gpio2
comma
l_string|&quot;dev:e6&quot;
comma
id|GPIO2
comma
l_int|NULL
)paren
suffix:semicolon
id|AMBA_DEVICE
c_func
(paren
id|gpio3
comma
l_string|&quot;dev:e7&quot;
comma
id|GPIO3
comma
l_int|NULL
)paren
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|amba_device
op_star
id|amba_devs
(braket
)braket
id|__initdata
op_assign
(brace
op_amp
id|uart3_device
comma
op_amp
id|gpio2_device
comma
op_amp
id|gpio3_device
comma
op_amp
id|sci1_device
comma
op_amp
id|mmc1_device
comma
)brace
suffix:semicolon
DECL|function|versatile_pb_init
r_static
r_int
id|__init
id|versatile_pb_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_versatile_pb
c_func
(paren
)paren
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ARRAY_SIZE
c_func
(paren
id|amba_devs
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|amba_device
op_star
id|d
op_assign
id|amba_devs
(braket
id|i
)braket
suffix:semicolon
id|amba_device_register
c_func
(paren
id|d
comma
op_amp
id|iomem_resource
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|versatile_pb_init
id|arch_initcall
c_func
(paren
id|versatile_pb_init
)paren
suffix:semicolon
id|MACHINE_START
c_func
(paren
id|VERSATILE_PB
comma
l_string|&quot;ARM-Versatile PB&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;ARM Ltd/Deep Blue Solutions Ltd&quot;
)paren
id|BOOT_MEM
c_func
(paren
l_int|0x00000000
comma
l_int|0x101f1000
comma
l_int|0xf11f1000
)paren
id|BOOT_PARAMS
c_func
(paren
l_int|0x00000100
)paren
id|MAPIO
c_func
(paren
id|versatile_map_io
)paren
id|INITIRQ
c_func
(paren
id|versatile_init_irq
)paren
dot
id|timer
op_assign
op_amp
id|versatile_timer
comma
id|INIT_MACHINE
c_func
(paren
id|versatile_init
)paren
id|MACHINE_END
eof
