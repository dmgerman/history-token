multiline_comment|/*&n; * OHCI HCD (Host Controller Driver) for USB.&n; *&n; * (C) Copyright 1999 Roman Weissgaerber &lt;weissg@vienna.at&gt;&n; * (C) Copyright 2000-2002 David Brownell &lt;dbrownell@users.sourceforge.net&gt;&n; * (C) Copyright 2002 Hewlett-Packard Company&n; * (C) Copyright 2003-2005 MontaVista Software Inc.&n; * &n; * Bus Glue for PPC On-Chip OHCI driver&n; * Tested on Freescale MPC5200 and IBM STB04xxx&n; *&n; * Modified by Dale Farnsworth &lt;dale@farnsworth.org&gt; from ohci-sa1111.c&n; *&n; * This file is licenced under the GPL.&n; */
macro_line|#include &lt;asm/usb.h&gt;
multiline_comment|/* configure so an HC device and id are always provided */
multiline_comment|/* always called with process context; sleeping is OK */
multiline_comment|/**&n; * usb_hcd_ppc_soc_probe - initialize On-Chip HCDs&n; * Context: !in_interrupt()&n; *&n; * Allocates basic resources for this USB host controller, and&n; * then invokes the start() method for the HCD associated with it&n; * through the hotplug entry&squot;s driver_data.&n; *&n; * Store this function in the HCD&squot;s struct pci_driver as probe().&n; */
DECL|function|usb_hcd_ppc_soc_probe
r_static
r_int
id|usb_hcd_ppc_soc_probe
c_func
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
r_struct
id|resource
op_star
id|res
suffix:semicolon
r_int
id|irq
suffix:semicolon
r_struct
id|usb_hcd_platform_data
op_star
id|pd
op_assign
id|pdev-&gt;dev.platform_data
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;initializing PPC-SOC USB Controller&bslash;n&quot;
)paren
suffix:semicolon
id|res
op_assign
id|platform_get_resource
c_func
(paren
id|pdev
comma
id|IORESOURCE_IRQ
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
(brace
id|pr_debug
c_func
(paren
id|__FILE__
l_string|&quot;: no irq&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|irq
op_assign
id|res-&gt;start
suffix:semicolon
id|res
op_assign
id|platform_get_resource
c_func
(paren
id|pdev
comma
id|IORESOURCE_MEM
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
(brace
id|pr_debug
c_func
(paren
id|__FILE__
l_string|&quot;: no reg addr&bslash;n&quot;
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
c_func
(paren
id|driver
comma
op_amp
id|pdev-&gt;dev
comma
l_string|&quot;PPC-SOC USB&quot;
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
id|res-&gt;start
suffix:semicolon
id|hcd-&gt;rsrc_len
op_assign
id|res-&gt;end
op_minus
id|res-&gt;start
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
id|pr_debug
c_func
(paren
id|__FILE__
l_string|&quot;: request_mem_region failed&bslash;n&quot;
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
id|hcd-&gt;regs
op_assign
id|ioremap
c_func
(paren
id|hcd-&gt;rsrc_start
comma
id|hcd-&gt;rsrc_len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hcd-&gt;regs
)paren
(brace
id|pr_debug
c_func
(paren
id|__FILE__
l_string|&quot;: ioremap failed&bslash;n&quot;
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|err2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pd-&gt;start
op_logical_and
(paren
id|retval
op_assign
id|pd
op_member_access_from_pointer
id|start
c_func
(paren
id|pdev
)paren
)paren
)paren
r_goto
id|err3
suffix:semicolon
id|ohci
op_assign
id|hcd_to_ohci
c_func
(paren
id|hcd
)paren
suffix:semicolon
id|ohci-&gt;flags
op_or_assign
id|OHCI_BIG_ENDIAN
suffix:semicolon
id|ohci_hcd_init
c_func
(paren
id|ohci
)paren
suffix:semicolon
id|retval
op_assign
id|usb_add_hcd
c_func
(paren
id|hcd
comma
id|irq
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
id|pr_debug
c_func
(paren
l_string|&quot;Removing PPC-SOC USB Controller&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pd
op_logical_and
id|pd-&gt;stop
)paren
id|pd
op_member_access_from_pointer
id|stop
c_func
(paren
id|pdev
)paren
suffix:semicolon
id|err3
suffix:colon
id|iounmap
c_func
(paren
id|hcd-&gt;regs
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
multiline_comment|/**&n; * usb_hcd_ppc_soc_remove - shutdown processing for On-Chip HCDs&n; * @pdev: USB Host Controller being removed&n; * Context: !in_interrupt()&n; *&n; * Reverses the effect of usb_hcd_ppc_soc_probe(), first invoking&n; * the HCD&squot;s stop() method.  It is always called from a thread&n; * context, normally &quot;rmmod&quot;, &quot;apmd&quot;, or something similar.&n; *&n; */
DECL|function|usb_hcd_ppc_soc_remove
r_static
r_void
id|usb_hcd_ppc_soc_remove
c_func
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
r_struct
id|usb_hcd_platform_data
op_star
id|pd
op_assign
id|pdev-&gt;dev.platform_data
suffix:semicolon
id|usb_remove_hcd
c_func
(paren
id|hcd
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;stopping PPC-SOC USB Controller&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pd
op_logical_and
id|pd-&gt;stop
)paren
id|pd
op_member_access_from_pointer
id|stop
c_func
(paren
id|pdev
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|hcd-&gt;regs
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
id|usb_hcd_put
c_func
(paren
id|hcd
)paren
suffix:semicolon
)brace
r_static
r_int
id|__devinit
DECL|function|ohci_ppc_soc_start
id|ohci_ppc_soc_start
c_func
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
c_func
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
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|ohci_run
c_func
(paren
id|ohci
)paren
)paren
OL
l_int|0
)paren
(brace
id|err
c_func
(paren
l_string|&quot;can&squot;t start %s&quot;
comma
id|ohci_to_hcd
c_func
(paren
id|ohci
)paren
op_member_access_from_pointer
id|self.bus_name
)paren
suffix:semicolon
id|ohci_stop
c_func
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
DECL|variable|ohci_ppc_soc_hc_driver
r_static
r_const
r_struct
id|hc_driver
id|ohci_ppc_soc_hc_driver
op_assign
(brace
dot
id|description
op_assign
id|hcd_name
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
id|ohci_ppc_soc_start
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
DECL|function|ohci_hcd_ppc_soc_drv_probe
r_static
r_int
id|ohci_hcd_ppc_soc_drv_probe
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
id|usb_hcd_ppc_soc_probe
c_func
(paren
op_amp
id|ohci_ppc_soc_hc_driver
comma
id|pdev
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|ohci_hcd_ppc_soc_drv_remove
r_static
r_int
id|ohci_hcd_ppc_soc_drv_remove
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
id|usb_hcd_ppc_soc_remove
c_func
(paren
id|hcd
comma
id|pdev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ohci_hcd_ppc_soc_driver
r_static
r_struct
id|device_driver
id|ohci_hcd_ppc_soc_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;ppc-soc-ohci&quot;
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
id|ohci_hcd_ppc_soc_drv_probe
comma
dot
id|remove
op_assign
id|ohci_hcd_ppc_soc_drv_remove
comma
macro_line|#if&t;defined(CONFIG_USB_SUSPEND) || defined(CONFIG_PM)
multiline_comment|/*.suspend&t;= ohci_hcd_ppc_soc_drv_suspend,*/
multiline_comment|/*.resume&t;= ohci_hcd_ppc_soc_drv_resume,*/
macro_line|#endif
)brace
suffix:semicolon
DECL|function|ohci_hcd_ppc_soc_init
r_static
r_int
id|__init
id|ohci_hcd_ppc_soc_init
c_func
(paren
r_void
)paren
(brace
id|pr_debug
c_func
(paren
id|DRIVER_INFO
l_string|&quot; (PPC SOC)&bslash;n&quot;
)paren
suffix:semicolon
id|pr_debug
c_func
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
r_return
id|driver_register
c_func
(paren
op_amp
id|ohci_hcd_ppc_soc_driver
)paren
suffix:semicolon
)brace
DECL|function|ohci_hcd_ppc_soc_cleanup
r_static
r_void
id|__exit
id|ohci_hcd_ppc_soc_cleanup
c_func
(paren
r_void
)paren
(brace
id|driver_unregister
c_func
(paren
op_amp
id|ohci_hcd_ppc_soc_driver
)paren
suffix:semicolon
)brace
DECL|variable|ohci_hcd_ppc_soc_init
id|module_init
c_func
(paren
id|ohci_hcd_ppc_soc_init
)paren
suffix:semicolon
DECL|variable|ohci_hcd_ppc_soc_cleanup
id|module_exit
c_func
(paren
id|ohci_hcd_ppc_soc_cleanup
)paren
suffix:semicolon
eof
