multiline_comment|/*&n; * OHCI HCD (Host Controller Driver) for USB.&n; *&n; * (C) Copyright 1999 Roman Weissgaerber &lt;weissg@vienna.at&gt;&n; * (C) Copyright 2000-2002 David Brownell &lt;dbrownell@users.sourceforge.net&gt;&n; * (C) Copyright 2002 Hewlett-Packard Company&n; * &n; * OMAP Bus Glue&n; *&n; * Written by Christopher Hoover &lt;ch@hpl.hp.com&gt;&n; * Based on fragments of previous driver by Rusell King et al.&n; *&n; * Modified for OMAP from ohci-sa1111.c by Tony Lindgren &lt;tony@atomide.com&gt;&n; * Based on the 2.4 OMAP OHCI driver originally done by MontaVista Software Inc.&n; *&n; * This file is licenced under the GPL.&n; */
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/arch/bus.h&gt;
macro_line|#include &lt;asm/arch/hardware.h&gt;
macro_line|#include &lt;asm/arch/mux.h&gt;
macro_line|#include &lt;asm/arch/irqs.h&gt;
macro_line|#include &quot;ohci-omap.h&quot;
macro_line|#ifndef CONFIG_ARCH_OMAP
macro_line|#error &quot;This file is OMAP bus glue.  CONFIG_OMAP must be defined.&quot;
macro_line|#endif
r_extern
r_int
id|usb_disabled
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ocpi_enable
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Use the first port only by default. Override with hmc_mode option.&n; *&n; * NOTE: Many OMAP-1510 Innovators supposedly have bad wiring for the USB ports&n; *       1 &amp; 2, so only port 0 will work. To use the OHCI on the first port, use &n; *       the Innovator USB client cable with a client-to-client connector and modify&n; *       either the cable or the hub to feed 5V VBUS back to Innovator. VBUS should&n; *       be the red lead in the cable.&n; *&n; *       To mount USB hard disk as root, see the patch for do_mounts.c that tries &n; *       remounting the root, and use root=0801 if your root is on sda1. Does not &n; *       work with devfs.&n; */
DECL|variable|default_hmc_mode
r_static
r_int
id|default_hmc_mode
op_assign
l_int|16
suffix:semicolon
DECL|variable|hmc_mode
r_static
r_int
id|hmc_mode
op_assign
l_int|1234
suffix:semicolon
multiline_comment|/*&n; * Set the USB host pin multiplexing and the selected HMC mode&n; */
DECL|function|omap_usb_set_hmc_mode
r_static
r_int
id|omap_usb_set_hmc_mode
c_func
(paren
r_int
id|hmc_mode
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
r_switch
c_cond
(paren
id|hmc_mode
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* 0: function, 1: disabled, 2: disabled */
id|omap_cfg_reg
c_func
(paren
id|W4_USB_PUEN
)paren
suffix:semicolon
id|omap_cfg_reg
c_func
(paren
id|R18_1510_USB_GPIO0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
multiline_comment|/* 0: function 1: host 2: host */
id|omap_cfg_reg
c_func
(paren
id|usb1_speed
)paren
suffix:semicolon
id|omap_cfg_reg
c_func
(paren
id|usb1_susp
)paren
suffix:semicolon
id|omap_cfg_reg
c_func
(paren
id|usb1_seo
)paren
suffix:semicolon
id|omap_cfg_reg
c_func
(paren
id|usb1_txen
)paren
suffix:semicolon
id|omap_cfg_reg
c_func
(paren
id|usb1_txd
)paren
suffix:semicolon
id|omap_cfg_reg
c_func
(paren
id|usb1_vp
)paren
suffix:semicolon
id|omap_cfg_reg
c_func
(paren
id|usb1_vm
)paren
suffix:semicolon
id|omap_cfg_reg
c_func
(paren
id|usb1_rcv
)paren
suffix:semicolon
id|omap_cfg_reg
c_func
(paren
id|usb2_susp
)paren
suffix:semicolon
id|omap_cfg_reg
c_func
(paren
id|usb2_seo
)paren
suffix:semicolon
id|omap_cfg_reg
c_func
(paren
id|usb2_txen
)paren
suffix:semicolon
id|omap_cfg_reg
c_func
(paren
id|usb2_txd
)paren
suffix:semicolon
id|omap_cfg_reg
c_func
(paren
id|usb2_vp
)paren
suffix:semicolon
id|omap_cfg_reg
c_func
(paren
id|usb2_vm
)paren
suffix:semicolon
id|omap_cfg_reg
c_func
(paren
id|usb2_rcv
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
multiline_comment|/* 0: host, 1: disabled, 2: disabled */
id|omap_cfg_reg
c_func
(paren
id|W9_USB0_TXEN
)paren
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
id|Y5_USB0_RCV
)paren
suffix:semicolon
id|omap_cfg_reg
c_func
(paren
id|R9_USB0_VM
)paren
suffix:semicolon
id|omap_cfg_reg
c_func
(paren
id|V6_USB0_TXD
)paren
suffix:semicolon
id|omap_cfg_reg
c_func
(paren
id|W5_USB0_SE0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Unknown USB host configuration: %i&bslash;n&quot;
comma
id|hmc_mode
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* Write the selected HMC mode */
id|val
op_assign
id|readl
c_func
(paren
id|MOD_CONF_CTRL_0
)paren
op_amp
op_complement
id|HMC_CLEAR
suffix:semicolon
id|val
op_or_assign
(paren
id|hmc_mode
op_lshift
l_int|1
)paren
suffix:semicolon
id|writel
c_func
(paren
id|val
comma
id|MOD_CONF_CTRL_0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * OHCI clock initialization for OMAP-1510 and 1610&n; */
DECL|function|omap_ohci_clock_power
r_static
r_int
id|omap_ohci_clock_power
c_func
(paren
r_int
id|on
)paren
(brace
r_if
c_cond
(paren
id|on
)paren
(brace
r_if
c_cond
(paren
id|cpu_is_omap_1510
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* Use DPLL, not APLL */
id|writel
c_func
(paren
id|readl
c_func
(paren
id|ULPD_APLL_CTRL_REG
)paren
op_amp
op_complement
id|APLL_NDPLL_SWITCH
comma
id|ULPD_APLL_CTRL_REG
)paren
suffix:semicolon
multiline_comment|/* Enable DPLL */
id|writel
c_func
(paren
id|readl
c_func
(paren
id|ULPD_DPLL_CTRL_REG
)paren
op_or
id|DPLL_PLL_ENABLE
comma
id|ULPD_DPLL_CTRL_REG
)paren
suffix:semicolon
multiline_comment|/* Software request for USB 48MHz clock */
id|writel
c_func
(paren
id|readl
c_func
(paren
id|ULPD_SOFT_REQ_REG
)paren
op_or
id|SOFT_REQ_REG_REQ
comma
id|ULPD_SOFT_REQ_REG
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|readl
c_func
(paren
id|ULPD_DPLL_CTRL_REG
)paren
op_amp
id|DPLL_LOCK
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cpu_is_omap_1610
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* Enable OHCI */
id|writel
c_func
(paren
id|readl
c_func
(paren
id|ULPD_SOFT_REQ_REG
)paren
op_or
id|SOFT_USB_OTG_REQ
comma
id|ULPD_SOFT_REQ_REG
)paren
suffix:semicolon
multiline_comment|/* USB host clock request if not using OTG */
id|writel
c_func
(paren
id|readl
c_func
(paren
id|ULPD_SOFT_REQ_REG
)paren
op_or
id|SOFT_USB_REQ
comma
id|ULPD_SOFT_REQ_REG
)paren
suffix:semicolon
id|outl
c_func
(paren
id|inl
c_func
(paren
id|ULPD_STATUS_REQ_REG
)paren
op_or
id|USB_HOST_DPLL_REQ
comma
id|ULPD_STATUS_REQ_REG
)paren
suffix:semicolon
)brace
multiline_comment|/* Enable 48MHz clock to USB */
id|writel
c_func
(paren
id|readl
c_func
(paren
id|ULPD_CLOCK_CTRL_REG
)paren
op_or
id|USB_MCLK_EN
comma
id|ULPD_CLOCK_CTRL_REG
)paren
suffix:semicolon
id|writel
c_func
(paren
id|readl
c_func
(paren
id|ARM_IDLECT2
)paren
op_or
(paren
l_int|1
op_lshift
id|EN_LBFREECK
)paren
op_or
(paren
l_int|1
op_lshift
id|EN_LBCK
)paren
comma
id|ARM_IDLECT2
)paren
suffix:semicolon
id|writel
c_func
(paren
id|readl
c_func
(paren
id|MOD_CONF_CTRL_0
)paren
op_or
id|USB_HOST_HHC_UHOST_EN
comma
id|MOD_CONF_CTRL_0
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Disable 48MHz clock to USB */
id|writel
c_func
(paren
id|readl
c_func
(paren
id|ULPD_CLOCK_CTRL_REG
)paren
op_amp
op_complement
id|USB_MCLK_EN
comma
id|ULPD_CLOCK_CTRL_REG
)paren
suffix:semicolon
multiline_comment|/* FIXME: The DPLL stays on for now */
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Hardware specific transceiver power on/off&n; */
DECL|function|omap_ohci_transceiver_power
r_static
r_int
id|omap_ohci_transceiver_power
c_func
(paren
r_int
id|on
)paren
(brace
r_if
c_cond
(paren
id|on
)paren
(brace
r_if
c_cond
(paren
id|omap_is_innovator
c_func
(paren
)paren
)paren
id|writel
c_func
(paren
id|readl
c_func
(paren
id|OMAP1510_FPGA_HOST_CTRL
)paren
op_or
l_int|0x20
comma
id|OMAP1510_FPGA_HOST_CTRL
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|omap_is_innovator
c_func
(paren
)paren
)paren
id|writel
c_func
(paren
id|readl
c_func
(paren
id|OMAP1510_FPGA_HOST_CTRL
)paren
op_amp
op_complement
l_int|0x20
comma
id|OMAP1510_FPGA_HOST_CTRL
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * OMAP-1510 specific Local Bus clock on/off&n; */
DECL|function|omap_1510_local_bus_power
r_static
r_int
id|omap_1510_local_bus_power
c_func
(paren
r_int
id|on
)paren
(brace
r_if
c_cond
(paren
id|on
)paren
(brace
id|writel
c_func
(paren
(paren
l_int|1
op_lshift
l_int|1
)paren
op_or
(paren
l_int|1
op_lshift
l_int|0
)paren
comma
id|OMAP1510_LB_MMU_CTL
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|200
)paren
suffix:semicolon
)brace
r_else
(brace
id|writel
c_func
(paren
l_int|0
comma
id|OMAP1510_LB_MMU_CTL
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * OMAP-1510 specific Local Bus initialization&n; * NOTE: This assumes 32MB memory size in OMAP1510LB_MEMSIZE.&n; *       See also arch/mach-omap/memory.h for __virt_to_bus() and &n; *       __bus_to_virt() which need to match with the physical &n; *       Local Bus address below.&n; */
DECL|function|omap_1510_local_bus_init
r_static
r_int
id|omap_1510_local_bus_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|tlb
suffix:semicolon
r_int
r_int
id|lbaddr
comma
id|physaddr
suffix:semicolon
id|writel
c_func
(paren
(paren
id|readl
c_func
(paren
id|OMAP1510_LB_CLOCK_DIV
)paren
op_amp
l_int|0xfffffff8
)paren
op_or
l_int|0x4
comma
id|OMAP1510_LB_CLOCK_DIV
)paren
suffix:semicolon
multiline_comment|/* Configure the Local Bus MMU table */
r_for
c_loop
(paren
id|tlb
op_assign
l_int|0
suffix:semicolon
id|tlb
OL
id|OMAP1510_LB_MEMSIZE
suffix:semicolon
id|tlb
op_increment
)paren
(brace
id|lbaddr
op_assign
id|tlb
op_star
l_int|0x00100000
op_plus
id|OMAP1510_LB_OFFSET
suffix:semicolon
id|physaddr
op_assign
id|tlb
op_star
l_int|0x00100000
op_plus
id|PHYS_OFFSET
suffix:semicolon
id|writel
c_func
(paren
(paren
id|lbaddr
op_amp
l_int|0x0fffffff
)paren
op_rshift
l_int|22
comma
id|OMAP1510_LB_MMU_CAM_H
)paren
suffix:semicolon
id|writel
c_func
(paren
(paren
(paren
id|lbaddr
op_amp
l_int|0x003ffc00
)paren
op_rshift
l_int|6
)paren
op_or
l_int|0xc
comma
id|OMAP1510_LB_MMU_CAM_L
)paren
suffix:semicolon
id|writel
c_func
(paren
id|physaddr
op_rshift
l_int|16
comma
id|OMAP1510_LB_MMU_RAM_H
)paren
suffix:semicolon
id|writel
c_func
(paren
(paren
id|physaddr
op_amp
l_int|0x0000fc00
)paren
op_or
l_int|0x300
comma
id|OMAP1510_LB_MMU_RAM_L
)paren
suffix:semicolon
id|writel
c_func
(paren
id|tlb
op_lshift
l_int|4
comma
id|OMAP1510_LB_MMU_LCK
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|0x1
comma
id|OMAP1510_LB_MMU_LD_TLB
)paren
suffix:semicolon
)brace
multiline_comment|/* Enable the walking table */
id|writel
c_func
(paren
id|readl
c_func
(paren
id|OMAP1510_LB_MMU_CTL
)paren
op_or
(paren
l_int|1
op_lshift
l_int|3
)paren
comma
id|OMAP1510_LB_MMU_CTL
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|200
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * OMAP-1610 specific hardware initialization&n; *&n; * Intended to configure OMAP-1610 USB host and OTG ports depending on &n; * the HMC mode selected.&n; *&n; * FIXME: Currently only supports alternate ping group 2 mode, should&n; *        be easy to modify for other configurations once there is some&n; *        hardware to test with.&n; */
DECL|function|omap_1610_usb_init
r_static
r_int
id|omap_1610_usb_init
c_func
(paren
r_int
id|mode
)paren
(brace
id|u_int
id|val
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Configure the OMAP transceiver settings */
id|val
op_or_assign
(paren
l_int|1
op_lshift
l_int|8
)paren
suffix:semicolon
multiline_comment|/* CONF_USB2_UNI TRM p 15-205*/
id|val
op_or_assign
(paren
l_int|4
op_lshift
l_int|4
)paren
suffix:semicolon
multiline_comment|/* TRM p 5-59, p 15-157 (1224) */
singleline_comment|//val |= (1 &lt;&lt; 3); /* Isolate integrated transceiver from port 0 */
id|val
op_or_assign
(paren
l_int|1
op_lshift
l_int|2
)paren
suffix:semicolon
multiline_comment|/* Disable pulldown on integrated transceiver DM */
id|val
op_or_assign
(paren
l_int|1
op_lshift
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Disable pulldown on integraded transceiver DP */
id|outl
c_func
(paren
id|val
comma
id|USB_TRANSCEIVER_CTRL
)paren
suffix:semicolon
multiline_comment|/* Set the USB0_TRX_MODE */
id|val
op_assign
l_int|0
suffix:semicolon
id|val
op_and_assign
op_complement
id|OTG_IDLE_EN
suffix:semicolon
id|val
op_and_assign
op_complement
id|DEV_IDLE_EN
suffix:semicolon
id|val
op_and_assign
op_complement
(paren
l_int|7
op_lshift
l_int|16
)paren
suffix:semicolon
multiline_comment|/* Clear USB0_TRX_MODE */
id|val
op_or_assign
(paren
l_int|3
op_lshift
l_int|16
)paren
suffix:semicolon
multiline_comment|/* 0 or 3, 6-wire DAT/SE0, TRM p 15-159 */
id|outl
c_func
(paren
id|val
comma
id|OTG_SYSCON_1
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * Control via OTG, see TRM p 15-163&n;&t; */
id|val
op_assign
l_int|0
suffix:semicolon
singleline_comment|//val |= 1;&t;&t;/* REVISIT: Enable OTG = 1 */
multiline_comment|/* Control via OTG */
id|val
op_and_assign
op_complement
id|HMC_PADEN
suffix:semicolon
id|val
op_and_assign
op_complement
id|OTG_PADEN
suffix:semicolon
id|val
op_or_assign
id|UHOST_EN
suffix:semicolon
id|val
op_and_assign
op_complement
l_int|0x3f
suffix:semicolon
multiline_comment|/* Clear HMC mode */
id|val
op_or_assign
id|mode
suffix:semicolon
multiline_comment|/* Set HMC mode */
id|val
op_and_assign
op_complement
(paren
l_int|7
op_lshift
l_int|16
)paren
suffix:semicolon
multiline_comment|/* Clear ASE0_BRST */
id|val
op_or_assign
(paren
l_int|4
op_lshift
l_int|16
)paren
suffix:semicolon
multiline_comment|/* Must be 4 */
id|val
op_or_assign
id|USBX_SYNCHRO
suffix:semicolon
multiline_comment|/* Must be set */
id|val
op_or_assign
id|SRP_VBUS
suffix:semicolon
id|outl
c_func
(paren
id|val
comma
id|OTG_SYSCON_2
)paren
suffix:semicolon
multiline_comment|/* Enable OTG idle */
singleline_comment|//outl(inl(OTG_SYSCON_1) | OTG_IDLE_EN, OTG_SYSCON_1);
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*-------------------------------------------------------------------------*/
DECL|function|omap_start_hc
r_static
r_void
id|omap_start_hc
c_func
(paren
r_struct
id|omap_dev
op_star
id|dev
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
id|__FILE__
l_string|&quot;: starting OMAP OHCI USB Controller&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * Set the HMC mode for the USB ports&n;&t; */
macro_line|#if 0
multiline_comment|/* See note about the Innovator wiring above */
r_if
c_cond
(paren
id|omap_is_innovator
c_func
(paren
)paren
)paren
id|hmc_mode
op_assign
l_int|4
suffix:semicolon
multiline_comment|/* 0: function 1: host 2: host */
macro_line|#endif
r_if
c_cond
(paren
id|cpu_is_omap_1610
c_func
(paren
)paren
)paren
id|ocpi_enable
c_func
(paren
)paren
suffix:semicolon
id|omap_usb_set_hmc_mode
c_func
(paren
id|hmc_mode
)paren
suffix:semicolon
id|omap_ohci_clock_power
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|omap_ohci_transceiver_power
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu_is_omap_1510
c_func
(paren
)paren
)paren
(brace
id|omap_1510_local_bus_power
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|omap_1510_local_bus_init
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cpu_is_omap_1610
c_func
(paren
)paren
)paren
id|omap_1610_usb_init
c_func
(paren
id|hmc_mode
)paren
suffix:semicolon
singleline_comment|//omap_enable_device(dev);
)brace
DECL|function|omap_stop_hc
r_static
r_void
id|omap_stop_hc
c_func
(paren
r_struct
id|omap_dev
op_star
id|dev
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
id|__FILE__
l_string|&quot;: stopping OMAP OHCI USB Controller&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * FIXME: Put the USB host controller into reset.&n;&t; */
multiline_comment|/*&n;&t; * FIXME: Stop the USB clock.&n;&t; */
singleline_comment|//omap_disable_device(dev);
)brace
multiline_comment|/*-------------------------------------------------------------------------*/
DECL|function|usb_hcd_omap_hcim_irq
r_static
id|irqreturn_t
id|usb_hcd_omap_hcim_irq
(paren
r_int
id|irq
comma
r_void
op_star
id|__hcd
comma
r_struct
id|pt_regs
op_star
id|r
)paren
(brace
r_struct
id|usb_hcd
op_star
id|hcd
op_assign
id|__hcd
suffix:semicolon
r_return
id|usb_hcd_irq
c_func
(paren
id|irq
comma
id|hcd
comma
id|r
)paren
suffix:semicolon
)brace
multiline_comment|/*-------------------------------------------------------------------------*/
r_void
id|usb_hcd_omap_remove
(paren
r_struct
id|usb_hcd
op_star
comma
r_struct
id|omap_dev
op_star
)paren
suffix:semicolon
multiline_comment|/* configure so an HC device and id are always provided */
multiline_comment|/* always called with process context; sleeping is OK */
multiline_comment|/**&n; * usb_hcd_omap_probe - initialize OMAP-based HCDs&n; * Context: !in_interrupt()&n; *&n; * Allocates basic resources for this USB host controller, and&n; * then invokes the start() method for the HCD associated with it&n; * through the hotplug entry&squot;s driver_data.&n; *&n; * Store this function in the HCD&squot;s struct pci_driver as probe().&n; */
DECL|function|usb_hcd_omap_probe
r_int
id|usb_hcd_omap_probe
(paren
r_const
r_struct
id|hc_driver
op_star
id|driver
comma
r_struct
id|usb_hcd
op_star
op_star
id|hcd_out
comma
r_struct
id|omap_dev
op_star
id|dev
)paren
(brace
r_int
id|retval
suffix:semicolon
r_struct
id|usb_hcd
op_star
id|hcd
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_mem_region
c_func
(paren
id|dev-&gt;res.start
comma
id|dev-&gt;res.end
op_minus
id|dev-&gt;res.start
op_plus
l_int|1
comma
id|hcd_name
)paren
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;request_mem_region failed&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|omap_start_hc
c_func
(paren
id|dev
)paren
suffix:semicolon
id|hcd
op_assign
id|driver-&gt;hcd_alloc
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hcd
op_eq
l_int|NULL
)paren
(brace
id|dbg
(paren
l_string|&quot;hcd_alloc failed&quot;
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|err1
suffix:semicolon
)brace
id|hcd-&gt;driver
op_assign
(paren
r_struct
id|hc_driver
op_star
)paren
id|driver
suffix:semicolon
id|hcd-&gt;description
op_assign
id|driver-&gt;description
suffix:semicolon
id|hcd-&gt;irq
op_assign
id|dev-&gt;irq
(braket
l_int|0
)braket
suffix:semicolon
id|hcd-&gt;regs
op_assign
id|dev-&gt;mapbase
suffix:semicolon
id|hcd-&gt;pdev
op_assign
id|OMAP_FAKE_PCIDEV
suffix:semicolon
id|hcd-&gt;self.controller
op_assign
op_amp
id|dev-&gt;dev
suffix:semicolon
id|hcd-&gt;controller
op_assign
id|hcd-&gt;self.controller
suffix:semicolon
id|retval
op_assign
id|hcd_buffer_create
(paren
id|hcd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_ne
l_int|0
)paren
(brace
id|dbg
(paren
l_string|&quot;pool alloc fail&quot;
)paren
suffix:semicolon
r_goto
id|err1
suffix:semicolon
)brace
id|retval
op_assign
id|request_irq
(paren
id|hcd-&gt;irq
comma
id|usb_hcd_omap_hcim_irq
comma
id|SA_INTERRUPT
comma
id|hcd-&gt;description
comma
id|hcd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_ne
l_int|0
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;request_irq failed&quot;
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|err2
suffix:semicolon
)brace
id|info
(paren
l_string|&quot;%s (OMAP) at 0x%p, irq %d&bslash;n&quot;
comma
id|hcd-&gt;description
comma
id|hcd-&gt;regs
comma
id|hcd-&gt;irq
)paren
suffix:semicolon
id|usb_bus_init
(paren
op_amp
id|hcd-&gt;self
)paren
suffix:semicolon
id|hcd-&gt;self.op
op_assign
op_amp
id|usb_hcd_operations
suffix:semicolon
id|hcd-&gt;self.hcpriv
op_assign
(paren
r_void
op_star
)paren
id|hcd
suffix:semicolon
id|hcd-&gt;self.bus_name
op_assign
l_string|&quot;omap&quot;
suffix:semicolon
id|hcd-&gt;product_desc
op_assign
l_string|&quot;OMAP OHCI&quot;
suffix:semicolon
id|INIT_LIST_HEAD
(paren
op_amp
id|hcd-&gt;dev_list
)paren
suffix:semicolon
id|usb_register_bus
(paren
op_amp
id|hcd-&gt;self
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|driver-&gt;start
(paren
id|hcd
)paren
)paren
OL
l_int|0
)paren
(brace
id|usb_hcd_omap_remove
c_func
(paren
id|hcd
comma
id|dev
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
op_star
id|hcd_out
op_assign
id|hcd
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err2
suffix:colon
id|hcd_buffer_destroy
(paren
id|hcd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hcd
)paren
id|driver
op_member_access_from_pointer
id|hcd_free
c_func
(paren
id|hcd
)paren
suffix:semicolon
id|err1
suffix:colon
id|omap_stop_hc
c_func
(paren
id|dev
)paren
suffix:semicolon
id|release_mem_region
c_func
(paren
id|dev-&gt;res.start
comma
id|dev-&gt;res.end
op_minus
id|dev-&gt;res.start
op_plus
l_int|1
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* may be called without controller electrically present */
multiline_comment|/* may be called with controller, bus, and devices active */
multiline_comment|/**&n; * usb_hcd_omap_remove - shutdown processing for OMAP-based HCDs&n; * @dev: USB Host Controller being removed&n; * Context: !in_interrupt()&n; *&n; * Reverses the effect of usb_hcd_omap_probe(), first invoking&n; * the HCD&squot;s stop() method.  It is always called from a thread&n; * context, normally &quot;rmmod&quot;, &quot;apmd&quot;, or something similar.&n; *&n; */
DECL|function|usb_hcd_omap_remove
r_void
id|usb_hcd_omap_remove
(paren
r_struct
id|usb_hcd
op_star
id|hcd
comma
r_struct
id|omap_dev
op_star
id|dev
)paren
(brace
r_struct
id|usb_device
op_star
id|hub
suffix:semicolon
r_void
op_star
id|base
suffix:semicolon
id|info
(paren
l_string|&quot;remove: %s, state %x&quot;
comma
id|hcd-&gt;self.bus_name
comma
id|hcd-&gt;state
)paren
suffix:semicolon
r_if
c_cond
(paren
id|in_interrupt
(paren
)paren
)paren
id|BUG
(paren
)paren
suffix:semicolon
id|hub
op_assign
id|hcd-&gt;self.root_hub
suffix:semicolon
id|hcd-&gt;state
op_assign
id|USB_STATE_QUIESCING
suffix:semicolon
id|dbg
(paren
l_string|&quot;%s: roothub graceful disconnect&quot;
comma
id|hcd-&gt;self.bus_name
)paren
suffix:semicolon
id|usb_disconnect
(paren
op_amp
id|hub
)paren
suffix:semicolon
id|hcd-&gt;driver-&gt;stop
(paren
id|hcd
)paren
suffix:semicolon
id|hcd_buffer_destroy
(paren
id|hcd
)paren
suffix:semicolon
id|hcd-&gt;state
op_assign
id|USB_STATE_HALT
suffix:semicolon
id|free_irq
(paren
id|hcd-&gt;irq
comma
id|hcd
)paren
suffix:semicolon
id|usb_deregister_bus
(paren
op_amp
id|hcd-&gt;self
)paren
suffix:semicolon
id|base
op_assign
id|hcd-&gt;regs
suffix:semicolon
id|hcd-&gt;driver-&gt;hcd_free
(paren
id|hcd
)paren
suffix:semicolon
id|omap_stop_hc
c_func
(paren
id|dev
)paren
suffix:semicolon
id|release_mem_region
c_func
(paren
id|dev-&gt;res.start
comma
id|dev-&gt;res.end
op_minus
id|dev-&gt;res.start
op_plus
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*-------------------------------------------------------------------------*/
r_static
r_int
id|__devinit
DECL|function|ohci_omap_start
id|ohci_omap_start
(paren
r_struct
id|usb_hcd
op_star
id|hcd
)paren
(brace
r_struct
id|ohci_hcd
op_star
id|ohci
op_assign
id|hcd_to_ohci
(paren
id|hcd
)paren
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|hcd-&gt;pdev
)paren
(brace
id|ohci-&gt;hcca
op_assign
id|pci_alloc_consistent
(paren
id|hcd-&gt;pdev
comma
r_sizeof
op_star
id|ohci-&gt;hcca
comma
op_amp
id|ohci-&gt;hcca_dma
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ohci-&gt;hcca
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
(paren
id|ohci-&gt;hcca
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ohci_hcca
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|ohci_mem_init
(paren
id|ohci
)paren
)paren
OL
l_int|0
)paren
(brace
id|ohci_stop
(paren
id|hcd
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|ohci-&gt;regs
op_assign
id|hcd-&gt;regs
suffix:semicolon
r_if
c_cond
(paren
id|hc_reset
(paren
id|ohci
)paren
OL
l_int|0
)paren
(brace
id|ohci_stop
(paren
id|hcd
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hc_start
(paren
id|ohci
)paren
OL
l_int|0
)paren
(brace
id|err
(paren
l_string|&quot;can&squot;t start %s&quot;
comma
id|ohci-&gt;hcd.self.bus_name
)paren
suffix:semicolon
id|ohci_stop
(paren
id|hcd
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|create_debug_files
(paren
id|ohci
)paren
suffix:semicolon
macro_line|#ifdef&t;DEBUG
id|ohci_dump
(paren
id|ohci
comma
l_int|1
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*-------------------------------------------------------------------------*/
DECL|variable|ohci_omap_hc_driver
r_static
r_const
r_struct
id|hc_driver
id|ohci_omap_hc_driver
op_assign
(brace
dot
id|description
op_assign
id|hcd_name
comma
multiline_comment|/*&n;&t; * generic hardware linkage&n;&t; */
dot
id|irq
op_assign
id|ohci_irq
comma
dot
id|flags
op_assign
id|HCD_USB11
comma
multiline_comment|/*&n;&t; * basic lifecycle operations&n;&t; */
dot
id|start
op_assign
id|ohci_omap_start
comma
macro_line|#ifdef&t;CONFIG_PM
multiline_comment|/* suspend:&t;&t;ohci_omap_suspend,  -- tbd */
multiline_comment|/* resume:&t;&t;ohci_omap_resume,   -- tbd */
macro_line|#endif
dot
id|stop
op_assign
id|ohci_stop
comma
multiline_comment|/*&n;&t; * memory lifecycle (except per-request)&n;&t; */
dot
id|hcd_alloc
op_assign
id|ohci_hcd_alloc
comma
dot
id|hcd_free
op_assign
id|ohci_hcd_free
comma
multiline_comment|/*&n;&t; * managing i/o requests and associated device resources&n;&t; */
dot
id|urb_enqueue
op_assign
id|ohci_urb_enqueue
comma
dot
id|urb_dequeue
op_assign
id|ohci_urb_dequeue
comma
dot
id|endpoint_disable
op_assign
id|ohci_endpoint_disable
comma
multiline_comment|/*&n;&t; * scheduling support&n;&t; */
dot
id|get_frame_number
op_assign
id|ohci_get_frame
comma
multiline_comment|/*&n;&t; * root hub support&n;&t; */
dot
id|hub_status_data
op_assign
id|ohci_hub_status_data
comma
dot
id|hub_control
op_assign
id|ohci_hub_control
comma
)brace
suffix:semicolon
multiline_comment|/*-------------------------------------------------------------------------*/
DECL|function|ohci_hcd_omap_drv_probe
r_static
r_int
id|ohci_hcd_omap_drv_probe
c_func
(paren
r_struct
id|omap_dev
op_star
id|dev
)paren
(brace
r_struct
id|usb_hcd
op_star
id|hcd
op_assign
l_int|NULL
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|usb_disabled
c_func
(paren
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|ret
op_assign
id|usb_hcd_omap_probe
c_func
(paren
op_amp
id|ohci_omap_hc_driver
comma
op_amp
id|hcd
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|omap_set_drvdata
c_func
(paren
id|dev
comma
id|hcd
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|ohci_hcd_omap_drv_remove
r_static
r_int
id|ohci_hcd_omap_drv_remove
c_func
(paren
r_struct
id|omap_dev
op_star
id|dev
)paren
(brace
r_struct
id|usb_hcd
op_star
id|hcd
op_assign
id|omap_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
id|usb_hcd_omap_remove
c_func
(paren
id|hcd
comma
id|dev
)paren
suffix:semicolon
id|omap_set_drvdata
c_func
(paren
id|dev
comma
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Driver definition to register with the OMAP bus&n; */
DECL|variable|ohci_hcd_omap_driver
r_static
r_struct
id|omap_driver
id|ohci_hcd_omap_driver
op_assign
(brace
dot
id|drv
op_assign
(brace
dot
id|name
op_assign
id|OMAP_OHCI_NAME
comma
)brace
comma
dot
id|devid
op_assign
id|OMAP_OCP_DEVID_USB
comma
dot
id|busid
op_assign
id|OMAP_BUS_OCP
comma
dot
id|clocks
op_assign
l_int|0
comma
dot
id|probe
op_assign
id|ohci_hcd_omap_drv_probe
comma
dot
id|remove
op_assign
id|ohci_hcd_omap_drv_remove
comma
)brace
suffix:semicolon
multiline_comment|/* Any dma_mask must be set for OHCI to work */
DECL|variable|omap_dmamask
r_static
id|u64
id|omap_dmamask
op_assign
l_int|0xffffffffUL
suffix:semicolon
multiline_comment|/*&n; * Device definition to match the driver above&n; */
DECL|variable|ohci_hcd_omap_device
r_static
r_struct
id|omap_dev
id|ohci_hcd_omap_device
op_assign
(brace
dot
id|name
op_assign
id|OMAP_OHCI_NAME
comma
dot
id|devid
op_assign
id|OMAP_OCP_DEVID_USB
comma
dot
id|busid
op_assign
id|OMAP_BUS_OCP
comma
dot
id|mapbase
op_assign
(paren
r_void
op_star
)paren
id|OMAP_OHCI_BASE
comma
dot
id|dma_mask
op_assign
op_amp
id|omap_dmamask
comma
multiline_comment|/* Needed only for OHCI */
dot
id|res
op_assign
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
id|OMAP_OHCI_SIZE
comma
)brace
comma
dot
id|irq
op_assign
(brace
id|INT_OHCI
comma
)brace
comma
)brace
suffix:semicolon
DECL|function|ohci_hcd_omap_init
r_static
r_int
id|__init
id|ohci_hcd_omap_init
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
id|dbg
(paren
id|DRIVER_INFO
l_string|&quot; (OMAP)&quot;
)paren
suffix:semicolon
id|dbg
(paren
l_string|&quot;block sizes: ed %d td %d&bslash;n&quot;
comma
r_sizeof
(paren
r_struct
id|ed
)paren
comma
r_sizeof
(paren
r_struct
id|td
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hmc_mode
template_param
l_int|25
)paren
id|hmc_mode
op_assign
id|default_hmc_mode
suffix:semicolon
multiline_comment|/* Register the driver with OMAP bus */
id|ret
op_assign
id|omap_driver_register
c_func
(paren
op_amp
id|ohci_hcd_omap_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|0
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* Register the device with OMAP bus */
id|ret
op_assign
id|omap_device_register
c_func
(paren
op_amp
id|ohci_hcd_omap_device
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|0
)paren
(brace
id|omap_driver_unregister
c_func
(paren
op_amp
id|ohci_hcd_omap_driver
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
id|MODULE_PARM
c_func
(paren
id|hmc_mode
comma
l_string|&quot;hmc_mode&quot;
)paren
suffix:semicolon
DECL|function|ohci_hcd_omap_cleanup
r_static
r_void
id|__exit
id|ohci_hcd_omap_cleanup
(paren
r_void
)paren
(brace
id|omap_device_unregister
c_func
(paren
op_amp
id|ohci_hcd_omap_device
)paren
suffix:semicolon
id|omap_driver_unregister
c_func
(paren
op_amp
id|ohci_hcd_omap_driver
)paren
suffix:semicolon
)brace
DECL|variable|ohci_hcd_omap_init
id|module_init
(paren
id|ohci_hcd_omap_init
)paren
suffix:semicolon
DECL|variable|ohci_hcd_omap_cleanup
id|module_exit
(paren
id|ohci_hcd_omap_cleanup
)paren
suffix:semicolon
eof
