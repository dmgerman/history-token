multiline_comment|/*&n; * arch/arm/mach-omap/usb.c -- platform level USB initialization&n; *&n; * Copyright (C) 2004 Texas Instruments, Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
DECL|macro|DEBUG
macro_line|#undef&t;DEBUG
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/usb_otg.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/arch/mux.h&gt;
macro_line|#include &lt;asm/arch/usb.h&gt;
macro_line|#include &lt;asm/arch/board.h&gt;
multiline_comment|/* These routines should handle the standard chip-specific modes&n; * for usb0/1/2 ports, covering basic mux and transceiver setup.&n; * Call omap_usb_init() once, from INIT_MACHINE().&n; *&n; * Some board-*.c files will need to set up additional mux options,&n; * like for suspend handling, vbus sensing, GPIOs, and the D+ pullup.&n; */
multiline_comment|/* TESTED ON:&n; *  - 1611B H2 (with usb1 mini-AB) using standard Mini-B or OTG cables&n; *  - 5912 OSK OHCI (with usb0 standard-A), standard A-to-B cables&n; *  - 5912 OSK UDC, with *nonstandard* A-to-A cable&n; *  - 1510 Innovator UDC with bundled usb0 cable&n; *  - 1510 Innovator OHCI with bundled usb1/usb2 cable&n; *  - 1510 Innovator OHCI with custom usb0 cable, feeding 5V VBUS&n; *  - 1710 custom development board using alternate pin group&n; *  - 1710 H3 (with usb1 mini-AB) using standard Mini-B or OTG cables&n; */
multiline_comment|/*-------------------------------------------------------------------------*/
macro_line|#ifdef&t;CONFIG_ARCH_OMAP_OTG
DECL|variable|xceiv
r_static
r_struct
id|otg_transceiver
op_star
id|xceiv
suffix:semicolon
multiline_comment|/**&n; * otg_get_transceiver - find the (single) OTG transceiver driver&n; *&n; * Returns the transceiver driver, after getting a refcount to it; or&n; * null if there is no such transceiver.  The caller is responsible for&n; * releasing that count.&n; */
DECL|function|otg_get_transceiver
r_struct
id|otg_transceiver
op_star
id|otg_get_transceiver
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|xceiv
)paren
id|get_device
c_func
(paren
id|xceiv-&gt;dev
)paren
suffix:semicolon
r_return
id|xceiv
suffix:semicolon
)brace
DECL|variable|otg_get_transceiver
id|EXPORT_SYMBOL
c_func
(paren
id|otg_get_transceiver
)paren
suffix:semicolon
DECL|function|otg_set_transceiver
r_int
id|otg_set_transceiver
c_func
(paren
r_struct
id|otg_transceiver
op_star
id|x
)paren
(brace
r_if
c_cond
(paren
id|xceiv
op_logical_and
id|x
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|xceiv
op_assign
id|x
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|otg_set_transceiver
id|EXPORT_SYMBOL
c_func
(paren
id|otg_set_transceiver
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*-------------------------------------------------------------------------*/
DECL|function|omap_usb0_init
r_static
id|u32
id|__init
id|omap_usb0_init
c_func
(paren
r_int
id|nwires
comma
r_int
id|is_device
)paren
(brace
id|u32
id|syscon1
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|nwires
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|cpu_is_omap15xx
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* pulldown D+/D- */
id|USB_TRANSCEIVER_CTRL_REG
op_and_assign
op_complement
(paren
l_int|3
op_lshift
l_int|1
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|is_device
)paren
id|omap_cfg_reg
c_func
(paren
id|W4_USB_PUEN
)paren
suffix:semicolon
multiline_comment|/* internal transceiver */
r_if
c_cond
(paren
id|nwires
op_eq
l_int|2
)paren
(brace
singleline_comment|// omap_cfg_reg(P9_USB_DP);
singleline_comment|// omap_cfg_reg(R8_USB_DM);
r_if
c_cond
(paren
id|cpu_is_omap15xx
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* This works on 1510-Innovator */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* NOTES:&n;&t;&t; *  - peripheral should configure VBUS detection!&n;&t;&t; *  - only peripherals may use the internal D+/D- pulldowns&n;&t;&t; *  - OTG support on this port not yet written&n;&t;&t; */
id|USB_TRANSCEIVER_CTRL_REG
op_and_assign
op_complement
(paren
l_int|7
op_lshift
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_device
)paren
id|USB_TRANSCEIVER_CTRL_REG
op_or_assign
(paren
l_int|3
op_lshift
l_int|1
)paren
suffix:semicolon
r_return
l_int|3
op_lshift
l_int|16
suffix:semicolon
)brace
multiline_comment|/* alternate pin config, external transceiver */
r_if
c_cond
(paren
id|cpu_is_omap15xx
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;no usb0 alt pin config on 15xx&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|omap_cfg_reg
c_func
(paren
id|V6_USB0_TXD
)paren
suffix:semicolon
id|omap_cfg_reg
c_func
(paren
id|W9_USB0_TXEN
)paren
suffix:semicolon
id|omap_cfg_reg
c_func
(paren
id|W5_USB0_SE0
)paren
suffix:semicolon
multiline_comment|/* NOTE:  SPEED and SUSP aren&squot;t configured here */
r_if
c_cond
(paren
id|nwires
op_ne
l_int|3
)paren
id|omap_cfg_reg
c_func
(paren
id|Y5_USB0_RCV
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nwires
op_ne
l_int|6
)paren
id|USB_TRANSCEIVER_CTRL_REG
op_and_assign
op_complement
id|CONF_USB2_UNI_R
suffix:semicolon
r_switch
c_cond
(paren
id|nwires
)paren
(brace
r_case
l_int|3
suffix:colon
id|syscon1
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|syscon1
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
id|syscon1
op_assign
l_int|3
suffix:semicolon
id|omap_cfg_reg
c_func
(paren
id|AA9_USB0_VP
)paren
suffix:semicolon
id|omap_cfg_reg
c_func
(paren
id|R9_USB0_VM
)paren
suffix:semicolon
id|USB_TRANSCEIVER_CTRL_REG
op_or_assign
id|CONF_USB2_UNI_R
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;illegal usb%d %d-wire transceiver&bslash;n&quot;
comma
l_int|0
comma
id|nwires
)paren
suffix:semicolon
)brace
r_return
id|syscon1
op_lshift
l_int|16
suffix:semicolon
)brace
DECL|function|omap_usb1_init
r_static
id|u32
id|__init
id|omap_usb1_init
c_func
(paren
r_int
id|nwires
)paren
(brace
id|u32
id|syscon1
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|nwires
op_ne
l_int|6
op_logical_and
op_logical_neg
id|cpu_is_omap15xx
c_func
(paren
)paren
)paren
id|USB_TRANSCEIVER_CTRL_REG
op_and_assign
op_complement
id|CONF_USB1_UNI_R
suffix:semicolon
r_if
c_cond
(paren
id|nwires
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* external transceiver */
id|omap_cfg_reg
c_func
(paren
id|USB1_TXD
)paren
suffix:semicolon
id|omap_cfg_reg
c_func
(paren
id|USB1_TXEN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu_is_omap15xx
c_func
(paren
)paren
)paren
(brace
id|omap_cfg_reg
c_func
(paren
id|USB1_SEO
)paren
suffix:semicolon
id|omap_cfg_reg
c_func
(paren
id|USB1_SPEED
)paren
suffix:semicolon
singleline_comment|// SUSP
)brace
r_else
r_if
c_cond
(paren
id|cpu_is_omap1610
c_func
(paren
)paren
op_logical_or
id|cpu_is_omap5912
c_func
(paren
)paren
)paren
(brace
id|omap_cfg_reg
c_func
(paren
id|W13_1610_USB1_SE0
)paren
suffix:semicolon
id|omap_cfg_reg
c_func
(paren
id|R13_1610_USB1_SPEED
)paren
suffix:semicolon
singleline_comment|// SUSP
)brace
r_else
r_if
c_cond
(paren
id|cpu_is_omap1710
c_func
(paren
)paren
)paren
(brace
id|omap_cfg_reg
c_func
(paren
id|R13_1710_USB1_SE0
)paren
suffix:semicolon
singleline_comment|// SUSP
)brace
r_else
(brace
id|pr_debug
c_func
(paren
l_string|&quot;usb unrecognized&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nwires
op_ne
l_int|3
)paren
id|omap_cfg_reg
c_func
(paren
id|USB1_RCV
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|nwires
)paren
(brace
r_case
l_int|3
suffix:colon
id|syscon1
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|syscon1
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
id|syscon1
op_assign
l_int|3
suffix:semicolon
id|omap_cfg_reg
c_func
(paren
id|USB1_VP
)paren
suffix:semicolon
id|omap_cfg_reg
c_func
(paren
id|USB1_VM
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpu_is_omap15xx
c_func
(paren
)paren
)paren
id|USB_TRANSCEIVER_CTRL_REG
op_or_assign
id|CONF_USB1_UNI_R
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;illegal usb%d %d-wire transceiver&bslash;n&quot;
comma
l_int|1
comma
id|nwires
)paren
suffix:semicolon
)brace
r_return
id|syscon1
op_lshift
l_int|20
suffix:semicolon
)brace
DECL|function|omap_usb2_init
r_static
id|u32
id|__init
id|omap_usb2_init
c_func
(paren
r_int
id|nwires
comma
r_int
id|alt_pingroup
)paren
(brace
id|u32
id|syscon1
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* NOTE erratum: must leave USB2_UNI_R set if usb0 in use */
r_if
c_cond
(paren
id|alt_pingroup
op_logical_or
id|nwires
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|nwires
op_ne
l_int|6
op_logical_and
op_logical_neg
id|cpu_is_omap15xx
c_func
(paren
)paren
)paren
id|USB_TRANSCEIVER_CTRL_REG
op_and_assign
op_complement
id|CONF_USB2_UNI_R
suffix:semicolon
multiline_comment|/* external transceiver */
r_if
c_cond
(paren
id|cpu_is_omap15xx
c_func
(paren
)paren
)paren
(brace
id|omap_cfg_reg
c_func
(paren
id|USB2_TXD
)paren
suffix:semicolon
id|omap_cfg_reg
c_func
(paren
id|USB2_TXEN
)paren
suffix:semicolon
id|omap_cfg_reg
c_func
(paren
id|USB2_SEO
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nwires
op_ne
l_int|3
)paren
id|omap_cfg_reg
c_func
(paren
id|USB2_RCV
)paren
suffix:semicolon
multiline_comment|/* there is no USB2_SPEED */
)brace
r_else
r_if
c_cond
(paren
id|cpu_is_omap16xx
c_func
(paren
)paren
)paren
(brace
id|omap_cfg_reg
c_func
(paren
id|V6_USB2_TXD
)paren
suffix:semicolon
id|omap_cfg_reg
c_func
(paren
id|W9_USB2_TXEN
)paren
suffix:semicolon
id|omap_cfg_reg
c_func
(paren
id|W5_USB2_SE0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nwires
op_ne
l_int|3
)paren
id|omap_cfg_reg
c_func
(paren
id|Y5_USB2_RCV
)paren
suffix:semicolon
singleline_comment|// FIXME omap_cfg_reg(USB2_SPEED);
)brace
r_else
(brace
id|pr_debug
c_func
(paren
l_string|&quot;usb unrecognized&bslash;n&quot;
)paren
suffix:semicolon
)brace
singleline_comment|// omap_cfg_reg(USB2_SUSP);
r_switch
c_cond
(paren
id|nwires
)paren
(brace
r_case
l_int|3
suffix:colon
id|syscon1
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|syscon1
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
id|syscon1
op_assign
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|cpu_is_omap15xx
c_func
(paren
)paren
)paren
(brace
id|omap_cfg_reg
c_func
(paren
id|USB2_VP
)paren
suffix:semicolon
id|omap_cfg_reg
c_func
(paren
id|USB2_VM
)paren
suffix:semicolon
)brace
r_else
(brace
id|omap_cfg_reg
c_func
(paren
id|AA9_USB2_VP
)paren
suffix:semicolon
id|omap_cfg_reg
c_func
(paren
id|R9_USB2_VM
)paren
suffix:semicolon
id|USB_TRANSCEIVER_CTRL_REG
op_or_assign
id|CONF_USB2_UNI_R
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;illegal usb%d %d-wire transceiver&bslash;n&quot;
comma
l_int|2
comma
id|nwires
)paren
suffix:semicolon
)brace
r_return
id|syscon1
op_lshift
l_int|24
suffix:semicolon
)brace
multiline_comment|/*-------------------------------------------------------------------------*/
macro_line|#if&t;defined(CONFIG_USB_GADGET_OMAP) || &bslash;&n;&t;defined(CONFIG_USB_OHCI_HCD) || defined(CONFIG_USB_OHCI_HCD_MODULE) || &bslash;&n;&t;(defined(CONFIG_USB_OTG) &amp;&amp; defined(CONFIG_ARCH_OMAP_OTG))
DECL|function|usb_release
r_static
r_void
id|usb_release
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
multiline_comment|/* normally not freed */
)brace
macro_line|#endif
macro_line|#ifdef&t;CONFIG_USB_GADGET_OMAP
DECL|variable|udc_resources
r_static
r_struct
id|resource
id|udc_resources
(braket
)braket
op_assign
(brace
multiline_comment|/* order is significant! */
(brace
multiline_comment|/* registers */
dot
id|start
op_assign
id|IO_ADDRESS
c_func
(paren
id|UDC_BASE
)paren
comma
dot
id|end
op_assign
id|IO_ADDRESS
c_func
(paren
id|UDC_BASE
op_plus
l_int|0xff
)paren
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
(brace
multiline_comment|/* general IRQ */
dot
id|start
op_assign
id|IH2_BASE
op_plus
l_int|20
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
comma
(brace
multiline_comment|/* PIO IRQ */
dot
id|start
op_assign
id|IH2_BASE
op_plus
l_int|30
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
comma
(brace
multiline_comment|/* SOF IRQ */
dot
id|start
op_assign
id|IH2_BASE
op_plus
l_int|29
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
DECL|variable|udc_dmamask
r_static
id|u64
id|udc_dmamask
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
l_string|&quot;omap_udc&quot;
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
id|release
op_assign
id|usb_release
comma
dot
id|dma_mask
op_assign
op_amp
id|udc_dmamask
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
id|udc_resources
)paren
comma
dot
id|resource
op_assign
id|udc_resources
comma
)brace
suffix:semicolon
macro_line|#endif
macro_line|#if&t;defined(CONFIG_USB_OHCI_HCD) || defined(CONFIG_USB_OHCI_HCD_MODULE)
multiline_comment|/* The dmamask must be set for OHCI to work */
DECL|variable|ohci_dmamask
r_static
id|u64
id|ohci_dmamask
op_assign
op_complement
(paren
id|u32
)paren
l_int|0
suffix:semicolon
DECL|variable|ohci_resources
r_static
r_struct
id|resource
id|ohci_resources
(braket
)braket
op_assign
(brace
(brace
dot
id|start
op_assign
id|OMAP_OHCI_BASE
comma
dot
id|end
op_assign
id|OMAP_OHCI_BASE
op_plus
l_int|4096
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
id|INT_USB_HHC_1
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
DECL|variable|ohci_device
r_static
r_struct
id|platform_device
id|ohci_device
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;ohci&quot;
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
id|release
op_assign
id|usb_release
comma
dot
id|dma_mask
op_assign
op_amp
id|ohci_dmamask
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
id|ohci_resources
)paren
comma
dot
id|resource
op_assign
id|ohci_resources
comma
)brace
suffix:semicolon
macro_line|#endif
macro_line|#if&t;defined(CONFIG_USB_OTG) &amp;&amp; defined(CONFIG_ARCH_OMAP_OTG)
DECL|variable|otg_resources
r_static
r_struct
id|resource
id|otg_resources
(braket
)braket
op_assign
(brace
multiline_comment|/* order is significant! */
(brace
dot
id|start
op_assign
id|IO_ADDRESS
c_func
(paren
id|OTG_BASE
)paren
comma
dot
id|end
op_assign
id|IO_ADDRESS
c_func
(paren
id|OTG_BASE
op_plus
l_int|0xff
)paren
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
id|IH2_BASE
op_plus
l_int|8
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
DECL|variable|otg_device
r_static
r_struct
id|platform_device
id|otg_device
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;omap_otg&quot;
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
id|release
op_assign
id|usb_release
comma
)brace
comma
dot
id|num_resources
op_assign
id|ARRAY_SIZE
c_func
(paren
id|otg_resources
)paren
comma
dot
id|resource
op_assign
id|otg_resources
comma
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*-------------------------------------------------------------------------*/
DECL|macro|ULPD_CLOCK_CTRL_REG
mdefine_line|#define ULPD_CLOCK_CTRL_REG&t;__REG16(ULPD_CLOCK_CTRL)
DECL|macro|ULPD_SOFT_REQ_REG
mdefine_line|#define ULPD_SOFT_REQ_REG&t;__REG16(ULPD_SOFT_REQ)
singleline_comment|// FIXME correct answer depends on hmc_mode,
singleline_comment|// as does any nonzero value for config-&gt;otg port number
macro_line|#ifdef&t;CONFIG_USB_GADGET_OMAP
DECL|macro|is_usb0_device
mdefine_line|#define&t;is_usb0_device(config)&t;1
macro_line|#else
DECL|macro|is_usb0_device
mdefine_line|#define&t;is_usb0_device(config)&t;0
macro_line|#endif
multiline_comment|/*-------------------------------------------------------------------------*/
macro_line|#ifdef&t;CONFIG_ARCH_OMAP_OTG
r_void
id|__init
DECL|function|omap_otg_init
id|omap_otg_init
c_func
(paren
r_struct
id|omap_usb_config
op_star
id|config
)paren
(brace
id|u32
id|syscon
op_assign
id|OTG_SYSCON_1_REG
op_amp
l_int|0xffff
suffix:semicolon
r_int
id|status
suffix:semicolon
r_int
id|alt_pingroup
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* NOTE:  no bus or clock setup (yet?) */
id|syscon
op_assign
id|OTG_SYSCON_1_REG
op_amp
l_int|0xffff
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|syscon
op_amp
id|OTG_RESET_DONE
)paren
)paren
id|pr_debug
c_func
(paren
l_string|&quot;USB resets not complete?&bslash;n&quot;
)paren
suffix:semicolon
singleline_comment|// OTG_IRQ_EN_REG = 0;
multiline_comment|/* pin muxing and transceiver pinouts */
r_if
c_cond
(paren
id|config-&gt;pins
(braket
l_int|0
)braket
OG
l_int|2
)paren
multiline_comment|/* alt pingroup 2 */
id|alt_pingroup
op_assign
l_int|1
suffix:semicolon
id|syscon
op_or_assign
id|omap_usb0_init
c_func
(paren
id|config-&gt;pins
(braket
l_int|0
)braket
comma
id|is_usb0_device
c_func
(paren
id|config
)paren
)paren
suffix:semicolon
id|syscon
op_or_assign
id|omap_usb1_init
c_func
(paren
id|config-&gt;pins
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|syscon
op_or_assign
id|omap_usb2_init
c_func
(paren
id|config-&gt;pins
(braket
l_int|2
)braket
comma
id|alt_pingroup
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;OTG_SYSCON_1_REG = %08x&bslash;n&quot;
comma
id|syscon
)paren
suffix:semicolon
id|OTG_SYSCON_1_REG
op_assign
id|syscon
suffix:semicolon
id|syscon
op_assign
id|config-&gt;hmc_mode
suffix:semicolon
id|syscon
op_or_assign
id|USBX_SYNCHRO
op_or
(paren
l_int|4
op_lshift
l_int|16
)paren
multiline_comment|/* B_ASE0_BRST */
suffix:semicolon
macro_line|#ifdef&t;CONFIG_USB_OTG
r_if
c_cond
(paren
id|config-&gt;otg
)paren
id|syscon
op_or_assign
id|OTG_EN
suffix:semicolon
macro_line|#endif
id|pr_debug
c_func
(paren
l_string|&quot;USB_TRANSCEIVER_CTRL_REG = %03x&bslash;n&quot;
comma
id|USB_TRANSCEIVER_CTRL_REG
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;OTG_SYSCON_2_REG = %08x&bslash;n&quot;
comma
id|syscon
)paren
suffix:semicolon
id|OTG_SYSCON_2_REG
op_assign
id|syscon
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;USB: hmc %d&quot;
comma
id|config-&gt;hmc_mode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|alt_pingroup
)paren
id|printk
c_func
(paren
l_string|&quot;, usb2 alt %d wires&quot;
comma
id|config-&gt;pins
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|config-&gt;pins
(braket
l_int|0
)braket
)paren
id|printk
c_func
(paren
l_string|&quot;, usb0 %d wires%s&quot;
comma
id|config-&gt;pins
(braket
l_int|0
)braket
comma
id|is_usb0_device
c_func
(paren
id|config
)paren
ques
c_cond
l_string|&quot; (dev)&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|config-&gt;pins
(braket
l_int|1
)braket
)paren
id|printk
c_func
(paren
l_string|&quot;, usb1 %d wires&quot;
comma
id|config-&gt;pins
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|alt_pingroup
op_logical_and
id|config-&gt;pins
(braket
l_int|2
)braket
)paren
id|printk
c_func
(paren
l_string|&quot;, usb2 %d wires&quot;
comma
id|config-&gt;pins
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|config-&gt;otg
)paren
id|printk
c_func
(paren
l_string|&quot;, Mini-AB on usb%d&quot;
comma
id|config-&gt;otg
op_minus
l_int|1
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* leave USB clocks/controllers off until needed */
id|ULPD_SOFT_REQ_REG
op_and_assign
op_complement
id|SOFT_USB_CLK_REQ
suffix:semicolon
id|ULPD_CLOCK_CTRL_REG
op_and_assign
op_complement
id|USB_MCLK_EN
suffix:semicolon
id|ULPD_CLOCK_CTRL_REG
op_or_assign
id|DIS_USB_PVCI_CLK
suffix:semicolon
id|syscon
op_assign
id|OTG_SYSCON_1_REG
suffix:semicolon
id|syscon
op_or_assign
id|HST_IDLE_EN
op_or
id|DEV_IDLE_EN
op_or
id|OTG_IDLE_EN
suffix:semicolon
macro_line|#ifdef&t;CONFIG_USB_GADGET_OMAP
r_if
c_cond
(paren
id|config-&gt;otg
op_logical_or
id|config-&gt;register_dev
)paren
(brace
id|syscon
op_and_assign
op_complement
id|DEV_IDLE_EN
suffix:semicolon
id|udc_device.dev.platform_data
op_assign
id|config
suffix:semicolon
multiline_comment|/* FIXME patch IRQ numbers for omap730 */
id|status
op_assign
id|platform_device_register
c_func
(paren
op_amp
id|udc_device
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
id|pr_debug
c_func
(paren
l_string|&quot;can&squot;t register UDC device, %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if&t;defined(CONFIG_USB_OHCI_HCD) || defined(CONFIG_USB_OHCI_HCD_MODULE)
r_if
c_cond
(paren
id|config-&gt;otg
op_logical_or
id|config-&gt;register_host
)paren
(brace
id|syscon
op_and_assign
op_complement
id|HST_IDLE_EN
suffix:semicolon
id|ohci_device.dev.platform_data
op_assign
id|config
suffix:semicolon
r_if
c_cond
(paren
id|cpu_is_omap730
c_func
(paren
)paren
)paren
id|ohci_resources
(braket
l_int|1
)braket
dot
id|start
op_assign
id|INT_730_USB_HHC_1
suffix:semicolon
id|status
op_assign
id|platform_device_register
c_func
(paren
op_amp
id|ohci_device
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
id|pr_debug
c_func
(paren
l_string|&quot;can&squot;t register OHCI device, %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef&t;CONFIG_USB_OTG
r_if
c_cond
(paren
id|config-&gt;otg
)paren
(brace
id|syscon
op_and_assign
op_complement
id|OTG_IDLE_EN
suffix:semicolon
id|otg_device.dev.platform_data
op_assign
id|config
suffix:semicolon
r_if
c_cond
(paren
id|cpu_is_omap730
c_func
(paren
)paren
)paren
id|otg_resources
(braket
l_int|1
)braket
dot
id|start
op_assign
id|INT_730_USB_OTG
suffix:semicolon
id|status
op_assign
id|platform_device_register
c_func
(paren
op_amp
id|otg_device
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
id|pr_debug
c_func
(paren
l_string|&quot;can&squot;t register OTG device, %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
)brace
macro_line|#endif
id|pr_debug
c_func
(paren
l_string|&quot;OTG_SYSCON_1_REG = %08x&bslash;n&quot;
comma
id|syscon
)paren
suffix:semicolon
id|OTG_SYSCON_1_REG
op_assign
id|syscon
suffix:semicolon
id|status
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#else
DECL|function|omap_otg_init
r_static
r_inline
r_void
id|omap_otg_init
c_func
(paren
r_struct
id|omap_usb_config
op_star
id|config
)paren
(brace
)brace
macro_line|#endif
multiline_comment|/*-------------------------------------------------------------------------*/
macro_line|#ifdef&t;CONFIG_ARCH_OMAP1510
DECL|macro|ULPD_DPLL_CTRL_REG
mdefine_line|#define ULPD_DPLL_CTRL_REG&t;__REG16(ULPD_DPLL_CTRL)
DECL|macro|DPLL_IOB
mdefine_line|#define DPLL_IOB&t;&t;(1 &lt;&lt; 13)
DECL|macro|DPLL_PLL_ENABLE
mdefine_line|#define DPLL_PLL_ENABLE&t;&t;(1 &lt;&lt; 4)
DECL|macro|DPLL_LOCK
mdefine_line|#define DPLL_LOCK&t;&t;(1 &lt;&lt; 0)
DECL|macro|ULPD_APLL_CTRL_REG
mdefine_line|#define ULPD_APLL_CTRL_REG&t;__REG16(ULPD_APLL_CTRL)
DECL|macro|APLL_NDPLL_SWITCH
mdefine_line|#define APLL_NDPLL_SWITCH&t;(1 &lt;&lt; 0)
DECL|function|omap_1510_usb_init
r_static
r_void
id|__init
id|omap_1510_usb_init
c_func
(paren
r_struct
id|omap_usb_config
op_star
id|config
)paren
(brace
r_int
id|status
suffix:semicolon
r_int
r_int
id|val
suffix:semicolon
id|omap_usb0_init
c_func
(paren
id|config-&gt;pins
(braket
l_int|0
)braket
comma
id|is_usb0_device
c_func
(paren
id|config
)paren
)paren
suffix:semicolon
id|omap_usb1_init
c_func
(paren
id|config-&gt;pins
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|omap_usb2_init
c_func
(paren
id|config-&gt;pins
(braket
l_int|2
)braket
comma
l_int|0
)paren
suffix:semicolon
id|val
op_assign
id|omap_readl
c_func
(paren
id|MOD_CONF_CTRL_0
)paren
op_amp
op_complement
(paren
l_int|0x3f
op_lshift
l_int|1
)paren
suffix:semicolon
id|val
op_or_assign
(paren
id|config-&gt;hmc_mode
op_lshift
l_int|1
)paren
suffix:semicolon
id|omap_writel
c_func
(paren
id|val
comma
id|MOD_CONF_CTRL_0
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;USB: hmc %d&quot;
comma
id|config-&gt;hmc_mode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|config-&gt;pins
(braket
l_int|0
)braket
)paren
id|printk
c_func
(paren
l_string|&quot;, usb0 %d wires%s&quot;
comma
id|config-&gt;pins
(braket
l_int|0
)braket
comma
id|is_usb0_device
c_func
(paren
id|config
)paren
ques
c_cond
l_string|&quot; (dev)&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|config-&gt;pins
(braket
l_int|1
)braket
)paren
id|printk
c_func
(paren
l_string|&quot;, usb1 %d wires&quot;
comma
id|config-&gt;pins
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|config-&gt;pins
(braket
l_int|2
)braket
)paren
id|printk
c_func
(paren
l_string|&quot;, usb2 %d wires&quot;
comma
id|config-&gt;pins
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* use DPLL for 48 MHz function clock */
id|pr_debug
c_func
(paren
l_string|&quot;APLL %04x DPLL %04x REQ %04x&bslash;n&quot;
comma
id|ULPD_APLL_CTRL_REG
comma
id|ULPD_DPLL_CTRL_REG
comma
id|ULPD_SOFT_REQ_REG
)paren
suffix:semicolon
id|ULPD_APLL_CTRL_REG
op_and_assign
op_complement
id|APLL_NDPLL_SWITCH
suffix:semicolon
id|ULPD_DPLL_CTRL_REG
op_or_assign
id|DPLL_IOB
op_or
id|DPLL_PLL_ENABLE
suffix:semicolon
id|ULPD_SOFT_REQ_REG
op_or_assign
id|SOFT_UDC_REQ
op_or
id|SOFT_DPLL_REQ
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|ULPD_DPLL_CTRL_REG
op_amp
id|DPLL_LOCK
)paren
)paren
id|cpu_relax
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef&t;CONFIG_USB_GADGET_OMAP
r_if
c_cond
(paren
id|config-&gt;register_dev
)paren
(brace
id|udc_device.dev.platform_data
op_assign
id|config
suffix:semicolon
id|status
op_assign
id|platform_device_register
c_func
(paren
op_amp
id|udc_device
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
id|pr_debug
c_func
(paren
l_string|&quot;can&squot;t register UDC device, %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
multiline_comment|/* udc driver gates 48MHz by D+ pullup */
)brace
macro_line|#endif
macro_line|#if&t;defined(CONFIG_USB_OHCI_HCD) || defined(CONFIG_USB_OHCI_HCD_MODULE)
r_if
c_cond
(paren
id|config-&gt;register_host
)paren
(brace
id|ohci_device.dev.platform_data
op_assign
id|config
suffix:semicolon
id|status
op_assign
id|platform_device_register
c_func
(paren
op_amp
id|ohci_device
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
id|pr_debug
c_func
(paren
l_string|&quot;can&squot;t register OHCI device, %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
multiline_comment|/* hcd explicitly gates 48MHz */
)brace
macro_line|#endif
)brace
macro_line|#else
DECL|function|omap_1510_usb_init
r_static
r_inline
r_void
id|omap_1510_usb_init
c_func
(paren
r_struct
id|omap_usb_config
op_star
id|config
)paren
(brace
)brace
macro_line|#endif
multiline_comment|/*-------------------------------------------------------------------------*/
DECL|variable|platform_data
r_static
r_struct
id|omap_usb_config
id|platform_data
suffix:semicolon
r_static
r_int
id|__init
DECL|function|omap_usb_init
id|omap_usb_init
c_func
(paren
r_void
)paren
(brace
r_const
r_struct
id|omap_usb_config
op_star
id|config
suffix:semicolon
id|config
op_assign
id|omap_get_config
c_func
(paren
id|OMAP_TAG_USB
comma
r_struct
id|omap_usb_config
)paren
suffix:semicolon
r_if
c_cond
(paren
id|config
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;USB: No board-specific &quot;
l_string|&quot;platform config found&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|platform_data
op_assign
op_star
id|config
suffix:semicolon
r_if
c_cond
(paren
id|cpu_is_omap730
c_func
(paren
)paren
op_logical_or
id|cpu_is_omap16xx
c_func
(paren
)paren
)paren
id|omap_otg_init
c_func
(paren
op_amp
id|platform_data
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|cpu_is_omap15xx
c_func
(paren
)paren
)paren
id|omap_1510_usb_init
c_func
(paren
op_amp
id|platform_data
)paren
suffix:semicolon
r_else
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;USB: No init for your chip yet&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|omap_usb_init
id|subsys_initcall
c_func
(paren
id|omap_usb_init
)paren
suffix:semicolon
eof
