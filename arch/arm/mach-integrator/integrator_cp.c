multiline_comment|/*&n; *  linux/arch/arm/mach-integrator/integrator_cp.c&n; *&n; *  Copyright (C) 2003 Deep Blue Solutions Ltd&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/dma-mapping.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/sysdev.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/hardware/amba.h&gt;
macro_line|#include &lt;asm/hardware/amba_kmi.h&gt;
macro_line|#include &lt;asm/hardware/amba_clcd.h&gt;
macro_line|#include &lt;asm/hardware/icst525.h&gt;
macro_line|#include &lt;asm/arch/cm.h&gt;
macro_line|#include &lt;asm/arch/lm.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/flash.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &lt;asm/mach/mmc.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &quot;clock.h&quot;
DECL|macro|INTCP_PA_MMC_BASE
mdefine_line|#define INTCP_PA_MMC_BASE&t;&t;0x1c000000
DECL|macro|INTCP_PA_AACI_BASE
mdefine_line|#define INTCP_PA_AACI_BASE&t;&t;0x1d000000
DECL|macro|INTCP_PA_FLASH_BASE
mdefine_line|#define INTCP_PA_FLASH_BASE&t;&t;0x24000000
DECL|macro|INTCP_FLASH_SIZE
mdefine_line|#define INTCP_FLASH_SIZE&t;&t;SZ_32M
DECL|macro|INTCP_PA_CLCD_BASE
mdefine_line|#define INTCP_PA_CLCD_BASE&t;&t;0xc0000000
DECL|macro|INTCP_VA_CIC_BASE
mdefine_line|#define INTCP_VA_CIC_BASE&t;&t;0xf1000040
DECL|macro|INTCP_VA_PIC_BASE
mdefine_line|#define INTCP_VA_PIC_BASE&t;&t;0xf1400000
DECL|macro|INTCP_VA_SIC_BASE
mdefine_line|#define INTCP_VA_SIC_BASE&t;&t;0xfca00000
DECL|macro|INTCP_PA_ETH_BASE
mdefine_line|#define INTCP_PA_ETH_BASE&t;&t;0xc8000000
DECL|macro|INTCP_ETH_SIZE
mdefine_line|#define INTCP_ETH_SIZE&t;&t;&t;0x10
DECL|macro|INTCP_VA_CTRL_BASE
mdefine_line|#define INTCP_VA_CTRL_BASE&t;&t;0xfcb00000
DECL|macro|INTCP_FLASHPROG
mdefine_line|#define INTCP_FLASHPROG&t;&t;&t;0x04
DECL|macro|CINTEGRATOR_FLASHPROG_FLVPPEN
mdefine_line|#define CINTEGRATOR_FLASHPROG_FLVPPEN&t;(1 &lt;&lt; 0)
DECL|macro|CINTEGRATOR_FLASHPROG_FLWREN
mdefine_line|#define CINTEGRATOR_FLASHPROG_FLWREN&t;(1 &lt;&lt; 1)
multiline_comment|/*&n; * Logical      Physical&n; * f1000000&t;10000000&t;Core module registers&n; * f1100000&t;11000000&t;System controller registers&n; * f1200000&t;12000000&t;EBI registers&n; * f1300000&t;13000000&t;Counter/Timer&n; * f1400000&t;14000000&t;Interrupt controller&n; * f1600000&t;16000000&t;UART 0&n; * f1700000&t;17000000&t;UART 1&n; * f1a00000&t;1a000000&t;Debug LEDs&n; * f1b00000&t;1b000000&t;GPIO&n; */
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|intcp_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|IO_ADDRESS
c_func
(paren
id|INTEGRATOR_HDR_BASE
)paren
comma
id|INTEGRATOR_HDR_BASE
comma
id|SZ_4K
comma
id|MT_DEVICE
)brace
comma
(brace
id|IO_ADDRESS
c_func
(paren
id|INTEGRATOR_SC_BASE
)paren
comma
id|INTEGRATOR_SC_BASE
comma
id|SZ_4K
comma
id|MT_DEVICE
)brace
comma
(brace
id|IO_ADDRESS
c_func
(paren
id|INTEGRATOR_EBI_BASE
)paren
comma
id|INTEGRATOR_EBI_BASE
comma
id|SZ_4K
comma
id|MT_DEVICE
)brace
comma
(brace
id|IO_ADDRESS
c_func
(paren
id|INTEGRATOR_CT_BASE
)paren
comma
id|INTEGRATOR_CT_BASE
comma
id|SZ_4K
comma
id|MT_DEVICE
)brace
comma
(brace
id|IO_ADDRESS
c_func
(paren
id|INTEGRATOR_IC_BASE
)paren
comma
id|INTEGRATOR_IC_BASE
comma
id|SZ_4K
comma
id|MT_DEVICE
)brace
comma
(brace
id|IO_ADDRESS
c_func
(paren
id|INTEGRATOR_UART0_BASE
)paren
comma
id|INTEGRATOR_UART0_BASE
comma
id|SZ_4K
comma
id|MT_DEVICE
)brace
comma
(brace
id|IO_ADDRESS
c_func
(paren
id|INTEGRATOR_UART1_BASE
)paren
comma
id|INTEGRATOR_UART1_BASE
comma
id|SZ_4K
comma
id|MT_DEVICE
)brace
comma
(brace
id|IO_ADDRESS
c_func
(paren
id|INTEGRATOR_DBG_BASE
)paren
comma
id|INTEGRATOR_DBG_BASE
comma
id|SZ_4K
comma
id|MT_DEVICE
)brace
comma
(brace
id|IO_ADDRESS
c_func
(paren
id|INTEGRATOR_GPIO_BASE
)paren
comma
id|INTEGRATOR_GPIO_BASE
comma
id|SZ_4K
comma
id|MT_DEVICE
)brace
comma
(brace
l_int|0xfc900000
comma
l_int|0xc9000000
comma
id|SZ_4K
comma
id|MT_DEVICE
)brace
comma
(brace
l_int|0xfca00000
comma
l_int|0xca000000
comma
id|SZ_4K
comma
id|MT_DEVICE
)brace
comma
(brace
l_int|0xfcb00000
comma
l_int|0xcb000000
comma
id|SZ_4K
comma
id|MT_DEVICE
)brace
comma
)brace
suffix:semicolon
DECL|function|intcp_map_io
r_static
r_void
id|__init
id|intcp_map_io
c_func
(paren
r_void
)paren
(brace
id|iotable_init
c_func
(paren
id|intcp_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|intcp_io_desc
)paren
)paren
suffix:semicolon
)brace
DECL|macro|cic_writel
mdefine_line|#define cic_writel&t;__raw_writel
DECL|macro|cic_readl
mdefine_line|#define cic_readl&t;__raw_readl
DECL|macro|pic_writel
mdefine_line|#define pic_writel&t;__raw_writel
DECL|macro|pic_readl
mdefine_line|#define pic_readl&t;__raw_readl
DECL|macro|sic_writel
mdefine_line|#define sic_writel&t;__raw_writel
DECL|macro|sic_readl
mdefine_line|#define sic_readl&t;__raw_readl
DECL|function|cic_mask_irq
r_static
r_void
id|cic_mask_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|irq
op_sub_assign
id|IRQ_CIC_START
suffix:semicolon
id|cic_writel
c_func
(paren
l_int|1
op_lshift
id|irq
comma
id|INTCP_VA_CIC_BASE
op_plus
id|IRQ_ENABLE_CLEAR
)paren
suffix:semicolon
)brace
DECL|function|cic_unmask_irq
r_static
r_void
id|cic_unmask_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|irq
op_sub_assign
id|IRQ_CIC_START
suffix:semicolon
id|cic_writel
c_func
(paren
l_int|1
op_lshift
id|irq
comma
id|INTCP_VA_CIC_BASE
op_plus
id|IRQ_ENABLE_SET
)paren
suffix:semicolon
)brace
DECL|variable|cic_chip
r_static
r_struct
id|irqchip
id|cic_chip
op_assign
(brace
dot
id|ack
op_assign
id|cic_mask_irq
comma
dot
id|mask
op_assign
id|cic_mask_irq
comma
dot
id|unmask
op_assign
id|cic_unmask_irq
comma
)brace
suffix:semicolon
DECL|function|pic_mask_irq
r_static
r_void
id|pic_mask_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|irq
op_sub_assign
id|IRQ_PIC_START
suffix:semicolon
id|pic_writel
c_func
(paren
l_int|1
op_lshift
id|irq
comma
id|INTCP_VA_PIC_BASE
op_plus
id|IRQ_ENABLE_CLEAR
)paren
suffix:semicolon
)brace
DECL|function|pic_unmask_irq
r_static
r_void
id|pic_unmask_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|irq
op_sub_assign
id|IRQ_PIC_START
suffix:semicolon
id|pic_writel
c_func
(paren
l_int|1
op_lshift
id|irq
comma
id|INTCP_VA_PIC_BASE
op_plus
id|IRQ_ENABLE_SET
)paren
suffix:semicolon
)brace
DECL|variable|pic_chip
r_static
r_struct
id|irqchip
id|pic_chip
op_assign
(brace
dot
id|ack
op_assign
id|pic_mask_irq
comma
dot
id|mask
op_assign
id|pic_mask_irq
comma
dot
id|unmask
op_assign
id|pic_unmask_irq
comma
)brace
suffix:semicolon
DECL|function|sic_mask_irq
r_static
r_void
id|sic_mask_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|irq
op_sub_assign
id|IRQ_SIC_START
suffix:semicolon
id|sic_writel
c_func
(paren
l_int|1
op_lshift
id|irq
comma
id|INTCP_VA_SIC_BASE
op_plus
id|IRQ_ENABLE_CLEAR
)paren
suffix:semicolon
)brace
DECL|function|sic_unmask_irq
r_static
r_void
id|sic_unmask_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|irq
op_sub_assign
id|IRQ_SIC_START
suffix:semicolon
id|sic_writel
c_func
(paren
l_int|1
op_lshift
id|irq
comma
id|INTCP_VA_SIC_BASE
op_plus
id|IRQ_ENABLE_SET
)paren
suffix:semicolon
)brace
DECL|variable|sic_chip
r_static
r_struct
id|irqchip
id|sic_chip
op_assign
(brace
dot
id|ack
op_assign
id|sic_mask_irq
comma
dot
id|mask
op_assign
id|sic_mask_irq
comma
dot
id|unmask
op_assign
id|sic_unmask_irq
comma
)brace
suffix:semicolon
r_static
r_void
DECL|function|sic_handle_irq
id|sic_handle_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_struct
id|irqdesc
op_star
id|desc
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|status
op_assign
id|sic_readl
c_func
(paren
id|INTCP_VA_SIC_BASE
op_plus
id|IRQ_STATUS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_eq
l_int|0
)paren
(brace
id|do_bad_IRQ
c_func
(paren
id|irq
comma
id|desc
comma
id|regs
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_do
(brace
id|irq
op_assign
id|ffs
c_func
(paren
id|status
)paren
op_minus
l_int|1
suffix:semicolon
id|status
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|irq
)paren
suffix:semicolon
id|irq
op_add_assign
id|IRQ_SIC_START
suffix:semicolon
id|desc
op_assign
id|irq_desc
op_plus
id|irq
suffix:semicolon
id|desc
op_member_access_from_pointer
id|handle
c_func
(paren
id|irq
comma
id|desc
comma
id|regs
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|status
)paren
suffix:semicolon
)brace
DECL|function|intcp_init_irq
r_static
r_void
id|__init
id|intcp_init_irq
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * Disable all interrupt sources&n;&t; */
id|pic_writel
c_func
(paren
l_int|0xffffffff
comma
id|INTCP_VA_PIC_BASE
op_plus
id|IRQ_ENABLE_CLEAR
)paren
suffix:semicolon
id|pic_writel
c_func
(paren
l_int|0xffffffff
comma
id|INTCP_VA_PIC_BASE
op_plus
id|FIQ_ENABLE_CLEAR
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|IRQ_PIC_START
suffix:semicolon
id|i
op_le
id|IRQ_PIC_END
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i
op_eq
l_int|11
)paren
id|i
op_assign
l_int|22
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|IRQ_CP_CPPLDINT
)paren
id|i
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
l_int|29
)paren
r_break
suffix:semicolon
id|set_irq_chip
c_func
(paren
id|i
comma
op_amp
id|pic_chip
)paren
suffix:semicolon
id|set_irq_handler
c_func
(paren
id|i
comma
id|do_level_IRQ
)paren
suffix:semicolon
id|set_irq_flags
c_func
(paren
id|i
comma
id|IRQF_VALID
op_or
id|IRQF_PROBE
)paren
suffix:semicolon
)brace
id|cic_writel
c_func
(paren
l_int|0xffffffff
comma
id|INTCP_VA_CIC_BASE
op_plus
id|IRQ_ENABLE_CLEAR
)paren
suffix:semicolon
id|cic_writel
c_func
(paren
l_int|0xffffffff
comma
id|INTCP_VA_CIC_BASE
op_plus
id|FIQ_ENABLE_CLEAR
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|IRQ_CIC_START
suffix:semicolon
id|i
op_le
id|IRQ_CIC_END
suffix:semicolon
id|i
op_increment
)paren
(brace
id|set_irq_chip
c_func
(paren
id|i
comma
op_amp
id|cic_chip
)paren
suffix:semicolon
id|set_irq_handler
c_func
(paren
id|i
comma
id|do_level_IRQ
)paren
suffix:semicolon
id|set_irq_flags
c_func
(paren
id|i
comma
id|IRQF_VALID
)paren
suffix:semicolon
)brace
id|sic_writel
c_func
(paren
l_int|0x00000fff
comma
id|INTCP_VA_SIC_BASE
op_plus
id|IRQ_ENABLE_CLEAR
)paren
suffix:semicolon
id|sic_writel
c_func
(paren
l_int|0x00000fff
comma
id|INTCP_VA_SIC_BASE
op_plus
id|FIQ_ENABLE_CLEAR
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|IRQ_SIC_START
suffix:semicolon
id|i
op_le
id|IRQ_SIC_END
suffix:semicolon
id|i
op_increment
)paren
(brace
id|set_irq_chip
c_func
(paren
id|i
comma
op_amp
id|sic_chip
)paren
suffix:semicolon
id|set_irq_handler
c_func
(paren
id|i
comma
id|do_level_IRQ
)paren
suffix:semicolon
id|set_irq_flags
c_func
(paren
id|i
comma
id|IRQF_VALID
op_or
id|IRQF_PROBE
)paren
suffix:semicolon
)brace
id|set_irq_handler
c_func
(paren
id|IRQ_CP_CPPLDINT
comma
id|sic_handle_irq
)paren
suffix:semicolon
id|pic_unmask_irq
c_func
(paren
id|IRQ_CP_CPPLDINT
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Clock handling&n; */
DECL|macro|CM_LOCK
mdefine_line|#define CM_LOCK (IO_ADDRESS(INTEGRATOR_HDR_BASE)+INTEGRATOR_HDR_LOCK_OFFSET)
DECL|macro|CM_AUXOSC
mdefine_line|#define CM_AUXOSC (IO_ADDRESS(INTEGRATOR_HDR_BASE)+0x1c)
DECL|variable|cp_auxvco_params
r_static
r_const
r_struct
id|icst525_params
id|cp_auxvco_params
op_assign
(brace
dot
id|ref
op_assign
l_int|24000
comma
dot
id|vco_max
op_assign
l_int|320000
comma
dot
id|vd_min
op_assign
l_int|8
comma
dot
id|vd_max
op_assign
l_int|263
comma
dot
id|rd_min
op_assign
l_int|3
comma
dot
id|rd_max
op_assign
l_int|65
comma
)brace
suffix:semicolon
DECL|function|cp_auxvco_set
r_static
r_void
id|cp_auxvco_set
c_func
(paren
r_struct
id|clk
op_star
id|clk
comma
r_struct
id|icst525_vco
id|vco
)paren
(brace
id|u32
id|val
suffix:semicolon
id|val
op_assign
id|readl
c_func
(paren
id|CM_AUXOSC
)paren
op_amp
op_complement
l_int|0x7ffff
suffix:semicolon
id|val
op_or_assign
id|vco.v
op_or
(paren
id|vco.r
op_lshift
l_int|9
)paren
op_or
(paren
id|vco.s
op_lshift
l_int|16
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|0xa05f
comma
id|CM_LOCK
)paren
suffix:semicolon
id|writel
c_func
(paren
id|val
comma
id|CM_AUXOSC
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|0
comma
id|CM_LOCK
)paren
suffix:semicolon
)brace
DECL|variable|cp_clcd_clk
r_static
r_struct
id|clk
id|cp_clcd_clk
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;CLCDCLK&quot;
comma
dot
id|params
op_assign
op_amp
id|cp_auxvco_params
comma
dot
id|setvco
op_assign
id|cp_auxvco_set
comma
)brace
suffix:semicolon
DECL|variable|cp_mmci_clk
r_static
r_struct
id|clk
id|cp_mmci_clk
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;MCLK&quot;
comma
dot
id|rate
op_assign
l_int|14745600
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Flash handling.&n; */
DECL|function|intcp_flash_init
r_static
r_int
id|intcp_flash_init
c_func
(paren
r_void
)paren
(brace
id|u32
id|val
suffix:semicolon
id|val
op_assign
id|readl
c_func
(paren
id|INTCP_VA_CTRL_BASE
op_plus
id|INTCP_FLASHPROG
)paren
suffix:semicolon
id|val
op_or_assign
id|CINTEGRATOR_FLASHPROG_FLWREN
suffix:semicolon
id|writel
c_func
(paren
id|val
comma
id|INTCP_VA_CTRL_BASE
op_plus
id|INTCP_FLASHPROG
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|intcp_flash_exit
r_static
r_void
id|intcp_flash_exit
c_func
(paren
r_void
)paren
(brace
id|u32
id|val
suffix:semicolon
id|val
op_assign
id|readl
c_func
(paren
id|INTCP_VA_CTRL_BASE
op_plus
id|INTCP_FLASHPROG
)paren
suffix:semicolon
id|val
op_and_assign
op_complement
(paren
id|CINTEGRATOR_FLASHPROG_FLVPPEN
op_or
id|CINTEGRATOR_FLASHPROG_FLWREN
)paren
suffix:semicolon
id|writel
c_func
(paren
id|val
comma
id|INTCP_VA_CTRL_BASE
op_plus
id|INTCP_FLASHPROG
)paren
suffix:semicolon
)brace
DECL|function|intcp_flash_set_vpp
r_static
r_void
id|intcp_flash_set_vpp
c_func
(paren
r_int
id|on
)paren
(brace
id|u32
id|val
suffix:semicolon
id|val
op_assign
id|readl
c_func
(paren
id|INTCP_VA_CTRL_BASE
op_plus
id|INTCP_FLASHPROG
)paren
suffix:semicolon
r_if
c_cond
(paren
id|on
)paren
id|val
op_or_assign
id|CINTEGRATOR_FLASHPROG_FLVPPEN
suffix:semicolon
r_else
id|val
op_and_assign
op_complement
id|CINTEGRATOR_FLASHPROG_FLVPPEN
suffix:semicolon
id|writel
c_func
(paren
id|val
comma
id|INTCP_VA_CTRL_BASE
op_plus
id|INTCP_FLASHPROG
)paren
suffix:semicolon
)brace
DECL|variable|intcp_flash_data
r_static
r_struct
id|flash_platform_data
id|intcp_flash_data
op_assign
(brace
dot
id|map_name
op_assign
l_string|&quot;cfi_probe&quot;
comma
dot
id|width
op_assign
l_int|4
comma
dot
id|init
op_assign
id|intcp_flash_init
comma
dot
m_exit
op_assign
id|intcp_flash_exit
comma
dot
id|set_vpp
op_assign
id|intcp_flash_set_vpp
comma
)brace
suffix:semicolon
DECL|variable|intcp_flash_resource
r_static
r_struct
id|resource
id|intcp_flash_resource
op_assign
(brace
dot
id|start
op_assign
id|INTCP_PA_FLASH_BASE
comma
dot
id|end
op_assign
id|INTCP_PA_FLASH_BASE
op_plus
id|INTCP_FLASH_SIZE
op_minus
l_int|1
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
suffix:semicolon
DECL|variable|intcp_flash_device
r_static
r_struct
id|platform_device
id|intcp_flash_device
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;armflash&quot;
comma
dot
id|id
op_assign
l_int|0
comma
dot
id|dev
op_assign
(brace
dot
id|platform_data
op_assign
op_amp
id|intcp_flash_data
comma
)brace
comma
dot
id|num_resources
op_assign
l_int|1
comma
dot
id|resource
op_assign
op_amp
id|intcp_flash_resource
comma
)brace
suffix:semicolon
DECL|variable|smc91x_resources
r_static
r_struct
id|resource
id|smc91x_resources
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
id|start
op_assign
id|INTCP_PA_ETH_BASE
comma
dot
id|end
op_assign
id|INTCP_PA_ETH_BASE
op_plus
id|INTCP_ETH_SIZE
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
(braket
l_int|1
)braket
op_assign
(brace
dot
id|start
op_assign
id|IRQ_CP_ETHINT
comma
dot
id|end
op_assign
id|IRQ_CP_ETHINT
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|smc91x_device
r_static
r_struct
id|platform_device
id|smc91x_device
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;smc91x&quot;
comma
dot
id|id
op_assign
l_int|0
comma
dot
id|num_resources
op_assign
id|ARRAY_SIZE
c_func
(paren
id|smc91x_resources
)paren
comma
dot
id|resource
op_assign
id|smc91x_resources
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|platform_device
op_star
id|intcp_devs
(braket
)braket
id|__initdata
op_assign
(brace
op_amp
id|intcp_flash_device
comma
op_amp
id|smc91x_device
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * It seems that the card insertion interrupt remains active after&n; * we&squot;ve acknowledged it.  We therefore ignore the interrupt, and&n; * rely on reading it from the SIC.  This also means that we must&n; * clear the latched interrupt.&n; */
DECL|function|mmc_status
r_static
r_int
r_int
id|mmc_status
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
r_int
id|status
op_assign
id|readl
c_func
(paren
l_int|0xfca00004
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|8
comma
l_int|0xfcb00008
)paren
suffix:semicolon
r_return
id|status
op_amp
l_int|8
suffix:semicolon
)brace
DECL|variable|mmc_data
r_static
r_struct
id|mmc_platform_data
id|mmc_data
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
DECL|variable|mmc_device
r_static
r_struct
id|amba_device
id|mmc_device
op_assign
(brace
dot
id|dev
op_assign
(brace
dot
id|bus_id
op_assign
l_string|&quot;mb:1c&quot;
comma
dot
id|platform_data
op_assign
op_amp
id|mmc_data
comma
)brace
comma
dot
id|res
op_assign
(brace
dot
id|start
op_assign
id|INTCP_PA_MMC_BASE
comma
dot
id|end
op_assign
id|INTCP_PA_MMC_BASE
op_plus
id|SZ_4K
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
dot
id|irq
op_assign
(brace
id|IRQ_CP_MMCIINT0
comma
id|IRQ_CP_MMCIINT1
)brace
comma
dot
id|periphid
op_assign
l_int|0
comma
)brace
suffix:semicolon
DECL|variable|aaci_device
r_static
r_struct
id|amba_device
id|aaci_device
op_assign
(brace
dot
id|dev
op_assign
(brace
dot
id|bus_id
op_assign
l_string|&quot;mb:1d&quot;
comma
)brace
comma
dot
id|res
op_assign
(brace
dot
id|start
op_assign
id|INTCP_PA_AACI_BASE
comma
dot
id|end
op_assign
id|INTCP_PA_AACI_BASE
op_plus
id|SZ_4K
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
dot
id|irq
op_assign
(brace
id|IRQ_CP_AACIINT
comma
id|NO_IRQ
)brace
comma
dot
id|periphid
op_assign
l_int|0
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * CLCD support&n; */
DECL|variable|vga
r_static
r_struct
id|clcd_panel
id|vga
op_assign
(brace
dot
id|mode
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;VGA&quot;
comma
dot
id|refresh
op_assign
l_int|60
comma
dot
id|xres
op_assign
l_int|640
comma
dot
id|yres
op_assign
l_int|480
comma
dot
id|pixclock
op_assign
l_int|39721
comma
dot
id|left_margin
op_assign
l_int|40
comma
dot
id|right_margin
op_assign
l_int|24
comma
dot
id|upper_margin
op_assign
l_int|32
comma
dot
id|lower_margin
op_assign
l_int|11
comma
dot
id|hsync_len
op_assign
l_int|96
comma
dot
id|vsync_len
op_assign
l_int|2
comma
dot
id|sync
op_assign
l_int|0
comma
dot
id|vmode
op_assign
id|FB_VMODE_NONINTERLACED
comma
)brace
comma
dot
id|width
op_assign
op_minus
l_int|1
comma
dot
id|height
op_assign
op_minus
l_int|1
comma
dot
id|tim2
op_assign
id|TIM2_BCD
op_or
id|TIM2_IPC
comma
dot
id|cntl
op_assign
id|CNTL_LCDTFT
op_or
id|CNTL_LCDVCOMP
c_func
(paren
l_int|1
)paren
comma
dot
id|bpp
op_assign
l_int|16
comma
dot
id|grayscale
op_assign
l_int|0
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Ensure VGA is selected.&n; */
DECL|function|cp_clcd_enable
r_static
r_void
id|cp_clcd_enable
c_func
(paren
r_struct
id|clcd_fb
op_star
id|fb
)paren
(brace
id|cm_control
c_func
(paren
id|CM_CTRL_LCDMUXSEL_MASK
comma
id|CM_CTRL_LCDMUXSEL_VGA
)paren
suffix:semicolon
)brace
DECL|variable|framesize
r_static
r_int
r_int
id|framesize
op_assign
id|SZ_1M
suffix:semicolon
DECL|function|cp_clcd_setup
r_static
r_int
id|cp_clcd_setup
c_func
(paren
r_struct
id|clcd_fb
op_star
id|fb
)paren
(brace
id|dma_addr_t
id|dma
suffix:semicolon
id|fb-&gt;panel
op_assign
op_amp
id|vga
suffix:semicolon
id|fb-&gt;fb.screen_base
op_assign
id|dma_alloc_writecombine
c_func
(paren
op_amp
id|fb-&gt;dev-&gt;dev
comma
id|framesize
comma
op_amp
id|dma
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fb-&gt;fb.screen_base
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;CLCD: unable to map framebuffer&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|fb-&gt;fb.fix.smem_start
op_assign
id|dma
suffix:semicolon
id|fb-&gt;fb.fix.smem_len
op_assign
id|framesize
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cp_clcd_remove
r_static
r_void
id|cp_clcd_remove
c_func
(paren
r_struct
id|clcd_fb
op_star
id|fb
)paren
(brace
id|dma_free_writecombine
c_func
(paren
op_amp
id|fb-&gt;dev-&gt;dev
comma
id|fb-&gt;fb.fix.smem_len
comma
id|fb-&gt;fb.screen_base
comma
id|fb-&gt;fb.fix.smem_start
)paren
suffix:semicolon
)brace
DECL|variable|clcd_data
r_static
r_struct
id|clcd_board
id|clcd_data
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Integrator/CP&quot;
comma
dot
id|check
op_assign
id|clcdfb_check
comma
dot
id|decode
op_assign
id|clcdfb_decode
comma
dot
id|enable
op_assign
id|cp_clcd_enable
comma
dot
id|setup
op_assign
id|cp_clcd_setup
comma
dot
id|remove
op_assign
id|cp_clcd_remove
comma
)brace
suffix:semicolon
DECL|variable|clcd_device
r_static
r_struct
id|amba_device
id|clcd_device
op_assign
(brace
dot
id|dev
op_assign
(brace
dot
id|bus_id
op_assign
l_string|&quot;mb:c0&quot;
comma
dot
id|coherent_dma_mask
op_assign
op_complement
l_int|0
comma
dot
id|platform_data
op_assign
op_amp
id|clcd_data
comma
)brace
comma
dot
id|res
op_assign
(brace
dot
id|start
op_assign
id|INTCP_PA_CLCD_BASE
comma
dot
id|end
op_assign
id|INTCP_PA_CLCD_BASE
op_plus
id|SZ_4K
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
dot
id|dma_mask
op_assign
op_complement
l_int|0
comma
dot
id|irq
op_assign
(brace
id|IRQ_CP_CLCDCINT
comma
id|NO_IRQ
)brace
comma
dot
id|periphid
op_assign
l_int|0
comma
)brace
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
id|mmc_device
comma
op_amp
id|aaci_device
comma
op_amp
id|clcd_device
comma
)brace
suffix:semicolon
DECL|function|intcp_init
r_static
r_void
id|__init
id|intcp_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|clk_register
c_func
(paren
op_amp
id|cp_clcd_clk
)paren
suffix:semicolon
id|clk_register
c_func
(paren
op_amp
id|cp_mmci_clk
)paren
suffix:semicolon
id|platform_add_devices
c_func
(paren
id|intcp_devs
comma
id|ARRAY_SIZE
c_func
(paren
id|intcp_devs
)paren
)paren
suffix:semicolon
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
DECL|macro|TIMER_CTRL_IE
mdefine_line|#define TIMER_CTRL_IE&t;(1 &lt;&lt; 5)&t;&t;&t;/* Interrupt Enable */
DECL|function|intcp_init_time
r_static
r_void
id|__init
id|intcp_init_time
c_func
(paren
r_void
)paren
(brace
id|integrator_time_init
c_func
(paren
l_int|1000000
op_div
id|HZ
comma
id|TIMER_CTRL_IE
)paren
suffix:semicolon
)brace
id|MACHINE_START
c_func
(paren
id|CINTEGRATOR
comma
l_string|&quot;ARM-IntegratorCP&quot;
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
l_int|0x16000000
comma
l_int|0xf1600000
)paren
id|BOOT_PARAMS
c_func
(paren
l_int|0x00000100
)paren
id|MAPIO
c_func
(paren
id|intcp_map_io
)paren
id|INITIRQ
c_func
(paren
id|intcp_init_irq
)paren
id|INITTIME
c_func
(paren
id|intcp_init_time
)paren
id|INIT_MACHINE
c_func
(paren
id|intcp_init
)paren
id|MACHINE_END
eof
