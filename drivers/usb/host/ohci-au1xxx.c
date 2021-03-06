multiline_comment|/*&n; * OHCI HCD (Host Controller Driver) for USB.&n; *&n; * (C) Copyright 1999 Roman Weissgaerber &lt;weissg@vienna.at&gt;&n; * (C) Copyright 2000-2002 David Brownell &lt;dbrownell@users.sourceforge.net&gt;&n; * (C) Copyright 2002 Hewlett-Packard Company&n; *&n; * Bus Glue for AMD Alchemy Au1xxx&n; *&n; * Written by Christopher Hoover &lt;ch@hpl.hp.com&gt;&n; * Based on fragments of previous driver by Rusell King et al.&n; *&n; * Modified for LH7A404 from ohci-sa1111.c&n; *  by Durgesh Pattamatta &lt;pattamattad@sharpsec.com&gt;&n; * Modified for AMD Alchemy Au1xxx&n; *  by Matt Porter &lt;mporter@kernel.crashing.org&gt;&n; *&n; * This file is licenced under the GPL.&n; */
macro_line|#include &lt;asm/mach-au1x00/au1000.h&gt;
DECL|macro|USBH_ENABLE_BE
mdefine_line|#define USBH_ENABLE_BE (1&lt;&lt;0)
DECL|macro|USBH_ENABLE_C
mdefine_line|#define USBH_ENABLE_C  (1&lt;&lt;1)
DECL|macro|USBH_ENABLE_E
mdefine_line|#define USBH_ENABLE_E  (1&lt;&lt;2)
DECL|macro|USBH_ENABLE_CE
mdefine_line|#define USBH_ENABLE_CE (1&lt;&lt;3)
DECL|macro|USBH_ENABLE_RD
mdefine_line|#define USBH_ENABLE_RD (1&lt;&lt;4)
macro_line|#ifdef __LITTLE_ENDIAN
DECL|macro|USBH_ENABLE_INIT
mdefine_line|#define USBH_ENABLE_INIT (USBH_ENABLE_CE | USBH_ENABLE_E | USBH_ENABLE_C)
macro_line|#elif __BIG_ENDIAN
DECL|macro|USBH_ENABLE_INIT
mdefine_line|#define USBH_ENABLE_INIT (USBH_ENABLE_CE | USBH_ENABLE_E | USBH_ENABLE_C | USBH_ENABLE_BE)
macro_line|#else
macro_line|#error not byte order defined
macro_line|#endif
r_extern
r_int
id|usb_disabled
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*-------------------------------------------------------------------------*/
DECL|function|au1xxx_start_hc
r_static
r_void
id|au1xxx_start_hc
c_func
(paren
r_struct
id|platform_device
op_star
id|dev
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
id|__FILE__
l_string|&quot;: starting Au1xxx OHCI USB Controller&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* enable host controller */
id|au_writel
c_func
(paren
id|USBH_ENABLE_CE
comma
id|USB_HOST_CONFIG
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1000
)paren
suffix:semicolon
id|au_writel
c_func
(paren
id|USBH_ENABLE_INIT
comma
id|USB_HOST_CONFIG
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1000
)paren
suffix:semicolon
multiline_comment|/* wait for reset complete (read register twice; see au1500 errata) */
r_while
c_loop
(paren
id|au_readl
c_func
(paren
id|USB_HOST_CONFIG
)paren
comma
op_logical_neg
(paren
id|au_readl
c_func
(paren
id|USB_HOST_CONFIG
)paren
op_amp
id|USBH_ENABLE_RD
)paren
)paren
id|udelay
c_func
(paren
l_int|1000
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
id|__FILE__
l_string|&quot;: Clock to USB host has been enabled &bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|au1xxx_stop_hc
r_static
r_void
id|au1xxx_stop_hc
c_func
(paren
r_struct
id|platform_device
op_star
id|dev
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
id|__FILE__
l_string|&quot;: stopping Au1xxx OHCI USB Controller&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Disable clock */
id|au_writel
c_func
(paren
id|readl
c_func
(paren
(paren
r_void
op_star
)paren
id|USB_HOST_CONFIG
)paren
op_amp
op_complement
id|USBH_ENABLE_CE
comma
id|USB_HOST_CONFIG
)paren
suffix:semicolon
)brace
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* configure so an HC device and id are always provided */
multiline_comment|/* always called with process context; sleeping is OK */
multiline_comment|/**&n; * usb_hcd_au1xxx_probe - initialize Au1xxx-based HCDs&n; * Context: !in_interrupt()&n; *&n; * Allocates basic resources for this USB host controller, and&n; * then invokes the start() method for the HCD associated with it&n; * through the hotplug entry&squot;s driver_data.&n; *&n; */
DECL|function|usb_hcd_au1xxx_probe
r_int
id|usb_hcd_au1xxx_probe
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
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;resource
(braket
l_int|1
)braket
dot
id|flags
op_ne
id|IORESOURCE_IRQ
)paren
(brace
id|pr_debug
(paren
l_string|&quot;resource[1] is not IORESOURCE_IRQ&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
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
id|dev-&gt;dev
comma
l_string|&quot;au1xxx&quot;
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
id|dev-&gt;resource
(braket
l_int|0
)braket
dot
id|start
suffix:semicolon
id|hcd-&gt;rsrc_len
op_assign
id|dev-&gt;resource
(braket
l_int|0
)braket
dot
id|end
op_minus
id|dev-&gt;resource
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
id|pr_debug
c_func
(paren
l_string|&quot;request_mem_region failed&quot;
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
l_string|&quot;ioremap failed&quot;
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
id|au1xxx_start_hc
c_func
(paren
id|dev
)paren
suffix:semicolon
id|ohci_hcd_init
c_func
(paren
id|hcd_to_ohci
c_func
(paren
id|hcd
)paren
)paren
suffix:semicolon
id|retval
op_assign
id|usb_add_hcd
c_func
(paren
id|hcd
comma
id|dev-&gt;resource
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
id|au1xxx_stop_hc
c_func
(paren
id|dev
)paren
suffix:semicolon
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
multiline_comment|/**&n; * usb_hcd_au1xxx_remove - shutdown processing for Au1xxx-based HCDs&n; * @dev: USB Host Controller being removed&n; * Context: !in_interrupt()&n; *&n; * Reverses the effect of usb_hcd_au1xxx_probe(), first invoking&n; * the HCD&squot;s stop() method.  It is always called from a thread&n; * context, normally &quot;rmmod&quot;, &quot;apmd&quot;, or something similar.&n; *&n; */
DECL|function|usb_hcd_au1xxx_remove
r_void
id|usb_hcd_au1xxx_remove
(paren
r_struct
id|usb_hcd
op_star
id|hcd
comma
r_struct
id|platform_device
op_star
id|dev
)paren
(brace
id|usb_remove_hcd
c_func
(paren
id|hcd
)paren
suffix:semicolon
id|au1xxx_stop_hc
c_func
(paren
id|dev
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
DECL|function|ohci_au1xxx_start
id|ohci_au1xxx_start
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
id|ohci_dbg
(paren
id|ohci
comma
l_string|&quot;ohci_au1xxx_start, ohci:%p&quot;
comma
id|ohci
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|ohci_init
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
DECL|variable|ohci_au1xxx_hc_driver
r_static
r_const
r_struct
id|hc_driver
id|ohci_au1xxx_hc_driver
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
l_string|&quot;Au1xxx OHCI&quot;
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
id|ohci_au1xxx_start
comma
macro_line|#ifdef&t;CONFIG_PM
multiline_comment|/* suspend:&t;&t;ohci_au1xxx_suspend,  -- tbd */
multiline_comment|/* resume:&t;&t;ohci_au1xxx_resume,   -- tbd */
macro_line|#endif /*CONFIG_PM*/
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
)brace
suffix:semicolon
multiline_comment|/*-------------------------------------------------------------------------*/
DECL|function|ohci_hcd_au1xxx_drv_probe
r_static
r_int
id|ohci_hcd_au1xxx_drv_probe
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
id|pr_debug
(paren
l_string|&quot;In ohci_hcd_au1xxx_drv_probe&quot;
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
id|ret
op_assign
id|usb_hcd_au1xxx_probe
c_func
(paren
op_amp
id|ohci_au1xxx_hc_driver
comma
id|pdev
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|ohci_hcd_au1xxx_drv_remove
r_static
r_int
id|ohci_hcd_au1xxx_drv_remove
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
id|usb_hcd_au1xxx_remove
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
multiline_comment|/*TBD*/
multiline_comment|/*static int ohci_hcd_au1xxx_drv_suspend(struct device *dev)&n;{&n;&t;struct platform_device *pdev = to_platform_device(dev);&n;&t;struct usb_hcd *hcd = dev_get_drvdata(dev);&n;&n;&t;return 0;&n;}&n;static int ohci_hcd_au1xxx_drv_resume(struct device *dev)&n;{&n;&t;struct platform_device *pdev = to_platform_device(dev);&n;&t;struct usb_hcd *hcd = dev_get_drvdata(dev);&n;&n;&t;return 0;&n;}&n;*/
DECL|variable|ohci_hcd_au1xxx_driver
r_static
r_struct
id|device_driver
id|ohci_hcd_au1xxx_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;au1xxx-ohci&quot;
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
id|ohci_hcd_au1xxx_drv_probe
comma
dot
id|remove
op_assign
id|ohci_hcd_au1xxx_drv_remove
comma
multiline_comment|/*.suspend&t;= ohci_hcd_au1xxx_drv_suspend, */
multiline_comment|/*.resume&t;= ohci_hcd_au1xxx_drv_resume, */
)brace
suffix:semicolon
DECL|function|ohci_hcd_au1xxx_init
r_static
r_int
id|__init
id|ohci_hcd_au1xxx_init
(paren
r_void
)paren
(brace
id|pr_debug
(paren
id|DRIVER_INFO
l_string|&quot; (Au1xxx)&quot;
)paren
suffix:semicolon
id|pr_debug
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
id|ohci_hcd_au1xxx_driver
)paren
suffix:semicolon
)brace
DECL|function|ohci_hcd_au1xxx_cleanup
r_static
r_void
id|__exit
id|ohci_hcd_au1xxx_cleanup
(paren
r_void
)paren
(brace
id|driver_unregister
c_func
(paren
op_amp
id|ohci_hcd_au1xxx_driver
)paren
suffix:semicolon
)brace
DECL|variable|ohci_hcd_au1xxx_init
id|module_init
(paren
id|ohci_hcd_au1xxx_init
)paren
suffix:semicolon
DECL|variable|ohci_hcd_au1xxx_cleanup
id|module_exit
(paren
id|ohci_hcd_au1xxx_cleanup
)paren
suffix:semicolon
eof
