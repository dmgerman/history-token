multiline_comment|/*&n; *  linux/arch/arm/mach-pxa/generic.c&n; *&n; *  Author:&t;Nicolas Pitre&n; *  Created:&t;Jun 15, 2001&n; *  Copyright:&t;MontaVista Software Inc.&n; *&n; * Code common to all PXA machines.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Since this file should be linked before any other machine specific file,&n; * the __initcall() here will be executed first.  This serves as default&n; * initialization stuff for PXA machines which can be overridden later if&n; * need be.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/arch/pxa-regs.h&gt;
macro_line|#include &lt;asm/arch/udc.h&gt;
macro_line|#include &lt;asm/arch/pxafb.h&gt;
macro_line|#include &lt;asm/arch/mmc.h&gt;
macro_line|#include &quot;generic.h&quot;
multiline_comment|/*&n; * Handy function to set GPIO alternate functions&n; */
DECL|function|pxa_gpio_mode
r_void
id|pxa_gpio_mode
c_func
(paren
r_int
id|gpio_mode
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|gpio
op_assign
id|gpio_mode
op_amp
id|GPIO_MD_MASK_NR
suffix:semicolon
r_int
id|fn
op_assign
(paren
id|gpio_mode
op_amp
id|GPIO_MD_MASK_FN
)paren
op_rshift
l_int|8
suffix:semicolon
r_int
id|gafr
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gpio_mode
op_amp
id|GPIO_DFLT_LOW
)paren
id|GPCR
c_func
(paren
id|gpio
)paren
op_assign
id|GPIO_bit
c_func
(paren
id|gpio
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|gpio_mode
op_amp
id|GPIO_DFLT_HIGH
)paren
id|GPSR
c_func
(paren
id|gpio
)paren
op_assign
id|GPIO_bit
c_func
(paren
id|gpio
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gpio_mode
op_amp
id|GPIO_MD_MASK_DIR
)paren
id|GPDR
c_func
(paren
id|gpio
)paren
op_or_assign
id|GPIO_bit
c_func
(paren
id|gpio
)paren
suffix:semicolon
r_else
id|GPDR
c_func
(paren
id|gpio
)paren
op_and_assign
op_complement
id|GPIO_bit
c_func
(paren
id|gpio
)paren
suffix:semicolon
id|gafr
op_assign
id|GAFR
c_func
(paren
id|gpio
)paren
op_amp
op_complement
(paren
l_int|0x3
op_lshift
(paren
(paren
(paren
id|gpio
)paren
op_amp
l_int|0xf
)paren
op_star
l_int|2
)paren
)paren
suffix:semicolon
id|GAFR
c_func
(paren
id|gpio
)paren
op_assign
id|gafr
op_or
(paren
id|fn
op_lshift
(paren
(paren
(paren
id|gpio
)paren
op_amp
l_int|0xf
)paren
op_star
l_int|2
)paren
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|variable|pxa_gpio_mode
id|EXPORT_SYMBOL
c_func
(paren
id|pxa_gpio_mode
)paren
suffix:semicolon
multiline_comment|/*&n; * Routine to safely enable or disable a clock in the CKEN&n; */
DECL|function|pxa_set_cken
r_void
id|pxa_set_cken
c_func
(paren
r_int
id|clock
comma
r_int
id|enable
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|enable
)paren
id|CKEN
op_or_assign
id|clock
suffix:semicolon
r_else
id|CKEN
op_and_assign
op_complement
id|clock
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|variable|pxa_set_cken
id|EXPORT_SYMBOL
c_func
(paren
id|pxa_set_cken
)paren
suffix:semicolon
multiline_comment|/*&n; * Intel PXA2xx internal register mapping.&n; *&n; * Note 1: not all PXA2xx variants implement all those addresses.&n; *&n; * Note 2: virtual 0xfffe0000-0xffffffff is reserved for the vector table&n; *         and cache flush area.&n; */
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|standard_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* virtual     physical    length      type */
(brace
l_int|0xf2000000
comma
l_int|0x40000000
comma
l_int|0x01800000
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* Devs */
(brace
l_int|0xf4000000
comma
l_int|0x44000000
comma
l_int|0x00100000
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* LCD */
(brace
l_int|0xf6000000
comma
l_int|0x48000000
comma
l_int|0x00100000
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* Mem Ctl */
(brace
l_int|0xf8000000
comma
l_int|0x4c000000
comma
l_int|0x00100000
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* USB host */
(brace
l_int|0xfa000000
comma
l_int|0x50000000
comma
l_int|0x00100000
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* Camera */
(brace
l_int|0xfe000000
comma
l_int|0x58000000
comma
l_int|0x00100000
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* IMem ctl */
(brace
l_int|0xff000000
comma
l_int|0x00000000
comma
l_int|0x00100000
comma
id|MT_DEVICE
)brace
multiline_comment|/* UNCACHED_PHYS_0 */
)brace
suffix:semicolon
DECL|function|pxa_map_io
r_void
id|__init
id|pxa_map_io
c_func
(paren
r_void
)paren
(brace
id|iotable_init
c_func
(paren
id|standard_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|standard_io_desc
)paren
)paren
suffix:semicolon
id|get_clk_frequency_khz
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|variable|pxamci_resources
r_static
r_struct
id|resource
id|pxamci_resources
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
l_int|0x41100000
comma
dot
id|end
op_assign
l_int|0x41100fff
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
id|IRQ_MMC
comma
dot
id|end
op_assign
id|IRQ_MMC
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
DECL|variable|pxamci_dmamask
r_static
id|u64
id|pxamci_dmamask
op_assign
l_int|0xffffffffUL
suffix:semicolon
DECL|variable|pxamci_device
r_static
r_struct
id|platform_device
id|pxamci_device
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;pxa2xx-mci&quot;
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
dot
id|dev
op_assign
(brace
dot
id|dma_mask
op_assign
op_amp
id|pxamci_dmamask
comma
dot
id|coherent_dma_mask
op_assign
l_int|0xffffffff
comma
)brace
comma
dot
id|num_resources
op_assign
id|ARRAY_SIZE
c_func
(paren
id|pxamci_resources
)paren
comma
dot
id|resource
op_assign
id|pxamci_resources
comma
)brace
suffix:semicolon
DECL|function|pxa_set_mci_info
r_void
id|__init
id|pxa_set_mci_info
c_func
(paren
r_struct
id|pxamci_platform_data
op_star
id|info
)paren
(brace
id|pxamci_device.dev.platform_data
op_assign
id|info
suffix:semicolon
)brace
DECL|variable|pxa_udc_info
r_static
r_struct
id|pxa2xx_udc_mach_info
id|pxa_udc_info
suffix:semicolon
DECL|function|pxa_set_udc_info
r_void
id|__init
id|pxa_set_udc_info
c_func
(paren
r_struct
id|pxa2xx_udc_mach_info
op_star
id|info
)paren
(brace
id|memcpy
c_func
(paren
op_amp
id|pxa_udc_info
comma
id|info
comma
r_sizeof
op_star
id|info
)paren
suffix:semicolon
)brace
DECL|variable|pxa2xx_udc_resources
r_static
r_struct
id|resource
id|pxa2xx_udc_resources
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
l_int|0x40600000
comma
dot
id|end
op_assign
l_int|0x4060ffff
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
id|IRQ_USB
comma
dot
id|end
op_assign
id|IRQ_USB
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
DECL|variable|udc_dma_mask
r_static
id|u64
id|udc_dma_mask
op_assign
op_complement
(paren
id|u32
)paren
l_int|0
suffix:semicolon
DECL|variable|udc_device
r_static
r_struct
id|platform_device
id|udc_device
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;pxa2xx-udc&quot;
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
dot
id|resource
op_assign
id|pxa2xx_udc_resources
comma
dot
id|num_resources
op_assign
id|ARRAY_SIZE
c_func
(paren
id|pxa2xx_udc_resources
)paren
comma
dot
id|dev
op_assign
(brace
dot
id|platform_data
op_assign
op_amp
id|pxa_udc_info
comma
dot
id|dma_mask
op_assign
op_amp
id|udc_dma_mask
comma
)brace
)brace
suffix:semicolon
DECL|variable|pxa_fb_info
r_static
r_struct
id|pxafb_mach_info
id|pxa_fb_info
suffix:semicolon
DECL|function|set_pxa_fb_info
r_void
id|__init
id|set_pxa_fb_info
c_func
(paren
r_struct
id|pxafb_mach_info
op_star
id|hard_pxa_fb_info
)paren
(brace
id|memcpy
c_func
(paren
op_amp
id|pxa_fb_info
comma
id|hard_pxa_fb_info
comma
r_sizeof
(paren
r_struct
id|pxafb_mach_info
)paren
)paren
suffix:semicolon
)brace
DECL|variable|pxafb_resources
r_static
r_struct
id|resource
id|pxafb_resources
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
l_int|0x44000000
comma
dot
id|end
op_assign
l_int|0x4400ffff
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
id|IRQ_LCD
comma
dot
id|end
op_assign
id|IRQ_LCD
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
DECL|variable|fb_dma_mask
r_static
id|u64
id|fb_dma_mask
op_assign
op_complement
(paren
id|u64
)paren
l_int|0
suffix:semicolon
DECL|variable|pxafb_device
r_static
r_struct
id|platform_device
id|pxafb_device
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;pxa2xx-fb&quot;
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
dot
id|dev
op_assign
(brace
dot
id|platform_data
op_assign
op_amp
id|pxa_fb_info
comma
dot
id|dma_mask
op_assign
op_amp
id|fb_dma_mask
comma
dot
id|coherent_dma_mask
op_assign
l_int|0xffffffff
comma
)brace
comma
dot
id|num_resources
op_assign
id|ARRAY_SIZE
c_func
(paren
id|pxafb_resources
)paren
comma
dot
id|resource
op_assign
id|pxafb_resources
comma
)brace
suffix:semicolon
DECL|variable|ffuart_device
r_static
r_struct
id|platform_device
id|ffuart_device
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;pxa2xx-uart&quot;
comma
dot
id|id
op_assign
l_int|0
comma
)brace
suffix:semicolon
DECL|variable|btuart_device
r_static
r_struct
id|platform_device
id|btuart_device
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;pxa2xx-uart&quot;
comma
dot
id|id
op_assign
l_int|1
comma
)brace
suffix:semicolon
DECL|variable|stuart_device
r_static
r_struct
id|platform_device
id|stuart_device
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;pxa2xx-uart&quot;
comma
dot
id|id
op_assign
l_int|2
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|platform_device
op_star
id|devices
(braket
)braket
id|__initdata
op_assign
(brace
op_amp
id|pxamci_device
comma
op_amp
id|udc_device
comma
op_amp
id|pxafb_device
comma
op_amp
id|ffuart_device
comma
op_amp
id|btuart_device
comma
op_amp
id|stuart_device
comma
)brace
suffix:semicolon
DECL|function|pxa_init
r_static
r_int
id|__init
id|pxa_init
c_func
(paren
r_void
)paren
(brace
r_return
id|platform_add_devices
c_func
(paren
id|devices
comma
id|ARRAY_SIZE
c_func
(paren
id|devices
)paren
)paren
suffix:semicolon
)brace
DECL|variable|pxa_init
id|subsys_initcall
c_func
(paren
id|pxa_init
)paren
suffix:semicolon
eof
