multiline_comment|/*&n; *  linux/arch/arm/mach-integrator/integrator_ap.c&n; *&n; *  Copyright (C) 2000-2003 Deep Blue Solutions Ltd&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/device.h&gt;
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
macro_line|#include &lt;asm/arch/lm.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/flash.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/time.h&gt;
macro_line|#include &quot;common.h&quot;
multiline_comment|/* &n; * All IO addresses are mapped onto VA 0xFFFx.xxxx, where x.xxxx&n; * is the (PA &gt;&gt; 12).&n; *&n; * Setup a VA for the Integrator interrupt controller (for header #0,&n; * just for now).&n; */
DECL|macro|VA_IC_BASE
mdefine_line|#define VA_IC_BASE&t;IO_ADDRESS(INTEGRATOR_IC_BASE) 
DECL|macro|VA_SC_BASE
mdefine_line|#define VA_SC_BASE&t;IO_ADDRESS(INTEGRATOR_SC_BASE)
DECL|macro|VA_EBI_BASE
mdefine_line|#define VA_EBI_BASE&t;IO_ADDRESS(INTEGRATOR_EBI_BASE)
DECL|macro|VA_CMIC_BASE
mdefine_line|#define VA_CMIC_BASE&t;IO_ADDRESS(INTEGRATOR_HDR_BASE) + INTEGRATOR_HDR_IC_OFFSET
multiline_comment|/*&n; * Logical      Physical&n; * e8000000&t;40000000&t;PCI memory&t;&t;PHYS_PCI_MEM_BASE&t;(max 512M)&n; * ec000000&t;61000000&t;PCI config space&t;PHYS_PCI_CONFIG_BASE&t;(max 16M)&n; * ed000000&t;62000000&t;PCI V3 regs&t;&t;PHYS_PCI_V3_BASE&t;(max 64k)&n; * ee000000&t;60000000&t;PCI IO&t;&t;&t;PHYS_PCI_IO_BASE&t;(max 16M)&n; * ef000000&t;&t;&t;Cache flush&n; * f1000000&t;10000000&t;Core module registers&n; * f1100000&t;11000000&t;System controller registers&n; * f1200000&t;12000000&t;EBI registers&n; * f1300000&t;13000000&t;Counter/Timer&n; * f1400000&t;14000000&t;Interrupt controller&n; * f1600000&t;16000000&t;UART 0&n; * f1700000&t;17000000&t;UART 1&n; * f1a00000&t;1a000000&t;Debug LEDs&n; * f1b00000&t;1b000000&t;GPIO&n; */
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|ap_io_desc
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
id|SZ_64K
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
)brace
suffix:semicolon
DECL|function|ap_map_io
r_static
r_void
id|__init
id|ap_map_io
c_func
(paren
r_void
)paren
(brace
id|iotable_init
c_func
(paren
id|ap_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|ap_io_desc
)paren
)paren
suffix:semicolon
)brace
DECL|macro|INTEGRATOR_SC_VALID_INT
mdefine_line|#define INTEGRATOR_SC_VALID_INT&t;0x003fffff
DECL|function|sc_mask_irq
r_static
r_void
id|sc_mask_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|writel
c_func
(paren
l_int|1
op_lshift
id|irq
comma
id|VA_IC_BASE
op_plus
id|IRQ_ENABLE_CLEAR
)paren
suffix:semicolon
)brace
DECL|function|sc_unmask_irq
r_static
r_void
id|sc_unmask_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|writel
c_func
(paren
l_int|1
op_lshift
id|irq
comma
id|VA_IC_BASE
op_plus
id|IRQ_ENABLE_SET
)paren
suffix:semicolon
)brace
DECL|variable|sc_chip
r_static
r_struct
id|irqchip
id|sc_chip
op_assign
(brace
dot
id|ack
op_assign
id|sc_mask_irq
comma
dot
id|mask
op_assign
id|sc_mask_irq
comma
dot
id|unmask
op_assign
id|sc_unmask_irq
comma
)brace
suffix:semicolon
DECL|function|ap_init_irq
r_static
r_void
id|__init
id|ap_init_irq
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
multiline_comment|/* Disable all interrupts initially. */
multiline_comment|/* Do the core module ones */
id|writel
c_func
(paren
op_minus
l_int|1
comma
id|VA_CMIC_BASE
op_plus
id|IRQ_ENABLE_CLEAR
)paren
suffix:semicolon
multiline_comment|/* do the header card stuff next */
id|writel
c_func
(paren
op_minus
l_int|1
comma
id|VA_IC_BASE
op_plus
id|IRQ_ENABLE_CLEAR
)paren
suffix:semicolon
id|writel
c_func
(paren
op_minus
l_int|1
comma
id|VA_IC_BASE
op_plus
id|FIQ_ENABLE_CLEAR
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
id|NR_IRQS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
l_int|1
op_lshift
id|i
)paren
op_amp
id|INTEGRATOR_SC_VALID_INT
)paren
op_ne
l_int|0
)paren
(brace
id|set_irq_chip
c_func
(paren
id|i
comma
op_amp
id|sc_chip
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
)brace
macro_line|#ifdef CONFIG_PM
DECL|variable|ic_irq_enable
r_static
r_int
r_int
id|ic_irq_enable
suffix:semicolon
DECL|function|irq_suspend
r_static
r_int
id|irq_suspend
c_func
(paren
r_struct
id|sys_device
op_star
id|dev
comma
id|pm_message_t
id|state
)paren
(brace
id|ic_irq_enable
op_assign
id|readl
c_func
(paren
id|VA_IC_BASE
op_plus
id|IRQ_ENABLE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|irq_resume
r_static
r_int
id|irq_resume
c_func
(paren
r_struct
id|sys_device
op_star
id|dev
)paren
(brace
multiline_comment|/* disable all irq sources */
id|writel
c_func
(paren
op_minus
l_int|1
comma
id|VA_CMIC_BASE
op_plus
id|IRQ_ENABLE_CLEAR
)paren
suffix:semicolon
id|writel
c_func
(paren
op_minus
l_int|1
comma
id|VA_IC_BASE
op_plus
id|IRQ_ENABLE_CLEAR
)paren
suffix:semicolon
id|writel
c_func
(paren
op_minus
l_int|1
comma
id|VA_IC_BASE
op_plus
id|FIQ_ENABLE_CLEAR
)paren
suffix:semicolon
id|writel
c_func
(paren
id|ic_irq_enable
comma
id|VA_IC_BASE
op_plus
id|IRQ_ENABLE_SET
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#else
DECL|macro|irq_suspend
mdefine_line|#define irq_suspend NULL
DECL|macro|irq_resume
mdefine_line|#define irq_resume NULL
macro_line|#endif
DECL|variable|irq_class
r_static
r_struct
id|sysdev_class
id|irq_class
op_assign
(brace
id|set_kset_name
c_func
(paren
l_string|&quot;irq&quot;
)paren
comma
dot
id|suspend
op_assign
id|irq_suspend
comma
dot
id|resume
op_assign
id|irq_resume
comma
)brace
suffix:semicolon
DECL|variable|irq_device
r_static
r_struct
id|sys_device
id|irq_device
op_assign
(brace
dot
id|id
op_assign
l_int|0
comma
dot
id|cls
op_assign
op_amp
id|irq_class
comma
)brace
suffix:semicolon
DECL|function|irq_init_sysfs
r_static
r_int
id|__init
id|irq_init_sysfs
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
op_assign
id|sysdev_class_register
c_func
(paren
op_amp
id|irq_class
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|ret
op_assign
id|sysdev_register
c_func
(paren
op_amp
id|irq_device
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|irq_init_sysfs
id|device_initcall
c_func
(paren
id|irq_init_sysfs
)paren
suffix:semicolon
multiline_comment|/*&n; * Flash handling.&n; */
DECL|macro|SC_CTRLC
mdefine_line|#define SC_CTRLC (VA_SC_BASE + INTEGRATOR_SC_CTRLC_OFFSET)
DECL|macro|SC_CTRLS
mdefine_line|#define SC_CTRLS (VA_SC_BASE + INTEGRATOR_SC_CTRLS_OFFSET)
DECL|macro|EBI_CSR1
mdefine_line|#define EBI_CSR1 (VA_EBI_BASE + INTEGRATOR_EBI_CSR1_OFFSET)
DECL|macro|EBI_LOCK
mdefine_line|#define EBI_LOCK (VA_EBI_BASE + INTEGRATOR_EBI_LOCK_OFFSET)
DECL|function|ap_flash_init
r_static
r_int
id|ap_flash_init
c_func
(paren
r_void
)paren
(brace
id|u32
id|tmp
suffix:semicolon
id|writel
c_func
(paren
id|INTEGRATOR_SC_CTRL_nFLVPPEN
op_or
id|INTEGRATOR_SC_CTRL_nFLWP
comma
id|SC_CTRLC
)paren
suffix:semicolon
id|tmp
op_assign
id|readl
c_func
(paren
id|EBI_CSR1
)paren
op_or
id|INTEGRATOR_EBI_WRITE_ENABLE
suffix:semicolon
id|writel
c_func
(paren
id|tmp
comma
id|EBI_CSR1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|readl
c_func
(paren
id|EBI_CSR1
)paren
op_amp
id|INTEGRATOR_EBI_WRITE_ENABLE
)paren
)paren
(brace
id|writel
c_func
(paren
l_int|0xa05f
comma
id|EBI_LOCK
)paren
suffix:semicolon
id|writel
c_func
(paren
id|tmp
comma
id|EBI_CSR1
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|0
comma
id|EBI_LOCK
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ap_flash_exit
r_static
r_void
id|ap_flash_exit
c_func
(paren
r_void
)paren
(brace
id|u32
id|tmp
suffix:semicolon
id|writel
c_func
(paren
id|INTEGRATOR_SC_CTRL_nFLVPPEN
op_or
id|INTEGRATOR_SC_CTRL_nFLWP
comma
id|SC_CTRLC
)paren
suffix:semicolon
id|tmp
op_assign
id|readl
c_func
(paren
id|EBI_CSR1
)paren
op_amp
op_complement
id|INTEGRATOR_EBI_WRITE_ENABLE
suffix:semicolon
id|writel
c_func
(paren
id|tmp
comma
id|EBI_CSR1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|readl
c_func
(paren
id|EBI_CSR1
)paren
op_amp
id|INTEGRATOR_EBI_WRITE_ENABLE
)paren
(brace
id|writel
c_func
(paren
l_int|0xa05f
comma
id|EBI_LOCK
)paren
suffix:semicolon
id|writel
c_func
(paren
id|tmp
comma
id|EBI_CSR1
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|0
comma
id|EBI_LOCK
)paren
suffix:semicolon
)brace
)brace
DECL|function|ap_flash_set_vpp
r_static
r_void
id|ap_flash_set_vpp
c_func
(paren
r_int
id|on
)paren
(brace
r_int
r_int
id|reg
op_assign
id|on
ques
c_cond
id|SC_CTRLS
suffix:colon
id|SC_CTRLC
suffix:semicolon
id|writel
c_func
(paren
id|INTEGRATOR_SC_CTRL_nFLVPPEN
comma
id|reg
)paren
suffix:semicolon
)brace
DECL|variable|ap_flash_data
r_static
r_struct
id|flash_platform_data
id|ap_flash_data
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
id|ap_flash_init
comma
dot
m_exit
op_assign
id|ap_flash_exit
comma
dot
id|set_vpp
op_assign
id|ap_flash_set_vpp
comma
)brace
suffix:semicolon
DECL|variable|cfi_flash_resource
r_static
r_struct
id|resource
id|cfi_flash_resource
op_assign
(brace
dot
id|start
op_assign
id|INTEGRATOR_FLASH_BASE
comma
dot
id|end
op_assign
id|INTEGRATOR_FLASH_BASE
op_plus
id|INTEGRATOR_FLASH_SIZE
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
DECL|variable|cfi_flash_device
r_static
r_struct
id|platform_device
id|cfi_flash_device
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
id|ap_flash_data
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
id|cfi_flash_resource
comma
)brace
suffix:semicolon
DECL|function|ap_init
r_static
r_void
id|__init
id|ap_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|sc_dec
suffix:semicolon
r_int
id|i
suffix:semicolon
id|platform_device_register
c_func
(paren
op_amp
id|cfi_flash_device
)paren
suffix:semicolon
id|sc_dec
op_assign
id|readl
c_func
(paren
id|VA_SC_BASE
op_plus
id|INTEGRATOR_SC_DEC_OFFSET
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
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|lm_device
op_star
id|lmdev
suffix:semicolon
r_if
c_cond
(paren
(paren
id|sc_dec
op_amp
(paren
l_int|16
op_lshift
id|i
)paren
)paren
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
id|lmdev
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|lm_device
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lmdev
)paren
r_continue
suffix:semicolon
id|memset
c_func
(paren
id|lmdev
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|lm_device
)paren
)paren
suffix:semicolon
id|lmdev-&gt;resource.start
op_assign
l_int|0xc0000000
op_plus
l_int|0x10000000
op_star
id|i
suffix:semicolon
id|lmdev-&gt;resource.end
op_assign
id|lmdev-&gt;resource.start
op_plus
l_int|0x0fffffff
suffix:semicolon
id|lmdev-&gt;resource.flags
op_assign
id|IORESOURCE_MEM
suffix:semicolon
id|lmdev-&gt;irq
op_assign
id|IRQ_AP_EXPINT0
op_plus
id|i
suffix:semicolon
id|lmdev-&gt;id
op_assign
id|i
suffix:semicolon
id|lm_device_register
c_func
(paren
id|lmdev
)paren
suffix:semicolon
)brace
)brace
DECL|function|ap_init_timer
r_static
r_void
id|__init
id|ap_init_timer
c_func
(paren
r_void
)paren
(brace
id|integrator_time_init
c_func
(paren
l_int|1000000
op_star
id|TICKS_PER_uSEC
op_div
id|HZ
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|variable|ap_timer
r_static
r_struct
id|sys_timer
id|ap_timer
op_assign
(brace
dot
id|init
op_assign
id|ap_init_timer
comma
dot
id|offset
op_assign
id|integrator_gettimeoffset
comma
)brace
suffix:semicolon
id|MACHINE_START
c_func
(paren
id|INTEGRATOR
comma
l_string|&quot;ARM-Integrator&quot;
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
id|ap_map_io
)paren
id|INITIRQ
c_func
(paren
id|ap_init_irq
)paren
dot
id|timer
op_assign
op_amp
id|ap_timer
comma
id|INIT_MACHINE
c_func
(paren
id|ap_init
)paren
id|MACHINE_END
eof
