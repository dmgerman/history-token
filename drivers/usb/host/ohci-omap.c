multiline_comment|/*&n; * OHCI HCD (Host Controller Driver) for USB.&n; *&n; * (C) Copyright 1999 Roman Weissgaerber &lt;weissg@vienna.at&gt;&n; * (C) Copyright 2000-2004 David Brownell &lt;dbrownell@users.sourceforge.net&gt;&n; * (C) Copyright 2002 Hewlett-Packard Company&n; * &n; * OMAP Bus Glue&n; *&n; * Written by Christopher Hoover &lt;ch@hpl.hp.com&gt;&n; * Based on fragments of previous driver by Russell King et al.&n; *&n; * Modified for OMAP from ohci-sa1111.c by Tony Lindgren &lt;tony@atomide.com&gt;&n; * Based on the 2.4 OMAP OHCI driver originally done by MontaVista Software Inc.&n; *&n; * This file is licenced under the GPL.&n; */
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/arch/hardware.h&gt;
macro_line|#include &lt;asm/arch/mux.h&gt;
macro_line|#include &lt;asm/arch/irqs.h&gt;
macro_line|#include &lt;asm/arch/gpio.h&gt;
macro_line|#include &lt;asm/arch/fpga.h&gt;
macro_line|#include &lt;asm/arch/usb.h&gt;
macro_line|#include &quot;ohci-omap.h&quot;
macro_line|#ifndef CONFIG_ARCH_OMAP
macro_line|#error &quot;This file is OMAP bus glue.  CONFIG_OMAP must be defined.&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_TPS65010
macro_line|#include &lt;asm/arch/tps65010.h&gt;
macro_line|#else
DECL|macro|LOW
mdefine_line|#define LOW&t;0
DECL|macro|HIGH
mdefine_line|#define HIGH&t;1
DECL|macro|GPIO1
mdefine_line|#define GPIO1&t;1
DECL|function|tps65010_set_gpio_out_value
r_static
r_inline
r_int
id|tps65010_set_gpio_out_value
c_func
(paren
r_int
id|gpio
comma
r_int
id|value
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
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
multiline_comment|/*&n; * OHCI clock initialization for OMAP-1510 and 16xx&n; */
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
multiline_comment|/* for 1510, 48MHz DPLL is set up in usb init */
r_if
c_cond
(paren
id|cpu_is_omap16xx
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* Enable OHCI */
id|omap_writel
c_func
(paren
id|omap_readl
c_func
(paren
id|ULPD_SOFT_REQ
)paren
op_or
id|SOFT_USB_OTG_REQ
comma
id|ULPD_SOFT_REQ
)paren
suffix:semicolon
multiline_comment|/* USB host clock request if not using OTG */
id|omap_writel
c_func
(paren
id|omap_readl
c_func
(paren
id|ULPD_SOFT_REQ
)paren
op_or
id|SOFT_USB_REQ
comma
id|ULPD_SOFT_REQ
)paren
suffix:semicolon
id|omap_writel
c_func
(paren
id|omap_readl
c_func
(paren
id|ULPD_STATUS_REQ
)paren
op_or
id|USB_HOST_DPLL_REQ
comma
id|ULPD_STATUS_REQ
)paren
suffix:semicolon
)brace
multiline_comment|/* Enable 48MHz clock to USB */
id|omap_writel
c_func
(paren
id|omap_readl
c_func
(paren
id|ULPD_CLOCK_CTRL
)paren
op_or
id|USB_MCLK_EN
comma
id|ULPD_CLOCK_CTRL
)paren
suffix:semicolon
id|omap_writel
c_func
(paren
id|omap_readl
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
id|omap_writel
c_func
(paren
id|omap_readl
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
id|omap_writel
c_func
(paren
id|omap_readl
c_func
(paren
id|ULPD_CLOCK_CTRL
)paren
op_amp
op_complement
id|USB_MCLK_EN
comma
id|ULPD_CLOCK_CTRL
)paren
suffix:semicolon
multiline_comment|/* FIXME: The DPLL stays on for now */
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Board specific gang-switched transceiver power on/off.&n; * NOTE:  OSK supplies power from DC, not battery.&n; */
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
id|machine_is_omap_innovator
c_func
(paren
)paren
op_logical_and
id|cpu_is_omap1510
c_func
(paren
)paren
)paren
id|fpga_write
c_func
(paren
id|fpga_read
c_func
(paren
id|INNOVATOR_FPGA_CAM_USB_CONTROL
)paren
op_or
(paren
(paren
l_int|1
op_lshift
l_int|5
multiline_comment|/*usb1*/
)paren
op_or
(paren
l_int|1
op_lshift
l_int|3
multiline_comment|/*usb2*/
)paren
)paren
comma
id|INNOVATOR_FPGA_CAM_USB_CONTROL
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|machine_is_omap_osk
c_func
(paren
)paren
)paren
id|tps65010_set_gpio_out_value
c_func
(paren
id|GPIO1
comma
id|LOW
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|machine_is_omap_innovator
c_func
(paren
)paren
op_logical_and
id|cpu_is_omap1510
c_func
(paren
)paren
)paren
id|fpga_write
c_func
(paren
id|fpga_read
c_func
(paren
id|INNOVATOR_FPGA_CAM_USB_CONTROL
)paren
op_amp
op_complement
(paren
(paren
l_int|1
op_lshift
l_int|5
multiline_comment|/*usb1*/
)paren
op_or
(paren
l_int|1
op_lshift
l_int|3
multiline_comment|/*usb2*/
)paren
)paren
comma
id|INNOVATOR_FPGA_CAM_USB_CONTROL
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|machine_is_omap_osk
c_func
(paren
)paren
)paren
id|tps65010_set_gpio_out_value
c_func
(paren
id|GPIO1
comma
id|HIGH
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
id|omap_writel
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
id|omap_writel
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
multiline_comment|/*&n; * OMAP-1510 specific Local Bus initialization&n; * NOTE: This assumes 32MB memory size in OMAP1510LB_MEMSIZE.&n; *       See also arch/mach-omap/memory.h for __virt_to_dma() and &n; *       __dma_to_virt() which need to match with the physical &n; *       Local Bus address below.&n; */
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
id|omap_writel
c_func
(paren
(paren
id|omap_readl
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
id|omap_writel
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
id|omap_writel
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
id|omap_writel
c_func
(paren
id|physaddr
op_rshift
l_int|16
comma
id|OMAP1510_LB_MMU_RAM_H
)paren
suffix:semicolon
id|omap_writel
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
id|omap_writel
c_func
(paren
id|tlb
op_lshift
l_int|4
comma
id|OMAP1510_LB_MMU_LCK
)paren
suffix:semicolon
id|omap_writel
c_func
(paren
l_int|0x1
comma
id|OMAP1510_LB_MMU_LD_TLB
)paren
suffix:semicolon
)brace
multiline_comment|/* Enable the walking table */
id|omap_writel
c_func
(paren
id|omap_readl
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
macro_line|#ifdef&t;CONFIG_USB_OTG
DECL|function|start_hnp
r_static
r_void
id|start_hnp
c_func
(paren
r_struct
id|ohci_hcd
op_star
id|ohci
)paren
(brace
r_const
r_int
id|port
op_assign
id|ohci_to_hcd
c_func
(paren
id|ohci
)paren
op_member_access_from_pointer
id|self.otg_port
op_minus
l_int|1
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|otg_start_hnp
c_func
(paren
id|ohci-&gt;transceiver
)paren
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|ohci-&gt;transceiver-&gt;state
op_assign
id|OTG_STATE_A_SUSPEND
suffix:semicolon
id|writel
(paren
id|RH_PS_PSS
comma
op_amp
id|ohci-&gt;regs-&gt;roothub.portstatus
(braket
id|port
)braket
)paren
suffix:semicolon
id|OTG_CTRL_REG
op_and_assign
op_complement
id|OTG_A_BUSREQ
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*-------------------------------------------------------------------------*/
DECL|function|omap_start_hc
r_static
r_int
id|omap_start_hc
c_func
(paren
r_struct
id|ohci_hcd
op_star
id|ohci
comma
r_struct
id|platform_device
op_star
id|pdev
)paren
(brace
r_struct
id|omap_usb_config
op_star
id|config
op_assign
id|pdev-&gt;dev.platform_data
suffix:semicolon
r_int
id|need_transceiver
op_assign
(paren
id|config-&gt;otg
op_ne
l_int|0
)paren
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|dev_dbg
c_func
(paren
op_amp
id|pdev-&gt;dev
comma
l_string|&quot;starting USB Controller&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|config-&gt;otg
)paren
(brace
id|ohci_to_hcd
c_func
(paren
id|ohci
)paren
op_member_access_from_pointer
id|self.otg_port
op_assign
id|config-&gt;otg
suffix:semicolon
multiline_comment|/* default/minimum OTG power budget:  8 mA */
id|ohci-&gt;power_budget
op_assign
l_int|8
suffix:semicolon
)brace
multiline_comment|/* boards can use OTG transceivers in non-OTG modes */
id|need_transceiver
op_assign
id|need_transceiver
op_logical_or
id|machine_is_omap_h2
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu_is_omap16xx
c_func
(paren
)paren
)paren
id|ocpi_enable
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef&t;CONFIG_ARCH_OMAP_OTG
r_if
c_cond
(paren
id|need_transceiver
)paren
(brace
id|ohci-&gt;transceiver
op_assign
id|otg_get_transceiver
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ohci-&gt;transceiver
)paren
(brace
r_int
id|status
op_assign
id|otg_set_host
c_func
(paren
id|ohci-&gt;transceiver
comma
op_amp
id|ohci_to_hcd
c_func
(paren
id|ohci
)paren
op_member_access_from_pointer
id|self
)paren
suffix:semicolon
id|dev_dbg
c_func
(paren
op_amp
id|pdev-&gt;dev
comma
l_string|&quot;init %s transceiver, status %d&bslash;n&quot;
comma
id|ohci-&gt;transceiver-&gt;label
comma
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
(brace
r_if
c_cond
(paren
id|ohci-&gt;transceiver
)paren
id|put_device
c_func
(paren
id|ohci-&gt;transceiver-&gt;dev
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
)brace
r_else
(brace
id|dev_err
c_func
(paren
op_amp
id|pdev-&gt;dev
comma
l_string|&quot;can&squot;t find transceiver&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
)brace
macro_line|#endif
id|omap_ohci_clock_power
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu_is_omap1510
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
(paren
id|ret
op_assign
id|ohci_init
c_func
(paren
id|ohci
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
multiline_comment|/* board-specific power switching and overcurrent support */
r_if
c_cond
(paren
id|machine_is_omap_osk
c_func
(paren
)paren
op_logical_or
id|machine_is_omap_innovator
c_func
(paren
)paren
)paren
(brace
id|u32
id|rh
op_assign
id|roothub_a
(paren
id|ohci
)paren
suffix:semicolon
multiline_comment|/* power switching (ganged by default) */
id|rh
op_and_assign
op_complement
id|RH_A_NPS
suffix:semicolon
multiline_comment|/* TPS2045 switch for internal transceiver (port 1) */
r_if
c_cond
(paren
id|machine_is_omap_osk
c_func
(paren
)paren
)paren
(brace
id|ohci-&gt;power_budget
op_assign
l_int|250
suffix:semicolon
id|rh
op_and_assign
op_complement
id|RH_A_NOCP
suffix:semicolon
multiline_comment|/* gpio9 for overcurrent detction */
id|omap_cfg_reg
c_func
(paren
id|W8_1610_GPIO9
)paren
suffix:semicolon
id|omap_request_gpio
c_func
(paren
l_int|9
)paren
suffix:semicolon
id|omap_set_gpio_direction
c_func
(paren
l_int|9
comma
l_int|1
multiline_comment|/* IN */
)paren
suffix:semicolon
multiline_comment|/* for paranoia&squot;s sake:  disable USB.PUEN */
id|omap_cfg_reg
c_func
(paren
id|W4_USB_HIGHZ
)paren
suffix:semicolon
)brace
id|ohci_writel
c_func
(paren
id|ohci
comma
id|rh
comma
op_amp
id|ohci-&gt;regs-&gt;roothub.a
)paren
suffix:semicolon
singleline_comment|// distrust_firmware = 0;
)brace
multiline_comment|/* FIXME khubd hub requests should manage power switching */
id|omap_ohci_transceiver_power
c_func
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* board init will have already handled HMC and mux setup.&n;&t; * any external transceiver should already be initialized&n;&t; * too, so all configured ports use the right signaling now.&n;&t; */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|omap_stop_hc
r_static
r_void
id|omap_stop_hc
c_func
(paren
r_struct
id|platform_device
op_star
id|pdev
)paren
(brace
id|dev_dbg
c_func
(paren
op_amp
id|pdev-&gt;dev
comma
l_string|&quot;stopping USB Controller&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * FIXME: Put the USB host controller into reset.&n;&t; */
multiline_comment|/*&n;&t; * FIXME: Stop the USB clock.&n;&t; */
singleline_comment|//omap_disable_device(dev);
)brace
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* configure so an HC device and id are always provided */
multiline_comment|/* always called with process context; sleeping is OK */
multiline_comment|/**&n; * usb_hcd_omap_probe - initialize OMAP-based HCDs&n; * Context: !in_interrupt()&n; *&n; * Allocates basic resources for this USB host controller, and&n; * then invokes the start() method for the HCD associated with it&n; * through the hotplug entry&squot;s driver_data.&n; */
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
id|platform_device
op_star
id|pdev
)paren
(brace
r_int
id|retval
suffix:semicolon
r_struct
id|usb_hcd
op_star
id|hcd
suffix:semicolon
r_struct
id|ohci_hcd
op_star
id|ohci
suffix:semicolon
r_if
c_cond
(paren
id|pdev-&gt;num_resources
op_ne
l_int|2
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;hcd probe: invalid num_resources: %i&bslash;n&quot;
comma
id|pdev-&gt;num_resources
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
id|pdev-&gt;resource
(braket
l_int|0
)braket
dot
id|flags
op_ne
id|IORESOURCE_MEM
op_logical_or
id|pdev-&gt;resource
(braket
l_int|1
)braket
dot
id|flags
op_ne
id|IORESOURCE_IRQ
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;hcd probe: invalid resource type&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|hcd
op_assign
id|usb_create_hcd
(paren
id|driver
comma
op_amp
id|pdev-&gt;dev
comma
id|pdev-&gt;dev.bus_id
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hcd
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|hcd-&gt;rsrc_start
op_assign
id|pdev-&gt;resource
(braket
l_int|0
)braket
dot
id|start
suffix:semicolon
id|hcd-&gt;rsrc_len
op_assign
id|pdev-&gt;resource
(braket
l_int|0
)braket
dot
id|end
op_minus
id|pdev-&gt;resource
(braket
l_int|0
)braket
dot
id|start
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_mem_region
c_func
(paren
id|hcd-&gt;rsrc_start
comma
id|hcd-&gt;rsrc_len
comma
id|hcd_name
)paren
)paren
(brace
id|dev_dbg
c_func
(paren
op_amp
id|pdev-&gt;dev
comma
l_string|&quot;request_mem_region failed&bslash;n&quot;
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|err1
suffix:semicolon
)brace
multiline_comment|/* FIXME: Cast to pointer from integer of different size!&n;&t; * Needs ioremap */
id|hcd-&gt;regs
op_assign
(paren
r_void
id|__iomem
op_star
)paren
(paren
id|u32
)paren
id|hcd-&gt;rsrc_start
suffix:semicolon
id|ohci
op_assign
id|hcd_to_ohci
c_func
(paren
id|hcd
)paren
suffix:semicolon
id|ohci_hcd_init
c_func
(paren
id|ohci
)paren
suffix:semicolon
id|retval
op_assign
id|omap_start_hc
c_func
(paren
id|ohci
comma
id|pdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
r_goto
id|err2
suffix:semicolon
id|retval
op_assign
id|usb_add_hcd
c_func
(paren
id|hcd
comma
id|pdev-&gt;resource
(braket
l_int|1
)braket
dot
id|start
comma
id|SA_INTERRUPT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_eq
l_int|0
)paren
r_return
id|retval
suffix:semicolon
id|omap_stop_hc
c_func
(paren
id|pdev
)paren
suffix:semicolon
id|err2
suffix:colon
id|release_mem_region
c_func
(paren
id|hcd-&gt;rsrc_start
comma
id|hcd-&gt;rsrc_len
)paren
suffix:semicolon
id|err1
suffix:colon
id|usb_put_hcd
c_func
(paren
id|hcd
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
id|platform_device
op_star
id|pdev
)paren
(brace
id|usb_remove_hcd
c_func
(paren
id|hcd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_omap_osk
c_func
(paren
)paren
)paren
id|omap_free_gpio
c_func
(paren
l_int|9
)paren
suffix:semicolon
id|omap_stop_hc
c_func
(paren
id|pdev
)paren
suffix:semicolon
id|release_mem_region
c_func
(paren
id|hcd-&gt;rsrc_start
comma
id|hcd-&gt;rsrc_len
)paren
suffix:semicolon
id|usb_put_hcd
c_func
(paren
id|hcd
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
id|omap_usb_config
op_star
id|config
suffix:semicolon
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
id|config
op_assign
id|hcd-&gt;self.controller-&gt;platform_data
suffix:semicolon
r_if
c_cond
(paren
id|config-&gt;otg
op_logical_or
id|config-&gt;rwc
)paren
id|writel
c_func
(paren
id|OHCI_CTRL_RWC
comma
op_amp
id|ohci-&gt;regs-&gt;control
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|ohci_run
(paren
id|ohci
)paren
)paren
OL
l_int|0
)paren
(brace
id|err
(paren
l_string|&quot;can&squot;t start %s&quot;
comma
id|hcd-&gt;self.bus_name
)paren
suffix:semicolon
id|ohci_stop
(paren
id|hcd
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
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
dot
id|product_desc
op_assign
l_string|&quot;OMAP OHCI&quot;
comma
dot
id|hcd_priv_size
op_assign
r_sizeof
(paren
r_struct
id|ohci_hcd
)paren
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
op_or
id|HCD_MEMORY
comma
multiline_comment|/*&n;&t; * basic lifecycle operations&n;&t; */
dot
id|start
op_assign
id|ohci_omap_start
comma
dot
id|stop
op_assign
id|ohci_stop
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
macro_line|#ifdef&t;CONFIG_USB_SUSPEND
dot
id|hub_suspend
op_assign
id|ohci_hub_suspend
comma
dot
id|hub_resume
op_assign
id|ohci_hub_resume
comma
macro_line|#endif
dot
id|start_port_reset
op_assign
id|ohci_start_port_reset
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
id|device
op_star
id|dev
)paren
(brace
r_return
id|usb_hcd_omap_probe
c_func
(paren
op_amp
id|ohci_omap_hc_driver
comma
id|to_platform_device
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
)brace
DECL|function|ohci_hcd_omap_drv_remove
r_static
r_int
id|ohci_hcd_omap_drv_remove
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|platform_device
op_star
id|pdev
op_assign
id|to_platform_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|usb_hcd
op_star
id|hcd
op_assign
id|dev_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
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
id|usb_hcd_omap_remove
c_func
(paren
id|hcd
comma
id|pdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ohci-&gt;transceiver
)paren
(brace
(paren
r_void
)paren
id|otg_set_host
c_func
(paren
id|ohci-&gt;transceiver
comma
l_int|0
)paren
suffix:semicolon
id|put_device
c_func
(paren
id|ohci-&gt;transceiver-&gt;dev
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*-------------------------------------------------------------------------*/
macro_line|#if&t;defined(CONFIG_USB_SUSPEND) || defined(CONFIG_PM)
multiline_comment|/* states match PCI usage, always suspending the root hub except that&n; * 4 ~= D3cold (ACPI D3) with clock off (resume sees reset).&n; */
DECL|function|ohci_omap_suspend
r_static
r_int
id|ohci_omap_suspend
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|u32
id|state
comma
id|u32
id|level
)paren
(brace
r_struct
id|ohci_hcd
op_star
id|ohci
op_assign
id|hcd_to_ohci
c_func
(paren
id|dev_get_drvdata
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_int
id|status
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|level
op_ne
id|SUSPEND_POWER_DOWN
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|state
op_le
id|dev-&gt;power.power_state
)paren
r_return
l_int|0
suffix:semicolon
id|dev_dbg
c_func
(paren
id|dev
comma
l_string|&quot;suspend to %d&bslash;n&quot;
comma
id|state
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|ohci_to_hcd
c_func
(paren
id|ohci
)paren
op_member_access_from_pointer
id|self.root_hub-&gt;serialize
)paren
suffix:semicolon
id|status
op_assign
id|ohci_hub_suspend
c_func
(paren
id|ohci_to_hcd
c_func
(paren
id|ohci
)paren
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
r_if
c_cond
(paren
id|state
op_ge
l_int|4
)paren
(brace
multiline_comment|/* power off + reset */
id|OTG_SYSCON_2_REG
op_and_assign
op_complement
id|UHOST_EN
suffix:semicolon
id|ohci_to_hcd
c_func
(paren
id|ohci
)paren
op_member_access_from_pointer
id|self.root_hub-&gt;state
op_assign
id|USB_STATE_SUSPENDED
suffix:semicolon
id|state
op_assign
l_int|4
suffix:semicolon
)brace
id|ohci_to_hcd
c_func
(paren
id|ohci
)paren
op_member_access_from_pointer
id|state
op_assign
id|HC_STATE_SUSPENDED
suffix:semicolon
id|dev-&gt;power.power_state
op_assign
id|state
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|ohci_to_hcd
c_func
(paren
id|ohci
)paren
op_member_access_from_pointer
id|self.root_hub-&gt;serialize
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
DECL|function|ohci_omap_resume
r_static
r_int
id|ohci_omap_resume
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|u32
id|level
)paren
(brace
r_struct
id|ohci_hcd
op_star
id|ohci
op_assign
id|hcd_to_ohci
c_func
(paren
id|dev_get_drvdata
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_int
id|status
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|level
op_ne
id|RESUME_POWER_ON
)paren
r_return
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|dev-&gt;power.power_state
)paren
(brace
r_case
l_int|0
suffix:colon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
r_if
c_cond
(paren
id|time_before
c_func
(paren
id|jiffies
comma
id|ohci-&gt;next_statechange
)paren
)paren
id|msleep
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|ohci-&gt;next_statechange
op_assign
id|jiffies
suffix:semicolon
id|OTG_SYSCON_2_REG
op_or_assign
id|UHOST_EN
suffix:semicolon
multiline_comment|/* FALLTHROUGH */
r_default
suffix:colon
id|dev_dbg
c_func
(paren
id|dev
comma
l_string|&quot;resume from %d&bslash;n&quot;
comma
id|dev-&gt;power.power_state
)paren
suffix:semicolon
macro_line|#ifdef&t;CONFIG_USB_SUSPEND
multiline_comment|/* get extra cleanup even if remote wakeup isn&squot;t in use */
id|status
op_assign
id|usb_resume_device
c_func
(paren
id|ohci_to_hcd
c_func
(paren
id|ohci
)paren
op_member_access_from_pointer
id|self.root_hub
)paren
suffix:semicolon
macro_line|#else
id|down
c_func
(paren
op_amp
id|ohci_to_hcd
c_func
(paren
id|ohci
)paren
op_member_access_from_pointer
id|self.root_hub-&gt;serialize
)paren
suffix:semicolon
id|status
op_assign
id|ohci_hub_resume
c_func
(paren
id|ohci_to_hcd
c_func
(paren
id|ohci
)paren
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|ohci_to_hcd
c_func
(paren
id|ohci
)paren
op_member_access_from_pointer
id|self.root_hub-&gt;serialize
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|status
op_eq
l_int|0
)paren
id|dev-&gt;power.power_state
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|status
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/*&n; * Driver definition to register with the OMAP bus&n; */
DECL|variable|ohci_hcd_omap_driver
r_static
r_struct
id|device_driver
id|ohci_hcd_omap_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;ohci&quot;
comma
dot
id|bus
op_assign
op_amp
id|platform_bus_type
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
macro_line|#if&t;defined(CONFIG_USB_SUSPEND) || defined(CONFIG_PM)
dot
id|suspend
op_assign
id|ohci_omap_suspend
comma
dot
id|resume
op_assign
id|ohci_omap_resume
comma
macro_line|#endif
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
id|printk
(paren
id|KERN_DEBUG
l_string|&quot;%s: &quot;
id|DRIVER_INFO
l_string|&quot; (OMAP)&bslash;n&quot;
comma
id|hcd_name
)paren
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
id|pr_debug
c_func
(paren
l_string|&quot;%s: block sizes: ed %Zd td %Zd&bslash;n&quot;
comma
id|hcd_name
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
r_return
id|driver_register
c_func
(paren
op_amp
id|ohci_hcd_omap_driver
)paren
suffix:semicolon
)brace
DECL|function|ohci_hcd_omap_cleanup
r_static
r_void
id|__exit
id|ohci_hcd_omap_cleanup
(paren
r_void
)paren
(brace
id|driver_unregister
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
