multiline_comment|/*&n; *  linux/arch/arm/mach-versatile/core.c&n; *&n; *  Copyright (C) 1999 - 2003 ARM Limited&n; *  Copyright (C) 2000 Deep Blue Solutions Ltd&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/sysdev.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/leds.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/hardware/amba.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/flash.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/mmc.h&gt;
multiline_comment|/*&n; * All IO addresses are mapped onto VA 0xFFFx.xxxx, where x.xxxx&n; * is the (PA &gt;&gt; 12).&n; *&n; * Setup a VA for the Versatile Vectored Interrupt Controller.&n; */
DECL|macro|VA_VIC_BASE
mdefine_line|#define VA_VIC_BASE&t;&t; IO_ADDRESS(VERSATILE_VIC_BASE)
DECL|macro|VA_SIC_BASE
mdefine_line|#define VA_SIC_BASE&t;&t; IO_ADDRESS(VERSATILE_SIC_BASE)
DECL|function|vic_mask_irq
r_static
r_void
id|vic_mask_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|irq
op_sub_assign
id|IRQ_VIC_START
suffix:semicolon
id|writel
c_func
(paren
l_int|1
op_lshift
id|irq
comma
id|VA_VIC_BASE
op_plus
id|VIC_IRQ_ENABLE_CLEAR
)paren
suffix:semicolon
)brace
DECL|function|vic_unmask_irq
r_static
r_void
id|vic_unmask_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|irq
op_sub_assign
id|IRQ_VIC_START
suffix:semicolon
id|writel
c_func
(paren
l_int|1
op_lshift
id|irq
comma
id|VA_VIC_BASE
op_plus
id|VIC_IRQ_ENABLE
)paren
suffix:semicolon
)brace
DECL|variable|vic_chip
r_static
r_struct
id|irqchip
id|vic_chip
op_assign
(brace
dot
id|ack
op_assign
id|vic_mask_irq
comma
dot
id|mask
op_assign
id|vic_mask_irq
comma
dot
id|unmask
op_assign
id|vic_unmask_irq
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
id|writel
c_func
(paren
l_int|1
op_lshift
id|irq
comma
id|VA_SIC_BASE
op_plus
id|SIC_IRQ_ENABLE_CLEAR
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
id|writel
c_func
(paren
l_int|1
op_lshift
id|irq
comma
id|VA_SIC_BASE
op_plus
id|SIC_IRQ_ENABLE_SET
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
id|readl
c_func
(paren
id|VA_SIC_BASE
op_plus
id|SIC_IRQ_STATUS
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
macro_line|#if 1
DECL|macro|IRQ_MMCI0A
mdefine_line|#define IRQ_MMCI0A&t;IRQ_VICSOURCE22
DECL|macro|IRQ_MMCI1A
mdefine_line|#define IRQ_MMCI1A&t;IRQ_VICSOURCE23
DECL|macro|IRQ_AACI
mdefine_line|#define IRQ_AACI&t;IRQ_VICSOURCE24
DECL|macro|IRQ_ETH
mdefine_line|#define IRQ_ETH&t;&t;IRQ_VICSOURCE25
DECL|macro|PIC_MASK
mdefine_line|#define PIC_MASK&t;0xFFD00000
macro_line|#else
DECL|macro|IRQ_MMCI0A
mdefine_line|#define IRQ_MMCI0A&t;IRQ_SIC_MMCI0A
DECL|macro|IRQ_MMCI1A
mdefine_line|#define IRQ_MMCI1A&t;IRQ_SIC_MMCI1A
DECL|macro|IRQ_AACI
mdefine_line|#define IRQ_AACI&t;IRQ_SIC_AACI
DECL|macro|IRQ_ETH
mdefine_line|#define IRQ_ETH&t;&t;IRQ_SIC_ETH
DECL|macro|PIC_MASK
mdefine_line|#define PIC_MASK&t;0
macro_line|#endif
DECL|function|versatile_init_irq
r_static
r_void
id|__init
id|versatile_init_irq
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|i
comma
id|value
suffix:semicolon
multiline_comment|/* Disable all interrupts initially. */
id|writel
c_func
(paren
l_int|0
comma
id|VA_VIC_BASE
op_plus
id|VIC_INT_SELECT
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|0
comma
id|VA_VIC_BASE
op_plus
id|VIC_IRQ_ENABLE
)paren
suffix:semicolon
id|writel
c_func
(paren
op_complement
l_int|0
comma
id|VA_VIC_BASE
op_plus
id|VIC_IRQ_ENABLE_CLEAR
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|0
comma
id|VA_VIC_BASE
op_plus
id|VIC_IRQ_STATUS
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|0
comma
id|VA_VIC_BASE
op_plus
id|VIC_ITCR
)paren
suffix:semicolon
id|writel
c_func
(paren
op_complement
l_int|0
comma
id|VA_VIC_BASE
op_plus
id|VIC_IRQ_SOFT_CLEAR
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Make sure we clear all existing interrupts&n;&t; */
id|writel
c_func
(paren
l_int|0
comma
id|VA_VIC_BASE
op_plus
id|VIC_VECT_ADDR
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
l_int|19
suffix:semicolon
id|i
op_increment
)paren
(brace
id|value
op_assign
id|readl
c_func
(paren
id|VA_VIC_BASE
op_plus
id|VIC_VECT_ADDR
)paren
suffix:semicolon
id|writel
c_func
(paren
id|value
comma
id|VA_VIC_BASE
op_plus
id|VIC_VECT_ADDR
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|i
op_increment
)paren
(brace
id|value
op_assign
id|readl
c_func
(paren
id|VA_VIC_BASE
op_plus
id|VIC_VECT_CNTL0
op_plus
(paren
id|i
op_star
l_int|4
)paren
)paren
suffix:semicolon
id|writel
c_func
(paren
id|value
op_or
id|VICVectCntl_Enable
op_or
id|i
comma
id|VA_VIC_BASE
op_plus
id|VIC_VECT_CNTL0
op_plus
(paren
id|i
op_star
l_int|4
)paren
)paren
suffix:semicolon
)brace
id|writel
c_func
(paren
l_int|32
comma
id|VA_VIC_BASE
op_plus
id|VIC_DEF_VECT_ADDR
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|IRQ_VIC_START
suffix:semicolon
id|i
op_le
id|IRQ_VIC_END
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i
op_ne
id|IRQ_VICSOURCE31
)paren
(brace
id|set_irq_chip
c_func
(paren
id|i
comma
op_amp
id|vic_chip
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
)brace
id|set_irq_handler
c_func
(paren
id|IRQ_VICSOURCE31
comma
id|sic_handle_irq
)paren
suffix:semicolon
id|vic_unmask_irq
c_func
(paren
id|IRQ_VICSOURCE31
)paren
suffix:semicolon
multiline_comment|/* Do second interrupt controller */
id|writel
c_func
(paren
op_complement
l_int|0
comma
id|VA_SIC_BASE
op_plus
id|SIC_IRQ_ENABLE_CLEAR
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
r_if
c_cond
(paren
(paren
id|PIC_MASK
op_amp
(paren
l_int|1
op_lshift
(paren
id|i
op_minus
id|IRQ_SIC_START
)paren
)paren
)paren
op_eq
l_int|0
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
)brace
multiline_comment|/*&n;&t; * Interrupts on secondary controller from 0 to 8 are routed to&n;&t; * source 31 on PIC.&n;&t; * Interrupts from 21 to 31 are routed directly to the VIC on&n;&t; * the corresponding number on primary controller. This is controlled&n;&t; * by setting PIC_ENABLEx.&n;&t; */
id|writel
c_func
(paren
id|PIC_MASK
comma
id|VA_SIC_BASE
op_plus
id|SIC_INT_PIC_ENABLE
)paren
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|versatile_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|IO_ADDRESS
c_func
(paren
id|VERSATILE_SYS_BASE
)paren
comma
id|VERSATILE_SYS_BASE
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
id|VERSATILE_SIC_BASE
)paren
comma
id|VERSATILE_SIC_BASE
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
id|VERSATILE_VIC_BASE
)paren
comma
id|VERSATILE_VIC_BASE
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
id|VERSATILE_SCTL_BASE
)paren
comma
id|VERSATILE_SCTL_BASE
comma
id|SZ_4K
op_star
l_int|9
comma
id|MT_DEVICE
)brace
comma
macro_line|#ifdef CONFIG_DEBUG_LL
(brace
id|IO_ADDRESS
c_func
(paren
id|VERSATILE_UART0_BASE
)paren
comma
id|VERSATILE_UART0_BASE
comma
id|SZ_4K
comma
id|MT_DEVICE
)brace
comma
macro_line|#endif
macro_line|#ifdef FIXME
(brace
id|PCI_MEMORY_VADDR
comma
id|PHYS_PCI_MEM_BASE
comma
id|SZ_16M
comma
id|MT_DEVICE
)brace
comma
(brace
id|PCI_CONFIG_VADDR
comma
id|PHYS_PCI_CONFIG_BASE
comma
id|SZ_16M
comma
id|MT_DEVICE
)brace
comma
(brace
id|PCI_V3_VADDR
comma
id|PHYS_PCI_V3_BASE
comma
id|SZ_512K
comma
id|MT_DEVICE
)brace
comma
(brace
id|PCI_IO_VADDR
comma
id|PHYS_PCI_IO_BASE
comma
id|SZ_64K
comma
id|MT_DEVICE
)brace
comma
macro_line|#endif
)brace
suffix:semicolon
DECL|function|versatile_map_io
r_static
r_void
id|__init
id|versatile_map_io
c_func
(paren
r_void
)paren
(brace
id|iotable_init
c_func
(paren
id|versatile_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|versatile_io_desc
)paren
)paren
suffix:semicolon
)brace
DECL|macro|VERSATILE_REFCOUNTER
mdefine_line|#define VERSATILE_REFCOUNTER&t;(IO_ADDRESS(VERSATILE_SYS_BASE) + VERSATILE_SYS_24MHz_OFFSET)
multiline_comment|/*&n; * This is the VersatilePB sched_clock implementation.  This has&n; * a resolution of 41.7ns, and a maximum value of about 179s.&n; */
DECL|function|sched_clock
r_int
r_int
r_int
id|sched_clock
c_func
(paren
r_void
)paren
(brace
r_int
r_int
r_int
id|v
suffix:semicolon
id|v
op_assign
(paren
r_int
r_int
r_int
)paren
id|readl
c_func
(paren
id|VERSATILE_REFCOUNTER
)paren
op_star
l_int|125
suffix:semicolon
id|do_div
c_func
(paren
id|v
comma
l_int|3
)paren
suffix:semicolon
r_return
id|v
suffix:semicolon
)brace
DECL|macro|VERSATILE_FLASHCTRL
mdefine_line|#define VERSATILE_FLASHCTRL    (IO_ADDRESS(VERSATILE_SYS_BASE) + VERSATILE_SYS_FLASH_OFFSET)
DECL|function|versatile_flash_init
r_static
r_int
id|versatile_flash_init
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
id|__raw_readl
c_func
(paren
id|VERSATILE_FLASHCTRL
)paren
suffix:semicolon
id|val
op_and_assign
op_complement
id|VERSATILE_FLASHPROG_FLVPPEN
suffix:semicolon
id|__raw_writel
c_func
(paren
id|val
comma
id|VERSATILE_FLASHCTRL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|versatile_flash_exit
r_static
r_void
id|versatile_flash_exit
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
id|__raw_readl
c_func
(paren
id|VERSATILE_FLASHCTRL
)paren
suffix:semicolon
id|val
op_and_assign
op_complement
id|VERSATILE_FLASHPROG_FLVPPEN
suffix:semicolon
id|__raw_writel
c_func
(paren
id|val
comma
id|VERSATILE_FLASHCTRL
)paren
suffix:semicolon
)brace
DECL|function|versatile_flash_set_vpp
r_static
r_void
id|versatile_flash_set_vpp
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
id|__raw_readl
c_func
(paren
id|VERSATILE_FLASHCTRL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|on
)paren
id|val
op_or_assign
id|VERSATILE_FLASHPROG_FLVPPEN
suffix:semicolon
r_else
id|val
op_and_assign
op_complement
id|VERSATILE_FLASHPROG_FLVPPEN
suffix:semicolon
id|__raw_writel
c_func
(paren
id|val
comma
id|VERSATILE_FLASHCTRL
)paren
suffix:semicolon
)brace
DECL|variable|versatile_flash_data
r_static
r_struct
id|flash_platform_data
id|versatile_flash_data
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
id|versatile_flash_init
comma
dot
m_exit
op_assign
id|versatile_flash_exit
comma
dot
id|set_vpp
op_assign
id|versatile_flash_set_vpp
comma
)brace
suffix:semicolon
DECL|variable|versatile_flash_resource
r_static
r_struct
id|resource
id|versatile_flash_resource
op_assign
(brace
dot
id|start
op_assign
id|VERSATILE_FLASH_BASE
comma
dot
id|end
op_assign
id|VERSATILE_FLASH_BASE
op_plus
id|VERSATILE_FLASH_SIZE
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
suffix:semicolon
DECL|variable|versatile_flash_device
r_static
r_struct
id|platform_device
id|versatile_flash_device
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
id|versatile_flash_data
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
id|versatile_flash_resource
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
id|VERSATILE_ETH_BASE
comma
dot
id|end
op_assign
id|VERSATILE_ETH_BASE
op_plus
id|SZ_64K
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
id|IRQ_ETH
comma
dot
id|end
op_assign
id|IRQ_ETH
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
DECL|macro|VERSATILE_SYSMCI
mdefine_line|#define VERSATILE_SYSMCI&t;(IO_ADDRESS(VERSATILE_SYS_BASE) + VERSATILE_SYS_MCI_OFFSET)
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
r_struct
id|amba_device
op_star
id|adev
op_assign
id|container_of
c_func
(paren
id|dev
comma
r_struct
id|amba_device
comma
id|dev
)paren
suffix:semicolon
id|u32
id|mask
suffix:semicolon
r_if
c_cond
(paren
id|adev-&gt;res.start
op_eq
id|VERSATILE_MMCI0_BASE
)paren
id|mask
op_assign
l_int|1
suffix:semicolon
r_else
id|mask
op_assign
l_int|2
suffix:semicolon
r_return
id|readl
c_func
(paren
id|VERSATILE_SYSMCI
)paren
op_amp
id|mask
suffix:semicolon
)brace
DECL|variable|mmc0_plat_data
r_static
r_struct
id|mmc_platform_data
id|mmc0_plat_data
op_assign
(brace
dot
id|mclk
op_assign
l_int|33000000
comma
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
DECL|variable|mmc1_plat_data
r_static
r_struct
id|mmc_platform_data
id|mmc1_plat_data
op_assign
(brace
dot
id|mclk
op_assign
l_int|33000000
comma
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
DECL|macro|AMBA_DEVICE
mdefine_line|#define AMBA_DEVICE(name,busid,base,plat)&t;&t;&t;&bslash;&n;static struct amba_device name##_device = {&t;&t;&t;&bslash;&n;&t;.dev&t;&t;= {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;.coherent_dma_mask = ~0,&t;&t;&t;&bslash;&n;&t;&t;.bus_id&t;= busid,&t;&t;&t;&t;&bslash;&n;&t;&t;.platform_data = plat,&t;&t;&t;&t;&bslash;&n;&t;},&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.res&t;&t;= {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;.start&t;= VERSATILE_##base##_BASE,&t;&t;&bslash;&n;&t;&t;.end&t;= (VERSATILE_##base##_BASE) + SZ_4K - 1,&bslash;&n;&t;&t;.flags&t;= IORESOURCE_MEM,&t;&t;&t;&bslash;&n;&t;},&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.irq&t;&t;= base##_IRQ,&t;&t;&t;&t;&bslash;&n;&t;/* .dma&t;&t;= base##_DMA,*/&t;&t;&t;&t;&bslash;&n;}
DECL|macro|AACI_IRQ
mdefine_line|#define AACI_IRQ&t;{ IRQ_AACI, NO_IRQ }
DECL|macro|AACI_DMA
mdefine_line|#define AACI_DMA&t;{ 0x80, 0x81 }
DECL|macro|MMCI0_IRQ
mdefine_line|#define MMCI0_IRQ&t;{ IRQ_MMCI0A,IRQ_SIC_MMCI0B }
DECL|macro|MMCI0_DMA
mdefine_line|#define MMCI0_DMA&t;{ 0x84, 0 }
DECL|macro|KMI0_IRQ
mdefine_line|#define KMI0_IRQ&t;{ IRQ_SIC_KMI0, NO_IRQ }
DECL|macro|KMI0_DMA
mdefine_line|#define KMI0_DMA&t;{ 0, 0 }
DECL|macro|KMI1_IRQ
mdefine_line|#define KMI1_IRQ&t;{ IRQ_SIC_KMI1, NO_IRQ }
DECL|macro|KMI1_DMA
mdefine_line|#define KMI1_DMA&t;{ 0, 0 }
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
multiline_comment|/*&n; * These devices are connected directly to the multi-layer AHB switch&n; */
DECL|macro|SMC_IRQ
mdefine_line|#define SMC_IRQ&t;&t;{ NO_IRQ, NO_IRQ }
DECL|macro|SMC_DMA
mdefine_line|#define SMC_DMA&t;&t;{ 0, 0 }
DECL|macro|MPMC_IRQ
mdefine_line|#define MPMC_IRQ&t;{ NO_IRQ, NO_IRQ }
DECL|macro|MPMC_DMA
mdefine_line|#define MPMC_DMA&t;{ 0, 0 }
DECL|macro|CLCD_IRQ
mdefine_line|#define CLCD_IRQ&t;{ IRQ_CLCDINT, NO_IRQ }
DECL|macro|CLCD_DMA
mdefine_line|#define CLCD_DMA&t;{ 0, 0 }
DECL|macro|DMAC_IRQ
mdefine_line|#define DMAC_IRQ&t;{ IRQ_DMAINT, NO_IRQ }
DECL|macro|DMAC_DMA
mdefine_line|#define DMAC_DMA&t;{ 0, 0 }
multiline_comment|/*&n; * These devices are connected via the core APB bridge&n; */
DECL|macro|SCTL_IRQ
mdefine_line|#define SCTL_IRQ&t;{ NO_IRQ, NO_IRQ }
DECL|macro|SCTL_DMA
mdefine_line|#define SCTL_DMA&t;{ 0, 0 }
DECL|macro|WATCHDOG_IRQ
mdefine_line|#define WATCHDOG_IRQ&t;{ IRQ_WDOGINT, NO_IRQ }
DECL|macro|WATCHDOG_DMA
mdefine_line|#define WATCHDOG_DMA&t;{ 0, 0 }
DECL|macro|GPIO0_IRQ
mdefine_line|#define GPIO0_IRQ&t;{ IRQ_GPIOINT0, NO_IRQ }
DECL|macro|GPIO0_DMA
mdefine_line|#define GPIO0_DMA&t;{ 0, 0 }
DECL|macro|GPIO1_IRQ
mdefine_line|#define GPIO1_IRQ&t;{ IRQ_GPIOINT1, NO_IRQ }
DECL|macro|GPIO1_DMA
mdefine_line|#define GPIO1_DMA&t;{ 0, 0 }
DECL|macro|GPIO2_IRQ
mdefine_line|#define GPIO2_IRQ&t;{ IRQ_GPIOINT2, NO_IRQ }
DECL|macro|GPIO2_DMA
mdefine_line|#define GPIO2_DMA&t;{ 0, 0 }
DECL|macro|GPIO3_IRQ
mdefine_line|#define GPIO3_IRQ&t;{ IRQ_GPIOINT3, NO_IRQ }
DECL|macro|GPIO3_DMA
mdefine_line|#define GPIO3_DMA&t;{ 0, 0 }
DECL|macro|RTC_IRQ
mdefine_line|#define RTC_IRQ&t;&t;{ IRQ_RTCINT, NO_IRQ }
DECL|macro|RTC_DMA
mdefine_line|#define RTC_DMA&t;&t;{ 0, 0 }
multiline_comment|/*&n; * These devices are connected via the DMA APB bridge&n; */
DECL|macro|SCI_IRQ
mdefine_line|#define SCI_IRQ&t;&t;{ IRQ_SCIINT, NO_IRQ }
DECL|macro|SCI_DMA
mdefine_line|#define SCI_DMA&t;&t;{ 7, 6 }
DECL|macro|UART0_IRQ
mdefine_line|#define UART0_IRQ&t;{ IRQ_UARTINT0, NO_IRQ }
DECL|macro|UART0_DMA
mdefine_line|#define UART0_DMA&t;{ 15, 14 }
DECL|macro|UART1_IRQ
mdefine_line|#define UART1_IRQ&t;{ IRQ_UARTINT1, NO_IRQ }
DECL|macro|UART1_DMA
mdefine_line|#define UART1_DMA&t;{ 13, 12 }
DECL|macro|UART2_IRQ
mdefine_line|#define UART2_IRQ&t;{ IRQ_UARTINT2, NO_IRQ }
DECL|macro|UART2_DMA
mdefine_line|#define UART2_DMA&t;{ 11, 10 }
DECL|macro|SSP_IRQ
mdefine_line|#define SSP_IRQ&t;&t;{ IRQ_SSPINT, NO_IRQ }
DECL|macro|SSP_DMA
mdefine_line|#define SSP_DMA&t;&t;{ 9, 8 }
multiline_comment|/* FPGA Primecells */
id|AMBA_DEVICE
c_func
(paren
id|aaci
comma
l_string|&quot;fpga:04&quot;
comma
id|AACI
comma
l_int|NULL
)paren
suffix:semicolon
id|AMBA_DEVICE
c_func
(paren
id|mmc0
comma
l_string|&quot;fpga:05&quot;
comma
id|MMCI0
comma
op_amp
id|mmc0_plat_data
)paren
suffix:semicolon
id|AMBA_DEVICE
c_func
(paren
id|kmi0
comma
l_string|&quot;fpga:06&quot;
comma
id|KMI0
comma
l_int|NULL
)paren
suffix:semicolon
id|AMBA_DEVICE
c_func
(paren
id|kmi1
comma
l_string|&quot;fpga:07&quot;
comma
id|KMI1
comma
l_int|NULL
)paren
suffix:semicolon
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
id|smc
comma
l_string|&quot;dev:00&quot;
comma
id|SMC
comma
l_int|NULL
)paren
suffix:semicolon
id|AMBA_DEVICE
c_func
(paren
id|mpmc
comma
l_string|&quot;dev:10&quot;
comma
id|MPMC
comma
l_int|NULL
)paren
suffix:semicolon
id|AMBA_DEVICE
c_func
(paren
id|clcd
comma
l_string|&quot;dev:20&quot;
comma
id|CLCD
comma
l_int|NULL
)paren
suffix:semicolon
id|AMBA_DEVICE
c_func
(paren
id|dmac
comma
l_string|&quot;dev:30&quot;
comma
id|DMAC
comma
l_int|NULL
)paren
suffix:semicolon
id|AMBA_DEVICE
c_func
(paren
id|sctl
comma
l_string|&quot;dev:e0&quot;
comma
id|SCTL
comma
l_int|NULL
)paren
suffix:semicolon
id|AMBA_DEVICE
c_func
(paren
id|wdog
comma
l_string|&quot;dev:e1&quot;
comma
id|WATCHDOG
comma
l_int|NULL
)paren
suffix:semicolon
id|AMBA_DEVICE
c_func
(paren
id|gpio0
comma
l_string|&quot;dev:e4&quot;
comma
id|GPIO0
comma
l_int|NULL
)paren
suffix:semicolon
id|AMBA_DEVICE
c_func
(paren
id|gpio1
comma
l_string|&quot;dev:e5&quot;
comma
id|GPIO1
comma
l_int|NULL
)paren
suffix:semicolon
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
id|AMBA_DEVICE
c_func
(paren
id|rtc
comma
l_string|&quot;dev:e8&quot;
comma
id|RTC
comma
l_int|NULL
)paren
suffix:semicolon
id|AMBA_DEVICE
c_func
(paren
id|sci0
comma
l_string|&quot;dev:f0&quot;
comma
id|SCI
comma
l_int|NULL
)paren
suffix:semicolon
id|AMBA_DEVICE
c_func
(paren
id|uart0
comma
l_string|&quot;dev:f1&quot;
comma
id|UART0
comma
l_int|NULL
)paren
suffix:semicolon
id|AMBA_DEVICE
c_func
(paren
id|uart1
comma
l_string|&quot;dev:f2&quot;
comma
id|UART1
comma
l_int|NULL
)paren
suffix:semicolon
id|AMBA_DEVICE
c_func
(paren
id|uart2
comma
l_string|&quot;dev:f3&quot;
comma
id|UART2
comma
l_int|NULL
)paren
suffix:semicolon
id|AMBA_DEVICE
c_func
(paren
id|ssp0
comma
l_string|&quot;dev:f4&quot;
comma
id|SSP
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
id|dmac_device
comma
op_amp
id|uart0_device
comma
op_amp
id|uart1_device
comma
op_amp
id|uart2_device
comma
op_amp
id|uart3_device
comma
op_amp
id|smc_device
comma
op_amp
id|mpmc_device
comma
op_amp
id|clcd_device
comma
op_amp
id|sctl_device
comma
op_amp
id|wdog_device
comma
op_amp
id|gpio0_device
comma
op_amp
id|gpio1_device
comma
op_amp
id|gpio2_device
comma
op_amp
id|gpio3_device
comma
op_amp
id|rtc_device
comma
op_amp
id|sci0_device
comma
op_amp
id|ssp0_device
comma
op_amp
id|aaci_device
comma
op_amp
id|mmc0_device
comma
op_amp
id|kmi0_device
comma
op_amp
id|kmi1_device
comma
op_amp
id|sci1_device
comma
op_amp
id|mmc1_device
comma
)brace
suffix:semicolon
DECL|macro|VA_LEDS_BASE
mdefine_line|#define VA_LEDS_BASE (IO_ADDRESS(VERSATILE_SYS_BASE) + VERSATILE_SYS_LED_OFFSET)
DECL|function|versatile_leds_event
r_static
r_void
id|versatile_leds_event
c_func
(paren
id|led_event_t
id|ledevt
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|u32
id|val
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|val
op_assign
id|readl
c_func
(paren
id|VA_LEDS_BASE
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|ledevt
)paren
(brace
r_case
id|led_idle_start
suffix:colon
id|val
op_assign
id|val
op_amp
op_complement
id|VERSATILE_SYS_LED0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|led_idle_end
suffix:colon
id|val
op_assign
id|val
op_or
id|VERSATILE_SYS_LED0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|led_timer
suffix:colon
id|val
op_assign
id|val
op_xor
id|VERSATILE_SYS_LED1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|led_halted
suffix:colon
id|val
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|writel
c_func
(paren
id|val
comma
id|VA_LEDS_BASE
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|versatile_init
r_static
r_void
id|__init
id|versatile_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|platform_add_device
c_func
(paren
op_amp
id|versatile_flash_device
)paren
suffix:semicolon
id|platform_add_device
c_func
(paren
op_amp
id|smc91x_device
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
id|leds_event
op_assign
id|versatile_leds_event
suffix:semicolon
)brace
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
id|INIT_MACHINE
c_func
(paren
id|versatile_init
)paren
id|MACHINE_END
eof
